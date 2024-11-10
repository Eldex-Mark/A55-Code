// A binding between application and GUI so that if any variable/function-name changes in backend it has to be modified only here at a single place (optional but useful feature))

#include "GUI_unified.h"



#define BACKEND_NAMESPACE_ //IO.
#define BACKEND_POINTER_ &BACKEND_NAMESPACE_

#define GUI_NAMESPACE_ _GUI.
#define GUI_POINTER_ &GUI_NAMESPACE_



//Binding of Aliases (pointers) for variables
struct IOpointers IOp = {
 //Set/selected (and displayed) by GUI:

  //General variables (for all/most screens):
    .Factory_Initialization_Done = BACKEND_POINTER_ Factory_Initialization_Done,
    .NumberOfPumps = BACKEND_POINTER_ NumberOfPumps,
    .FactoryPassword = BACKEND_NAMESPACE_ FactoryPassword,
    .UserPassword = BACKEND_NAMESPACE_ UserPassword,
    .RemoteControlPassword = BACKEND_NAMESPACE_ RemotePassword,
    //struct Connections_p_t
    .ConnectionStates = BACKEND_POINTER_ Connections,
    //struct RemoteControls_p_t
    .RemoteControlRights = BACKEND_POINTER_ RemoteControls,

  //Splash-screen:
    .GUI_Version = BACKEND_POINTER_ GUI_Version,
    .Firmware_Version = BACKEND_POINTER_ Firmware_Version,

  //Initial Set-Up (Factory Menu) screen:
    .Serial_Number = BACKEND_POINTER_ Serial_Number,
    .Model_Number = BACKEND_POINTER_ Model_Number,
    //struct StrokeLengths_p_t
    .PumpStrokeLengths = BACKEND_POINTER_ StrokeLengths,
    //struct PistonSizes_p_t
    .PumpPistonSizes = BACKEND_POINTER_ PistonSizes,
    //struct WettedParts_p_t
    .PumpWettedParts = BACKEND_POINTER_ WettedParts,

  //Select Options (Purchase Settings) screen:
    //struct Options_p_t
    .OptionalEquipment = BACKEND_POINTER_ Options,

  //Home 1/2/3-Pump (Pump Control/PumpHomePage) screen:
    //struct PumpModes_p_t
    .PumpModes = BACKEND_POINTER_ PumpModes,
    .FlowRate_Pump1 = BACKEND_POINTER_ Flow_Rate1,
    .FlowRate_Pump2 = BACKEND_POINTER_ Flow_Rate2,
    .FlowRate_Pump3 = BACKEND_POINTER_ Flow_Rate3,
    .Pressure_Pump1 = BACKEND_POINTER_ Pressure,
    .Pressure_Target = BACKEND_POINTER_ Pressure_Target,
    .FlowAmount_Pump1 = BACKEND_POINTER_ Flow_total_1,
    .FlowAmount_Pump2 = BACKEND_POINTER_ Flow_total_2,
    .FlowAmount_Pump3 = BACKEND_POINTER_ Flow_total_3,
    .RunTime_Pump1 = BACKEND_POINTER_ Run_time_1,
    .RunTime_Pump2 = BACKEND_POINTER_ Run_time_2,
    .RunTime_Pump3 = BACKEND_POINTER_ Run_time_3,
    .PressureTransducer_Present = BACKEND_POINTER_ Pressure_transducer,
    .DispenseAmount_Pump1 = BACKEND_POINTER_ Dispense_Amount_1,
    .DispenseAmount_Pump2 = BACKEND_POINTER_ Dispense_Amount_2,
    .DispenseAmount_Pump3 = BACKEND_POINTER_ Dispense_Amount_3,
    .DispenseDuration_Pump1 = BACKEND_POINTER_ Dispense_Duration_1,
    .DispenseDuration_Pump2 = BACKEND_POINTER_ Dispense_Duration_2,
    .DispenseDuration_Pump3 = BACKEND_POINTER_ Dispense_Duration_3,
    //struct Repeat_p_t
    .PumpRepeatEnabled = BACKEND_POINTER_ Repeat,
    .RepeatDelay_Pump1 = BACKEND_POINTER_ Delay_1,
    .RepeatDelay_Pump2 = BACKEND_POINTER_ Delay_2,
    .RepeatDelay_Pump3 = BACKEND_POINTER_ Delay_3,
    .RepeatAmount_Pump1 = BACKEND_POINTER_ Occurrences_1,
    .RepeatAmount_Pump2 = BACKEND_POINTER_ Occurrences_2,
    .RepeatAmount_Pump3 = BACKEND_POINTER_ Occurrences_3,
    .FooterText = BACKEND_NAMESPACE_ Message_Center,

