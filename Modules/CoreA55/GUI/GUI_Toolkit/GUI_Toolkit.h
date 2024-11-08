//public header //Convenience function-prototypes to use SquareLine Studio UI easier and more efficiently


#ifndef _GUI_TOOLKIT_INCLUDED
#define _GUI_TOOLKIT_INCLUDED



#include "ObserverModifier/ObserverModifier.h"



typedef struct _GUI_ScreenDescriptor { lv_obj_t* *const Screen; void (*initScreen)(void); void (*initScreenValues)(lv_event_t* event /*void*/); _GUI_Observer *Observers; _GUI_Modifier *Modifiers; } _GUI_ScreenDescriptor;



//General:
void _GUI_debug (const char* format, ...);

char* _GUI_convertIntToText (int number);
char* _GUI_convertFloatToText (float number);
int _GUI_convertTextToInt (char* text);
float _GUI_convertTextToFloat (char* text);
char* _GUI_convertIPaddressToText (uint8_t* address);
void _GUI_convertTextToIPaddress (char* text, uint8_t* address);
char* _GUI_convertStringArrayToList (char* source_strings, int sourcearray_size);

int _GUI_handleKeyRepeat (lv_indev_t* input, bool pressed, int repeat_delay, int repeat_rate, int repeat_rate_min);


//Screens:
void _GUI_loadScreen (lv_obj_t* screen);
void _GUI_loadScreenWithFade (lv_obj_t* *screen, int duration);
lv_obj_t* _GUI_getCurrentScreen ();


//Widgets:

void _GUI_setWidgetCheckedState (lv_obj_t* widget, bool value);
bool _GUI_getWidgetCheckedState (lv_obj_t* widget);
void _GUI_setWidgetFocusedState (lv_obj_t* widget, bool value);
bool _GUI_getWidgetFocusedState (lv_obj_t* widget);

void _GUI_showWidget (lv_obj_t* widget);
void _GUI_hideWidget (lv_obj_t* widget);
void _GUI_enableWidget (lv_obj_t* widget);
void _GUI_disableWidget (lv_obj_t* widget);
void _GUI_conditionalShowWidget (lv_obj_t* widget, bool condition);
void _GUI_conditionalEnableWidget (lv_obj_t* widget, bool condition);

void _GUI_setWidgetText (lv_obj_t* widget, char* text);
void _GUI_setWidgetPlaceholderText (lv_obj_t* widget, char* text);

int _GUI_getSliderValue (lv_obj_t* slider);
void _GUI_setSliderValue (lv_obj_t* slider, int value);


//Callback-related:

void _GUI_screenLoadedCallback (lv_event_t* event);

void _GUI_removeAllObjectEvents (lv_obj_t* object);

void _GUI_setScreenLoadCallback ( lv_obj_t* widget, void (*function)() );
//void _GUI_setScreenLoadStartCallback ( lv_obj_t* widget, void (*function)() );
void _GUI_setScreenLoadCallbackWithValue (lv_obj_t* screen, void (*function)(), uintptr_t user_data);
void _GUI_setScreenLoadCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data);
void _GUI_setClickCallback ( lv_obj_t* widget, void (*function)() );
void _GUI_setClickCallbackWithValue (lv_obj_t* widget, void (*function)(), uintptr_t user_data);
void _GUI_setClickCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data);
void _GUI_setPressingCallback ( lv_obj_t* widget, void (*function)() );
void _GUI_setValueChangeCallback ( lv_obj_t* widget, void (*function)() );
void _GUI_setValueChangeCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data);
void _GUI_setReadyCallback ( lv_obj_t* widget, void (*function)() );
void _GUI_setReadyCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data);
void _GUI_setCancelCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data);
void _GUI_setDefocusCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data);

//void _GUI_setClickScreenChange ( lv_obj_t* widget, lv_obj_t* screen, void (*init_function)() );


//Selectors:

uint16_t _GUI_getSelectorIndex (lv_obj_t* selector_widget);
void _GUI_setSelectorIndex (lv_obj_t* selector_widget, uint16_t index);
char* _GUI_getSelectorOption (lv_obj_t* selector_widget);
//void _GUI_clearSelectorOptions (lv_obj_t* selector_widget, char* options );
void _GUI_createSelectorOptions (lv_obj_t* selector_widget, char* options);
void _GUI_createSelectorOptionsFromStringArray (lv_obj_t* selector_widget, char* source_stringarray, int sourcearray_size);
void _GUI_createSelectorOptions_Integer (lv_obj_t* selector_widget, short min, short max, short step, char* indent);



#endif //_GUI_TOOLKIT_INCLUDED
