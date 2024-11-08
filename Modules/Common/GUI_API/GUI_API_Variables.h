//API-Variables


//General variables (for all/most screens):
EXTERN uint8_t Factory_Initialization_Done;
EXTERN uint8_t NumberOfPumps; //Not present in the specification, but it says: 'The backend will auto detect the number of the pumps', and 'The number of tabs is decided by autodetection of the number of pumps by the backend.'

//General password Screen:
//This screen is used to change the Remote password and enter the Factory password. This screen can work in 2 modes: Password check / Password modification
EXTERN uint8_t FactoryPassword [16]; //known only by the factory?
EXTERN uint8_t UserPassword [16]; //given in the user-manual?
EXTERN uint8_t RemotePassword [16]; //RemotePIN //or is it the 'User' password? //default value: as defined in the user-manual In case of modification, save a new password, else check if the passwords match  //Password number input field: characters shown as ‘*’ characters.

EXTERN struct __attribute__((aligned(1))) Connections_t {
 uint8_t USB_Inserted : 1; //Bit0  Values:0,1  //Event:Home USB indicator: Glowing design when active. It needs to be checked only when the value must be changed.
 uint8_t Ethernet_Active : 1; //Bit1  Values:0,1  Event:Pump-settings //Ethernet indicator: Glowing design when active. It needs to be checked only when the value must be changed.
 uint8_t Wifi_On : 1; //Bit2  Values:0,1  Event: Adv. Settings //Wifi indicator: Glowing design when active. It needs to be checked only when the value must be changed.
} Connections;

//Optos pumps can be controlled remotely via an analog signal (either 4-20 mA or 0-5 VDC). If you wish to operate the Optos pump remotely using one of the available analog signals,
//you need to set the field to that signal (operating via RS232 does not require any setup).
EXTERN struct __attribute__((aligned(1))) RemoteControls_t { //Optos pumps can be controlled remotely via an analog signal (either 4-20 mA or 0-5 VDC).
uint8_t Serial_RemoteControl : 1;  //Bit0            //If you wish to operate the Optos pump remotely using one of the available analog signals, you need to set the field to that signal (operating via RS232 does not require any setup).
uint8_t Ethernet_RemoteControl : 1;  //Bit1
uint8_t Wifi_RemoteControl : 1; //Bit2
} RemoteControls;



//Splash-screen:
//This is the startup screen. It has no other functions.
//Logo: The file is in: „Optos Touch 20240723.zip\SQLI Data\SQLI Data\assets”. „We may want to consider
//changing this screen to the Eldex Splash.mp4 video I uploaded or something similar instead of this. I did not
//know how to do this in Squareline.”

EXTERN uint16_t GUI_Version; //0..99.99 fixed point (scale 100x?)  //comes from the backend
                             //Also shown on maintenance-screen: Firmware Version: Value: it comes from the backend. The version of the firmware.
EXTERN uint16_t Firmware_Version; //0..99.99 fixed point  //comes from the backend, appears on firmware update screen too (called 'Current Version' in the specification but I guess it's the same)
                             //Also shown on maintenance-screen: GUI Version: Value: hard coded in UI code (but at splash-srceen description of spec it's said to be coming from backend! spec. discrepancy)



//Initial Set-Up (Factory Menu) screen:
//This screen sets up basic pump and device settings. These settings will be set in the factory. This screen comes up
//the first time when powered up in the factory. In the future, the user needs to enter the User password (defined in
//the user manual) to reach this screen from the Advanced settings screen. The backend will auto detect the number
//of the pumps. To change the serial, model number, and Purchase setting the user needs to enter the secret Factory Password, which is only known by the factory.
//Pump Selector tabview: The number of tabs is decided by autodetection of the number of pumps by the backend.

EXTERN uint16_t Serial_Number; //0-999999  //Event: Reset to Factory, Factory Burn In , overwrite is Factory password-protected  //serial number of the whole machine. We will need a burn-in factory password to modify this, after the first set.
                                           //Also shown on maintenance-screen: Serial Number: Value: comes from the backend. Serial number of the device.
