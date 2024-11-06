//App variable-changes that affect GUI widgets



extern _GUI_Observer _GUI_Observers__StartupSplash [];
extern _GUI_Observer _GUI_Observers__Initial_Setup [];
extern _GUI_Observer _GUI_Observers__Select_Option [];
extern _GUI_Observer _GUI_Observers__Generic_Password [];
extern _GUI_Observer _GUI_Observers__Home [];
extern _GUI_Observer _GUI_Observers__Pump_Settings [];
extern _GUI_Observer _GUI_Observers__Advanced_Settings [];
extern _GUI_Observer _GUI_Observers__Firmware_Update [];
extern _GUI_Observer _GUI_Observers__Maintenance [];
extern _GUI_Observer _GUI_Observers__Self_Test [];
extern _GUI_Observer _GUI_Observers__Communications [];



void _GUI_init_SynchOutputs ();
void _GUI_refresh_SynchOutputs ();

