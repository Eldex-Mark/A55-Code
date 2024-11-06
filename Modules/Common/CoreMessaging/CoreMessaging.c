
#include <stdio.h> //for printf(), etc.
#include <stdint.h>
#include <stdbool.h>

#include "CoreMessaging.h"


static CoreMessaging_EndPoint CoreMessaging_EndPoints [COREMESSAGING_ENDPOINT_AMOUNT];



__attribute__((always_inline))
static inline CoreMessaging_VariableTypes CoreMessaging_getTypeClass (CoreMessaging_VariableTypes type) {
    if ( /*COREMESSAGING_VARIABLE_TYPE__INT__START < type &&*/ type < COREMESSAGING_VARIABLE_TYPE__INT__END) {
        return COREMESSAGING_VARIABLE_TYPE_CATEGORY__INT;
    }
    else { //if ( COREMESSAGING_VARIABLE_TYPE__FLOAT__START < type && type < COREMESSAGING_VARIABLE_TYPE__FLOAT__END) {
        return COREMESSAGING_VARIABLE_TYPE_CATEGORY__FLOAT;
    }
}


__attribute__((always_inline))
static inline CoreMessaging_ValueContainer CoreMessaging_castVariableToValue (CoreMessaging_VariableTypes type, void* variable_pointer) {
    static CoreMessaging_ValueContainer ValueContainer;
    if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__INT ) {
        switch (type) { //might take advantage of computed goto for faster operation
            case COREMESSAGING_VARIABLE_TYPE__BOOL:    ValueContainer.Int =  * (bool*)     variable_pointer;  break;
            case COREMESSAGING_VARIABLE_TYPE__INT8:    ValueContainer.Int =  * (int8_t*)   variable_pointer;  break;
            case COREMESSAGING_VARIABLE_TYPE__UINT8:   ValueContainer.Int =  * (uint8_t*)  variable_pointer;  break;
            case COREMESSAGING_VARIABLE_TYPE__INT16:   ValueContainer.Int =  * (int16_t*)  variable_pointer;  break;
            case COREMESSAGING_VARIABLE_TYPE__UINT16:  ValueContainer.Int =  * (uint16_t*) variable_pointer;  break;
            case COREMESSAGING_VARIABLE_TYPE__INT32:   ValueContainer.Int =  * (int32_t*)  variable_pointer;  break;
            case COREMESSAGING_VARIABLE_TYPE__UINT32:  ValueContainer.Uint =  * (uint32_t*) variable_pointer;  break;
            default: break;
        }
    }
    else { //if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__FLOAT ) {
       #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
        if (type == COREMESSAGING_VARIABLE_TYPE__FLOAT)
       #endif
        { ValueContainer.Float = * (float*) variable_pointer; }
       #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
        else { //if (type == COREMESSAGING_VARIABLE_TYPE__DOUBLE)
            ValueContainer.Double = * (double*) variable_pointer;
        }
       #endif
    }
    return ValueContainer;
}


__attribute__((always_inline))
static inline void CoreMessaging_castValueToVariable (CoreMessaging_VariableTypes type, CoreMessaging_ValueContainer value, void* variable_pointer) {
    if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__INT ) {
        switch (type) { //might take advantage of computed goto for faster operation
            case COREMESSAGING_VARIABLE_TYPE__BOOL:    * (bool*)     variable_pointer  =  (bool)     value.Int;  break;
            case COREMESSAGING_VARIABLE_TYPE__INT8:    * (int8_t*)   variable_pointer  =  (int8_t)   value.Int;  break;
            case COREMESSAGING_VARIABLE_TYPE__UINT8:   * (uint8_t*)  variable_pointer  =  (uint8_t)  value.Int;  break;
            case COREMESSAGING_VARIABLE_TYPE__INT16:   * (int16_t*)  variable_pointer  =  (int16_t)  value.Int;  break;
            case COREMESSAGING_VARIABLE_TYPE__UINT16:  * (uint16_t*) variable_pointer  =  (uint16_t) value.Int;  break;
            case COREMESSAGING_VARIABLE_TYPE__INT32:   * (int32_t*)  variable_pointer  =  (int32_t)  value.Int;  break;
            case COREMESSAGING_VARIABLE_TYPE__UINT32:  * (uint32_t*) variable_pointer  =  (uint32_t) value.Uint;  break;
            default: break;
        }
    }
    else { //if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__FLOAT ) {
        switch (type) { //might take advantage of computed goto for faster operation
            case COREMESSAGING_VARIABLE_TYPE__FLOAT:   * (float*)    variable_pointer  =  (float)    value.Float;  break;
           #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
            case COREMESSAGING_VARIABLE_TYPE__DOUBLE:  * (double*)   variable_pointer  =  (double)   value.Double;  break;
           #endif
            default: break;
        }
    }
}