EXTERN /*uint16_t*/uint8_t Model_Number; //0-99999 (Doesn't fit into 8 bits!)  //Event: Reset to Factory, Factory Burn In , overwrite is Factory password-protected  //model number of the whole machine. We will need a burn-in factory password to modify this, after the first set.
                                           //Also shown on maintenance-screen: Model Number: Value: it comes from the backend. The model number of the device.
EXTERN struct __attribute__((aligned(1))) PistonSizes_t {
 uint8_t PistonSize_Pump1 : 2; //bits[0:1]
 uint8_t PistonSize_Pump2 : 2; //bits[2:3]
 uint8_t PistonSize_Pump3 : 2; //bits[4:5]
} PistonSizes;

EXTERN struct __attribute__((aligned(1))) StrokeLengths_t {
 uint8_t StrokeLength_Pump1 : 2; //bits[0:1]
 uint8_t StrokeLength_Pump2 : 2; //bits[2:3]
 uint8_t StrokeLength_Pump3 : 2; //bits[4:5]
} StrokeLengths;

//Optos pumps can have one of several different liquid ends and pistons installed. When shipped from the factory, the setting is for the model purchased.
//You may have occasion to wish to change the piston and/or liquid end type to change the flow rate range or material of construction.
//The numeric field indicates piston size (3/32, 1/8, ¼), and alpha field indicates material of construction of the head (SS, PK).
//The high and low pressure limits are reset when changing the liquid end type to the default for that type.
EXTERN struct __attribute__((aligned(1))) WettedParts_t {
 uint8_t WettedPart_Pump1 : 2; //bits[0:1]
 uint8_t WettedPart_Pump2 : 2; //bits[2:3]
 uint8_t WettedPart_Pump3 : 2; //bits[4:5]
} WettedParts;



//Select Options (Purchase Settings) screen:
//This screen is used to set up the purchase settings when the device has started for the first time in the factory. These
//settings can be modified later using the Factory password.

EXTERN struct __attribute__((aligned(1))) Options_t {
 uint8_t Pressure_Transducer : 1;  //bit0 //This setting tells the Home screen to show the pressure or not!
 uint8_t WashPort_Pump : 1;        //bit1
 uint8_t LeakDetector_Sensor : 1;  //bit2
 uint8_t Flow_Sensor : 1;          //bit3 //users have a more accurate flow rate if they have a sensor for that
 uint8_t Encoder : 1;              //bit4
} Options;



//Home 1/2/3-Pump (Pump Control/PumpHomePage) screen:
//This screen controls Pump 1 and displays the header and the main menu.
//In the case of remote control: controls are disabled on this screen, except the Purge button. Remote control can be
//enabled/disabled by each pump individually.

EXTERN struct __attribute__((aligned(1))) PumpModes_t {
 uint8_t Pump_1_mode : 2; //bits[0:1] //Flow, Pressure, or Dispense
 uint8_t Pump_2_mode : 2; //bits[2:3] //Flow, Pressure, or Dispense
 uint8_t Pump_3_mode : 2; //bits[4:5] //Flow, Pressure, or Dispense
} PumpModes;

//When the power is turned ON, the display shows the set flow rate (and pressure when the optional damper is installed).
EXTERN float Flow_Rate1/*Pump_Rate1*/; //0.002 to 100.00ml/min  Event: Purge Pump 1  //Up/down button (only in flow and pressure modes): In flow mode: 1 click increases/decreaeses Flow rate by .001 mL/min.
EXTERN float Flow_Rate2/*Pump_Rate2*/; //0.002 to 100.00ml/min  Event: Purge Pump 2  //(If you hold down the button, it should start incrementing/decrementing slowly and speed up the longer that you hold it down.)
EXTERN float Flow_Rate3/*Pump_Rate3*/; //0.002 to 100.00ml/min  Event: Purge Pump 3  //Flow rate value: Pump Rate 1 value, can come from adjusting up and down buttons, 4-20mA analog input, 0-5V analog input, or RS232 command.

