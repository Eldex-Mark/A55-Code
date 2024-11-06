//Common code used by both Observers and Modifiers

#include <stdio.h>

#include "../GUI_Toolkit.h"
#include "../GUI_Toolkit_internal.h"

#include "ObserverModifier.h"
#include "ObserverModifier_internal.h"



inline _GUI_SubjectVariableTypes _GUI_getTypeCategory (_GUI_SubjectVariableTypes type) {
    return (type < _GUI_SUBJECT_TYPE__INTP__END) ? _GUI_SUBJECT_TYPE_CATEGORY__INT : ( type<_GUI_SUBJECT_TYPE__FLOATP__END? _GUI_SUBJECT_TYPE_CATEGORY__FLOAT : _GUI_SUBJECT_TYPE_CATEGORY__STRING );
}


inline void _GUI_setWidgetFormattedText (lv_obj_t* widget, _GUI_DisplayedTypes displayed_type, char* format, ...) {
    va_list args; va_start( args, format ); vsprintf( _GUI_Toolkit_TempString, format, args ); va_end( args );
    if (displayed_type == _GUI_DISPLAYED_TYPE__PLACEHOLDER) _GUI_setWidgetPlaceholderText( widget, _GUI_Toolkit_TempString );
    else _GUI_setWidgetText( widget, _GUI_Toolkit_TempString );
}


