//Initialize widgets on the screens based on the application/backend (or GUI-API)

#include "GUI_unified.h"


//Set at GUI-startup:

void _GUI_initScreen__StartupSplash () {
    //_GUI_removeAllObjectEvents( ui_Screen__StartupSplash ); //lv_anim_del( NULL, (lv_anim_exec_xcb_t) _ui_anim_callback_set_image_frame );
}


void _GUI_initScreen__Initial_Setup () {
    //_GUI_setScreenLoadCallback( ui_Screen__Initial_Setup, _GUI_initScreenValues__Initial_Setup ); //made automatically at GUI-init based on screen-descriptor

    _GUI_removeAllObjectEvents( ui_Textarea__Initial_Setup__Serial_Number ); //password-protected, and clicking again to the same field has problem with bringing keyboard up again anyway
    _GUI_setClickCallback( ui_Textarea__Initial_Setup__Serial_Number, _GUI_clicked__Textarea__Initial_Setup__Serial_Number ); //_GUI_setPasswordCall( ui_Textarea__Initial_Setup__Serial_Number, true, _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY, GUI_SCREEN_ID__Initial_Setup );
    _GUI_removeAllObjectEvents( ui_Textarea__Initial_Setup__Model_Number ); //password-protected, and clicking again to the same field has problem with bringing keyboard up again anyway
    _GUI_setClickCallback( ui_Textarea__Initial_Setup__Model_Number, _GUI_clicked__Textarea__Initial_Setup__Model_Number ); //_GUI_setPasswordCall( ui_Textarea__Initial_Setup__Model_Number, true, _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY, GUI_SCREEN_ID__Initial_Setup );

    _GUI_setClickCallback( ui_Button__Initial_Setup__Pump1, _GUI_clicked__Button__Initial_Setup__Pump1 );
    _GUI_setClickCallback( ui_Button__Initial_Setup__Pump2, _GUI_clicked__Button__Initial_Setup__Pump2 );
    _GUI_setClickCallback( ui_Button__Initial_Setup__Pump3, _GUI_clicked__Button__Initial_Setup__Pump3 );
    _GUI_setValueChangeCallback( ui_Roller__Initial_Setup__PistonSize, _GUI_changed__Roller__Initial_Setup__PistonSize );
    _GUI_setValueChangeCallback( ui_Roller__Initial_Setup__StrokeLength, _GUI_changed__Roller__Initial_Setup__StrokeLength );
    _GUI_setValueChangeCallback( ui_Roller__Initial_Setup__WettedParts, _GUI_changed__Roller__Initial_Setup__WettedParts );

    _GUI_removeAllObjectEvents( ui_Button__Initial_Setup__ChangeRemotePassword ); //screen-change is made internally instead to call the correct screen programmatically
    _GUI_setClickCallback( ui_Button__Initial_Setup__ChangeRemotePassword, _GUI_clicked__Button__Initial_Setup__ChangeRemotePassword ); //_GUI_setPasswordCall( ui_Button__Initial_Setup__ChangeRemotePassword, true, _GUI_PASSWORD_SCREEN_MODE__CHANGE_REMOTE, GUI_SCREEN_ID__Initial_Setup );
    _GUI_removeAllObjectEvents( ui_Button__Initial_Setup__SelectOptions ); //screen-change is made internally instead to call the correct screen programmatically
    _GUI_setClickCallback( ui_Button__Initial_Setup__SelectOptions, _GUI_clicked__Button__Initial_Setup__SelectOptions ); //_GUI_setPasswordCall( ui_Button__Initial_Setup__SelectOptions, !*IOp.Factory_Initialization_Done, _GUI_PASSWORD_SCREEN_MODE__CHANGE_FACTORY, GUI_SCREEN_ID__Initial_Setup );

    _GUI_removeAllObjectEvents( ui_Button__Initial_Setup__Next ); //original screenchange doesn't necessarily update CurrentScreenID
    _GUI_setClickCallback( ui_Button__Initial_Setup__Next, _GUI_clicked__Button__Initial_Setup__Next );

    _GUI_setClickCallback( ui_Button__Initial_Setup__FactoryTest, _GUI_clicked__Button__Initial_Setup__FactoryTest ); //Placeholder for future factory test, so it does nothing yet. //Popup prompt? („Do you want to perform a Factory burn-in test?”, „Yes”, „No”) //A pop-up window („The factory test has been completed”, „Ok”)
}


