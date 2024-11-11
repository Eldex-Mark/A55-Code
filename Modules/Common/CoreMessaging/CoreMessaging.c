
#include <stdlib.h> //for malloc(), etc.
#include <stdio.h> //for printf(), etc.
#include <stdint.h>
#include <stdbool.h>
#include <string.h> //for memcpy(), etc.

#include "CoreMessaging.h"
#if ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 )
 #include "CoreM33_CoreMessaging.h"
#elif ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) && SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 )
 #include "CoreA55_CoreMessaging.h"
#endif



static CoreMessaging_EndPointDescriptor CoreMessaging_EndPoints [COREMESSAGING_ENDPOINT_AMOUNT];

static CoreMessaging_EventDescriptor CoreMessaging_Events [COREMESSAGING_ENDPOINT_AMOUNT] [COREMESSAGING_EVENT_AMOUNT_MAX];

static uint8_t CoreMessaging_Incoming_Message [COREMESSAGING_MESSAGE_SIZE_MAX];
static uint8_t CoreMessaging_Outgoing_Message [COREMESSAGING_MESSAGE_SIZE_MAX];

static int CoreMessaging_Incoming_ByteCount = 0;
static int CoreMessaging_Outgoing_ByteCount = 0;



//Serializing variables/arrays/events for inter-CPU messaging:
#if ( ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) || ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) && SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )
__attribute__((always_inline)) static inline void CoreMessaging_appendMessage (uint8_t value ) { CoreMessaging_Outgoing_Message[ CoreMessaging_Outgoing_ByteCount++ ] = value; }
#endif



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
static inline size_t CoreMessaging_castValueToVariable (CoreMessaging_VariableTypes type, CoreMessaging_ValueContainer value, void* variable_pointer) {
    if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__INT ) {
        switch (type) { //might take advantage of computed goto for faster operation
            case COREMESSAGING_VARIABLE_TYPE__BOOL:    if (variable_pointer!=NULL)  * (bool*)     variable_pointer  =  (bool)     value.Int;  return sizeof( bool );
            case COREMESSAGING_VARIABLE_TYPE__INT8:    if (variable_pointer!=NULL)  * (int8_t*)   variable_pointer  =  (int8_t)   value.Int;  return sizeof( int8_t );
            case COREMESSAGING_VARIABLE_TYPE__UINT8:   if (variable_pointer!=NULL)  * (uint8_t*)  variable_pointer  =  (uint8_t)  value.Int;  return sizeof( uint8_t );
            case COREMESSAGING_VARIABLE_TYPE__INT16:   if (variable_pointer!=NULL)  * (int16_t*)  variable_pointer  =  (int16_t)  value.Int;  return sizeof( int16_t );
            case COREMESSAGING_VARIABLE_TYPE__UINT16:  if (variable_pointer!=NULL)  * (uint16_t*) variable_pointer  =  (uint16_t) value.Int;  return sizeof( uint16_t );
            case COREMESSAGING_VARIABLE_TYPE__INT32:   if (variable_pointer!=NULL)  * (int32_t*)  variable_pointer  =  (int32_t)  value.Int;  return sizeof( int32_t );
            case COREMESSAGING_VARIABLE_TYPE__UINT32:  if (variable_pointer!=NULL)  * (uint32_t*) variable_pointer  =  (uint32_t) value.Uint;  return sizeof( uint32_t );
            default: break;
        }
    }
    else { //if ( CoreMessaging_getTypeClass( type ) == COREMESSAGING_VARIABLE_TYPE_CATEGORY__FLOAT ) {
        switch (type) { //might take advantage of computed goto for faster operation
            case COREMESSAGING_VARIABLE_TYPE__FLOAT:   if (variable_pointer!=NULL)  * (float*)    variable_pointer  =  (float)    value.Float;  return sizeof( float );
           #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
            case COREMESSAGING_VARIABLE_TYPE__DOUBLE:  if (variable_pointer!=NULL)  * (double*)   variable_pointer  =  (double)   value.Double;  return sizeof( double );
           #endif
            default: break;
        }
    }
    return 0; //keep GCC satisfied
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
   #if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )  //for now we don't want segfault with an uninitialized array of a single core
    static CoreMessaging_VariableDescriptor* TargetVariables;  //printf("Sending value %d to variable at index %d at endpoint %d\n", value.Int, variable_index, target_endpoint_index );
    TargetVariables = CoreMessaging_EndPoints[ target_endpoint_index ].Variables;
    CoreMessaging_castValueToVariable( type, value, TargetVariables[ variable_index ].VariablePointer );
    TargetVariables[ variable_index ].PreviousValue = value; //avoid triggering of a false 'change' at the endpoint
   #else
    CoreMessaging_appendMessage( COREMESSAGING_COMMAND__SET_VARIABLE ); CoreMessaging_appendMessage( variable_index ); //CoreMessaging_appendMessage( value );
   #endif
}


