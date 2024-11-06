
//#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/ - but might cause issues in Windows (and VScode?)
//#ifdef SQUARELINE_BUILD_TARGET__UNIX
 //#include <SDL2/SDL.h>  //LVGL handles inclusion in lv_conf.h if SDL is enabled
//#endif

#include "lvgl/lvgl.h"


#define GUI_RESOLUTION_HORIZONTAL 800
#define GUI_RESOLUTION_VERTICAL 480


extern lv_indev_t *_GUI_InputDevice; //Needed because LVGL-9.1 doesn't seem to set indev_active and returns NULL for lv_indev_active()


void HAL_init (int input_id, int framebuffer_id);

