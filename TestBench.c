//Eldex Optos Touch pump project Testbench code

#include <stdio.h>  //for printf(), etc.
#include <stdlib.h>
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
 #define  TESTBENCH_REFRESH_PERIOD     CORE_A55__GUI_REFRESH_PERIOD
 #define  COREMESSAGING_REFRESH_PERIOD CORE_A55__COREMESSAGING_REFRESH_PERIOD
 #define DELAY_MILLISECONDS(x) usleep(x * 1000)
#else
 #include "hal_data.h"
 #include "FreeRTOS.h"
 #include "FreeRTOSConfig.h"
 #include "task.h"
 #define DELAY_MILLISECONDS(x) vTaskDelay(x/portTICK_PERIOD_MS)
 #define  TESTBENCH_REFRESH_PERIOD  CORE_M33__COREMESSAGING_REFRESH_PERIOD
 extern void * CoreM33_CoreMessaging_FreeRTOS_Parameters;
 extern bsp_leds_t g_bsp_leds; //for the blinker example
#endif



static void TestBench_CoreMessaging_init ();
static void TestBench_CoreMessaging_refresh ();
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
 static void TestBench_GUI_init (int input_id, int framebuffer_id);
 static void TestBench_GUI_refresh ();
#endif



static void TestBench_init (int input_id, int framebuffer_id) {
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    (void) input_id; (void) framebuffer_id;
    //CoreM33_init();
#endif
    TestBench_CoreMessaging_init();
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    //CoreA55_CoreMessaging_init(); //CoreA55_init( input_id, framebuffer_id );
    //TestBench_CoreMessaging_refresh(); //First coremessage-update can surely happen before very 1st frame of GUI
    TestBench_GUI_init( input_id, framebuffer_id ); //CoreA55_GUI_init( input_id, framebuffer_id );
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

static void TestBench_CoreMessaging_init () {
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    CoreM33_CoreMessaging_init();
#endif
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    CoreA55_CoreMessaging_init(); //CoreA55_init( input_id, framebuffer_id );
    TestBench_CoreMessaging_refresh(); //First coremessage-update can surely happen before very 1st frame of GUI
#endif
}

#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
static void TestBench_GUI_init (int input_id, int framebuffer_id) {
    CoreA55_GUI_init( input_id, framebuffer_id );
}
#endif

static void TestBench_CoreMessaging_refresh () {
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    CoreM33_CoreMessaging_refresh();
#endif
#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
    CoreA55_CoreMessaging_refresh();
#endif
}

#if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
static void TestBench_GUI_refresh () {
    CoreA55_GUI_refresh();
}
#endif


#if (SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
void Emscripten_Loop () { //(void *arg) {
    TestBench_refresh(); //lv_task_handler();
}
#endif


#if (!defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33)

 #if (SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
    int main () {
    TestBench_init( -1, -1 );
    emscripten_set_main_loop_arg( Emscripten_Loop, NULL, (1000/TESTBENCH_REFRESH_PERIOD) /*-1*/, true );

 #else

int main (int argc, char* argv[]) {
    int InputEventID = GUI_ARGUMENT_UNINITIALIZED, FrameBufferID = GUI_ARGUMENT_UNINITIALIZED;

    if (argc<2) printf("\nUsage: TestBench [InputDeviceID] [FrameBufferID]    (Default touchscreen-ID is detected automatically.)\n\n");  // (Defaults: %d, %d\n)", _GUI_InputEventID, _GUI_FrameBufferID );
    else {
        sscanf( argv[1], "%d", &InputEventID );
        if (argc>=3) sscanf( argv[2], "%d", &FrameBufferID );
    }

    //TestBench_init( InputEventID, FrameBufferID );

    #if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
    TestBench_init( InputEventID, FrameBufferID );
    #else
    pid_t ForkedProcess = fork(); if (ForkedProcess < 0) exit(1);
    if (ForkedProcess > 0) {
        TestBench_CoreMessaging_init();
        while (1) { TestBench_CoreMessaging_refresh(); DELAY_MILLISECONDS( COREMESSAGING_REFRESH_PERIOD ); }
    }
    TestBench_GUI_init( InputEventID, FrameBufferID );
    #endif

    while (1) { //GUI-refreshment handles input/output, can be called from cyclically timed IRQ too
    #if ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
        TestBench_refresh();
    #else
        TestBench_GUI_refresh();
    #endif
        DELAY_MILLISECONDS( TESTBENCH_REFRESH_PERIOD ); //usleep( TESTBENCH_REFRESH_PERIOD * 1000 ); //wait a bit to avoid 100% CPU-usage by main thread
    }

 #endif
    return 0;
}

#else //elif (defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && SQUARELINE_BUILD_TARGET__BOARD__CORE_M33)

//The inter-CPU communication entry point of thread created by main.c
void app_CoreMessagingTask (void* pvParameters) { //Renesas FreeRTOS MHU package calls app_MainTask() through MainTask_entry created in MainTask from main()
    CoreM33_CoreMessaging_FreeRTOS_Parameters = pvParameters;
    /*if (*/ TestBench_CoreMessaging_init(); //) return;
    while (1) { TestBench_CoreMessaging_refresh(); /*DELAY_MILLISECONDS( COREMESSAGING_REFRESH_PERIOD );*/ }
}

//The essential backend code entry point, blinking LED example task: (This is the code responsible for fast blinking of blue led at startup to signal that M33 code started up.)
void app_MainTask (void* pvParameters) { //Renesas FreeRTOS MHU package calls app_MainTask() through MainTask_entry created in MainTask from main()
    (void) pvParameters;

    bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

    while (1) {
        // Enable access to the PFS registers. If using r_ioport module then register protection is automatically
        // handled. This code uses BSP IO functions to show how it is used.
        for (uint32_t i = 0; i < g_bsp_leds.led_count; i++) { // Update all board LEDs
            uint32_t pin = g_bsp_leds.p_leds[i]; // Get pin to toggle
            R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level); // Write to this pin
        }

        if (BSP_IO_LEVEL_LOW == pin_level) pin_level = BSP_IO_LEVEL_HIGH; // Toggle level for next write
        else pin_level = BSP_IO_LEVEL_LOW;

        vTaskDelay(50 / portTICK_PERIOD_MS); //vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

#endif



