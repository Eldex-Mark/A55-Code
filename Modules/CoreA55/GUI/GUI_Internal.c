//GUIproject-specific functions only used internally, not public towards Backend

#include "GUI_unified.h"

#include "CoreMessaging.h"



struct GUIprivateVariables _GUI = {
    .TempString = "",
    .CurrentScreenID = GUI_SCREEN_ID__StartupSplash, //-1,
    .PreviousScreenID = GUI_SCREEN_ID__StartupSplash, //-1
    .ScreenDescriptors = {
        [GUI_SCREEN_ID__StartupSplash]      = { & ui_Screen__StartupSplash,      _GUI_initScreen__StartupSplash,      _GUI_initScreenValues__StartupSplash,      _GUI_Observers__StartupSplash,     _GUI_Modifiers__StartupSplash     },
        [GUI_SCREEN_ID__Initial_Setup]      = { & ui_Screen__Initial_Setup,      _GUI_initScreen__Initial_Setup,      _GUI_initScreenValues__Initial_Setup,      _GUI_Observers__Initial_Setup,     _GUI_Modifiers__Initial_Setup     },
        [GUI_SCREEN_ID__Select_Option]      = { & ui_Screen__Select_Option,      _GUI_initScreen__Select_Option,      _GUI_initScreenValues__Select_Option,      _GUI_Observers__Select_Option,     _GUI_Modifiers__Select_Option     },
        [GUI_SCREEN_ID__Generic_Password]   = { & ui_Screen__Generic_Password,   _GUI_initScreen__Generic_Password,   _GUI_initScreenValues__Generic_Password,   _GUI_Observers__Generic_Password,  _GUI_Modifiers__Generic_Password  },
        [GUI_SCREEN_ID__Home]               = { & ui_Screen__Home,               _GUI_initScreen__Home,               _GUI_initScreenValues__Home,               _GUI_Observers__Home,              _GUI_Modifiers__Home              },
        [GUI_SCREEN_ID__Pump_Settings]      = { & ui_Screen__Pump_Settings,      _GUI_initScreen__Pump_Settings,      _GUI_initScreenValues__Pump_Settings,      _GUI_Observers__Pump_Settings,     _GUI_Modifiers__Pump_Settings     },
        [GUI_SCREEN_ID__Advanced_Settings]  = { & ui_Screen__Advanced_Settings,  _GUI_initScreen__Advanced_Settings,  _GUI_initScreenValues__Advanced_Settings,  _GUI_Observers__Advanced_Settings, _GUI_Modifiers__Advanced_Settings },
        [GUI_SCREEN_ID__Firmware_Update]    = { & ui_Screen__Firmware_Update,    _GUI_initScreen__Firmware_Update,    _GUI_initScreenValues__Firmware_Update,    _GUI_Observers__Firmware_Update,   _GUI_Modifiers__Firmware_Update   },
        [GUI_SCREEN_ID__Maintenance]        = { & ui_Screen__Maintenance,        _GUI_initScreen__Maintenance,        _GUI_initScreenValues__Maintenance,        _GUI_Observers__Maintenance,       _GUI_Modifiers__Maintenance       },
        [GUI_SCREEN_ID__Self_Test]          = { & ui_Screen__Self_Test,          _GUI_initScreen__Self_Test,          _GUI_initScreenValues__Self_Test,          _GUI_Observers__Self_Test,         _GUI_Modifiers__Self_Test         },
        [GUI_SCREEN_ID__Communications]     = { & ui_Screen__Communications,     _GUI_initScreen__Communications,     _GUI_initScreenValues__Communications,     _GUI_Observers__Communications,    _GUI_Modifiers__Communications    },
        [GUI_SCREEN_ID__Popup_Modal]        = { & ui_Screen__Popup_Modal,        _GUI_initScreen__Popup_Modal,        _GUI_initScreenValues__Popup_Modal,        _GUI_Observers__Popup_Modal,       _GUI_Modifiers__Popup_Modal       }
    },
    .PasswordScreen_Mode = _GUI_PASSWORD_SCREEN_MODE__CHANGE_REMOTE, .PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Home, .PasswordScreen_TargetWidget = NULL, .PasswordScreen_RememberedPasswordType = -1,
    .SelectedPump__Initial_Setup = 0/*1*/, .SelectedPump__Home = 0/*1*//*2*/, .SelectedPump__Pump_Settings = 0, .SelectedPump__Maintenance = 0/*1*/, .SelectedPump__Communication_Serial = 0/*2*/,
    .WiFi_HiddenNetwork = 0/*1*/, .Maintenance__PumpPart = 0/*1*/, .Pump_Settings__SettingID = 1/*2*/
};



