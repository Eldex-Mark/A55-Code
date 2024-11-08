//Variable descriptor/registry array for the inter-core messaging (last parameter is used to initialize variables so they're synchronized and have the same values on both cores at startup)


//General variables (for all/most screens):
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Factory_Initialization_Done, 1, { 0 } },  //Not present in the specification, but it says: 'The backend will auto detect the number of the pumps', and 'The number of tabs is decided by autodetection of the number of pumps by the backend.'
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX NumberOfPumps,            1, { 0 } },  //Not present in the specification, but it says: 'The backend will auto detect the number of the pumps', and 'The number of tabs is decided by autodetection of the number of pumps by the backend.'

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX FactoryPassword,         16, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX UserPassword,            16, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX RemotePassword,          16, { 0 } },

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Connections,           1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Connections.USB_Inserted,          1, { 0 } },           //Bit0  Values:0,1  Event:Home
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Connections.Ethernet_Active,       1, { 0 } },           //Bit1  Values:0,1  Event:Pump-settings
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Connections.Wifi_On,               1, { 0 } },           //Bit2  Values:0,1  Event: Adv. Settings

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX RemoteControls,           1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX RemoteControls.Serial_RemoteControl,    1, { 0 } },  //Bit0
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX RemoteControls.Ethernet_RemoteControl,  1, { 0 } },  //Bit0
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX RemoteControls.Wifi_RemoteControl,      1, { 0 } },  //Bit0



//Splash-screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX GUI_Version,           1, { 100 *01+00 } },  //0..99.99 fixed point (scale 100x?)  //specification says it comes from the backend
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Firmware_Version,      1, { 100 *00+99 } },  //0..99.99 fixed point



//Initial Set-Up (Factory Menu) screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Serial_Number,         1, { 0 } },           //0-999999  //Event: Reset to Factory, Factory Burn In
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Model_Number,          1, { 0 } },           //0-99999  //Event: Reset to Factory, Factory Burn In

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX PistonSizes,           1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX PistonSizes.PistonSize_Pump1,      1, { 0 } },           //bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX PistonSizes.PistonSize_Pump2,      1, { 0 } },           //bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX PistonSizes.PistonSize_Pump3,      1, { 0 } },           //bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX StrokeLengths,         1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX StrokeLengths.StrokeLength_Pump1,  1, { 0 } },           //bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX StrokeLengths.StrokeLength_Pump2,  1, { 0 } },           //bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX StrokeLengths.StrokeLength_Pump3,  1, { 0 } },           //bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX WettedParts,           1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX WettedParts.WettedPart_Pump1,      1, { 0 } },           //bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX WettedParts.WettedPart_Pump2,      1, { 0 } },           //bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX WettedParts.WettedPart_Pump3,      1, { 0 } },           //bits[4:5]



//Select Options screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Options,               1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.Pressure_Transducer,         1, { 0 } },            //bit0
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.WashPort_Pump,               1, { 0 } },            //bit1
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.LeakDetector_Sensor,         1, { 0 } },            //bit2
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.Flow_Sensor,                 1, { 0 } },            //bit3
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.Encoder,                     1, { 0 } },            //bit4



//Home 1/2/3-Pump (Pump Control/PumpHomePage) screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX PumpModes,            1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX PumpModes.Pump_1_mode,  1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX PumpModes.Pump_2_mode,  1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX PumpModes.Pump_3_mode,  1, { 0 } },  //Bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Flow_Rate1/*Pump_Rate1*/,            1, { 0.0 } },         //0.002 to 100.00ml/min  Event: Purge Pump 1
{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Flow_Rate2/*Pump_Rate2*/,            1, { 0.0 } },         //0.002 to 100.00ml/min  Event: Purge Pump 2
{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Flow_Rate3/*Pump_Rate3*/,            1, { 0.0 } },         //0.002 to 100.00ml/min  Event: Purge Pump 3

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure/*1*/,             1, { 0 } },           //0 to 7500 psi  Events: Run/Stop Pump1, Up Pump1, Down Pump1
//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure2,             1, { 0 } },           //0 to 7500 psi  Events: Run/Stop Pump2, Up Pump2, Down Pump2
//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure3,             1, { 0 } },           //0 to 7500 psi  Events: Run/Stop Pump3, Up Pump3, Down Pump3

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure_Target,       1, { 0 } },           //0 to 7500 psi

{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Flow_total_1,          1, { 0 } },  //Pump total 1 ?
{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Flow_total_2,          1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Flow_total_3,          1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Run_time_1,            1, { 0 } },  //Run time 1
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Run_time_2,            1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Run_time_3,            1, { 0 } },

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Pressure_transducer,   1, { 0 } },

