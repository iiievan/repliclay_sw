#ifndef __SW_TIMER_H
#define __SW_TIMER_H

class system_timer;
#include "system_timer.h"

typedef void (*tmrCallback)(void * p_Obj);

class swTimer
{
public:
              swTimer(uint64_t preset, system_timer& s_Source, tmrCallback clb);
        void  set_period(uint64_t period)     { m_Preset   = period; }
        void  set_callback(tmrCallback clb)   { m_Callback = clb; }
        bool  is_working() const              { return m_CountPprogress; }
     swTimer& start();         // run countdown
        void  stop()                          { m_CountPprogress = false; }
     swTimer& update();
    
        bool  on_delay(void * p_Obj = nullptr);      // run tmrCallback once at the end of countdown
        bool  off_delay(void * p_Obj = nullptr);     // run tmrCallback for all countdown time

private:
     
        
    uint64_t  m_Timer = 0;
    uint64_t  m_Preset;      // in  milliseconds
        bool  m_CountPprogress { false };
 tmrCallback  m_Callback;
system_timer& m_timeSource;
};

extern swTimer intrprtr_backup_timer;
extern swTimer bt_cfg_backup_timer;
extern void timer_intrprtr_backup_callback(void * p_Obj);
extern void timer_bt_cfg_backup_callback(void * p_Obj);
extern swTimer radio_off_timer;
extern void radio_off_callback(void * p_Obj);

#endif //__SW_TIMER_H