EXTERN uint16_t Pressure/*1*/; //0 to 7500 psi  Events: Run/Stop Pump1, Up Pump1, Down Pump1  //Pump Pressure 1 value, (comes from a 0-5V input on the PCBA) //Pressure (There is only 1 pressure value for all the pumps): This is only available when the pressure transducer has been purchased by the user. Each pump has the same pressure. This is the real pressure.
//EXTERN uint16_t Pressure2; //0 to 7500 psi  Events: Run/Stop Pump2, Up Pump2, Down Pump2
//EXTERN uint16_t Pressure3; //0 to 7500 psi  Events: Run/Stop Pump3, Up Pump3, Down Pump3

EXTERN uint16_t Pressure_Target; //0 to 7500 psi  //Value: the wanted pressure  //Up/down button (only in flow and pressure modes): In pressure mode: increase/decrease the target pressure

EXTERN float Flow_total_1; //Pump total 1 ?  //Flow total (Originally: Pump Total): Flow total value: Counter of the total pumped amount in ml that resets and starts on ’Start’ and stops at ’Stop’.
EXTERN float Flow_total_2;
EXTERN float Flow_total_3;
EXTERN uint16_t Run_time_1; //Run time 1 //Run time value: Counter in Minutes/Seconds that resets and starts on ’Start’ and stops at ’Stop’. Need to add
EXTERN uint16_t Run_time_2;
EXTERN uint16_t Run_time_3;

EXTERN uint8_t Pressure_transducer; //Values: 0,1 //It is used to decide whether to show the pressure on this screen or not

EXTERN float Dispense_Amount_1; //Amount (input field - dispense mode only): Number input field: we want the pump to pump an “x” amount of fluid over “y” time. After that amount (ml) the pump will stop automatically (except if it repeats).
EXTERN float Dispense_Amount_2; //                                           (Default: 0. Each time when it’s changed the interval of the dispense time will be recalculated. The backend will calculate it.)
EXTERN float Dispense_Amount_3;
EXTERN uint16_t Dispense_Duration_1; //Duration (input field - dispense mode only): Number input field: This is the calculated time the customer plans to run the pump.
EXTERN uint16_t Dispense_Duration_2; //                                             (Default: 10. The interval here is dynamically calculated by the given amount.)
EXTERN uint16_t Dispense_Duration_3;

EXTERN struct __attribute__((aligned(1))) Repeat_t {
 uint8_t Repeat_1 : 1; //Bit0
 uint8_t Repeat_2 : 1; //Bit1
 uint8_t Repeat_3 : 1; //Bit2
} Repeat;

EXTERN uint16_t Delay_1; //Delay (input field - dispense mode only): Number input field: it is the time in seconds between repeats.
EXTERN uint16_t Delay_2;
EXTERN uint16_t Delay_3;
EXTERN uint16_t Occurrences_1; //Occurrences (input field - dispense mode only): Number input field: After that many repeats the pump will stop automatically. The default is 1. Zero means it will repeat forever or until the stop button has been pressed.
EXTERN uint16_t Occurrences_2;
EXTERN uint16_t Occurrences_3;

EXTERN uint8_t Message_Center[128]; //max 128 chars  Default:"The support link"  //Footer: Message center: default text: nothing, except on the Home screen where the default value is the support link. Error messages, alarms, and other messages may appear here.



//Pump Settings screen:
//On this screen, we find advanced configuration options for each pump.

//Property and Value Selector rollers:

EXTERN struct __attribute__((aligned(1))) DispenseModes_t {
 uint8_t Dispense_Mode_Pump1 : 2; //Bits[0:1]  Pump Dispense Mode: fixed constant values from the original SLS project: “Flow”, “Pressure”, “Dispense”
 uint8_t Dispense_Mode_Pump2 : 2; //Bits[2:3]
 uint8_t Dispense_Mode_Pump3 : 2; //Bits[4:5]
} DispenseModes;

