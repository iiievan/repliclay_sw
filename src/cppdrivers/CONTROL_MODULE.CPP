#include "CONTROL_MODULE.h"

x_CONTROL_MODULE ctrl_module;

x_CONTROL_MODULE::x_CONTROL_MODULE()
: m_CTRL_MODULE_regs(*CONTROL_MODULE::AM335x_CONTROL_MODULE)
{ }
                     
void  x_CONTROL_MODULE::I2C0_pin_mux_setup()
{    
    m_CTRL_MODULE_regs.conf_i2c0_sda.b.putypesel = CONTROL_MODULE::PULL_UP;
    m_CTRL_MODULE_regs.conf_i2c0_sda.b.rxactive  = CONTROL_MODULE::INPUT_ENABLE;
    m_CTRL_MODULE_regs.conf_i2c0_sda.b.slewctrl  = CONTROL_MODULE::SLOW;

    m_CTRL_MODULE_regs.conf_i2c0_scl.b.putypesel = CONTROL_MODULE::PULL_UP;
    m_CTRL_MODULE_regs.conf_i2c0_scl.b.rxactive  = CONTROL_MODULE::INPUT_ENABLE;
    m_CTRL_MODULE_regs.conf_i2c0_scl.b.slewctrl  = CONTROL_MODULE::SLOW;
}

void  x_CONTROL_MODULE::I2C1_pin_mux_setup()
{
    /** I2C_SCLK **/
    m_CTRL_MODULE_regs.conf_spi0_d1.b.putypesel = CONTROL_MODULE::PULL_UP;
    m_CTRL_MODULE_regs.conf_spi0_d1.b.rxactive  = CONTROL_MODULE::INPUT_ENABLE;
    m_CTRL_MODULE_regs.conf_spi0_d1.b.slewctrl  = CONTROL_MODULE::SLOW;
    m_CTRL_MODULE_regs.conf_spi0_d1.b.mode      = CONTROL_MODULE::PINMODE_2;
   
    /** I2C_SDA **/
    m_CTRL_MODULE_regs.conf_spi0_cs0.b.putypesel = CONTROL_MODULE::PULL_UP;
    m_CTRL_MODULE_regs.conf_spi0_cs0.b.rxactive  = CONTROL_MODULE::INPUT_ENABLE;
    m_CTRL_MODULE_regs.conf_spi0_cs0.b.slewctrl  = CONTROL_MODULE::SLOW; 
    m_CTRL_MODULE_regs.conf_spi0_cs0.b.mode      = CONTROL_MODULE::PINMODE_2;          
}

void  x_CONTROL_MODULE::I2C2_pin_mux_setup()
{
    /** I2C_SCLK **/ 
    m_CTRL_MODULE_regs.conf_uart1_rtsn.b.putypesel = CONTROL_MODULE::PULL_UP;
    m_CTRL_MODULE_regs.conf_uart1_rtsn.b.rxactive  = CONTROL_MODULE::INPUT_ENABLE;
    m_CTRL_MODULE_regs.conf_uart1_rtsn.b.slewctrl  = CONTROL_MODULE::SLOW;
    m_CTRL_MODULE_regs.conf_uart1_rtsn.b.mode      = CONTROL_MODULE::PINMODE_3;
   
    /** I2C_SDA **/ 
    m_CTRL_MODULE_regs.conf_uart1_ctsn.b.putypesel = CONTROL_MODULE::PULL_UP;
    m_CTRL_MODULE_regs.conf_uart1_ctsn.b.rxactive  = CONTROL_MODULE::INPUT_ENABLE;
    m_CTRL_MODULE_regs.conf_uart1_ctsn.b.slewctrl  = CONTROL_MODULE::SLOW; 
    m_CTRL_MODULE_regs.conf_uart1_ctsn.b.mode      = CONTROL_MODULE::PINMODE_3;
}