#include "am335x_gpio.h"
#include "PRCM.h"
#include "utils.h"

am335x_gpio::am335x_gpio(REGS::GPIO::AM335x_GPIO_Type *p_gpio_regs)
:m_regs(*p_gpio_regs),
 m_regs_adr((uint32_t)p_gpio_regs)
{
  
}

void  am335x_gpio::init()
{
    switch(m_regs_adr)
    {
        case REGS::GPIO::AM335x_GPIO_0_BASE:
            REGS::PRCM::run_clk_GPIO0();
            break;
        case REGS::GPIO::AM335x_GPIO_1_BASE:
            REGS::PRCM::run_clk_GPIO1();
            break;
        case REGS::GPIO::AM335x_GPIO_2_BASE:
            REGS::PRCM::run_clk_GPIO2();
            break;
        case REGS::GPIO::AM335x_GPIO_3_BASE:
            REGS::PRCM::run_clk_GPIO3();
            break;
        default:
          return;      
    }

    module_enable();
    module_reset();
}
    
void  am335x_gpio::module_reset()
{
    //Setting the SOFTRESET bit in System Configuration register.
    //Doing so would reset the GPIO module.
    m_regs.SYSCONFIG.b.SOFTRESET = HIGH;
    
    while(!m_regs.SYSSTATUS.b.RESETDONE);
}

void  am335x_gpio::module_enable()
{
    m_regs.CTRL.b.DISABLEMODULE = LOW;
}

void  am335x_gpio::module_disable()
{
    m_regs.CTRL.b.DISABLEMODULE = HIGH;
}

void  am335x_gpio::multiple_pins_write(uint32_t setmsk, uint32_t clrmsk)
{
    // Setting the specified output pins in GPIO_DATAOUT register.
    m_regs.SETDATAOUT.reg = setmsk;

    // Clearing the specified output pins in GPIO_DATAOUT register.
    m_regs.CLEARDATAOUT.reg = clrmsk;
}

uint32_t  am335x_gpio::multiple_pins_read(uint32_t readmsk)
{
    return (m_regs.DATAIN.reg & readmsk);
}

void  am335x_gpio::wakeup_global_enable()
{
    // Setting the ENAWAKEUP bit in SYSCONFIG register.
    //HWREG(baseAdd + GPIO_SYSCONFIG) |= (GPIO_SYSCONFIG_ENAWAKEUP);
    m_regs.SYSCONFIG.b.ENAWAKEUP = HIGH;
}

void  am335x_gpio::wakeup_global_disable()
{
    // Clearing the ENAWAKEUP bit in SYSCONFIG register.
    //HWREG(baseAdd + GPIO_SYSCONFIG) &= ~(GPIO_SYSCONFIG_ENAWAKEUP);
    m_regs.SYSCONFIG.b.ENAWAKEUP = LOW;
}

void  am335x_gpio::auto_idle_mode_control(bool mode_flag)
{
    // Clearing the AUTOIDLE bit in System Configuration Register.
    //HWREG(baseAdd + GPIO_SYSCONFIG) &= ~(GPIO_SYSCONFIG_AUTOIDLE);
    m_regs.SYSCONFIG.b.AUTOIDLE = LOW;

    // Programming the AUTOIDLE bit in System Configuration Register.
    //HWREG(baseAdd + GPIO_SYSCONFIG) |= (mode_flag & GPIO_SYSCONFIG_AUTOIDLE);
    m_regs.SYSCONFIG.b.AUTOIDLE = mode_flag;
}

void  am335x_gpio::idle_mode_configure(REGS::GPIO::e_IDLEMODE mode_flag)
{
    // Clearing the IDLEMODE field in System Configuration Register.
    //HWREG(baseAdd + GPIO_SYSCONFIG) &= ~(GPIO_SYSCONFIG_IDLEMODE);
    m_regs.SYSCONFIG.b.IDLEMODE = 0x0;

    // Programming the IDLEMODE field in System Configuration Register.
    //HWREG(baseAdd + GPIO_SYSCONFIG) |= (mode_flag & GPIO_SYSCONFIG_IDLEMODE);
    m_regs.SYSCONFIG.b.IDLEMODE = mode_flag;
}

void  am335x_gpio::gating_ratio_configure(REGS::GPIO::e_GATINGRATIO config_flag)
{
    // Clearing the GATINGRATIO field in GPIO_CTRL register.
    //HWREG(baseAdd + GPIO_CTRL) &= ~(GPIO_CTRL_GATINGRATIO);
    m_regs.CTRL.b.GATINGRATIO = 0x0;

    // Programming the GATINGRATIO field in GPIO_CTRL register.
    //HWREG(baseAdd + GPIO_CTRL) |= (config_flag & GPIO_CTRL_GATINGRATIO);    
    m_regs.CTRL.b.GATINGRATIO = config_flag;
}

