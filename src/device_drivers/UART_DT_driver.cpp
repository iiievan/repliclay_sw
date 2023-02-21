#include "UART_DT_driver.h"

sw_Timer RX_end_timer(3, os_timer, RX_end_callback);
ring_buffer<n_UART::RX_FIFO_MAX*4> Terminal_buffer; 

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

// @brief This Callback is called to write buffer to UART
static int UART_write_isr(void *p_Obj, const char *buffer, size_t len)
{
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);
    
    s_UART.write(buffer, len);
}

static void  UART_0_irqhandler(void *p_Obj)
{  
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);
  
    // go to interrupt handlers
    s_UART.rx_irq();
    s_UART.tx_irq();
}
    
static int console_pollrx(void *p_Obj)
{
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);

    int ret = -1;
    
    /* ��� ����� ������� ��������� ������ � ����� ������� ��������*/
    s_UART.is_RX_data_rdy(&Terminal_buffer);
    
    if(Terminal_buffer.get_avail() > 0)
    {
        ret = (int)Terminal_buffer.get_one();
    }
    
    return ret;
}

// @brief  UART device opertaion functions callbacks
// @detail
UART_client_ops UART_ops;

// @brief  device tree property
// @details
const DT_device_id_t  AM335x_UART_ids =
{
   .compatible = "AM335x_UART",
};

int  UART_DT_Driver::probe(void *p_owner)
{   
    UART_ops.write = UART_write_isr;
    UART_ops.read = UART_read;
    UART_ops.isr = UART_0_irqhandler;
    UART_ops.pollrx = console_pollrx;
    set_Client_ops(p_owner,dynamic_cast<Client_ops*>(&UART_ops));
    
    return 0;
}

void UART_DT_Driver::set_Client_ops(void *p_owner, Client_ops *p_ops)
{
    Device_driver::m_Owner = p_owner;
    Device_driver::mp_Ops  = p_ops;
    
    UART_client_ops *p_client = static_cast<UART_client_ops *>(Device_driver::m_Owner);  //static because p_owner is (void *)
    std::string compat(m_Of_match_table->compatible);
    
    if(p_client->compatible.compare(compat) == 0)
    {  
        UART_client_ops *input_ops = dynamic_cast<UART_client_ops*>(mp_Ops);
        
        p_client->write = input_ops->write;
        p_client->read = input_ops->read;
        p_client->p_UART_instance = input_ops->p_UART_instance;
        p_client->pollrx = input_ops->pollrx;
        p_client->p_UART_instance = get_instance(); 
    } 
}
 
int  UART_DT_Driver::init(void)
{    
    /// Initialize the UART console /// 
    m_prcm_module.run_clk_UART0();                                 // Configuring the system clocks for UART0 instance.
    m_pinmux_ctrl.UART0_pin_mux_setup();                           // Performing the Pin Multiplexing for UART0 instance.                            
    m_UART_device.module_reset();                                  // Performing a module reset.        
    //m_UART_device.FIFO_configure_no_DMA(1, (RX_FIFO_MAX - 4));   // Performing FIFO configurations.
    m_UART_device.FIFO_configure_no_DMA(1, 1);                     // Performing FIFO configurations.

    
    m_UART_device.BAUD_set(115200);                                // Performing Baud Rate settings.    
    
    m_UART_device.reg_config_mode_enable(n_UART::CONFIG_MODE_B);   // Switching to Configuration Mode B. 
    
    // Programming the Line Characteristics. 
    m_UART_device.char_len_config(n_UART::CHL_8_BITS);
    m_UART_device.stop_bit_config(n_UART::STOP_1);
    m_UART_device.parity_config(n_UART::PARITY_NONE);
             
    m_UART_device.divisor_latch_disable();                         // Disabling write access to Divisor Latches.        
    m_UART_device.break_ctl(false);                                // Disabling Break Control.
    m_UART_device.operating_mode_select(n_UART::MODE_UART_16x);    // Switching to UART16x operating mode.    

    AINTC_configure();    
    
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

void  UART_DT_Driver::AINTC_configure(void)
{
    m_int_controller.register_handler(m_UART_sys_interrupt, UART_ops.isr);      // Registering I2C_irqhandler         
    m_int_controller.priority_set(m_UART_sys_interrupt,5, INTC::HOSTINT_ROUTE_IRQ);    // Set the highest priority
    sys_interrupt_enable();
}

UART_DT_Driver uart_driver(uart_0);
