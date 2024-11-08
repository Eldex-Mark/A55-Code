
#include "GUI_unified.h"



enum {
    MODIFIER_INDEX__SERIAL__ANALOG_OUTPUT = 1
};



//bind GUI-input widgets to variables (event-based callback and refresh):

static _GUI_HEADER_valueConverterFunction( _GUI_refreshSerialPortPumpSelection ) {
    if (input_type == _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL) _GUI_refreshModifierWidget( &_GUI_Modifiers__Communications[ MODIFIER_INDEX__SERIAL__ANALOG_OUTPUT ] ); //_GUI_refreshScreenModifiers( _GUI_Modifiers__Communications ); }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL; return input_value;
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getSerialPortAnalogOutputType ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) {
        .Int = _GUI.SelectedPump__Communication_Serial==0? IOp.PumpAnalogOutputTypes->Analog_Output_pump_1
               : (_GUI.SelectedPump__Communication_Serial==1? IOp.PumpAnalogOutputTypes->Analog_Output_pump_2 : IOp.PumpAnalogOutputTypes->Analog_Output_pump_3)
    };
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setSerialPortAnalogOutputType ) {
    switch (_GUI.SelectedPump__Communication_Serial) {
        case 0: IOp.PumpAnalogOutputTypes->Analog_Output_pump_1 = input_value.Int; break;
        case 1: IOp.PumpAnalogOutputTypes->Analog_Output_pump_2 = input_value.Int; break;
        case 2: IOp.PumpAnalogOutputTypes->Analog_Output_pump_3 = input_value.Int; break;
    }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getSerialPortStandard )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.SerialPortSelections->RS_232 /*& !IOp.SerialPortSelections->RS_485*/ }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setSerialPortStandard )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.SerialPortSelections->RS_485 = !( IOp.SerialPortSelections->RS_232 = input_value.Int ); return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getSerialPortRemoteControl )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.RemoteControlRights->Serial_RemoteControl }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setSerialPortRemoteControl ) {
    if (input_value.Int) { _GUI_displayStatusMessage( "Remote control is enabled" ); }
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.RemoteControlRights->Serial_RemoteControl = input_value.Int; return input_value;
}


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getSerialPortDatabitsPerBaud ) //simple bitfield reader solution //better solution to handle bit-fields as pointers?
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.SerialPortBitSettings->Data_Bit }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setSerialPortDatabitsPerBaud )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.SerialPortBitSettings->Data_Bit = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getSerialPortStopBitAmount )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.SerialPortBitSettings->Stop_Bit }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setSerialPortStopBitAmount )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.SerialPortBitSettings->Stop_Bit = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getSerialPortParityBitType )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.SerialPortBitSettings->Parity_Bit }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setSerialPortParityBitType )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.SerialPortBitSettings->Parity_Bit = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setEthernetIPaddress ) {
    if (input_value.Pointer != NULL && *(char*)input_value.Pointer != '\0') _GUI_convertTextToIPaddress( input_value.Pointer, IOp.Ethernet_IPaddress /** (uint8_t**) output_value.Pointer*/ );
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE/*POINTER*/; return input_value;
}
static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setEthernetSubnetMask ) {
    if (input_value.Pointer != NULL && *(char*)input_value.Pointer != '\0') _GUI_convertTextToIPaddress( input_value.Pointer, IOp.Ethernet_SubnetMask );
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}
static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setEthernetGateWayIP ) {
    if (input_value.Pointer != NULL && *(char*)input_value.Pointer != '\0') _GUI_convertTextToIPaddress( input_value.Pointer, IOp.Ethernet_GateWayIP );
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}
static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setEthernetDNSaddress ) {
    if (input_value.Pointer != NULL && *(char*)input_value.Pointer != '\0') _GUI_convertTextToIPaddress( input_value.Pointer, IOp.Ethernet_DNSaddress );
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; return input_value;
}

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getEthernetDHCP )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.EthernetSettings->DHCP }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setEthernetDHCP )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.EthernetSettings->DHCP = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getEthernetRemoteControl )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.RemoteControlRights->Ethernet_RemoteControl }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setEthernetRemoteControl )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.RemoteControlRights->Ethernet_RemoteControl = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getWiFiAutomaticConnection )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.WiFiSettings->Automatic_connection }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setWiFiAutomaticConnection )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.WiFiSettings->Automatic_connection = input_value.Int; return input_value; }


static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getWiFiSecurityType )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.WiFiConnectionDetails->Security_Type }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setWiFiSecurityType )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.WiFiConnectionDetails->Security_Type = input_value.Int; return input_value; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getWiFiRemoteControl )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__INT; return (_GUI_ValueContainer) { .Int = IOp.RemoteControlRights->Wifi_RemoteControl }; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_setWiFiRemoteControl )
{ *output_type = _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE; IOp.RemoteControlRights->Wifi_RemoteControl = input_value.Int; return input_value; }

