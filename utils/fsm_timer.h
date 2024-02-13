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
    fsm_timer(DMT *p_regs);

    float  get_ms(void); 
    
    /* reset counter to 0*/
    void  update();

    /* reset counter to 0 and time from start*/
    void  reboot();

    /* enable timer to start count*/
    void  enable();

    /* enable timer to start count*/
    void  disable();

    /*
     * Setup the timer for one-shot and compare mode.
     */
    void init(REGS::DMTIMER::e_DMTIMER_mode  mode = REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE);

private:  
       REGS::DMTIMER::e_TIMER_NUM  m_DMTIMER_num;
                             bool  m_enabled;
};

#endif //__OS_TIMER_H