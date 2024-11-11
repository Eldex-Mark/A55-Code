
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "metal/alloc.h"
#include "openamp/open_amp.h"

#include "platform_info.h"
#include "rsc_table.h"

#include "CoreA55_CoreMessaging.h"



#define SHUTDOWN_MSG (0xEF56A55A)



static void *Priv;
static void *platform;
static struct rpmsg_device *rpdev;

static struct rpmsg_endpoint rp_ept = { 0 };
static int rnum = 0;
static int err_cnt = 0;
static char *svc_name = NULL;

static int shutdown_msg = SHUTDOWN_MSG;

char test_payload [] = "This is a test clock/sync signal for MHU communication from A55 core.\n";



extern void init_system ();
extern void cleanup_system ();

static void rpmsg_service_bind (struct rpmsg_device *rdev, const char *name, uint32_t dest);
static void rpmsg_service_unbind (struct rpmsg_endpoint *ept);
static int rpmsg_service_cb0 (struct rpmsg_endpoint *rp_ept, void *data, size_t len, uint32_t src, void *priv);
static int payload_init (struct rpmsg_device *rdev);



int app (struct rpmsg_device *rdev, void *priv, unsigned long svcno) {
    Priv = priv;
    int ret = 0;

    LPRINTF(" 1 - Send data to remote core, retrieve the echo");
    LPRINTF(" and validate its integrity ..  (Eldex)\n");


    if ( (ret = payload_init(rdev)) ) return ret; // Initialization of the payload and its related information

    LPRINTF( "Remote proc init.\n" );

    // Create RPMsg endpoint:
    if (svcno == 0) svc_name = (char *) CFG_RPMSG_SVC_NAME0;
    else svc_name = (char *) CFG_RPMSG_SVC_NAME1;

    ret = rpmsg_create_ept( &rp_ept, rdev, svc_name, APP_EPT_ADDR, RPMSG_ADDR_ANY, rpmsg_service_cb0, rpmsg_service_unbind );
    if (ret) { LPERROR( "Failed to create RPMsg endpoint.\n" ); return ret; }
    LPRINTF( "RPMSG endpoint is created.\n" );

    while ( !is_rpmsg_ept_ready(&rp_ept) ) platform_poll( priv );
    LPRINTF( "RPMSG service is created.\n" );

    return 0;
}


static void rpmsg_service_bind (struct rpmsg_device *rdev, const char *name, uint32_t dest) {
    LPRINTF( "new endpoint notification is received.\n" );
    if ( strcmp(name, svc_name) ) { LPERROR( "Unexpected name service %s.\n", name ); }
    else (void) rpmsg_create_ept( &rp_ept, rdev, svc_name, APP_EPT_ADDR, dest, rpmsg_service_cb0, rpmsg_service_unbind );
}

static void rpmsg_service_unbind (struct rpmsg_endpoint *ept) {
    (void)ept;
    rpmsg_destroy_ept( &rp_ept );
    memset( &rp_ept, 0x0, sizeof( struct rpmsg_endpoint ) );
}



static int rpmsg_service_cb0 (struct rpmsg_endpoint *cb_rp_ept, void *data, size_t len, uint32_t src, void *priv) {
    (void) cb_rp_ept; (void) src; (void) priv;

    LPRINTF( " received reply: \'%s\' ( size %lu )\r\n", (char*)data, len );
    rnum = 1;

    return 0;
}



static int payload_init (struct rpmsg_device *rdev) {
    int rpmsg_buf_size = 0;

    if ( ( rpmsg_buf_size = rpmsg_virtio_get_buffer_size(rdev) ) <= 0 ) { return rpmsg_buf_size; } // Get the maximum buffer size of a rpmsg packet
    LPRINTF( "RPMsg buffer-size: %d bytes\n", rpmsg_buf_size );
    //payload = (uint8_t*) metal_allocate_memory( max_size ); //if (!payload) { LPERROR( "memory allocation failed.\n" ); return -ENOMEM; }

    return 0;
}



int CoreMessagingDriver_init () {
    unsigned long proc_id = 0;
    unsigned long rsc_id = 0;
    int ret = 0;

    init_system(); // Initialize HW system components
    proc_id = 1;
    rsc_id = proc_id;

    ret = platform_init (proc_id, rsc_id, &platform); // Initialize platform
    if (ret) { LPERROR( "Failed to initialize platform.\n" ); ret = -1; }
    else {
        rpdev = platform_create_rpmsg_vdev( platform, 0, VIRTIO_DEV_MASTER, NULL, rpmsg_service_bind );
        if (!rpdev) { LPERROR("Failed to create rpmsg virtio device.\n"); ret = -1; }
        else { (void) app( rpdev, platform, proc_id ); }
    }
    return 0;
}



int CoreMessagingDriver_refresh () {
    int ret = 0;
    static int size = sizeof( test_payload );

    static int counter;
    test_payload[50] = (counter++) & 0x7F; //A55 allows change, why M33 doesn't then?

    ret = rpmsg_send( &rp_ept, test_payload, size );
    if (ret < 0) { LPRINTF( "Error sending data...%d\n", ret ); return -1; }
    LPRINTF( "echo test: sent \'%s\' : %d\n", test_payload, size );

    do { platform_poll( Priv ); } while (rnum == 0);
    rnum = 0;

    return 0;
}



void CoreMessagingDriver_close () {
    rpmsg_send( &rp_ept, &shutdown_msg, sizeof(int) ); // Send shutdown message to remote
    sleep( 1 );
    LPRINTF( "Quitting application .. Echo test end\n" );
    //metal_free_memory( payload );
    platform_release_rpmsg_vdev( platform, rpdev );
    LPRINTF( "Stopping application...\n" );
    platform_cleanup( platform );
    cleanup_system();
}

