
#include "GUI_unified.h"
#include "GUI_NonSync_GUItoApp_internal.h"



//bind GUI-input widgets to variables (event-based callback and refresh):

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getPressureLimitEnable )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.AdvancedSetup_bits->Pressure_limit_enabled }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setPressureLimitEnable )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.AdvancedSetup_bits->Pressure_limit_enabled = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getPressureMeasureUnit )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.AdvancedSetup_bits->Pressure_unit_of_measure }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setPressureMeasureUnit )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.AdvancedSetup_bits->Pressure_unit_of_measure = input_value.Int; return input_value; }



_GUI_Modifier _GUI_Modifiers__Advanced_Settings [] = {
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.PressureAlarm_UpperThreshold,  &ui_Textarea__Advanced_Settings__PressureAlarm_Max, _GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.PressureAlarm_LowerThreshold,  &ui_Textarea__Advanced_Settings__PressureAlarm_Min, _GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.AdvancedSetup_bits, &ui_Switch__Advanced_Settings__PressureLimit_Enable, _GUI_valueConverter_getPressureLimitEnable, _GUI_valueConverter_setPressureLimitEnable },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.AdvancedSetup_bits, &ui_Roller__Advanced_Settings__PressureUnit, _GUI_valueConverter_getPressureMeasureUnit, _GUI_valueConverter_setPressureMeasureUnit },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Advanced_Settings__FactoryMenu (lv_event_t* event) {
    _GUI.PasswordScreen_Mode = _GUI_PASSWORD_SCREEN_MODE__ENTER_USER;
    _GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Initial_Setup;
    _GUI.PasswordScreen_TargetWidget = NULL;
    _GUI_loadScreenByID( GUI_SCREEN_ID__Generic_Password );
}



