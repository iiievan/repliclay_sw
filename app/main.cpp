#include <stdint.h>
#include "board.h"
#include "init.h"
#include "sys_timer.h"
#include "pin.h"
#include "am3358zcz_pins.hpp"

int main()
{  
    static uint64_t time = 0;
    
    init_board();    

    while(1)
    {      
        if(sys_time.get_ms() - time > 1000)
        {
            time = sys_time.get_ms();
            
            USR_LED_3.toggle();
            
            if(END_STOP_X_2.read_input())
                USR_LED_0.set();
            else
                USR_LED_0.clear();
        }
    }
} 

/******************************* End of file *********************************/
