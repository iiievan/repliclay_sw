#ifndef __SW_TIMER_H
#define __SW_TIMER_H

class OS_Timer;
#include "OS_Timer.h"

typedef void (*tmrCallback)(void * p_Obj);

class sw_Timer
{
public:
              sw_Timer(uint64_t preset, OS_Timer& s_Source, tmrCallback clb);
        void  set_period(uint64_t period)     { m_Preset   = period; }
        void  set_callback(tmrCallback clb)   { m_Callback = clb; }
        bool  is_working() const              { return m_CountPprogress; }
    sw_Timer& start();         // run countdown
        void  stop()                          { m_CountPprogress = false; }
    sw_Timer& update();
    
        bool  on_delay(void * p_Obj = nullptr);      // run tmrCallback once at the end of countdown
        bool  off_delay(void * p_Obj = nullptr);     // run tmrCallback for all countdown time

private:  
  
    uint64_t  m_Timer = 0;
    uint64_t  m_Preset;      // in  milliseconds
        bool  m_CountPprogress { false };
 tmrCallback  m_Callback;
    OS_Timer& m_timeSource;
};

extern sw_Timer intrprtr_backup_timer;
extern sw_Timer bt_cfg_backup_timer;
extern void timer_intrprtr_backup_callback(void * p_Obj);
extern void timer_bt_cfg_backup_callback(void * p_Obj);
extern sw_Timer radio_off_timer;
extern void radio_off_callback(void * p_Obj);

#endif //__SW_TIMER_H