//public header

#include "GUI_Toolkit/GUI_Toolkit.h"



enum {
    _GUI_TEMP_STRING_SIZE_MAX = 20000, _GUI_DATETIME_STRING_SIZE_MAX = 32,
    _GUI_FOOTERTEXT_STRING_SIZE_MAX = 128, //according to backend-API

    _GUI_PASSWORD_SCREEN_MODE__CHANGE_REMOTE = 0,
    _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY = 1,
    _GUI_PASSWORD_SCREEN_MODE__ENTER_USER = 2,

    _GUI_PUMPSETTING__DISPENSE_MODE__FLOW = 0,
    _GUI_PUMPSETTING__DISPENSE_MODE__PRESSURE = 1,
    _GUI_PUMPSETTING__DISPENSE_MODE__DISPENSE = 2,

    _GUI_PRESSURE_TARGET_VALUE_MAX = 7500 //psi
};



struct GUIprivateVariables { //initialized in GUI_Internal.c
    char TempString [_GUI_TEMP_STRING_SIZE_MAX];
    int CurrentScreenID;
    int PreviousScreenID;
    const _GUI_ScreenDescriptor ScreenDescriptors [GUI_SCREEN_AMOUNT];
    float GUI_Version_Float;
    float Firmware_Version_Float;
    char DateTimeString [_GUI_DATETIME_STRING_SIZE_MAX]; char DateTimeString_previous [_GUI_DATETIME_STRING_SIZE_MAX];
    char FooterText_previous [_GUI_FOOTERTEXT_STRING_SIZE_MAX];
    int PasswordScreen_Mode; int PasswordScreen_TargetScreenID; lv_obj_t* PasswordScreen_TargetWidget; int PasswordScreen_RememberedPasswordType;
    int SelectedPump__Initial_Setup; int SelectedPump__Home; int SelectedPump__Pump_Settings; int SelectedPump__Maintenance; int SelectedPump__Communication_Serial;
    int Pump_Settings__SettingID;
    int Maintenance__PumpPart;
    bool WiFi_HiddenNetwork;
};



//GUI_Internal.c own functions:
void _GUI_init_Main (int intput_id, int framebuffer_id);
void _GUI_refresh_Main ();

//void _GUI_updateScreenIDs (GUI_ScreenIDs screen_id);
void _GUI_loadScreenByID (GUI_ScreenIDs screen_id);
void _GUI_loadScreenByIDwithFade (GUI_ScreenIDs screen_id, int fade_duration);
void _GUI_setClickScreenChangeByID (lv_obj_t* widget, GUI_ScreenIDs screen_id);


int _GUI_getPumpMode (int selected_pump);
float _GUI_getFlowRate (int selected_pump);
