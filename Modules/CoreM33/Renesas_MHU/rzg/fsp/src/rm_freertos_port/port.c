/*
 * FreeRTOS Kernel V10.4.3
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "hal_data.h"

/* MPU wrappers includes. */
#include "mpu_wrappers.h"

/* Portasm includes. */
#include "portasm.h"

#if (configENABLE_TRUSTZONE == 1)

/* Secure components includes. */
 #include "secure_context.h"
 #include "secure_init.h"
#endif                                 /* configENABLE_TRUSTZONE */

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/**
 * The FreeRTOS Cortex M33 port can be configured to run on the Secure Side only
 * i.e. the processor boots as secure and never jumps to the non-secure side.
 * The Trust Zone support in the port must be disabled in order to run FreeRTOS
 * on the secure side. The following are the valid configuration seetings:
 *
 * 1. Run FreeRTOS on the Secure Side:
 *    configRUN_FREERTOS_SECURE_ONLY = 1 and configENABLE_TRUSTZONE = 0
 *
 * 2. Run FreeRTOS on the Non-Secure Side with Secure Side function call support:
 *    configRUN_FREERTOS_SECURE_ONLY = 0 and configENABLE_TRUSTZONE = 1
 *
 * 3. Run FreeRTOS on the Non-Secure Side only i.e. no Secure Side function call support:
 *    configRUN_FREERTOS_SECURE_ONLY = 0 and configENABLE_TRUSTZONE = 0
 */
#if ((configRUN_FREERTOS_SECURE_ONLY == 1) && (configENABLE_TRUSTZONE == 1))
 #error TrustZone needs to be disabled in order to run FreeRTOS on the Secure Side.
#endif

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#define portNVIC_SHPR2_REG            (*((volatile uint32_t *) 0xe000ed1c))
#define portNVIC_SHPR3_REG            (*((volatile uint32_t *) 0xe000ed20))
#define portMAX_INTERRUPT_PRIORITY    (0UL)
#define portMIN_INTERRUPT_PRIORITY    (255UL)
#define portNVIC_SVC_PRI              (portMAX_INTERRUPT_PRIORITY << 24UL)
#define portNVIC_PENDSV_PRI           (portMIN_INTERRUPT_PRIORITY << 16UL)
#define portNVIC_SYSTICK_PRI          (portMIN_INTERRUPT_PRIORITY << 24UL)
#define portNVIC_SVC_MASK             (unsigned long) (~(0xffUL << 24UL))
#define portNVIC_PENDSV_MASK          (unsigned long) (~(0xffUL << 16UL))
#define portNVIC_SYSTICK_MASK         (unsigned long) (~(0xffUL << 24UL))
#ifndef configSYSTICK_CLOCK_HZ
 #define configSYSTICK_CLOCK_HZ       configCPU_CLOCK_HZ

/* Ensure the SysTick is clocked at the same frequency as the core. */
 #define portNVIC_SYSTICK_CLK_BIT     (1UL << 2UL)
#else

/* The way the SysTick is clocked is not modified in case it is not the
 * same a the core. */
 #define portNVIC_SYSTICK_CLK_BIT     (0)
#endif

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#define portSCB_SYS_HANDLER_CTRL_STATE_REG    (*(volatile uint32_t *) 0xe000ed24)
#define portSCB_MEM_FAULT_ENABLE_BIT          (1UL << 16UL)

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the FPU.
 */
#define portCPACR                             ((volatile uint32_t *) 0xe000ed88) /* Coprocessor Access Control Register. */
#define portCPACR_CP10_VALUE                  (3UL)
#define portCPACR_CP11_VALUE                  portCPACR_CP10_VALUE
#define portCPACR_CP10_POS                    (20UL)
#define portCPACR_CP11_POS                    (22UL)

#define portFPCCR                             ((volatile uint32_t *) 0xe000ef34) /* Floating Point Context Control Register. */
#define portFPCCR_ASPEN_POS                   (31UL)
#define portFPCCR_ASPEN_MASK                  (1UL << portFPCCR_ASPEN_POS)
#define portFPCCR_LSPEN_POS                   (30UL)
#define portFPCCR_LSPEN_MASK                  (1UL << portFPCCR_LSPEN_POS)

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#define portMPU_TYPE_REG                      (*((volatile uint32_t *) 0xe000ed90))
#define portMPU_CTRL_REG                      (*((volatile uint32_t *) 0xe000ed94))
#define portMPU_RNR_REG                       (*((volatile uint32_t *) 0xe000ed98))

#define portMPU_RBAR_REG                      (*((volatile uint32_t *) 0xe000ed9c))
#define portMPU_RLAR_REG                      (*((volatile uint32_t *) 0xe000eda0))

#define portMPU_RBAR_A1_REG                   (*((volatile uint32_t *) 0xe000eda4))
#define portMPU_RLAR_A1_REG                   (*((volatile uint32_t *) 0xe000eda8))

#define portMPU_RBAR_A2_REG                   (*((volatile uint32_t *) 0xe000edac))
#define portMPU_RLAR_A2_REG                   (*((volatile uint32_t *) 0xe000edb0))

#define portMPU_RBAR_A3_REG                   (*((volatile uint32_t *) 0xe000edb4))
#define portMPU_RLAR_A3_REG                   (*((volatile uint32_t *) 0xe000edb8))

#define portMPU_MAIR0_REG                     (*((volatile uint32_t *) 0xe000edc0))
#define portMPU_MAIR1_REG                     (*((volatile uint32_t *) 0xe000edc4))

#define portMPU_RBAR_ADDRESS_MASK             (0xffffffe0) /* Must be 32-byte aligned. */
#define portMPU_RLAR_ADDRESS_MASK             (0xffffffe0) /* Must be 32-byte aligned. */

#define portMPU_MAIR_ATTR0_POS                (0UL)
#define portMPU_MAIR_ATTR0_MASK               (0x000000ff)

#define portMPU_MAIR_ATTR1_POS                (8UL)
#define portMPU_MAIR_ATTR1_MASK               (0x0000ff00)

#define portMPU_MAIR_ATTR2_POS                (16UL)
#define portMPU_MAIR_ATTR2_MASK               (0x00ff0000)

#define portMPU_MAIR_ATTR3_POS                (24UL)
#define portMPU_MAIR_ATTR3_MASK               (0xff000000)

#define portMPU_MAIR_ATTR4_POS                (0UL)
#define portMPU_MAIR_ATTR4_MASK               (0x000000ff)

#define portMPU_MAIR_ATTR5_POS                (8UL)
#define portMPU_MAIR_ATTR5_MASK               (0x0000ff00)

