#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H

#include "HS_I2C.h"

#define  I2C_SLAVE_ADDR   (0x50) // I2C address of CAT24C256 e2prom
#define  E2PROM_ADDR_MSB  (0x00) // Higher byte address (i.e A8-A15)
#define  E2PROM_ADDR_LSB  (0x00) // Lower byte address (i.e A0-A7)

void I2C_irqhandler(void *p_obj);

class I2C_EEPROM : public HS_I2C
{
    friend void I2C_irqhandler(void *p_obj);
    
public:
    I2C_EEPROM(I2C::AM335x_I2C_Type *p_i2c_regs, uint8_t address) 
    : HS_I2C(p_i2c_regs),
      m_prcm_module(prcm_module),
      m_int_controller(intc)
    { 
        m_I2C_number = HS_I2C::get_I2C_ser_number();
        m_I2C_sys_interrupt = HS_I2C::get_I2C_sys_interrupt();
        m_isr_handler = (INTC::isr_handler_t)I2C_irqhandler;

        m_slave_address = address;

        m_t_count = 0;
        m_r_count = 0;
        m_flag   = 1;
        m_num_of_bytes = 0;
    }

    /** Clear status of all interrupts **/
    void clean_interrupts(void)
    {
        //I2CMasterIntEnableEx(SOC_I2C_0_REGS, 0x7FF);
        //I2CMasterIntClearEx(SOC_I2C_0_REGS,  0x7FF);
        //I2CMasterIntDisableEx(SOC_I2C_0_REGS, 0x7FF);
      
        HS_I2C::master_int_enable_ex(I2C::F_IRQENABLE_SET_ALL);
        HS_I2C::master_int_clear_ex(I2C::F_IRQSTATUS_ALL);
        HS_I2C::master_int_disable_ex(I2C::F_IRQENABLE_CLR_ALL);
        
    }

    void setup_to_transmit()
    {
        /* Enable the clock for I2C0 */
        //I2C0ModuleClkConfig();
        m_prcm_module.run_I2C0_clk();
    
        I2CPinMuxSetup(0);    
        
        //I2CMasterDisable(SOC_I2C_0_REGS);
        HS_I2C::master_disable();  // Put i2c in reset/disabled state 
        
        //I2CAutoIdleDisable(SOC_I2C_0_REGS);
        HS_I2C::auto_idle_disable();    // Disable auto Idle functionality  
        
        //I2CMasterInitExpClk(SOC_I2C_0_REGS, 48000000, 12000000, 100000);
        HS_I2C::master_init_exp_clk(48000000, 12000000, 100000);    // Configure i2c bus speed to 100khz 
        
        //I2CMasterSlaveAddrSet(SOC_I2C_0_REGS, I2C_SLAVE_ADDR);
        master_slave_addr_set(I2C_SLAVE_ADDR);    // Set i2c slave address
        
        //I2CMasterEnable(SOC_I2C_0_REGS);
        HS_I2C::master_disable();   // Bring I2C out of reset
    }

    /** Receives data over I2C bus **/
    void setup_to_receive(uint32_t reload_value)
    {
        /* Data Count specifies the number of bytes to be transmitted */
        //I2CSetDataCount(SOC_I2C_0_REGS, 0x02); 
        HS_I2C::set_data_count();
    
        //m_num_of_bytes = I2CDataCountGet(SOC_I2C_0_REGS);
        m_num_of_bytes = HS_I2C::data_count_get();
    
        /* Clear status of all interrupts */
        clean_interrupts();
    
        /* Configure I2C controller in Master Transmitter mode */
        //I2CMasterControl(SOC_I2C_0_REGS, I2C_CFG_MST_TX);
        HS_I2C::master_control(I2C_CFG_MST_TX);
    
        /* Transmit interrupt is enabled */
        //I2CMasterIntEnableEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY);
        HS_I2C::master_int_enable_ex(I2C::F_IRQENABLE_SET_XRDY_IE);
    
        /* Generate Start Condition over I2C bus */
        //I2CMasterStart(SOC_I2C_0_REGS);
        HS_I2C::master_start();
    
        //while(I2CMasterBusBusy(SOC_I2C_0_REGS) == 0);
        while(HS_I2C::master_bus_busy());
        
        while(m_t_count != m_num_of_bytes);
    
        m_flag = 1;
    
        /* Wait untill I2C registers are ready to access */
        while(!(I2CMasterIntRawStatus(SOC_I2C_0_REGS) & (I2C_INT_ADRR_READY_ACESS)));
        while(!(HS_I2C::master_int_raw_status() & (I2C_INT_ADRR_READY_ACESS)));
        
        /* Data Count specifies the number of bytes to be received */
        I2CSetDataCount(SOC_I2C_0_REGS, dcount);
    
        m_num_of_bytes = I2CDataCountGet(SOC_I2C_0_REGS);
    
        clean_interrupts();
    
        /* Configure I2C controller in Master Receiver mode */
        I2CMasterControl(SOC_I2C_0_REGS, I2C_CFG_MST_RX);
    
        /* Receive and Stop Condition Interrupts are enabled */
        I2CMasterIntEnableEx(SOC_I2C_0_REGS,  I2C_INT_RECV_READY |
                                              I2C_INT_STOP_CONDITION);
    
        /* Generate Start Condition over I2C bus */
        I2CMasterStart(SOC_I2C_0_REGS);
    
        while(I2CMasterBusBusy(SOC_I2C_0_REGS) == 0);
    
        while(m_flag);    
        m_flag = 1;
    }

