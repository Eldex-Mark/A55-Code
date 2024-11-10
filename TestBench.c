//Eldex Optos Touch pump project Testbench code

#include <stdio.h>  //for printf(), etc.
#include <unistd.h> //for usleep()
#include <stdbool.h> //for bool type in C

#if (SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
 #include <emscripten.h>
#endif

#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
 #include "CoreM33_Example.h"
#endif
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
 #include "CoreA55_Example.h"
#endif


#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
 #define  TESTBENCH_REFRESH_PERIOD  CORE_A55__GUI_REFRESH_PERIOD
 #define DELAY_MILLISECONDS(x) usleep(x * 1000)
#else
 #include "FreeRTOS.h"
 #include "platform_info.h"
 #include "task.h"
 #define DELAY_MILLISECONDS(x) vTaskDelay(x/portTICK_PERIOD_MS)
 #define  TESTBENCH_REFRESH_PERIOD  CORE_M33__COREMESSAGING_REFRESH_PERIOD
#endif


static void TestBench_CoreMessaging_refresh (); static void TestBench_GUI_refresh ();


static void TestBench_init (int input_id, int framebuffer_id) {
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    (void) input_id; (void) framebuffer_id;
    CoreM33_init();
#endif
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    CoreA55_CoreMessaging_init(); //CoreA55_init( input_id, framebuffer_id );
    TestBench_CoreMessaging_refresh(); //First coremessage-update can surely happen before very 1st frame of GUI
    CoreA55_GUI_init( input_id, framebuffer_id );
#endif
}

static void TestBench_refresh () { //main loop content
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    CoreM33_refresh();
#endif
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    CoreA55_refresh();
#endif
}

static void TestBench_CoreMessaging_refresh () {
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    CoreM33_refresh();
#endif
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    CoreA55_CoreMessaging_refresh();
#endif
}

static void TestBench_GUI_refresh () {
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    CoreA55_GUI_refresh();
#endif
}


#if (SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
void Emscripten_Loop () { //(void *arg) {
    TestBench_refresh(); //lv_task_handler();
}
#endif


#if ( (!defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && !SQUARELINE_BUILD_TARGET__EMSCRIPTEN )

int main (int argc, char* argv[]) {
    int InputEventID = GUI_ARGUMENT_UNINITIALIZED, FrameBufferID = GUI_ARGUMENT_UNINITIALIZED;

    if (argc<2) printf("\nUsage: TestBench [InputDeviceID] [FrameBufferID]    (Default touchscreen-ID is detected automatically.)\n\n");  // (Defaults: %d, %d\n)", _GUI_InputEventID, _GUI_FrameBufferID );
    else {
        sscanf( argv[1], "%d", &InputEventID );
        if (argc>=3) sscanf( argv[2], "%d", &FrameBufferID );
    }
    TestBench_init( InputEventID, FrameBufferID );

#else

#if (defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && SQUARELINE_BUILD_TARGET__BOARD__CORE_M33)
struct rpmsg_device *RPMsg_Device;
void *RPMsg_Platform;
int app (struct rpmsg_device* rdev, void* platform, unsigned long parameter) { //Renesas FreeRTOS MHU package calls app() through MainTask_entry created in MainTask from main()
    (void) parameter; //(void) platform;
    RPMsg_Device = rdev; RPMsg_Platform = platform;
#else
int main () {
#endif

    TestBench_init( -1, -1 );

#endif


    #if (SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
     emscripten_set_main_loop_arg( Emscripten_Loop, NULL, (1000/TESTBENCH_REFRESH_PERIOD) /*-1*/, true );
    #else
    while (1) { //GUI-refreshment handles input/output, can be called from cyclically timed IRQ too
        TestBench_refresh();
        DELAY_MILLISECONDS( TESTBENCH_REFRESH_PERIOD ); //usleep( TESTBENCH_REFRESH_PERIOD * 1000 ); //wait a bit to avoid 100% CPU-usage by main thread
    }
    #endif

    return 0;
}