//Synchronization mode: This option is only available when there are multiple pumps. When we change the sync, we need to restart the machine. We can only sync a pump with the
//main pump (Pump 1), so there is no option like 2 and 3 are optimized, but 1 is individual. If 2 pumps are synchronized, then they will be handled as 1 pump. So if Pump 1 and Pump 2 are
//synchronized, then they will be shown as one pump like „Pump 1 and 2” in the Pump selector rollers and in the title of pump tabs.On change: popup: („In order to change this option, the pumps must be stopped
//and the machine needs to be restarted. Do you want to change this, stop the pumps and restart the machine now?”, „Ok”, Cancel”).
//Values: Values are depending on the number of pumps:
//-In the case of 3 pumps: "No synchronization", "1 and 2 synchronized", "1 and 3 synchronized", ("2 and 3 synchronized" not possible, always synchronizing to pump1), "All synchronized"
//-In the case of 2 pumps: "No synchronization", "synchronized"
EXTERN struct __attribute__((aligned(1))) SynchronizationModes_t {
 uint8_t Synchronization_1 : 2; //Bits[0:1] //synchronization-setting is probably only needed once as common for all pumps, isn't it?
 uint8_t Synchronization_2 : 2; //Bits[2:3]
 uint8_t Synchronization_3 : 2; //Bits[4:5]
} SynchronizationModes;
/*EXTERN struct __attribute__((aligned(1))) { //what is it? number of pumps? (i created a single variable for that), most probably it referred to the pump-synchronization
 uint8_t Multi_Pump_1 : 2; //Bits[0:1]
 uint8_t Multi_Pump_2 : 2; //Bits[2:3]
 uint8_t Multi_Pump_3 : 2; //Bits[4:5]
} MultiPumps;*/

//Optos pumps can be set to a variety of refill:output ratios. The default setting, refill: full out, optimizes the ratio for minimal pulsation throughout the flow rate range, by minimizing the refill portion of the duty cycle. Other settings are:
//refill: 15 out: 85 (sets the ratio to 15:85), refill: 30 out: 70 (sets the ratio to 30:70), refill: 50 out: 50 (sets the ratio to 50:50), refill: 70 out: 30 (sets to ratio to 70:30).
EXTERN struct __attribute__((aligned(1))) PumpOutputRatios_t {
 uint8_t Output_Ratio_Pump1 : 4; //Bits[0:3]  //Set Refill Output Ratio: fixed constant values from the original SLS project
 uint8_t Output_Ratio_Pump2 : 4; //Bits[4:7]
 //uint8_t : 0; //start new byte
 uint8_t Output_Ratio_Pump3 : 4; //Bits[0:3]
} PumpOutputRatios;

//When an error occurs, the red light is illuminated. If the motor stall shutdown is set to ON, the pump will stop pumping. These occur immediately when the Error Delay is set to 0.
//You may wish for a delay to be built into the response to an error (in the event of a transient problem). You can set a delay of up to 10 seconds.
//With the delay, the pump will not illuminate the red light or stop the pump (when the motor stall shutdown is set to ON) until the error condition persists for the set number of seconds (0-10). The default setting is 0.
EXTERN struct __attribute__((aligned(1))) ErrDelays_t {
 uint8_t Err_Delay_1 : 4; //Bits[0:3]  //Error Delay: fixed constant values from the original SLS project
 uint8_t Err_Delay_2 : 4; //Bits[4:7]
 //uint8_t : 0; //start new byte
 uint8_t Err_Delay_3 : 4; //Bits[0:3]
} ErrDelays;

EXTERN struct __attribute__((aligned(1))) VoltageOutputs_t {
 uint8_t Voltage_Output_1 : 2; //Bits[0:1]  //Set Voltage Out: fixed constant values from the original SLS project
 uint8_t Voltage_Output_2 : 2; //Bits[2:3]
 uint8_t Voltage_Output_3 : 2; //Bits[4:5]
} VoltageOutputs;

