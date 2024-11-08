//Modifier (event-based variable read/update by widget) handling:

#include <string.h>

#include "../GUI_Toolkit.h"
#include "../GUI_Toolkit_internal.h"

#include "ObserverModifier.h"
#include "ObserverModifier_internal.h"



static bool _GUI_getValueFromModifierWidget (_GUI_Modifier* modifier, _GUI_SubjectVariableTypes* type_category, _GUI_ValueContainer* value, lv_obj_t* trigger_widget) {
    static lv_obj_t* Widget; Widget = *modifier->WidgetPointer_pointer;
    if ( _GUI_widgetIsSelector( Widget ) ) {
        /*if (TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__INT)*/ value->Int = _GUI_getSelectorIndex( Widget );
    }
    else if ( lv_obj_check_type( Widget, &lv_switch_class ) || lv_obj_check_type( Widget, &lv_checkbox_class ) ) {
        /*if (TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__INT)*/ value->Int = _GUI_getWidgetCheckedState( Widget );
    }
    else if ( lv_obj_check_type( Widget, &lv_textarea_class ) ) {
        lv_obj_t* Keyboard = trigger_widget; //_GUI_getTextareaKeyboard( Widget );
        if (Keyboard==NULL || lv_keyboard_get_textarea( Keyboard ) != Widget) return false;
        if (modifier->outputConverter == NULL && *type_category != _GUI_SUBJECT_TYPE_CATEGORY__STRING) { //implicit built-in textarea conversion
            switch (*type_category) {
                case _GUI_SUBJECT_TYPE_CATEGORY__INT: value->Int = _GUI_convertTextToInt( (char*) lv_textarea_get_text( Widget ) ); break;
                case _GUI_SUBJECT_TYPE_CATEGORY__FLOAT: value->Float = _GUI_convertTextToFloat( (char*) lv_textarea_get_text( Widget ) ); break;
                default: break;
            }
        }
        else value->Pointer = (void*) lv_textarea_get_text( Widget );
        _GUI_setWidgetFocusedState( Widget, false );
    }
    if (modifier->outputConverter != NULL) *value = modifier->outputConverter( *type_category, *value, type_category );
    return true;
}

void _GUI_closeKeyboard (lv_obj_t* widget, _GUI_SubjectVariableTypes type) {
    lv_keyboard_set_textarea( widget, NULL );
    if (type != _GUI_SUBJECT_TYPE__ARRAY_NOHIDE) _GUI_hideWidget( widget );
}

void _GUI_modifierEvent (_GUI_Modifier *Modifier, lv_obj_t* trigger_widget) {
    static _GUI_ValueContainer Value;
    static _GUI_SubjectVariableTypes TypeCategory;

    TypeCategory = _GUI_getTypeCategory( Modifier->VariableType );
    if ( !_GUI_getValueFromModifierWidget( Modifier, &TypeCategory, &Value, trigger_widget ) ) return;
    if (TypeCategory != _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE) { //written already? (e.g. struct bitfields)
        switch (Modifier->VariableType) {
            case _GUI_SUBJECT_TYPE__UINT8:    * (uint8_t *const)        Modifier->VariablePointer = Value.Int; break;
            case _GUI_SUBJECT_TYPE__UINT8P:  ** (uint8_t *const*const)  Modifier->VariablePointer = Value.Int; break;
            case _GUI_SUBJECT_TYPE__UINT16:   * (uint16_t *const)       Modifier->VariablePointer = Value.Int; break;
            case _GUI_SUBJECT_TYPE__UINT16P: ** (uint16_t *const*const) Modifier->VariablePointer = Value.Int; break;
            case _GUI_SUBJECT_TYPE__UINT32:   * (uint32_t *const)       Modifier->VariablePointer = Value.Int; break;
            case _GUI_SUBJECT_TYPE__UINT32P: ** (uint32_t *const*const) Modifier->VariablePointer = Value.Int; break;
            case _GUI_SUBJECT_TYPE__FLOAT:    * (float *const)          Modifier->VariablePointer = Value.Float; break;
            case _GUI_SUBJECT_TYPE__FLOATP:  ** (float *const*const)    Modifier->VariablePointer = Value.Float; break;
            case _GUI_SUBJECT_TYPE__STRING:  strcpy( (char *const) Modifier->VariablePointer, Value.Pointer ); break;
            case _GUI_SUBJECT_TYPE__STRINGP: case _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD: strcpy( * (char *const*const) Modifier->VariablePointer, Value.Pointer ); break;
            default: break;
        }
    }
    if (TypeCategory == _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL) Modifier->outputConverter( TypeCategory, Value, &TypeCategory );
    if ( lv_obj_check_type( *Modifier->WidgetPointer_pointer, &lv_textarea_class ) ) {
        _GUI_refreshModifierWidget( Modifier ); //see if it could be processed fine
        _GUI_closeKeyboard( trigger_widget, Modifier->VariableType );
    }
}

