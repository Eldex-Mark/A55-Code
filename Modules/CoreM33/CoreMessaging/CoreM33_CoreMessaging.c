
#include "FreeRTOS.h"
#include "openamp/open_amp.h"

#include "platform_info.h"
#include "rsc_table.h"

#include "CoreM33_CoreMessaging.h"



#define SHUTDOWN_MSG (0xEF56A55A)



extern void *RPMsg_Platform;
extern struct rpmsg_device *RPMsg_Device; //pre-created by MainTask_entry in Renesas_MHU library

static unsigned long svcno = 1;
static struct rpmsg_endpoint rp_ept[CFG_RPMSG_SVCNO] = {0}; //static struct rpmsg_endpoint RPMsg_Endpoint = {0};
volatile static int evt_svc_unbind[CFG_RPMSG_SVCNO] = {0}; //volatile static int RPMsg_Unbind_Signal = 0;

static char test_payload [] = "This is the example reply from M33 core for incoming clock/sync signal.\n";



extern int  init_system (void);
extern void cleanup_system (void);



static int rpmsg_endpoint_cb1 (struct rpmsg_endpoint * cb_rp_ept, void * data, size_t len, uint32_t src, void * priv) {
    (void) priv; (void) src;
    static const int size = sizeof( test_payload );

    if ((*(unsigned int *) data) == SHUTDOWN_MSG) { evt_svc_unbind[1] = 1; return RPMSG_SUCCESS; }

    if ( rpmsg_send( cb_rp_ept, test_payload, size ) < 0 ) { LPERROR( "rpmsg_send failed\n" ); return -1; }

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

    ret = rpmsg_create_ept( &rp_ept[1], RPMsg_Device, CFG_RPMSG_SVC_NAME1, APP_EPT_ADDR, RPMSG_ADDR_ANY, rpmsg_endpoint_cb1, rpmsg_service_unbind1 );
    if (ret) { LPERROR( "Failed to create endpoint.\n" ); return -1; }
    /*if ( rpmsg_create_ept( &RPMsg_Endpoint, RPMsg_Device, CFG_RPMSG_SVC_NAME1, APP_EPT_ADDR, RPMSG_ADDR_ANY, CoreMessaging_receiveCallback, CoreMessaging_unbindCallback ) )
    { LPERROR("Failed to create RPMsg endpoint.\n"); return -1; }*/

    LPRINTF( "Waiting for RPMsg events...\n" );
    return 0;
}



int CoreMessagingDriver_refresh () { //check if unbound

    while (1) {
        vTaskDelay(0); //this loop should be very tight, the essential code should be done entirely in the RPMsg endpoint callback to modify variables and send them through MHU
        if ( evt_svc_unbind[ svcno ] ) break; //shutdown-request to exit?
    }

    CoreMessagingDriver_close();

    //platform_poll(RPMsg_Platform); //taskYIELD();
    return 0; //return (RPMsg_Unbind_Signal);
}



void CoreMessagingDriver_close () {
    evt_svc_unbind[ svcno ] = 0; //RPMsg_Unbind_Signal = 0; // Clear shutdown flag
}