#define portMPU_MAIR_ATTR6_POS                (16UL)
#define portMPU_MAIR_ATTR6_MASK               (0x00ff0000)

#define portMPU_MAIR_ATTR7_POS                (24UL)
#define portMPU_MAIR_ATTR7_MASK               (0xff000000)

#define portMPU_RLAR_ATTR_INDEX0              (0UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX1              (1UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX2              (2UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX3              (3UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX4              (4UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX5              (5UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX6              (6UL << 1UL)
#define portMPU_RLAR_ATTR_INDEX7              (7UL << 1UL)

#define portMPU_RLAR_REGION_ENABLE            (1UL)

/* Enable privileged access to unmapped region. */
#define portMPU_PRIV_BACKGROUND_ENABLE_BIT    (1UL << 2UL)

/* Enable MPU. */
#define portMPU_ENABLE_BIT                    (1UL << 0UL)

/* Expected value of the portMPU_TYPE register. */
#define portEXPECTED_MPU_TYPE_VALUE           (8UL << 8UL) /* 8 regions, unified. */
/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#define portMAX_24_BIT_NUMBER                 (0xffffffUL)

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#define portMISSED_COUNTS_FACTOR              (45UL)

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#define portINITIAL_XPSR                      (0x01000000)

#if (configRUN_FREERTOS_SECURE_ONLY == 1)

/**
 * @brief Initial EXC_RETURN value.
 *
 *     FF         FF         FF         FD
 * 1111 1111  1111 1111  1111 1111  1111 1101
 *
 * Bit[6] - 1 --> The exception was taken from the Secure state.
 * Bit[5] - 1 --> Do not skip stacking of additional state context.
 * Bit[4] - 1 --> The PE did not allocate space on the stack for FP context.
 * Bit[3] - 1 --> Return to the Thread mode.
 * Bit[2] - 1 --> Restore registers from the process stack.
 * Bit[1] - 0 --> Reserved, 0.
 * Bit[0] - 1 --> The exception was taken to the Secure state.
 */
 #define portINITIAL_EXC_RETURN               (0xfffffffd)
#else

/**
 * @brief Initial EXC_RETURN value.
 *
 *     FF         FF         FF         BC
 * 1111 1111  1111 1111  1111 1111  1011 1100
 *
 * Bit[6] - 0 --> The exception was taken from the Non-Secure state.
 * Bit[5] - 1 --> Do not skip stacking of additional state context.
 * Bit[4] - 1 --> The PE did not allocate space on the stack for FP context.
 * Bit[3] - 1 --> Return to the Thread mode.
 * Bit[2] - 1 --> Restore registers from the process stack.
 * Bit[1] - 0 --> Reserved, 0.
 * Bit[0] - 0 --> The exception was taken to the Non-Secure state.
 */
 #define portINITIAL_EXC_RETURN               (0xffffffbc)
#endif                                 /* configRUN_FREERTOS_SECURE_ONLY */

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#define portCONTROL_PRIVILEGED_MASK           (1UL << 0UL)

/**
 * @brief Initial CONTROL register values.
 */
#define portINITIAL_CONTROL_UNPRIVILEGED      (0x3)
#define portINITIAL_CONTROL_PRIVILEGED        (0x2)

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#ifdef configTASK_RETURN_ADDRESS
 #define portTASK_RETURN_ADDRESS              configTASK_RETURN_ADDRESS
#else
 #define portTASK_RETURN_ADDRESS              prvTaskExitError
#endif

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#define portPRELOAD_REGISTERS                 1

/**
 * @brief A task is created without a secure context, and must call
 * portALLOCATE_SECURE_CONTEXT() to give itself a secure context before it makes
 * any secure calls.
 */
#define portNO_SECURE_CONTEXT                 0

/* Used to convert an evaluated macro into a string. */
#define RM_FREERTOS_PORT_STRINGIFY_EXPANDED(s)    RM_FREERTOS_PORT_STRINGIFY(s)

/* Used to convert text into a string. */
#define RM_FREERTOS_PORT_STRINGIFY(s)             #s

/* Value to write to OAD register of MPU stack monitor to enable NMI when a stack overflow is detected. */
#define RM_FREERTOS_PORT_SPMON_NMI_ON_DETECTION        (0xA500U)

#define RM_FREERTOS_PORT_UNLOCK_LPM_REGISTER_ACCESS    (0xA502U)
#define RM_FREERTOS_PORT_LOCK_LPM_REGISTER_ACCESS      (0xA500U)

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
static void prvTaskExitError(void);

#if (configENABLE_MPU == 1)

/**
 * @brief Setup the Memory Protection Unit (MPU).
 */
static void prvSetupMPU(void) PRIVILEGED_FUNCTION;

#endif                                 /* configENABLE_MPU */

#if (configENABLE_FPU == 1)

/**
 * @brief Setup the Floating Point Unit (FPU).
 */
static void prvSetupFPU(void) PRIVILEGED_FUNCTION;

#endif                                 /* configENABLE_FPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
void vPortSetupTimerInterrupt(void) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
BaseType_t xPortIsInsideInterrupt(void);

/**
 * @brief Yield the processor.
 */
void vPortYield(void) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
void vPortEnterCritical(void) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
void vPortExitCritical(void) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
void SysTick_Handler(timer_callback_args_t * p_args) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
portDONT_DISCARD void vPortSVCHandler_C(uint32_t * pulCallerStackAddress) PRIVILEGED_FUNCTION;

/**
 * @brief Idle Hook
 */
void vApplicationIdleHook(void);

/**
 * @brief Idle Hook
 */
void rm_freertos_port_sleep_preserving_lpm(uint32_t xExpectedIdleTime);

/*-----------------------------------------------------------*/

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_DATA static volatile uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#if (configENABLE_TRUSTZONE == 1)

/**
 * @brief Saved as part of the task context to indicate which context the
 * task is using on the secure side.
 */
PRIVILEGED_DATA portDONT_DISCARD volatile SecureContextHandle_t xSecureContext = portNO_SECURE_CONTEXT;
#endif                                 /* configENABLE_TRUSTZONE */

#if (configUSE_TICKLESS_IDLE == 1)
 #error Set configUSE_TICKLESS_IDLE = 0. Tickless Idle is not supported

/**
 * @brief The number of SysTick increments that make up one tick period.
 */
PRIVILEGED_DATA static uint32_t ulTimerCountsForOneTick = 0;

/**
 * @brief The maximum number of tick periods that can be suppressed is
 * limited by the 24 bit resolution of the SysTick timer.
 */
PRIVILEGED_DATA static uint32_t xMaximumPossibleSuppressedTicks = 0;

