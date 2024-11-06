//Unified (GUI+Application) topmost-level header-file for inclusion by internal operations


//API towards the lower levels

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include "HAL/HAL.h"
#include "lvgl/lvgl.h"
#include "ui/ui.h"

#include "GUI.h"


//Backend API-header for the GUI
#include "GUI_API.h"


//Pointers used by the Application-to/from-GUI binding (optional but useful feature)

#include "App_bindings.h"

extern struct IOpointers IOp;


#include "GUI_Internal.h"  //Private GUI-specific variables and functions (if exported names are suboptimal, or for dynamically used component-child indexes)

extern struct GUIprivateVariables _GUI;


#include "GUI_Toolkit/GUI_Toolkit.h"


//Inits
#include "GUI_InitScreens/GUI_InitScreens.h"

//Events
#include "GUI_NonSync_GUItoApp/GUI_NonSync_GUItoApp.h"

//Continuous updates
#include "GUI_Synch_AppToGUI/GUI_Synch_AppToGUI.h"

