//Pointers used by the Application-to/from-GUI binding (optional but useful feature)

//Should have the same layout as App_bindings.c for easier comparison


//Binding of Aliases (pointers) for variables
struct IOpointers {
 //Set/selected (and displayed) by GUI:

  //General variables (for all/most screens):
    uint8_t *const Factory_Initialization_Done;
    uint8_t *const NumberOfPumps;
    uint8_t *const FactoryPassword; //[16];
    uint8_t *const UserPassword; //[16];
    uint8_t *const RemoteControlPassword; //[16];
    //struct Connections_p_t { uint8_t *const USB_Inserted : 1; uint8_t *const Ethernet_Active : 1; uint8_t *const Wifi_On : 1; } Connections_p_t;
    struct  Connections_t *const ConnectionStates;
    //struct RemoteControls_p_t { uint8_t *const Serial_RemoteControl : 1; uint8_t *const Ethernet_RemoteControl : 1; uint8_t *const Wifi_RemoteControl : 1; } RemoteControls_p_t;
    struct  RemoteControls_t *const RemoteControlRights;

  //Splash-screen:
    uint16_t *const GUI_Version;
    uint16_t *const Firmware_Version;

  //Initial Set-Up (Factory Menu) screen:
    uint16_t *const Serial_Number;
    uint8_t *const Model_Number;
    //struct StrokeLengths_p_t { uint8_t *const StrokeLength_Pump1 : 2; uint8_t *const StrokeLength_Pump2 : 2; uint8_t *const StrokeLength_Pump3 : 2; } StrokeLengths_p_t;
    struct  StrokeLengths_t *const PumpStrokeLengths;
    //struct PistonSizes_p_t { uint8_t *const PistonSize_Pump1 : 2; uint8_t *const PistonSize_Pump2 : 2; uint8_t *const PistonSize_Pump3 : 2; } PistonSizes_p_t;
    struct  PistonSizes_t *const PumpPistonSizes;
    //struct WettedParts_p_t { uint8_t *const WettedPart_Pump1 : 2; uint8_t *const WettedPart_Pump2 : 2; uint8_t *const WettedPart_Pump3 : 2; } WettedParts_p_t;
    struct  WettedParts_t *const PumpWettedParts;

  //Select Options (Purchase Settings) screen:
    //struct Options_p_t { uint8_t *const Pressure_Transducer : 1; uint8_t *const WashPort_Pump : 1; LeakDetector_Sensor : 1; Flow_Sensor : 1; Encoder : 1; } Options_p_t;
    struct  Options_t *OptionalEquipment;

  //Home 1/2/3-Pump (Pump Control/PumpHomePage) screen:
    //struct PumpModes_p_t { uint8_t *const Pump_1_mode : 2; uint8_t *const Pump_2_mode : 2; uint8_t *const Pump_3_mode : 2; } PumpModes_p_t;
    struct  PumpModes_t *const PumpModes;
    float *const FlowRate_Pump1;
    float *const FlowRate_Pump2;
    float *const FlowRate_Pump3;
    uint16_t *const Pressure_Pump1;
    uint16_t *const Pressure_Target;
    float *const FlowAmount_Pump1;
    float *const FlowAmount_Pump2;
    float *const FlowAmount_Pump3;
    uint16_t *const RunTime_Pump1;
    uint16_t *const RunTime_Pump2;
    uint16_t *const RunTime_Pump3;
    uint8_t *const PressureTransducer_Present;
    float *const DispenseAmount_Pump1;
    float *const DispenseAmount_Pump2;
    float *const DispenseAmount_Pump3;
    uint16_t *const DispenseDuration_Pump1;
    uint16_t *const DispenseDuration_Pump2;
    uint16_t *const DispenseDuration_Pump3;
    //struct Repeat_p_t { uint8_t *const Repeat_1 : 1; uint8_t *const Repeat_2 : 1; uint8_t *const Repeat_3 : 1; } Repeat_p_t;
    struct  Repeat_t *const PumpRepeatEnabled;
    uint16_t *const RepeatDelay_Pump1;
    uint16_t *const RepeatDelay_Pump2;
    uint16_t *const RepeatDelay_Pump3;
    uint16_t *const RepeatAmount_Pump1;
    uint16_t *const RepeatAmount_Pump2;
    uint16_t *const RepeatAmount_Pump3;
    uint8_t *const FooterText; //[128];