/**
 * @brief Compensate for the CPU cycles that pass while the SysTick is
 * stopped (low power functionality only).
 */
PRIVILEGED_DATA static uint32_t ulStoppedTimerCompensation = 0;
#endif                                 /* configUSE_TICKLESS_IDLE */

#if (configAPPLICATION_ALLOCATED_HEAP == 1)
uint8_t ucHeap[configTOTAL_HEAP_SIZE];
#endif

/*-----------------------------------------------------------*/

#if (configUSE_TICKLESS_IDLE == 1)
 #error Set configUSE_TICKLESS_IDLE = 0. Tickless Idle is not supported
__attribute__((weak)) void vPortSuppressTicksAndSleep (TickType_t xExpectedIdleTime)
{
    uint32_t   ulReloadValue, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
    TickType_t xModifiableIdleTime;

    /* Make sure the SysTick reload value does not overflow the counter. */
    if (xExpectedIdleTime > xMaximumPossibleSuppressedTicks)
    {
        xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
    }

    /* Stop the SysTick momentarily. The time the SysTick is stopped for is
     * accounted for as best it can be, but using the tickless mode will
     * inevitably result in some tiny drift of the time maintained by the
     * kernel with respect to calendar time. */
    portNVIC_SYSTICK_CTRL_REG &= ~portNVIC_SYSTICK_ENABLE_BIT;

    /* Calculate the reload value required to wait xExpectedIdleTime
     * tick periods. -1 is used because this code will execute part way
     * through one of the tick periods. */
    ulReloadValue = portNVIC_SYSTICK_CURRENT_VALUE_REG + (ulTimerCountsForOneTick * (xExpectedIdleTime - 1UL));

    if (ulReloadValue > ulStoppedTimerCompensation)
    {
        ulReloadValue -= ulStoppedTimerCompensation;
    }

    /* Enter a critical section but don't use the taskENTER_CRITICAL()
     * method as that will mask interrupts that should exit sleep mode. */
    __disable_irq();
    __DSB();
    __ISB();

    /* If a context switch is pending or a task is waiting for the scheduler
     * to be un-suspended then abandon the low power entry. */
    if (eTaskConfirmSleepModeStatus() == eAbortSleep)
    {
        /* Restart from whatever is left in the count register to complete
         * this tick period. */
        portNVIC_SYSTICK_LOAD_REG = portNVIC_SYSTICK_CURRENT_VALUE_REG;

        /* Restart SysTick. */
        portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

        /* Reset the reload register to the value required for normal tick
         * periods. */
        portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;

        /* Re-enable interrupts - see comments above the cpsid instruction()
         * above. */
        __enable_irq();
    }
    else
    {
        /* Set the new reload value. */
        portNVIC_SYSTICK_LOAD_REG = ulReloadValue;

        /* Clear the SysTick count flag and set the count value back to
         * zero. */
        portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;

        /* Restart SysTick. */
        portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

        /* Sleep until something happens. configPRE_SLEEP_PROCESSING() can
         * set its parameter to 0 to indicate that its implementation
         * contains its own wait for interrupt or wait for event
         * instruction, and so wfi should not be executed again. However,
         * the original expected idle time variable must remain unmodified,
         * so a copy is taken. */
        xModifiableIdleTime = xExpectedIdleTime;
        configPRE_SLEEP_PROCESSING(xModifiableIdleTime);

        if (xModifiableIdleTime > 0)
        {
            __DSB();
            __WFI();
            __ISB();
        }

        configPOST_SLEEP_PROCESSING(xExpectedIdleTime);

        /* Re-enable interrupts to allow the interrupt that brought the MCU
         * out of sleep mode to execute immediately. See comments above
         * the cpsid instruction above. */
        __enable_irq();
        __DSB();
        __ISB();

        /* Disable interrupts again because the clock is about to be stopped
         * and interrupts that execute while the clock is stopped will
         * increase any slippage between the time maintained by the RTOS and
         * calendar time. */
        __disable_irq();
        __DSB();
        __ISB();

        /* Disable the SysTick clock without reading the
         * portNVIC_SYSTICK_CTRL_REG register to ensure the
         * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.
         * Again, the time the SysTick is stopped for is accounted for as
         * best it can be, but using the tickless mode will inevitably
         * result in some tiny drift of the time maintained by the kernel
         * with respect to calendar time*/
        portNVIC_SYSTICK_CTRL_REG = (portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT);

        /* Determine if the SysTick clock has already counted to zero and
         * been set back to the current reload value (the reload back being
         * correct for the entire expected idle time) or if the SysTick is
         * yet to count to zero (in which case an interrupt other than the
         * SysTick must have brought the system out of sleep mode). */
        if ((portNVIC_SYSTICK_CTRL_REG & portNVIC_SYSTICK_COUNT_FLAG_BIT) != 0)
        {
            uint32_t ulCalculatedLoadValue;

            /* The tick interrupt is already pending, and the SysTick count
             * reloaded with ulReloadValue.  Reset the
             * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
             * period. */
            ulCalculatedLoadValue = (ulTimerCountsForOneTick - 1UL) -
                                    (ulReloadValue - portNVIC_SYSTICK_CURRENT_VALUE_REG);

            /* Don't allow a tiny value, or values that have somehow
             * underflowed because the post sleep hook did something
             * that took too long. */
            if ((ulCalculatedLoadValue < ulStoppedTimerCompensation) ||
                (ulCalculatedLoadValue > ulTimerCountsForOneTick))
            {
                ulCalculatedLoadValue = (ulTimerCountsForOneTick - 1UL);
            }

            portNVIC_SYSTICK_LOAD_REG = ulCalculatedLoadValue;

            /* As the pending tick will be processed as soon as this
             * function exits, the tick value maintained by the tick is
             * stepped forward by one less than the time spent waiting. */
            ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
        }
        else
        {
            /* Something other than the tick interrupt ended the sleep.
             * Work out how long the sleep lasted rounded to complete tick
             * periods (not the ulReload value which accounted for part
             * ticks). */
            ulCompletedSysTickDecrements = (xExpectedIdleTime * ulTimerCountsForOneTick) -
                                           portNVIC_SYSTICK_CURRENT_VALUE_REG;

            /* How many complete tick periods passed while the processor
             * was waiting? */
            ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

            /* The reload value is set to whatever fraction of a single tick
             * period remains. */
            portNVIC_SYSTICK_LOAD_REG = ((ulCompleteTickPeriods + 1UL) * ulTimerCountsForOneTick) -
                                        ulCompletedSysTickDecrements;
        }

        /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
         * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
         * value. */
        portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;
        portNVIC_SYSTICK_CTRL_REG         |= portNVIC_SYSTICK_ENABLE_BIT;
        vTaskStepTick(ulCompleteTickPeriods);
        portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;

        /* Exit with interrupts enabled. */
        __enable_irq();
    }
}

