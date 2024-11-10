
#include "GUI_unified.h"



//bind GUI-input widgets to variables (event-based callback and refresh):
_GUI_Modifier _GUI_Modifiers__Select_Option [] = {
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Select_Option__OK  (lv_event_t* event) {
    _GUI_triggerBackendEvent( _GUI_TO_BACKEND_EVENT__Select_Option__OK );
}


void _GUI_changed__Checkbox__Select_Option__PressureTransducer (lv_event_t* event) {
    IOp.OptionalEquipment->Pressure_Transducer = _GUI_getWidgetCheckedState( ui_Checkbox__Select_Option__PressureTransducer );
}
void _GUI_changed__Checkbox__Select_Option__WashPort_Pump  (lv_event_t* event) {
    IOp.OptionalEquipment->WashPort_Pump = _GUI_getWidgetCheckedState( ui_Checkbox__Select_Option__WashPort_Pump );
}
void _GUI_changed__Checkbox__Select_Option__LeakDetector_Sensor (lv_event_t* event) {
    IOp.OptionalEquipment->LeakDetector_Sensor = _GUI_getWidgetCheckedState( ui_Checkbox__Select_Option__LeakDetector_Sensor );
}
void _GUI_changed__Checkbox__Select_Option__FlowSensor (lv_event_t* event) {
    IOp.OptionalEquipment->Flow_Sensor = _GUI_getWidgetCheckedState( ui_Checkbox__Select_Option__FlowSensor );
}
void _GUI_changed__Checkbox__Select_Option__Encoder (lv_event_t* event) {
    IOp.OptionalEquipment->Encoder = _GUI_getWidgetCheckedState( ui_Checkbox__Select_Option__Encoder );
}



void _GUI_display_OptionSelections__Select_Option () {
    _GUI_setWidgetCheckedState( ui_Checkbox__Select_Option__PressureTransducer, IOp.OptionalEquipment->Pressure_Transducer );
    _GUI_setWidgetCheckedState( ui_Checkbox__Select_Option__WashPort_Pump, IOp.OptionalEquipment->WashPort_Pump );
    _GUI_setWidgetCheckedState( ui_Checkbox__Select_Option__LeakDetector_Sensor, IOp.OptionalEquipment->LeakDetector_Sensor );
    _GUI_setWidgetCheckedState( ui_Checkbox__Select_Option__FlowSensor, IOp.OptionalEquipment->Flow_Sensor );
    _GUI_setWidgetCheckedState( ui_Checkbox__Select_Option__Encoder, IOp.OptionalEquipment->Encoder );
}