static void _GUI_updateScreenIDs (GUI_ScreenIDs screen_id) {
    _GUI.PreviousScreenID = _GUI.CurrentScreenID; _GUI.CurrentScreenID = screen_id;
}

static void _GUI_screenIDsetCallback (lv_event_t* event) { //generic screen-loaded callback for internal functionalities (observers, modifiers)
    _GUI_updateScreenIDs( (uintptr_t) lv_event_get_user_data( event ) );
}

static void _GUI_initScreens () {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) {
        _GUI.ScreenDescriptors[ i ].initScreen();
        _GUI_setScreenLoadCallbackWithPointer( *_GUI.ScreenDescriptors[ i ].Screen, _GUI_screenLoadedCallback, (void*) &_GUI.ScreenDescriptors[ i ] ); //_GUI_setScreenLoadCallback( *_GUI.ScreenDescriptors[ i ].Screen, _GUI.ScreenDescriptors[ i ].initScreenValues );
        _GUI_setScreenLoadCallbackWithValue( *_GUI.ScreenDescriptors[ i ].Screen, _GUI_screenIDsetCallback, i );
    }
    _GUI_init_AsyncInputs();
    _GUI_init_SynchOutputs();
}

void _GUI_init_Main (int input_id, int framebuffer_id) {
    lv_init(); //Initialize LVGL
    HAL_init( input_id, framebuffer_id ); //Initialize the HAL (display, input devices, tick) for LVGL
    ui_init(); //Create and initialize all screens (create widgets, etc.) and load first screen
    _GUI_initScreens(); //extra initialization from code if needed
}


void _GUI_refresh_Main () {
    lv_timer_handler(); //Essential, LVGL does every internal handlers inside this function
    //_GUI_refreshScreens(); //should have a registered function for every screen, called at every frame if the screen is currently loaded/displayed, just in case for custom tasks..
    _GUI_refresh_SynchOutputs(); //Synchronous happenings (App-to-GUI)
}


void _GUI_loadScreenByID (GUI_ScreenIDs screen_id) {
    const _GUI_ScreenDescriptor* ScreenDescriptor = &_GUI.ScreenDescriptors[ screen_id ];
    _GUI_loadScreen( *ScreenDescriptor->Screen );
    //if (ScreenDescriptor->initScreen != NULL) ( *ScreenDescriptor->initScreenValues )(NULL);  //done in screen-loaded callback created by initScreens
    //_GUI_refreshScreenObservers( _GUI.ScreenDescriptors[screen_id].Observers, true ); //force refreshment of observers when screen opens  //done in screen-loaded callback created by initScreens
    //_GUI_updateScreenIDs( screen_id ); //_GUI.PreviousScreenID = _GUI.CurrentScreenID; _GUI.CurrentScreenID = screen_id;
}

void _GUI_loadScreenByIDwithFade (GUI_ScreenIDs screen_id, int fade_duration) {
    const _GUI_ScreenDescriptor* ScreenDescriptor = &_GUI.ScreenDescriptors[ screen_id ];
    if (fade_duration == 0) _GUI_loadScreen( *ScreenDescriptor->Screen ); else _GUI_loadScreenWithFade( ScreenDescriptor->Screen, fade_duration );
    //_GUI_updateScreenIDs( screen_id );
}


static void _GUI_loadScreenByID_Event (lv_event_t* event) { //Emscripten freezes if there's no 'event' argument for callback
    _GUI_closePopupScreen();
    _GUI_loadScreenByID( (uintptr_t) lv_event_get_user_data( event ) );
}

