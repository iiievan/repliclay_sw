#include "I2C_EEPROM.h" 
#include "beaglebone.h"

I2C_EEPROM::I2C_EEPROM(I2C::AM335x_I2C_Type *p_i2c_regs, uint8_t address) 
: HS_I2C(p_i2c_regs), 
  m_prcm_module(prcm_module),
  m_int_controller(intc)
{ 
    m_I2C_number        = HS_I2C::get_I2C_ser_number();
    m_I2C_sys_interrupt = HS_I2C::get_I2C_sys_interrupt();
    m_isr_handler       = (INTC::isr_handler_t)I2C_irqhandler;

    m_t_count      = 0;
    m_r_count      = 0;
    m_Wait_flag    = true;
    m_num_of_bytes = 0;

    m_slave_address   = address;
    m_E2PROM_ADDR_MSB = 0x00;   // Higher byte address (i.e A8-A15)
    m_E2PROM_ADDR_LSB = 0x00;   // Lower byte address (i.e A0-A7)
}

/** Clear status of all interrupts **/
void  I2C_EEPROM::clean_interrupts(void)
{      
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_ALL);
    HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_ALL);
    HS_I2C::master_int_disable_ex((uint32_t)I2C::F_IRQENABLE_ALL);        
}

void  I2C_EEPROM::setup(uint32_t output_freq)
{        
    m_prcm_module.run_I2C0_clk(); // Enable the clock for I2C0        
    AINTC_configure();

    I2CPinMuxSetup(0);    
    
    HS_I2C::master_disable();                                   // Put i2c in reset/disabled state 
    
    HS_I2C::auto_idle_disable();                                // Disable auto Idle functionality         
    HS_I2C::master_init_exp_clk(48000000, 12000000, output_freq);    // Configure i2c bus speed to 100khz         
    HS_I2C::master_slave_addr_set(m_slave_address);             // Set i2c slave address
    
    HS_I2C::master_enable();                                    // Bring I2C out of reset
}

/** Receives data over I2C bus **/
void  I2C_EEPROM::setup_to_receive(uint16_t d_count)
{        
    HS_I2C::set_data_count(0x02);               // Data Count specifies the number of bytes to be transmitted 
    m_num_of_bytes = HS_I2C::data_count_get();
    clean_interrupts();                         // Clear status of all interrupts

    /** Configure I2C controller in Master Transmitter mode **/
    uint32_t cmd = (uint32_t)(I2C::F_CON_MST|I2C::F_CON_TRX);
    HS_I2C::master_control(cmd);    
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_XRDY_IE); // Transmit interrupt is enabled
    
    HS_I2C::master_start();                                           // Generate Start Condition over I2C bus and start to transmit

    while(!HS_I2C::master_bus_busy());        
    while(m_t_count != m_num_of_bytes);    
    m_Wait_flag = true;

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
    HS_I2C::master_start();                                             // Generate Start Condition over I2C bus and start to Receive
    
    while(!HS_I2C::master_bus_busy());    
    while(m_Wait_flag);                                                 // wait transaction end flag  
    m_Wait_flag = true;
}

void  I2C_EEPROM::AINTC_configure(void)
{        
    m_int_controller.register_handler(m_I2C_sys_interrupt, m_isr_handler);            // Registering I2C_irqhandler         
    m_int_controller.priority_set(m_I2C_sys_interrupt,0, INTC::HOSTINT_ROUTE_IRQ);    // Set the highest priority
    sys_interrupt_enable();                                                           // Enabling the system interrupt in AINTC. 
}

// Reads data from a specific address of e2prom
void  I2C_EEPROM::EEPROM_Read(uint8_t *data)
{   
    m_data_to_slave[0] = m_E2PROM_ADDR_MSB;
    m_data_to_slave[1] = m_E2PROM_ADDR_LSB;

    m_t_count = 0;
    m_r_count = 0;
    
    setup_to_receive(50);

    for (uint32_t i = 0; i < 50; i++ )
        data[i] = m_data_from_slave[i];
}

/** I2C Interrupt Service Routine. This function will read and write data through I2C bus. 
This function is a friend of class I2C_EEPROM **/
void  I2C_irqhandler(void *p_obj)
{ 
    uint32_t status = 0; 
    I2C_EEPROM &s_I2C = *((I2C_EEPROM*)p_obj);
    
    status = s_I2C.HS_I2C::master_int_status(); // Get only Enabled interrupt status 

    /** Clear all enabled interrupt status except receive ready and transmit ready interrupt status **/
    s_I2C.HS_I2C::master_int_clear_ex((status & ~(I2C::F_IRQSTATUS_RRDY | I2C::F_IRQSTATUS_XRDY)));
                        
    if (status & (uint32_t)I2C::F_IRQSTATUS_RRDY)
    {        
        s_I2C.m_data_from_slave[s_I2C.m_r_count++] = s_I2C.HS_I2C::master_data_get(); // Receive data from data receive register
        s_I2C.HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_RRDY);           // Clear receive ready interrupt status 
        
        if(s_I2C.m_r_count == s_I2C.m_num_of_bytes)
        {             
             s_I2C.HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE)); // Disable the receive ready interrupt            
             s_I2C.HS_I2C::master_stop();                                               // Generate a STOP            
        }
    }

    if (status & (uint32_t)I2C::F_IRQSTATUS_XRDY)
    {        
        s_I2C.HS_I2C::master_data_put(s_I2C.m_data_to_slave[s_I2C.m_t_count++]); // Put data to data transmit register of i2c        
        s_I2C.HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_XRDY);      // Clear Transmit interrupt status
                        
        if(s_I2C.m_t_count == s_I2C.m_num_of_bytes)            
             s_I2C.HS_I2C::master_int_disable_ex(I2C::F_IRQENABLE_XRDY_IE);      // Disable the transmit ready interrupt
    }
        
    if (status & (uint32_t)I2C::F_IRQSTATUS_BF)
    {
        /** Disable transmit data ready, receive data read and STOP event interupts **/
        s_I2C.HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE | 
                                                       I2C::F_IRQENABLE_XRDY_IE | 
                                                       I2C::F_IRQENABLE_BF_IE));        
        s_I2C.m_Wait_flag = false;   // set transaction flag
    }
   
    if (status & (uint32_t)I2C::F_IRQSTATUS_NACK)
    {    
        /** Disable transmit data ready, receive data read, STOP event and NACK event interrupts **/
        s_I2C.HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE | 
                                                       I2C::F_IRQENABLE_XRDY_IE |
                                                       I2C::F_IRQENABLE_NACK_IE |
                                                       I2C::F_IRQENABLE_BF_IE));

        s_I2C.HS_I2C::master_stop();    // Generate a STOP 
        s_I2C.m_Wait_flag = false;      // set transaction end flag
    }
}   


