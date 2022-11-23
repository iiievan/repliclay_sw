#include "I2C_EEPROM.h" 
#include "beaglebone.h"

template <auto EEPROM_SIZE, auto PAGE_SIZE>
I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::I2C_EEPROM(I2C::AM335x_I2C_Type *p_i2c_regs, uint8_t slave_address, INTC::isr_handler_t isr_hndlr) 
: HS_I2C(p_i2c_regs), 
  m_prcm_module(prcm_module),
  m_int_controller(intc),
  m_pinmux_ctrl(ctrl_module)
{ 
    m_I2C_number        = HS_I2C::get_I2C_ser_number();
    m_I2C_sys_interrupt = HS_I2C::get_I2C_sys_interrupt();
    m_isr_handler       = isr_hndlr;

    m_t_count         = 0;
    m_r_count         = 0;
    m_Wait_flag       = true;
    m_num_of_bytes    = 0;

    m_slave_address   = slave_address;    
    m_Pages_max       = EEPROM_SIZE/PAGE_SIZE;
}

template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::setup(I2C::e_CLK_FREQUENCY output_freq)  // output_freq 100kHz by default
{ 
    switch(m_I2C_number)
    {
        case I2C::I2C_NUM_0:
            m_prcm_module.run_I2C0_clk(); // Enable the clock for I2C0        
            m_pinmux_ctrl.I2C0_pin_mux_setup(); 
            break;
        case I2C::I2C_NUM_1:
            m_prcm_module.run_I2C1_clk(); // Enable the clock for I2C1        
            m_pinmux_ctrl.I2C1_pin_mux_setup();
            break;
        case I2C::I2C_NUM_2:
            m_prcm_module.run_I2C2_clk(); // Enable the clock for I2C2        
            m_pinmux_ctrl.I2C2_pin_mux_setup();
            break;
        default:
            return;
    }  
    
    AINTC_configure();
 
    HS_I2C::master_disable();                                        // Put i2c in reset/disabled state     
    HS_I2C::auto_idle_disable();                                     // Disable auto Idle functionality  
    
    switch(output_freq)
    {
        case I2C::F_100KHz:
            HS_I2C::master_init_exp_clk(48000000, 12000000, 100000); 
            break;
        case I2C::F_250KHz:
            HS_I2C::master_init_exp_clk(48000000, 12000000, 250000);
            break;
        case I2C::F_400KHz:
            HS_I2C::master_init_exp_clk(48000000, 12000000, 400000);
            break;
        default:
            return;
    }    
                
    HS_I2C::master_slave_addr_set(m_slave_address);                  // Set i2c slave address   
    HS_I2C::master_enable();                                         // Bring I2C out of reset
}

template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::AINTC_configure(void)
{        
    m_int_controller.register_handler(m_I2C_sys_interrupt, m_isr_handler);            // Registering I2C_irqhandler         
    m_int_controller.priority_set(m_I2C_sys_interrupt,0, INTC::HOSTINT_ROUTE_IRQ);    // Set the highest priority
    sys_interrupt_enable();                                                           // Enabling the system interrupt in AINTC. 
}

/** Clear status of all interrupts **/
template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::clean_interrupts(void)
{      
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_ALL);
    HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_ALL);
    HS_I2C::master_int_disable_ex((uint32_t)I2C::F_IRQENABLE_ALL);        
}

// write one byte
template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::write_byte(EEPROM_byte_address_t byte_addr, uint8_t data)
{
    m_data_to_slave[0] = byte_addr.msb;
    m_data_to_slave[1] = byte_addr.lsb;
    
    m_data_to_slave[2] = data;
    m_t_count = 0;
        
    HS_I2C::set_data_count(3);                  // Data Count specifies the number of bytes to be transmitted 
    m_num_of_bytes = HS_I2C::data_count_get();
    clean_interrupts();                         // Clear status of all interrupts

    /** Configure I2C controller in Master Transmitter mode **/
    uint32_t cmd = (uint32_t)(I2C::F_CON_MST|I2C::F_CON_TRX);
    HS_I2C::master_control(cmd);    
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_XRDY_IE); // Transmit interrupt is enabled    
    HS_I2C::master_start();                                           // Generate Start Condition over I2C bus and start to transmit

    while(!HS_I2C::master_bus_busy());        
    while(m_t_count != m_num_of_bytes);    
    HS_I2C::master_stop();
}

