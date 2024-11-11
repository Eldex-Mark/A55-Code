//public header


#ifndef _GUI_TOOLKIT_OBSERVERMODIFIER_INCLUDED
#define _GUI_TOOLKIT_OBSERVERMODIFIER_INCLUDED



#include <stdint.h>
#include <stdbool.h>
#include <lvgl/lvgl.h>



typedef enum {
    _GUI_SUBJECT_TYPE__END = 0,

    _GUI_SUBJECT_TYPE_CATEGORY__INT,
    _GUI_SUBJECT_TYPE__INT__START, //MIN,
    _GUI_SUBJECT_TYPE__BOOL, // = _GUI_SUBJECT_TYPE__INT__MIN
    _GUI_SUBJECT_TYPE__UINT8, // = _GUI_SUBJECT_TYPE__INT__MIN
    _GUI_SUBJECT_TYPE__UINT16,
    _GUI_SUBJECT_TYPE__UINT32,
    _GUI_SUBJECT_TYPE__INT__END, //MAX = _GUI_SUBJECT_TYPE__UINT32
    _GUI_SUBJECT_TYPE_CATEGORY__INTP,  //pointers to ints
    _GUI_SUBJECT_TYPE__INTP__START, //MIN,
    _GUI_SUBJECT_TYPE__UINT8P, // = _GUI_SUBJECT_TYPE__INTP__MIN
    _GUI_SUBJECT_TYPE__UINT16P,
    _GUI_SUBJECT_TYPE__UINT32P,
    _GUI_SUBJECT_TYPE__INTP__END, //MAX = _GUI_SUBJECT_TYPE__UINT32P

    _GUI_SUBJECT_TYPE_CATEGORY__FLOAT,
    _GUI_SUBJECT_TYPE__FLOAT_START, //MIN,
    _GUI_SUBJECT_TYPE__FLOAT, // = _GUI_SUBJECT_TYPE__FLOAT__MIN
    _GUI_SUBJECT_TYPE__DOUBLE,
    _GUI_SUBJECT_TYPE__FLOAT__END, //MAX = _GUI_SUBJECT_TYPE__DOUBLE
    _GUI_SUBJECT_TYPE_CATEGORY__FLOATP,  //pointers to floats/doubles
    _GUI_SUBJECT_TYPE__FLOATP_START, //MIN,
    _GUI_SUBJECT_TYPE__FLOATP, // = _GUI_SUBJECT_TYPE__FLOATP__MIN
    _GUI_SUBJECT_TYPE__DOUBLEP,
    _GUI_SUBJECT_TYPE__FLOATP__END, //MAX = _GUI_SUBJECT_TYPE__DOUBLEP

    _GUI_SUBJECT_TYPE_CATEGORY__STRING,
    _GUI_SUBJECT_TYPE__STRING_START,
    _GUI_SUBJECT_TYPE__STRING, //static (constant) string-pointer
    _GUI_SUBJECT_TYPE__STRINGP, //static (constant) string-pointer-pointer
    _GUI_SUBJECT_TYPE__STRINGP_OTHERKEYBOARD, //workaround to assign a keyboard other than the 1st one found on the screen
    _GUI_SUBJECT_TYPE__STRINGARRAYP, //has the size of a single element in 'previous value' field
    _GUI_SUBJECT_TYPE__ARRAY,  //array address
    _GUI_SUBJECT_TYPE__ARRAYP,  //array-pointer address
    _GUI_SUBJECT_TYPE__ARRAY_NOHIDE, //a workaround not to hide keyboard for this input-type (so no need to have a specific field in descriptor)
    _GUI_SUBJECT_TYPE__POINTER, //changing string/etc-pointer
    _GUI_SUBJECT_TYPE__STRING_END,

    //extras for observers:
    _GUI_SUBJECT_TYPE_CATEGORY__IGNORE, //if for example the input type/variable mismatches (when more variable-subjects are attached to a single observer-widget), ignore the non-relevant ones
    //extras for modifiers:
    _GUI_SUBJECT_TYPE_CATEGORY__CUSTOMWRITE, //for bitfields that are written by custom modifier function
    _GUI_SUBJECT_TYPE_CATEGORY__POSTCALL, //custom call after setting the variable with modifier

} _GUI_SubjectVariableTypes;


