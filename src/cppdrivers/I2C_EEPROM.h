#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H

#include "HS_I2C.h"
#include "PRCM.h"
#include "CONTROL_MODULE.h"

#define  I2C_SLAVE_ADDR   (0x50) // I2C address of CAT24C256 e2prom

void I2C_irqhandler(void *p_obj);

class I2C_EEPROM : public HS_I2C
{
    friend void I2C_irqhandler(void *p_obj);
    
public:
          I2C_EEPROM(I2C::AM335x_I2C_Type *p_i2c_regs, uint8_t address);
          ~I2C_EEPROM() {}   

          void  setup(I2C::e_CLK_FREQUENCY output_freq = I2C::F_400KHz);   //100kHz by default
    void  AINTC_configure(void);
    void  clean_interrupts(void);                 // Clear status of all interrupts
    
    void  transmit(uint16_t d_count);             // Transmit data over I2C bus
    void  receive(uint16_t d_count);              // Receives data over I2C bus
    void  setup_to_receive(uint16_t d_count);     // 
    void  EEPROM_Read(uint8_t *data);             // Reads data from a specific address of e2prom
    
    void  sys_interrupt_enable()  { m_int_controller.system_enable(m_I2C_sys_interrupt);  }
    void  sys_interrupt_disable() { m_int_controller.system_disable(m_I2C_sys_interrupt); }

private:
          INTC::isr_handler_t  m_isr_handler;
           I2C::e_I2C_SER_NUM  m_I2C_number;
        INTC::e_SYS_INTERRUPT  m_I2C_sys_interrupt;

    power_reset_clock_control &m_prcm_module;      // for clock contrlol setup and management
         Interrupt_controller &m_int_controller;   // for interrupt setup and management
             x_CONTROL_MODULE &m_pinmux_ctrl;      // for PINMUX

                     uint32_t  m_t_count;
                     uint32_t  m_r_count;
                         bool  m_Wait_flag;
                     uint16_t  m_num_of_bytes;
                      uint8_t  m_data_to_slave[2];
                      uint8_t  m_data_from_slave[50];
                    
                      uint8_t  m_slave_address;
                      uint8_t  m_E2PROM_ADDR_MSB;   // Higher byte address (i.e A8-A15)
                      uint8_t  m_E2PROM_ADDR_LSB;   // Lower byte address (i.e A0-A7)
};

extern I2C_EEPROM BRDINFO_24LC32A;

#endif //__I2C_EEPROM_H