//Define and perform synchronous (cyclic) input happenings, like displaying continuously changing values periodically (from Application to GUI)

#include "GUI_unified.h"



static void _GUI_preProcessValues () { //better being done in the converter callback-functions, but sometimes it might be better to have these converted values remain statically
    //_GUI.GUI_Version_Float = *IOp.GUI_Version / 100.0;
    _GUI.Firmware_Version_Float = *IOp.Firmware_Version / 100.0;
    sprintf( _GUI.DateTimeString, "%2.2d/%2.2d/%2.2d %2.2d:%2.2d", *IOp.DateAndTime.Month, *IOp.DateAndTime.Day, *IOp.DateAndTime.Year % 100, *IOp.DateAndTime.Hour, *IOp.DateAndTime.Minute ); //_GUI_debug("%s",_GUI.DateTimeString);
}


static void _GUI_init_Observers () {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) {
        _GUI_initScreenObservers( _GUI.ScreenDescriptors[ i ].Observers );
    }
}

static void _GUI_refresh_Observers (bool force_refresh) {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) { //speed-optimization: only run those observers that are seen on an active screen
        if ( _GUI_getCurrentScreen() == *_GUI.ScreenDescriptors[ i ].Screen ) _GUI_refreshScreenObservers( _GUI.ScreenDescriptors[ i ].Observers, force_refresh );
    }
}


void _GUI_init_SynchOutputs () {
    _GUI_init_Observers();
    _GUI_preProcessValues();
    _GUI_refresh_Observers( true ); //one call is needed for the default startup screen as it's loaded implicitly
}


void _GUI_refresh_SynchOutputs () { //Application-value/state/pointer-following observers/etc. can be put here
    _GUI_preProcessValues();
    _GUI_refresh_Observers( false );
    _GUI_handleKeyRepeat( _GUI_InputDevice, false, GUI_KEYREPEAT_DELAY, GUI_KEYREPEAT_RATE, GUI_KEYREPEAT_RATE_MIN );

    //other manually handled cyclic object checks & changes can be put here too:

    static int SelfTest_Progress_Percentage_previous = -1;
    if (*IOp.SelfTest_Progress_Percentage == 0 && SelfTest_Progress_Percentage_previous > 90) _GUI_displayPopupScreen( "The test has ended", "",  "", -1,  "OK", GUI_SCREEN_ID__Self_Test, -1 ); //GUI_SCREEN_ID__BACK ); //_GUI_loadScreenByID( GUI_SCREEN_ID__Popup_Modal );
    SelfTest_Progress_Percentage_previous = *IOp.SelfTest_Progress_Percentage;

    static int FirmwareUpdate_ProgressPercentage_previous = -1;
    if (*IOp.FirmwareUpdate_ProgressPercentage == 0 && FirmwareUpdate_ProgressPercentage_previous > 90) {
        _GUI_displayPopupScreen( "", 1? "The firmware has been successfully updated": 1? "No internet connection" : "Error: ERROR_MESSAGE",  "", -1,  "OK", GUI_SCREEN_ID__Firmware_Update, -1 ); //GUI_SCREEN_ID__BACK );
        //_GUI_displayPopupScreen( "", 1? "The firmware has been successfully updated": 1? "The installer file \"optos_firmware_installer\" could not be found in the root of the flash drive" : 1? "No Flash drive found" : "Error: ERROR_MESSAGE",  "", -1,  "OK", GUI_SCREEN_ID__Firmware_Update ); //GUI_SCREEN_ID__BACK );
    }
    FirmwareUpdate_ProgressPercentage_previous = *IOp.FirmwareUpdate_ProgressPercentage;

    static int TotalRunHours__Pump1_PistonSeal_oneshot = 0;
    if (*IOp.TotalRunHours__Pump1_PistonSeal >= *IOp.AlarmLifetime__Pump1_PistonSeal && !TotalRunHours__Pump1_PistonSeal_oneshot) {
        TotalRunHours__Pump1_PistonSeal_oneshot=1; _GUI_displayStatusMessage( "Piston Seal of Pump 1 requires maintenance" );
    }
    static int TotalRunHours__Pump2_PistonSeal_oneshot = 0;
    if (*IOp.TotalRunHours__Pump2_PistonSeal >= *IOp.AlarmLifetime__Pump2_PistonSeal && !TotalRunHours__Pump2_PistonSeal_oneshot) {
        TotalRunHours__Pump2_PistonSeal_oneshot=1; _GUI_displayStatusMessage( "Piston Seal of Pump 2 requires maintenance" );
    }
    static int TotalRunHours__Pump3_PistonSeal_oneshot = 0;
    if (*IOp.TotalRunHours__Pump3_PistonSeal >= *IOp.AlarmLifetime__Pump3_PistonSeal && !TotalRunHours__Pump3_PistonSeal_oneshot) {
        TotalRunHours__Pump3_PistonSeal_oneshot=1; _GUI_displayStatusMessage( "Piston Seal of Pump 3 requires maintenance" );
    }

    static int TotalRunHours__Pump1_CheckValve_oneshot = 0;
    if (*IOp.TotalRunHours__Pump1_CheckValve >= *IOp.AlarmLifetime__Pump1_CheckValve && !TotalRunHours__Pump1_CheckValve_oneshot) {
        TotalRunHours__Pump1_CheckValve_oneshot=1; _GUI_displayStatusMessage( "Valve of Pump 1 requires maintenance" );
    }
    static int TotalRunHours__Pump2_CheckValve_oneshot = 0;
    if (*IOp.TotalRunHours__Pump2_CheckValve >= *IOp.AlarmLifetime__Pump2_CheckValve && !TotalRunHours__Pump2_CheckValve_oneshot) {
        TotalRunHours__Pump2_CheckValve_oneshot=1; _GUI_displayStatusMessage( "Valve of Pump 2 requires maintenance" );
    }
    static int TotalRunHours__Pump3_CheckValve_oneshot = 0;
    if (*IOp.TotalRunHours__Pump3_CheckValve >= *IOp.AlarmLifetime__Pump3_CheckValve && !TotalRunHours__Pump3_CheckValve_oneshot) {
        TotalRunHours__Pump3_CheckValve_oneshot=1; _GUI_displayStatusMessage( "Valve of Pump 3 requires maintenance" );
    }

    _GUI.RemoteControl_Active = IOp.RemoteControlRights->Serial_RemoteControl || IOp.RemoteControlRights->Ethernet_RemoteControl || IOp.RemoteControlRights->Wifi_RemoteControl; //|| Ethernet_RemoteConnection; //? //see state of connection?
}



