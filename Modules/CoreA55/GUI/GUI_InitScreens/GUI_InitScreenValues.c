//Set at every screen-call:

#include "GUI_unified.h"



void _GUI_initScreenValues__StartupSplash (lv_event_t* event) {
}


void _GUI_initScreenValues__Initial_Setup (lv_event_t* event) {
    if (_GUI.PreviousScreenID==GUI_SCREEN_ID__StartupSplash && Factory_Initialization_Done) { _GUI_loadScreenByID( GUI_SCREEN_ID__Home ); return; }

    _GUI_display_PumpSelection__Initial_Setup();

    //_GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Home;
    if (_GUI.PasswordScreen_TargetWidget == ui_Textarea__Initial_Setup__Serial_Number) { _GUI_editSerialNumber(); lv_obj_add_state(ui_Textarea__Initial_Setup__Serial_Number, LV_STATE_EDITED /*LV_STATE_PRESSED*/); } //lv_obj_send_event( ui_Textarea__Initial_Setup__Serial_Number, LV_EVENT_CLICKED, NULL ); }
    else if (_GUI.PasswordScreen_TargetWidget == ui_Textarea__Initial_Setup__Model_Number) { _GUI_editModelNumber(); lv_obj_add_state(ui_Textarea__Initial_Setup__Model_Number, LV_STATE_EDITED /*LV_STATE_PRESSED*/); } // lv_obj_send_event( ui_Textarea__Initial_Setup__Model_Number, LV_EVENT_CLICKED, NULL ); }
    else _GUI_hideWidget( ui_Keyboard__Initial_Setup__NumberEntry );
    _GUI.PasswordScreen_TargetWidget = NULL;
}


void _GUI_initScreenValues__Select_Option (lv_event_t* event) {
    _GUI_display_OptionSelections__Select_Option();
}


void _GUI_initScreenValues__Generic_Password (lv_event_t* event) {
    if (_GUI.PasswordScreen_Mode == _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY) {
        _GUI_setWidgetText( ui_Label__Generic_Password__ScreenTitle, "Factory password required" );
        _GUI_setWidgetText( ui_Label__Generic_Password__PasswordField_Title, "Enter Factory password" );
    }
    else if (_GUI.PasswordScreen_Mode == _GUI_PASSWORD_SCREEN_MODE__ENTER_USER) {
        _GUI_setWidgetText( ui_Label__Generic_Password__ScreenTitle, "Please enter User Password" );
        _GUI_setWidgetText( ui_Label__Generic_Password__PasswordField_Title, "Enter User password" );
    }
    else if (_GUI.PasswordScreen_Mode == _GUI_PASSWORD_SCREEN_MODE__CHANGE_REMOTE) {
        _GUI_setWidgetText( ui_Label__Generic_Password__ScreenTitle, "Change Remote password" );
        _GUI_setWidgetText( ui_Label__Generic_Password__PasswordField_Title, "Enter new Remote password" );
    }

    _GUI_setWidgetText( ui_Textarea__Generic_Password__PasswordField, "" ); //lv_textarea_set_text( ui_Textarea__Generic_Password__PasswordField, "" );
}


void _GUI_initScreenValues__Home (lv_event_t* event) {
    _GUI_display_PumpSelection__Home();
}


void _GUI_initScreenValues__Pump_Settings (lv_event_t* event) {
    _GUI_display_PumpSelection__Pump_Settings();
}


void _GUI_initScreenValues__Advanced_Settings (lv_event_t* event) {
    _GUI_hideWidget( ui_Keyboard__Advanced_Settings__PressureAlarmInterval_Entry );
}


void _GUI_initScreenValues__Maintenance (lv_event_t* event) {
    _GUI_display_PumpSelection__Maintenance();

    _GUI_removeAllObjectEvents( ui_Textarea__Maintenance__SerialNumber ); _GUI_disableWidget( ui_Textarea__Maintenance__SerialNumber );
    _GUI_removeAllObjectEvents( ui_Textarea__Maintenance__ModelNumber ); _GUI_disableWidget( ui_Textarea__Maintenance__ModelNumber );
    _GUI_removeAllObjectEvents( ui_Textarea__Maintenance__FirmwareVersion ); _GUI_disableWidget( ui_Textarea__Maintenance__FirmwareVersion );
    _GUI_removeAllObjectEvents( ui_Textarea__Maintenance__GUIversion ); _GUI_disableWidget( ui_Textarea__Maintenance__GUIversion );
    _GUI_removeAllObjectEvents( ui_Textarea__Maintenance__Pump1_TotalRun ); _GUI_disableWidget( ui_Textarea__Maintenance__Pump1_TotalRun );
}


void _GUI_initScreenValues__Self_Test (lv_event_t* event) {
}


void _GUI_initScreenValues__Communications (lv_event_t* event) {
    _GUI_hideWidget( ui_Keyboard__Communications__WiFi_AuthenticationDataEntry );
    lv_keyboard_set_textarea( ui_Keyboard__Communications__Ethernet_IPAddressEntry, NULL );
}


void _GUI_initScreenValues__Firmware_Update (lv_event_t* event) {
}


void _GUI_initScreenValues__Popup_Modal (lv_event_t* event) {
}

