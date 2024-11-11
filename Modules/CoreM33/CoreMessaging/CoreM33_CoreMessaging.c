
#include <stdint.h>

#include "FreeRTOS.h"
#include "metal/alloc.h"
#include "openamp/open_amp.h"
//#include <openamp/rpmsg.h>

#include "platform_info.h"
#include "rsc_table.h"

#include "CoreM33_CoreMessaging.h"



#define RECONNECT_FLG    (1)           // 1:reconnect after exit, 0:disconnect after exit
#define RECONNECT_DLY    (10000u)
#define SHUTDOWN_MSG (0xEF56A55A)



void *CoreM33_CoreMessaging_FreeRTOS_Parameters; //should be set externally when the task is called (so lengthy passing of pvParameters through init functions is avoidable)

void                *platform; //extern void *RPMsg_Platform;
struct rpmsg_device *RPMsg_Device; //*rpdev; //extern struct rpmsg_device *RPMsg_Device; //pre-created by MainTask_entry in Renesas_MHU library

static unsigned long svcno = 1;
static struct rpmsg_endpoint rp_ept[CFG_RPMSG_SVCNO] = {0}; //static struct rpmsg_endpoint RPMsg_Endpoint = {0};
volatile static int evt_svc_unbind[CFG_RPMSG_SVCNO] = {0}; //volatile static int RPMsg_Unbind_Signal = 0;

char test_payload [] = "This is the example reply from M33 core for incoming clock/sync signal.\n";
static uint8_t *write_buffer = NULL, *transmit_buffer = NULL; //should be allocated by libmetal because otherwise cache-coherency issues can happen with writing regular memory-areas for sending


extern int  init_system (void);
extern void cleanup_system (void);
static char sync = 0;


static int rpmsg_endpoint_cb1 (struct rpmsg_endpoint * cb_rp_ept, void * data, size_t len, uint32_t src, void * priv) {
    (void) priv; (void) src;
    static const int size = sizeof( test_payload );
    static uint8_t *Temp;

    if ((*(unsigned int *) data) == SHUTDOWN_MSG) { evt_svc_unbind[1] = 1; return RPMSG_SUCCESS; }

    //Temp = transmit_buffer; transmit_buffer = write_buffer; write_buffer = Temp; //switch prepared buffer to be transmited, vice-versa

    //sync = 1;
    if ( rpmsg_send( cb_rp_ept, transmit_buffer /*payload_buffer_1*/ /*test_payload*/, size ) < 0 ) { LPERROR( "rpmsg_send failed\n" ); return -1; }
    //static int counter = 0;
    //((uint8_t*) data)[60] = (counter++) & 0x7F; //write_buffer[60] = (counter++) & 0x7F; /*payload_buffer_2[60] = (counter++) & 0x7F;*/  //test_payload[60] = (counter++) & 0x7F; //sprintf( test_payload+60, "%d", counter++ );
    //if ( rpmsg_send( cb_rp_ept, data, (int)len ) < 0 ) { LPERROR( "rpmsg_send failed\n" ); return -1; }


    return RPMSG_SUCCESS;
}
/*static int CoreMessaging_receiveCallback (struct rpmsg_endpoint* endpoint, void* received_data, size_t data_length, uint32_t sender_source_address, void* endpoint_private_data) {
    (void) endpoint_private_data; (void) sender_source_address;

    if ( * (unsigned int *) received_data == SHUTDOWN_MESSAGE ) { RPMsg_Unbind_Signal = 1; return RPMSG_SUCCESS; } // On reception of a shutdown we signal the application to terminate

    if ( rpmsg_send( endpoint, received_data, (int) data_length ) < 0 ) { LPERROR("rpmsg_send failed\n"); return -1; } // Send received_data back to master

    return RPMSG_SUCCESS;
}*/



static void rpmsg_service_unbind1 (struct rpmsg_endpoint * ept) {
    (void) ept;

    rpmsg_destroy_ept( &rp_ept[1] );
    memset( &rp_ept[1], 0x0, sizeof(struct rpmsg_endpoint) );
    evt_svc_unbind[1] = 1;
}
/*static void CoreMessaging_unbindCallback (struct rpmsg_endpoint* endpoint) {
    (void) endpoint;
    rpmsg_destroy_ept( &RPMsg_Endpoint );
    memset( &RPMsg_Endpoint, 0x0, sizeof( struct rpmsg_endpoint ) );
    RPMsg_Unbind_Signal = 1;
}*/