// write multiple bytes until page end
template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::write(EEPROM_byte_address_t byte_addr, uint8_t *data, size_t d_count)
{
    m_data_to_slave[0] = byte_addr.msb;
    m_data_to_slave[1] = byte_addr.lsb;
    
    std::memcpy(&m_data_to_slave[2],data, d_count);
    m_t_count = 0;
        
    HS_I2C::set_data_count(d_count + 1);        // Data Count specifies the number of bytes to be transmitted + msb and lsb byte addr
    m_num_of_bytes = HS_I2C::data_count_get();
    clean_interrupts();                         // Clear status of all interrupts

    /** Configure I2C controller in Master Transmitter mode **/
    uint32_t cmd = (uint32_t)(I2C::F_CON_MST|I2C::F_CON_TRX);
    HS_I2C::master_control(cmd);    
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_XRDY_IE); // Transmit interrupt is enabled    
    HS_I2C::master_start();                                           // Generate Start Condition over I2C bus and start to transmit

    while(!HS_I2C::master_bus_busy());        
    while(m_t_count != m_num_of_bytes);    
    HS_I2C::master_stop();
}

// write page to the end
template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::write_page(EEPROM_byte_address_t byte_addr, uint8_t *page_data)
{    
    return;
}

// immediate read byte accessed by prevous operation
template <auto EEPROM_SIZE, auto PAGE_SIZE>
uint8_t  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::immediate_read()
{
    /** Wait untill I2C registers are ready to access **/
    while(!(HS_I2C::master_int_raw_status() &
           ((uint32_t)I2C::F_IRQSTATUS_ARDY)));  
    
    HS_I2C::set_data_count(1);                                        // Data Count specifies the number of bytes to be received      
    m_num_of_bytes = HS_I2C::data_count_get();       
    clean_interrupts();                                               // Clear status of all interrupts
    
    HS_I2C::master_control((uint32_t)I2C::F_CON_MST);                 // Configure I2C controller in Master Receiver mode  
    HS_I2C::master_int_enable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE |
                                            I2C::F_IRQENABLE_BF_IE)); // Receive and Stop Condition Interrupts are enabled          
    
    m_Wait_flag = true;
    HS_I2C::master_start();                                           // Generate Start Condition over I2C bus and start to Receive
    
    while(!HS_I2C::master_bus_busy());    
    while(m_Wait_flag);                                               // wait read transaction end flag  
    
    return m_data_from_slave[0];
}

// selective read byte by address
template <auto EEPROM_SIZE, auto PAGE_SIZE>
uint8_t  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::read_byte(EEPROM_byte_address_t byte_addr)
{  
    //--------------------------------- set byte address to read from ----------------->
    m_data_to_slave[0] = byte_addr.msb;
    m_data_to_slave[1] = byte_addr.lsb;  

    m_t_count = 0;
        
    HS_I2C::set_data_count(2);                  // Data Count specifies the number of bytes to be transmitted 
    m_num_of_bytes = HS_I2C::data_count_get();
    clean_interrupts();                         // Clear status of all interrupts

    /** Configure I2C controller in Master Transmitter mode **/
    uint32_t cmd = (uint32_t)(I2C::F_CON_MST|I2C::F_CON_TRX);
    HS_I2C::master_control(cmd);    
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_XRDY_IE); // Transmit interrupt is enabled    
    HS_I2C::master_start();                                           // Generate Start Condition over I2C bus and start to transmit
       
    while(m_t_count != m_num_of_bytes);    
    //<-------------------------------- set byte address to read from -----------------
    
    return immediate_read();
}