    /* Configures AINTC to generate interrupt */
    void AINTC_configure(void)
    {
        /* Intialize the ARM Interrupt Controller(AINTC) */
        IntAINTCInit();
    
        /* Registering the Interrupt Service Routine(ISR). */
        IntRegister(SYS_INT_I2C0INT, I2CIsr);
    
        /* Setting the priority for the system interrupt in AINTC. */
        IntPrioritySet(SYS_INT_I2C0INT, 0, AINTC_HOSTINT_ROUTE_IRQ );
    
        /* Enabling the system interrupt in AINTC. */
        IntSystemEnable(SYS_INT_I2C0INT);
    }

    /** Reads data from a specific address of e2prom **/
    void EEPROM_Read(uint8_t *data)
    {   
        m_data_to_slave[0] = E2PROM_ADDR_MSB;
        m_data_to_slave[1] = E2PROM_ADDR_LSB;
    
        m_t_count = 0;
        m_r_count = 0;
        setup_to_receive(50);
    
        for (uint32_t i = 0; i < 50; i++ )
        {
            data[i] = m_data_from_slave[i];
        }
    }

private:
          INTC::isr_handler_t  m_isr_handler;
           I2C::e_I2C_SER_NUM  m_I2C_number;
        INTC::e_SYS_INTERRUPT  m_I2C_sys_interrupt;

    power_reset_clock_control &m_prcm_module;      // for clock contrlol setup and management
    Interrupt_controller      &m_int_controller;   // for interrupt setup and management

                uint32_t  m_t_count;
                uint32_t  m_r_count;
                uint32_t  m_flag;
                uint32_t  m_num_of_bytes;
                 uint8_t  m_data_to_slave[2];
                 uint8_t  m_data_from_slave[50];

                 uint8_t m_slave_address;
};

extern I2C_EEPROM CAT24C256WI;


/** I2C Interrupt Service Routine. This function will read and write data through I2C bus. 
This function is a friend of class I2C_EEPROM **/
inline void I2C_irqhandler(void *p_obj)
{ 
    uint32_t status = 0; 
    I2C_EEPROM &s_I2C = *((I2C_EEPROM*)p_obj);

    /* Get only Enabled interrupt status */
    status = I2CMasterIntStatus(SOC_I2C_0_REGS);

    /* 
    ** Clear all enabled interrupt status except receive ready and
    ** transmit ready interrupt status 
    */
    I2CMasterIntClearEx(SOC_I2C_0_REGS, (status & ~(I2C_INT_RECV_READY | I2C_INT_TRANSMIT_READY)));
                        
    if(status & I2C_INT_RECV_READY)
    {
        /* Receive data from data receive register */
        s_I2C.m_data_from_slave[m_r_count++] = I2CMasterDataGet(SOC_I2C_0_REGS);

        /* Clear receive ready interrupt status */  
        I2CMasterIntClearEx(SOC_I2C_0_REGS,  I2C_INT_RECV_READY);
        
        if(s_I2C.m_r_count == s_I2C.m_num_of_bytes)
        {
             /* Disable the receive ready interrupt */
             I2CMasterIntDisableEx(SOC_I2C_0_REGS, I2C_INT_RECV_READY);
             /* Generate a STOP */
             I2CMasterStop(SOC_I2C_0_REGS);
             
        }
    }

    if (status & I2C_INT_TRANSMIT_READY)
    {
        /* Put data to data transmit register of i2c */
        I2CMasterDataPut(SOC_I2C_0_REGS, s_I2C.m_data_to_slave[m_t_count++]);

        /* Clear Transmit interrupt status */
        I2CMasterIntClearEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY);         
                        
        if(s_I2C.m_t_count == s_I2C.m_num_of_bytes)
        {
             /* Disable the transmit ready interrupt */
             I2CMasterIntDisableEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY);
        }

    }
        
    if (status & I2C_INT_STOP_CONDITION)
    {
        /* Disable transmit data ready and receive data read interupt */
        I2CMasterIntDisableEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY |
                                              I2C_INT_RECV_READY     |
                          I2C_INT_STOP_CONDITION);
        s_I2C.m_flag = 0;
    }
   
    if(status & I2C_INT_NO_ACK)
    {
        I2CMasterIntDisableEx(SOC_I2C_0_REGS, I2C_INT_TRANSMIT_READY  |
                                              I2C_INT_RECV_READY      |
                                              I2C_INT_NO_ACK          |
                                              I2C_INT_STOP_CONDITION);
        /* Generate a STOP */
        I2CMasterStop(SOC_I2C_0_REGS);

        s_I2C.m_flag = 0;
    }

}

#endif //__I2C_EEPROM_H