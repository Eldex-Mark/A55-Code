
#include <stdio.h>  //for printf(), etc.
#include <string.h>

#include "CoreA55_Example.h"


#include "CoreMessaging.h"  //#include "Modules/Common/CoreMessaging/CoreMessaging.h" //#include "CoreA55_CoreMessaging.h" //"Modules/CoreA55/CoreMessaging/CoreA55_CoreMessaging.h"

#include "GUI.h"  //"Modules/CoreA55/GUI/GUI.h"


#include "GUI_API_Includes.h"  //"Modules/Common/GUI_API/GUI_API_Includes.h"
#include "GUI_API_Events.h"

#define EXTERN ;       // becomes empty in the source-file
 #include "GUI_API_Variables.h"  //"Modules/Common/GUI_API/GUI_API_Variables.h"
#undef EXTERN


static CoreMessaging_VariableDescriptor GUI_API_VariableDescriptors [] = { //should contain description of all variables/arrays to automatically transfer between the cores upon change
#define PREFIX &
 #include "GUI_API_VariableDescriptors.h"  //"Modules/Common/GUI_API/GUI_API_VariableDescriptors.h"
#undef PREFIX
};


//select startup state for faster testing during development:
#define DEFAULT_MACHINESTATE MACHINE_STATE__BOOT
//#define DEFAULT_MACHINESTATE MACHINE_STATE__INITIAL_SETUP
//#define DEFAULT_MACHINESTATE MACHINE_STATE__INITIALIZED

//select startup screen for faster testing during development: - if given, disables/overrides state-machine
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__StartupSplash
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Initial_Setup
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Select_Option
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Generic_Password
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Home
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Pump_Settings
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Advanced_Settings
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Maintenance
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Communications
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Self_Test
//#define DEFAULT_STARTSCREEN GUI_SCREEN_ID__Firmware_Update



enum MachineStates {
    MACHINE_STATE__BOOT,
    MACHINE_STATE__STARTED,
    MACHINE_STATE__INITIAL_SETUP,
    MACHINE_STATE__INITIALIZED,
    MACHINE_STATE__DUMMY
};

enum MacineProcessFrames { //time that some states take (simulation of background processes to wait for)
    MACHINE_PROCESSFRAMES__BOOT = 1800 /GUI_REFRESH_PERIOD, //ms
};


const int CORE_A55__GUI_REFRESH_PERIOD = (GUI_REFRESH_PERIOD); //ms

char MachineState = DEFAULT_MACHINESTATE;
int MachineProcessFrameCounter = 0;



static void stateMachine ();



void CoreA55_testEventFunction__Next () { printf( "CoreA55 Event received from GUI: Initial Setup 'Next' button was pressed.\n" ); }
void CoreA55_testEventFunction__Options_Set () { printf( "CoreA55 Event received from GUI: Select Options 'OK' button was pressed.\n" ); }
void CoreA55_testEventFunction__RemotePassword_Set () { printf( "CoreA55 Event received from GUI: Remote-password was modified to \'%s\'.\n", RemotePassword ); }
void CoreA55_testEventFunction__Purge () { printf( "CoreA55 Event received from GUI: Pump Control 'Purge' button was pressed.\n" ); }
//void CoreA55_testEventFunction__StartStop () { printf( "CoreA55 Event received from GUI: Pump Control 'Start/Stop' button was pressed.\n" ); }
void CoreA55_testEventFunction__ResetDefaults () { printf( "CoreA55 Event received from GUI: Advanced Setup 'Reset Defaults' button was pressed.\n" ); }
void CoreA55_testEventFunction__Rinse () { printf( "CoreA55 Event received from GUI: Maintenance 'Rinse' button was pressed.\n" ); }
void CoreA55_testEventFunction__Reset () { printf( "CoreA55 Event received from GUI: Maintenance 'Reset' button was pressed.\n" ); }
void CoreA55_testEventFunction__ZeroPressTransducer () { printf( "CoreA55 Event received from GUI: Maintenance 'Zero Pressure Transducer' button was pressed.\n" ); }
void CoreA55_testEventFunction__SensorHome () { printf( "CoreA55 Event received from GUI: Maintenance 'Sensor Home' button was pressed.\n" ); }
void CoreA55_testEventFunction__WiFi_Connect () { printf( "CoreA55 Event received from GUI: WiFi 'Connect' button was pressed.\n" ); }
void CoreA55_testEventFunction__WiFi_Disconnect () { printf( "CoreA55 Event received from GUI: WiFi 'Forget Connection' button was pressed.\n" ); }
void CoreA55_testEventFunction__UpdateFromWeb () { printf( "CoreA55 Event received from GUI: Firmware Update 'Update from Web' button was pressed.\n" ); }
void CoreA55_testEventFunction__UpdateFromFlashDrive () { printf( "CoreA55 Event received from GUI: Firmware Update 'Update from flash-drive' button was pressed.\n" ); }
void CoreA55_testEventFunction__RunSelfTest () { printf( "CoreA55 Event received from GUI: Self-test 'Run Self-test' button was pressed.\n" ); }
void CoreA55_testEventFunction__SaveTestLogToFlashDrive () { printf( "CoreA55 Event received from GUI: Self-test 'Save to flash-drive' button was pressed.\n" ); }