void _GUI_initScreen__Select_Option () {
    //_GUI_setScreenLoadCallback( ui_Screen__Select_Option, _GUI_initScreenValues__Select_Option );

    _GUI_setValueChangeCallback( ui_Checkbox__Select_Option__PressureTransducer, _GUI_changed__Checkbox__Select_Option__PressureTransducer );
    _GUI_setValueChangeCallback( ui_Checkbox__Select_Option__WashPort_Pump, _GUI_changed__Checkbox__Select_Option__WashPort_Pump );
    _GUI_setValueChangeCallback( ui_Checkbox__Select_Option__LeakDetector_Sensor, _GUI_changed__Checkbox__Select_Option__LeakDetector_Sensor );
    _GUI_setValueChangeCallback( ui_Checkbox__Select_Option__FlowSensor, _GUI_changed__Checkbox__Select_Option__FlowSensor );
    _GUI_setValueChangeCallback( ui_Checkbox__Select_Option__Encoder, _GUI_changed__Checkbox__Select_Option__Encoder );

    _GUI_removeAllObjectEvents( ui_Button__Select_Option__OK );
    _GUI_setClickScreenChangeByID( ui_Button__Select_Option__OK, GUI_SCREEN_ID__Initial_Setup );

    _GUI_setClickCallback( ui_Button__Select_Option__OK, _GUI_clicked__Button__Select_Option__OK );
}


void _GUI_initScreen__Generic_Password () {
    //_GUI_setScreenLoadCallback( ui_Screen__Generic_Password, _GUI_initScreenValues__Generic_Password );

    _GUI_removeAllObjectEvents( ui_Button__Generic_Password__Cancel );
    _GUI_setClickCallback( ui_Button__Generic_Password__Cancel, _GUI_clicked__Button__Generic_Password__Cancel );

    _GUI_removeAllObjectEvents( ui_Button__Generic_Password__OK );
    _GUI_setClickCallback( ui_Button__Generic_Password__OK, _GUI_clicked__Button__Generic_Password__OK );

    _GUI_setClickCallback( ui_Keyboard__Generic_Password__PasswordEntry, _GUI_clicked__Keyboard__Generic_Password__PasswordEntry );
    _GUI_setReadyCallback( ui_Keyboard__Generic_Password__PasswordEntry, _GUI_clicked__Button__Generic_Password__OK );
}


void _GUI_initScreen__Home () {
    //_GUI_setScreenLoadCallback( ui_Screen__Home, _GUI_initScreenValues__Home );

    _GUI_setClickCallback( ui_Button__Home__Pump1, _GUI_clicked__Button__Home__Pump1 );
    _GUI_setClickCallback( ui_Button__Home__Pump2, _GUI_clicked__Button__Home__Pump2 );
    _GUI_setClickCallback( ui_Button__Home__Pump3, _GUI_clicked__Button__Home__Pump3 );

    _GUI_setPressingCallback( ui_Button__Home__FlowOrPressure_Up, _GUI_pressing__Button__Home__FlowOrPressure_Up ); //needs key-repeat delays
    _GUI_setPressingCallback( ui_Button__Home__FlowOrPressure_Down, _GUI_pressing__Button__Home__FlowOrPressure_Down ); //needs key-repeat delays

    _GUI_setClickCallback( ui_Button__Home__StartStop, _GUI_clicked__Button__Home__StartStop ); //zeroes the counters, sends event to backend?
    _GUI_setClickCallback( ui_Button__Home__Purge, _GUI_clicked__Button__Home__Purge ); //Popup (“Do you want to start the purge process”, “Confirm”, “Cancel”)
}


