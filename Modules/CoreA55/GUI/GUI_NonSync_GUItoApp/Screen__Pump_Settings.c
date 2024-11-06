
#include "GUI_unified.h"



enum {
    MODIFIER_INDEX__PUMPSETTING_VALUELIST = 1,

    PUMPSETTING__SYNCHRONIZATION = 0,
    PUMPSETTING__DISPENSE_MODE = 1,
    PUMPSETTING__REFILLOUTPUT_RATIO = 2,
    PUMPSETTING__ERROR_STOP_DELAY = 3,
    PUMPSETTING__VOLTAGE_OUTPUT = 4
};



//bind GUI-input widgets to variables (event-based callback and refresh):
static _GUI_HEADER_valueConverterFunction( _GUI_refreshPumpSettingValueSelector ) {
    if (input_type == _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL) {
        _GUI_createPumpSettingValueList();
        _GUI_refreshModifierWidget( &_GUI_Modifiers__Pump_Settings[ MODIFIER_INDEX__PUMPSETTING_VALUELIST ] ); //_GUI_refreshScreenModifiers( _GUI_Modifiers__Communications ); }
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL; return input_value;
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getPumpSettingValue ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT;
    switch (_GUI.Pump_Settings__SettingID) { //synchronization-setting is probably only needed once as common for all pumps, isn't it?
        case PUMPSETTING__SYNCHRONIZATION: return (_GUI_ValueContainer) { .Int = _GUI.SelectedPump__Pump_Settings==0? IOp.PumpSynchronizationModes->Synchronization_1 : (_GUI.SelectedPump__Pump_Settings==1? IOp.PumpSynchronizationModes->Synchronization_2 : IOp.PumpSynchronizationModes->Synchronization_3) };
        case PUMPSETTING__DISPENSE_MODE: return (_GUI_ValueContainer) { .Int = _GUI_getPumpMode( _GUI.SelectedPump__Pump_Settings ) };
        case PUMPSETTING__REFILLOUTPUT_RATIO: return (_GUI_ValueContainer) { .Int = _GUI.SelectedPump__Pump_Settings==0? IOp.PumpRefillOutputRatios->Output_Ratio_Pump1 : (_GUI.SelectedPump__Pump_Settings==1? IOp.PumpRefillOutputRatios->Output_Ratio_Pump2 : IOp.PumpRefillOutputRatios->Output_Ratio_Pump3) };
        case PUMPSETTING__ERROR_STOP_DELAY: return (_GUI_ValueContainer) { .Int = _GUI.SelectedPump__Pump_Settings==0? IOp.PumpErrorStopDelays->Err_Delay_1 : (_GUI.SelectedPump__Pump_Settings==1? IOp.PumpErrorStopDelays->Err_Delay_2 : IOp.PumpErrorStopDelays->Err_Delay_3) };
        case PUMPSETTING__VOLTAGE_OUTPUT: return (_GUI_ValueContainer) { .Int = _GUI.SelectedPump__Pump_Settings==0? IOp.PumpVoltageOutputTypes->Voltage_Output_1 : (_GUI.SelectedPump__Pump_Settings==1? IOp.PumpVoltageOutputTypes->Voltage_Output_2 : IOp.PumpVoltageOutputTypes->Voltage_Output_3) };
    }
    return input_value;
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setPumpSettingValue ) {
    switch (_GUI.Pump_Settings__SettingID) { //synchronization-setting is probably only needed once as common for all pumps, isn't it?
        case PUMPSETTING__SYNCHRONIZATION: switch (_GUI.SelectedPump__Pump_Settings) { case 0: IOp.PumpSynchronizationModes->Synchronization_1 = input_value.Int; break;  case 1: IOp.PumpSynchronizationModes->Synchronization_2 = input_value.Int; break;  case 2: IOp.PumpSynchronizationModes->Synchronization_3 = input_value.Int; break; }  break;
        case PUMPSETTING__DISPENSE_MODE: switch (_GUI.SelectedPump__Pump_Settings) { case 0: IOp.PumpDispenseModes->Dispense_Mode_Pump1 = input_value.Int; break;  case 1: IOp.PumpDispenseModes->Dispense_Mode_Pump2 = input_value.Int; break;  case 2: IOp.PumpDispenseModes->Dispense_Mode_Pump3 = input_value.Int; break; }  break;
        case PUMPSETTING__REFILLOUTPUT_RATIO: switch (_GUI.SelectedPump__Pump_Settings) { case 0: IOp.PumpRefillOutputRatios->Output_Ratio_Pump1 = input_value.Int; break;  case 1: IOp.PumpRefillOutputRatios->Output_Ratio_Pump2 = input_value.Int; break;  case 2: IOp.PumpRefillOutputRatios->Output_Ratio_Pump3 = input_value.Int; break; }  break;
        case PUMPSETTING__ERROR_STOP_DELAY: switch (_GUI.SelectedPump__Pump_Settings) { case 0: IOp.PumpErrorStopDelays->Err_Delay_1 = input_value.Int; break;  case 1: IOp.PumpErrorStopDelays->Err_Delay_2 = input_value.Int; break;  case 2: IOp.PumpErrorStopDelays->Err_Delay_3 = input_value.Int; break; }  break;
        case PUMPSETTING__VOLTAGE_OUTPUT: switch (_GUI.SelectedPump__Pump_Settings) { case 0: IOp.PumpVoltageOutputTypes->Voltage_Output_1 = input_value.Int; break;  case 1: IOp.PumpVoltageOutputTypes->Voltage_Output_2 = input_value.Int; break;  case 2: IOp.PumpVoltageOutputTypes->Voltage_Output_3 = input_value.Int; break; }  break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getRestartOnPowerup )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.StopRestartConfig->Restart_on_Power_Up }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setRestartOnPowerup )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.StopRestartConfig->Restart_on_Power_Up = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getStopOnStall )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.StopRestartConfig->Stop_on_Stall }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setStopOnStall )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.StopRestartConfig->Stop_on_Stall = input_value.Int; return input_value; }



