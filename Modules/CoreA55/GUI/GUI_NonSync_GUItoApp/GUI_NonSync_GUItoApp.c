//Define and perform asynchronous (event-driven) input happenings  (From GUI to Application)
//(These SquareLine Studio project defined functions might be usable in the application code directly but that would expose lv_event_t to application, mixing layers.)

#include "GUI_unified.h"



//Converter functions usable in the observer-arrays
/*static*/ _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_IntToText ) {
    //sprintf( _GUI.TempString, "%d", input_value.Int );
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__STRING; return (_GUI_ValueContainer) { .Pointer = _GUI_convertIntToText( input_value.Int ) /*_GUI.TempString*/ };
}

/*static*/ _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_TextToInt ) {
    int Value;
    if (input_value.Pointer != NULL && *(char*)input_value.Pointer != '\0') Value = _GUI_convertTextToInt( input_value.Pointer ) /*sscanf( input_value.Pointer, "%d", &Value )*/; else Value = 0;
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = Value };
}


/*static*/ _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_FloatToText ) {
    //sprintf( _GUI.TempString, "%.2f", input_value.Float );
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__STRING; return (_GUI_ValueContainer) { .Pointer = _GUI_convertFloatToText( input_value.Float ) /*_GUI.TempString*/ };
}

/*static*/ _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_TextToFloat ) {
    float Value;
    if (input_value.Pointer != NULL && *(char*)input_value.Pointer != '\0') Value = _GUI_convertTextToFloat( input_value.Pointer ) /*sscanf( input_value.Pointer, "%f", &Value )*/; else Value = 0.0;
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__FLOAT; return (_GUI_ValueContainer) { .Float = Value };
}









//bind inputs to variables (event-based callback and refresh):













//These functions don't need binding because they're internal to the GUI but use variables/functions presented by the binding


/*void _GUI_xxx () {
    _GUI_setLabel( UIp.Label_XXX, _GUI_getText("Wait for XXX") );
    _App_startXXX();
}*/



//Internal (GUI doesn't call App-functions but sets App-variables)


//Button callback-functions:








//Selector/slider/etc. value-change callbacks:



//Checkbox, etc. callbacks


//Auxiliary functions related to inits/callbacks







//Main infrastructure:
static void _GUI_init_Modifiers () {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) {
        _GUI_initScreenModifiers( _GUI.ScreenDescriptors[ i ].Modifiers );
        _GUI_refreshScreenModifiers( _GUI.ScreenDescriptors[ i ].Modifiers );
    }
}

static void _GUI_refresh_Modifiers () {
    for (int i=0; i<GUI_SCREEN_AMOUNT; ++i) {
        _GUI_refreshScreenModifiers( _GUI.ScreenDescriptors[ i ].Modifiers );
    }
}

void _GUI_init_AsyncInputs () {
    _GUI_init_Modifiers();
    //other manually added event-handler initializations can be put here too
}

void _GUI_refresh_AsyncInputs () {
    _GUI_refresh_Modifiers();
    //other manually added event-handler initializations can be put here too
}