void  am335x_gpio::debounce_time_config(uint8_t debounce_time)
{
    // Programming the DEBOUNCETIME field in GPIO_DEBOUNCINGTIME register.
    //HWREG(baseAdd + GPIO_DEBOUNCINGTIME) = (debounce_time & GPIO_DEBOUNCINGTIME_DEBOUNCETIME);
    m_regs.DEBOUNCINGTIME.b.DEBOUNCETIME = debounce_time;
}

REGS::GPIO::GPIO_REVISION_reg_t  am335x_gpio::revision_info_get()
{
  REGS::GPIO::GPIO_REVISION_reg_t revision_reg;
                               revision_reg.reg =  m_regs.REVISION.reg;
                               
    //return(HWREG(baseAdd + GPIO_REVISION));
    return revision_reg;
}

void  am335x_gpio::gpio_context_save()
{
    m_context.ctrl = m_regs.CTRL.reg;           // HWREG(baseAdd + GPIO_CTRL);
    m_context.dir = m_regs.OE.reg;              // HWREG(baseAdd + GPIO_OE);
    m_context.data = m_regs.SETDATAOUT.reg;     //HWREG(baseAdd + GPIO_SETDATAOUT);
}

void  am335x_gpio::gpio_context_restore()
{
    m_regs.CTRL.reg = m_context.ctrl;
    m_regs.OE.reg = m_context.dir;
    m_regs.SETDATAOUT.reg = m_context.data;
    //HWREG(baseAdd + GPIO_CTRL) = m_context.ctrl;
    //HWREG(baseAdd + GPIO_OE) = m_context.dir;
    //HWREG(baseAdd + GPIO_SETDATAOUT) = m_context.data;
}

/********************************************************************************************************************/  

/************************************** functions that duplicate the pin class **************************************/ 
    
/********************************************************************************************************************/

void  am335x_gpio::pin_write(uint32_t pinnum, bool value)
{
    if(value)
        m_regs.SETDATAOUT.reg = (1 << pinnum);
    else
        m_regs.CLEARDATAOUT.reg = (1 << pinnum); 
}

uint32_t  am335x_gpio::pin_read(uint32_t pinnum)
{
    return (m_regs.DATAIN.reg & (1 << pinnum));    
}

void  am335x_gpio::pin_int_enable(uint32_t intline, uint32_t pinnum)
{
    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS_SET(0)) = (1 << pinnum);
        m_regs.IRQSTATUS_SET_0.reg = (1 << pinnum);
    }
    else     
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS_SET(1)) = (1 << pinnum);
        m_regs.IRQSTATUS_SET_1.reg = (1 << pinnum);
    }
}

void  am335x_gpio::pin_int_disable(uint32_t intline, uint32_t pinnum)
{
    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS_CLR(0)) = (1 << pinnum);
        m_regs.IRQSTATUS_CLR_0.reg = (1 << pinnum);
    }
    else 
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS_CLR(1)) = (1 << pinnum);
        m_regs.IRQSTATUS_CLR_1.reg = (1 << pinnum);
    }
}
      