void _GUI_modifierEventCallback (lv_event_t* event) { //common value-change callback internally used for modifiers
    _GUI_modifierEvent( (_GUI_Modifier*) lv_event_get_user_data( event ), (lv_obj_t*) lv_event_get_target( event ) );
}

void _GUI_modifierClickCallback (lv_event_t* event) {
    lv_obj_t* Widget = lv_event_get_target( event );
    if ( lv_obj_check_type( Widget, &lv_textarea_class ) ) {
        lv_obj_t* Keyboard = (lv_obj_t*) lv_event_get_user_data( event );
        _GUI_setWidgetFocusedState( Widget, true ); _GUI_showWidget( Keyboard ); lv_keyboard_set_textarea( Keyboard, Widget );
    }
}

void _GUI_modifierEnterCallback (lv_event_t* event) { //make it possible to close onscreen-keyboard by Enter too, not just OK
    enum { KEYINDEX_ENTER = 22 };
    _GUI_Modifier *Modifier = (_GUI_Modifier*) lv_event_get_user_data( event );
    lv_obj_t* Keyboard = (lv_obj_t*) lv_event_get_target( event );
    uint16_t ButtonID = lv_keyboard_get_selected_btn( lv_event_get_target(event) );
    if (ButtonID == KEYINDEX_ENTER) {
        _GUI_modifierEvent( Modifier, Keyboard );
        if ( lv_obj_check_type( Keyboard, &lv_keyboard_class ) ) _GUI_closeKeyboard( Keyboard, Modifier->VariableType );
    }
}


void _GUI_modifierCancelCallback (lv_event_t* event) {
    _GUI_Modifier *Modifier = (_GUI_Modifier*) lv_event_get_user_data( event );
    lv_obj_t *Keyboard = lv_event_get_target( event );
    _GUI_setWidgetFocusedState( *Modifier->WidgetPointer_pointer, false ); _GUI_refreshModifierWidget( Modifier );
    if ( lv_obj_check_type( Keyboard, &lv_keyboard_class ) ) _GUI_closeKeyboard( Keyboard, Modifier->VariableType );
}

void _GUI_modifierDefocusCallback (lv_event_t* event) {
    lv_obj_t *Widget = lv_event_get_target( event );
    lv_obj_t *Keyboard = lv_event_get_user_data( event );
    _GUI_setWidgetFocusedState( Widget, false );
    lv_keyboard_set_textarea( Keyboard, NULL );
}



static void _GUI_setModifierWidget (_GUI_Modifier* modifier, _GUI_ValueContainer value) {
    static lv_obj_t* Widget;
    static _GUI_SubjectVariableTypes TypeCategory;
    Widget = *modifier->WidgetPointer_pointer;
    TypeCategory = _GUI_getTypeCategory( modifier->VariableType );
    if (modifier->inputConverter != NULL && modifier->VariableType != _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD) value = modifier->inputConverter( TypeCategory, value, &TypeCategory );
    if ( _GUI_widgetIsSelector( Widget ) ) {
        _GUI_setSelectorIndex( Widget, /*(TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__INT)?*/ value.Int );
    }
    else if ( lv_obj_check_type( Widget, &lv_switch_class ) || lv_obj_check_type( Widget, &lv_checkbox_class ) ) {
        _GUI_setWidgetCheckedState( Widget, /*(TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__INT)?*/ value.Int );
    }
    else if ( lv_obj_check_type( Widget, &lv_textarea_class ) ) {
        if (/*modifier->inputConverter == NULL &&*/ TypeCategory != _GUI_SUBJECT_TYPE_CATEGORY__STRING) { //implicit built-in textarea conversion
            switch (TypeCategory) {
                case _GUI_SUBJECT_TYPE_CATEGORY__INT: _GUI_setWidgetText( Widget, _GUI_convertIntToText(value.Int) ); break;
                case _GUI_SUBJECT_TYPE_CATEGORY__FLOAT: _GUI_setWidgetText( Widget, _GUI_convertFloatToText(value.Float) ); break;
                default: break;
            }
        }
        else _GUI_setWidgetText( Widget, (char*) value.Pointer );
        lv_obj_scroll_to_x( Widget, 0, LV_ANIM_OFF ); //lv_textarea_set_cursor_pos( Widget, 0 );
    }
}

