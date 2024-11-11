
#include <stdio.h>  //for printf(), etc.
#include <string.h>

#include "CoreM33_Example.h"

#include "CoreMessaging.h"  //"Modules/Common/CoreMessaging/CoreMessaging.h" //#include "Modules/CoreM33/CoreMessaging/CoreM33_CoreMessaging.h"


#include "GUI_API_Includes.h"  //"Modules/Common/GUI_API/GUI_API_Includes.h"
#include "GUI_API_Events.h"

#if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )
 #define CORE_M33__NAMESPACE_ M33.
 struct M33variables { //need to put in different namespace due to C's restriction of one-time definition of a single name linked into the same TestBench file, but can be used directly when compiled to different runnables on the cores
#else
 #define CORE_M33__NAMESPACE_
#endif

#define EXTERN ;       // becomes empty in the source-file
 #include "GUI_API_Variables.h"  //"Modules/Common/GUI_API/GUI_API_Variables.h"
#undef EXTERN

#if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )
 } M33;
#endif


static CoreMessaging_VariableDescriptor GUI_API_VariableDescriptors [] = { //should contain description of all variables/arrays to automatically transfer between the cores upon change
    #define PREFIX &CORE_M33__NAMESPACE_
     #include "GUI_API_VariableDescriptors.h"  //"Modules/Common/GUI_API/GUI_API_VariableDescriptors.h"
    #undef PREFIX
};

static bool UpdateProgress = false;
static bool SelfTestProgress = false;



static void stateMachine ();



void CoreM33_testEventFunction__Purge () { printf( "CoreM33 Event received from GUI: Pump Control 'Purge' button was pressed.\n" ); }
void CoreM33_testEventFunction__StartStop () { printf( "CoreM33 Event received from GUI: Pump Control 'Start/Stop' button was pressed.\n" ); }
void CoreM33_testEventFunction__UpdateFromWeb () {
    printf( "CoreM33 Event received from GUI: Firmware Update 'Update from Web' button was pressed.\n" );
    UpdateProgress = true; CORE_M33__NAMESPACE_ FirmwareUpdate_Progress_Bar = 0;
}
void CoreM33_testEventFunction__UpdateFromFlashDrive () {
    printf( "CoreM33 Event received from GUI: Firmware Update 'Update from flash-drive' button was pressed.\n" );
    UpdateProgress = true; CORE_M33__NAMESPACE_ FirmwareUpdate_Progress_Bar = 0;
}
void CoreM33_testEventFunction__RunSelfTest () {
    printf( "CoreM33 Event received from GUI: Self-test 'Run Self-test' button was pressed.\n" );
    SelfTestProgress = true; CORE_M33__NAMESPACE_ SelfTest_ProgressBar = 0;
}



