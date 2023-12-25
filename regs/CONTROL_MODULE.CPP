#include "CONTROL_MODULE.h"

namespace REGS
{  
    namespace CONTROL_MODULE
    {                      
        void  I2C0_pin_mux_setup()
        {    
            AM335x_CONTROL_MODULE->conf_i2c0_sda.b.putypesel = PULL_UP;
            AM335x_CONTROL_MODULE->conf_i2c0_sda.b.rxactive  = INPUT_ENABLE;
            AM335x_CONTROL_MODULE->conf_i2c0_sda.b.slewctrl  = SLOW;
        
            AM335x_CONTROL_MODULE->conf_i2c0_scl.b.putypesel = PULL_UP;
            AM335x_CONTROL_MODULE->conf_i2c0_scl.b.rxactive  = INPUT_ENABLE;
            AM335x_CONTROL_MODULE->conf_i2c0_scl.b.slewctrl  = SLOW;
        }
    
        void  I2C1_pin_mux_setup()
        {
            /** I2C_SCLK **/
            AM335x_CONTROL_MODULE->conf_spi0_d1.b.putypesel  = PULL_UP;
            AM335x_CONTROL_MODULE->conf_spi0_d1.b.rxactive   = INPUT_ENABLE;
            AM335x_CONTROL_MODULE->conf_spi0_d1.b.slewctrl   = SLOW;
            AM335x_CONTROL_MODULE->conf_spi0_d1.b.mode       = PINMODE_2;
           
            /** I2C_SDA **/
            AM335x_CONTROL_MODULE->conf_spi0_cs0.b.putypesel = PULL_UP;
            AM335x_CONTROL_MODULE->conf_spi0_cs0.b.rxactive  = INPUT_ENABLE;
            AM335x_CONTROL_MODULE->conf_spi0_cs0.b.slewctrl  = SLOW; 
            AM335x_CONTROL_MODULE->conf_spi0_cs0.b.mode      = PINMODE_2;          
        }
    
        void  I2C2_pin_mux_setup()
        {
            /** I2C_SCLK **/ 
            AM335x_CONTROL_MODULE->conf_uart1_rtsn.b.putypesel = PULL_UP;
            AM335x_CONTROL_MODULE->conf_uart1_rtsn.b.rxactive  = INPUT_ENABLE;
            AM335x_CONTROL_MODULE->conf_uart1_rtsn.b.slewctrl  = SLOW;
            AM335x_CONTROL_MODULE->conf_uart1_rtsn.b.mode      = PINMODE_3;
           
            /** I2C_SDA **/ 
            AM335x_CONTROL_MODULE->conf_uart1_ctsn.b.putypesel = PULL_UP;
            AM335x_CONTROL_MODULE->conf_uart1_ctsn.b.rxactive  = INPUT_ENABLE;
            AM335x_CONTROL_MODULE->conf_uart1_ctsn.b.slewctrl  = SLOW; 
            AM335x_CONTROL_MODULE->conf_uart1_ctsn.b.mode      = PINMODE_3;
        }
    
        void  UART0_pin_mux_setup()
        {
           /** RXD **/
           AM335x_CONTROL_MODULE->conf_uart0_rxd.b.putypesel = PULL_UP;
           AM335x_CONTROL_MODULE->conf_uart0_rxd.b.putypesel = INPUT_ENABLE;
            
           /** TXD **/
           AM335x_CONTROL_MODULE->conf_uart0_txd.b.putypesel = PULL_UP;
        }

    }   //namespace CONTROL_MODULE
    
}   //namespace REGS