void _GUI_setClickScreenChangeByID (lv_obj_t* widget, GUI_ScreenIDs screen_id) {
    _GUI_setClickCallbackWithValue( widget, _GUI_loadScreenByID_Event, screen_id );
}
void _GUI_clearClickScreenChangeByID (lv_obj_t* widget) {
    lv_obj_remove_event_cb( widget, _GUI_loadScreenByID_Event );
}


static void _GUI_sendEventMessage_Event (lv_event_t* event) {
    _GUI_triggerBackendEvent( (uintptr_t) lv_event_get_user_data( event ) );
}

void _GUI_setClickBackendEventSend (lv_obj_t* widget, int event_id) {
    _GUI_setClickCallbackWithValue( widget, _GUI_sendEventMessage_Event, event_id );
}
void _GUI_clearClickBackendEventSend (lv_obj_t* widget) {
    lv_obj_remove_event_cb( widget, _GUI_sendEventMessage_Event );
}


void _GUI_displayPopupScreen (char* title, char* text, char* leftbutton_text, int leftbutton_screen_id, char* rightbutton_text, int rightbutton_screen_id, int rightbutton_event_id) {
    _GUI_setWidgetText( ui_Label__Popup_Modal__Title, title );
    _GUI_setWidgetText( ui_Label__Popup_Modal__Text, text );
    _GUI_setWidgetText( ui_ButtonLabel__Popup_Modal__Left, leftbutton_text ); _GUI_conditionalShowWidget( ui_Button__Popup_Modal__Left, leftbutton_text[0]!='\0' );
    _GUI_setWidgetText( ui_ButtonLabel__Popup_Modal__Right, rightbutton_text ); _GUI_conditionalShowWidget( ui_Button__Popup_Modal__Right, rightbutton_text[0]!='\0' );

    _GUI_clearClickScreenChangeByID( ui_Button__Popup_Modal__Left ); //delete events previously used by the popup
    if (leftbutton_screen_id >= 0) _GUI_setClickScreenChangeByID( ui_Button__Popup_Modal__Left, leftbutton_screen_id==GUI_SCREEN_ID__BACK? _GUI.PreviousScreenID : leftbutton_screen_id );
    _GUI_clearClickScreenChangeByID( ui_Button__Popup_Modal__Right ); //delete events previously used by the popup
    if (rightbutton_screen_id >= 0) _GUI_setClickScreenChangeByID( ui_Button__Popup_Modal__Right, rightbutton_screen_id==GUI_SCREEN_ID__BACK? _GUI.PreviousScreenID : rightbutton_screen_id );
    _GUI_clearClickBackendEventSend( ui_Button__Popup_Modal__Right ); //delete events previously used by the popup
    if (rightbutton_event_id >= 0) _GUI_setClickBackendEventSend( ui_Button__Popup_Modal__Right, rightbutton_event_id );

    lv_obj_set_parent( ui_Panel__Popup_Modal__Full, lv_layer_top() );  //_GUI_loadScreenByID( GUI_SCREEN_ID__Popup_Modal );
}

void _GUI_closePopupScreen () {
    if ( lv_obj_get_parent( ui_Panel__Popup_Modal__Full ) == lv_layer_top() )  lv_obj_set_parent( ui_Panel__Popup_Modal__Full, ui_Screen__Popup_Modal );
}


void _GUI_displayStatusMessage (char* message) { //backend or GUI sets the message?
    strcpy( (char*) IOp.FooterText, message );
}


inline void _GUI_triggerBackendEvent (int event_id) {
    CoreMessaging_broadcastEvent( event_id ); //CoreMessaging_callEvent( event_id, COREMESSAGING_ENDPOINT__CORE_A55 );
}


int _GUI_getPumpMode (int selected_pump) {
    return selected_pump==0 ? IOp.PumpDispenseModes->Dispense_Mode_Pump1 : ( selected_pump==1? IOp.PumpDispenseModes->Dispense_Mode_Pump2 : IOp.PumpDispenseModes->Dispense_Mode_Pump3 );
}

float _GUI_getFlowRate (int selected_pump) {
    return selected_pump==0 ? *IOp.FlowRate_Pump1 : ( selected_pump==1? *IOp.FlowRate_Pump2 : *IOp.FlowRate_Pump3 );
}

