#include <stdint.h>
#include "init.h"
#include "sys_timer.h"

int main()
{  
    static uint64_t time = 0;
    static bool pin_state = true;
    
    init_board();

    while(1)
    {      
        if(sys_time.get_ms() - time > 1000)
        {
            time = sys_time.get_ms();
            
            // toggle GPIO pin.
            GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                     GPIO_INSTANCE_PIN_NUMBER,
                     (unsigned int)pin_state);
            
            pin_state = !pin_state;
        }
    }
} 

/******************************* End of file *********************************/