//Various fluids have different compressibilities at different pressures. You can adjust for compressibility by setting the compressibility compensation factor.
//The default setting is 4. The maximum setting is 60? 100!. Each increment increases motor speed by approximately 1%.
EXTERN uint8_t Compressibility_1; //0 to 100  //Adjust Compressibility Compensation: it compensates the compressibility differences between different types of liquids (water, oils, ...)  Value: %, Slider: 0-100
EXTERN uint8_t Compressibility_2; //0 to 100
EXTERN uint8_t Compressibility_3; //0 to 100

//Stop on Stall: If Optos pumps are not fitted with the optional damper or if the pressures limits are de-activated, the motor will stall when exposed to excessive pressure.
// When the stall stop field is set to ON, the pump will stop pumping when a stall condition is noted; when the stall stop field is set to OFF, the pump will continue pumping,
// or trying to pump even in the presence of a motor stall. The default setting is OFF.
//Save State: When a power failure occurs, the pump does not normally start again when power is restored. If you want the pump to start pumping again when power is restored, you can set the “save state” to ON.
// The default setting is OFF. (OFF = pump does not start pumping after power is restored; ON = pump starts running after power is restored)
//Save run-flow rate: Depending on conditions, the pump may not “remember” the set flow rate when turning the pump off. If you want the pump to always remember the last run flow rate, set the save in run to ON.
// The default setting is OFF. (OFF = pump may not remember the last run flow rate; ON = pump remembers the last run flow rate).
EXTERN struct __attribute__((aligned(1))) StopRestart_bits_t {
 uint8_t Stop_on_Stall : 1; //Bit0  //Stop On Stall: Toggle: If it is enabled, will automatically stop the pump if the motor is stuck.This setting is for all pumps.
 uint8_t Restart_on_Power_Up : 1; //Bit1  //Restart On Power Up: Toggle: If it is enabled and If the pump loses electricity and when it gets electricity again it will start automatically. This setting is for all pumps.
} StopRestart_bits;



//Advanced Setup screen (leads to other setup-screens):
//Settings of alarms, units of measure, and others. We can see the settings menu here too.

//Optos pumps (with the optional damper) can have their high and low pressure limits de-activated. The default setting is ENA (limits are active).
EXTERN struct __attribute__((aligned(1))) AdvancedSetup_bits_t {
 uint8_t Temperature_unit_of_measure : 1; //Bit0  Values:0,1 //Fahrenheit/Celsius?  //removed? - can't see in the speci-fiction
 uint8_t Pressure_unit_of_measure : 1; //Bit1?  Values:0,1  //PSI/bar?  //Pressure unit of measure roller
 uint8_t Pressure_limit_enabled : 1; //Bit2?  Values:0,1  //Press limit enable: it needs pressure sensor hardware to work. API call, Default value: off
} AdvancedSetup_bits;

//Optos pumps fitted with a pulse damper are able to have high pressure limits set. The default setting is the maximum pressure capability of the model:
EXTERN uint16_t Pressure_Alarm_Max; //Upper; //0 to 7500 psi  //Pressure alarm max number input field: Value: see the Pump table, Slider: user control to set the value, Default: the same as the max (see the Pump table)
//Optos pumps fitted with a pulse damper are able to have low pressure limits set. The default setting is the zero psi. The maximum setting is 50 psi less than the high pressure limit:
EXTERN uint16_t Pressure_Alarm_Min; //Lower; //0 to 7500 psi?  //Pressure alarm min number input field: Value: 0, Slider: user control to set the value, Default: 0

EXTERN struct __attribute__((aligned(1))) DateTime_t {  //Set DateTime: DateTime picker
    uint16_t Year; uint8_t Month; uint8_t Day;
    uint8_t Hour; uint8_t Minute;
} DateTime;

