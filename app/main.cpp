#include <stdint.h>
#include "init.h"
#include "sys_timer.h"
#include "pin.h"

int main()
{  
    static uint64_t time = 0;
    
    init_board();    

    while(1)
    {      
        if(sys_time.get_ms() - time > 1000)
        {
            time = sys_time.get_ms();
            
            APP_LED.toggle();
        }
    }
} 

/******************************* End of file *********************************/
