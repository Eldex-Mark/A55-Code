//bind cyclically refreshed 'observer' outputs (labels/etc.) to 'subject' variables:



#include "GUI_unified.h"
#include "GUI_Synch_AppToGUI_internal.h"



_GUI_Observer _GUI_Observers__StartupSplash [] = {
 { _GUI_SUBJECT_TYPE__UINT16P/*FLOAT*/, /*&_GUI.GUI_Version_Float*/ &IOp.GUI_Version,           &ui_Label__StartupSplash__GUIversion,     _GUI_valueConverter_VersionNumbers, "GUI v%2.2f",      _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__FLOAT/*UINT16P*/,  &_GUI.Firmware_Version_Float/*&IOp.Firmware_Version*/, &ui_Label__StartupSplash__FirwareVersion,               NULL,                 "Firmware v%2.2f", _GUI_DISPLAYED_TYPE__NORMAL, { .Float=0.0 } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Initial_Setup [] = {
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Serial_Number, &ui_Textarea__Initial_Setup__Serial_Number, NULL,   "" , _GUI_DISPLAYED_TYPE__PLACEHOLDER,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.Model_Number,  &ui_Textarea__Initial_Setup__Model_Number,  NULL,   NULL, _GUI_DISPLAYED_TYPE__PLACEHOLDER,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Initial_Setup__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Initial_Setup__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Initial_Setup__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Select_Option [] = {
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Select_Option__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Select_Option__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Select_Option__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Generic_Password [] = {
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Generic_Password__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Generic_Password__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Generic_Password__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Home [] = {
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Pressure_Target, &ui_Label__Home__MainValue, _GUI_valueConverter_getHomeMainValue, "", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__FLOATP, &IOp.FlowRate_Pump1, &ui_Label__Home__MainValue, _GUI_valueConverter_getHomeMainValue, "%.1f", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__FLOATP, &IOp.FlowRate_Pump2, &ui_Label__Home__MainValue, _GUI_valueConverter_getHomeMainValue, "%.1f", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__FLOATP, &IOp.FlowRate_Pump3, &ui_Label__Home__MainValue, _GUI_valueConverter_getHomeMainValue, "%.1f", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Pressure_Pump1,  &ui_Label__Home__CurrentPressure, NULL,   "", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__FLOATP, &IOp.FlowAmount_Pump1,  &ui_Label__Home__Total_PumpedFlowAmount, _GUI_valueConverter_getHomePumpFlowAmount,   "%.0f ml", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__FLOATP, &IOp.FlowAmount_Pump2,  &ui_Label__Home__Total_PumpedFlowAmount, _GUI_valueConverter_getHomePumpFlowAmount,   "%.0f ml", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__FLOATP, &IOp.FlowAmount_Pump3,  &ui_Label__Home__Total_PumpedFlowAmount, _GUI_valueConverter_getHomePumpFlowAmount,   "%.0f ml", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.RunTime_Pump1,    &ui_Label__Home__RunTime, _GUI_valueConverter_getHomePumpRuntime,   "%d min", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.RunTime_Pump2,    &ui_Label__Home__RunTime, _GUI_valueConverter_getHomePumpRuntime,   "%d min", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.RunTime_Pump3,    &ui_Label__Home__RunTime, _GUI_valueConverter_getHomePumpRuntime,   "%d min", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Home__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Home__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Home__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Home__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Pump_Settings [] = {
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.FluidCompressibility_Pump1, &ui_Label__Pump_Settings__CompressibilityCompensation_Value, _GUI_valueConverter_getCompressibilityValue,  "%d%%", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.FluidCompressibility_Pump2, &ui_Label__Pump_Settings__CompressibilityCompensation_Value, _GUI_valueConverter_getCompressibilityValue,  "%d%%", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.FluidCompressibility_Pump3, &ui_Label__Pump_Settings__CompressibilityCompensation_Value, _GUI_valueConverter_getCompressibilityValue,  "%d%%", _GUI_DISPLAYED_TYPE__NORMAL,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Pump_Settings__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Pump_Settings__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Pump_Settings__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Pump_Settings__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Advanced_Settings [] = {
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.PressureAlarm_UpperThreshold,  &ui_Textarea__Advanced_Settings__PressureAlarm_Max, NULL,   "", _GUI_DISPLAYED_TYPE__PLACEHOLDER,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.PressureAlarm_LowerThreshold,  &ui_Textarea__Advanced_Settings__PressureAlarm_Min, NULL,   "", _GUI_DISPLAYED_TYPE__PLACEHOLDER,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRING, _GUI.DateTimeString,  &ui_Label__Advanced_Settings__DateAndTime, NULL,   "", _GUI_DISPLAYED_TYPE__NORMAL,   { .Pointer=_GUI.DateTimeString_previous } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Advanced_Settings__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Advanced_Settings__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Advanced_Settings__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Advanced_Settings__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Firmware_Update [] = {
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Firmware_Update__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Firmware_Update__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Firmware_Update__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Firmware_Update__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Maintenance [] = {
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Serial_Number,  &ui_Textarea__Maintenance__SerialNumber, NULL,  "%d",  _GUI_DISPLAYED_TYPE__NORMAL,  { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Model_Number,   &ui_Textarea__Maintenance__ModelNumber, NULL,   "%d",  _GUI_DISPLAYED_TYPE__NORMAL,  { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.GUI_Version,      &ui_Textarea__Maintenance__GUIversion,      _GUI_valueConverter_VersionNumbers,  "%2.2f",  _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.Firmware_Version, &ui_Textarea__Maintenance__FirmwareVersion, _GUI_valueConverter_VersionNumbers,  "%2.2f",  _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT32P, &IOp.TotalRunHours_Pump1, &ui_Textarea__Maintenance__Pump1_TotalRun, NULL, "%d hours", _GUI_DISPLAYED_TYPE__NORMAL,  { 0 } },

 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.TotalRunHours__Pump1_PistonSeal,  &ui_Label__Maintenance__PumpPart_Runtime, _GUI_valueConverter_getPumpPartRuntime, "%d", _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.TotalRunHours__Pump2_PistonSeal,  &ui_Label__Maintenance__PumpPart_Runtime, _GUI_valueConverter_getPumpPartRuntime, "%d", _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.TotalRunHours__Pump3_PistonSeal,  &ui_Label__Maintenance__PumpPart_Runtime, _GUI_valueConverter_getPumpPartRuntime, "%d", _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.TotalRunHours__Pump1_CheckValve,  &ui_Label__Maintenance__PumpPart_Runtime, _GUI_valueConverter_getPumpPartRuntime, "%d", _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.TotalRunHours__Pump2_CheckValve,  &ui_Label__Maintenance__PumpPart_Runtime, _GUI_valueConverter_getPumpPartRuntime, "%d", _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },
 { _GUI_SUBJECT_TYPE__UINT16P, &IOp.TotalRunHours__Pump3_CheckValve,  &ui_Label__Maintenance__PumpPart_Runtime, _GUI_valueConverter_getPumpPartRuntime, "%d", _GUI_DISPLAYED_TYPE__NORMAL, { 0 } },

 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Maintenance__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Maintenance__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Maintenance__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Maintenance__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Self_Test [] = {
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Self_Test__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Self_Test__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Self_Test__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Self_Test__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};


_GUI_Observer _GUI_Observers__Communications [] = {
 { _GUI_SUBJECT_TYPE__UINT8, &_GUI.WiFi_HiddenNetwork,  &ui_Container__Communications__WiFi__LeftSide,   NULL,  NULL,  _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8, &_GUI.WiFi_HiddenNetwork,  &ui_Container__Communications__WiFi__RightSide,   _GUI_valueConverter_Negate,  NULL,  _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },

 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Communications__USB_Status,      _GUI_valueConverter_getUSBsatusBit,       NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Communications__Ethernet_Status, _GUI_valueConverter_getEthernetStatusBit, NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.ConnectionStates,  &ui_Image__Communications__WiFi_Status,     _GUI_valueConverter_getWiFiStatusBit,     NULL, _GUI_DISPLAYED_TYPE__SHOW_HIDE,   { 0 } },
 { _GUI_SUBJECT_TYPE__STRINGP, &IOp.FooterText,  &ui_Label__Communications__StatusFooter, NULL,  "",  _GUI_DISPLAYED_TYPE__NORMAL,  { .Pointer=_GUI.FooterText_previous } },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL, _GUI_DISPLAYED_TYPE__NONE, {0} }
};