#endif                                                     /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/
__attribute__((weak)) void vPortSetupTimerInterrupt (void) /* PRIVILEGED_FUNCTION */
{
    /* Stop and reset the SysTick. */
    g_timer2.p_api->open(g_timer2.p_ctrl, g_timer2.p_cfg);

    /* Configure SysTick to interrupt at the requested rate. */
    g_timer2.p_api->callbackSet(g_timer2.p_ctrl, SysTick_Handler, NULL, NULL);

    /* Start the SysTick. */
    g_timer2.p_api->start(g_timer2.p_ctrl);

    /* Calculate the constants required to configure the tick interrupt. */
#if (configUSE_TICKLESS_IDLE == 1)
 #error Set configUSE_TICKLESS_IDLE = 0. Tickless Idle is not supported

    {
        ulTimerCountsForOneTick         = (configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ);
        xMaximumPossibleSuppressedTicks = portMAX_24_BIT_NUMBER / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation      = portMISSED_COUNTS_FACTOR / (configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ);
    }
#endif                                 /* configUSE_TICKLESS_IDLE */
}

/*-----------------------------------------------------------*/

static void prvTaskExitError (void)
{
    volatile uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT(ulCriticalNesting == ~0UL);
    portDISABLE_INTERRUPTS();

    while (ulDummy == 0)
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being
         * defined but never called.  ulDummy is used purely to quieten other
         * warnings about code appearing after this function is called - making
         * ulDummy volatile makes the compiler think the function could return
         * and therefore not output an 'unreachable code' warning for code that
         * appears after it. */
    }
}

/*-----------------------------------------------------------*/

#if (configENABLE_MPU == 1)
static void prvSetupMPU (void)         /* PRIVILEGED_FUNCTION */
{
 #if defined(__ARMCC_VERSION)

    /* Declaration when these variable are defined in code instead of being
     * exported from linker scripts. */
    extern uint32_t * __privileged_functions_start__;
    extern uint32_t * __privileged_functions_end__;
    extern uint32_t * __syscalls_flash_start__;
    extern uint32_t * __syscalls_flash_end__;
    extern uint32_t * __unprivileged_flash_start__;
    extern uint32_t * __unprivileged_flash_end__;
    extern uint32_t * __privileged_sram_start__;
    extern uint32_t * __privileged_sram_end__;
 #else                                 /* if defined( __ARMCC_VERSION ) */
    /* Declaration when these variable are exported from linker scripts. */
    extern uint32_t __privileged_functions_start__[];
    extern uint32_t __privileged_functions_end__[];
    extern uint32_t __syscalls_flash_start__[];
    extern uint32_t __syscalls_flash_end__[];
    extern uint32_t __unprivileged_flash_start__[];
    extern uint32_t __unprivileged_flash_end__[];
    extern uint32_t __privileged_sram_start__[];
    extern uint32_t __privileged_sram_end__[];
 #endif                                /* defined( __ARMCC_VERSION ) */

    /* Check that the MPU is present. */
    if (portMPU_TYPE_REG == portEXPECTED_MPU_TYPE_VALUE)
    {
        /* MAIR0 - Index 0. */
        portMPU_MAIR0_REG |=
            ((portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_ATTR0_POS) & portMPU_MAIR_ATTR0_MASK);

        /* MAIR0 - Index 1. */
        portMPU_MAIR0_REG |= ((portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_ATTR1_POS) & portMPU_MAIR_ATTR1_MASK);

        /* Setup privileged flash as Read Only so that privileged tasks can
         * read it but not modify. */
        portMPU_RNR_REG  = portPRIVILEGED_FLASH_REGION;
        portMPU_RBAR_REG = (((uint32_t) __privileged_functions_start__) & portMPU_RBAR_ADDRESS_MASK) |
                           (portMPU_REGION_NON_SHAREABLE) |
                           (portMPU_REGION_PRIVILEGED_READ_ONLY);
        portMPU_RLAR_REG = (((uint32_t) __privileged_functions_end__) & portMPU_RLAR_ADDRESS_MASK) |
                           (portMPU_RLAR_ATTR_INDEX0) |
                           (portMPU_RLAR_REGION_ENABLE);

        /* Setup unprivileged flash as Read Only by both privileged and
         * unprivileged tasks. All tasks can read it but no-one can modify. */
        portMPU_RNR_REG  = portUNPRIVILEGED_FLASH_REGION;
        portMPU_RBAR_REG = (((uint32_t) __unprivileged_flash_start__) & portMPU_RBAR_ADDRESS_MASK) |
                           (portMPU_REGION_NON_SHAREABLE) |
                           (portMPU_REGION_READ_ONLY);
        portMPU_RLAR_REG = (((uint32_t) __unprivileged_flash_end__) & portMPU_RLAR_ADDRESS_MASK) |
                           (portMPU_RLAR_ATTR_INDEX0) |
                           (portMPU_RLAR_REGION_ENABLE);

        /* Setup unprivileged syscalls flash as Read Only by both privileged
         * and unprivileged tasks. All tasks can read it but no-one can modify. */
        portMPU_RNR_REG  = portUNPRIVILEGED_SYSCALLS_REGION;
        portMPU_RBAR_REG = (((uint32_t) __syscalls_flash_start__) & portMPU_RBAR_ADDRESS_MASK) |
                           (portMPU_REGION_NON_SHAREABLE) |
                           (portMPU_REGION_READ_ONLY);
        portMPU_RLAR_REG = (((uint32_t) __syscalls_flash_end__) & portMPU_RLAR_ADDRESS_MASK) |
                           (portMPU_RLAR_ATTR_INDEX0) |
                           (portMPU_RLAR_REGION_ENABLE);

        /* Setup RAM containing kernel data for privileged access only. */
        portMPU_RNR_REG  = portPRIVILEGED_RAM_REGION;
        portMPU_RBAR_REG = (((uint32_t) __privileged_sram_start__) & portMPU_RBAR_ADDRESS_MASK) |
                           (portMPU_REGION_NON_SHAREABLE) |
                           (portMPU_REGION_PRIVILEGED_READ_WRITE) |
                           (portMPU_REGION_EXECUTE_NEVER);
        portMPU_RLAR_REG = (((uint32_t) __privileged_sram_end__) & portMPU_RLAR_ADDRESS_MASK) |
                           (portMPU_RLAR_ATTR_INDEX0) |
                           (portMPU_RLAR_REGION_ENABLE);

        /* Enable mem fault. */
        portSCB_SYS_HANDLER_CTRL_STATE_REG |= portSCB_MEM_FAULT_ENABLE_BIT;

        /* Enable MPU with privileged background access i.e. unmapped
         * regions have privileged access. */
        portMPU_CTRL_REG |= (portMPU_PRIV_BACKGROUND_ENABLE_BIT | portMPU_ENABLE_BIT);
    }
}