static _GUI_HEADER_valueConverterFunction( _GUI_valueConverter_getEthernetIPaddress ) {
    *output_type = _GUI_SUBJECT_TYPE_CATEGORY__STRING; return (_GUI_ValueContainer) { .Pointer = _GUI_convertIPaddressToText( * (uint8_t**) input_value.Pointer ) };
}



_GUI_Modifier _GUI_Modifiers__Communications [] = {
 [0] = { _GUI_SUBJECT_TYPE__UINT8, &_GUI.SelectedPump__Communication_Serial, &ui_Roller__Communications__Serial_SelectPump, NULL, _GUI_refreshSerialPortPumpSelection },
 [MODIFIER_INDEX__SERIAL__ANALOG_OUTPUT/*1*/] = { _GUI_SUBJECT_TYPE__UINT8P, &IOp.PumpAnalogOutputTypes, &ui_Roller__Communications__Serial_PumpAnalogControlPort, _GUI_valueConverter_getSerialPortAnalogOutputType, _GUI_valueConverter_setSerialPortAnalogOutputType },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.SerialPortSelections, &ui_Roller__Communications__Serial_ProtocolTypeStandard, _GUI_valueConverter_getSerialPortStandard, _GUI_valueConverter_setSerialPortStandard },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.RemoteControlRights, &ui_Switch__Communications__Serial_RemoteControl, _GUI_valueConverter_getSerialPortRemoteControl, _GUI_valueConverter_setSerialPortRemoteControl }, //If it is enabled then change the constant message in the message center to „Remote control is enabled”
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.SerialPort_DeviceID, &ui_Roller__Communications__Serial_DeviceID, NULL, NULL },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.SerialPort_BaudRate, &ui_Roller__Communications__Serial_BaudRate, NULL, NULL },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.SerialPortBitSettings, &ui_Roller__Communications__Serial_DatabitsPerBaud, _GUI_valueConverter_getSerialPortDatabitsPerBaud, _GUI_valueConverter_setSerialPortDatabitsPerBaud },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.SerialPortBitSettings, &ui_Roller__Communications__Serial_StopBitAmount,   _GUI_valueConverter_getSerialPortStopBitAmount, _GUI_valueConverter_setSerialPortStopBitAmount },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.SerialPortBitSettings, &ui_Roller__Communications__Serial_ParityBitType,   _GUI_valueConverter_getSerialPortParityBitType, _GUI_valueConverter_setSerialPortParityBitType },

 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.EthernetSettings, &ui_Checkbox__Communications__Ethernet_DHCP, _GUI_valueConverter_getEthernetDHCP, _GUI_valueConverter_setEthernetDHCP },
 { _GUI_SUBJECT_TYPE__ARRAY_NOHIDE, &IOp.Ethernet_IPaddress, &ui_Textarea__Communications__Ethernet_IPaddress, _GUI_valueConverter_getEthernetIPaddress, _GUI_valueConverter_setEthernetIPaddress },
 { _GUI_SUBJECT_TYPE__ARRAY_NOHIDE, &IOp.Ethernet_SubnetMask, &ui_Textarea__Communications__Ethernet_SubnetMask, _GUI_valueConverter_getEthernetIPaddress, _GUI_valueConverter_setEthernetSubnetMask },
 { _GUI_SUBJECT_TYPE__ARRAY_NOHIDE, &IOp.Ethernet_GateWayIP, &ui_Textarea__Communications__Ethernet_GatewayIP, _GUI_valueConverter_getEthernetIPaddress, _GUI_valueConverter_setEthernetGateWayIP },
 { _GUI_SUBJECT_TYPE__ARRAY_NOHIDE, &IOp.Ethernet_DNSaddress, &ui_Textarea__Communications__Ethernet_DNSaddress, _GUI_valueConverter_getEthernetIPaddress, _GUI_valueConverter_setEthernetDNSaddress },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.RemoteControlRights, &ui_Switch__Communications__Ethernet_RemoteControl, _GUI_valueConverter_getEthernetRemoteControl, _GUI_valueConverter_setEthernetRemoteControl },

 { _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD, &IOp.WiFi_SSID,     &ui_Textarea__Communications__WiFi_SSID,     (void*) &ui_Keyboard__Communications__WiFi_AuthenticationDataEntry, NULL },
 { _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD, &IOp.WiFi_Password, &ui_Textarea__Communications__WiFi_Password, (void*) &ui_Keyboard__Communications__WiFi_AuthenticationDataEntry, NULL },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.WiFiConnectionDetails, &ui_Roller__Communications__WiFi_SecurityType, _GUI_valueConverter_getWiFiSecurityType, _GUI_valueConverter_setWiFiSecurityType },
 { _GUI_SUBJECT_TYPE__UINT8, &_GUI.WiFi_HiddenNetwork, &ui_Switch__Communications__WiFi_ConnectToHiddenNetwork, NULL, NULL },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.WiFiSettings, &ui_Checkbox__Communications__WiFi_AutomaticConnection, _GUI_valueConverter_getWiFiAutomaticConnection, _GUI_valueConverter_setWiFiAutomaticConnection },
 { _GUI_SUBJECT_TYPE__UINT8P, &IOp.RemoteControlRights, &ui_Switch__Communications__WiFi_RemoteControl, _GUI_valueConverter_getWiFiRemoteControl, _GUI_valueConverter_setWiFiRemoteControl },
 { _GUI_SUBJECT_TYPE__END, NULL, NULL, NULL, NULL }
};



