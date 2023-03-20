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
    HS_I2C::master_int_disable_ex((uint32_t)I2C::F_IRQENABLE_ALL);
    HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_ALL);        
}

template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::generate_STOP_with_IRQ()
{
    HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_BF_IE);
    HS_I2C::master_stop();
    while(m_transaction_fsm != STOPPED);
    m_transaction_fsm = IDLE;
}

// write one byte
template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::write_byte(EEPROM_byte_address_t byte_addr, uint8_t data)
{
    uint8_t send = data;
    write(byte_addr, &send, 1);
}

// write multiple bytes until page end
template <auto EEPROM_SIZE, auto PAGE_SIZE>
void  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::write(EEPROM_byte_address_t byte_addr, uint8_t *data, size_t d_count)
{  
    uint8_t strt_sequence_tryes = STRT_SEQ_TRYES_NUM;
    
    while(m_transaction_fsm != IDLE); //in case bus is still not free after the last operation
    
    do
    {
        if(m_transaction_fsm == NACK_DURING_START)
        {
            delay_100us(2);
            strt_sequence_tryes--;
        }
        
        m_data_to_slave[0] = byte_addr.msb;
        m_data_to_slave[1] = byte_addr.lsb;  
    
        if(d_count)
            std::memcpy(&m_data_to_slave[2],data, d_count);
        
        m_t_count = 0;
            
        HS_I2C::set_data_count(d_count + 2);   // Data Count specifies the number of bytes to be transmitted + msb and lsb byte addr - (/0 symbol)
        m_num_of_bytes = HS_I2C::data_count_get();
        clean_interrupts();                         // Clear status of all interrupts
    
        /** Configure I2C controller in Master Transmitter mode **/
        uint32_t cmd = (uint32_t)(I2C::F_CON_MST|I2C::F_CON_TRX);
        HS_I2C::master_control(cmd);
        
        HS_I2C::master_int_enable_ex((uint32_t)(I2C::F_IRQENABLE_XRDY_IE |  // Transmit interrupt 
                                                I2C::F_IRQENABLE_ARDY_IE |  // transmit finished and rredisters ready
                                                I2C::F_IRQENABLE_NACK_IE |  // NACK intarrupt
                                                I2C::F_IRQENABLE_BF_IE));     
        m_transaction_fsm = STARTED;
        HS_I2C::master_start();                                             // Generate Start Condition over I2C bus and start to transmit
        while(m_transaction_fsm == STARTED);
    }
    while(m_transaction_fsm == NACK_DURING_START &&
          (strt_sequence_tryes > 0)); // repeat appeal to if EEPROM  is busy after the previous operation
    
    if(strt_sequence_tryes == 0)
    {
        // unsuccsesfully start sequence.
        // generate stop condition, and return.
        HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_BF_IE);
        HS_I2C::master_stop();
        while(m_transaction_fsm != STOPPED);
        m_transaction_fsm = IDLE;
        
        return;  
    }    
    
    while(m_transaction_fsm != ARDY); // Wait untill I2C registers are ready to access after transmit   
    
    if(d_count)
        generate_STOP_with_IRQ();
    else 
    {
        // do not generate a stop as this is the start of a read operation
        m_transaction_fsm = IDLE;        // start sequence successfully finished
    }
    
    
    HS_I2C::FIFO_clear(I2C::I2C_TX_MODE);   // clear FIFO in case the threshold value is not a multiple of the number of bytes!!!
                                            // without this stuff you can't do like that:
                                            //
                                            // uint8_t p_Read = CAT24C256WI.read_byte(addr1);
                                            //         p_Read = CAT24C256WI.read_byte(addr2);
                                            //         p_Read = CAT24C256WI.read_byte(addr3);
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
    uint8_t strt_sequence_tryes = STRT_SEQ_TRYES_NUM;
    
    while(m_transaction_fsm != IDLE);
    
    do
    {
        if(m_transaction_fsm == NACK_DURING_START)
        {
            delay_100us(2);
            strt_sequence_tryes--;
        } 
    
        m_r_count = 0;
        HS_I2C::set_data_count(1);                                        // Data Count specifies the number of bytes to be received  

        m_num_of_bytes = HS_I2C::data_count_get();
        clean_interrupts();                                               // Clear status of all interrupts
        
        HS_I2C::master_control((uint32_t)I2C::F_CON_MST);                   // Configure I2C controller in Master Receiver mode  
        HS_I2C::master_int_enable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE |  // Transmit interrupt 
                                                I2C::F_IRQENABLE_ARDY_IE |  // transmit finished and rredisters ready
                                                I2C::F_IRQENABLE_BF_IE));           
        
        m_transaction_fsm = STARTED;
        HS_I2C::master_start();                                             // Generate Start Condition over I2C bus and start to transmit
        while(m_transaction_fsm == STARTED);  
    }
    while(m_transaction_fsm == NACK_DURING_START &&
          (strt_sequence_tryes > 0)); // repeat appeal to if EEPROM  is busy after the previous operation 

    if(strt_sequence_tryes == 0)
    {
        // unsuccsesfully start sequence.
        // generate stop condition, and return.
        HS_I2C::master_int_enable_ex((uint32_t)I2C::F_IRQENABLE_BF_IE);
        HS_I2C::master_stop();
        while(m_transaction_fsm != STOPPED);
        m_transaction_fsm = IDLE;
        
        return 0;  
    }    
    
    while(m_transaction_fsm != ARDY); // Wait untill I2C registers are ready to access after transmit 

    generate_STOP_with_IRQ();
    HS_I2C::FIFO_clear(I2C::I2C_RX_MODE);   // clear FIFO in case the threshold value is not a multiple of the number of bytes!!!
                                            // without this stuff you can't do like that:
                                            //
                                            // uint8_t p_Read = CAT24C256WI.read_byte(addr1);
                                            //         p_Read = CAT24C256WI.read_byte(addr2);
                                            //         p_Read = CAT24C256WI.read_byte(addr3);
    
    return m_data_from_slave[0];
}