static void initVariables () {
    CORE_M33__NAMESPACE_ Factory_Initialization_Done = false; //true; //false;
    CORE_M33__NAMESPACE_ Model_Number = 123;
    CORE_M33__NAMESPACE_ NumberOfPumps = 3; //1; //3; //2; //1; //2; //3;
    strcpy( (char*) CORE_M33__NAMESPACE_ FactoryPassword, "fct" ); strcpy( (char*) CORE_M33__NAMESPACE_ UserPassword, "usr" ); strcpy( (char*) CORE_M33__NAMESPACE_ RemotePassword, "rmt" ); //to be on M33 it needs array-messaging finalized
    strcpy( (char*) CORE_M33__NAMESPACE_ Message_Center, "Dummy Status Message: Ensure a valid string here (terminated by 0)" );
    CORE_M33__NAMESPACE_ PistonSizes.PistonSize_Pump1 = 2; CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump1 = 0; CORE_M33__NAMESPACE_ WettedParts.WettedPart_Pump1 = 2;
    CORE_M33__NAMESPACE_ PistonSizes.PistonSize_Pump2 = 0; CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump2 = 1; CORE_M33__NAMESPACE_ WettedParts.WettedPart_Pump2 = 1;
    CORE_M33__NAMESPACE_ PistonSizes.PistonSize_Pump3 = 1; CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump3 = 2; CORE_M33__NAMESPACE_ WettedParts.WettedPart_Pump3 = 0;
    CORE_M33__NAMESPACE_ Options.Pressure_Transducer = true; CORE_M33__NAMESPACE_ Options.WashPort_Pump = false;
    CORE_M33__NAMESPACE_ Options.LeakDetector_Sensor = true; CORE_M33__NAMESPACE_ Options.Flow_Sensor = false; CORE_M33__NAMESPACE_ Options.Encoder = true;
    CORE_M33__NAMESPACE_ Compressibility_1 = 83; CORE_M33__NAMESPACE_ Compressibility_2 = 53; CORE_M33__NAMESPACE_ Compressibility_3 = 14;
    CORE_M33__NAMESPACE_ DispenseModes.Dispense_Mode_Pump1 = 0/*2*//*0*/; CORE_M33__NAMESPACE_ DispenseModes.Dispense_Mode_Pump2 = 1/*2*//*1*/; CORE_M33__NAMESPACE_ DispenseModes.Dispense_Mode_Pump3 = 2;
    CORE_M33__NAMESPACE_ PumpOutputRatios.Output_Ratio_Pump1 = 3; CORE_M33__NAMESPACE_ PumpOutputRatios.Output_Ratio_Pump2 = 1; CORE_M33__NAMESPACE_ PumpOutputRatios.Output_Ratio_Pump3 = 4;
    CORE_M33__NAMESPACE_ AdvancedSetup4_bits.RS_232 = 1; CORE_M33__NAMESPACE_ AdvancedSetup4_bits.RS_485 = 0;
    CORE_M33__NAMESPACE_ AnalogOutputs = (struct AnalogOutputs_t) { .Analog_Output_pump_1 = 2, .Analog_Output_pump_2 = 0, .Analog_Output_pump_3 = 1 };
    CORE_M33__NAMESPACE_ RemoteControls.Serial_RemoteControl = 0; //1; //0; //1; //only 1 remote-control allowed at a time according to specs
    CORE_M33__NAMESPACE_ Device_ID = 20; CORE_M33__NAMESPACE_ Baud_Rate = 2; CORE_M33__NAMESPACE_ SerialSettings.Data_Bit = 3;  CORE_M33__NAMESPACE_ SerialSettings.Stop_Bit = 2;  CORE_M33__NAMESPACE_ SerialSettings.Parity_Bit = 1;
    CORE_M33__NAMESPACE_ EthernetSettings.DHCP = 1; CORE_M33__NAMESPACE_ RemoteControls.Ethernet_RemoteControl = 0; //1; //only 1 remote-control allowed at a time according to specs
    CORE_M33__NAMESPACE_ WiFiConnectionDetails.Security_Type = 2; CORE_M33__NAMESPACE_ WiFiSettings.Automatic_connection = 1; CORE_M33__NAMESPACE_ RemoteControls.Wifi_RemoteControl = 0; //1; //only 1 remote-control allowed at a time according to specs
    CORE_M33__NAMESPACE_ Network_Details[1].Security_Type = 1; CORE_M33__NAMESPACE_ Network_Details[2].Security_Type = 2; CORE_M33__NAMESPACE_ Network_Details[3].Security_Type = 3;
    CORE_M33__NAMESPACE_ Washport_Auto = 1;
    CORE_M33__NAMESPACE_ AdvancedSetup_bits.Pressure_unit_of_measure = 1; CORE_M33__NAMESPACE_ AdvancedSetup_bits.Pressure_limit_enabled = 1;
    CORE_M33__NAMESPACE_ StopRestart_bits.Stop_on_Stall = 1; CORE_M33__NAMESPACE_ StopRestart_bits.Restart_on_Power_Up = 1;
    CORE_M33__NAMESPACE_ Pressure_Alarm_Min = 245; CORE_M33__NAMESPACE_ Pressure_Alarm_Max = 6425;
    CORE_M33__NAMESPACE_ Pump1_Check_Valve_Alarm = 2345; CORE_M33__NAMESPACE_ Pump2_Check_Valve_Alarm = 393; CORE_M33__NAMESPACE_ Pump3_Check_Valve_Alarm = 1536;
    CORE_M33__NAMESPACE_ Pump1_Total_Seal_Alarm = 5557; CORE_M33__NAMESPACE_ Pump2_Total_Seal_Alarm = 34526; CORE_M33__NAMESPACE_ Pump3_Total_Seal_Alarm = 800; //16;
    CORE_M33__NAMESPACE_ Pump_1_Total_Run = 3569;
    CORE_M33__NAMESPACE_ Pressure_Target = 2193; CORE_M33__NAMESPACE_ Flow_Rate1 = 45.69; CORE_M33__NAMESPACE_ Flow_Rate2 = 90.2; CORE_M33__NAMESPACE_ Flow_Rate3 = 5.4;
    CORE_M33__NAMESPACE_ Flow_total_1 = 45.4; CORE_M33__NAMESPACE_ Flow_total_3 = 180.25; CORE_M33__NAMESPACE_ Run_time_2 = 88; CORE_M33__NAMESPACE_ Run_time_3 = 452;
    CORE_M33__NAMESPACE_ Dispense_Amount_1 = 234.23; CORE_M33__NAMESPACE_ Dispense_Duration_1 = 32340; CORE_M33__NAMESPACE_ Delay_1 = 3445; CORE_M33__NAMESPACE_ Occurrences_1 = 23499;
    CORE_M33__NAMESPACE_ Dispense_Amount_2 = 7.6;    CORE_M33__NAMESPACE_ Dispense_Duration_2 = 84;    CORE_M33__NAMESPACE_ Delay_2 = 945;  CORE_M33__NAMESPACE_ Occurrences_2 = 56499;
    CORE_M33__NAMESPACE_ Dispense_Amount_3 = 43.2;   CORE_M33__NAMESPACE_ Dispense_Duration_3 = 1492;  CORE_M33__NAMESPACE_ Delay_3 = 7554; CORE_M33__NAMESPACE_ Occurrences_3 = 8;
    CORE_M33__NAMESPACE_ Pump2_Seal_RunTime = 256; CORE_M33__NAMESPACE_ Pump2_CheckValve_RunTime = 3526;
    CORE_M33__NAMESPACE_ Address[0]=123; CORE_M33__NAMESPACE_ Address[1]=234; CORE_M33__NAMESPACE_ Address[2]=56; CORE_M33__NAMESPACE_ Address[3]=7;
    CORE_M33__NAMESPACE_ Mask[0]=255; CORE_M33__NAMESPACE_ Mask[1]=255; CORE_M33__NAMESPACE_ Mask[2]=255; CORE_M33__NAMESPACE_ Mask[3]=0;
    CORE_M33__NAMESPACE_ GateWay[0]=210; CORE_M33__NAMESPACE_ GateWay[1]=109; CORE_M33__NAMESPACE_ GateWay[2]=98; CORE_M33__NAMESPACE_ GateWay[3]=77;
    strcpy( (char*) CORE_M33__NAMESPACE_ SSID, "Example-SSID.." ); strcpy( (char*) CORE_M33__NAMESPACE_ Password, "wfi" );
    strcpy( (char*) CORE_M33__NAMESPACE_ Networks[0], "Network 1" ); strcpy( (char*) CORE_M33__NAMESPACE_ Networks[1], "Network 2" ); strcpy( (char*) CORE_M33__NAMESPACE_ Networks[2], "Example Network" );
    strcpy( (char*) CORE_M33__NAMESPACE_ Networks[3], "Exawple Network 2" ); strcpy( (char*) CORE_M33__NAMESPACE_ Networks[4], "Whatever" ); strcpy( (char*) CORE_M33__NAMESPACE_ Networks[5], "Good Strength WiFi" );

    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[0], "This is an example for log-message.");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[1], "");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[2], "3rd line of the log");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[3], " ");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[4], "The board will update this array after test.");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[5], "And the GUI will follow in every 1 second.");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[6], "--------------------------------------------"); //this line is exactly 45 characters
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[7], "This dashe-line above has exactly 44 chars.");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[8], "This is example of a changing text:");
    strcpy( (char*) CORE_M33__NAMESPACE_ TextBuffer[9], "");
    CORE_M33__NAMESPACE_ FirmwareUpdate_Progress_Bar = 0;
}