static void initVariables () {
    //GUI_Version = GUI_VERSION;  //specification says it comes from the backend (see in VariableDescriptors array)
    Serial_Number = 12345;
    //strcpy( (char*) FactoryPassword, "fct" ); strcpy( (char*) UserPassword, "usr" ); strcpy( (char*) RemotePassword, "rmt" ); //to be on M33 it needs array-messaging finalized
    //strcpy( (char*) Message_Center, "Dummy Status Message: Ensure a valid string here (terminated by 0)" );
}


static inline void CoreA55_bindEventFunction ( int event_id, void (*callback_function)() ) {
    CoreMessaging_bindEventFunction( event_id, callback_function, COREMESSAGING_ENDPOINT__CORE_A55 );
}

static void initEvents () {
    CoreMessaging_bindEventFunction( GUI_TO_BACKEND_EVENT__Next_button, CoreA55_testEventFunction__Next, COREMESSAGING_ENDPOINT__CORE_A55 );
    CoreMessaging_bindEventFunction( GUI_TO_BACKEND_EVENT__Select_Options_Ok_button, CoreA55_testEventFunction__Options_Set, COREMESSAGING_ENDPOINT__CORE_A55 );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Generic_Password__Ok_button, CoreA55_testEventFunction__RemotePassword_Set );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Purge_button, CoreA55_testEventFunction__Purge );
    //CoreMessaging_bindEventFunction( GUI_TO_BACKEND_EVENT__StartStop_button, CoreA55_testEventFunction__StartStop, COREMESSAGING_ENDPOINT__CORE_A55 );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__FactoryReset, CoreA55_testEventFunction__ResetDefaults );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Rinse_button, CoreA55_testEventFunction__Rinse );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Reset_button, CoreA55_testEventFunction__Reset );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Zero_Press_Transducer_button, CoreA55_testEventFunction__ZeroPressTransducer );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Sensor_Home_Button, CoreA55_testEventFunction__SensorHome );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__WiFi_Connect, CoreA55_testEventFunction__WiFi_Connect );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__WiFi_ForgetConnection, CoreA55_testEventFunction__WiFi_Disconnect );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Update_on_the_web_Button, CoreA55_testEventFunction__UpdateFromWeb );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Update_from_flash_drive_button, CoreA55_testEventFunction__UpdateFromFlashDrive );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Run_Self_Test_button, CoreA55_testEventFunction__RunSelfTest );
    CoreA55_bindEventFunction( GUI_TO_BACKEND_EVENT__Save_To_Flash_drive_button, CoreA55_testEventFunction__SaveTestLogToFlashDrive );
    //... not all bingings are necessarily created in this example but can be added in the final product by using this binding function in the core where it should be run
}


void CoreA55_CoreMessaging_init () {
    CoreMessaging_init( GUI_API_VariableDescriptors, COREMESSAGING_ENDPOINT__CORE_A55 );  //CoreA55_CoreMessaging_init();

    initVariables();
    initEvents();
}

void CoreA55_GUI_init (int input_id, int framebuffer_id) {
    GUI_init( input_id, framebuffer_id );

    #ifdef DEFAULT_STARTSCREEN
     GUI_loadScreen( DEFAULT_STARTSCREEN );
    #endif
}

