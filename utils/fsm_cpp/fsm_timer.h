#ifndef __FSM_TIMER_H
#define __FSM_TIMER_H

#include "PRCM.h"
#include "am335x_dmtimer.h"

// for DMTIMER 0,2,3,4,5,6,7
#define FSMT_t         REGS::DMTIMER::AM335x_DMTIMER_Type
#define FSMT_TIMER_ptr REGS::DMTIMER::AM335X_DMTIMER_2

template <typename DMT> 
class fsm_timer : public am335x_dmtimer<DMT>
{
public:
    fsm_timer(DMT *p_regs) 
    : am335x_dmtimer<DMT>(p_regs)
    { 
        m_DMTIMER_num = am335x_dmtimer<DMT>::get_DMTIMER_number();
        m_enabled = false;
    }

    float  get_ms(void)  
    { 
        // (FFFF FFFFh – TLDR + 1) × timer Clock period × Clock Divider (PS)
        // Clock period = 1/ fclk and PS = 2e(PTV + 1).
        // PTV = 0,  PS = 2e(1) =  2
        // timer Clock period = 1/26e6
        // FFFF FFFE = (4294967294 /26000000)*2 =  330 seconds
        // 0.001s = 4294967294*0.001/330 = 13015(0x32D7)

        #define ms_INTERVALi (0x2EE0)
        #define ms_INTERVALf (12000.0f)

        if(!m_enabled)
            enable();

        uint32_t tccr = am335x_dmtimer<DMT>::counter_get();
        float ms = (float)(tccr/ms_INTERVALi);
        float us = ((float)(tccr%ms_INTERVALi))/ms_INTERVALf;

        am335x_dmtimer<DMT>::m_time += (ms+us);

        am335x_dmtimer<DMT>::counter_set(0);

        return am335x_dmtimer<DMT>::m_time; 
    }
    
    /* reset counter to 0*/
    inline void  update()
    {  
        am335x_dmtimer<DMT>::counter_set(0);
    }

    /* reset counter to 0 and time from start*/
    inline void  reboot()
    {  
        am335x_dmtimer<DMT>::m_time = 0;
        am335x_dmtimer<DMT>::counter_set(0);
    }

    /* enable timer to start count*/
    inline void  enable()
    {  
        m_enabled = true;
        am335x_dmtimer<DMT>::enable();
    }

    /* enable timer to start count*/
    inline void  disable()
    {  
        m_enabled = false;
        am335x_dmtimer<DMT>::disable();
    }

    /*
     * Setup the timer for one-shot and compare mode.
     */
    void init(REGS::DMTIMER::e_DMTIMER_mode  mode = REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE)
    {          
        REGS::PRCM::run_clk_DMTIMER(m_DMTIMER_num);     
        
        am335x_dmtimer<DMT>::counter_set(0);        
        am335x_dmtimer<DMT>::reload_set(0); 
        am335x_dmtimer<DMT>::mode_configure(mode);

        am335x_dmtimer<DMT>::prescaler_clk_enable(REGS::DMTIMER::CLK_DIV_BY_128);
    }

private:  
       REGS::DMTIMER::e_TIMER_NUM  m_DMTIMER_num;
                             bool  m_enabled;
};

extern fsm_timer<FSMT_t> fsm_time;


#endif //__OS_TIMER_H