// selective read byte by address
template <auto EEPROM_SIZE, auto PAGE_SIZE>
uint8_t  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE>::read_byte(EEPROM_byte_address_t byte_addr)
{  
    /** Step 1: Initiate read transaction and set byte_addr to read from **/
    write(byte_addr, nullptr, 0); 
    
    /** Step 2: Read data **/
    return immediate_read();
}

// sequential read multiple bytes
template <auto EEPROM_SIZE, auto PAGE_SIZE>
uint8_t*  I2C_EEPROM <EEPROM_SIZE, PAGE_SIZE> ::read(EEPROM_byte_address_t byte_addr, size_t d_count)
{    
    if(d_count > PAGE_SIZE)
        return nullptr;
    
    /** Step 1: Initiate read transaction and set byte_addr to read from **/
    write(byte_addr, nullptr, 0);    
        
    /** Step 2: Read data **/
    
    HS_I2C::set_data_count(d_count);                                    // Data Count specifies the number of bytes to be received      
    m_num_of_bytes = HS_I2C::data_count_get();       
    clean_interrupts();                                                 // Clear status of all interrupts
    
    HS_I2C::master_control((uint32_t)I2C::F_CON_MST);                   // Configure I2C controller in Master Receiver mode  
    HS_I2C::master_int_enable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE |
                                            I2C::F_IRQENABLE_ARDY_IE |
                                            I2C::F_IRQENABLE_BF_IE));   // Receive and Stop Condition Interrupts are enabled
    m_transaction_fsm = STARTED;
    HS_I2C::master_start();                                             // Generate Start Condition over I2C bus and start to Receive
    
    while(m_transaction_fsm != ARDY); // Wait untill I2C registers are ready to access after recieve all bytes (DCOUNT = 0 and rcvFIFO is empty)
 
    // receive sequence successfully finished
    // generate stop condition, and return.
    generate_STOP_with_IRQ();
    HS_I2C::FIFO_clear(I2C::I2C_RX_MODE);   // clear FIFO in case the threshold value is not a multiple of the number of bytes!!!
                                            // without this stuff you can't do like that:
                                            //
                                            // uint8_t p_Read = CAT24C256WI.read_byte(addr1);
                                            //         p_Read = CAT24C256WI.read_byte(addr2);
                                            //         p_Read = CAT24C256WI.read_byte(addr3);
    
    
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
        }
    }

    if (status & (uint32_t)I2C::F_IRQSTATUS_XRDY)
    {   
        HS_I2C::master_data_put(m_data_to_slave[m_t_count++]); // Put data to data transmit register of i2c         
        HS_I2C::master_int_clear_ex((uint32_t)I2C::F_IRQSTATUS_XRDY);      // Clear Transmit interrupt status
                        
        if(m_t_count == m_num_of_bytes)
        {             
             HS_I2C::master_int_disable_ex(I2C::F_IRQENABLE_XRDY_IE);      // Disable the transmit ready interrupt
        }
    }
        
    if (status & (uint32_t)I2C::F_IRQSTATUS_BF)
    {
        /** Disable transmit data ready, receive data read and STOP event interupts **/
        HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_RRDY_IE | 
                                                 I2C::F_IRQENABLE_XRDY_IE | 
                                                 I2C::F_IRQENABLE_BF_IE));
        
        m_transaction_fsm = STOPPED;
    }
    
    if (status & (uint32_t)I2C::F_IRQSTATUS_ARDY)
    { 
        HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_ARDY_IE));
        m_transaction_fsm = ARDY;
    }
   
    if (status & (uint32_t)I2C::F_IRQSTATUS_NACK)
    {           
        /** Disable transmit data ready, receive data read, STOP event and NACK event interrupts **/
        HS_I2C::master_int_disable_ex((uint32_t)(I2C::F_IRQENABLE_NACK_IE |
                                                 I2C::F_IRQENABLE_BF_IE)); 
        
        m_transaction_fsm = NACK_DURING_START;
    }
}

/** I2C Interrupt Service Routine. **/
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