  //Pump Settings screen:
    //struct DispenseModes_p_t
    .PumpDispenseModes = BACKEND_POINTER_ DispenseModes,
    //struct SynchronizationModes_p_t
    .PumpSynchronizationModes = BACKEND_POINTER_ SynchronizationModes,
    //struct PumpOutputRatios_p_t
    .PumpRefillOutputRatios = BACKEND_POINTER_ PumpOutputRatios,
    //struct ErrDelays_p_t
    .PumpErrorStopDelays = BACKEND_POINTER_ ErrDelays,
    //struct VoltageOutputs_p_t
    .PumpVoltageOutputTypes = BACKEND_POINTER_ VoltageOutputs,
    .FluidCompressibility_Pump1 = BACKEND_POINTER_ Compressibility_1,
    .FluidCompressibility_Pump2 = BACKEND_POINTER_ Compressibility_2,
    .FluidCompressibility_Pump3 = BACKEND_POINTER_ Compressibility_3,
    //struct StopRestart_bits_p_t
    .StopRestartConfig = BACKEND_POINTER_ StopRestart_bits,

  //Advanced Setup screen (leads to other setup-screens):
    //struct AdvancedSetup_bits_p_t
    .AdvancedSetup_bits = BACKEND_POINTER_ AdvancedSetup_bits,
    .PressureAlarm_UpperThreshold = BACKEND_POINTER_ Pressure_Alarm_Max,
    .PressureAlarm_LowerThreshold = BACKEND_POINTER_ Pressure_Alarm_Min,
    //struct DateTime_p_t
    .DateAndTime = { .Year = BACKEND_POINTER_ DateTime.Year, .Month = BACKEND_POINTER_ DateTime.Month, .Day = BACKEND_POINTER_ DateTime.Day, .Hour = BACKEND_POINTER_ DateTime.Hour, .Minute = BACKEND_POINTER_ DateTime.Minute }, //.DateAndTime = BACKEND_POINTER_ DateTime,

  //Maintenance (Advanced Setup 2) screen:
    .TotalRunHours_Pump1 = BACKEND_POINTER_ Pump_1_Total_Run,
    //.TotalRunHours_Pump2 = BACKEND_POINTER_ Pump_2_Total_Run,
    //.TotalRunHours_Pump3 = BACKEND_POINTER_ Pump_3_Total_Run,
    .TotalRunHours__Pump1_PistonSeal = BACKEND_POINTER_ Pump1_Seal_RunTime,
    .TotalRunHours__Pump2_PistonSeal = BACKEND_POINTER_ Pump2_Seal_RunTime,
    .TotalRunHours__Pump3_PistonSeal = BACKEND_POINTER_ Pump3_Seal_RunTime,
    .AlarmLifetime__Pump1_PistonSeal = BACKEND_POINTER_ Pump1_Total_Seal_Alarm,
    .AlarmLifetime__Pump2_PistonSeal = BACKEND_POINTER_ Pump2_Total_Seal_Alarm,
    .AlarmLifetime__Pump3_PistonSeal = BACKEND_POINTER_ Pump3_Total_Seal_Alarm,
    .TotalRunHours__Pump1_CheckValve = BACKEND_POINTER_ Pump1_CheckValve_RunTime,
    .TotalRunHours__Pump2_CheckValve = BACKEND_POINTER_ Pump2_CheckValve_RunTime,
    .TotalRunHours__Pump3_CheckValve = BACKEND_POINTER_ Pump3_CheckValve_RunTime,
    .AlarmLifetime__Pump1_CheckValve = BACKEND_POINTER_ Pump1_Check_Valve_Alarm,
    .AlarmLifetime__Pump2_CheckValve = BACKEND_POINTER_ Pump2_Check_Valve_Alarm,
    .AlarmLifetime__Pump3_CheckValve = BACKEND_POINTER_ Pump3_Check_Valve_Alarm,
    .Washport_AutoStartStop = BACKEND_POINTER_ Washport_Auto,