  //Pump Settings screen:
    //struct DispenseModes_p_t { uint8_t *const Dispense_Mode_Pump1 : 2; uint8_t *const Dispense_Mode_Pump2 : 2; uint8_t *const Dispense_Mode_Pump3 : 2; } DispenseModes_p_t;
    struct  DispenseModes_t *const PumpDispenseModes;
    //struct SynchronizationModes_p_t { uint8_t *const Synchronization_1 : 2; uint8_t *const Synchronization_2 : 2; uint8_t *const Synchronization_3 : 2; } SynchronizationModes_p_t;
    struct  SynchronizationModes_t *const PumpSynchronizationModes;
    //struct PumpOutputRatios_p_t { uint8_t *const Output_Ratio_Pump1 : 4; uint8_t *const Output_Ratio_Pump2 : 4; uint8_t *const : 0; uint8_t *const Output_Ratio_Pump3 : 4; } PumpOutputRatios_p_t;
    struct  PumpOutputRatios_t *const PumpRefillOutputRatios;
    //struct ErrDelays_p_t { uint8_t *const Err_Delay_1 : 4; uint8_t *const Err_Delay_2 : 4; uint8_t *const Err_Delay_3 : 4; } ErrDelays_p_t;
    struct  ErrDelays_t *const PumpErrorStopDelays;
    //struct VoltageOutputs_p_t { uint8_t *const Voltage_Output_1 : 2; uint8_t *const Voltage_Output_2 : 2; uint8_t *const Voltage_Output_3 : 2; } VoltageOutputs_p_t;
    struct  VoltageOutputs_t *const PumpVoltageOutputTypes;
    uint8_t *const FluidCompressibility_Pump1;
    uint8_t *const FluidCompressibility_Pump2;
    uint8_t *const FluidCompressibility_Pump3;
    //struct StopRestart_bits_p_t { uint8_t *const Stop_on_Stall : 1; uint8_t *const Restart_on_Power_Up : 1; } StopRestart_bits_p_t;
    struct  StopRestart_bits_t *const StopRestartConfig;

  //Advanced Setup screen (leads to other setup-screens):
    //struct AdvancedSetup_bits_p_t { uint8_t *const Temperature_unit_of_measure : 1; uint8_t *const Pressure_unit_of_measure : 1; uint8_t *const Pressure_limit_enabled : 1; } AdvancedSetup_bits_p_t;
    struct  AdvancedSetup_bits_t *const AdvancedSetup_bits;
    uint16_t *const PressureAlarm_UpperThreshold;
    uint16_t *const PressureAlarm_LowerThreshold;
    struct DateTime_p_t { uint16_t *const Year; uint8_t *const Month; uint8_t *const Day; uint8_t *const Hour; uint8_t *const Minute; } DateAndTime;

  //Firmware Update (Advanced Setup 1) screen:
    uint8_t *const FirmwareUpdate_ProgressPercentage;

  //Maintenance (Advanced Setup 2) screen:
    uint16_t *const TotalRunHours__Pump1_CheckValve;
    uint16_t *const TotalRunHours__Pump2_CheckValve;
    uint16_t *const TotalRunHours__Pump3_CheckValve;
    uint32_t *const TotalRunHours_Pump1;
    //uint32_t *const TotalRunHours_Pump2;
    //uint32_t *const TotalRunHours_Pump3;
    uint16_t *const TotalRunHours__Pump1_PistonSeal;
    uint16_t *const TotalRunHours__Pump2_PistonSeal;
    uint16_t *const TotalRunHours__Pump3_PistonSeal;
    uint16_t *const AlarmLifetime__Pump1_CheckValve;
    uint16_t *const AlarmLifetime__Pump2_CheckValve;
    uint16_t *const AlarmLifetime__Pump3_CheckValve;
    uint16_t *const AlarmLifetime__Pump1_PistonSeal;
    uint16_t *const AlarmLifetime__Pump2_PistonSeal;
    uint16_t *const AlarmLifetime__Pump3_PistonSeal;
    uint8_t *const Washport_AutoStartStop;

