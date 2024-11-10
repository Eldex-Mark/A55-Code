//Convenience functions to use SquareLine Studio UI easier and more efficiently

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GUI_Toolkit.h"

#include "GUI_Toolkit_internal.h"



char _GUI_Toolkit_TempString [_GUI_TOOLKIT_TEMP_STRING_SIZE_MAX];



void _GUI_debug (const char* format, ...) {
    #if (defined(SQUARELINE_DEBUG) && SQUARELINE_DEBUG)  //printf( "GUI: %s\n", message );
        printf("GUI: ");
        if ( strchr( format, '%' ) == NULL ) { printf( "%s\n", format ); return; }
        va_list args; va_start( args, format ); vprintf( format, args ); va_end( args ); printf( "\n" );
    #else
     (void) format; //avoid possible 'unused variable' warnings
    #endif
}


inline char* _GUI_convertIntToText (int number) { sprintf( _GUI_Toolkit_TempString, "%d", number ); return _GUI_Toolkit_TempString; }

inline char* _GUI_convertFloatToText (float number) { sprintf( _GUI_Toolkit_TempString, "%.2f", number ); return _GUI_Toolkit_TempString; }

inline int _GUI_convertTextToInt (char* text) { int Number; sscanf( text, "%d", &Number ); return Number; }

inline float _GUI_convertTextToFloat (char* text) { float Number; sscanf( text, "%f", &Number ); return Number; }

char* _GUI_convertIPaddressToText (uint8_t* address) {
    sprintf( _GUI_Toolkit_TempString, "%d.%d.%d.%d", address[0], address[1], address[2], address[3] );
    return _GUI_Toolkit_TempString;
}

void _GUI_convertTextToIPaddress (char* text, uint8_t* address) {
    static int Part1, Part2, Part3, Part4;
    sscanf( text, "%d.%d.%d.%d", &Part1, &Part2, &Part3, &Part4 );
    address[0] = Part1; address[1] = Part2; address[2] = Part3; address[3] = Part4;
}

char* _GUI_convertStringArrayToList (char* source_strings, int sourcearray_size) { //converting stringlist array to newline-selected //size is the total size of array in bytes
    static int i, SourceIndex, LastNewlineIndex;
    for (i = SourceIndex = LastNewlineIndex = 0; i < sourcearray_size && SourceIndex < sourcearray_size; ++i) { //previous variable holds the total size of the array (only reached )
        if (source_strings[ SourceIndex ] != '\0') _GUI_Toolkit_TempString[ i ] = source_strings[ SourceIndex++ ];
        else { _GUI_Toolkit_TempString[ i ] = '\n'; LastNewlineIndex=i; while ( source_strings[ ++SourceIndex ] == '\0' && SourceIndex < sourcearray_size ); }
    }
    _GUI_Toolkit_TempString[ LastNewlineIndex ] = '\0'; //ensure string-termination right after last character that was not a terminating '\0'
    return _GUI_Toolkit_TempString;
}



int _GUI_handleKeyRepeat (lv_indev_t* input, bool pressed, int repeat_delay, int repeat_rate, int repeat_rate_min) {
    enum { KEYREPEAT_ACCELERATION_PRESCALE = 10 };

    static int KeyRepeatCounter = 1;
    static int AccelerationCounter = 0, AccelerationPrescaleCounter = 0;

    if ( !pressed ) { //check if still pressed, if not, reset the counter to first delay value
        if ( lv_indev_get_state( input /*lv_indev_active()*/ ) == LV_INDEV_STATE_RELEASED ) { KeyRepeatCounter = repeat_delay; AccelerationCounter = AccelerationPrescaleCounter = 0; }
    }
    else {
        if ( KeyRepeatCounter == repeat_delay ) { --KeyRepeatCounter; return repeat_delay; } //true; }
        else if (KeyRepeatCounter == 0) {
            KeyRepeatCounter = repeat_rate - AccelerationCounter;
            if ( AccelerationPrescaleCounter < KEYREPEAT_ACCELERATION_PRESCALE ) ++AccelerationPrescaleCounter;
            else {
                AccelerationPrescaleCounter = 0;
                if (repeat_rate - AccelerationCounter > repeat_rate_min) {++AccelerationCounter;}
            }
            return repeat_rate - AccelerationCounter; //true;
        }
        --KeyRepeatCounter;
    }
    return false;
}


inline void _GUI_loadScreen (lv_obj_t* screen) { lv_scr_load( screen ); }
inline void _GUI_loadScreenWithFade (lv_obj_t* *screen, int duration) { lv_scr_load_anim( *screen, LV_SCR_LOAD_ANIM_FADE_ON, duration, 0, false ); }; //_ui_screen_change( screen, LV_SCR_LOAD_ANIM_FADE_ON /*LV_SCR_LOAD_ANIM_NONE*/, duration/*100*/ /*0*/, 0, NULL ); }

