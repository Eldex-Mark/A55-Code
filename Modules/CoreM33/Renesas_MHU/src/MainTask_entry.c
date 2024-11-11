
#include "MainTask.h"



extern void app_MainTask (void* pvParameters);



void MainTask_entry (void* pvParameters) {

    app_MainTask( pvParameters );

    vTaskDelete( NULL );
}