_GUI_Modifier _GUI_Modifiers__Pump_Settings [] = {
 [0] = { _GUI_SUBJECT_TYPE__UINT8,  &_GUI.Pump_Settings__SettingID, &ui_Dropdown__Pump_Settings__Property,      NULL, _GUI_refreshPumpSettingValueSelector },
 [MODIFIER_INDEX__PUMPSETTING_VALUELIST/*1*/] = { _GUI_SUBJECT_TYPE__UINT8P,  &IOp.PumpSynchronizationModes, &ui_Dropdown__Pump_Settings__Value, _GUI_valueConverter_getPumpSettingValue, _GUI_valueConverter_setPumpSettingValue },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.StopRestartConfig, &ui_Switch__Pump_Settings__RestartOnPowerup, _GUI_valueConverter_getRestartOnPowerup, _GUI_valueConverter_setRestartOnPowerup },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.StopRestartConfig, &ui_Switch__Pump_Settings__StopOnStall, _GUI_valueConverter_getStopOnStall, _GUI_valueConverter_setStopOnStall },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Pump_Settings__Pump1 (lv_event_t* event) {
    _GUI.SelectedPump__Pump_Settings = 0;
    _GUI_display_PumpSelection__Pump_Settings();
}

void _GUI_clicked__Button__Pump_Settings__Pump2 (lv_event_t* event) {
    _GUI.SelectedPump__Pump_Settings = 1;
    _GUI_display_PumpSelection__Pump_Settings();
}

void _GUI_clicked__Button__Pump_Settings__Pump3 (lv_event_t* event) {
    _GUI.SelectedPump__Pump_Settings = 2;
    _GUI_display_PumpSelection__Pump_Settings();
}


void _GUI_changed__Slider__Pump_Settings__CompressibilityCompensation_Value (lv_event_t* event) {
    int Value = _GUI_getSliderValue( ui_Slider__Pump_Settings__CompressibilityCompensation_Value );
    switch (_GUI.SelectedPump__Pump_Settings) {
        case 0: *IOp.FluidCompressibility_Pump1 = Value; break; case 1: *IOp.FluidCompressibility_Pump2 = Value; break; case 2: *IOp.FluidCompressibility_Pump3 = Value; break;
    }
}



void _GUI_display_PumpSelection__Pump_Settings () {
    _GUI_setWidgetCheckedState( ui_Button__Pump_Settings__Pump1, _GUI.SelectedPump__Pump_Settings == 0 );
    _GUI_setWidgetCheckedState( ui_Button__Pump_Settings__Pump2, _GUI.SelectedPump__Pump_Settings == 1 );
    _GUI_setWidgetCheckedState( ui_Button__Pump_Settings__Pump3, _GUI.SelectedPump__Pump_Settings == 2 );
    _GUI_refreshModifierWidget( &_GUI_Modifiers__Pump_Settings[ MODIFIER_INDEX__PUMPSETTING_VALUELIST ] );
    _GUI_setSliderValue( ui_Slider__Pump_Settings__CompressibilityCompensation_Value, (int) _GUI.SelectedPump__Pump_Settings==0? *IOp.FluidCompressibility_Pump1 : (_GUI.SelectedPump__Pump_Settings==1? *IOp.FluidCompressibility_Pump2:*IOp.FluidCompressibility_Pump3) );
    _GUI_refreshScreenObservers( _GUI_Observers__Pump_Settings, true );
}



void _GUI_createPumpSettingValueList () {
    switch (_GUI.Pump_Settings__SettingID) {
        case PUMPSETTING__SYNCHRONIZATION/*0*/: _GUI_createSelectorOptions( ui_Dropdown__Pump_Settings__Value, *IOp.NumberOfPumps==3? "No synchronization\n1 and 2 synchronized\n1 and 3 synchronized\nAll synchronized" : "No synchronization\nsynchronized" ); break; //synchronization
        case PUMPSETTING__DISPENSE_MODE/*1*/: _GUI_createSelectorOptions( ui_Dropdown__Pump_Settings__Value, "Flow\nPressure\nDispense" ); break; //dispense
        case PUMPSETTING__REFILLOUTPUT_RATIO/*2*/: _GUI_createSelectorOptions( ui_Dropdown__Pump_Settings__Value, "Full Out\n15 / 85\n30 / 70\n50 / 50\n70 / 30" ); break; //refill output ratio
        case PUMPSETTING__ERROR_STOP_DELAY/*3*/: _GUI_createSelectorOptions_Integer( ui_Dropdown__Pump_Settings__Value, 0, 4, 1, "" ); break; //Error delay
        case PUMPSETTING__VOLTAGE_OUTPUT/*4*/: _GUI_createSelectorOptions( ui_Dropdown__Pump_Settings__Value, "Flow\nPressure" ); break; //voltage output
    }
}