#endif                                 /* configENABLE_MPU */
/*-----------------------------------------------------------*/

#if (configENABLE_FPU == 1)
static void prvSetupFPU (void)         /* PRIVILEGED_FUNCTION */
{
 #if (configENABLE_TRUSTZONE == 1)
    {
        /* Enable non-secure access to the FPU. */
        SecureInit_EnableNSFPUAccess();
    }
 #endif                                /* configENABLE_TRUSTZONE */

    /* CP10 = 11 ==> Full access to FPU i.e. both privileged and
     * unprivileged code should be able to access FPU. CP11 should be
     * programmed to the same value as CP10. */
    *(portCPACR) |= ((portCPACR_CP10_VALUE << portCPACR_CP10_POS) |
                     (portCPACR_CP11_VALUE << portCPACR_CP11_POS)
                     );

    /* ASPEN = 1 ==> Hardware should automatically preserve floating point
     * context on exception entry and restore on exception return.
     * LSPEN = 1 ==> Enable lazy context save of FP state. */
    *(portFPCCR) |= (portFPCCR_ASPEN_MASK | portFPCCR_LSPEN_MASK);
}

#endif                                 /* configENABLE_FPU */
/*-----------------------------------------------------------*/

void vPortYield (void)                 /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}

/*-----------------------------------------------------------*/

void vPortEnterCritical (void)         /* PRIVILEGED_FUNCTION */
{
    portDISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}

/*-----------------------------------------------------------*/

void vPortExitCritical (void)          /* PRIVILEGED_FUNCTION */
{
    configASSERT(ulCriticalNesting);
    ulCriticalNesting--;

    if (ulCriticalNesting == 0)
    {
        portENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

void SysTick_Handler (__attribute__((unused)) timer_callback_args_t * p_args) /* PRIVILEGED_FUNCTION */
{
    uint32_t ulPreviousMask;

    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        /* Increment the RTOS tick. */
        if (xTaskIncrementTick() != pdFALSE)
        {
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR(ulPreviousMask);
}

/*-----------------------------------------------------------*/

void vPortSVCHandler_C (uint32_t * pulCallerStackAddress) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
#if (configENABLE_MPU == 1)
 #if defined(__ARMCC_VERSION)

    /* Declaration when these variable are defined in code instead of being
     * exported from linker scripts. */
    extern uint32_t * __syscalls_flash_start__;
    extern uint32_t * __syscalls_flash_end__;
 #else

    /* Declaration when these variable are exported from linker scripts. */
    extern uint32_t __syscalls_flash_start__[];
    extern uint32_t __syscalls_flash_end__[];
 #endif                                /* defined( __ARMCC_VERSION ) */
#endif                                 /* configENABLE_MPU */

    uint32_t ulPC;

#if (configENABLE_TRUSTZONE == 1)
    uint32_t ulR0;
 #if (configENABLE_MPU == 1)
    uint32_t ulControl, ulIsTaskPrivileged;
 #endif                                /* configENABLE_MPU */
#endif                                 /* configENABLE_TRUSTZONE */
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC        = pulCallerStackAddress[6];
    ucSVCNumber = ((uint8_t *) ulPC)[-2];

    switch (ucSVCNumber)
    {
#if (configENABLE_TRUSTZONE == 1)
        case portSVC_ALLOCATE_SECURE_CONTEXT:
        {
            /* R0 contains the stack size passed as parameter to the
             * vPortAllocateSecureContext function. */
            ulR0 = pulCallerStackAddress[0];

 #if (configENABLE_MPU == 1)
            {
                /* Read the CONTROL register value. */
                ulControl = __get_CONTROL();

                /* The task that raised the SVC is privileged if Bit[0]
                 * in the CONTROL register is 0. */
                ulIsTaskPrivileged = ((ulControl & portCONTROL_PRIVILEGED_MASK) == 0);

                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext(ulR0, ulIsTaskPrivileged);
            }
 #else                                 /* if ( configENABLE_MPU == 1 ) */
            {
                /* Allocate and load a context for the secure task. */
                xSecureContext = SecureContext_AllocateContext(ulR0);
            }
 #endif                                /* configENABLE_MPU */

            configASSERT(xSecureContext != NULL);
            SecureContext_LoadContext(xSecureContext);
            break;
        }

        case portSVC_FREE_SECURE_CONTEXT:
        {
            /* R0 contains the secure context handle to be freed. */
            ulR0 = pulCallerStackAddress[0];

            /* Free the secure context. */
            SecureContext_FreeContext((SecureContextHandle_t) ulR0);
            break;
        }
#endif                                 /* configENABLE_TRUSTZONE */

        case portSVC_START_SCHEDULER:
#if (configENABLE_TRUSTZONE == 1)
            {
                /* De-prioritize the non-secure exceptions so that the
                 * non-secure pendSV runs at the lowest priority. */
                SecureInit_DePrioritizeNSExceptions();

                /* Initialize the secure context management system. */
                SecureContext_Init();
            }
#endif                                 /* configENABLE_TRUSTZONE */

#if (configENABLE_FPU == 1)
            {
                /* Setup the Floating Point Unit (FPU). */
                prvSetupFPU();
            }
#endif                                 /* configENABLE_FPU */

            /* Setup the context of the first task so that the first task starts
             * executing. */
            vRestoreContextOfFirstTask();
            break;

#if (configENABLE_MPU == 1)
        case portSVC_RAISE_PRIVILEGE:
        {
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            if ((ulPC >= (uint32_t) __syscalls_flash_start__) &&
                (ulPC <= (uint32_t) __syscalls_flash_end__))
            {
                vRaisePrivilege();
            }

            break;
        }
#endif                                 /* configENABLE_MPU */

        default:

            /* Incorrect SVC call. */
            configASSERT(pdFALSE);
    }
}

/*-----------------------------------------------------------*/
/* *INDENT-OFF* */
#if (configENABLE_MPU == 1)
StackType_t * pxPortInitialiseStack (StackType_t  * pxTopOfStack,
                                     StackType_t  * pxEndOfStack,
                                     TaskFunction_t pxCode,
                                     void         * pvParameters,
                                     BaseType_t     xRunPrivileged) /* PRIVILEGED_FUNCTION */
#else
StackType_t * pxPortInitialiseStack(StackType_t * pxTopOfStack,
                                    StackType_t * pxEndOfStack,
                                    TaskFunction_t pxCode,
                                    void * pvParameters) /* PRIVILEGED_FUNCTION */
#endif /* configENABLE_MPU */
/* *INDENT-ON* */
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
#if (portPRELOAD_REGISTERS == 0)
    {
        pxTopOfStack--;                                        /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
        *pxTopOfStack = portINITIAL_XPSR;                      /* xPSR */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) pxCode;                  /* PC */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) portTASK_RETURN_ADDRESS; /* LR */
        pxTopOfStack -= 5;                                     /* R12, R3, R2 and R1. */
        *pxTopOfStack = (StackType_t) pvParameters;            /* R0 */
        pxTopOfStack -= 9;                                     /* R11..R4, EXC_RETURN. */
        *pxTopOfStack = portINITIAL_EXC_RETURN;

 #if (configENABLE_MPU == 1)
        {
            pxTopOfStack--;

            if (xRunPrivileged == pdTRUE)
            {
                *pxTopOfStack = portINITIAL_CONTROL_PRIVILEGED;   /* Slot used to hold this task's CONTROL value. */
            }
            else
            {
                *pxTopOfStack = portINITIAL_CONTROL_UNPRIVILEGED; /* Slot used to hold this task's CONTROL value. */
            }
        }
 #endif                                                           /* configENABLE_MPU */

        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) pxEndOfStack;               /* Slot used to hold this task's PSPLIM value. */

 #if (configENABLE_TRUSTZONE == 1)
        {
            pxTopOfStack--;
            *pxTopOfStack = portNO_SECURE_CONTEXT;             /* Slot used to hold this task's xSecureContext value. */
        }
 #endif                                                        /* configENABLE_TRUSTZONE */
    }
