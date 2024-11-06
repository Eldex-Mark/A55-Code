//Define and perform synchronous (cyclic) input happenings, like displaying continuously changing values periodically (from Application to GUI)

#include "GUI_unified.h"



static void _GUI_preProcessValues () { //better being done in the converter callback-functions, but sometimes it might be better to have these converted values remain statically
    //_GUI.GUI_Version_Float = *IOp.GUI_Version / 100.0;
    _GUI.Firmware_Version_Float = *IOp.Firmware_Version / 100.0;
    sprintf( _GUI.DateTimeString, "%2.2d/%2.2d/%2.2d %2.2d:%2.2d", *IOp.DateAndTime.Month, *IOp.DateAndTime.Day, *IOp.DateAndTime.Year % 100, *IOp.DateAndTime.Hour, *IOp.DateAndTime.Minute ); //_GUI_debug("%s",_GUI.DateTimeString);
}


static void _GUI_init_Observers () {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) {
        _GUI_initScreenObservers( _GUI.ScreenDescriptors[ i ].Observers );
    }
}

static void _GUI_refresh_Observers (bool force_refresh) {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) { //speed-optimization: only run those observers that are seen on an active screen
        if ( _GUI_getCurrentScreen() == *_GUI.ScreenDescriptors[ i ].Screen ) _GUI_refreshScreenObservers( _GUI.ScreenDescriptors[ i ].Observers, force_refresh );
    }
}


void _GUI_init_SynchOutputs () {
    _GUI_init_Observers();
    _GUI_preProcessValues();
    _GUI_refresh_Observers( true ); //one call is needed for the default startup screen as it's loaded implicitly
}


void _GUI_refresh_SynchOutputs () { //Application-value/state/pointer-following observers/etc. can be put here
    _GUI_preProcessValues();
    _GUI_refresh_Observers( false );
    _GUI_handleKeyRepeat( _GUI_InputDevice, false, GUI_KEYREPEAT_DELAY, GUI_KEYREPEAT_RATE, GUI_KEYREPEAT_RATE_MIN );
    //other manually handled cyclic object checks & changes can be put here too
}