void  am335x_gpio::int_type_set(uint32_t pinnum, REGS::GPIO::e_INT_TYPE evnt_type)
{
    switch(evnt_type)
    {
        case REGS::GPIO::INT_TYPE_NO_LEVEL:            
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinnum);            
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinnum);
          
            // Disabling logic LOW level detect interrupt generation.
            m_regs.LEVELDETECT0.reg &= ~(1 << pinnum);
            // Disabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg &= ~(1 << pinnum);

            break;
        case REGS::GPIO::INT_TYPE_LEVEL_LOW:
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinnum);
            
            // Enabling logic LOW level detect interrupt geenration.
            m_regs.LEVELDETECT0.reg  |=  (1 << pinnum);
            // Disabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg  &= ~(1 << pinnum);
            // Disabling rising edge detect interrupt generation.
            m_regs.RISINGDETECT.reg  &= ~(1 << pinnum);
            // Disabling falling edge detect interrupt generation.
            m_regs.FALLINGDETECT.reg &= ~(1 << pinnum);
            
            break;
        case REGS::GPIO::INT_TYPE_LEVEL_HIGH:
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinnum); 

            // Disabling logic LOW level detect interrupt generation. 
            m_regs.LEVELDETECT0.reg  &=  ~(1 << pinnum);
            // Enabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg  |=  (1 << pinnum);
            // Disabling rising edge detect interrupt generation. 
            m_regs.RISINGDETECT.reg  &= ~(1 << pinnum);
            // Disabling falling edge detect interrupt generation. 
            m_regs.FALLINGDETECT.reg &= ~(1 << pinnum);

            break;
        case REGS::GPIO::INT_TYPE_BOTH_LEVEL:            
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinnum);

            // Enabling logic LOW level detect interrupt geenration.
            m_regs.LEVELDETECT0.reg  |=  (1 << pinnum);
            // Enabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg  |=  (1 << pinnum);
            // Disabling rising edge detect interrupt generation.
            m_regs.RISINGDETECT.reg  &= ~(1 << pinnum);
            // Disabling falling edge detect interrupt generation.
            m_regs.FALLINGDETECT.reg &= ~(1 << pinnum);            
            
            break;            
        case REGS::GPIO::INT_TYPE_NO_EDGE:            
            //HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinnum);

            // Disabling rising edge detect interrupt generation.
            m_regs.RISINGDETECT.reg  &= ~(1 << pinnum);
            // Disabling falling edge detect interrupt generation.
            m_regs.FALLINGDETECT.reg &= ~(1 << pinnum); 

            break;
        case REGS::GPIO::INT_TYPE_RISE_EDGE:
            //HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinnum);

            // Enabling rising edge detect interrupt generation. 
            m_regs.RISINGDETECT.reg  |=  (1 << pinnum);
            // Disabling falling edge detect interrupt generation. 
            m_regs.FALLINGDETECT.reg &= ~(1 << pinnum);
            // Disabling logic LOW level detect interrupt generation.
            m_regs.LEVELDETECT0.reg  &= ~(1 << pinnum);
            // Disabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg  &= ~(1 << pinnum);

            break;
        case REGS::GPIO::INT_TYPE_FALL_EDGE:
            //HWREG(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinnum);

            // Disabling rising edge detect interrupt generation.
            m_regs.RISINGDETECT.reg  &= ~(1 << pinnum);
            // Enabling falling edge detect interrupt generation.
            m_regs.FALLINGDETECT.reg |=  (1 << pinnum);
            // Disabling logic LOW level detect interrupt generation.
            m_regs.LEVELDETECT0.reg  &= ~(1 << pinnum);
            // Disabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg  &= ~(1 << pinnum);

            break;
        case REGS::GPIO::INT_TYPE_BOTH_EDGE:
            //HWREG(baseAdd + GPIO_RISINGDETECT) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinnum);
            //HWREG(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinnum);

            // Enabling rising edge detect interrupt generation.
            m_regs.RISINGDETECT.reg  |=  (1 << pinnum);
            // Enabling falling edge detect interrupt generation.
            m_regs.FALLINGDETECT.reg |=  (1 << pinnum);
            // Disabling logic LOW level detect interrupt generation.
            m_regs.LEVELDETECT0.reg  &= ~(1 << pinnum);
            // Disabling logic HIGH level detect interrupt generation.
            m_regs.LEVELDETECT1.reg  &= ~(1 << pinnum);

            break;
        default:
            break;
    }
}

uint32_t  am335x_gpio::int_type_get(uint32_t pinnum)
{
    uint32_t int_event = (REGS::GPIO::INT_TYPE_NO_LEVEL | 
                          REGS::GPIO::INT_TYPE_NO_EDGE);

    // Checking if logic LOW level trigger interrupt is enabled.
    //if(HWREG(baseAdd + GPIO_LEVELDETECT(0)) & (1 << pinnum))
    if(m_regs.LEVELDETECT0.reg & (1 << pinnum))
    {
        int_event &= ~(REGS::GPIO::INT_TYPE_NO_LEVEL);
        int_event |=  REGS::GPIO::INT_TYPE_LEVEL_LOW;
    }

    // Checking if logic HIGH level trigger interrupt is enabled. 
    //if(HWREG(baseAdd + GPIO_LEVELDETECT(1)) & (1 << pinnum))
    if(m_regs.LEVELDETECT1.reg & (1 << pinnum))
    {
        int_event &= ~(REGS::GPIO::INT_TYPE_NO_LEVEL);
        int_event |=  REGS::GPIO::INT_TYPE_LEVEL_HIGH;
    }

    // Checking if rising edge trigger interrupt is enabled.
    //if(HWREG(baseAdd + GPIO_RISINGDETECT) & (1 << pinnum))
    if(m_regs.RISINGDETECT.reg & (1 << pinnum))
    {
        int_event &= ~(REGS::GPIO::INT_TYPE_NO_EDGE);
        int_event |=  REGS::GPIO::INT_TYPE_RISE_EDGE;
    }

    // Checking if falling edge trigger interrupt is enabled.
    //if(HWREG(baseAdd + GPIO_FALLINGDETECT) & (1 << pinnum))
    if(m_regs.FALLINGDETECT.reg & (1 << pinnum))
    {
        int_event &= ~(REGS::GPIO::INT_TYPE_NO_EDGE);
        int_event |=  REGS::GPIO::INT_TYPE_FALL_EDGE;
    }

    return int_event;
}

