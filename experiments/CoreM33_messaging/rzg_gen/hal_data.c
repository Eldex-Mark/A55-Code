/* generated HAL source file - do not edit */
#include "hal_data.h"
scif_uart_instance_ctrl_t g_uart2_ctrl;

scif_baud_setting_t g_uart2_baud_setting =
{
/* Baud rate calculated with 0.469% error. */.abcs = 0,
  .bgdm = 1, .cks = 0, .brr = 53, .mddr = (uint8_t) 256, .brme = false };

/** UART extended configuration for UARTonSCIF HAL driver */
const scif_uart_extended_cfg_t g_uart2_cfg_extend =
{ .bri_ipl = 14, .bri_irq = SCIF2_BRK_IRQn, .clock = SCIF_UART_CLOCK_INT, .noise_cancel =
          SCIF_UART_NOISE_CANCELLATION_DISABLE,
  .p_baud_setting = &g_uart2_baud_setting, .rx_fifo_trigger = SCIF_UART_RECEIVE_TRIGGER_MAX, .rts_fifo_trigger =
          SCIF_UART_RTS_TRIGGER_14,
  .uart_mode = SCIF_UART_MODE_RS232, .flow_control = SCIF_UART_FLOW_CONTROL_NONE, .driver_enable_pin =
          (bsp_io_port_pin_t) SCIF_UART_INVALID_16BIT_PARAM, };

/** UART interface configuration */
const uart_cfg_t g_uart2_cfg =
{ .channel = 2,
  .data_bits = UART_DATA_BITS_8,
  .parity = UART_PARITY_OFF,
  .stop_bits = UART_STOP_BITS_1,
  .p_callback = NULL,
  .p_context = NULL,
  .p_extend = &g_uart2_cfg_extend,
  .p_transfer_tx = NULL,
  .p_transfer_rx = NULL,
  .rxi_ipl = 14,
  .txi_ipl = 14,
  .tei_ipl = 14,
  .eri_ipl = 14,
  .rxi_irq = SCIF2_RXI_IRQn,
  .txi_irq = SCIF2_TXI_IRQn,
  .tei_irq = SCIF2_TEI_DRI_IRQn,
  .eri_irq = SCIF2_RERR_IRQn, };

/* Instance structure to use this module. */
const uart_instance_t g_uart2 =
{ .p_ctrl = &g_uart2_ctrl, .p_cfg = &g_uart2_cfg, .p_api = &g_uart_on_scif };
mhu_ns_instance_ctrl_t g_mhu_ns0_ctrl;
const mhu_cfg_t g_mhu_ns0_cfg =
{ .channel = 1, .rx_ipl = 12, .rx_irq = MHU_MSG1_NS_IRQn, .p_callback = NULL, .p_shared_memory = 0, .p_context = NULL, };
/* Instance structure to use this module. */
const mhu_instance_t g_mhu_ns0 =
{ .p_ctrl = &g_mhu_ns0_ctrl, .p_cfg = &g_mhu_ns0_cfg, .p_api = &g_mhu_ns_on_mhu_ns };
gtm_instance_ctrl_t g_timer2_ctrl;
const gtm_extended_cfg_t g_timer2_extend =
{ .generate_interrupt_when_starts = GTM_GIWS_TYPE_DISABLED, .gtm_mode = GTM_TIMER_MODE_INTERVAL, };
const timer_cfg_t g_timer2_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period_counts = 99999 /* Actual period: 0.001 seconds. */, .channel = 2, .p_callback =
          NULL,
  .p_context = NULL, .cycle_end_ipl = 255, .p_extend = &g_timer2_extend,
#if defined(VECTOR_NUMBER_GTM2_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GTM2_COUNTER_OVERFLOW,
#else
  .cycle_end_irq = GTM2_OSTM2INT_IRQn,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer2 =
{ .p_ctrl = &g_timer2_ctrl, .p_cfg = &g_timer2_cfg, .p_api = &g_timer_on_gtm };
extern void SysTick_Handler(timer_callback_args_t *p_args);
void vPortSetupTimerInterrupt(void) /* PRIVILEGED_FUNCTION */
{
    /* Stop and reset the SysTick. */
    g_timer2.p_api->open (g_timer2.p_ctrl, g_timer2.p_cfg);
    /* Configure SysTick to interrupt at the requested rate. */
    g_timer2.p_api->callbackSet (g_timer2.p_ctrl, SysTick_Handler, NULL, NULL);
    /* Start the SysTick. */
    g_timer2.p_api->start (g_timer2.p_ctrl);
#if (configUSE_TICKLESS_IDLE == 1)
 #error Set configUSE_TICKLESS_IDLE = 0. Tickless Idle is not supported
#endif                                 /* configUSE_TICKLESS_IDLE */

}
void vPortConfigureTimerForRunTimeStatus(void)
{
#if configGENERATE_RUN_TIME_STATS
    /* Stop and reset the Status Timer. */
    FSP_NOT_DEFINED.p_api->open(FSP_NOT_DEFINED.p_ctrl, FSP_NOT_DEFINED.p_cfg);
    /* Start the Status Timer. */
    FSP_NOT_DEFINED.p_api->start(FSP_NOT_DEFINED.p_ctrl);
#endif
}

/* Count clock = 100MHz
 10-bits-right-shift makes 10.24us counting interval */
#define runtimeCLOCK_SCALE_SHIFT    ( 10 )

/* GTM overflows 32bit */
#define runtimeOVERFLOW_SHIFT       ( 32 - runtimeCLOCK_SCALE_SHIFT )
unsigned long ulGetRunTimeCounterValue(void)
{
#if configGENERATE_RUN_TIME_STATS
    static unsigned long ulLastCounterValue = 0UL, ulOverflows = 0;
    unsigned long ulValueNow = 0;
    timer_status_t timer_status;

    /* Get count value */
    if (FSP_SUCCESS == FSP_NOT_DEFINED.p_api->statusGet(FSP_NOT_DEFINED.p_ctrl, &timer_status))
    {
        ulValueNow = timer_status.counter;
        
        /* Has the value overflowed since it was last read. */
        if( ulValueNow < ulLastCounterValue )
        {
            ulOverflows++;
        }
        ulLastCounterValue = ulValueNow;

        /* move the count value to  */
        ulValueNow >>= runtimeCLOCK_SCALE_SHIFT;
        ulValueNow += ulOverflows << runtimeOVERFLOW_SHIFT;
    }

    return ulValueNow;
#else
    return 0;
#endif
}
void g_hal_init(void)
{
    g_common_init ();
}