#else                                                          /* portPRELOAD_REGISTERS */
    {
        pxTopOfStack--;                                        /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
        *pxTopOfStack = portINITIAL_XPSR;                      /* xPSR */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) pxCode;                  /* PC */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) portTASK_RETURN_ADDRESS; /* LR */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x12121212UL;            /* R12 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x03030303UL;            /* R3 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x02020202UL;            /* R2 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x01010101UL;            /* R1 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) pvParameters;            /* R0 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x11111111UL;            /* R11 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x10101010UL;            /* R10 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x09090909UL;            /* R09 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x08080808UL;            /* R08 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x07070707UL;            /* R07 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x06060606UL;            /* R06 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x05050505UL;            /* R05 */
        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) 0x04040404UL;            /* R04 */
        pxTopOfStack--;
        *pxTopOfStack = portINITIAL_EXC_RETURN;                /* EXC_RETURN */

 #if (configENABLE_MPU == 1)
        {
            pxTopOfStack--;

            if (xRunPrivileged == pdTRUE)
            {
                *pxTopOfStack = portINITIAL_CONTROL_PRIVILEGED;   /* Slot used to hold this task's CONTROL value. */
            }
            else
            {
                *pxTopOfStack = portINITIAL_CONTROL_UNPRIVILEGED; /* Slot used to hold this task's CONTROL value. */
            }
        }
 #endif                                                           /* configENABLE_MPU */

        pxTopOfStack--;
        *pxTopOfStack = (StackType_t) pxEndOfStack;               /* Slot used to hold this task's PSPLIM value. */

 #if (configENABLE_TRUSTZONE == 1)
        {
            pxTopOfStack--;
            *pxTopOfStack = portNO_SECURE_CONTEXT; /* Slot used to hold this task's xSecureContext value. */
        }
 #endif                                            /* configENABLE_TRUSTZONE */
    }
#endif                                             /* portPRELOAD_REGISTERS */

    return pxTopOfStack;
}

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler (void)  /* PRIVILEGED_FUNCTION */
{
    /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
    portNVIC_SHPR2_REG = (portNVIC_SHPR2_REG & portNVIC_SVC_MASK) | portNVIC_SVC_PRI;
    portNVIC_SHPR3_REG = (portNVIC_SHPR3_REG & portNVIC_PENDSV_MASK) | portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG = (portNVIC_SHPR3_REG & portNVIC_SYSTICK_MASK) | portNVIC_SYSTICK_PRI;

#if (configENABLE_MPU == 1)
    {
        /* Setup the Memory Protection Unit (MPU). */
        prvSetupMPU();
    }
#endif                                 /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    vPortSetupTimerInterrupt();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Enable Interrupts */
    portENABLE_INTERRUPTS();

    /* Start the first task. */
    vStartFirstTask();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    return 0;
}

/*-----------------------------------------------------------*/

void vPortEndScheduler (void)          /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT(ulCriticalNesting == 1000UL);
}

/*-----------------------------------------------------------*/

