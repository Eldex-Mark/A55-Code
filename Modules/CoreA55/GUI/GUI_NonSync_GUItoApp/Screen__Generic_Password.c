
#include "GUI_unified.h"



//bind GUI-input widgets to variables (event-based callback and refresh):
_GUI_Modifier _GUI_Modifiers__Generic_Password [] = {
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Generic_Password__Cancel (lv_event_t* event) {
    _GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Home;
    _GUI.PasswordScreen_TargetWidget = NULL;
    _GUI_loadScreenByID( _GUI.PreviousScreenID );
}

void _GUI_clicked__Button__Generic_Password__OK (lv_event_t* event) {
    enum { BACKEND_PASSWORD_SIZE_MAX = 16, BACKEND_PASSWORD_LENGTH_MAX = BACKEND_PASSWORD_SIZE_MAX -1 };
    bool PasswordMatches = false;
    char* EnteredText = (char*) lv_textarea_get_text( ui_Textarea__Generic_Password__PasswordField );
    switch (_GUI.PasswordScreen_Mode) {
        case _GUI_PASSWORD_SCREEN_MODE__ENTER_FACTORY: PasswordMatches = !strcmp( EnteredText, (char*) IOp.FactoryPassword ); break;
        case _GUI_PASSWORD_SCREEN_MODE__ENTER_USER: PasswordMatches = !strcmp( EnteredText, (char*) IOp.UserPassword ); break;
        case _GUI_PASSWORD_SCREEN_MODE__CHANGE_REMOTE:
            strncpy( (char*) IOp.RemoteControlPassword, EnteredText, BACKEND_PASSWORD_LENGTH_MAX ); PasswordMatches = true;
            _GUI_triggerEvent( _GUI_TO_BACKEND_EVENT__Generic_Password__OK__RemoteControlPassword_Changed );
        break;
    }
    if (PasswordMatches) {
        _GUI_loadScreenByID( _GUI.PasswordScreen_TargetScreenID );
        _GUI.PasswordScreen_RememberedPasswordType = _GUI.PasswordScreen_Mode; //_GUI.PasswordScreen_TargetScreenID = GUI_SCREEN_ID__Home;
    }
    else return;
}


void _GUI_clicked__Keyboard__Generic_Password__PasswordEntry (lv_event_t* event) { //make it possible to close onscreen-keyboard by Enter too, not just OK
    enum { KEYINDEX_ENTER = 22 };
    uint16_t ButtonID = lv_keyboard_get_selected_btn( ui_Keyboard__Generic_Password__PasswordEntry );
    if (ButtonID == KEYINDEX_ENTER) _GUI_clicked__Button__Generic_Password__OK( NULL );
}



/*typedef struct _GUI_PasswordCall_t {
    bool PasswordRequired;
    int  PasswordMode;
    int  TargetScreenID;
};

*void _GUI_passwordCallback (lv_event_t* event) {
    _GUI_PasswordCall_t *PasswordCall = (_GUI_PasswordCall_t*) lv_event_get_user_data( event );
    _GUI.PasswordScreen_Mode = PasswordCall->PasswordMode;
    _GUI_loadScreenByID( GUI_SCREEN_ID__Generic_Password );
}

void _GUI_setPasswordCall( lv_obj_t* widget, bool password_required, int password_mode, int target_screen_id ) {
    _GUI_setClickCallbackWithPointer( widget, _GUI_passwordCallback,  );
}*/