void CoreA55_init (int input_id, int framebuffer_id) {
    CoreA55_CoreMessaging_init();
    CoreA55_GUI_init( input_id, framebuffer_id );
}


void CoreA55_CoreMessaging_refresh () {
    CoreMessaging_refresh( GUI_API_VariableDescriptors, COREMESSAGING_ENDPOINT__CORE_A55, COREMESSAGING_ENDPOINT__CORE_M33 );  //CoreA55_CoreMessaging_refresh();  //CoreMessaging_sendValue( GUI_Version, GUI_API_VARIABLE_ID__GUI_Version );
    //printf( "CoreA55_CoreMessaging: GUI_Version: %d, Firmware_Version: %d\n", GUI_Version, Firmware_Version );
}

void CoreA55_GUI_refresh () {
    GUI_refresh();
    stateMachine(); //moved here now for advancing forward from splash-screen
}

void CoreA55_refresh () {
    CoreA55_CoreMessaging_refresh();
    CoreA55_GUI_refresh();
    //stateMachine();
}


static void stateMachine () { //TestBench state machine

   #ifndef DEFAULT_STARTSCREEN  //if tested screen deviates from the screen dictated by machine state, it's better to avoid state-handling (or otherwise, states should be initialized, not screens)
    switch (MachineState) {
        case MACHINE_STATE__BOOT:
            ++MachineProcessFrameCounter;
            if (MachineProcessFrameCounter > MACHINE_PROCESSFRAMES__BOOT) {
                MachineProcessFrameCounter=0; MachineState = MACHINE_STATE__STARTED;
            }
            break;
        case MACHINE_STATE__STARTED:
            MachineState = Factory_Initialization_Done? MACHINE_STATE__INITIALIZED : MACHINE_STATE__INITIAL_SETUP;
            break;
        case MACHINE_STATE__INITIAL_SETUP:
            GUI_loadScreenWithFade( GUI_SCREEN_ID__Initial_Setup, 200 ); //GUI_loadScreen( GUI_SCREEN_ID__Initial_Setup );
            MachineState = MACHINE_STATE__DUMMY;
            break;
        case MACHINE_STATE__INITIALIZED:
            GUI_loadScreenWithFade( GUI_SCREEN_ID__Home, 200 );
            MachineState = MACHINE_STATE__DUMMY;
            break;
        case MACHINE_STATE__DUMMY: break; //placeholder for other state, other states pointing to this can be transitioned from one-shot screen-switching
    }
   #endif

    //Continuously changing (e.g. measured) variable values and pointed text (e.g. status message) to display synchronously/cyclically on screen
    //if ( (GUI_Version += 1) >= 9999 )  GUI_Version = 0100;  //++GUI_Version; //printf( "CoreA55: GUI_Version:%d, Firmware_Version:%d\n", GUI_Version, Firmware_Version );
    //if ( (Firmware_Version += 1) >= 9999 )  Firmware_Version = 0100;
    //if ( (Serial_Number += 1) >= 9999/*99*/ )  Serial_Number = 0;
    //if ( (Model_Number += 1) >= 99999 )  Model_Number = 0;
    //printf("%d\n",StrokeLengths.StrokeLength_Pump1); //if ( (StrokeLengths.StrokeLength_Pump1 += 1) >= 4 )  StrokeLengths.StrokeLength_Pump1 = 0;
    //if ( (StrokeLengths.StrokeLength_Pump2 += 1) >= 4 )  StrokeLengths.StrokeLength_Pump2 = 0;
    //if ( (StrokeLengths.StrokeLength_Pump3 += 1) >= 4 )  StrokeLengths.StrokeLength_Pump3 = 0;
    //if ( (Pump_Rate1 += 1) >= 100.00 )  Pump_Rate1 = 0.002;
    //if ( (Pump_Rate2 += 1) >= 100.00 )  Pump_Rate2 = 0.002;
    //if ( (Pump_Rate3 += 1) >= 100.00 )  Pump_Rate3 = 0.002;
    //if ( (Pressure1 += 1) >= 7500 )  Pressure1 = 0;
    //if ( (Pressure2 += 1) >= 7500 )  Pressure2 = 0;
    //if ( (Pressure3 += 1) >= 7500 )  Pressure3 = 0;
    //if ( (CORE_M33__NAMESPACE_ Pressure_Target += 1) >= 7500 )  CORE_M33__NAMESPACE_ Pressure_Target = 0;
    //if ( (Flow_total_1 += 1.324) >= 2000.0 )  Flow_total_1 = 0;
    //if ( (CORE_M33__NAMESPACE_ Flow_total_2 += 3.324) >= 2000.0 )  CORE_M33__NAMESPACE_ Flow_total_2 = 0;
    //if ( (CORE_M33__NAMESPACE_ Flow_total_3 += 5.324) >= 2000.0 )  CORE_M33__NAMESPACE_ Flow_total_3 = 0;
    //if ( (CORE_M33__NAMESPACE_ Run_time_1 += 1) >= 50000 )  CORE_M33__NAMESPACE_ Run_time_1 = 0;
    //if ( (CORE_M33__NAMESPACE_ Run_time_2 += 1) >= 50000 )  CORE_M33__NAMESPACE_ Run_time_2 = 0;
    //if ( (CORE_M33__NAMESPACE_ Run_time_3 += 1) >= 50000 )  CORE_M33__NAMESPACE_ Run_time_3 = 0;
    //if ( (Pressure_Graph [30][2] += 1) >= 7500 )  Pressure_Graph [30][2] = 0;
    //if ( (Pressure_Alarm_Upper += 1) >= 7500 )  Pressure_Alarm_Upper = 0;
    //if ( (Pressure_Alarm_Lower += 1) >= 7500 )  Pressure_Alarm_Lower = 0;
    //if ( (FirmwareUpdate_Progress_Bar += 1) >= 1000 )  FirmwareUpdate_Progress_Bar = 0;
    //if ( (Pump1_Check_Valve_Hours += 1) >= 9999 )  Pump1_Check_Valve_Hours = 0;
    //if ( (Pump2_Check_Valve_Hours += 1) >= 9999 )  Pump2_Check_Valve_Hours = 0;
    //if ( (Pump3_Check_Valve_Hours += 1) >= 9999 )  Pump3_Check_Valve_Hours = 0;
    //if ( (Pump1_Total_Hours_Run += 1) >= 100000 )  Pump1_Total_Hours_Run = 0;
    //if ( (Pump2_Total_Hours_Run += 1) >= 100000 )  Pump2_Total_Hours_Run = 0;
    //if ( (Pump3_Total_Hours_Run += 1) >= 100000 )  Pump3_Total_Hours_Run = 0;
    //if ( (Pump1_Total_Seal_Hours += 1) >= 9999 )  Pump1_Total_Seal_Hours = 0;
    //if ( (Pump2_Total_Seal_Hours += 1) >= 9999 )  Pump2_Total_Seal_Hours = 0;
    //if ( (Pump3_Total_Seal_Hours += 1) >= 9999 )  Pump3_Total_Seal_Hours = 0;
    //if ( (Pump1_Check_Valve_Alarm += 1) >= 9999 )  Pump1_Check_Valve_Alarm = 0;
    //if ( (Pump2_Check_Valve_Alarm += 1) >= 9999 )  Pump2_Check_Valve_Alarm = 0;
    //if ( (Pump3_Check_Valve_Alarm += 1) >= 9999 )  Pump3_Check_Valve_Alarm = 0;
    //if ( (Pump1_Total_Seal_Alarm += 1) >= 9999 )  Pump1_Total_Seal_Alarm = 0;
    //if ( (Pump2_Total_Seal_Alarm += 1) >= 9999 )  Pump2_Total_Seal_Alarm = 0;
    //if ( (Pump3_Total_Seal_Alarm += 1) >= 9999 )  Pump3_Total_Seal_Alarm = 0;
    //if ( (Data_Frequency += 1) >= 999 )  Data_Frequency = 0;
    //if ( (RS_485_ID += 1) >= 255 )  RS_485_ID = 0;
    //if ( (SelfTest_ProgressBar += 1) >= 100 )  SelfTest_ProgressBar = 0;
    //if ( (Compressibility_1 += 1) >= 100 )  Compressibility_1 = 10;
    //if ( (Compressibility_2 += 1) >= 100 )  Compressibility_2 = 20;
    //if ( (Compressibility_3 += 1) >= 100 )  Compressibility_3 = 30;

    //Example of continuously changing value/state refreshed cyclically from GUI variables
    //printf( "%d\n", ChangingState );
}