__attribute__((always_inline))
static inline int CoreMessaging_checkArrayChange ( CoreMessaging_VariableDescriptor* variable_descriptors, int index, size_t array_size ) {
    static size_t j;
    for (j=0; j < array_size; ++j) { //detect for change
        if ( ( (uint8_t*) variable_descriptors[ index ].VariablePointer )[ j ] != ( (uint8_t*) variable_descriptors[ index ].PreviousValue.Pointer )[ j ] ) return j;
    }
    return -1;
}

__attribute__((always_inline))
static inline void CoreMessaging_sendArray (CoreMessaging_VariableDescriptor* variable_descriptors, int index, size_t start_index, size_t array_size, int target_endpoint_index) {
    static size_t j;
   #if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )  //for now we don't want segfault with an uninitialized array of a single core
    static CoreMessaging_VariableDescriptor* TargetVariables;
    TargetVariables = CoreMessaging_EndPoints[ target_endpoint_index ].Variables;
   #else
    CoreMessaging_appendMessage( COREMESSAGING_COMMAND__SET_VARIABLE ); CoreMessaging_appendMessage( index );
   #endif
    for (j = start_index /*0*/; j < array_size; ++j) { //update starting from the changed point
       #if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )  //for now we don't want segfault with an uninitialized array of a single core
        ( (uint8_t*) TargetVariables[ index ].VariablePointer )[ j ] =
       #else
        //CoreMessaging_appendMessage( value );
       #endif
        ( (uint8_t*) variable_descriptors[ index ].PreviousValue.Pointer )[ j ] = ( (uint8_t*) variable_descriptors[ index ].VariablePointer )[ j ]; //refresh array (or changed part of array if possible);
    }
}


void CoreMessaging_bindEventFunction (int event_id, CoreMessaging_callbackFunction callback_function, int endpoint_index) { //void (*callback_function)() ) {
    CoreMessaging_EndPoints[ endpoint_index ].Events[ event_id ].callbackFunction = callback_function;
}

__attribute__((always_inline))
static inline bool CoreMessaging_checkEventReceipt (int event_index, int endpoint_index) {
    static CoreMessaging_EventDescriptor *Event;
    Event = &CoreMessaging_EndPoints[ endpoint_index ].Events[ event_index ];
    if (Event->Triggered) { Event->Triggered = false; return true; }  else return false;
}

__attribute__((always_inline))
inline void CoreMessaging_sendEvent (int event_id, int target_endpoint_index) {
   #if ( ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) && ( !defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) || !SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )  //for now we don't want segfault with an uninitialized array of a single core
    static CoreMessaging_EventDescriptor* TargetEvents;
    TargetEvents = CoreMessaging_EndPoints[ target_endpoint_index ].Events;
    TargetEvents[ event_id ].Triggered = true;
   #else
    CoreMessaging_appendMessage( COREMESSAGING_COMMAND__SEND_EVENT ); CoreMessaging_appendMessage( event_id );
   #endif
}

void CoreMessaging_callEvent (int event_id, int endpoint_index) { //for now no parameters are requested for the events
    static CoreMessaging_EventDescriptor Event;
    Event = CoreMessaging_EndPoints[ endpoint_index ].Events[ event_id ];
    if (Event.callbackFunction != NULL) ( Event.callbackFunction ) (); //call a local callback directly if registered
    //CoreMessaging_sendEvent( event_id, target_endpoint_index ); //message to the other core implicitly
}