uint32_t  am335x_gpio::pin_int_status(uint32_t intline, uint32_t pinnum)
{
    uint32_t int_sts = 0;

    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //int_sts = (HWREG(baseAdd + GPIO_IRQSTATUS(0)) & (1 << pinnum));
        int_sts = (m_regs.IRQSTATUS_0.reg & (1 << pinnum));
    }
    else 
    {
        //int_sts = (HWREG(baseAdd + GPIO_IRQSTATUS(1)) & (1 << pinnum));
        int_sts = (m_regs.IRQSTATUS_1.reg & (1 << pinnum));
    }

    return int_sts;
}

void  am335x_gpio::pin_int_clear(uint32_t intline, uint32_t pinnum)
{
    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS(0)) = (1 << pinnum);
        m_regs.IRQSTATUS_0.reg = (1 << pinnum);
    }
    else
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS(1)) = (1 << pinnum);
        m_regs.IRQSTATUS_1.reg = (1 << pinnum);
    }
}

uint32_t  am335x_gpio::raw_int_status(uint32_t intline,uint32_t readmsk)
{
    uint32_t int_sts = 0;

    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //int_sts = HWREG(baseAdd + GPIO_IRQSTATUS_RAW(0)) & readmsk;
        int_sts = m_regs.IRQSTATUS_RAW_0.reg & readmsk;
    }
    else  
    {
        //int_sts = HWREG(baseAdd + GPIO_IRQSTATUS_RAW(1)) & readmsk;
        int_sts = m_regs.IRQSTATUS_RAW_1.reg & readmsk;
    }

    return int_sts;
}

void  am335x_gpio::trigger_pin_int(uint32_t intline, uint32_t pinnum)
{
    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS_RAW(0)) = (1 << pinnum);
        m_regs.IRQSTATUS_RAW_0.reg = (1 << pinnum);
    }
    else
    {
        //HWREG(baseAdd + GPIO_IRQSTATUS_RAW(1)) = (1 << pinnum);
        m_regs.IRQSTATUS_RAW_1.reg = (1 << pinnum);
    }
}

void  am335x_gpio::pin_int_wakeup_enable(uint32_t intline, uint32_t pinnum)
{
    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //HWREG(baseAdd + GPIO_IRQWAKEN(0)) |= (1 << pinnum);
        m_regs.IRQWAKEN_0.reg = (1 << pinnum);
    }
    else
    {
        //HWREG(baseAdd + GPIO_IRQWAKEN(1)) |= (1 << pinnum);
        m_regs.IRQWAKEN_1.reg = (1 << pinnum);
    }
}

void  am335x_gpio::pin_int_wakeup_disable(uint32_t intline, uint32_t pinnum)
{
    if(REGS::GPIO::INT_LINE_1 == intline)
    {
        //HWREG(baseAdd + GPIO_IRQWAKEN(0)) &= ~(1 << pinnum);
        m_regs.IRQWAKEN_0.reg &= ~(1 << pinnum);
    }
    else
    {
        //HWREG(baseAdd + GPIO_IRQWAKEN(1)) &= ~(1 << pinnum);
        m_regs.IRQWAKEN_1.reg &= ~(1 << pinnum);
    }
}

void  am335x_gpio::debounce_func_control(uint32_t pinnum, bool ctrl_flag)
{    
    // Clearing the DEBOUNCEENABLE[n] bit in GPIO_DEBOUNCEENABLE register.
    //HWREG(baseAdd + GPIO_DEBOUNCENABLE) &= ~(1 << pinnum);
    m_regs.DEBOUNCENABLE.reg&= ~(1 << pinnum);

    // Programming the DEBOUNCEENABLE[n] bit in GPIO_DEBOUNCEENABLE register.
    //HWREG(baseAdd + GPIO_DEBOUNCENABLE) |= (ctrl_flag  << pinnum);
    m_regs.DEBOUNCENABLE.reg |= (ctrl_flag << pinnum);
}
