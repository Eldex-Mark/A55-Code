
#include "CoreMessagingTask.h"



extern void app_CoreMessagingTask (void* pvParameters);



void CoreMessagingTask_entry (void *pvParameters) {

    app_CoreMessagingTask( pvParameters );

    vTaskDelete( NULL );
}