static inline void CoreM33_bindEventFunction ( int event_id, void (*callback_function)() ) {
    CoreMessaging_bindEventFunction( event_id, callback_function, COREMESSAGING_ENDPOINT__CORE_M33 );
}

void initEvents () {
    CoreMessaging_bindEventFunction( GUI_TO_BACKEND_EVENT__Purge_button, CoreM33_testEventFunction__Purge, COREMESSAGING_ENDPOINT__CORE_M33 );
    CoreM33_bindEventFunction( GUI_TO_BACKEND_EVENT__StartStop_button, CoreM33_testEventFunction__StartStop );
    CoreM33_bindEventFunction( GUI_TO_BACKEND_EVENT__Update_on_the_web_Button, CoreM33_testEventFunction__UpdateFromWeb );
    CoreM33_bindEventFunction( GUI_TO_BACKEND_EVENT__Update_from_flash_drive_button, CoreM33_testEventFunction__UpdateFromFlashDrive );
    CoreM33_bindEventFunction( GUI_TO_BACKEND_EVENT__Run_Self_Test_button, CoreM33_testEventFunction__RunSelfTest );
    //... not all bingings are necessarily created in this example but can be added in the final product by using this binding function in the core where it should be run
}


void CoreM33_CoreMessaging_init () {
    CoreMessaging_init( GUI_API_VariableDescriptors, COREMESSAGING_ENDPOINT__CORE_M33 );  //CoreM33_CoreMessaging_init();
    initVariables();
    initEvents();
}

