//UI-project GUI-interface (public towards the application/backend)  //should be abstracted away from ui/LVGL namespace?

#ifdef __cplusplus
extern "C" {
#endif


enum GUIconstants {
    //GUI_VERSION = 100* 01+00, //in the format as backend requires (uint16_t 0..99.99 fixed-point)  //specification says it comes from the backend
    GUI_REFRESH_PERIOD = 10, //milliseconds
    GUI_KEYREPEAT_DELAY = (250 / GUI_REFRESH_PERIOD), //milliseconds
    GUI_KEYREPEAT_RATE = (30 / GUI_REFRESH_PERIOD), //milliseconds
    GUI_KEYREPEAT_RATE_MIN = 1 //(5 / GUI_REFRESH_PERIOD) //milliseconds
};

typedef enum GUI_ScreenIDs {
    GUI_SCREEN_ID__StartupSplash,
    GUI_SCREEN_ID__Initial_Setup,
    GUI_SCREEN_ID__Select_Option,
    GUI_SCREEN_ID__Generic_Password,
    GUI_SCREEN_ID__Home,
    GUI_SCREEN_ID__Pump_Settings,
    GUI_SCREEN_ID__Advanced_Settings,
    GUI_SCREEN_ID__Firmware_Update,
    GUI_SCREEN_ID__Maintenance,
    GUI_SCREEN_ID__Self_Test,
    GUI_SCREEN_ID__Communications,
    GUI_SCREEN_ID__Popup_Modal,
    GUI_SCREEN_AMOUNT, //Should be at the end of screen-list! (and 1st list-element's value should be 0)
    GUI_SCREEN_ID__BACK, //back to previous screen
} GUI_ScreenIDs;



void  GUI_init     (int input_id, int framebuffer_id);  //initializes screens and GUI-states ( use negative parameter-value if you want to retain the default IDs)

void  GUI_refresh  ();  //Should be called periodically (in 5..10ms periods) to request input and refresh GUI content

void GUI_loadScreen (GUI_ScreenIDs screen_id);
void GUI_loadScreenWithFade (GUI_ScreenIDs screen_id, int duration);


#ifdef __cplusplus
} /*extern "C"*/
#endif

