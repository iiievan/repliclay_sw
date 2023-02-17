#include "UART_DT_driver.h"

// @brief This Callback is called when charater is receive
static char UART_read(void *p_Obj)
{    
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);

    char result = s_UART.char_get();
    return result;
}

// @brief This Callback is called to write buffer to UART
static int UART_write(void *p_Obj, const char *buffer, size_t len)
{
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);
    int index = -1 ;    

    // Send the characters
    for(index = 0; index < len; index++)
    {
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        if(buffer[index] == '\n')
            s_UART.char_put('\r');
        
        s_UART.char_put(buffer[index]); // Send the character to the UART output
    }

    // Return the number of characters written. */
    return (index);
}

// @brief  UART device opertaion functions callbacks
// @detail
Dev_ops_t UART_ops = 
{
    .write = UART_write,
    .read = UART_read,
    .isr_handler = nullptr
};

// @brief  device tree property
// @details
const DT_device_id_t  AM335x_UART_ids =
{
    .compatible = "AM335x_UART"
};

int  UART_DT_Driver::probe(void)
{   
    Device_driver::set_Client_ops(&UART_ops);
    
    return 0;
}
 
int  UART_DT_Driver::init(void)
{
    /// Initialize the UART console /// 
    m_prcm_module.run_clk_UART0();                                 // Configuring the system clocks for UART0 instance.
    m_pinmux_ctrl.UART0_pin_mux_setup();                           // Performing the Pin Multiplexing for UART0 instance.                            
    m_UART_device.module_reset();                                  // Performing a module reset.        
    m_UART_device.FIFO_configure_no_DMA(1, 1);                     // Performing FIFO configurations.
    
    m_UART_device.BAUD_set(115200);                                // Performing Baud Rate settings.
    m_UART_device.reg_config_mode_enable(n_UART::CONFIG_MODE_B);   // Switching to Configuration Mode B.
    m_UART_device.line_char_config((UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1), UART_PARITY_NONE);   // Programming the Line Characteristics.        
    m_UART_device.divisor_latch_disable();                         // Disabling write access to Divisor Latches.        
    m_UART_device.break_ctl(false);                                // Disabling Break Control.
    m_UART_device.operating_mode_select(n_UART::MODE_UART_16x);    // Switching to UART16x operating mode.
    
    return 0;
}
 
void  UART_DT_Driver::sync_state(void* dev)
{
  
}
 
int  UART_DT_Driver::remove(void* dev)
{
    return 0;
}
 
void  UART_DT_Driver::shutdown(void* dev)
{
}
 
int  UART_DT_Driver::suspend(void* dev)
{
    return 0;
}
 
int  UART_DT_Driver::resume(void* dev)
{
    return 0;
}

int  UART_DT_Driver::exit(void)
{
    return 0;
}

UART_DT_Driver uart_console(uart_0);
