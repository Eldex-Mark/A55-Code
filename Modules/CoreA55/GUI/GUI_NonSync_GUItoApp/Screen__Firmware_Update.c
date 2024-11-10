
#include "GUI_unified.h"



//bind GUI-input widgets to variables (event-based callback and refresh):
_GUI_Modifier _GUI_Modifiers__Firmware_Update [] = {
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Firmware_Update__UpdateFromWeb (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Firmware_Update__UpdateFromWeb );
}

void _GUI_clicked__Button__Firmware_Update__UpdateFromFlashdrive (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Firmware_Update__UpdateFromFlashdrive );
}