// sequential read multiple bytes
template <auto EEPROM_SIZE, auto PAGE_SIZE>
uint8_t*  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE> ::read(EEPROM_byte_address_t byte_addr, size_t d_count)
{
    if(d_count > PAGE_SIZE)
        return nullptr;
    //--------------------------------- set byte address to start read from ----------------->
    m_data_to_slave[0] = byte_addr.msb;
    m_data_to_slave[1] = byte_addr.lsb;  

    m_t_count = 0;
        
    HS_I2C::set_data_count(2);                  // Data Count specifies the number of bytes to be transmitted 
    m_num_of_bytes = HS_I2C::data_count_get();
    clean_interrupts();                         // Clear status of all interrupts

    /** Configure I2C controller in Master Transmitter mode **/
    uint32_t cmd = (uint32_t)(I2C::F_CON_MST|I2C::F_CON_TRX);
    HS_I2C::master_control(cmd);    
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_XRDY_IE); // Transmit interrupt is enabled    
    HS_I2C::master_start();                                           // Generate Start Condition over I2C bus and start to transmit
       
    while(m_t_count != m_num_of_bytes);    
    //<-------------------------------- set byte address to start read from -----------------
    
      /** Wait untill I2C registers are ready to access **/
    while(!(HS_I2C::master_int_raw_status() &
           ((uint32_t)I2C::F_IRQSTATUS_ARDY)));  
    
    HS_I2C::set_data_count(d_count);                                  // Data Count specifies the number of bytes to be received      
    m_num_of_bytes = HS_I2C::data_count_get();       
    clean_interrupts();                                               // Clear status of all interrupts
    
    HS_I2C::master_control((uint32_t)I2C::F_CON_MST);                 // Configure I2C controller in Master Receiver mode  
    HS_I2C::master_int_enable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE |
                                            I2C::F_IRQENABLE_BF_IE | 
                                            I2C::F_IRQENABLE_NACK_IE)); // Receive and Stop Condition Interrupts are enabled 
    m_Wait_flag = true;
    HS_I2C::master_start();                                             // Generate Start Condition over I2C bus and start to Receive
    
    while(!HS_I2C::master_bus_busy());    
    while(m_Wait_flag);                                                 // wait transaction end flag  
    
    return &m_data_from_slave[0];
}

template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::irq_handler()
{
    uint32_t status = HS_I2C::master_int_status(); // Get only Enabled interrupt status 

    /** Clear all enabled interrupt status except receive ready and transmit ready interrupt status **/
    HS_I2C::master_int_clear_ex((status & ~(I2C::F_IRQSTATUS_RRDY | I2C::F_IRQSTATUS_XRDY)));
                        
    if (status & (uint32_t)I2C::F_IRQSTATUS_RRDY)
    {        
        m_data_from_slave[m_r_count++] = HS_I2C::master_data_get(); // Receive data from data receive register
        HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_RRDY);           // Clear receive ready interrupt status 
        
        if(m_r_count == m_num_of_bytes)
        {             
             HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE)); // Disable the receive ready interrupt            
             HS_I2C::master_stop();                                               // Generate a STOP            
        }
    }

    if (status & (uint32_t)I2C::F_IRQSTATUS_XRDY)
    {   
        HS_I2C::master_data_put(m_data_to_slave[m_t_count++]); // Put data to data transmit register of i2c         
        HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_XRDY);      // Clear Transmit interrupt status
                        
        if(m_t_count == m_num_of_bytes)            
             HS_I2C::master_int_disable_ex(I2C::F_IRQENABLE_XRDY_IE);      // Disable the transmit ready interrupt
    }
        
    if (status & (uint32_t)I2C::F_IRQSTATUS_BF)
    {
        /** Disable transmit data ready, receive data read and STOP event interupts **/
        HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE | 
                                                 I2C::F_IRQENABLE_XRDY_IE | 
                                                 I2C::F_IRQENABLE_BF_IE));        
        m_Wait_flag = false;   // set transaction flag
    }
   
    if (status & (uint32_t)I2C::F_IRQSTATUS_NACK)
    {    
        /** Disable transmit data ready, receive data read, STOP event and NACK event interrupts **/
        HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE | 
                                                 I2C::F_IRQENABLE_XRDY_IE |
                                                 I2C::F_IRQENABLE_NACK_IE |
                                                 I2C::F_IRQENABLE_BF_IE));

        HS_I2C::master_stop();    // Generate a STOP 
        m_Wait_flag = false;      // set transaction end flag
    }
}

/** I2C Interrupt Service Routine. This function will read and write data through I2C bus. 
This function is a friend of class I2C_EEPROM **/
void  BRDINFO_24LC32A_irqhandler(void *p_obj)
{  
    I2C_EEPROM<(32*1024),32> &s_I2C = *((I2C_EEPROM<(32*1024),32> *)p_obj);
  
    // go to interrupt handler
    s_I2C.irq_handler();
} 

void  CAT24C256WI_irqhandler(void *p_obj)
{  
    I2C_EEPROM<(32*1024),64> &s_I2C = *((I2C_EEPROM<(32*1024),64> *)p_obj);
  
    // go to interrupt handler
    s_I2C.irq_handler();
}

template class I2C_EEPROM <(32*1024), 32>;
template class I2C_EEPROM <(32*1024), 64>;