typedef enum { //to override default? - but formatting string already does that
    _GUI_DISPLAYED_TYPE__NONE = 0,
    _GUI_DISPLAYED_TYPE__NORMAL,
    _GUI_DISPLAYED_TYPE__PLACEHOLDER,
    _GUI_DISPLAYED_TYPE__SHOW_HIDE, //BOOL
    _GUI_DISPLAYED_TYPE__DISABLE, //BOOL
    //_GUI_DISPLAYED_TYPE__STRING, //string-pointer coming from converter
    //_GUI_DISPLAYED_TYPE__INNERLABEL,
    //_GUI_DISPLAYED_TYPE__INT,
    //_GUI_DISPLAYED_TYPE__FLOAT,
    //_GUI_DISPLAYED_TYPE__PERCENTAGE,
} _GUI_DisplayedTypes;


typedef  int32_t /*long long int*/ Int;  //used for conversion, should be the biggest-sized type that's representated by the project, that also handles signedness
typedef  double /*long double*/ Float;  //used for conversion, should be the biggest-sized type that's representated by the project

typedef union { //_GUI_ValueContainer {
    Int/*int32_t*/ Int;  Int/*uint32_t*/ Uint; //bool Bool; //used for conversion, should be the biggest-sized type that's representated by the project, that also handles signedness  //if value is bigger then maximum positive, it can lead to problems with signedness, that's why uint32_t is added
    float /*Float*/ Float; //used for conversion, should be the biggest-sized type that's representated by the project
    double /*Float*/ Double;  //Double and float shouldn't be equality tested due to their different representations and precisions
    void* Pointer; //for strings, but if it's a string at static address its content should be scanned through about changes
} _GUI_ValueContainer; //for checking changes (makes enough space for any type)


#define _GUI_HEADER_valueConverterFunction(FunctionName) _GUI_ValueContainer FunctionName (_GUI_SubjectVariableTypes input_type, _GUI_ValueContainer input_value, _GUI_SubjectVariableTypes* output_type)
typedef _GUI_HEADER_valueConverterFunction(_GUI_valueConverterFunction);


typedef struct { //_GUI_Observer {  //this struct must be public because it's used in arrays and size must be known
    _GUI_SubjectVariableTypes VariableType;
    const void *const         VariablePointer; //_pointer;
    lv_obj_t* *const          WidgetPointer_pointer;
    _GUI_valueConverterFunction* converterFunction; //_GUI_ValueContainer (*converterFunction) (_GUI_SubjectVariableTypes input_type, _GUI_ValueContainer input_value, _GUI_SubjectVariableTypes* output_type);  //_GUI_ConversionTypes      ConversionType; //conversion
    const char *const         FormatString_pointer; //further formatting of the displayed type and maybe adding prefix/postfix
    _GUI_DisplayedTypes       DisplayedType;
    _GUI_ValueContainer       PreviousValue; //(it's a pointer to a previous-value string array in case of static-address string)
} _GUI_Observer;

typedef struct { //_GUI_Modifier {  //this struct must be public because it's used in arrays and size must be known
    _GUI_SubjectVariableTypes VariableType;
    const void *const         VariablePointer; //_pointer;
    lv_obj_t* *const          WidgetPointer_pointer;   //for textareas it's better (?) not to use their value-callback but assigned keyboards 'ready': keyboard found on the screen is assigned automatically (works well if there's only 1 keyboard on the screen)
    _GUI_valueConverterFunction* inputConverter; //for processing the variable
    _GUI_valueConverterFunction* outputConverter; //for modifying the variable
} _GUI_Modifier;



void _GUI_initScreenObservers (_GUI_Observer* observer_array);
void _GUI_refreshScreenObservers (_GUI_Observer* observer_array, bool force_refresh);

void _GUI_refreshModifierWidget (_GUI_Modifier* modifier);
void _GUI_initScreenModifiers (_GUI_Modifier* modifier_array);
void _GUI_refreshScreenModifiers (_GUI_Modifier* modifier_array);

_GUI_SubjectVariableTypes _GUI_getTypeCategory (_GUI_SubjectVariableTypes type);



#endif //_GUI_TOOLKIT_OBSERVERMODIFIER_INCLUDED

