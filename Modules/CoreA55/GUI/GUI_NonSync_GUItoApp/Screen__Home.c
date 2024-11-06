
#include "GUI_unified.h"
#include "GUI_NonSync_GUItoApp_internal.h"


#define _GUI_PRESSURE_TARGET_STEPSIZE 1
#define _GUI_FLOWRATE_STEPSIZE 0.001 //0.1 //0.01 //0.001 //0.1  //0.001 is required  //1.0 for 1st testing
#define _GUI_FLOWRATE_VALUE_MIN 0.002 //ml/min
#define _GUI_FLOWRATE_VALUE_MAX 100.0 //ml/min



//bind GUI-input widgets to variables (event-based callback and refresh):
static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getDispenseAmount ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__FLOAT/*STRING*/; return (_GUI_ValueContainer) {
        ./*Pointer*/Float = /*_GUI_convertFloatToText*/( _GUI.SelectedPump__Home==0? *IOp.DispenseAmount_Pump1 : ( _GUI.SelectedPump__Home==1? *IOp.DispenseAmount_Pump2 : *IOp.DispenseAmount_Pump3 ) )
    };
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setDispenseAmount ) {
    Float Value = /*input_value.Float*/ _GUI_convertTextToFloat( input_value.Pointer );
    switch (_GUI.SelectedPump__Home) {
        case 0: *IOp.DispenseAmount_Pump1 = Value; break;  case 1: *IOp.DispenseAmount_Pump2 = Value; break;  case 2: *IOp.DispenseAmount_Pump3 = Value; break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getDispenseDuration ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT/*STRING*/; return (_GUI_ValueContainer) {
        ./*Pointer*/Int = /*_GUI_convertIntToText*/( _GUI.SelectedPump__Home==0? *IOp.DispenseDuration_Pump1 : ( _GUI.SelectedPump__Home==1? *IOp.DispenseDuration_Pump2 : *IOp.DispenseDuration_Pump3 ) )
    };
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setDispenseDuration ) {
    Int Value = /*input_value.Int*/ _GUI_convertTextToInt( input_value.Pointer );
    switch (_GUI.SelectedPump__Home) {
        case 0: *IOp.DispenseDuration_Pump1 = Value; break;  case 1: *IOp.DispenseDuration_Pump2 = Value; break;  case 2: *IOp.DispenseDuration_Pump3 = Value; break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getDispenseRepeatDelay ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT/*STRING*/; return (_GUI_ValueContainer) {
        ./*Pointer*/Int = /*_GUI_convertIntToText*/( _GUI.SelectedPump__Home==0? *IOp.RepeatDelay_Pump1 : ( _GUI.SelectedPump__Home==1? *IOp.RepeatDelay_Pump2 : *IOp.RepeatDelay_Pump3 ) )
    };
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setDispenseRepeatDelay ) {
    Int Value = /*input_value.Int*/ _GUI_convertTextToInt( input_value.Pointer );
    switch (_GUI.SelectedPump__Home) {
        case 0: *IOp.RepeatDelay_Pump1 = Value; break;  case 1: *IOp.RepeatDelay_Pump2 = Value; break;  case 2: *IOp.RepeatDelay_Pump3 = Value; break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getDispenseRepeatAmount ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT/*STRING*/; return (_GUI_ValueContainer) {
        ./*Pointer*/Int = /*_GUI_convertIntToText*/( _GUI.SelectedPump__Home==0? *IOp.RepeatAmount_Pump1 : ( _GUI.SelectedPump__Home==1? *IOp.RepeatAmount_Pump2 : *IOp.RepeatAmount_Pump3 ) )
    };
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setDispenseRepeatAmount ) {
    Int Value = /*input_value.Int*/ _GUI_convertTextToInt( input_value.Pointer );
    switch (_GUI.SelectedPump__Home) {
        case 0: *IOp.RepeatAmount_Pump1 = Value; break;  case 1: *IOp.RepeatAmount_Pump2 = Value; break;  case 2: *IOp.RepeatAmount_Pump3 = Value; break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}



_GUI_Modifier _GUI_Modifiers__Home [] = {
 { _GUI_SUBJECT_TYPE__FLOATP,  &IOp.DispenseAmount_Pump1,   &ui_Textarea__Home__Dispense_FluidAmount, _GUI_valueConverter_getDispenseAmount, _GUI_valueConverter_setDispenseAmount }, //_GUI_valueConverter_FloatToText, _GUI_valueConverter_TextToFloat },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.DispenseDuration_Pump1, &ui_Textarea__Home__Dispense_PumpRunDuration, _GUI_valueConverter_getDispenseDuration, _GUI_valueConverter_setDispenseDuration }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.RepeatDelay_Pump1,      &ui_Textarea__Home__Dispense_RepeatDelay,     _GUI_valueConverter_getDispenseRepeatDelay, _GUI_valueConverter_setDispenseRepeatDelay }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.RepeatAmount_Pump1,     &ui_Textarea__Home__Dispense_RepeatAmount,    _GUI_valueConverter_getDispenseRepeatAmount, _GUI_valueConverter_setDispenseRepeatAmount }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Home__Pump1 (lv_event_t* event) {
    _GUI.SelectedPump__Home = 0;
    _GUI_display_PumpSelection__Home();
}

void _GUI_clicked__Button__Home__Pump2 (lv_event_t* event) {
    _GUI.SelectedPump__Home = 1;
    _GUI_display_PumpSelection__Home();
}

void _GUI_clicked__Button__Home__Pump3 (lv_event_t* event) {
    _GUI.SelectedPump__Home = 2;
    _GUI_display_PumpSelection__Home();
}

void _GUI_clicked__Button__Home__StartStop (lv_event_t* event) {
    *IOp.RunTime_Pump1 = *IOp.RunTime_Pump2 = *IOp.RunTime_Pump3 = 0;
    *IOp.FlowAmount_Pump1 = *IOp.FlowAmount_Pump2 = *IOp.FlowAmount_Pump3 = 0;
}


void _GUI_pressing__Button__Home__FlowOrPressure_Up (lv_event_t* event) {
    enum { KEYREPEAT_ACCELERATION_PRESCALE = 20 };
    static int Acceleration = 0, AccelerationPrescaleCounter = 0;
    int RepeatSpeed = _GUI_handleKeyRepeat( _GUI_InputDevice, true, GUI_KEYREPEAT_DELAY, GUI_KEYREPEAT_RATE, GUI_KEYREPEAT_RATE_MIN );
    if ( !RepeatSpeed ) return;
    else if (RepeatSpeed > GUI_KEYREPEAT_RATE_MIN) { Acceleration = 1; AccelerationPrescaleCounter = 0; }
    else { if (++AccelerationPrescaleCounter >= KEYREPEAT_ACCELERATION_PRESCALE) { AccelerationPrescaleCounter = 0; ++Acceleration; } }
    switch ( _GUI_getPumpMode( _GUI.SelectedPump__Home ) ) {
        case _GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE:
            if (*IOp.Pressure_Target < _GUI_PRESSURE_TARGET_VALUE_MAX) *IOp.Pressure_Target += _GUI_PRESSURE_TARGET_STEPSIZE * Acceleration;
            if (*IOp.Pressure_Target > _GUI_PRESSURE_TARGET_VALUE_MAX) *IOp.Pressure_Target = _GUI_PRESSURE_TARGET_VALUE_MAX;
        break;
        case _GUI_PUMPSETTING__DISPENSE_MODE__FLOW:
            switch (_GUI.SelectedPump__Home) {
                case 0: if (*IOp.FlowRate_Pump1 < _GUI_FLOWRATE_VALUE_MAX) *IOp.FlowRate_Pump1 += _GUI_FLOWRATE_STEPSIZE * Acceleration; if (*IOp.FlowRate_Pump1 >= _GUI_FLOWRATE_VALUE_MAX) *IOp.FlowRate_Pump1 = _GUI_FLOWRATE_VALUE_MAX; break;
                case 1: if (*IOp.FlowRate_Pump2 < _GUI_FLOWRATE_VALUE_MAX) *IOp.FlowRate_Pump2 += _GUI_FLOWRATE_STEPSIZE * Acceleration; if (*IOp.FlowRate_Pump2 >= _GUI_FLOWRATE_VALUE_MAX) *IOp.FlowRate_Pump2 = _GUI_FLOWRATE_VALUE_MAX; break;
                case 2: if (*IOp.FlowRate_Pump3 < _GUI_FLOWRATE_VALUE_MAX) *IOp.FlowRate_Pump3 += _GUI_FLOWRATE_STEPSIZE * Acceleration; if (*IOp.FlowRate_Pump3 >= _GUI_FLOWRATE_VALUE_MAX) *IOp.FlowRate_Pump3 = _GUI_FLOWRATE_VALUE_MAX; break;
            }
        break;
    }
}

void _GUI_pressing__Button__Home__FlowOrPressure_Down (lv_event_t* event) {
    enum { KEYREPEAT_ACCELERATION_PRESCALE = 20 };
    static int Acceleration = 0, AccelerationPrescaleCounter = 0, Result;
    int RepeatSpeed = _GUI_handleKeyRepeat( _GUI_InputDevice, true, GUI_KEYREPEAT_DELAY, GUI_KEYREPEAT_RATE, GUI_KEYREPEAT_RATE_MIN );
    if ( !RepeatSpeed ) return;
    else if (RepeatSpeed > GUI_KEYREPEAT_RATE_MIN) { Acceleration = 1; AccelerationPrescaleCounter = 0; }
    else { if (++AccelerationPrescaleCounter >= KEYREPEAT_ACCELERATION_PRESCALE) { AccelerationPrescaleCounter = 0; ++Acceleration; } }
    switch ( _GUI_getPumpMode( _GUI.SelectedPump__Home ) ) {
        case _GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE:
            if (*IOp.Pressure_Target > 0) {
                Result = *IOp.Pressure_Target - _GUI_PRESSURE_TARGET_STEPSIZE * Acceleration;
                *IOp.Pressure_Target = (Result >= 0) ? Result : 0;
            }
        break;
        case _GUI_PUMPSETTING__DISPENSE_MODE__FLOW:
            switch (_GUI.SelectedPump__Home) {
                case 0: if (*IOp.FlowRate_Pump1 > _GUI_FLOWRATE_VALUE_MIN) *IOp.FlowRate_Pump1 -= _GUI_FLOWRATE_STEPSIZE * Acceleration; if (*IOp.FlowRate_Pump1 <= _GUI_FLOWRATE_VALUE_MIN) *IOp.FlowRate_Pump1 = _GUI_FLOWRATE_VALUE_MIN; break;
                case 1: if (*IOp.FlowRate_Pump2 > _GUI_FLOWRATE_VALUE_MIN) *IOp.FlowRate_Pump2 -= _GUI_FLOWRATE_STEPSIZE * Acceleration; if (*IOp.FlowRate_Pump2 <= _GUI_FLOWRATE_VALUE_MIN) *IOp.FlowRate_Pump2 = _GUI_FLOWRATE_VALUE_MIN; break;
                case 2: if (*IOp.FlowRate_Pump3 > _GUI_FLOWRATE_VALUE_MIN) *IOp.FlowRate_Pump3 -= _GUI_FLOWRATE_STEPSIZE * Acceleration; if (*IOp.FlowRate_Pump3 <= _GUI_FLOWRATE_VALUE_MIN) *IOp.FlowRate_Pump3 = _GUI_FLOWRATE_VALUE_MIN; break;
            }
        break;
    }
}



void _GUI_display_PumpSelection__Home () {
    _GUI_setWidgetCheckedState( ui_Button__Home__Pump1, _GUI.SelectedPump__Home == 0 );
    _GUI_setWidgetCheckedState( ui_Button__Home__Pump2, _GUI.SelectedPump__Home == 1 );
    _GUI_setWidgetCheckedState( ui_Button__Home__Pump3, _GUI.SelectedPump__Home == 2 );
    int DispenseMode = _GUI_getPumpMode( _GUI.SelectedPump__Home ); //_GUI.SelectedPump__Home==0 ? IOp.PumpDispenseModes->Dispense_Mode_Pump1 : (_GUI.SelectedPump__Home==1? IOp.PumpDispenseModes->Dispense_Mode_Pump2:IOp.PumpDispenseModes->Dispense_Mode_Pump3);
    _GUI_conditionalShowWidget( ui_Container__Home__DispenseGroup, DispenseMode==_GUI_PUMPSETTING__DISPENSE_MODE__DISPENSE );
    _GUI_conditionalShowWidget( ui_Container__Home__ButtonGroup, DispenseMode==_GUI_PUMPSETTING__DISPENSE_MODE__FLOW || DispenseMode==_GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE );
    _GUI_setWidgetText( ui_Label__Home__MainValue_Title, DispenseMode==_GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE? "Pressure Target":"Flow Rate" );
    _GUI_setWidgetText( ui_Label__Home__MainValue_Unit, DispenseMode==_GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE? "psi":"mL/min" );
    _GUI_setWidgetText( ui_Label__Home__ScreenTitle, DispenseMode==_GUI_PUMPSETTING__DISPENSE_MODE__DISPENSE? "Dispense":"Pump Control" );
    _GUI_refreshScreenObservers( _GUI_Observers__Home, true ); _GUI_refreshScreenModifiers( _GUI_Modifiers__Home );
    _GUI_hideWidget( ui_Keyboard__Home__DispenseDataEntry );
}



