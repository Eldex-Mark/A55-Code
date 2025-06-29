
#include "GUI_unified.h"
#include "GUI_NonSync_GUItoApp_internal.h"


//bind GUI-input widgets to variables (event-based callback and refresh):
static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getAlarmLifetime ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT/*STRING*/;
    switch (_GUI.Maintenance__PumpPart) {
        case 0: return (_GUI_ValueContainer) {
            ./*Pointer*/Int = /*_GUI_convertIntToText*/( *IOp/*_GUI*/.SelectedPump__Maintenance==0? *IOp.AlarmLifetime__Pump1_PistonSeal : ( *IOp/*_GUI*/.SelectedPump__Maintenance==1? *IOp.AlarmLifetime__Pump2_PistonSeal : *IOp.AlarmLifetime__Pump3_PistonSeal ) )
        };
        case 1: return (_GUI_ValueContainer) {
            ./*Pointer*/Int = /*_GUI_convertIntToText*/( *IOp/*_GUI*/.SelectedPump__Maintenance==0? *IOp.AlarmLifetime__Pump1_CheckValve : ( *IOp/*_GUI*/.SelectedPump__Maintenance==1? *IOp.AlarmLifetime__Pump2_CheckValve : *IOp.AlarmLifetime__Pump3_CheckValve ) )
        };
    } return input_value; //make smarty compiler happy
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setAlarmLifetime ) {
    Int Value = /*input_value.Int*/ _GUI_convertTextToInt( input_value.Pointer );
    switch (_GUI.Maintenance__PumpPart) {
        case 0: switch (*IOp/*_GUI*/.SelectedPump__Maintenance)
                { case 0: *IOp.AlarmLifetime__Pump1_PistonSeal = Value; break;  case 1: *IOp.AlarmLifetime__Pump2_PistonSeal = Value; break;  case 2: *IOp.AlarmLifetime__Pump3_PistonSeal = Value; break; }
        break;
        case 1: switch (*IOp/*_GUI*/.SelectedPump__Maintenance)
                { case 0: *IOp.AlarmLifetime__Pump1_CheckValve = Value; break;  case 1: *IOp.AlarmLifetime__Pump2_CheckValve = Value; break;  case 2: *IOp.AlarmLifetime__Pump3_CheckValve = Value; break; }
        break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}

static _GUI_HEADER_valueConverterFunction( _GUI_refreshMaintenancePumpSelection ) {
    if (input_type == _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL) _GUI_display_PumpSelection__Maintenance();
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL; return input_value;
}



_GUI_Modifier _GUI_Modifiers__Maintenance [] = { //Reminders: Alarms will show in the message center blinking on all screens. Main Alarm Reminder label: constant text: „Alarm Reminder” (checking/textmodding handled by frontend or backend?}
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.AlarmLifetime__Pump1_CheckValve, &ui_Textarea__Maintenance__PumpPart_RuntimeReminder_Period, _GUI_valueConverter_getAlarmLifetime, _GUI_valueConverter_setAlarmLifetime, }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.Washport_AutoStartStop, &ui_Switch__Maintenance__Washport_Auto, NULL, NULL },
 { _GUI_SUBJECT_TYPE__UINT8,  &_GUI.Maintenance__PumpPart, &ui_Roller__Maintenance__PumpPart,      NULL, _GUI_refreshMaintenancePumpSelection },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Maintenance__Pump1 (lv_event_t* event) {
    *IOp/*_GUI*/.SelectedPump__Maintenance = 0;
    _GUI_display_PumpSelection__Maintenance();
}

void _GUI_clicked__Button__Maintenance__Pump2 (lv_event_t* event) {
    *IOp/*_GUI*/.SelectedPump__Maintenance = 1;
    _GUI_display_PumpSelection__Maintenance();
}

void _GUI_clicked__Button__Maintenance__Pump3 (lv_event_t* event) {
    *IOp/*_GUI*/.SelectedPump__Maintenance = 2;
    _GUI_display_PumpSelection__Maintenance();
}

void _GUI_clicked__Button__Maintenance__Washport_Rinse (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Maintenance__Washport_Rinse );
}

void _GUI_clicked__Button__Maintenance__Reset_PumpPart_Runtime (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Maintenance__Reset_PumpPart_Runtime );
}

void _GUI_clicked__Button__Maintenance__ZeroPressure_Transducer (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Maintenance__ZeroPressure_Transducer );
}

void _GUI_clicked__Button__Maintenance__Sensor_MoveMotorsHome (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Maintenance__Sensor_MoveMotorsHome );
    _GUI_displayPopupScreen( 1? "Success" : "Failed", "",  "", -1,  "OK", GUI_SCREEN_ID__Maintenance, -1 ); //GUI_SCREEN_ID__BACK
}



void _GUI_display_PumpSelection__Maintenance () {
    _GUI_setWidgetCheckedState( ui_Button__Maintenance__Pump1, *IOp/*_GUI*/.SelectedPump__Maintenance == 0 );
    _GUI_setWidgetCheckedState( ui_Button__Maintenance__Pump2, *IOp/*_GUI*/.SelectedPump__Maintenance == 1 ); _GUI_conditionalShowWidget( ui_Button__Maintenance__Pump2, *IOp.NumberOfPumps >= 2 );
    _GUI_setWidgetCheckedState( ui_Button__Maintenance__Pump3, *IOp/*_GUI*/.SelectedPump__Maintenance == 2 ); _GUI_conditionalShowWidget( ui_Button__Maintenance__Pump3, *IOp.NumberOfPumps >= 3 );
    _GUI_refreshScreenObservers( _GUI_Observers__Maintenance, true ); _GUI_refreshScreenModifiers( _GUI_Modifiers__Maintenance );
    _GUI_hideWidget( ui_Keyboard__Maintenance__PumpPart_RuntimeReminderPeriod_Entry );
}