__attribute__((always_inline))
static inline bool CoreMessaging_checkValueChange ( CoreMessaging_VariableTypes type, CoreMessaging_ValueContainer current_value, CoreMessaging_ValueContainer* previous_value__pointer ) {
    if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__INT ) {
        if (current_value.Uint != previous_value__pointer->Uint) {  previous_value__pointer->Uint = current_value.Uint; return true; } //equality-test with int32_t/uint32_t should work regardless of signed/unsigned nature (same bits compared by CPU)
    }
    else { //if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__FLOAT ) {
       #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
        if (type == COREMESSAGING_VARIABLE_TYPE__FLOAT)
       #endif
        { if (current_value.Float != previous_value__pointer->Float) { previous_value__pointer->Float = current_value.Float; return true; } }
       #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
        else { //if (type == COREMESSAGING_VARIABLE_TYPE__DOUBLE)
            if (current_value.Double != previous_value__pointer->Double) { previous_value__pointer->Double = current_value.Double; return true; }
        }
       #endif
    }
    return false;
}


__attribute__((always_inline))
static inline void CoreMessaging_sendValue (int variable_index, CoreMessaging_VariableTypes type, CoreMessaging_ValueContainer value, int target_endpoint_index) {
    static CoreMessaging_VariableDescriptor* TargetEndpoint;  //printf("Sending value %d to variable at index %d at endpoint %d\n", value.Int, variable_index, target_endpoint_index );
    TargetEndpoint = CoreMessaging_EndPoints[ target_endpoint_index ];
   #if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )  //for now we don't want segfault with an uninitialized array of a single core
    CoreMessaging_castValueToVariable( type, value, TargetEndpoint[ variable_index ].Pointer );
    TargetEndpoint[ variable_index ].PreviousValue = value; //avoid triggering of a false 'change' at the endpoint
   #endif
}



void CoreMessaging_init (CoreMessaging_VariableDescriptor* value_descriptors, int endpoint_index) {
    CoreMessaging_EndPoints[ endpoint_index ] = value_descriptors;
    for (int i=0; value_descriptors[i].Type != COREMESSAGING_VARIABLE_TYPE__END; ++i) {
        //for (j=0; j < value_descriptors[i].Count; ++j) {
            CoreMessaging_castValueToVariable( value_descriptors[i].Type, value_descriptors[i].PreviousValue, value_descriptors[i].Pointer ); //value_descriptors[i].PreviousValue = CoreMessaging_castVariableToValue( value_descriptors[i].Type, value_descriptors[i].Pointer ); //The other way round? (Backend initializes the same variables on both sides.)
        //}
    }
}


void CoreMessaging_refresh (CoreMessaging_VariableDescriptor* value_descriptors, int target_endpoint_index) {
    static CoreMessaging_ValueContainer CurrentValue;
    for (int i=0; value_descriptors[i].Type != COREMESSAGING_VARIABLE_TYPE__END; ++i) {
        //for (j=0; j < value_descriptors[i].Count; ++j) {
            CurrentValue = CoreMessaging_castVariableToValue( value_descriptors[i].Type, value_descriptors[i].Pointer );
            if ( CoreMessaging_checkValueChange( value_descriptors[i].Type, CurrentValue, &value_descriptors[i].PreviousValue ) ) {
                CoreMessaging_sendValue( i, value_descriptors[i].Type, CurrentValue, target_endpoint_index );
            }
        //}
    }
}