void _GUI_refreshModifierWidget (_GUI_Modifier* modifier) {
    static _GUI_ValueContainer Value;
    switch (modifier->VariableType) {
        case _GUI_SUBJECT_TYPE__UINT8:   Value.Int =  * (uint8_t *const)        modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__UINT8P:  Value.Int = ** (uint8_t *const*const)  modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__UINT16:  Value.Int =  * (uint16_t *const)       modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__UINT16P: Value.Int = ** (uint16_t *const*const) modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__UINT32:  Value.Int =  * (uint32_t *const)       modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__UINT32P: Value.Int = ** (uint32_t *const*const) modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__FLOAT:   Value.Float =  * (float *const)        modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__FLOATP:  Value.Float = ** (float *const*const)  modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__STRING:  Value.Pointer =    (char *const)       modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__STRINGP: case _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD: Value.Pointer =  * (char *const*const) modifier->VariablePointer; break;
        case _GUI_SUBJECT_TYPE__POINTER: case _GUI_SUBJECT_TYPE__ARRAY: case _GUI_SUBJECT_TYPE__ARRAY_NOHIDE: Value.Pointer = (void *const) modifier->VariablePointer; break;
        default: break;
    }
    _GUI_setModifierWidget( modifier, Value );
}


void _GUI_initModifierWidget (_GUI_Modifier* modifier) {
    static lv_obj_t *Widget, *Keyboard;
    Widget = *modifier->WidgetPointer_pointer;
    if ( lv_obj_check_type( Widget, &lv_textarea_class ) ) { //for textareas it's better (?) not to use their value-callback but assigned keyboards 'ready': keyboard found on the screen is assigned automatically (works well if there's only 1 keyboard on the screen)
        if (modifier->VariableType != _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD) Keyboard = _GUI_getTextareaKeyboard( Widget );
        else Keyboard = * (lv_obj_t**) modifier->inputConverter; //a workaround to have other keyboard than the first found on the screen
        _GUI_setClickCallbackWithPointer( Widget, _GUI_modifierClickCallback, Keyboard );
        _GUI_setReadyCallbackWithPointer( Keyboard , _GUI_modifierEventCallback, modifier );
        _GUI_setClickCallbackWithPointer( Keyboard , _GUI_modifierEnterCallback, modifier );
        _GUI_setCancelCallbackWithPointer( Keyboard, _GUI_modifierCancelCallback, modifier );
        _GUI_setDefocusCallbackWithPointer( Widget, _GUI_modifierCancelCallback, modifier );
        _GUI_setDefocusCallbackWithPointer( Widget, _GUI_modifierDefocusCallback, Keyboard ); //'defocus' event doesn't seem to happen when switching manually from model-number field to serial-number field after giving factory-password
    }
    else _GUI_setValueChangeCallbackWithPointer( Widget, _GUI_modifierEventCallback, modifier );
}
void _GUI_initScreenModifiers (_GUI_Modifier* modifier_array) {
    static _GUI_SubjectVariableTypes VariableType;
    for (int i=0; (VariableType = modifier_array[i].VariableType) != _GUI_SUBJECT_TYPE__END; ++i) {
        _GUI_initModifierWidget( &modifier_array[i] );
    }
}

void _GUI_refreshScreenModifiers (_GUI_Modifier* modifier_array) {
    static _GUI_SubjectVariableTypes VariableType;
    for (int i=0; (VariableType = modifier_array[i].VariableType) != _GUI_SUBJECT_TYPE__END; ++i) {
        _GUI_refreshModifierWidget( &modifier_array[i] );
    }
}
