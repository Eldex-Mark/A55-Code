/* generated thread header file - do not edit */
#ifndef MAINTASK_H_
#define MAINTASK_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void MainTask_entry(void * pvParameters);
                #else
extern void MainTask_entry(void *pvParameters);
#endif
FSP_HEADER
FSP_FOOTER
#endif /* MAINTASK_H_ */