{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Dispense_Amount_1,     1, { 0.0 } },
{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Dispense_Amount_2,     1, { 0.0 } },
{ COREMESSAGING_VARIABLE_TYPE__FLOAT,  PREFIX Dispense_Amount_3,     1, { 0.0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Dispense_Duration_1,   1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Dispense_Duration_2,   1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Dispense_Duration_3,   1, { 0 } },

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Repeat,                1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.Repeat_1,         1, { 0 } },            //bit0
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.Repeat_2,         1, { 0 } },            //bit1
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Options.Repeat_3,         1, { 0 } },            //bit2

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Delay_1,               1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Delay_2,               1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Delay_3,               1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Occurrences_1,         1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Occurrences_2,         1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Occurrences_3,         1, { 0 } },

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Message_Center,      128, { 0 } },           //max 128 chars  Default:"The support link"



//Pump Settings screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX DispenseModes,            1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX DispenseModes.Dispense_Mode_Pump1,  1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX DispenseModes.Dispense_Mode_Pump2,  1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX DispenseModes.Dispense_Mode_Pump3,  1, { 0 } },  //Bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX SynchronizationModes,     1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX DispenseModes.Synchronization_1,    1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX DispenseModes.Synchronization_2,    1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX DispenseModes.Synchronization_3,    1, { 0 } },  //Bits[4:5]
//{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX MultiPumps,               1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX MultiPumps.Multi_Pump_1,  1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX MultiPumps.Multi_Pump_2,  1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX MultiPumps.Multi_Pump_3,  1, { 0 } },  //Bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX PumpOutputRatios,         1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT4,  PREFIX PumpOutputRatios Output_Ratio_Pump1,  1, { 0 } },  //Bits[0:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT4,  PREFIX PumpOutputRatios Output_Ratio_Pump2,  1, { 0 } },  //Bits[4:7]
//{ COREMESSAGING_VARIABLE_TYPE__UINT4,  PREFIX PumpOutputRatios Ourput_Ratio_Pump3,  1, { 0 } },  //Bits[0:3]

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX ErrDelays,                1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT4,  PREFIX ErrDelays.Err_Delay_1,  1, { 0 } },  //Bits[0:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT4,  PREFIX ErrDelays.Err_Delay_2,  1, { 0 } },  //Bits[4:7]
//{ COREMESSAGING_VARIABLE_TYPE__UINT4,  PREFIX ErrDelays.Err_Delay_3,  1, { 0 } },  //Bits[0:3]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX VoltageOutputs,           1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX VoltageOutputs.Voltage_Output_1,  1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX VoltageOutputs.Voltage_Output_2,  1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX VoltageOutputs.Voltage_Output_3,  1, { 0 } },  //Bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Compressibility_1,        1, { 0 } },        //10 to 100
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Compressibility_2,        1, { 0 } },        //20 to 100
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Compressibility_3,        1, { 0 } },        //30 to 100

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX StopRestart_bits,         1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX StopRestart_bits.Stop_on_Stall,        1, { 0 } },  //Bit0
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX StopRestart_bits.Restart_on_Power_Up,  1, { 0 } },  //Bit1



//Advanced Setup screen (leads to other setup-screens):
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX AdvancedSetup_bits,    1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup_bits.Temperature_unit_of_measure,  1, { 0 } },  //Bit0  Values:0,1 //Fahrenheit/Celsius?
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup_bits.Pressure_unit_of_measure,     1, { 0 } },  //Bit1  Values:0,1  //PSI/bar?
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup_bits.Pressure_limit_enabled,       1, { 0 } },  //Bit2  Values:0,1

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure_Alarm_Max/*Upper*/,  1, { 0 } },           //0 to 7500 psi
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure_Alarm_Min/*Lower*/,  1, { 0 } },           //0 to 7500 psi?

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX DateTime.Year,            1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX DateTime.Month,           1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX DateTime.Day,             1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX DateTime.Hour,            1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX DateTime.Minute,          1, { 0 } },



//Firmware Update (Advanced Setup 1) screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX FirmwareUpdate_Progress_Bar,  1, { 0 } },    //Value:0..1000  Events: Check for update, Update from Flash



//Maintenance (Advanced Setup 2) screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump1_CheckValve_RunTime/*Pump1_Check_Valve_Hours*/,  1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump2_CheckValve_RunTime/*Pump2_Check_Valve_Hours*/,  1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump3_CheckValve_RunTime/*Pump3_Check_Valve_Hours*/,  1, { 0 } },        //0 to 9,999

{ COREMESSAGING_VARIABLE_TYPE__UINT32, PREFIX Pump_1_Total_Run/*Pump1_Total_Hours_Run*/,    1, { 0 } },        //0 to 100,000 //Events: Reset Check Valve, Sensor Home
//{ COREMESSAGING_VARIABLE_TYPE__UINT32, PREFIX Pump2_Total_Hours_Run,    1, { 0 } },        //0 to 100,000
//{ COREMESSAGING_VARIABLE_TYPE__UINT32, PREFIX Pump3_Total_Hours_Run,    1, { 0 } },        //0 to 100,000

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump1_Seal_RunTime/*Pump1_Total_Seal_Hours*/,   1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump2_Seal_RunTime/*Pump2_Total_Seal_Hours*/,   1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump3_Seal_RunTime/*Pump3_Total_Seal_Hours*/,   1, { 0 } },        //0 to 9,999