//The software for speeding up and slowing down the motor is set off the home position sensor location. The software is optimized for running flows with minimal pulse at substantial pressures.
//If your conditions are different, you may wish to change the home offset setting to minimize pulsation. The default setting is 0. Other settings are from -99 to +99.
//No variable given for home-position offset for Optos Touch yet


//Firmware Update (Advanced Setup 1) screen:
//An online and offline software update option

EXTERN uint8_t FirmwareUpdate_Progress_Bar; //Value:0..100  Events: Check for update, Update from Flash  //bar and label is only shown while it is updating.



//Maintenance (Advanced Setup 2) screen:
//This screen shows the working hours of the parts to help maintain them.
//Pump selector selector: we need to select the pump to set alarms on

EXTERN uint16_t Pump1_CheckValve_RunTime/*Pump1_Check_Valve_Hours*/; //0 to 9,999  Run Time: Value: comes from the backend. This is how many hours the part has run since the last maintenance.
EXTERN uint16_t Pump2_CheckValve_RunTime/*Pump2_Check_Valve_Hours*/; //0 to 9,999  Reset button: Event?: Set the value of the “Seal Run Time” or the “Check Valve Run TIme” to 0. The customer would press this after replacing the part. So this reset button will reset the total hours the actual part of the pump has been running.
EXTERN uint16_t Pump3_CheckValve_RunTime/*Pump3_Check_Valve_Hours*/; //0 to 9,999  Warning Message: Check Valve hours has reached the the point to show a reminder (Maintenance): "Valve of Pump x requires maintenance"

EXTERN uint32_t Pump_1_Total_Run; //EXTERN uint32_t Pump1_Total_Hours_Run; //0 to 100,000 //Events: Reset Check Valve, Sensor Home
                                  //0..100,000 //Pump 1 Total Run: This is the total lifetime hours of the main (number 1) pump that has been running. (We don’t measure the lifetime run hours of the other pumps).
                                  //Value: it comes from the backend. The total hours the pump 1 has been running since the last start. This is the main pump and that’s why we don’t need to measure the total ringing hours of the others.
//EXTERN uint32_t Pump2_Total_Hours_Run; //0 to 100,000
//EXTERN uint32_t Pump3_Total_Hours_Run; //0 to 100,000

EXTERN uint16_t Pump1_Seal_RunTime/*Pump1_Total_Seal_Hours*/; //0 to 9,999  Warning Message: Piston Seal hours has reached the the point to show a reminder (Maintenance): "Piston Seal of Pump x requires maintenance"
EXTERN uint16_t Pump2_Seal_RunTime/*Pump2_Total_Seal_Hours*/; //0 to 9,999
EXTERN uint16_t Pump3_Seal_RunTime/*Pump3_Total_Seal_Hours*/; //0 to 9,999

//EXTERN uint16_t GUI_Version; //0-99.99 fixed point - is already present (Splash-screen)
//EXTERN uint16_t Firmware_Version; //0-99.99 fixed point - is already present (Splash-screen)
//EXTERN uint8_t Current_Pump? Total Hours? Total Cycles? - are they still present?

//Alarm reminder section: can set alarms of 2 parts for each pump. Alarms will show in the message center blinking on all screens. Some GUI-elements: Pump Selector tabview, Pump Part Selector roller: values: “Piston seal”, “Check Valve”
//Reminder hours: Number Input: comes from the backend. The part will have to be serviced again after these hours. The message will pop up on the message window when service is needed.
EXTERN uint16_t Pump1_Check_Valve_Alarm; //0 to 9,999
EXTERN uint16_t Pump2_Check_Valve_Alarm; //0 to 9,999
EXTERN uint16_t Pump3_Check_Valve_Alarm; //0 to 9,999
EXTERN uint16_t Pump1_Total_Seal_Alarm; //0 to 9,999
EXTERN uint16_t Pump2_Total_Seal_Alarm; //0 to 9,999
EXTERN uint16_t Pump3_Total_Seal_Alarm; //0 to 9,999

