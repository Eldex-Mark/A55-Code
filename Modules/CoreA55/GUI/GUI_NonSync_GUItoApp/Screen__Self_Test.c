
#include "GUI_unified.h"



//bind GUI-input widgets to variables (event-based callback and refresh):
_GUI_Modifier _GUI_Modifiers__Self_Test [] = {
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Self_Test__Run_SelfTest (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Self_Test__Run_SelfTest );
}

void _GUI_clicked__Button__Self_Test__SaveToFlashdrive (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Self_Test__SaveToFlashdrive );
    _GUI_displayPopupScreen( "", "The output of the test has successfully saved on the root of the flash drive with this name: optos_test_log.txt",  "", -1,  "OK", GUI_SCREEN_ID__Self_Test, -1 ); //GUI_SCREEN_ID__BACK ); //there's no event or other indication from backend!
}


