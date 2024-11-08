
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GUI_Toolkit.h"
#include "GUI_Toolkit_internal.h"


//Selector: Roller / Dropdown common API

/*static*/ bool _GUI_widgetIsSelector (lv_obj_t* widget) { return lv_obj_check_type( widget, &lv_roller_class ) || lv_obj_check_type( widget, &lv_dropdown_class ); }

uint16_t _GUI_getSelectorIndex (lv_obj_t* selector_widget) {
    if ( lv_obj_check_type( selector_widget, &lv_roller_class ) ) return lv_roller_get_selected( selector_widget );
    else if ( lv_obj_check_type( selector_widget, &lv_dropdown_class ) ) return lv_dropdown_get_selected( selector_widget );
    else return 0;
}

void _GUI_setSelectorIndex (lv_obj_t* selector_widget, uint16_t index) { //based on index, not text
    if ( lv_obj_check_type( selector_widget, &lv_roller_class ) )  lv_roller_set_selected( selector_widget, index, LV_ANIM_OFF );
    else if ( lv_obj_check_type( selector_widget, &lv_dropdown_class ) )  lv_dropdown_set_selected( selector_widget, index );
}

char* _GUI_getSelectorOption (lv_obj_t* selector_widget) {
    enum Config { OPTION_STRING_SIZE_MAX = 32 };
    static char Option [OPTION_STRING_SIZE_MAX];
    if ( lv_obj_check_type( selector_widget, &lv_roller_class ) ) lv_roller_get_selected_str( selector_widget, Option, OPTION_STRING_SIZE_MAX );
    else if ( lv_obj_check_type( selector_widget, &lv_dropdown_class ) ) lv_dropdown_get_selected_str( selector_widget, Option, OPTION_STRING_SIZE_MAX );
    else return NULL;
    return Option;
}


static inline char* _GUI_convertNumberToTextIndent (int number, char* indent) { //indenting with spaces before are design decisions in SLS project
    enum { NUMBERSTRING_SIZE_MAX = 32, INTEGER_VALUE_MAX = 1000000000 };
    static char Text [NUMBERSTRING_SIZE_MAX] = "";
    if ( abs(number) > INTEGER_VALUE_MAX ) { sprintf( Text, "%s>%d", indent, INTEGER_VALUE_MAX ); return Text; }
    sprintf( Text, "%s%d", indent, number );
    return Text;
}

void _GUI_clearSelectorOptions (lv_obj_t* selector_widget, char* options ) {
    if ( lv_obj_check_type( selector_widget, &lv_roller_class ) )  { options[0] = '\0'; lv_roller_set_options( selector_widget, options, LV_ROLLER_MODE_NORMAL ); }
    else if ( lv_obj_check_type( selector_widget, &lv_dropdown_class ) )  lv_dropdown_clear_options( selector_widget ); //seems leaving litter (mem.usage string displayed as options of empty list)
}

void _GUI_addSelectorOption (lv_obj_t* selector_widget, char* option, char* options, char index, char last) {
    if ( lv_obj_check_type( selector_widget, &lv_roller_class ) ) {
        strcat( options, option );
        if (!last) strcat( options,"\n" );
        else lv_roller_set_options( selector_widget, options, LV_ROLLER_MODE_INFINITE );
    }
    else if ( lv_obj_check_type( selector_widget, &lv_dropdown_class ) ) lv_dropdown_add_option( selector_widget, option, index ); //if index is LV_DROPDOWN_POS_LAST, it's the last
}

void _GUI_createSelectorOptions (lv_obj_t* selector_widget, char* options) {
    if ( lv_obj_is_valid( selector_widget ) ) {
        if ( lv_obj_check_type( selector_widget, &lv_roller_class ) )  lv_roller_set_options( selector_widget, options, LV_ROLLER_MODE_NORMAL ); //LV_ROLLER_MODE_INFINITE );
        else if ( lv_obj_check_type( selector_widget, &lv_dropdown_class ) ) lv_dropdown_set_options( selector_widget, options );
    }
}


void _GUI_createSelectorOptionsFromStringArray (lv_obj_t* selector_widget, char* source_strings, int sourcearray_size) { //converting stringlist array to selector options //size is the total size of array in bytes
    _GUI_createSelectorOptions( selector_widget,  _GUI_convertStringArrayToList ( source_strings, sourcearray_size ) );
}


void _GUI_createSelectorOptions_Integer (lv_obj_t* selector_widget, short min, short max, short step, char* indent) {
    short i;
    //if ( *selector_widget==NULL || !lv_obj_is_valid(*selector_widget) ) return;
    _GUI_clearSelectorOptions( selector_widget, _GUI_Toolkit_TempString );
    for (i=min; i<=max; i+=step) _GUI_addSelectorOption( selector_widget, _GUI_convertNumberToTextIndent( i,indent ), _GUI_Toolkit_TempString, i, i+step > max );
}
