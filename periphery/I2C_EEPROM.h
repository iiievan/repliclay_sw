#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H

#include "HS_I2C.h"
#include "PRCM.h"
#include "INTC.h"
#include "CONTROL_MODULE.h"
#include <cstring>

#define  SLAVE_ADDR_24LC32A     (0x50) // I2C address of 24LC32A eeprom
#define  SLAVE_ADDR_CAT24C256   (0x54) // I2C address of CAT24C256 eeprom

#define   STRT_SEQ_TRYES_NUM    (20)
typedef union 
{
    struct 
    { 
        uint8_t   lsb;   // A0..A7
        uint8_t   msb;   // A15..A8	 
    };
    uint16_t   addr;
} EEPROM_byte_address_t;

extern void  BRDINFO_24LC32A_irqhandler(void *p_obj);
extern void  CAT24C256WI_irqhandler(void *p_obj);

 
/** To instantiate object, it is necessary to specify the size of the memory page and the amount of EEPROM memory **/
template <auto EEPROM_SIZE = (32*1024), auto PAGE_SIZE = 32> 
class I2C_EEPROM : public HS_I2C
{
   
public:
  
          enum e_Transaction_fsm_sts : uint32_t
          {
              IDLE                = 0x0,  // nothing to happen, readi to operation
              STARTED             = 0x1,  // transaction started, start condition has occured
              NACK_DURING_START   = 0x2,  // EEPROM write busy after prevous operation
              ARDY                = 0x3,  // tx finished, and all registers ready to next operation
              STOPPED             = 0x4   // transaction finished, stop condition has occured 
          };
          
          I2C_EEPROM(I2C::AM335x_I2C_Type *p_i2c_regs, uint8_t slave_address, INTC::isr_handler_t isr_hndlr);
         ~I2C_EEPROM() {}   

    void  setup(I2C::e_CLK_FREQUENCY output_freq = I2C::F_400KHz);                //100kHz by default
    void  AINTC_configure(void);
    void  clean_interrupts(void);                                                 // Clear status of all interrupts 
    void  generate_STOP_with_IRQ();
  
    void  write_byte(EEPROM_byte_address_t byte_addr, uint8_t data);              // write one byte
    void  write(EEPROM_byte_address_t byte_addr, uint8_t *data, size_t d_count);  // write multiple bytes until page end
    void  write_page(EEPROM_byte_address_t byte_addr, uint8_t *page_data);        // write page to the end
 uint8_t  immediate_read();                                                       // immediate read byte accessed by prevous operation
 uint8_t  read_byte(EEPROM_byte_address_t byte_addr);                             // selective read byte by address
uint8_t*  read(EEPROM_byte_address_t byte_addr, size_t d_count);                  // sequential read multiple bytes
    
    void  sys_interrupt_enable()  { m_int_controller.system_enable(m_I2C_sys_interrupt);  }
    void  sys_interrupt_disable() { m_int_controller.system_disable(m_I2C_sys_interrupt); }
    void  irq_handler();
    
private:
          INTC::isr_handler_t  m_isr_handler;
           I2C::e_I2C_SER_NUM  m_I2C_number;
        INTC::e_SYS_INTERRUPT  m_I2C_sys_interrupt;

    power_reset_clock_control &m_prcm_module;      // for clock contrlol setup and management
         Interrupt_controller &m_int_controller;   // for interrupt setup and management
             x_CONTROL_MODULE &m_pinmux_ctrl;      // for PINMUX

                     uint32_t  m_t_count;
                     uint32_t  m_r_count;
        e_Transaction_fsm_sts  m_transaction_fsm { IDLE };
                     uint16_t  m_num_of_bytes;
                      uint8_t  m_data_to_slave[PAGE_SIZE + 2];     // 2 for msb and lsb address values
                      uint8_t  m_data_from_slave[PAGE_SIZE];   
                    
                      uint8_t  m_slave_address;
                     uint32_t  m_Pages_max;
};

extern I2C_EEPROM<(32*1024),32> BRDINFO_24LC32A;
extern I2C_EEPROM<(32*1024),64> CAT24C256WI;

#endif //__I2C_EEPROM_H