EXTERN uint8_t Washport_Auto; //Values:0,1  //Washport: Clean the back side of the pistons▪Washport:
                 //Washport Auto toggle: When we want to start or stop the pump. This setting is shared among all pumps. Turns on Washport automatically immediately after the pump starts and turns off after 5 seconds the pump stops.



//Communications (Advanced Setup 4) screen:
//Settings of network protocols for the pumps. All connection types can be used for remote control. 1 remote connection can be active at the same time. When the remote connection is active then we need to disable every
//user input via touchscreen. 1 remote connection controls all the pumps and the whole firmware. Network connection functionalities handled by the backend (Eldex).

//Serial:

//Select pump roller: This is for the analog control port only. We must set it individually for each pump. Every other setting is for all pumps. Roller: maximum 3 pumps
//Analog Control Port: Dropdown: constant values: “None”, “0-5V Out 1”, “4-20 mA Out 1”, “0-5V Out 2”, “4-20 mA Out 2”

EXTERN struct __attribute__((aligned(1))) AdvancedSetup4_bits_t {
 uint8_t RS_485 : 1; //Bit0  Values:0,1
 uint8_t RS_232 : 1; //Bit1  Values:0,1
 //uint8_t Ethernet : 1; //Bit2  Values:0,1 //moved to 'Connections' structure
 //uint8_t DHCP : 1; //Bit3  Values:0,1
 //uint8_t WiFi : 1; //Bit4  Values:0,1 //moved to 'Connections' structure
} AdvancedSetup4_bits;

EXTERN uint8_t Device_ID/*RS_485_ID*/; //0 to 255
EXTERN uint8_t Baud_Rate; //roller: values at roller-indexes: 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600.
EXTERN struct __attribute__((aligned(1))) SerialSettings_t {
 uint8_t Data_Bit : 2;   //Bits[0:1] //roller: values: 5 bits, 7 bits, 8 bits, 9 bits
 uint8_t Stop_Bit : 2;   //Bits[2:3] //roller: values: 1 bit, 1.5 bits, 2 bits
 uint8_t Parity_Bit : 2; //Bits[4:5] //roller: values: Odd, Even, Mark, Space
} SerialSettings;

//Normally, the contact closures start and stop are used in conjunction with the local keypad. The keypad is used to set the flow rate and the start and stop contacts are used to mimic the function of the RUN/STOP key.
//Normally, when using the remote analog modes of operation, if you do not want the pump to run, you do not send an appropriate signal to the relevant remote analog port on the I/O.
//If you want to use the contact closures to start and stop the pump when sending an analog signal, change the setting in the REM Contact screen to ON. The default setting is OFF.
//(OFF = contact closures cannot be used in conjunction with the remote analog controls; ON = contact closures must be used in conjunction with the remote analog controls).
EXTERN struct __attribute__((aligned(1))) RemoteContacts_t {
 uint8_t Remote_Contacts_1 : 1; //Bits[0:1]/Bit0? //Eldex: We only need 1 bit.  Remote Contacts: This allows us to use analog ports. (It doesn’t connect to other communication types) I will disable the following buttons on the main screen: Up, Down, Start/Stop.
 //uint8_t : 1;                                                                                  //Toggle: If it is enabled then change the constant message in the message center to "Remote control is enabled"  //Message: on click Remote Contacts button on Communication - Serial screen -> Warning: Remote control is enabled
 //uint8_t Remote_Contacts_2 : 1; //Bits[2:3]/Bit1? //Eldex: We only need 1 bit.
 //uint8_t : 1;
 //uint8_t Remote_Contacts_3 : 1; //Bits[4:5]/Bit2? //Eldex: We only need 1 bit.
 //uint8_t : 1;
} RemoteContacts;

//One of the outputs on the I/O ports is a 0-5V output. This output can be changed between pressure (if the Plus option is present) and flow.
EXTERN struct __attribute__((aligned(1))) AnalogOutputs_t {
 uint8_t Analog_Output_pump_1 : 2; //Bits[0:1]
 uint8_t Analog_Output_pump_2 : 2; //Bits[2:3]
 uint8_t Analog_Output_pump_3 : 2; //Bits[4:5]
} AnalogOutputs;

