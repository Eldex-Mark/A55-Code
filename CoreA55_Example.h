//public header



extern const int CORE_A55__GUI_REFRESH_PERIOD;
#define CORE_A55__COREMESSAGING_REFRESH_PERIOD 4 //ms



enum { GUI_ARGUMENT_UNINITIALIZED = -1 };



void CoreA55_init (int input_id, int framebuffer_id);
 void CoreA55_CoreMessaging_init ();
 void CoreA55_GUI_init (int input_id, int framebuffer_id); //separately available so a first coremessage-update can surely happen before very 1st frame of GUI

void CoreA55_refresh ();
 void CoreA55_CoreMessaging_refresh ();
 void CoreA55_GUI_refresh ();