void CoreM33_init () { CoreM33_CoreMessaging_init(); }


void CoreM33_CoreMessaging_refresh () {
    CoreMessaging_refresh( GUI_API_VariableDescriptors, COREMESSAGING_ENDPOINT__CORE_M33, COREMESSAGING_ENDPOINT__CORE_A55 );  //CoreM33_CoreMessaging_refresh();
    //printf( "CoreM33_CoreMessaging: GUI_Version: %d, Firmware_Version: %d\n", CORE_M33__NAMESPACE_ GUI_Version, CORE_M33__NAMESPACE_ Firmware_Version );
    stateMachine();
}

void CoreM33_refresh () { CoreM33_CoreMessaging_refresh(); }


static void stateMachine () { //TestBench state machine
    static uint8_t TestCounter = 0; ++TestCounter;

    //Continuously changing (e.g. measured) variable values and pointed text (e.g. status message) to display synchronously/cyclically on screen

    //if ( (CORE_M33__NAMESPACE_ GUI_Version += 1) >= 9999 )  CORE_M33__NAMESPACE_ GUI_Version = 0100;
    //if ( (CORE_M33__NAMESPACE_ Firmware_Version += 1) >= 9999 )  CORE_M33__NAMESPACE_ Firmware_Version = 0100;  //--CORE_M33__NAMESPACE_ Firmware_Version; //printf( "CoreM33: GUI_Version:%d, Firmware_Version:%d\n", M33.GUI_Version, M33.Firmware_Version );
    //if ( (CORE_M33__NAMESPACE_ Serial_Number += 1) >= 999999 )  CORE_M33__NAMESPACE_ Serial_Number = 0;
    //if ( (CORE_M33__NAMESPACE_ Model_Number += 1) >= 99/*999*/ )  CORE_M33__NAMESPACE_ Model_Number = 0;
    //if ( (CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump1 += 1) >= 4 )  CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump1 = 0;
    //if ( (CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump2 += 1) >= 4 )  CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump2 = 0;
    //if ( (CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump3 += 1) >= 4 )  CORE_M33__NAMESPACE_ StrokeLengths.StrokeLength_Pump3 = 0;
    CORE_M33__NAMESPACE_ Connections.USB_Inserted = (TestCounter & 0x80) != 0; //true;
    CORE_M33__NAMESPACE_ Connections.Ethernet_Active = (TestCounter & 0x20) != 0; //true;
    CORE_M33__NAMESPACE_ Connections.Wifi_On = (TestCounter & 0x40) != 0; //true;
    //if ( (CORE_M33__NAMESPACE_ Flow_Rate1 += 1.04) >= 100.00 )  CORE_M33__NAMESPACE_ Flow_Rate1 = 0.002;
    //if ( (CORE_M33__NAMESPACE_ Flow_Rate2 += 1.5) >= 100.00 )  CORE_M33__NAMESPACE_ Flow_Rate2 = 70.002;
    if ( (CORE_M33__NAMESPACE_ Flow_Rate3 += 2.9) >= 100.00 )  CORE_M33__NAMESPACE_ Flow_Rate3 = 20.002;
    if ( (CORE_M33__NAMESPACE_ Pressure/*1*/ += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure/*1*/ = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure2 += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure2 = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure3 += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure3 = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure_Target += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure_Target = 0;
    //if ( (CORE_M33__NAMESPACE_ Flow_total_1 += 1.324) >= 2000.0 )  CORE_M33__NAMESPACE_ Flow_total_1 = 0;
    if ( (CORE_M33__NAMESPACE_ Flow_total_2 += 3.324) >= 2000.0 )  CORE_M33__NAMESPACE_ Flow_total_2 = 0;
    //if ( (CORE_M33__NAMESPACE_ Flow_total_3 += 5.324) >= 2000.0 )  CORE_M33__NAMESPACE_ Flow_total_3 = 0;
    if ( (CORE_M33__NAMESPACE_ Run_time_1 += 1) >= 50000 )  CORE_M33__NAMESPACE_ Run_time_1 = 0;
    //if ( (CORE_M33__NAMESPACE_ Run_time_2 += 1) >= 50000 )  CORE_M33__NAMESPACE_ Run_time_2 = 0;
    //if ( (CORE_M33__NAMESPACE_ Run_time_3 += 1) >= 50000 )  CORE_M33__NAMESPACE_ Run_time_3 = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure_Graph [30][2] += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure_Graph [30][2] = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure_Alarm_Max/*Upper*/ += 1) >= 500/*7500*/ )  CORE_M33__NAMESPACE_ Pressure_Alarm_Max/*Upper*/ = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure_Alarm_Min/*Lower*/ += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure_Alarm_Min/*Lower*/ = 0;
    if ( (CORE_M33__NAMESPACE_ DateTime.Year += 1) >= 7500 )  CORE_M33__NAMESPACE_ DateTime.Year = 0;
    if ( (CORE_M33__NAMESPACE_ DateTime.Month += 1) >= 12 )  CORE_M33__NAMESPACE_ DateTime.Month = 0;
    if ( (CORE_M33__NAMESPACE_ DateTime.Day += 1) >= 31 )  CORE_M33__NAMESPACE_ DateTime.Day = 0;
    if ( (CORE_M33__NAMESPACE_ DateTime.Hour += 1) >= 59 )  CORE_M33__NAMESPACE_ DateTime.Hour = 0;
    if ( (CORE_M33__NAMESPACE_ DateTime.Minute += 1) >= 59 )  CORE_M33__NAMESPACE_ DateTime.Minute = 1;
    if ( UpdateProgress && (CORE_M33__NAMESPACE_ FirmwareUpdate_Progress_Bar += 1) >= 100 ) { CORE_M33__NAMESPACE_ FirmwareUpdate_Progress_Bar = 0; UpdateProgress = false; }
    if ( (CORE_M33__NAMESPACE_ Pump1_CheckValve_RunTime += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump1_CheckValve_RunTime = 0; //if ( (CORE_M33__NAMESPACE_ Pump1_Check_Valve_Hours += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump1_Check_Valve_Hours = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump2_CheckValve_RunTime += 100) >= 3999 )  CORE_M33__NAMESPACE_ Pump2_CheckValve_RunTime = 0; //if ( (CORE_M33__NAMESPACE_ Pump2_Check_Valve_Hours += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump2_Check_Valve_Hours = 0;
    if ( (CORE_M33__NAMESPACE_ Pump3_CheckValve_RunTime += 5) >= 599 )  CORE_M33__NAMESPACE_ Pump3_CheckValve_RunTime = 0;
    if ( (CORE_M33__NAMESPACE_ Pump_1_Total_Run += 1) >= 100000 )  CORE_M33__NAMESPACE_ Pump_1_Total_Run = 0; //if ( (CORE_M33__NAMESPACE_ Pump1_Total_Hours_Run += 1) >= 100000 )  CORE_M33__NAMESPACE_ Pump1_Total_Hours_Run = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump2_Total_Hours_Run += 1) >= 100000 )  CORE_M33__NAMESPACE_ Pump2_Total_Hours_Run = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump3_Total_Hours_Run += 1) >= 100000 )  CORE_M33__NAMESPACE_ Pump3_Total_Hours_Run = 0;
    if ( (CORE_M33__NAMESPACE_ Pump1_Seal_RunTime += 2) >= 1999 )  CORE_M33__NAMESPACE_ Pump1_Seal_RunTime = 900;     //if ( (CORE_M33__NAMESPACE_ Pump1_Total_Seal_Hours += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump1_Total_Seal_Hours = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump2_Seal_RunTime += 3) >= 1999 )  CORE_M33__NAMESPACE_ Pump2_Seal_RunTime = 0; //if ( (CORE_M33__NAMESPACE_ Pump2_Total_Seal_Hours += 3) >= 1999 )  CORE_M33__NAMESPACE_ Pump2_Total_Seal_Hours = 0;
    if ( (CORE_M33__NAMESPACE_ Pump3_Seal_RunTime += 1) >= 399 )  CORE_M33__NAMESPACE_ Pump3_Seal_RunTime = 200; //if ( (CORE_M33__NAMESPACE_ Pump3_Total_Seal_Hours += 1) >= 399 )  CORE_M33__NAMESPACE_ Pump3_Total_Seal_Hours = 200;
    //if ( (CORE_M33__NAMESPACE_ Pump1_Check_Valve_Alarm += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump1_Check_Valve_Alarm = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump2_Check_Valve_Alarm += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump2_Check_Valve_Alarm = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump3_Check_Valve_Alarm += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump3_Check_Valve_Alarm = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump1_Total_Seal_Alarm += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump1_Total_Seal_Alarm = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump2_Total_Seal_Alarm += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump2_Total_Seal_Alarm = 0;
    //if ( (CORE_M33__NAMESPACE_ Pump3_Total_Seal_Alarm += 1) >= 9999 )  CORE_M33__NAMESPACE_ Pump3_Total_Seal_Alarm = 0;
    //if ( (CORE_M33__NAMESPACE_ Data_Frequency += 1) >= 999 )  CORE_M33__NAMESPACE_ Data_Frequency = 0;
    //if ( (CORE_M33__NAMESPACE_ RS_485_ID += 1) >= 255 )  CORE_M33__NAMESPACE_ RS_485_ID = 0;
    if ( SelfTestProgress && (CORE_M33__NAMESPACE_ SelfTest_ProgressBar += 1) >= 100 ) { CORE_M33__NAMESPACE_ SelfTest_ProgressBar = 0; SelfTestProgress = false; printf("Self-test finished\n"); }
    //if ( (CORE_M33__NAMESPACE_ Compressibility_1 += 1) >= 100 )  CORE_M33__NAMESPACE_ Compressibility_1 = 10;
    //if ( (CORE_M33__NAMESPACE_ Compressibility_2 += 1) >= 100 )  CORE_M33__NAMESPACE_ Compressibility_2 = 20;
    //if ( (CORE_M33__NAMESPACE_ Compressibility_3 += 1) >= 100 )  CORE_M33__NAMESPACE_ Compressibility_3 = 30;
    sprintf( (char*) CORE_M33__NAMESPACE_ TextBuffer[9], "Pump1 Total Runtime: %d", (int) CORE_M33__NAMESPACE_ Pump_1_Total_Run );

}


#undef CORE_M33__NAMESPACE_

