
#include <stdio.h>  //for sprintf, etc.
#include <stdbool.h>

#include "HAL.h"


lv_indev_t *_GUI_InputDevice = NULL; //Needed because LVGL-9.1 doesn't seem to set indev_active and returns NULL for lv_indev_active()


/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
void HAL_init (int input_id, int framebuffer_id) {
    int InputEventID = 0; //1;
    int FrameBufferID = 0;
    char* TouchScreenDeviceName = NULL;
    static char TempString [32] = "";

    if (input_id >= 0) InputEventID = input_id;
    if (framebuffer_id >= 0) FrameBufferID = framebuffer_id;

    /*Create a display*/
    static lv_display_t *display;
#if (SQUARELINE_BUILD_TARGET__UNIX || SQUARELINE_BUILD_TARGET__WINDOWS || SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
    display = lv_sdl_window_create( GUI_RESOLUTION_HORIZONTAL, GUI_RESOLUTION_VERTICAL );
#elif (SQUARELINE_BUILD_TARGET__BOARD || SQUARELINE_BUILD_TARGET__BOARD__CORE_A55)
    display = lv_linux_fbdev_create();
    sprintf( TempString, "/dev/fb%d", FrameBufferID );
    lv_linux_fbdev_set_file( display, TempString );
    //lv_linux_fbdev_set_force_refresh( disp, 1 ); //only use if really necessary! (In case of partial drawing and other issues.)
#endif

    /*Add the mouse/touchscreen as input device*/
    //static lv_indev_t *pointer;
#if (SQUARELINE_BUILD_TARGET__UNIX || SQUARELINE_BUILD_TARGET__WINDOWS || SQUARELINE_BUILD_TARGET__EMSCRIPTEN)
    _GUI_InputDevice /*pointer*/ = lv_sdl_mouse_create();
#elif (SQUARELINE_BUILD_TARGET__BOARD || SQUARELINE_BUILD_TARGET__BOARD__CORE_A55)
    sprintf( TempString, "/dev/input/event%d", InputEventID );
    TouchScreenDeviceName = lv_libinput_find_dev( LV_LIBINPUT_CAPABILITY_TOUCH, true );
    if (TouchScreenDeviceName == NULL || input_id >= 0) { TouchScreenDeviceName = TempString; }
    _GUI_InputDevice /*pointer*/ = lv_libinput_create/*lv_evdev_create*/( LV_INDEV_TYPE_POINTER, TouchScreenDeviceName /*TempString*/ );
#endif

    /*Add the keyboard as an input device*/
    //static lv_indev_t *keyboard;
    //keyboard = lv_sdl_keyboard_create();
}

