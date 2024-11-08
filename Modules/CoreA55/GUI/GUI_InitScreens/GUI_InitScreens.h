
//Set at GUI-startup:
void _GUI_initScreen__StartupSplash ();
void _GUI_initScreen__Initial_Setup ();
void _GUI_initScreen__Select_Option ();
void _GUI_initScreen__Generic_Password ();
void _GUI_initScreen__Home ();
void _GUI_initScreen__Pump_Settings ();
void _GUI_initScreen__Advanced_Settings ();
void _GUI_initScreen__Maintenance ();
void _GUI_initScreen__Communications ();
void _GUI_initScreen__Self_Test ();
void _GUI_initScreen__Firmware_Update ();
void _GUI_initScreen__Popup_Modal ();

//Set at every screen-call:
void _GUI_initScreenValues__StartupSplash (lv_event_t* event);
void _GUI_initScreenValues__Initial_Setup (lv_event_t* event);
void _GUI_initScreenValues__Select_Option (lv_event_t* event);
void _GUI_initScreenValues__Generic_Password (lv_event_t* event);
void _GUI_initScreenValues__Home (lv_event_t* event);
void _GUI_initScreenValues__Pump_Settings (lv_event_t* event);
void _GUI_initScreenValues__Advanced_Settings (lv_event_t* event);
void _GUI_initScreenValues__Maintenance (lv_event_t* event);
void _GUI_initScreenValues__Communications (lv_event_t* event);
void _GUI_initScreenValues__Self_Test (lv_event_t* event);
void _GUI_initScreenValues__Firmware_Update (lv_event_t* event);
void _GUI_initScreenValues__Popup_Modal (lv_event_t* event);
