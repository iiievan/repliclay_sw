#include <stdint.h>
#include "board.hpp"
#include "init.h"
#include "sys_timer.h"
#include "pin.h"
#include "am3358zcz_pins.hpp"
#include "fsm_types_capi.h"
#include "fsm_timer.h"
#include "utils.h"
#include "ring_buffer.h"

int main()
{  
    //static float time = 0;
       
    init_board(); 
    
    init_fsm(); 

    for ever
    {   
      /*
        if(sys_time.get_ms() - time > 1000.0f)
        {
            time = sys_time.get_ms();
            
            USR_LED_3.toggle();
            
            if(END_STOP_X_2.read_input())
                USR_LED_0.set();
            else
                USR_LED_0.clear();
        }
        */
      
        fsm_sheduler_dispatch();
    }
} 

/******************************* End of file *********************************/
