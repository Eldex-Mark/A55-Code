
#include "GUI_unified.h"
#include "GUI_NonSync_GUItoApp_internal.h"



enum {
    MODIFIER_INDEX__INITIAL_SETUP__SERIAL_NUMBER = 0, MODIFIER_INDEX__INITIAL_SETUP__MODEL_NUMBER = 1
};



//bind GUI-input widgets to variables (event-based callback and refresh):
_GUI_Modifier _GUI_Modifiers__Initial_Setup [] = {
 [MODIFIER_INDEX__INITIAL_SETUP__SERIAL_NUMBER/*0*/] = { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Serial_Number, &ui_Textarea__Initial_Setup__Serial_Number, NULL, NULL }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt }, //{ _GUI_SUBJECT_TYPE__UINT16P, &IOp.Serial_Number, &ui_Keyboard__Initial_Setup__NumberEntry, _GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt },
 [MODIFIER_INDEX__INITIAL_SETUP__MODEL_NUMBER/*1*/] = { _GUI_SUBJECT_TYPE__UINT8P,  &IOp.Model_Number,  &ui_Textarea__Initial_Setup__Model_Number,  NULL, NULL }, //_GUI_valueConverter_IntToText, _GUI_valueConverter_TextToInt }, //keyboard found on the screen is assigned automatically (works well if there's only 1 keyboard on the screen)
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Initial_Setup__Pump1 (lv_event_t* event) {
    _GUI.SelectedPump__Initial_Setup = 0;
    _GUI_display_PumpSelection__Initial_Setup();
}

void _GUI_clicked__Button__Initial_Setup__Pump2 (lv_event_t* event) {
    _GUI.SelectedPump__Initial_Setup = 1;
    _GUI_display_PumpSelection__Initial_Setup();
}

void _GUI_clicked__Button__Initial_Setup__Pump3 (lv_event_t* event) {
    _GUI.SelectedPump__Initial_Setup = 2;
    _GUI_display_PumpSelection__Initial_Setup();
}

void _GUI_clicked__Button__Initial_Setup__Next (lv_event_t* event) {
    *IOp.Factory_Initialization_Done = true; //should send an 'event' to the backend according to API  (setting should be saved in backend permanently)
    _GUI_loadScreenByID( GUI_SCREEN_ID__Home );
    _GUI.PasswordScreen_RememberedPasswordType = -1; //this ensures forgetting factory password when leaving the initial setup screen
}


void _GUI_clicked__Textarea__Initial_Setup__Serial_Number (lv_event_t* event) {
    if (!*IOp.Factory_Initialization_Done || _GUI.PasswordScreen_RememberedPasswordType == _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY) { _GUI_editSerialNumber(); return; } //once remembered for initial setup screen, it doesn't request it again
    _GUI.PasswordScreen_Mode = _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY;
    _GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Initial_Setup;
    _GUI.PasswordScreen_TargetWidget = lv_event_get_target( event );
    _GUI_loadScreenByID( GUI_SCREEN_ID__Generic_Password );
}

void _GUI_clicked__Textarea__Initial_Setup__Model_Number (lv_event_t* event) {
    if (!*IOp.Factory_Initialization_Done || _GUI.PasswordScreen_RememberedPasswordType == _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY) { _GUI_editModelNumber(); return; } //once remembered for initial setup screen, it doesn't request it again
    _GUI.PasswordScreen_Mode = _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY;
    _GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Initial_Setup;
    _GUI.PasswordScreen_TargetWidget = lv_event_get_target( event );
    _GUI_loadScreenByID( GUI_SCREEN_ID__Generic_Password );
}

void _GUI_clicked__Button__Initial_Setup__ChangeRemotePassword (lv_event_t* event) {
    _GUI.PasswordScreen_Mode = _GUI_PASSWORD_SCREEN_MODE__CHANGE_REMOTE;
    _GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Initial_Setup;
    _GUI.PasswordScreen_TargetWidget = NULL;
    _GUI_loadScreenByID( GUI_SCREEN_ID__Generic_Password );
}

void _GUI_clicked__Button__Initial_Setup__SelectOptions (lv_event_t* event) {
    if (!*IOp.Factory_Initialization_Done || _GUI.PasswordScreen_RememberedPasswordType == _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY) { _GUI_loadScreenByID( GUI_SCREEN_ID__Select_Option ); return; }
    _GUI.PasswordScreen_Mode = _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY;
    _GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Select_Option;
    _GUI.PasswordScreen_TargetWidget = NULL;
    _GUI_loadScreenByID( GUI_SCREEN_ID__Generic_Password );
}



void _GUI_changed__Roller__Initial_Setup__PistonSize (lv_event_t* event) {
    int PistonSizeIndex = _GUI_getSelectorIndex( ui_Roller__Initial_Setup__PistonSize );
    switch (_GUI.SelectedPump__Initial_Setup) {
        case 0: IOp.PumpPistonSizes->PistonSize_Pump1 = PistonSizeIndex; return;
        case 1: IOp.PumpPistonSizes->PistonSize_Pump2 = PistonSizeIndex; return;
        case 2: IOp.PumpPistonSizes->PistonSize_Pump3 = PistonSizeIndex; return;
    }
}

