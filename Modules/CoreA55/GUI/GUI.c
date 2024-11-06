//Public GUI-interface (Application-to-GUI) implementation (GUI initialization and main cyclic refresher, etc.)

#include "GUI_unified.h"



void GUI_init (int input_id, int framebuffer_id) {
    _GUI_init_Main( input_id, framebuffer_id );
}


void GUI_refresh () { //called periodically from the application
    _GUI_refresh_Main();
}


