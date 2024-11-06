
#include "GUI_unified.h"
#include "GUI_NonSync_GUItoApp_internal.h"


//bind GUI-input widgets to variables (event-based callback and refresh):
static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getAlarmLifetime ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT/*STRING*/;
    switch (_GUI.Maintenance__PumpPart) {
        case 0: return (_GUI_ValueContainer) {
            ./*Pointer*/Int = /*_GUI_convertIntToText*/( _GUI.SelectedPump__Maintenance==0? *IOp.AlarmLifetime__Pump1_PistonSeal : ( _GUI.SelectedPump__Maintenance==1? *IOp.AlarmLifetime__Pump2_PistonSeal : *IOp.AlarmLifetime__Pump3_PistonSeal ) )
        };
        case 1: return (_GUI_ValueContainer) {
            ./*Pointer*/Int = /*_GUI_convertIntToText*/( _GUI.SelectedPump__Maintenance==0? *IOp.AlarmLifetime__Pump1_CheckValve : ( _GUI.SelectedPump__Maintenance==1? *IOp.AlarmLifetime__Pump2_CheckValve : *IOp.AlarmLifetime__Pump3_CheckValve ) )
        };
    } return input_value; //make smarty compiler happy
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setAlarmLifetime ) {
    Int Value = /*input_value.Int*/ _GUI_convertTextToInt( input_value.Pointer );
    switch (_GUI.Maintenance__PumpPart) {
        case 0: switch (_GUI.SelectedPump__Maintenance)
                { case 0: *IOp.AlarmLifetime__Pump1_PistonSeal = Value; break;  case 1: *IOp.AlarmLifetime__Pump2_PistonSeal = Value; break;  case 2: *IOp.AlarmLifetime__Pump3_PistonSeal = Value; break; }
        break;
        case 1: switch (_GUI.SelectedPump__Maintenance)
                { case 0: *IOp.AlarmLifetime__Pump1_CheckValve = Value; break;  case 1: *IOp.AlarmLifetime__Pump2_CheckValve = Value; break;  case 2: *IOp.AlarmLifetime__Pump3_CheckValve = Value; break; }
        break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}

static _GUI_HEADER_valueConverterFunction( _GUI_refreshMaintenancePumpSelection ) {
    if (input_type == _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL) _GUI_display_PumpSelection__Maintenance();
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL; return input_value;
}



_GUI_Modifier _GUI_Modifiers__Maintenance [] = {
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.AlarmLifetime__Pump1_CheckValve, &ui_Textarea__Maintenance__PumpPart_RuntimeReminder_Period, _GUI_valueConverter_getAlarmLifetime, _GUI_valueConverter_setAlarmLifetime, }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.Washport_AutoStartStop, &ui_Switch__Maintenance__Washport_Auto, NULL, NULL },
 { _GUI_SUBJECT_TYPE__UINT8,  &_GUI.Maintenance__PumpPart, &ui_Roller__Maintenance__PumpPart,      NULL, _GUI_refreshMaintenancePumpSelection },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Maintenance__Pump1 (lv_event_t* event) {
    _GUI.SelectedPump__Maintenance = 0;
    _GUI_display_PumpSelection__Maintenance();
}

void _GUI_clicked__Button__Maintenance__Pump2 (lv_event_t* event) {
    _GUI.SelectedPump__Maintenance = 1;
    _GUI_display_PumpSelection__Maintenance();
}

void _GUI_clicked__Button__Maintenance__Pump3 (lv_event_t* event) {
    _GUI.SelectedPump__Maintenance = 2;
    _GUI_display_PumpSelection__Maintenance();
}



void _GUI_display_PumpSelection__Maintenance () {
    _GUI_setWidgetCheckedState( ui_Button__Maintenance__Pump1, _GUI.SelectedPump__Maintenance == 0 );
    _GUI_setWidgetCheckedState( ui_Button__Maintenance__Pump2, _GUI.SelectedPump__Maintenance == 1 );
    _GUI_setWidgetCheckedState( ui_Button__Maintenance__Pump3, _GUI.SelectedPump__Maintenance == 2 );
    _GUI_refreshScreenObservers( _GUI_Observers__Maintenance, true ); _GUI_refreshScreenModifiers( _GUI_Modifiers__Maintenance );
    _GUI_hideWidget( ui_Keyboard__Maintenance__PumpPart_RuntimeReminderPeriod_Entry );
}



