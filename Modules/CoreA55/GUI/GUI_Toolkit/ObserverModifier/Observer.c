//Observer (cyclic variable display by widget) handling:

#include <string.h>

#include "../GUI_Toolkit.h"
#include "../GUI_Toolkit_internal.h"

#include "ObserverModifier.h"
#include "ObserverModifier_internal.h"



static inline char* _GUI_getFormatString (const char* format, const char* fallback) { return (char*) ( (format!=NULL && format[0]!='\0') ? format : fallback ); }

static inline void _GUI_refreshObserverWidget (_GUI_Observer* observer, _GUI_ValueContainer value) { //(lv_obj_t* widget, _GUI_SubjectVariableTypes type, _GUI_ValueContainer value, _GUI_valueConverterFunction convert, const char* format, _GUI_DisplayedTypes displayed_type) {
    static _GUI_SubjectVariableTypes TypeCategory;
    static lv_obj_t *Widget;
    Widget = *observer->WidgetPointer_pointer;
    TypeCategory = _GUI_getTypeCategory( observer->VariableType );
    if (observer->converterFunction != NULL) value = observer->converterFunction( TypeCategory, value, &TypeCategory );
    //if ( lv_obj_is_valid( widget ) ) {
        if (TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__INT/* || TypeCategory==_GUI_SUBJECT_TYPE_BOOL*/) {
            if (observer->DisplayedType == _GUI_DISPLAYED_TYPE__SHOW_HIDE) _GUI_conditionalShowWidget( Widget, value.Int );
            else if (observer->DisplayedType == _GUI_DISPLAYED_TYPE__DISABLE) _GUI_conditionalEnableWidget( Widget, !value.Int );
            else if ( lv_obj_check_type( Widget, &lv_bar_class ) ) lv_bar_set_value( Widget, value.Int, LV_ANIM_OFF );
            else _GUI_setWidgetFormattedText( Widget, observer->DisplayedType, _GUI_getFormatString( observer->FormatString_pointer,"%d" ), value.Int ); //lv_label_set_text_fmt is not enough
        }
        else if (TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__FLOAT) _GUI_setWidgetFormattedText( Widget, observer->DisplayedType, _GUI_getFormatString( observer->FormatString_pointer, "%f" ), value.Float );
        else if (TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__STRING) {
            if (observer->VariableType == _GUI_SUBJECT_TYPE__ARRAYP || observer->VariableType == _GUI_SUBJECT_TYPE__STRINGARRAYP) {
                value.Pointer = _GUI_convertStringArrayToList( * (char**) observer->VariablePointer, observer->PreviousValue.Int );
                if ( _GUI_widgetIsSelector( Widget ) /*&& observer->VariableType==_GUI_SUBJECT_TYPE__ARRAYP*/ ) { //converting stringlist array to selector options
                    _GUI_createSelectorOptions( Widget, value.Pointer ); //_GUI_createSelectorOptionsFromStringArray( Widget, * (char**) observer->VariablePointer, observer->PreviousValue.Int ); //previous variable holds the total size of the array
                }
                else _GUI_setWidgetText( Widget, value.Pointer );
            }
            else _GUI_setWidgetFormattedText( Widget, observer->DisplayedType, _GUI_getFormatString( observer->FormatString_pointer, "%s" ), value.Pointer );
        }
        //else if (TypeCategory==_GUI_SUBJECT_TYPE_CATEGORY__IGNORE) ; //does nothing
    //}
}