void _GUI_initScreen__Pump_Settings () {
    //_GUI_setScreenLoadCallback( ui_Screen__Pump_Settings, _GUI_initScreenValues__Pump_Settings );

    _GUI_setClickCallback( ui_Button__Pump_Settings__Pump1, _GUI_clicked__Button__Pump_Settings__Pump1 );
    _GUI_setClickCallback( ui_Button__Pump_Settings__Pump2, _GUI_clicked__Button__Pump_Settings__Pump2 );
    _GUI_setClickCallback( ui_Button__Pump_Settings__Pump3, _GUI_clicked__Button__Pump_Settings__Pump3 );
    _GUI_setValueChangeCallback( ui_Slider__Pump_Settings__CompressibilityCompensation_Value, _GUI_changed__Slider__Pump_Settings__CompressibilityCompensation_Value );

    _GUI_createPumpSettingValueList();
}


void _GUI_initScreen__Advanced_Settings () {
    //_GUI_setScreenLoadCallback( ui_Screen__Advanced_Settings, _GUI_initScreenValues__Advanced_Settings );

    _GUI_setClickCallback( ui_Button__Maintenance__Pump1, _GUI_clicked__Button__Maintenance__Pump1 );
    _GUI_setClickCallback( ui_Button__Maintenance__Pump2, _GUI_clicked__Button__Maintenance__Pump2 );
    _GUI_setClickCallback( ui_Button__Maintenance__Pump3, _GUI_clicked__Button__Maintenance__Pump3 );

    _GUI_removeAllObjectEvents( ui_Button__Advanced_Settings__FactoryMenu ); //screen-change is made internally instead to call the correct screen programmatically
    _GUI_setClickCallback( ui_Button__Advanced_Settings__FactoryMenu, _GUI_clicked__Button__Advanced_Settings__FactoryMenu ); //_GUI_setPasswordCall( ui_Button__Advanced_Settings__FactoryMenu, true, _GUI_PASSWORD_SCREEN_MODE__USER, GUI_SCREEN_ID__Initial_Setup );

    _GUI_setClickCallback( ui_Button__Advanced_Settings__FactoryReset, _GUI_clicked__Button__Advanced_Settings__FactoryReset );
}


void _GUI_initScreen__Maintenance () {
    //_GUI_setScreenLoadCallback( ui_Screen__Maintenance, _GUI_initScreenValues__Maintenance );

    _GUI_setClickCallback( ui_Button__Maintenance__Washport_Rinse, _GUI_clicked__Button__Maintenance__Washport_Rinse ); //runs washport on all pumps immediately for 30 seconds. This button should be disabled for 30 seconds. after the user clicks on it.
    _GUI_setClickCallback( ui_Button__Maintenance__Reset_PumpPart_Runtime, _GUI_clicked__Button__Maintenance__Reset_PumpPart_Runtime ); //Set the value of the “Seal Run Time” or the “Check Valve Run Time” to 0.
    _GUI_setClickCallback( ui_Button__Maintenance__ZeroPressure_Transducer, _GUI_clicked__Button__Maintenance__ZeroPressure_Transducer ); //It is just 1 signal on the backend, The feedback must be immediate? (what does this mean?)
    _GUI_setClickCallback( ui_Button__Maintenance__Sensor_MoveMotorsHome, _GUI_clicked__Button__Maintenance__Sensor_MoveMotorsHome ); //It is just 1 signal on the backend.
}


