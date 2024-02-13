#ifndef _SYS_TIMER_H
#define _SYS_TIMER_H

#include "fsm_timer.h"
#include "fsm_timer_capi.h"

template <typename DMT>
fsm_timer<DMT>::fsm_timer(DMT *p_regs) 
: am335x_dmtimer<DMT>(p_regs)
{ 
    m_DMTIMER_num = am335x_dmtimer<DMT>::get_DMTIMER_number();
    m_enabled = false;
}

template <typename DMT>
float  fsm_timer<DMT>::get_ms(void)  
{ 
    // (FFFF FFFFh – TLDR + 1) × timer Clock period × Clock Divider (PS)
    // Clock period = 1/ fclk and PS = 2e(PTV + 1).
    // PTV = 0,  PS = 2e(1) =  2
    // timer Clock period = 1/26e6
    // FFFF FFFE = (4294967294 /26000000)*2 =  330 seconds
    // 0.001s = 4294967294*0.001/330 = 13015(0x32D7)

    #define ms_INTERVALi (0x10E8)
    #define ms_INTERVALf (4328.0f)

    if(!m_enabled)
        enable();

    uint32_t tccr = am335x_dmtimer<DMT>::counter_get();
    float ms = (float)(tccr/ms_INTERVALi);
    float us = ((float)(tccr%ms_INTERVALi))/ms_INTERVALf;

    am335x_dmtimer<DMT>::m_time += (ms+us);

    am335x_dmtimer<DMT>::counter_set(0);

    return am335x_dmtimer<DMT>::m_time;
}

template <typename DMT>
void  fsm_timer<DMT>::update()
{  
    am335x_dmtimer<DMT>::counter_set(0);
}

template <typename DMT>
void  fsm_timer<DMT>::reboot()
{  
    am335x_dmtimer<DMT>::m_time = 0;
    am335x_dmtimer<DMT>::counter_set(0);
}

template <typename DMT>
void  fsm_timer<DMT>::enable()
{  
    m_enabled = true;
    am335x_dmtimer<DMT>::enable();
}

template <typename DMT>
void  fsm_timer<DMT>::disable()
{  
    m_enabled = false;
    am335x_dmtimer<DMT>::disable();
}

template <typename DMT>
void fsm_timer<DMT>::init(REGS::DMTIMER::e_DMTIMER_mode  mode)
{          
    REGS::PRCM::run_clk_DMTIMER(m_DMTIMER_num);     
    
    am335x_dmtimer<DMT>::counter_set(0);        
    am335x_dmtimer<DMT>::reload_set(0); 
    am335x_dmtimer<DMT>::mode_configure(mode);

    am335x_dmtimer<DMT>::prescaler_clk_enable(REGS::DMTIMER::CLK_DIV_BY_128);
}

template class fsm_timer<FSMT_t>;

extern fsm_timer<FSMT_t> fsm_time;

/**********************************  sys_timer capi  ********************************/

float fsm_tmr_get_ms(void)
{
    return fsm_time.get_ms();
}

void fsm_tmr_reboot(void)
{
    fsm_time.reboot();
}

#endif //_SYS_TIMER_H