inline lv_obj_t* _GUI_getCurrentScreen () { return lv_screen_active(); }



static inline void _GUI_setWidgetState (lv_obj_t* widget, lv_state_t state_type, bool state) {
    if ( lv_obj_is_valid(widget) ) {
        if (state) lv_obj_add_state( widget, state_type ); else lv_obj_remove_state( widget, state_type );
    }
}

void _GUI_setWidgetCheckedState (lv_obj_t* widget, bool value) { _GUI_setWidgetState( widget, LV_STATE_CHECKED, value ); }
bool _GUI_getWidgetCheckedState (lv_obj_t* widget) { return lv_obj_has_state(widget, LV_STATE_CHECKED); }

void _GUI_setWidgetFocusedState (lv_obj_t* widget, bool value) { _GUI_setWidgetState( widget, LV_STATE_FOCUSED/* | LV_STATE_EDITED*/, value ); }
bool _GUI_getWidgetFocusedState (lv_obj_t* widget) { return lv_obj_has_state(widget, LV_STATE_FOCUSED); }

void _GUI_showWidget (lv_obj_t* widget) { if ( lv_obj_is_valid(widget) ) lv_obj_remove_flag( widget, LV_OBJ_FLAG_HIDDEN ); }
void _GUI_hideWidget (lv_obj_t* widget) { if ( lv_obj_is_valid(widget) ) lv_obj_add_flag( widget, LV_OBJ_FLAG_HIDDEN ); }
void _GUI_enableWidget (lv_obj_t* widget) { if ( lv_obj_is_valid(widget) ) { lv_obj_remove_state( widget, LV_STATE_DISABLED ); lv_obj_add_flag( widget, LV_OBJ_FLAG_CLICKABLE ); } }
void _GUI_disableWidget (lv_obj_t* widget) { if ( lv_obj_is_valid(widget) ) { lv_obj_add_state( widget, LV_STATE_DISABLED ); lv_obj_remove_flag( widget, LV_OBJ_FLAG_CLICKABLE ); } }

void _GUI_conditionalShowWidget (lv_obj_t* widget, bool condition) { if (condition) _GUI_showWidget( widget ); else _GUI_hideWidget( widget ); }
void _GUI_conditionalEnableWidget (lv_obj_t* widget, bool condition) { if (condition) _GUI_enableWidget( widget ); else _GUI_disableWidget( widget ); }


inline void _GUI_setWidgetText (lv_obj_t* widget, char* text) {
    if ( lv_obj_is_valid( widget ) ) {
        if ( lv_obj_check_type( widget, &lv_label_class ) ) lv_label_set_text( widget, text );
        else if ( lv_obj_check_type( widget, &lv_textarea_class) ) lv_textarea_set_text( widget, text ); //lv_label_set_text( lv_textarea_get_label( widget ), text );
    }
}

inline void _GUI_setWidgetPlaceholderText (lv_obj_t* widget, char* text) {
    if ( lv_obj_is_valid( widget ) ) {
        if ( lv_obj_check_type( widget, &lv_textarea_class) ) lv_textarea_set_placeholder_text( widget, text );
    }
}


inline int _GUI_getSliderValue (lv_obj_t* slider) { return lv_slider_get_value( slider ); }
inline void _GUI_setSliderValue (lv_obj_t* slider, int value) { if ( lv_obj_is_valid( slider ) ) lv_slider_set_value( slider, value, LV_ANIM_OFF ); }


static lv_obj_t* _GUI_searchTextareaKeyboard (lv_obj_t* object, lv_obj_t* textarea) {
    int ChildAmount = lv_obj_get_child_count( object );
    lv_obj_t *Child;
    for (int i=0; i < ChildAmount; ++i) {
        Child = lv_obj_get_child( object, i );
        if ( lv_obj_check_type( Child, &lv_keyboard_class ) /*&& lv_keyboard_get_textarea( Child ) == textarea*/ ) return Child; //not connecting with textarea if the keyboard is probably assigned to other textarea too
        else if ( (Child = _GUI_searchTextareaKeyboard( Child, textarea ) ) ) return Child;
    }
    return NULL; //keyboard not found
}

lv_obj_t* _GUI_getTextareaKeyboard (lv_obj_t* textarea) {
    static lv_obj_t *Screen;
    Screen = lv_obj_get_screen( textarea );
    return _GUI_searchTextareaKeyboard( Screen, textarea );
}