#if (configENABLE_MPU == 1)
void vPortStoreTaskMPUSettings (xMPU_SETTINGS                     * xMPUSettings,
                                const struct xMEMORY_REGION * const xRegions,
                                StackType_t                       * pxBottomOfStack,
                                uint32_t                            ulStackDepth)
{
    uint32_t ulRegionStartAddress, ulRegionEndAddress, ulRegionNumber;
    int32_t  lIndex = 0;

 #if defined(__ARMCC_VERSION)

    /* Declaration when these variable are defined in code instead of being
     * exported from linker scripts. */
    extern uint32_t * __privileged_sram_start__;
    extern uint32_t * __privileged_sram_end__;
 #else

    /* Declaration when these variable are exported from linker scripts. */
    extern uint32_t __privileged_sram_start__[];
    extern uint32_t __privileged_sram_end__[];
 #endif                                /* defined( __ARMCC_VERSION ) */

    /* Setup MAIR0. */
    xMPUSettings->ulMAIR0 =
        ((portMPU_NORMAL_MEMORY_BUFFERABLE_CACHEABLE << portMPU_MAIR_ATTR0_POS) & portMPU_MAIR_ATTR0_MASK);
    xMPUSettings->ulMAIR0 |= ((portMPU_DEVICE_MEMORY_nGnRE << portMPU_MAIR_ATTR1_POS) & portMPU_MAIR_ATTR1_MASK);

    /* This function is called automatically when the task is created - in
     * which case the stack region parameters will be valid.  At all other
     * times the stack parameters will not be valid and it is assumed that
     * the stack region has already been configured. */
    if (ulStackDepth > 0)
    {
        ulRegionStartAddress = (uint32_t) pxBottomOfStack;
        ulRegionEndAddress   = (uint32_t) pxBottomOfStack + (ulStackDepth * (uint32_t) sizeof(StackType_t)) - 1;

        /* If the stack is within the privileged SRAM, do not protect it
         * using a separate MPU region. This is needed because privileged
         * SRAM is already protected using an MPU region and ARMv8-M does
         * not allow overlapping MPU regions. */
        if ((ulRegionStartAddress >= (uint32_t) __privileged_sram_start__) &&
            (ulRegionEndAddress <= (uint32_t) __privileged_sram_end__))
        {
            xMPUSettings->xRegionsSettings[0].ulRBAR = 0;
            xMPUSettings->xRegionsSettings[0].ulRLAR = 0;
        }
        else
        {
            /* Define the region that allows access to the stack. */
            ulRegionStartAddress &= portMPU_RBAR_ADDRESS_MASK;
            ulRegionEndAddress   &= portMPU_RLAR_ADDRESS_MASK;

            xMPUSettings->xRegionsSettings[0].ulRBAR = (ulRegionStartAddress) |
                                                       (portMPU_REGION_NON_SHAREABLE) |
                                                       (portMPU_REGION_READ_WRITE) |
                                                       (portMPU_REGION_EXECUTE_NEVER);

            xMPUSettings->xRegionsSettings[0].ulRLAR = (ulRegionEndAddress) |
                                                       (portMPU_RLAR_ATTR_INDEX0) |
                                                       (portMPU_RLAR_REGION_ENABLE);
        }
    }

    /* User supplied configurable regions. */
    for (ulRegionNumber = 1; ulRegionNumber <= portNUM_CONFIGURABLE_REGIONS; ulRegionNumber++)
    {
        /* If xRegions is NULL i.e. the task has not specified any MPU
         * region, the else part ensures that all the configurable MPU
         * regions are invalidated. */
        if ((xRegions != NULL) && (xRegions[lIndex].ulLengthInBytes > 0UL))
        {
            /* Translate the generic region definition contained in xRegions
             * into the ARMv8 specific MPU settings that are then stored in
             * xMPUSettings. */
            ulRegionStartAddress = ((uint32_t) xRegions[lIndex].pvBaseAddress) & portMPU_RBAR_ADDRESS_MASK;
            ulRegionEndAddress   = (uint32_t) xRegions[lIndex].pvBaseAddress + xRegions[lIndex].ulLengthInBytes - 1;
            ulRegionEndAddress  &= portMPU_RLAR_ADDRESS_MASK;

            /* Start address. */
            xMPUSettings->xRegionsSettings[ulRegionNumber].ulRBAR = (ulRegionStartAddress) |
                                                                    (portMPU_REGION_NON_SHAREABLE);

            /* RO/RW. */
            if ((xRegions[lIndex].ulParameters & tskMPU_REGION_READ_ONLY) != 0)
            {
                xMPUSettings->xRegionsSettings[ulRegionNumber].ulRBAR |= (portMPU_REGION_READ_ONLY);
            }
            else
            {
                xMPUSettings->xRegionsSettings[ulRegionNumber].ulRBAR |= (portMPU_REGION_READ_WRITE);
            }

            /* XN. */
            if ((xRegions[lIndex].ulParameters & tskMPU_REGION_EXECUTE_NEVER) != 0)
            {
                xMPUSettings->xRegionsSettings[ulRegionNumber].ulRBAR |= (portMPU_REGION_EXECUTE_NEVER);
            }

            /* End Address. */
            xMPUSettings->xRegionsSettings[ulRegionNumber].ulRLAR = (ulRegionEndAddress) |
                                                                    (portMPU_RLAR_REGION_ENABLE);

            /* Normal memory/ Device memory. */
            if ((xRegions[lIndex].ulParameters & tskMPU_REGION_DEVICE_MEMORY) != 0)
            {
                /* Attr1 in MAIR0 is configured as device memory. */
                xMPUSettings->xRegionsSettings[ulRegionNumber].ulRLAR |= portMPU_RLAR_ATTR_INDEX1;
            }
            else
            {
                /* Attr1 in MAIR0 is configured as normal memory. */
                xMPUSettings->xRegionsSettings[ulRegionNumber].ulRLAR |= portMPU_RLAR_ATTR_INDEX0;
            }
        }
        else
        {
            /* Invalidate the region. */
            xMPUSettings->xRegionsSettings[ulRegionNumber].ulRBAR = 0UL;
            xMPUSettings->xRegionsSettings[ulRegionNumber].ulRLAR = 0UL;
        }

        lIndex++;
    }
}

#endif                                 /* configENABLE_MPU */
/*-----------------------------------------------------------*/

BaseType_t xPortIsInsideInterrupt (void)
{
    uint32_t   ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    ulCurrentInterrupt = __get_IPSR();

    if (ulCurrentInterrupt == 0)
    {
        xReturn = pdFALSE;
    }
    else
    {
        xReturn = pdTRUE;
    }

    return xReturn;
}

/*-----------------------------------------------------------*/
#if configUSE_IDLE_HOOK || configUSE_TICKLESS_IDLE

/*-----------------------------------------------------------*/
#if !defined(portGENERATED_GET_WAKEUP_IRQ)
__attribute__((weak)) IRQn_Type vPortGetWakeUpIrq(void)
{
    return GTM2_OSTM2INT_IRQn;
}
#endif
/***********************************************************************************************************************
 * Saves the LPM state, then enters sleep mode. After waking, reenables interrupts briefly to allow any pending
 * interrupts to run.
 *
 * @pre Disable interrupts an suspend all tasks before calling this function.
 *
 * @param[in] xExpectedIdleTime Expected idle time in ticks
 **********************************************************************************************************************/