//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX GUI_Version,  1, { 0 } }, //0-99.99 fixed point - is already present (Splash-screen)
//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Firmware_Version,  1, { 0 } }, //0-99.99 fixed point - is already present (Splash-screen)
//{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX ,  1, { 0 } }, Current_Pump? Total Hours? Total Cycles? - are they still present?

{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump1_Check_Valve_Alarm,  1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump2_Check_Valve_Alarm,  1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump3_Check_Valve_Alarm,  1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump1_Total_Seal_Alarm,   1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump2_Total_Seal_Alarm,   1, { 0 } },        //0 to 9,999
{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pump3_Total_Seal_Alarm,   1, { 0 } },        //0 to 9,999

{ COREMESSAGING_VARIABLE_TYPE__BOOL,  PREFIX Washport_Auto,             1, { 0 } },



//Communications (Advanced Setup 4) screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX AdvancedSetup4_bits,      1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup4_bits.RS_485,    1, { 0 } },  //Bit0  Values:0,1
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup4_bits.RS_232,    1, { 0 } },  //Bit1  Values:0,1
////{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup4_bits.Ethernet,  1, { 0 } },  //Bit2  Values:0,1
////{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup4_bits.DHCP,      1, { 0 } },  //Bit3  Values:0,1
////{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup4_bits.WiFi,      1, { 0 } },  //Bit4  Values:0,1

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Device_ID/*RS_485_ID*/,              1, { 0 } },        //0 to 255
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Baud_Rate,                           1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX SerialSettings,                      1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX SerialSettings.Data_Bit,         1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX SerialSettings.Stop_Bit,         1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX SerialSettings.Parity_Bit,       1, { 0 } },  //Bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX RemoteContacts,           1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX RemoteContacts.Remote_Contacts_1,  1, { 0 } },  //Bits[0:1]/Bit0? //Eldex: We only need 1 bit.
////{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX RemoteContacts.Remote_Contacts_2,  1, { 0 } },  //Bits[2:3]/Bit1? //Eldex: We only need 1 bit.
////{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX RemoteContacts.Remote_Contacts_3,  1, { 0 } },  //Bits[4:5]/Bit2? //Eldex: We only need 1 bit.

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX AnalogOutputs,       1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX AnalogOutputs.Analog_Output_pump_1,  1, { 0 } },  //Bits[0:1]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX AnalogOutputs.Analog_Output_pump_2,  1, { 0 } },  //Bits[2:3]
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX AnalogOutputs.Analog_Output_pump_3,  1, { 0 } },  //Bits[4:5]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Address,                  4, { 0 } },        //255.255.255.255
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Mask,                     4, { 0 } },        //255.255.255.255
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX GateWay,                  4, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX DNS,                      4, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX Remote_Connection,        1, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX EthernetSettings,         1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX EthernetSettings.DHCP,             1, { 0 } },  //Bit0

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX SSID,                    32, { 0 } },        //32 char
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Password,                32, { 0 } },        //32 char
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX WiFiConnectionDetails,    1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT2,  PREFIX WiFiConnectionDetails.Security_Type,  1, { 0 } },  //Bits[0:1]

{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Networks,             50*32, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Network_Details,         50, { 0 } },
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX WiFiSettings,             1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX WiFiSettings.Automatic_connection, 1, { 0 } },  //Bit0
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX WiFiSettings.Remote_Connection,    1, { 0 } },  //Bit1



//Self Test (Advanced Setup 5) screen:
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX TextBuffer,           10*45, { 0 } },        //10 lines of 45 char  Event: Start
{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX SelfTest_ProgressBar,     1, { 0 } },        //0 to 100



//Data Recorder (Advanced Setup 3) screen:
//{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX AdvancedSetup3_bits,      1, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup3_bits.Flow,      1, { 0 } },  //Bit0  Values:0,1
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup3_bits.Pressure,  1, { 0 } },  //Bit1  Values:0,1
//{ COREMESSAGING_VARIABLE_TYPE__BOOL,   PREFIX AdvancedSetup3_bits.Run,       1, { 0 } },  //Bit2  Values:0,1  //Start/Stop?

//{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX File_Name,              128, { 0 } },
//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Data_Frequency,           1, { 0 } },        //0 to 999 seconds  //data-period?



//Home 1 Pump Graph (Chart) screen:
//{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Max_Flow,              1, { 0 } },           //?
//{ COREMESSAGING_VARIABLE_TYPE__UINT8,  PREFIX Max_Pressure,          1, { 0 } },           //?
//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Flow_Rate_Graph,    32*2, { 0 } },           //? //3 of them needed?
//{ COREMESSAGING_VARIABLE_TYPE__UINT16, PREFIX Pressure_Graph,     32*2, { 0 } },           //0 to 7500 psi //3 of them needed?



{ COREMESSAGING_VARIABLE_TYPE__END, NULL, 0, {0} }



