#ifndef _PIN_H
#define _PIN_H

#include "am335x_gpio.h"
#include "CONTROL_MODULE.h"
#include "GPIO.h"


namespace PINS
{
    #define CTRLMREG(x)                              \
    (*((REGS::CONTROL_MODULE::conf_module_pin_reg_t *)(REGS::CONTROL_MODULE::AM335x_CONTROL_MODULE_BASE + x)))

    enum class e_GPMC_A5 : uint8_t
    {    
        gpmc_a5         = 0, // O 
        gmii2_txd0      = 1, // O
        rgmii2_td0      = 2, // O
        rmii2_txd0      = 3, // O
        gpmc_a21        = 4, // O
        pr1_mii1_rxd3   = 5, // I
        eQEP1B_in       = 6, // I
        gpio1_21        = 7, // I/O
    
    };

    enum class e_GPMC_A6 : uint8_t
    {    
        gpmc_a6         = 0, // O 
        gmii2_txclk     = 1, // I
        rgmii2_tclk     = 2, // O
        mmc2_dat4       = 3, // I/O
        gpmc_a22        = 4, // O
        pr1_mii1_rxd2   = 5, // I
        eQEP1_index     = 6, // I/O
        gpio1_22        = 7, // I/O
    
    };

    enum class e_GPMC_A7 : uint8_t
    {    
        gpmc_a7         = 0, // O 
        gmii2_rxclk     = 1, // I
        rgmii2_rclk     = 2, // I
        mmc2_dat5       = 3, // I/O
        gpmc_a23        = 4, // O
        pr1_mii1_rxd1   = 5, // I
        eQEP1_strobe    = 6, // I/O
        gpio1_23        = 7, // I/O
    
    };

    enum class e_GPMC_A8 : uint8_t
    {    
        gpmc_a8         = 0, // O
        gmii2_rxd3      = 1, // I
        rgmii2_rd3      = 2, // I
        mmc2_dat6       = 3, // I/O
        gpmc_a24        = 4, // O
        pr1_mii1_rxd0   = 5, // I
        mcasp0_aclkx    = 6, // I/O
        gpio1_24        = 7, // I/O
    
    };

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin
    {
    public:   
                      pin(REGS::GPIO::AM335x_GPIO_Type *gpio_module);
                     ~pin(){ }
            
                void  init();        
                void  switch_function(T function);
                void  dir_set(REGS::GPIO::e_PINDIR pindir);
REGS::GPIO::e_PINDIR  dir_get();

                void  set();
                void  clear();
                void  toggle();
         inline bool  read() const { return (bool)(m_gpio_regs.DATAIN.reg & m_pinbitmsk); }        
    
    private:

                       REGS::GPIO::AM335x_GPIO_Type &m_gpio_regs;
        REGS::CONTROL_MODULE::conf_module_pin_reg_t &m_cntrmdl_reg;
                                           uint32_t  m_pinnum;
                                           uint32_t  m_pinbitmsk;
    };

    extern pin<e_GPMC_A5, 21U, 0x854> gpmc_a5;
    extern pin<e_GPMC_A6, 22U, 0x858> gpmc_a6;
    extern pin<e_GPMC_A7, 23U, 0x85C> gpmc_a7;
    extern pin<e_GPMC_A8, 24U, 0x860> gpmc_a8;

}  // namespace PINS

#endif // _PIN_H