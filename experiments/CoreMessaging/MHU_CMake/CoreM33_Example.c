
#include "hal_data.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"



extern bsp_leds_t g_bsp_leds;



void app_MainTask (void* pvParameters) {
    (void) pvParameters;

    bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

    while (1)
    {
        /* Enable access to the PFS registers. If using r_ioport module then register protection is automatically
         * handled. This code uses BSP IO functions to show how it is used.
         */

        /* Update all board LEDs */
        for (uint32_t i = 0; i < g_bsp_leds.led_count; i++)
        {
            /* Get pin to toggle */
            uint32_t pin = g_bsp_leds.p_leds[i];

            /* Write to this pin */
            R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level);
        }

        /* Toggle level for next write */
        if (BSP_IO_LEVEL_LOW == pin_level)
        {
            pin_level = BSP_IO_LEVEL_HIGH;
        }
        else
        {
            pin_level = BSP_IO_LEVEL_LOW;
        }

        vTaskDelay(50 / portTICK_PERIOD_MS); //vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}



#include "FreeRTOS.h"
#include "openamp/open_amp.h"
#include "platform_info.h"
#include "rsc_table.h"

extern int  init_system(void);
extern void cleanup_system(void);

#define SHUTDOWN_MSG     (0xEF56A55A)

/* Local variables */

/*-----------------------------------------------------------------------------*
 *  RPMSG callbacks setup by remoteproc_resource_init()
 *-----------------------------------------------------------------------------*/

/* Local variables */

static struct rpmsg_endpoint rp_ept[CFG_RPMSG_SVCNO] = {0};

volatile static int evt_svc_unbind[CFG_RPMSG_SVCNO] = {0};

/**
 *  Callback Function: rpmsg_endpoint_cb
 *
 *  @param[in] rp_svc
 *  @param[in] data
 *  @param[in] len
 *  @param[in] priv
 *  @param[in] src
 */
static int rpmsg_endpoint_cb0 (struct rpmsg_endpoint * cb_rp_ept, void * data, size_t len, uint32_t src, void * priv)
{
    /* service 0 */
    (void) priv;
    (void) src;

    /* On reception of a shutdown we signal the application to terminate */
    if ((*(unsigned int *) data) == SHUTDOWN_MSG)
    {
        evt_svc_unbind[0] = 1;

        return RPMSG_SUCCESS;
    }

    /* Send data back to master*/
    if (rpmsg_send(cb_rp_ept, data, (int) len) < 0)
    {
        LPERROR("rpmsg_send failed\n");

        return -1;
    }

    return RPMSG_SUCCESS;
}

static int rpmsg_endpoint_cb1 (struct rpmsg_endpoint * cb_rp_ept, void * data, size_t len, uint32_t src, void * priv)
{
    /* service 1 */
    (void) priv;
    (void) src;

    /* On reception of a shutdown we signal the application to terminate */
    if ((*(unsigned int *) data) == SHUTDOWN_MSG)
    {
        evt_svc_unbind[1] = 1;

        return RPMSG_SUCCESS;
    }

    /* Send data back to master*/
    if (rpmsg_send(cb_rp_ept, data, (int) len) < 0)
    {
        LPERROR("rpmsg_send failed\n");

        return -1;
    }

    return RPMSG_SUCCESS;
}

/**
 *  Callback Function: rpmsg_service_unbind
 *
 *  @param[in] ept
 */
static void rpmsg_service_unbind0 (struct rpmsg_endpoint * ept)
{
    (void) ept;

    /* service 0 */
    rpmsg_destroy_ept(&rp_ept[0]);
    memset(&rp_ept[0], 0x0, sizeof(struct rpmsg_endpoint));
    evt_svc_unbind[0] = 1;
}

static void rpmsg_service_unbind1 (struct rpmsg_endpoint * ept)
{
    (void) ept;

    /* service 1 */
    rpmsg_destroy_ept(&rp_ept[1]);
    memset(&rp_ept[1], 0x0, sizeof(struct rpmsg_endpoint));
    evt_svc_unbind[1] = 1;
}

/*-----------------------------------------------------------------------------*
 *  Application
 *-----------------------------------------------------------------------------*/
int app (struct rpmsg_device * rdev, void * platform, unsigned long svcno) {
    (void) platform;
    int ret;

    if (svcno == 0UL)
    {
        ret = rpmsg_create_ept(&rp_ept[0],
                               rdev,
                               CFG_RPMSG_SVC_NAME0,
                               APP_EPT_ADDR,
                               RPMSG_ADDR_ANY,
                               rpmsg_endpoint_cb0,
                               rpmsg_service_unbind0);
        if (ret)
        {
            LPERROR("Failed to create endpoint.\n");

            return -1;
        }
    }
    else
    {
        ret = rpmsg_create_ept(&rp_ept[1],
                               rdev,
                               CFG_RPMSG_SVC_NAME1,
                               APP_EPT_ADDR,
                               RPMSG_ADDR_ANY,
                               rpmsg_endpoint_cb1,
                               rpmsg_service_unbind1);
        if (ret)
        {
            LPERROR("Failed to create endpoint.\n");

            return -1;
        }
    }

    LPRINTF("Waiting for events...\n");
    while (1)
    {
        vTaskDelay(0);

        /* we got a shutdown request, exit */
        if (evt_svc_unbind[svcno])
        {
            break;
        }
    }

    /* Clear shutdown flag */
    evt_svc_unbind[svcno] = 0;

    return 0;
}



#include "openamp/open_amp.h"
#include "platform_info.h"
#include "rsc_table.h"

#define RECONNECT_FLG    (1)           /* 1:reconnect after exit, 0:disconnect after exit */
#define RECONNECT_DLY    (10000u)

void app_CoreMessagingTask (void* pvParameters) { // CoreMessaging Thread entry function

    unsigned long         proc_id = *((unsigned long*)pvParameters);
    unsigned long         rsc_id  = *((unsigned long*)pvParameters);
    struct rpmsg_device * rpdev;
    void                * platform;
    int ret;

    ret = init_system();
    if (ret)
    {
        LPERROR("Failed to init remoteproc device.\n");
        goto err1;
    }

    ret = platform_init(proc_id, rsc_id, &platform);
    if (ret)
    {
        LPERROR("Failed to create remoteproc device.\n");
        goto err1;
    }
    else
    {
        do
        {
            /* RTOS is Master, but this setting must remote in this release. */
            rpdev = platform_create_rpmsg_vdev(platform, 0x0U, VIRTIO_DEV_SLAVE, NULL, NULL);
            if (!rpdev)
            {
                LPERROR("Fail, platform_create_rpmsg_vdev.\n");
                metal_log(METAL_LOG_INFO, "Fail, platform_create_rpmsg_vdev.");
                goto err2;
            }

            /* Kick the application */
            (void) app(rpdev, platform, proc_id);

            LPRINTF("De-initializating remoteproc\n");
            platform_release_rpmsg_vdev(platform, rpdev);

            vTaskDelay(RECONNECT_DLY);
        } while (RECONNECT_FLG);
    }

err2:
    platform_cleanup(platform);
err1:

}