//Ethernet:

EXTERN uint8_t Address [4]; //255.255.255.255  //IP-address: Number Input field with ‘.’ character
EXTERN uint8_t Mask [4]; //255.255.255.255  //Subnet-mask: Number Input field with ‘.’ character
EXTERN uint8_t GateWay [4]; //Gateway-IP: Number Input field with ‘.’ character
EXTERN uint8_t DNS [4]; //DNS-IP: Number Input field with ‘.’ character
EXTERN uint8_t Remote_Connection; //values: 0,1  //what is this?
EXTERN struct __attribute__((aligned(1))) EthernetSettings_t {
 uint8_t DHCP : 1; //Bit0 //Checkbox: when it is checked, the input fields must be disabled.
} EthernetSettings;

//WiFi:
//Hidden Networks toggle-checbox/switch: when it is off, SSID and Security Type controls are disabled, when it is on, networks control is disabled
//Connect button: connects to the selected network or the SSID (in case the hidden network is on) using the password
//Forget button: forgets the selected network

EXTERN uint8_t SSID [32]; //32 char //Text Input
EXTERN uint8_t Password [32]; //32 char (spec says nonsense size) //Text input
EXTERN struct __attribute__((aligned(1))) WiFiConnectionDetails_t {
 uint8_t Security_Type : 2; //Bits[0:1] //Roller: static list: WEP, WPA, WPA2, WPA3   Saved and/or automatic details in bits
} WiFiConnectionDetails;
EXTERN uint8_t Networks [50][32]; //Roller: explored nearby networks, and values coming from the backend, including the previously saved ones.
EXTERN struct WiFiConnectionDetails_t Network_Details [50]; //SecurityType: Roller: static list: WEP, WPA, WPA2, WPA3
EXTERN struct __attribute__((aligned(1))) WiFiSettings_t {
 uint8_t Automatic_connection : 1; //Bit0
 uint8_t Remote_Connection : 1;    //Bit1 //Enable remote control - isn't it the same as the global setting  RemoteControls.WiFi_RemoteControl?
} WiFiSettings;



//Self Test (Advanced Setup 5) screen:
//On this screen, we can start a self-test and see the results of it.
//-Run Self-Test Button: Starts the self-test. Froze the screen while the process except the scrollbar. Popup at the end: „The test has ended” with an OK button
//-Save to Flash Drive button: It only appears after the test ends. This button will be enabled only after the test has ended. After the save show a popup: („The output of the test has successfully saved on the root of the flash drive with this name: optos_test_log.txt”, „Ok”)

EXTERN uint8_t TextBuffer [10][45]; //10 lines of 45 char  Event: Start //-Self-Test Data Textarea (Only Readable): This is a console showing the process. It needs a scrollbar.

EXTERN uint8_t SelfTest_ProgressBar; //0 to 100



//Screens not present in the specification and in the GUI (obsolete/removed):


//Data Recorder (Advanced Setup 3) screen:
/*EXTERN struct __attribute__((aligned(1))) {
 uint8_t Flow : 1; //Bit0  Values:0,1
 uint8_t Pressure : 1;//Bit1  Values:0,1
 uint8_t Run : 1; //Bit2  Values:0,1  //Start/Stop?
} AdvancedSetup3_bits;*/

//EXTERN uint8_t File_Name [128];
//EXTERN uint16_t Data_Frequency; //0 to 999 seconds  //data-period?


//Home 1 Pump Graph (Chart) screen:
//EXTERN uint8_t Max_Flow; //?
//EXTERN uint8_t Max_Pressure; //?
//EXTERN uint16_t Flow_Rate_Graph [30][2]; //? //3 of them needed?
//EXTERN uint16_t Pressure_Graph [30][2]; //0 to 7500 psi


