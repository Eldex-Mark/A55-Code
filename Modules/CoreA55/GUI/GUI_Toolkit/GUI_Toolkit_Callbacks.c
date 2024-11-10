
#include "GUI_Toolkit.h"



/*static void _GUI_loadScreenEvent (lv_event_t* event) { //Emscripten freezes if there's no 'event' argument for callback
    lv_scr_load( (lv_obj_t*) lv_event_get_user_data( event ) );
}*/

void _GUI_screenLoadedCallback (lv_event_t* event) { //generic screen-loaded callback for internal functionalities (observers, modifiers)
    const _GUI_ScreenDescriptor* ScreenDescriptor = (_GUI_ScreenDescriptor*) lv_event_get_user_data( event );
    if (ScreenDescriptor->initScreen != NULL) ( *ScreenDescriptor->initScreenValues )(NULL);
    if (ScreenDescriptor->Observers != NULL) _GUI_refreshScreenObservers( ScreenDescriptor->Observers, true );
    if (ScreenDescriptor->Modifiers != NULL) _GUI_refreshScreenModifiers( ScreenDescriptor->Modifiers );
}


void _GUI_removeAllObjectEvents (lv_obj_t* object) {
    uint32_t EventCount = lv_obj_get_event_count( object );
    for (uint32_t i = 0; i < EventCount; ++i) lv_obj_remove_event( object, i );
}


inline void _GUI_setScreenLoadCallback ( lv_obj_t* screen, void (*function)() ) {
    if ( screen==NULL || !lv_obj_is_valid( screen ) ) return;
    lv_obj_remove_event_cb( screen, function ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( screen, (void(*)(lv_event_t*)) function, LV_EVENT_SCREEN_LOADED, NULL );
}
/*inline void _GUI_setScreenLoadStartCallback ( lv_obj_t* widget, void (*function)() ) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb( widget, function ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_SCREEN_LOAD_START, NULL );
}*/

inline void _GUI_setScreenLoadCallbackWithValue (lv_obj_t* screen, void (*function)(), uintptr_t user_data) {
    if ( screen==NULL || !lv_obj_is_valid( screen ) ) return;
    lv_obj_remove_event_cb_with_user_data( screen, function, (void*) user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( screen, (void(*)(lv_event_t*)) function, LV_EVENT_SCREEN_LOADED, (void*) user_data );
}
inline void _GUI_setScreenLoadCallbackWithPointer (lv_obj_t* screen, void (*function)(), void* user_data) {
    if ( screen==NULL || !lv_obj_is_valid( screen ) ) return;
    lv_obj_remove_event_cb_with_user_data( screen, function, user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( screen, (void(*)(lv_event_t*)) function, LV_EVENT_SCREEN_LOADED, user_data );
}

inline void _GUI_setClickCallback ( lv_obj_t* widget, void (*function)() ) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    if ( !lv_obj_has_flag( widget, LV_OBJ_FLAG_CLICKABLE ) ) lv_obj_add_flag( widget, LV_OBJ_FLAG_CLICKABLE );
    lv_obj_remove_event_cb( widget, function ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_CLICKED, NULL );
}
inline void _GUI_setClickCallbackWithValue (lv_obj_t* widget, void (*function)(), uintptr_t user_data) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb_with_user_data( widget, function, (void*) user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_CLICKED, (void*) user_data );
}
inline void _GUI_setClickCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb_with_user_data( widget, function, user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_CLICKED, user_data );
}

inline void _GUI_setPressingCallback ( lv_obj_t* widget, void (*function)() ) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb( widget, function ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_PRESSING, NULL );
}


inline void _GUI_setValueChangeCallback ( lv_obj_t* widget, void (*function)() ) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb( widget, function ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_VALUE_CHANGED, NULL );
}
inline void _GUI_setValueChangeCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb_with_user_data( widget, function, user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_VALUE_CHANGED, user_data );
}

inline void _GUI_setReadyCallback ( lv_obj_t* widget, void (*function)() ) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb( widget, function ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_READY, NULL );
}

inline void _GUI_setReadyCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb_with_user_data( widget, function, user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_READY, user_data );
}

inline void _GUI_setCancelCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb_with_user_data( widget, function, user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_CANCEL, user_data );
}

inline void _GUI_setDefocusCallbackWithPointer (lv_obj_t* widget, void (*function)(), void* user_data) {
    if ( widget==NULL || !lv_obj_is_valid( widget ) ) return;
    lv_obj_remove_event_cb_with_user_data( widget, function, user_data ); //prevent accumulation of the same function callback
    lv_obj_add_event_cb( widget, (void(*)(lv_event_t*)) function, LV_EVENT_DEFOCUSED, user_data );
}

/*void _GUI_setClickScreenChange ( lv_obj_t* widget, lv_obj_t* screen, void (*init_function)() ) { //using setClickScreenChangeByID instead in GUI_internal.c
    _GUI_setClickCallbackWithValue( widget, _GUI_loadScreenEvent, (uintptr_t) screen );
    if (init_function != NULL) _GUI_setScreenLoadStartCallback( screen, init_function );
}*/
