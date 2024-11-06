//public header

#include <stdint.h> //to determine size of biggest uint32_t-style variable-type for change-detection previous value storage


#define COREMESSAGING_VARIABLE_TYPE__DOUBLE__SUPPORT 0  //Not needed in this project (yet), as it seems


enum {
    COREMESSAGING_ENDPOINT__CORE_M33 = 0,
    COREMESSAGING_ENDPOINT__CORE_A55,
    COREMESSAGING_ENDPOINT_AMOUNT //must be the last entry
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
    /*uintptr_t*//*void* Pointer;*/;  //could be used to point to the array's 'PreviousValues' change-tester
} CoreMessaging_ValueContainer; //for checking changes (makes enough space for any type)

typedef struct {
    const CoreMessaging_VariableTypes Type;
    void *const                       Pointer;
    const int                         Count; //1 for simple variables, more for arrays
    CoreMessaging_ValueContainer      PreviousValue; //at init this is loaded to the corresponding variables, i.e. used as initial value for them
} CoreMessaging_VariableDescriptor;

typedef void* CoreMessaging_EndPoint;



void CoreMessaging_init (CoreMessaging_VariableDescriptor* value_descriptors, int endpoint_index); //initializes variables to their values given in the value-descriptor table

void CoreMessaging_refresh (CoreMessaging_VariableDescriptor* value_descriptors, int target_endpoint_index);