void rm_freertos_port_sleep_preserving_lpm (uint32_t xExpectedIdleTime)
{
    /* Get IRQ number for the return factor. */
    IRQn_Type irq_for_wakeup = vPortGetWakeUpIrq();
    /* This program jumps to IRQ handler of the return factor. */
    #define portJUMP_TO_IRQ_HANDLER_OF_RETURN_FACTOR    (1)

    /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
     * set its parameter to 0 to indicate that its implementation contains
     * its own wait for interrupt or wait for event instruction, and so wfi
     * should not be executed again. The original expected idle
     * time variable must remain unmodified, so this is done in a subroutine. */
    configPRE_SLEEP_PROCESSING(xExpectedIdleTime);
    if (xExpectedIdleTime > 0)
    {
        uint32_t nvic_iser_backup[sizeof(NVIC->ISER)/sizeof(uint32_t)];
        uint32_t nvic_icer[sizeof(NVIC->ICER)/sizeof(uint32_t)];
        /* Go to Cortex-M33 Sleep Mode. Refer to "Cortex-M33 Sleep Mode" section of Hardware Manual */

        /* Sequence "1. Slow down the speed of Cortex-M33 clock" is not mandatory. */

        /* Sequence 2.
         * Set the IM33_MASK bit of the SYS_LP_CTL7 register to 1.
         * Interrupts to IM33 are masked and interrupts from IM33 to Cortex-M33 are not accepted.
         * The IM33_MASK bit is automatically cleared after completing the transition to Cortex-M33 Sleep Mode.
         * Refer to the SYS_LP_CTL7 register in the SYSC section.
         */
        R_SYSC->SYS_LP_CTL7_b.IM33_MASK = 1;

        /* Sequence 3.
         * Set the return factor to NVIC. Enables only the interrupts used for return from Cortex-M33 Sleep Mode and
         * disables the interrupts used for the normal operation.
         */
        /* Backup all NVIC ISER registers */
        memcpy((void*)nvic_iser_backup, (void*)NVIC->ISER, sizeof(NVIC->ISER));
        /* Set all NVIC ICER registers except the return factor */
        memset((void*)nvic_icer, 0xffu, sizeof(nvic_icer));
        nvic_icer[irq_for_wakeup / 32] = (uint32_t)~(1u << (uint32_t)(irq_for_wakeup % 32));
        memcpy((void*)NVIC->ICER, (void*)nvic_icer, sizeof(NVIC->ICER));

        /* Sequence 4. 
         * Issue Barrier instruction.
         *
         * DSB should be last instruction executed before WFI
         * infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0321a/BIHICBGB.html
         */
        __DSB();

        /* Sequence 5. 
         * Set the SLEEPDEEP bit of the SCR register in Cortex-M33 to 1.
         * Note that to do above in the case of non-secure mode, SLEEPDEEPS bit is required to be 0.
         */
        SCB->SCR = (SCB->SCR & (~SCB_SCR_SLEEPDEEP_Msk)) |
                   ((1 << SCB_SCR_SLEEPDEEP_Pos) & SCB_SCR_SLEEPDEEP_Msk);

        /* Sequence 6. 
         * Read SCR register to confirm whether the SLEEPDEEP bit is set to 1.
         */
        while(!(SCB->SCR & SCB_SCR_SLEEPDEEP_Msk));

        /* Sequence 7. 
         * Issue a WFI instruction to enter Cortex-M33 Sleep Mode.
         *
         * If there is a pending interrupt (wake up condition for WFI is true), the MCU does not enter low power mode:
         * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/BABHHGEB.html
         * Note that interrupt will bring the CPU out of the low power mode.  After exiting from low power mode,
         * interrupt will be re-enabled. */
        __WFI();
        __ISB();

        /* Sequence 8. 
         * Return from Cortex-M33 Sleep Mode when the event ocurrs or the interrupt set in NVIC occurs.
         */

        /* Sequence 9. 
         * Confirm the interrupt cause and perform the processing required for returning from Cortex-M33 Sleep Mode.
         */

        /* Sequence 10. 
         * And then clear the interrupt cause.
         */
#if !portJUMP_TO_IRQ_HANDLER_OF_RETURN_FACTOR
        R_BSP_IrqClearPending(irq_for_wakeup);
#endif

        /* Sequence 11. 
         * Set the interrupt causes for the normal operation to NVIC.
         */
        /* Restore NVIC ISER register from backup */
        memcpy((void*)NVIC->ISER, (void*)nvic_iser_backup, sizeof(NVIC->ISER));
        
        /* Sequence "12. Recover the speed of Cortex-M33 clock." is not mandatory. */

        /* Re-enable interrupts to allow the interrupt that brought the MCU
         * out of sleep mode to execute immediately. This will not cause a
         * context switch because all tasks are currently suspended. */
        __enable_irq();
        __ISB();

        /* Disable interrupts again to restore the LPM state. */
        __disable_irq();
    }

    configPOST_SLEEP_PROCESSING(xExpectedIdleTime);
}

#endif

#if configUSE_IDLE_HOOK

/***********************************************************************************************************************
 * Suspends tasks and sleeps, waking for each interrupt.
 *
 * @note This is a weak function. It can be overridden by an application specific implementation if desired.
 **********************************************************************************************************************/
__attribute__((weak)) void vApplicationIdleHook (void)
{
    /* Enter a critical section but don't use the taskENTER_CRITICAL() method as that will mask interrupts that should
     * exit sleep mode. This must be done before suspending tasks because a pending interrupt will prevent sleep from
     * WFI, but a task ready to run will not. If a task becomes ready to run before disabling interrupts, a context
     * switch will happen. */
    __disable_irq();

    /* Don't allow a context switch during sleep processing to ensure the LPM state is restored
     * before switching from idle to the next ready task. This is done in the idle task
     * before vPortSuppressTicksAndSleep when configUSE_TICKLESS_IDLE is used. */
    vTaskSuspendAll();

    /* Save current LPM state, then sleep. */
    rm_freertos_port_sleep_preserving_lpm(1);

    /* Exit with interrupts enabled. */
    __enable_irq();

    /* Allow context switches again. No need to yield here since the idle task yields when it loops around. */
    (void) xTaskResumeAll();
}

#endif

__attribute__((weak)) void vPortConfigureTimerForRunTimeStatus (void)
{
#if configGENERATE_RUN_TIME_STATS
    /* open and start GTM0 */
#endif
}

#if configGENERATE_RUN_TIME_STATS

/* Count clock = 100MHz
 * 10-bits-right-shift makes 10.24us counting interval */
 #define runtimeCLOCK_SCALE_SHIFT    (10)

/* GTM overflows 32bit */
 #define runtimeOVERFLOW_SHIFT       (32 - runtimeCLOCK_SCALE_SHIFT)
__attribute__((weak)) unsigned long ulGetRunTimeCounterValue (void)
{
    static unsigned long ulLastCounterValue = 0UL, ulOverflows = 0;
    unsigned long        ulValueNow = 0;
    timer_status_t       timer_status;

    /* copy the count value of GTM0 to timer_status.counter. */
    {
        ulValueNow = timer_status.counter;

        /* Has the value overflowed since it was last read. */
        if (ulValueNow < ulLastCounterValue)
        {
            ulOverflows++;
        }

        ulLastCounterValue = ulValueNow;

        /* move the count value to  */
        ulValueNow >>= runtimeCLOCK_SCALE_SHIFT;
        ulValueNow  += ulOverflows << runtimeOVERFLOW_SHIFT;
    }

    return ulValueNow;
}

#endif

__attribute__((weak)) void vPortDefineHeapRegions (__attribute__((unused)) const HeapRegion_t * const pxHeapRegions)
{
}