void _GUI_initScreen__Communications () {
    //_GUI_setScreenLoadCallback( ui_Screen__Communications, _GUI_initScreenValues__Communications );

    _GUI_setClickCallback( ui_Button__Communications__Serial, _GUI_clicked__Button__Communications__Serial );
    _GUI_setClickCallback( ui_Button__Communications__Ethernet, _GUI_clicked__Button__Communications__Ethernet );
    _GUI_setClickCallback( ui_Button__Communications__WiFi, _GUI_clicked__Button__Communications__WiFi );

    //select subscreen at startup (comment out the others):
    //_GUI_showSubscreen__Communications__Serial();
    //_GUI_showSubscreen__Communications__Ethernet();
    _GUI_showSubscreen__Communications__WiFi();

    _GUI_createSelectorOptions_Integer( ui_Roller__Communications__Serial_DeviceID, 0, 255, 1, "" );
    //_GUI_createSelectorOptions( ui_Roller__Communications__Serial_BaudRate, "4800\n9600\n19200\n38400\n57600\n115200\n230400\n460800\n921600" );
    //_GUI_createSelectorOptions( ui_Roller__Communications__Serial_DatabitsPerBaud, "5\n7\n8\n9" );
    //_GUI_createSelectorOptions( ui_Roller__Communications__Serial_StopBitAmount, "1\n1.5\n2" );
    //_GUI_createSelectorOptions( ui_Roller__Communications__Serial_ParityBitType, "Odd\nEven\nMark\nSpace" );

    _GUI_setClickCallback( ui_Button__Communications__WiFi_Connect, _GUI_clicked__Button__Communications__WiFi_Connect );
    _GUI_setClickCallback( ui_Button__Communications__WiFi_ForgetConnection, _GUI_clicked__Button__Communications__WiFi_ForgetConnection );

    //_GUI_setClickCallback( ui_Keyboard__Communications__WiFi_AuthenticationDataEntry, _GUI_clicked__Keyboard__Communications__WiFi_AuthenticationDataEntry );
    _GUI_createSelectorOptions( ui_Roller__Communications__WiFi_SSIDlist, "" ); //_GUI_clearSelectorOptions( ui_Roller__Communications__WiFi_SSIDlist );
    _GUI_setValueChangeCallback( ui_Roller__Communications__WiFi_SSIDlist, _GUI_changed__Roller__Communications__WiFi_SSIDlist );
}


void _GUI_initScreen__Self_Test () {
    //_GUI_setScreenLoadCallback( ui_Screen__Self_Test, _GUI_initScreenValues__Self_Test );

    _GUI_setClickCallback( ui_Button__Self_Test__Run_SelfTest, _GUI_clicked__Button__Self_Test__Run_SelfTest ); //Starts the self-test. Froze the screen while the process except the scrollbar. Popup at the end: „The test has ended” with an OK button
    _GUI_setClickCallback( ui_Button__Self_Test__SaveToFlashdrive, _GUI_clicked__Button__Self_Test__SaveToFlashdrive ); //It only appears after the test ends. This button will be enabled only after the test has ended. After the save show a popup: („The output of the test has successfully saved on the root of the flash drive with this name: optos_test_log.txt”, „Ok”)
}


void _GUI_initScreen__Firmware_Update () {
    //_GUI_setScreenLoadCallback( ui_Screen__Firmware_Update, _GUI_initScreenValues__Firmware_Update );

    _GUI_setClickCallback( ui_Button__Firmware_Update__UpdateFromWeb, _GUI_clicked__Button__Firmware_Update__UpdateFromWeb ); //Popup at the end: („The firmware has been successfully updated”, „OK”) //Or Popup(„No internet connection”, „OK”) //Or in case of any other error: Popup(„Error: ERROR_MESSAGE”, „OK”)
    _GUI_setClickCallback( ui_Button__Firmware_Update__UpdateFromFlashdrive, _GUI_clicked__Button__Firmware_Update__UpdateFromFlashdrive ); //If the file could not be found: Popup („The installer file „optos_firmware_installer” could not be found in the root of the flash drive”, „OK”). //Popup at the end in case of success: („The firmware has been successfully updated”, „OK”). //Or Popup(„No Flash drive found”, „OK”) //Or in case of any other error: Popup(„Error: ERROR_MESSAGE”, „OK”)
}


void _GUI_initScreen__Popup_Modal () {
}
