/*
 * Copyright (c) 2019-2020 Renesas Electronics Europe Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
 
/*
    BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER.

    Note1:  This driver is used specifically to provide an interface to the
    FreeRTOS+CLI command interpreter.  It is *not* intended to be a generic
    serial port driver.  Nor is it intended to be used as an example of an
    efficient implementation.  In particular, a queue is used to buffer
    received characters, which is fine in this case as key presses arrive
    slowly, but a DMA and/or RAM buffer should be used in place of the queue in
    applications that expect higher throughput.

    Note2:  This driver does not attempt to handle UART errors.
*/

#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include "hal_data.h"
#include "mbed_printf_implementation.h"


#define SCIF_FIFO_DEPTH 16

extern uint32_t console_init(void);

/*----------------------------------------------------------------------------*/
static uint32_t xSerialPortInitialized = 0;
static uint32_t flag_tend = 1;

static void prvUART_Handler(void);

static void uart_callback(uart_callback_args_t *const p_arg)
{
    if (p_arg->event & UART_EVENT_RX_COMPLETE)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_TX_COMPLETE)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_RX_CHAR)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_ERR_PARITY)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_ERR_FRAMING)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_ERR_OVERFLOW)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_BREAK_DETECT)
    {
        __NOP();
    }
    if (p_arg->event & UART_EVENT_TX_DATA_EMPTY)
    {
        flag_tend = 1;
    }
}

/*----------------------------------------------------------------------------*/
static void outbyte1(console_t console, char c)
{
    flag_tend = 0;
    g_uart2.p_api->write(g_uart2.p_ctrl, &c, 1);
    while(flag_tend == 0)
    {
        __WFI();
    }
}

void outbyte(console_t console, char c)
{
    if (!xSerialPortInitialized)
    {
        g_uart2.p_api->open(g_uart2.p_ctrl, g_uart2.p_cfg);
        g_uart2.p_api->callbackSet(g_uart2.p_ctrl, uart_callback, NULL, NULL);
        xSerialPortInitialized = 1;
    }

    /* Standard practice to convert \n to \r\n */
    if (c == '\n')
        outbyte1(console, '\r');

    outbyte1(console, c);
}

/* Use a mutex around printf to avoid output from multiple threads mixed */
static char printf_initialised;
static SemaphoreHandle_t xSemaphore;
static StaticSemaphore_t xMutexBuffer;

int printf(const char *format, ...)
{
    console_t console;
    va_list args;
    int ret;

    if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING) {
        /* Force the output to be unbuffered */
        console = CONSOLE_RAW;
        va_start(args, format);
        ret = mbed_minimal_formatted_string(NULL, LONG_MAX, format, args, console);
        va_end(args);
    } else {
        ret = 0;
    }

    return ret;
}

int printf_buff(const char *format, ...)
{
    console_t console;
    va_list args;
    int ret;

    if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING) {
        /* Force the output to be unbuffered */
        console = CONSOLE_RAW;
        va_start(args, format);
        ret = mbed_minimal_formatted_string(NULL, LONG_MAX, format, args, console);
        va_end(args);
    } else {
        if (!printf_initialised) {
            printf_initialised = 1;
            xSemaphore = xSemaphoreCreateMutexStatic(&xMutexBuffer);
        }

        console = CONSOLE_BUFFERED;
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        va_start(args, format);
        ret = mbed_minimal_formatted_string(NULL, LONG_MAX, format, args, console);
        va_end(args);
        xSemaphoreGive(xSemaphore);
    }

    return ret;
}

/*
 * Special version of printf that does not use any OS resources, it's just sends
 * characters out, blocking until the hardware has accepted all of them.
 */
int printf_raw(const char *format, ...)
{
    console_t console = CONSOLE_RAW;
    va_list args;
    int ret;

    va_start(args, format);
    ret = mbed_minimal_formatted_string(NULL, LONG_MAX, format, args, console);
    va_end(args);

    return ret;
}


int sprintf(char *buffer, const char *format, ...)
{
    console_t console = CONSOLE_CONVERSION;
    va_list args;
    int ret;

    va_start(args, format);
    ret = mbed_minimal_formatted_string(buffer, LONG_MAX, format, args, console);
    va_end(args);

    return ret;
    
}

int snprintf(char *buffer, size_t length, const char *format, ...)
{
    console_t console = CONSOLE_CONVERSION;
    va_list args;
    int ret;

    va_start(args, format);
    ret = mbed_minimal_formatted_string(buffer, length, format, args, console);
    va_end(args);

    return ret;
    
}