static inline bool _GUI_checkVariableChange (_GUI_SubjectVariableTypes type, const void *const variablepointer, _GUI_ValueContainer* previous_value, bool set) { //check and acquire current value (in previous_value) at the same time
    enum { ARRAYREFRESH_PERIOD = 100 };
    static _GUI_ValueContainer CurrentValue;
    static int ArrayRefreshCounter = 0; //arrays are not changed in every frame if changed, but at certain intervals
    switch (type) {
        case _GUI_SUBJECT_TYPE__UINT8:   if ( (CurrentValue.Int = (Int ) * (uint8_t *const)       variablepointer) != previous_value->Int || set ) { previous_value->Int = CurrentValue.Int; return true; } break;
        case _GUI_SUBJECT_TYPE__UINT8P:  if ( (CurrentValue.Int = (Int) ** (uint8_t *const*const) variablepointer) != previous_value->Int || set ) { previous_value->Int = CurrentValue.Int; return true; } break;
        case _GUI_SUBJECT_TYPE__UINT16:  if ( (CurrentValue.Int = (Int ) * (uint16_t *const)       variablepointer) != previous_value->Int || set ) { previous_value->Int = CurrentValue.Int; return true; } break;
        case _GUI_SUBJECT_TYPE__UINT16P: if ( (CurrentValue.Int = (Int) ** (uint16_t *const*const) variablepointer) != previous_value->Int || set ) { previous_value->Int = CurrentValue.Int; return true; } break;
        case _GUI_SUBJECT_TYPE__UINT32:  if ( (CurrentValue.Int = (Int ) * (uint32_t *const)       variablepointer) != previous_value->Int || set ) { previous_value->Int = CurrentValue.Int; return true; } break;
        case _GUI_SUBJECT_TYPE__UINT32P: if ( (CurrentValue.Int = (Int) ** (uint32_t *const*const) variablepointer) != previous_value->Int || set ) { previous_value->Int = CurrentValue.Int; return true; } break;
        case _GUI_SUBJECT_TYPE__FLOAT:   if ( (CurrentValue.Float = (Float) *  (float *const)       variablepointer) != previous_value->Float || set ) { previous_value->Float = CurrentValue.Float; return true; } break;
        case _GUI_SUBJECT_TYPE__FLOATP:  if ( (CurrentValue.Float = (Float) ** (float *const*const) variablepointer) != previous_value->Float || set ) { previous_value->Float = CurrentValue.Float; return true; } break;
        case _GUI_SUBJECT_TYPE__STRING:  if ( strcmp( (char*) variablepointer, (char*) previous_value->Pointer ) || set ) { strcpy( (char*) previous_value->Pointer, (char*) variablepointer ); return true; } break;
        case _GUI_SUBJECT_TYPE__STRINGP: if ( strcmp( *(char**) variablepointer, (char*) previous_value->Pointer ) || set ) { strcpy( (char*) previous_value->Pointer, *(char**) variablepointer ); return true; } break;
        case _GUI_SUBJECT_TYPE__ARRAY: case _GUI_SUBJECT_TYPE__ARRAYP: case _GUI_SUBJECT_TYPE__STRINGARRAYP: if (++ArrayRefreshCounter >= ARRAYREFRESH_PERIOD) { ArrayRefreshCounter=0; return true; }  break;
        default: break;
    }
    return false;
}

void _GUI_initScreenObservers (_GUI_Observer* observer_array) {
    static _GUI_SubjectVariableTypes VariableType;
    for (int i=0; (VariableType = observer_array[i].VariableType) != _GUI_SUBJECT_TYPE__END; ++i) {
        _GUI_checkVariableChange( VariableType, observer_array[i].VariablePointer, &observer_array[i].PreviousValue, true ); //sets previous values
    }
}

void _GUI_refreshScreenObservers (_GUI_Observer* observer_array, bool force_refresh) { //if a screen opens, it should force the refreshment of all its observers even if no change is indicated (undetected change could occur meanwhile)
    static _GUI_SubjectVariableTypes VariableType;
    for (int i=0; (VariableType = observer_array[i].VariableType) != _GUI_SUBJECT_TYPE__END; ++i) {
        if ( _GUI_checkVariableChange( VariableType, observer_array[i].VariablePointer, &observer_array[i].PreviousValue, force_refresh ) ) { //PreviousValue is now the current value
            _GUI_refreshObserverWidget( &observer_array[i], observer_array[i].PreviousValue ); //.WidgetPointer_pointer, VariableType, observer_array[i].PreviousValue, observer_array[i].converterFunction, observer_array[i].FormatString_pointer, observer_array[i].DisplayedType );
        }
    }
}

