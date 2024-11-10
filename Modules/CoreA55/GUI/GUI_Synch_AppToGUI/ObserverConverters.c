
#include "GUI_unified.h"



//Converter functions usable in the observer-arrays

_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_Negate ) { //bool
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = input_value.Int? 0:1 /* ^ 1 */ };
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_VersionNumbers ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__FLOAT; return (_GUI_ValueContainer) { .Float = (float)input_value.Int / 100.0 };
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getHomeMainValue ) {
    static _GUI_ValueContainer Value;
    switch ( _GUI_getPumpMode( *IOp/*_GUI*/.SelectedPump__Home ) ) {
        case _GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE: *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; Value.Int = *IOp.Pressure_Target; break;
        case _GUI_PUMPSETTING__DISPENSE_MODE__FLOW: case _GUI_PUMPSETTING__DISPENSE_MODE__DISPENSE: *output_type = _GUI_SUBJECT_TYPE_CATEGORY__FLOAT; Value.Float = _GUI_getFlowRate( *IOp/*_GUI*/.SelectedPump__Home ); break;
    }
    if (_GUI_getTypeCategory( input_type ) != *output_type) *output_type = _GUI_SUBJECT_TYPE_CATEGORY__IGNORE;  //could filter to selected pump match too, but it works
    return Value;
}

_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getHomePumpFlowAmount ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__FLOAT;
    return (_GUI_ValueContainer) { .Float = *IOp/*_GUI*/.SelectedPump__Home==0? *IOp.FlowAmount_Pump1 : (*IOp/*_GUI*/.SelectedPump__Home==1? *IOp.FlowAmount_Pump2 : *IOp.FlowAmount_Pump3) };
}

_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getHomePumpRuntime ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT;
    return (_GUI_ValueContainer) { .Int = *IOp/*_GUI*/.SelectedPump__Home==0? *IOp.RunTime_Pump1 : (*IOp/*_GUI*/.SelectedPump__Home==1? *IOp.RunTime_Pump2 : *IOp.RunTime_Pump3) };
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getCompressibilityValue ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT;
    return (_GUI_ValueContainer) { .Int = *IOp/*_GUI*/.SelectedPump__Pump_Settings==0? *IOp.FluidCompressibility_Pump1 : (*IOp/*_GUI*/.SelectedPump__Pump_Settings==1? *IOp.FluidCompressibility_Pump2:*IOp.FluidCompressibility_Pump3) };
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getPumpPartRuntime ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT;
    switch (_GUI.Maintenance__PumpPart) {
        case 0: return (_GUI_ValueContainer) { .Int = *IOp/*_GUI*/.SelectedPump__Maintenance==0? *IOp.TotalRunHours__Pump1_PistonSeal : (*IOp/*_GUI*/.SelectedPump__Maintenance==1? *IOp.TotalRunHours__Pump2_PistonSeal : *IOp.TotalRunHours__Pump3_PistonSeal) };
        case 1: return (_GUI_ValueContainer) { .Int = *IOp/*_GUI*/.SelectedPump__Maintenance==0? *IOp.TotalRunHours__Pump1_CheckValve : (*IOp/*_GUI*/.SelectedPump__Maintenance==1? *IOp.TotalRunHours__Pump2_CheckValve : *IOp.TotalRunHours__Pump3_CheckValve) };
    } return input_value; //make GCC happy
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getUSBsatusBit ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT /*_GUI_SUBJECT_TYPE_BOOL*/; return (_GUI_ValueContainer) { .Int = IOp.ConnectionStates->USB_Inserted }; //better solution to handle bit-fields as pointers?
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getEthernetStatusBit ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT /*_GUI_SUBJECT_TYPE_BOOL*/; return (_GUI_ValueContainer) { .Int = IOp.ConnectionStates->Ethernet_Active };
}


_GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getWiFiStatusBit ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT /*_GUI_SUBJECT_TYPE_BOOL*/; return (_GUI_ValueContainer) { .Int = IOp.ConnectionStates->Wifi_On };
}