int CoreMessagingDriver_init () {

    int ret;
    unsigned long proc_id = * ( (unsigned long*) CoreM33_CoreMessaging_FreeRTOS_Parameters ); //pvParameters);
    unsigned long rsc_id  = * ( (unsigned long*) CoreM33_CoreMessaging_FreeRTOS_Parameters ); //pvParameters);
    int rpmsg_buffersize = 0;

    ret = init_system();
    if (ret) { LPERROR("Failed to init remoteproc device.\n"); return -1; } //goto err1; }

    ret = platform_init(proc_id, rsc_id, &platform);
    if (ret) { LPERROR("Failed to create remoteproc device.\n"); return -1; } //goto err1; }
    do {
        RPMsg_Device/*rpdev*/ = platform_create_rpmsg_vdev(platform, 0x0U, VIRTIO_DEV_SLAVE, NULL, NULL); // RTOS is Master, but this setting must remote in this release.

        if ( ( rpmsg_buffersize = rpmsg_virtio_get_buffer_size(RPMsg_Device) ) <= 0 ) return rpmsg_buffersize;
        write_buffer = (uint8_t*) metal_allocate_memory( rpmsg_buffersize - 24 );
        if (write_buffer == NULL) { LPERROR("Memory allocation failed.\n"); return -ENOMEM; }
        transmit_buffer = (uint8_t*) metal_allocate_memory( rpmsg_buffersize - 24 );
        if (transmit_buffer == NULL) { LPERROR("Memory allocation failed.\n"); return -ENOMEM; }
        strcpy( (char*) write_buffer, test_payload ); strcpy( (char*) transmit_buffer, test_payload );

        if (!RPMsg_Device/*rpdev*/) { LPERROR("Fail, platform_create_rpmsg_vdev.\n"); metal_log(METAL_LOG_INFO, "Fail, platform_create_rpmsg_vdev."); platform_cleanup(platform); return -2; } //goto err2; }

        ret = rpmsg_create_ept( &rp_ept[1], RPMsg_Device, CFG_RPMSG_SVC_NAME1, APP_EPT_ADDR, RPMSG_ADDR_ANY, rpmsg_endpoint_cb1, rpmsg_service_unbind1 );
        if (ret) { LPERROR( "Failed to create endpoint.\n" ); } //return -1; }
        /*if ( rpmsg_create_ept( &RPMsg_Endpoint, RPMsg_Device, CFG_RPMSG_SVC_NAME1, APP_EPT_ADDR, RPMSG_ADDR_ANY, CoreMessaging_receiveCallback, CoreMessaging_unbindCallback ) )
        { LPERROR("Failed to create RPMsg endpoint.\n"); return -1; }*/
        else {
            LPRINTF( "Waiting for RPMsg events...\n" );
            CoreMessagingDriver_refresh(); return 0;
        }

        CoreMessagingDriver_close ();
        vTaskDelay(RECONNECT_DLY);
    } while (RECONNECT_FLG);

    return 0;
}



int CoreMessagingDriver_refresh () { //check if unbound
    static uint8_t counter = 0;

    while (1) {
        vTaskDelay(0); //this loop should be very tight, the essential code should be done entirely in the RPMsg endpoint callback to modify variables and send them through MHU
        if ( evt_svc_unbind[ svcno ] ) break; //shutdown-request to exit?
        //if (sync) {
        //    sync = 0;
            //transmit_buffer[60] = counter++;
            //vTaskDelay(200);
        //    if ( rpmsg_send( &rp_ept[1], transmit_buffer /*payload_buffer_1*/ /*test_payload*/, sizeof( test_payload ) ) < 0 ) { LPERROR( "rpmsg_send failed\n" ); return -1; }
            //vTaskDelay(200);
        //}
    }

    evt_svc_unbind[ svcno ] = 0; //RPMsg_Unbind_Signal = 0; // Clear shutdown flag
    CoreMessagingDriver_close();

    //platform_poll(RPMsg_Platform); //taskYIELD();
    return 0; //return (RPMsg_Unbind_Signal);
}



void CoreMessagingDriver_close () {
    LPRINTF("De-initializating remoteproc\n");
    platform_release_rpmsg_vdev(platform, RPMsg_Device/*rpdev*/);
    metal_free_memory( write_buffer ); metal_free_memory( transmit_buffer );
    platform_cleanup(platform);
}