  //Communications (Advanced Setup 4) screen:
    //struct AdvancedSetup4_bits_p_t
    .SerialPortSelections = BACKEND_POINTER_ AdvancedSetup4_bits,
    .SerialPort_DeviceID = BACKEND_POINTER_ Device_ID,
    .SerialPort_BaudRate = BACKEND_POINTER_ Baud_Rate,
    //struct SerialSettings_p_t
    .SerialPortBitSettings = BACKEND_POINTER_ SerialSettings,
    //struct RemoteContacts_p_t
    .StartStop_RemoteContacts_Required = BACKEND_POINTER_ RemoteContacts,
    //struct AnalogOutputs_p_t
    .PumpAnalogOutputTypes = BACKEND_POINTER_ AnalogOutputs,
    .Ethernet_IPaddress = BACKEND_NAMESPACE_ Address,
    .Ethernet_SubnetMask = BACKEND_NAMESPACE_ Mask,
    .Ethernet_GateWayIP = BACKEND_NAMESPACE_ GateWay,
    .Ethernet_DNSaddress = BACKEND_NAMESPACE_ DNS,
    .Ethernet_RemoteConnection = BACKEND_POINTER_ Remote_Connection,
    //struct EthernetSettings_p_t
    .EthernetSettings = BACKEND_POINTER_ EthernetSettings,
    .WiFi_SSID = BACKEND_NAMESPACE_ SSID,
    .WiFi_Password = BACKEND_NAMESPACE_ Password,
    //struct WiFiConnectionDetails_p_t
    .WiFiConnectionDetails = BACKEND_POINTER_ WiFiConnectionDetails,
    .WiFiConnectionList = BACKEND_NAMESPACE_ Networks,
    .WiFiConnectionList_NetworkDetails = BACKEND_NAMESPACE_ Network_Details,
    //struct WiFiSettings_p_t
    .WiFiSettings = BACKEND_POINTER_ WiFiSettings,

  //Self Test (Advanced Setup 5) screen:
    .SelfTest_ConsoleLog = BACKEND_NAMESPACE_ TextBuffer,
    .SelfTest_Progress_Percentage = BACKEND_POINTER_ SelfTest_ProgressBar,

  //Firmware Update (Advanced Setup 1) screen:
    .FirmwareUpdate_ProgressPercentage = BACKEND_POINTER_ FirmwareUpdate_Progress_Bar,

  /* //Data Recorder (Advanced Setup 3) screen:
    //struct AdvancedSetup3_bits_p_t
    .AdvancedSetup3_bits = BACKEND_POINTER_ AdvancedSetup3_bits,
    .DataRecord_FileName [128] = BACKEND_POINTER_ File_Name,
    .DataRecord_DataFrequency = BACKEND_POINTER_ Data_Frequency,*/

  /* //Home 1 Pump Graph (Chart) screen:
    .Max_Flow = BACKEND_POINTER_ Max_Flow,
    .Max_Pressure = BACKEND_POINTER_ Max_Pressure,
    .FlowRate_Graph [30][2] = BACKEND_POINTER_ Flow_Rate_Graph,
    .Pressure_Graph [30][2] = BACKEND_POINTER_ Pressure_Graph [30][2],*/


    //Simply change the linkages here to only one of the pump-selector variables to follow the same selection on all screens wherever it changes
    .SelectedPump__Initial_Setup        = GUI_POINTER_ SelectedPump__Home, //SelectedPump__Initial_Setup,
    .SelectedPump__Home                 = GUI_POINTER_ SelectedPump__Home,
    .SelectedPump__Pump_Settings        = GUI_POINTER_ SelectedPump__Home, //SelectedPump__Pump_Settings,
    .SelectedPump__Maintenance          = GUI_POINTER_ SelectedPump__Home, //SelectedPump__Maintenance,
    .SelectedPump__Communication_Serial = GUI_POINTER_ SelectedPump__Home //SelectedPump__Communication_Serial
};


#undef BACKEND_POINTER_
#undef BACKEND_NAMESPACE_


//Application-to-GUI function-call bindings/wrappers (1st name can be renamed if changed in Application):
__attribute__((always_inline)) inline  void GUI_loadScreen (GUI_ScreenIDs screen_id) { _GUI_loadScreenByID( screen_id ); }
__attribute__((always_inline)) inline  void GUI_loadScreenWithFade (GUI_ScreenIDs screen_id, int duration) { _GUI_loadScreenByIDwithFade( screen_id, duration ); }

//__attribute__((always_inline)) inline  void GUI_loadScreen (GUI_ScreenIDs screen_id) { _GUI_loadScreenByID( screen_id ); }


//GUI-to-Application function-call bindings (2nd name can be renamed if changed in Application):

//__attribute__((always_inline)) inline  void _App_WiFi_subscribeToEvents (CallbackWifiEvent callback_function)  { WIFI_API_SubscribeToEvents( callback_function); }
