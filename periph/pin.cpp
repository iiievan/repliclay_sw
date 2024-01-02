#include "pin.h"
#include "PRCM.h"

namespace PINS
{
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    pin<T, pinnum, ctrlm_reg>::pin(REGS::GPIO::AM335x_GPIO_Type *gpio_module)
    : m_gpio_regs(*gpio_module),
      m_cntrmdl_reg(CTRLMREG(ctrlm_reg)),
      m_pinnum(pinnum)
    {
        m_pinbitmsk = (1 << m_pinnum);
    }              
     
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>  
    void pin<T, pinnum, ctrlm_reg>::init()
    {
        REGS::PRCM::run_clk_GPIO1();
    }   

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>  
    void pin<T, pinnum, ctrlm_reg>::switch_function(T function)
    {
        m_cntrmdl_reg.b.mode = (uint8_t)function;
    } 

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>
    void pin<T, pinnum, ctrlm_reg>::dir_set(REGS::GPIO::e_PINDIR pindir)
    {
        if(REGS::GPIO::GPIO_INPUT == pindir)                                             
            m_gpio_regs.OE.reg |= m_pinbitmsk; // config as input
        else
            m_gpio_regs.OE.reg &= ~m_pinbitmsk; // config as output
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>
    REGS::GPIO::e_PINDIR  pin<T, pinnum, ctrlm_reg>::dir_get()
    {
        REGS::GPIO::e_PINDIR result = REGS::GPIO::GPIO_INPUT;
    
        if(!(m_gpio_regs.OE.reg & m_pinbitmsk))
        {
            result = REGS::GPIO::GPIO_OUTPUT;
        }
    
        return result;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::set()
    {
        m_gpio_regs.SETDATAOUT.reg |= m_pinbitmsk; 
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::clear()
    {
        m_gpio_regs.CLEARDATAOUT.reg |= m_pinbitmsk; 
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::toggle()
    {
        if(m_gpio_regs.DATAOUT.reg & m_pinbitmsk)
            m_gpio_regs.CLEARDATAOUT.reg |= m_pinbitmsk; 
        else
            m_gpio_regs.SETDATAOUT.reg |= m_pinbitmsk;
    }

    template class pin<e_GPMC_A5, 21U, 0x854>;
    template class pin<e_GPMC_A6, 22U, 0x858>;
    template class pin<e_GPMC_A7, 23U, 0x85C>;
    template class pin<e_GPMC_A8, 24U, 0x860>;
    
    pin<e_GPMC_A5, 21U, 0x854> gpmc_a5(REGS::GPIO::AM335x_GPIO_1);
    pin<e_GPMC_A6, 22U, 0x858> gpmc_a6(REGS::GPIO::AM335x_GPIO_1);
    pin<e_GPMC_A7, 23U, 0x85C> gpmc_a7(REGS::GPIO::AM335x_GPIO_1);
    pin<e_GPMC_A8, 24U, 0x860> gpmc_a8(REGS::GPIO::AM335x_GPIO_1);

}   // namespace PINS