void  _GUI_changed__Roller__Initial_Setup__StrokeLength (lv_event_t* event) {
    int StrokeLengthIndex = _GUI_getSelectorIndex( ui_Roller__Initial_Setup__StrokeLength );
    switch (_GUI.SelectedPump__Initial_Setup) {
        case 0: IOp.PumpStrokeLengths->StrokeLength_Pump1 = StrokeLengthIndex; return;
        case 1: IOp.PumpStrokeLengths->StrokeLength_Pump2 = StrokeLengthIndex; return;
        case 2: IOp.PumpStrokeLengths->StrokeLength_Pump3 = StrokeLengthIndex; return;
    }
}

void _GUI_changed__Roller__Initial_Setup__WettedParts (lv_event_t* event) {
    int WettedPartIndex = _GUI_getSelectorIndex( ui_Roller__Initial_Setup__WettedParts );
    switch (_GUI.SelectedPump__Initial_Setup) {
        case 0: IOp.PumpWettedParts->WettedPart_Pump1 = WettedPartIndex; return;
        case 1: IOp.PumpWettedParts->WettedPart_Pump2 = WettedPartIndex; return;
        case 2: IOp.PumpWettedParts->WettedPart_Pump3 = WettedPartIndex; return;
    }
}



void _GUI_editSerialNumber () {
    _GUI_showWidget( ui_Keyboard__Initial_Setup__NumberEntry );
    lv_keyboard_set_textarea( ui_Keyboard__Initial_Setup__NumberEntry, ui_Textarea__Initial_Setup__Serial_Number );  //lv_obj_send_event( ui_Textarea__Initial_Setup__Serial_Number, LV_EVENT_CLICKED, NULL );
    _GUI_setWidgetFocusedState( ui_Textarea__Initial_Setup__Model_Number, false ); _GUI_refreshModifierWidget( &_GUI_Modifiers__Initial_Setup[ MODIFIER_INDEX__INITIAL_SETUP__MODEL_NUMBER ] ); //workaround for an LVGL programmatic focus-problem
    _GUI_setWidgetFocusedState( ui_Textarea__Initial_Setup__Serial_Number, true ); //lv_group_focus_obj( ui_Textarea__Initial_Setup__Serial_Number );
}

void _GUI_editModelNumber () {
    _GUI_showWidget( ui_Keyboard__Initial_Setup__NumberEntry );
    lv_keyboard_set_textarea( ui_Keyboard__Initial_Setup__NumberEntry, ui_Textarea__Initial_Setup__Model_Number );
    _GUI_setWidgetFocusedState( ui_Textarea__Initial_Setup__Serial_Number, false ); _GUI_refreshModifierWidget( &_GUI_Modifiers__Initial_Setup[ MODIFIER_INDEX__INITIAL_SETUP__SERIAL_NUMBER ] ); //workaround for an LVGL programmatic focus-problem
    _GUI_setWidgetFocusedState( ui_Textarea__Initial_Setup__Model_Number, true ); lv_group_focus_obj( ui_Textarea__Initial_Setup__Model_Number );
}



void _GUI_display_PumpSelection__Initial_Setup () {
    _GUI_setWidgetCheckedState( ui_Button__Initial_Setup__Pump1, _GUI.SelectedPump__Initial_Setup == 0 );
    _GUI_setWidgetCheckedState( ui_Button__Initial_Setup__Pump2, _GUI.SelectedPump__Initial_Setup == 1 );
    _GUI_setWidgetCheckedState( ui_Button__Initial_Setup__Pump3, _GUI.SelectedPump__Initial_Setup == 2 );
    _GUI_setSelectorIndex( ui_Roller__Initial_Setup__PistonSize, _GUI.SelectedPump__Initial_Setup==0? IOp.PumpPistonSizes->PistonSize_Pump1 : _GUI.SelectedPump__Initial_Setup==1? IOp.PumpPistonSizes->PistonSize_Pump2 : IOp.PumpPistonSizes->PistonSize_Pump3 );
    _GUI_setSelectorIndex( ui_Roller__Initial_Setup__StrokeLength, _GUI.SelectedPump__Initial_Setup==0? IOp.PumpStrokeLengths->StrokeLength_Pump1 : _GUI.SelectedPump__Initial_Setup==1? IOp.PumpStrokeLengths->StrokeLength_Pump2 : IOp.PumpStrokeLengths->StrokeLength_Pump3 );
    _GUI_setSelectorIndex( ui_Roller__Initial_Setup__WettedParts, _GUI.SelectedPump__Initial_Setup==0? IOp.PumpWettedParts->WettedPart_Pump1 : _GUI.SelectedPump__Initial_Setup==1? IOp.PumpWettedParts->WettedPart_Pump2 : IOp.PumpWettedParts->WettedPart_Pump3 );
}