void CoreMessaging_broadcastEvent (int event_id) { //send to all cores, and who has a non-NULL function-binding for the event_id, will call that function
    for (int i=0; i<COREMESSAGING_ENDPOINT_AMOUNT; ++i) CoreMessaging_sendEvent( event_id, i );
}



void CoreMessaging_init (CoreMessaging_VariableDescriptor* variable_descriptors, int endpoint_index) {
    static size_t ElementSize;

   #if ( ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) || ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) && SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )
    CoreMessagingDriver_init();
   #endif

    CoreMessaging_EndPoints[ endpoint_index ].Variables = variable_descriptors;
    for (int i=0; variable_descriptors[i].Type != COREMESSAGING_VARIABLE_TYPE__END; ++i) {
        if (variable_descriptors[i].Count <= 1) CoreMessaging_castValueToVariable( variable_descriptors[i].Type, variable_descriptors[i].PreviousValue, variable_descriptors[i].VariablePointer ); //variable_descriptors[i].PreviousValue = CoreMessaging_castVariableToValue( variable_descriptors[i].Type, variable_descriptors[i].VariablePointer ); //The other way round? (Backend initializes the same variables on both sides.)
        else {
            ElementSize = CoreMessaging_castValueToVariable( variable_descriptors[i].Type, variable_descriptors[i].PreviousValue, NULL );
            variable_descriptors[i].PreviousValue.Pointer = (void*) malloc( variable_descriptors[i].Count * ElementSize );
            if (variable_descriptors[i].PreviousValue.Pointer != NULL) memcpy( variable_descriptors[i].PreviousValue.Pointer, variable_descriptors[i].VariablePointer, variable_descriptors[i].Count * ElementSize );
        }
    }
    CoreMessaging_EndPoints[ endpoint_index ].Events = CoreMessaging_Events[ endpoint_index ];
    for (int i=0; i < COREMESSAGING_EVENT_AMOUNT; ++i) {
        CoreMessaging_EventDescriptor Event = CoreMessaging_EndPoints[ endpoint_index ].Events[ i ];
        Event.callbackFunction = NULL; Event.Triggered = false;
    }
}


void CoreMessaging_refresh (CoreMessaging_VariableDescriptor* variable_descriptors, int endpoint_index, int target_endpoint_index) {
    static int i, ChangeIndex;
    static size_t ArraySize;
    static CoreMessaging_ValueContainer CurrentValue;

    CoreMessaging_Outgoing_ByteCount = 0; //2; leave place for upcoming 'message-size' bytes, if messaging protocol doesn't add it or send length/delimiter

    for (i=0; variable_descriptors[i].Type != COREMESSAGING_VARIABLE_TYPE__END; ++i) {
        if (variable_descriptors[i].Count <= 1) { //check if single value changed
            CurrentValue = CoreMessaging_castVariableToValue( variable_descriptors[i].Type, variable_descriptors[i].VariablePointer );
            if ( CoreMessaging_checkValueChange( variable_descriptors[i].Type, CurrentValue, &variable_descriptors[i].PreviousValue ) ) {
                CoreMessaging_sendValue( i, variable_descriptors[i].Type, CurrentValue, target_endpoint_index );
            }
        }
        else { //check if any element of an array changed, if yes, send the changed portion (or full array at least)
            ArraySize = (size_t) variable_descriptors[i].Count * CoreMessaging_castValueToVariable( variable_descriptors[i].Type, variable_descriptors[i].PreviousValue, NULL ); //get array-size in bytes
            if ( ( ChangeIndex = CoreMessaging_checkArrayChange( variable_descriptors, i, ArraySize ) ) >= 0 ) {
                CoreMessaging_sendArray( variable_descriptors, i, ChangeIndex, ArraySize, target_endpoint_index );
            }
        }
    }
    for (i=0; i < COREMESSAGING_EVENT_AMOUNT; ++i) {
        if ( CoreMessaging_checkEventReceipt( i, endpoint_index ) ) CoreMessaging_callEvent( i, endpoint_index );
    }

   #if ( ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_M33) && SQUARELINE_BUILD_TARGET__BOARD__CORE_M33 ) || ( defined(SQUARELINE_BUILD_TARGET__BOARD__CORE_A55) && SQUARELINE_BUILD_TARGET__BOARD__CORE_A55 ) )
    CoreMessagingDriver_refresh();
   #endif
}



