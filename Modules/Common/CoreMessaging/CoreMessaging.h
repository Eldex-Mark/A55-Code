//public header

#include <stdint.h> //to determine size of biggest uint32_t-style variable-type for change-detection previous value storage
#include <stdbool.h>


#define COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT 0  //Not needed in this project (yet), as it seems


enum {
    COREMESSAGING_ENDPOINT__CORE_M33 = 0,
    COREMESSAGING_ENDPOINT__CORE_A55,
    COREMESSAGING_ENDPOINT_AMOUNT, //must be the last endpoint entry

    COREMESSAGING_EVENT_AMOUNT_MAX = 100,
    COREMESSAGING_EVENT_AMOUNT = COREMESSAGING_EVENT_AMOUNT_MAX //GUI_TO_BACKEND_EVENT__AMOUNT
};


typedef enum { //order of INTs is important for checking INT type
    COREMESSAGING_VARIABLE_TYPE__END = 0,

    COREMESSAGING_VARIABLE_TYPE_CATEGORY__INT,
    COREMESSAGING_VARIABLE_TYPE__INT__START, //MIN,
    COREMESSAGING_VARIABLE_TYPE__BOOL, //= COREMESSAGING_VARIABLE_TYPE__INT__MIN,
    COREMESSAGING_VARIABLE_TYPE__INT8,
    COREMESSAGING_VARIABLE_TYPE__UINT8,
    COREMESSAGING_VARIABLE_TYPE__INT16,
    COREMESSAGING_VARIABLE_TYPE__UINT16,
    COREMESSAGING_VARIABLE_TYPE__INT32,
    COREMESSAGING_VARIABLE_TYPE__UINT32,
    COREMESSAGING_VARIABLE_TYPE__INT__END, //MAX = COREMESSAGING_VARIABLE_TYPE__UINT32,

    COREMESSAGING_VARIABLE_TYPE_CATEGORY__FLOAT,
    COREMESSAGING_VARIABLE_TYPE__FLOAT__START,
    COREMESSAGING_VARIABLE_TYPE__FLOAT,
    COREMESSAGING_VARIABLE_TYPE__DOUBLE,
    COREMESSAGING_VARIABLE_TYPE__FLOAT__END

} CoreMessaging_VariableTypes;


typedef union {
    int32_t/*long long int*/ Int;  uint32_t Uint; //if value is bigger then maximum positive, it can lead to problems with signedness, that's why uint32_t is added
    float/*long double*/ Float;
    #if (COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT)
     double Double;  //Double and float shouldn't be equality tested due to their different representations and precisions
    #endif
    /*uintptr_t*/void* Pointer;  //could be used to point to the array's 'PreviousValues' change-tester
} CoreMessaging_ValueContainer; //for checking changes (makes enough space for any type)

typedef struct {
    const CoreMessaging_VariableTypes Type;
    void *const                       VariablePointer;
    const int                         Count; //1 for simple variables, more for arrays
    CoreMessaging_ValueContainer      PreviousValue; //at init this is loaded to the corresponding variables, i.e. used as initial value for them, with array it's set to point to a same-size prev-values array dynamically created at init
} CoreMessaging_VariableDescriptor;


typedef void (*CoreMessaging_callbackFunction)();

typedef struct {
    CoreMessaging_callbackFunction callbackFunction; //the registered callback-function on a core
    bool                           Triggered; //set to true when a message arrives (later to be replaced by messaging 'Event' command)
} CoreMessaging_EventDescriptor;


typedef struct {
    CoreMessaging_VariableDescriptor* Variables;
    CoreMessaging_EventDescriptor* Events;
} CoreMessaging_EndPointDescriptor;



void CoreMessaging_init (CoreMessaging_VariableDescriptor* value_descriptors, int endpoint_index); //initializes variables to their values given in the value-descriptor table

void CoreMessaging_refresh (CoreMessaging_VariableDescriptor* value_descriptors, int endpoint_index, int target_endpoint_index);


void CoreMessaging_bindEventFunction (int event_id, void (*callback_function)(), int endpoint_index); //bind event to function on current endpoint (core)

void CoreMessaging_sendEvent (int event_id, int target_endpoint_index); //send event to the other endpoint (core)
void CoreMessaging_callEvent (int event_id, int endpoint_index); //call event directly on current enpoint (core)

void CoreMessaging_broadcastEvent (int event_id); //send to all cores, and who has a non-NULL function-binding for the event_id, will call that function (advantage: no need to give endpoint)

