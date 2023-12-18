#include "init.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static void Delay(unsigned int count);

#ifdef __cplusplus
}
#endif


int main()
{  
    init_board();

    while(1)
    {
        // Driving a logic HIGH on the GPIO pin.
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                     GPIO_INSTANCE_PIN_NUMBER,
                     GPIO_PIN_HIGH);

       Delay(0x1FFFFFF);

        // Driving a logic LOW on the GPIO pin
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                     GPIO_INSTANCE_PIN_NUMBER,
                     GPIO_PIN_LOW);

        Delay(0x1FFFFFF);
    }

} 

/*
** A function which is used to generate a delay.
*/
#ifdef __cplusplus
extern "C" {
#endif
static void Delay(volatile unsigned int count)
{
    while(count--);
}
#ifdef __cplusplus
}
#endif


/******************************* End of file *********************************/