  //Communications (Advanced Setup 4) screen:
    //struct AdvancedSetup4_bits_p_t { uint8_t *const RS_485 : 1; uint8_t *const RS_232 : 1; } AdvancedSetup4_bits_p_t;
    struct  AdvancedSetup4_bits_t *const SerialPortSelections;
    uint8_t *const SerialPort_DeviceID;
    uint8_t *const SerialPort_BaudRate;
    //struct SerialSettings_p_t { uint8_t *const Data_Bit : 2; uint8_t *const Stop_Bit : 2; uint8_t *const Parity_Bit : 2; } SerialSettings_p_t;
    struct  SerialSettings_t *const SerialPortBitSettings;
    //struct RemoteContacts_p_t { uint8_t *const Remote_Contacts_1 : 1; } RemoteContacts_p_t;
    struct  RemoteContacts_t *const StartStop_RemoteContacts_Required;
    //struct AnalogOutputs_p_t { uint8_t *const Analog_Output_pump_1 : 2; uint8_t *const Analog_Output_pump_2 : 2; uint8_t *const Analog_Output_pump_3 : 2; } AnalogOutputs_p_t;
    struct  AnalogOutputs_t *const PumpAnalogOutputTypes;
    uint8_t *const Ethernet_IPaddress; //[4];
    uint8_t *const Ethernet_SubnetMask; //[4];
    uint8_t *const Ethernet_GateWayIP; //[4];
    uint8_t *const Ethernet_DNSaddress; //[4];
    uint8_t *const Ethernet_RemoteConnection;
    //struct EthernetSettings_p_t { uin8_t DHCP : 1; } EthernetSettings_p_t;
    struct  EthernetSettings_t *const EthernetSettings;
    uint8_t *const WiFi_SSID; //[32];
    uint8_t *const WiFi_Password; //[32];
    //struct WiFiConnectionDetails_p_t { uint8_t *const Security_Type : 2; } WiFiConnectionDetails_p_t;
    struct  WiFiConnectionDetails_t *const WiFiConnectionDetails;
    uint8_t (*const WiFiConnectionList) [32];
    struct WiFiConnectionDetails_t *const WiFiConnectionList_NetworkDetails; //[50];
    //struct WiFiSettings_p_t { uint8_t *const Automatic_connection : 1; uint8_t *const Remote_Connection : 1; } WiFiSettings_p_t;
    struct  WiFiSettings_t *const WiFiSettings;

  //Self Test (Advanced Setup 5) screen:
    uint8_t (*const SelfTest_ConsoleLog) [10];
    uint8_t *const SelfTest_Progress_Percentage;

  /* //Data Recorder (Advanced Setup 3) screen:
    struct AdvancedSetup3_bits_p_t { uint8_t *const Flow : 1; uint8_t *const Pressure : 1; uint8_t *const Run : 1; } AdvancedSetup3_bits_p_t;
    struct  AdvancedSetup3_bits_t *AdvancedSetup3_bits;
    uint8_t *const DataRecord_FileName; //[128];
    uint16_t *const DataRecord_DataFrequency;*/

  /* //Home 1 Pump Graph (Chart) screen:
    uint8_t *const Max_Flow;
    uint8_t *const Max_Pressure;
    uint16_t (*const FlowRate_Graph) [2];
    uint16_t (*const Pressure_Graph) [2];*/
};



//GUI-to-Application function-bindings:

//void _App_WiFi_subscribeToEvents (CallbackWifiEvent callback_function);


//BLE - Enumerations: written in a strange textual/numerical-index form in the API, so adding the custom symbols for the values here in the GUI to work that around

//enum { //status_enum:
//#define  _App_BLE_CONNECTIONSTATUS__CONNECTED  BLE_INSTALLER_STATUS_CONNECTED  // = GUI_BLE_CONNECTIONSTATUS__CONNECTED,   //[0] = "Connected"

//enum {
    //_APP_LANGUAGE_ID__ENGISH = LANG_ENGLISH,
//};
