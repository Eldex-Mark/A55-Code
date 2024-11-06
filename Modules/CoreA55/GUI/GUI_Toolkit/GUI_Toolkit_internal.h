//module-public header

#ifndef _GUI_TOOLKIT_INTERNAL_INCLUDED
#define _GUI_TOOLKIT_INTERNAL_INCLUDED


#include <stdbool.h>
#include <lvgl/lvgl.h>



enum { _GUI_TOOLKIT_TEMP_STRING_SIZE_MAX = 20000 };



extern char _GUI_Toolkit_TempString [_GUI_TOOLKIT_TEMP_STRING_SIZE_MAX];



bool _GUI_widgetIsSelector (lv_obj_t* widget);

lv_obj_t* _GUI_getTextareaKeyboard (lv_obj_t* textarea);



#endif //_GUI_TOOLKIT_PRIVATE_INCLUDED

