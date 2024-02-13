#include "pin.h"

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
    void pin<T, pinnum, ctrlm_reg>::sel_pinmode(T pinmode)
    {
        m_cntrmdl_reg.b.mode = (uint8_t)pinmode;
    } 
    
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>  
    void pin<T, pinnum, ctrlm_reg>::pullup_enable(bool pull_en)
    {
        if(pull_en)
            m_cntrmdl_reg.b.puden = REGS::CONTROL_MODULE::PULL_ENABLED;
        else
            m_cntrmdl_reg.b.puden = REGS::CONTROL_MODULE::PULL_DISABLED;
    } 
    
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>  
    void pin<T, pinnum, ctrlm_reg>::sel_pull_type(REGS::CONTROL_MODULE::e_PUTYPESEL putypesel)
    {
        m_cntrmdl_reg.b.putypesel = putypesel;
    } 
    
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>  
    void pin<T, pinnum, ctrlm_reg>::sel_rxactive(REGS::CONTROL_MODULE::e_RXACTIVE rxactive)
    {
        m_cntrmdl_reg.b.rxactive = rxactive;
    } 

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>  
    void pin<T, pinnum, ctrlm_reg>::sel_slewrate(REGS::CONTROL_MODULE::e_SLEWCTRL slewctrl)
    {
        m_cntrmdl_reg.b.slewctrl = slewctrl;
    }
    
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>
    void pin<T, pinnum, ctrlm_reg>::dir_set(REGS::GPIO::e_PINDIR pindir)
    {
        if(REGS::GPIO::GPIO_INPUT == pindir)  
        {                                         
            m_gpio_regs.OE.reg |= m_pinbitmsk; // config as input
            m_cntrmdl_reg.b.rxactive = REGS::CONTROL_MODULE::INPUT_ENABLE; 
        }
        else
        {
            m_gpio_regs.OE.reg &= ~m_pinbitmsk; // config as output
            m_cntrmdl_reg.b.rxactive = REGS::CONTROL_MODULE::INPUT_DISABLE; 
        }
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
        m_gpio_regs.SETDATAOUT.reg = m_pinbitmsk; 
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::clear()
    {
        m_gpio_regs.CLEARDATAOUT.reg = m_pinbitmsk; 
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::toggle()
    {
        if(m_gpio_regs.DATAOUT.reg & m_pinbitmsk)
            m_gpio_regs.CLEARDATAOUT.reg = m_pinbitmsk; 
        else
            m_gpio_regs.SETDATAOUT.reg = m_pinbitmsk;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::write(bool value)
    {
        if(value)
            m_gpio_regs.SETDATAOUT.reg = m_pinbitmsk;
        else
            m_gpio_regs.CLEARDATAOUT.reg = m_pinbitmsk;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::debounce_enable()
    {
        m_gpio_regs.DEBOUNCENABLE.reg &= ~m_pinbitmsk;  // clear bit in register
        m_gpio_regs.DEBOUNCENABLE.reg |= m_pinbitmsk;   // program bit in register
    } 

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg>                 
    void  pin<T, pinnum, ctrlm_reg>::debounce_disable()
    {
        m_gpio_regs.DEBOUNCENABLE.reg &= ~m_pinbitmsk;  // clear bit in register
        m_gpio_regs.DEBOUNCENABLE.reg &= ~m_pinbitmsk;  // program bit in register
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::int_enable(uint32_t intline)
    {
        if(REGS::GPIO::INT_LINE_1 == intline)
            m_gpio_regs.IRQSTATUS_SET_0.reg = m_pinbitmsk;
        else
            m_gpio_regs.IRQSTATUS_SET_1.reg = m_pinbitmsk;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::int_disable(uint32_t intline)
    {
        if(REGS::GPIO::INT_LINE_1 == intline)
            m_gpio_regs.IRQSTATUS_CLR_0.reg = m_pinbitmsk;
        else 
            m_gpio_regs.IRQSTATUS_CLR_1.reg = m_pinbitmsk;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::int_type_set(REGS::GPIO::e_INT_TYPE evnt_type)
    {
        switch(evnt_type)
        {
            case REGS::GPIO::INT_TYPE_NO_LEVEL:              
                // Disabling logic LOW level detect interrupt generation.
                m_gpio_regs.LEVELDETECT0.reg &= ~m_pinbitmsk;
                // Disabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg &= ~m_pinbitmsk;
    
                break;
            case REGS::GPIO::INT_TYPE_LEVEL_LOW:                
                // Enabling logic LOW level detect interrupt geenration.
                m_gpio_regs.LEVELDETECT0.reg  |=  m_pinbitmsk;
                // Disabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;
                // Disabling rising edge detect interrupt generation.
                m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                // Disabling falling edge detect interrupt generation.
                m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;
                
                break;
            case REGS::GPIO::INT_TYPE_LEVEL_HIGH:    
                // Disabling logic LOW level detect interrupt generation. 
                m_gpio_regs.LEVELDETECT0.reg  &=  ~m_pinbitmsk;
                // Enabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg  |=  m_pinbitmsk;
                // Disabling rising edge detect interrupt generation. 
                m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                // Disabling falling edge detect interrupt generation. 
                m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;
    
                break;
            case REGS::GPIO::INT_TYPE_BOTH_LEVEL:              
                // Enabling logic LOW level detect interrupt geenration.
                m_gpio_regs.LEVELDETECT0.reg  |=  m_pinbitmsk;
                // Enabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg  |=  m_pinbitmsk;
                // Disabling rising edge detect interrupt generation.
                m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                // Disabling falling edge detect interrupt generation.
                m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;            
                
                break;            
            case REGS::GPIO::INT_TYPE_NO_EDGE:               
                // Disabling rising edge detect interrupt generation.
                m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                // Disabling falling edge detect interrupt generation.
                m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk; 
    
                break;
            case REGS::GPIO::INT_TYPE_RISE_EDGE:    
                // Enabling rising edge detect interrupt generation. 
                m_gpio_regs.RISINGDETECT.reg  |=  m_pinbitmsk;
                // Disabling falling edge detect interrupt generation. 
                m_gpio_regs.FALLINGDETECT.reg &= ~m_pinbitmsk;
                // Disabling logic LOW level detect interrupt generation.
                m_gpio_regs.LEVELDETECT0.reg  &= ~m_pinbitmsk;
                // Disabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;
    
                break;
            case REGS::GPIO::INT_TYPE_FALL_EDGE:    
                // Disabling rising edge detect interrupt generation.
                m_gpio_regs.RISINGDETECT.reg  &= ~m_pinbitmsk;
                // Enabling falling edge detect interrupt generation.
                m_gpio_regs.FALLINGDETECT.reg |=  m_pinbitmsk;
                // Disabling logic LOW level detect interrupt generation.
                m_gpio_regs.LEVELDETECT0.reg  &= ~m_pinbitmsk;
                // Disabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;
    
                break;
            case REGS::GPIO::INT_TYPE_BOTH_EDGE:    
                // Enabling rising edge detect interrupt generation.
                m_gpio_regs.RISINGDETECT.reg  |=  m_pinbitmsk;
                // Enabling falling edge detect interrupt generation.
                m_gpio_regs.FALLINGDETECT.reg |=  m_pinbitmsk;
                // Disabling logic LOW level detect interrupt generation.
                m_gpio_regs.LEVELDETECT0.reg  &= ~m_pinbitmsk;
                // Disabling logic HIGH level detect interrupt generation.
                m_gpio_regs.LEVELDETECT1.reg  &= ~m_pinbitmsk;
    
                break;
            default:
                break;
        }
    }  

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    uint32_t  pin<T, pinnum, ctrlm_reg>::int_type_get()
    {
        uint32_t int_event = (REGS::GPIO::INT_TYPE_NO_LEVEL | 
                              REGS::GPIO::INT_TYPE_NO_EDGE);

        // Checking if logic LOW level trigger interrupt is enabled.
        if(m_gpio_regs.LEVELDETECT0.reg & m_pinbitmsk)
        {
            int_event &= ~(REGS::GPIO::INT_TYPE_NO_LEVEL);
            int_event |=  REGS::GPIO::INT_TYPE_LEVEL_LOW;
        }
    
        // Checking if logic HIGH level trigger interrupt is enabled. 
        if(m_gpio_regs.LEVELDETECT1.reg & m_pinbitmsk)
        {
            int_event &= ~(REGS::GPIO::INT_TYPE_NO_LEVEL);
            int_event |=  REGS::GPIO::INT_TYPE_LEVEL_HIGH;
        }
    
        // Checking if rising edge trigger interrupt is enabled.
        if(m_gpio_regs.RISINGDETECT.reg & m_pinbitmsk)
        {
            int_event &= ~(REGS::GPIO::INT_TYPE_NO_EDGE);
            int_event |=  REGS::GPIO::INT_TYPE_RISE_EDGE;
        }
    
        // Checking if falling edge trigger interrupt is enabled.
        if(m_gpio_regs.FALLINGDETECT.reg & m_pinbitmsk)
        {
            int_event &= ~(REGS::GPIO::INT_TYPE_NO_EDGE);
            int_event |=  REGS::GPIO::INT_TYPE_FALL_EDGE;
        }
    
        return int_event;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    bool  pin<T, pinnum, ctrlm_reg>::int_status(uint32_t intline)
    {
        bool int_sts = false;
    
        if(REGS::GPIO::INT_LINE_1 == intline)
            int_sts = (m_gpio_regs.IRQSTATUS_0.reg & m_pinbitmsk);
        else 
            int_sts = (m_gpio_regs.IRQSTATUS_1.reg & m_pinbitmsk);
    
        return int_sts;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    bool  pin<T, pinnum, ctrlm_reg>::raw_int_status(uint32_t intline)
    {
        bool int_sts = false;
    
        if(REGS::GPIO::INT_LINE_1 == intline)
            int_sts = (m_gpio_regs.IRQSTATUS_RAW_0.reg & m_pinbitmsk);
        else  
            int_sts = (m_gpio_regs.IRQSTATUS_RAW_1.reg & m_pinbitmsk);

    
        return int_sts;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::int_clear(uint32_t intline)
    {
        if(REGS::GPIO::INT_LINE_1 == intline)
            m_gpio_regs.IRQSTATUS_0.reg = m_pinbitmsk;
        else
            m_gpio_regs.IRQSTATUS_1.reg = m_pinbitmsk;

    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::trigger_int(uint32_t intline)
    {
        if(REGS::GPIO::INT_LINE_1 == intline)
            m_gpio_regs.IRQSTATUS_RAW_0.reg = m_pinbitmsk;
        else
            m_gpio_regs.IRQSTATUS_RAW_1.reg = m_pinbitmsk;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::int_wakeup_enable(uint32_t intline)
    {
        if(REGS::GPIO::INT_LINE_1 == intline)
            m_gpio_regs.IRQWAKEN_0.reg |= m_pinbitmsk;
        else
            m_gpio_regs.IRQWAKEN_1.reg |= m_pinbitmsk;
    }

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    void  pin<T, pinnum, ctrlm_reg>::int_wakeup_disable(uint32_t intline)
    {
        if(REGS::GPIO::INT_LINE_1 == intline)
            m_gpio_regs.IRQWAKEN_0.reg &= ~m_pinbitmsk;
        else
            m_gpio_regs.IRQWAKEN_1.reg &= ~m_pinbitmsk;
    }

    template class pin<e_GPMC_A5, 21U, 0x854>;
    template class pin<e_GPMC_A6, 22U, 0x858>;
    template class pin<e_GPMC_A7, 23U, 0x85C>;
    template class pin<e_GPMC_A8, 24U, 0x860>;

    template class pin<e_GPMC_WAIT0, 30U, 0x870>;
    template class pin<e_UART1_RTSn, 13U, 0x97C>;
    template class pin<e_UART1_CTSn, 12U, 0x978>;
    template class pin<e_UART0_TXD,  11U, 0x974>;
    template class pin<e_UART0_RXD,  10U, 0x970>;
    template class pin<e_XDMA_EVENT_INTR1, 20U, 0x9B4>;

    template class pin<e_LCD_DATA1, 7U, 0x8A4>;
    template class pin<e_LCD_DATA3, 9U, 0x8AC>;
    template class pin<e_LCD_DATA5, 11U, 0x8B4>;
    template class pin<e_LCD_DATA7, 13U, 0x8BC>;

}   // namespace PINS

