/* FSP MHU (Message Handling Unit) Inter-processor Communication Example for RZG/2L
 * This example demonstrates communication between Cortex-A55 (Linux) and Cortex-M33 */

#include "hal_data.h"
#include "r_mhu_ns_api.h"

/* MHU channel configuration */
#define MHU_CH0     (0)
#define MSG_SIZE    (64)
#define TIMEOUT     (1000)

/* Message buffer */
static uint32_t g_message_buffer[MSG_SIZE];

/* MHU callback */
void mhu_callback(mhu_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        switch (p_args->event)
        {
            case MHU_EVENT_TX_COMPLETE:
                /* Handle transmission complete */
                break;
            
            case MHU_EVENT_RX_COMPLETE:
                /* Handle received message */
                /* Process g_message_buffer contents */
                break;
            
            case MHU_EVENT_ERR:
                /* Handle error event */
                break;
            
            default:
                break;
        }
    }
}

/* MHU configuration */
const mhu_instance_t g_mhu = {
    .p_ctrl = &g_mhu_ctrl,
    .p_cfg = &g_mhu_cfg,
    .p_api = &g_mhu_on_mhu
};

/* Initialize MHU */
fsp_err_t init_mhu(void)
{
    fsp_err_t err = FSP_SUCCESS;
    
    /* Open MHU driver */
    err = R_MHU_Open(&g_mhu_ctrl, &g_mhu_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }
    
    /* Enable interrupts */
    err = R_MHU_InterruptEnable(&g_mhu_ctrl);
    
    return err;
}

/* Send message through MHU */
fsp_err_t send_message(uint32_t *p_msg, uint32_t size)
{
    fsp_err_t err = FSP_SUCCESS;
    
    if (size > MSG_SIZE)
    {
        return FSP_ERR_INVALID_SIZE;
    }
    
    /* Send message */
    err = R_MHU_Send(&g_mhu_ctrl, p_msg, size, MHU_CH0, TIMEOUT);
    
    return err;
}

/* Receive message through MHU */
fsp_err_t receive_message(uint32_t *p_msg, uint32_t size)
{
    fsp_err_t err = FSP_SUCCESS;
    
    if (size > MSG_SIZE)
    {
        return FSP_ERR_INVALID_SIZE;
    }
    
    /* Receive message */
    err = R_MHU_Receive(&g_mhu_ctrl, p_msg, size, MHU_CH0, TIMEOUT);
    
    return err;
}

/* Example usage */
void example_mhu_communication(void)
{
    fsp_err_t err;
    
    /* Initialize MHU */
    err = init_mhu();
    if (FSP_SUCCESS != err)
    {
        /* Handle error */
        return;
    }
    
    /* Prepare message to send */
    uint32_t tx_message[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444444};
    
    /* Send message */
    err = send_message(tx_message, 4);
    if (FSP_SUCCESS != err)
    {
        /* Handle error */
        return;
    }
    
    /* Receive message */
    uint32_t rx_message[4] = {0};
    err = receive_message(rx_message, 4);
    if (FSP_SUCCESS != err)
    {
        /* Handle error */
        return;
    }
}
