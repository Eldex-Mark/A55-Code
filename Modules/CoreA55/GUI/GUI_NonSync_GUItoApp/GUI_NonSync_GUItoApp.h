//GUI-events that affect Backend values/states

extern _GUI_Modifier _GUI_Modifiers__StartupSplash [];
extern _GUI_Modifier _GUI_Modifiers__Initial_Setup [];
extern _GUI_Modifier _GUI_Modifiers__Select_Option [];
extern _GUI_Modifier _GUI_Modifiers__Generic_Password [];
extern _GUI_Modifier _GUI_Modifiers__Home [];
extern _GUI_Modifier _GUI_Modifiers__Pump_Settings [];
extern _GUI_Modifier _GUI_Modifiers__Advanced_Settings [];
extern _GUI_Modifier _GUI_Modifiers__Firmware_Update [];
extern _GUI_Modifier _GUI_Modifiers__Maintenance [];
extern _GUI_Modifier _GUI_Modifiers__Self_Test [];
extern _GUI_Modifier _GUI_Modifiers__Communications [];


//These functions don't need binding because they're internal to the GUI but use variables/functions presented by the binding

//_GUI Input-events (calling App-functions from the App-binding)
//void _GUI_xxx ();

//_GUI callbacks modifying App-variables (in the App-binding) only

//Button callback-functions:
void _GUI_clicked__Button__Initial_Setup__Pump1 (lv_event_t* event);
void _GUI_clicked__Button__Initial_Setup__Pump2 (lv_event_t* event);
void _GUI_clicked__Button__Initial_Setup__Pump3 (lv_event_t* event);
void _GUI_clicked__Button__Initial_Setup__Next (lv_event_t* event);
void _GUI_editSerialNumber ();
void _GUI_clicked__Textarea__Initial_Setup__Serial_Number (lv_event_t* event);
void _GUI_editModelNumber ();
void _GUI_clicked__Textarea__Initial_Setup__Model_Number (lv_event_t* event);
void _GUI_clicked__Button__Initial_Setup__ChangeRemotePassword (lv_event_t* event);
void _GUI_clicked__Button__Initial_Setup__SelectOptions (lv_event_t* event);

void _GUI_clicked__Button__Advanced_Settings__FactoryMenu (lv_event_t* event);

void _GUI_clicked__Button__Generic_Password__Cancel (lv_event_t* event);
void _GUI_clicked__Button__Generic_Password__OK (lv_event_t* event);
void _GUI_clicked__Keyboard__Generic_Password__PasswordEntry (lv_event_t* event);

void _GUI_clicked__Button__Home__Pump1 (lv_event_t* event);
void _GUI_clicked__Button__Home__Pump2 (lv_event_t* event);
void _GUI_clicked__Button__Home__Pump3 (lv_event_t* event);
void _GUI_clicked__Button__Home__StartStop (lv_event_t* event);
void _GUI_pressing__Button__Home__FlowOrPressure_Up (lv_event_t* event);
void _GUI_pressing__Button__Home__FlowOrPressure_Down (lv_event_t* event);

void _GUI_clicked__Button__Pump_Settings__Pump1 (lv_event_t* event);
void _GUI_clicked__Button__Pump_Settings__Pump2 (lv_event_t* event);
void _GUI_clicked__Button__Pump_Settings__Pump3 (lv_event_t* event);

void _GUI_clicked__Button__Maintenance__Pump1 (lv_event_t* event);
void _GUI_clicked__Button__Maintenance__Pump2 (lv_event_t* event);
void _GUI_clicked__Button__Maintenance__Pump3 (lv_event_t* event);

void _GUI_clicked__Button__Communications__Serial (lv_event_t* event);
void _GUI_clicked__Button__Communications__Ethernet (lv_event_t* event);
void _GUI_clicked__Button__Communications__WiFi (lv_event_t* event);


//Selector callback-functions:
void _GUI_changed__Roller__Initial_Setup__PistonSize (lv_event_t* event);
void _GUI_changed__Roller__Initial_Setup__StrokeLength (lv_event_t* event);
void _GUI_changed__Roller__Initial_Setup__WettedParts (lv_event_t* event);

void _GUI_changed__Slider__Pump_Settings__CompressibilityCompensation_Value (lv_event_t* event);


//Checkbox, etc. callbacks
void _GUI_changed__Checkbox__Select_Option__PressureTransducer (lv_event_t* event);
void _GUI_changed__Checkbox__Select_Option__WashPort_Pump  (lv_event_t* event);
void _GUI_changed__Checkbox__Select_Option__LeakDetector_Sensor (lv_event_t* event);
void _GUI_changed__Checkbox__Select_Option__FlowSensor (lv_event_t* event);
void _GUI_changed__Checkbox__Select_Option__Encoder (lv_event_t* event);


//Textarea callback-functions


//Slider callback-functions


//Auxiliary functions related to inits/callbacks
void _GUI_display_PumpSelection__Initial_Setup ();
void _GUI_display_PumpSelection__Home ();
void _GUI_display_PumpSelection__Pump_Settings ();
void _GUI_display_PumpSelection__Maintenance ();

void _GUI_display_OptionSelections__Select_Option ();

void _GUI_showSubscreen__Communications__Serial ();
void _GUI_showSubscreen__Communications__Ethernet ();
void _GUI_showSubscreen__Communications__WiFi ();

void _GUI_createPumpSettingValueList ();


//Main infrastructure:
void _GUI_init_AsyncInputs ();