void _GUI_clicked__Button__Communications__Serial (lv_event_t* event) { _GUI_showSubscreen__Communications__Serial(); }

void _GUI_clicked__Button__Communications__Ethernet (lv_event_t* event) { _GUI_showSubscreen__Communications__Ethernet(); }

void _GUI_clicked__Button__Communications__WiFi (lv_event_t* event) { _GUI_showSubscreen__Communications__WiFi(); }

void _GUI_clicked__Button__Communications__WiFi_Connect (lv_event_t* event) {
    _GUI_triggerEvent( _GUI_TO_BACKEND_EVENT__Communications__WiFi_Connect );
}

void _GUI_clicked__Button__Communications__WiFi_ForgetConnection (lv_event_t* event) {
    _GUI_triggerEvent( _GUI_TO_BACKEND_EVENT__Communications__WiFi_ForgetConnection );
}


void _GUI_changed__Roller__Communications__WiFi_SSIDlist (lv_event_t* event) {
    int SelectedIndex = _GUI_getSelectorIndex( ui_Roller__Communications__WiFi_SSIDlist );
    strcpy( (char*) IOp.WiFi_SSID, _GUI_getSelectorOption( ui_Roller__Communications__WiFi_SSIDlist ) );
    //strcpy( (char*) IOp.WiFi_Password, IOp.WiFiPasswords[ SelectedIndex ] ); //no saved password array in backend?
    *IOp.WiFiConnectionDetails = IOp.WiFiConnectionList_NetworkDetails[ SelectedIndex ];
    _GUI_refreshScreenModifiers( _GUI_Modifiers__Communications );
}



void _GUI_showSubscreen__Communications__Serial () {
    _GUI_conditionalShowWidget( ui_Container__Communications__Serial_Content,   true  ); _GUI_setWidgetCheckedState( ui_Button__Communications__Serial,   true  );
    _GUI_conditionalShowWidget( ui_Container__Communications__Ethernet_Content, false ); _GUI_setWidgetCheckedState( ui_Button__Communications__Ethernet, false );
    _GUI_conditionalShowWidget( ui_Container__Communications__WiFi_Content,     false ); _GUI_setWidgetCheckedState( ui_Button__Communications__WiFi,     false );
    _GUI_hideWidget( ui_Keyboard__Communications__WiFi_AuthenticationDataEntry );
}

void _GUI_showSubscreen__Communications__Ethernet () {
    _GUI_conditionalShowWidget( ui_Container__Communications__Serial_Content,   false ); _GUI_setWidgetCheckedState( ui_Button__Communications__Serial,   false );
    _GUI_conditionalShowWidget( ui_Container__Communications__Ethernet_Content, true  ); _GUI_setWidgetCheckedState( ui_Button__Communications__Ethernet, true  );
    _GUI_conditionalShowWidget( ui_Container__Communications__WiFi_Content,     false ); _GUI_setWidgetCheckedState( ui_Button__Communications__WiFi,     false );
    _GUI_hideWidget( ui_Keyboard__Communications__WiFi_AuthenticationDataEntry );
    lv_keyboard_set_textarea( ui_Keyboard__Communications__Ethernet_IPAddressEntry, NULL );
}

void _GUI_showSubscreen__Communications__WiFi () {
    _GUI_conditionalShowWidget( ui_Container__Communications__Serial_Content,   false ); _GUI_setWidgetCheckedState( ui_Button__Communications__Serial,   false );
    _GUI_conditionalShowWidget( ui_Container__Communications__Ethernet_Content, false ); _GUI_setWidgetCheckedState( ui_Button__Communications__Ethernet, false );
    _GUI_conditionalShowWidget( ui_Container__Communications__WiFi_Content,     true  ); _GUI_setWidgetCheckedState( ui_Button__Communications__WiFi,     true  );
    _GUI_hideWidget( ui_Keyboard__Communications__WiFi_AuthenticationDataEntry );
}



