#include "UART_DT_driver.h"

// @brief This Callback is called when charater is receive
char UART_read(void *p_Obj)
{    
    AM335x_UART &s_UART = *((AM335x_UART *)p_Obj);
    char result = s_UART.char_get();
    return result;
}

// @brief This Callback is called to write buffer to UART
int UART_write(void *p_Obj, const char *buffer, size_t len)
{
    AM335x_UART &s_UART = *((AM335x_UART *)p_Obj);
    int index = -1 ;    

    // Send the characters
    for(index = 0; index < len; index++)
    {
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        if(buffer[index] == '\n')
            s_UART.char_put('\r');
        
        s_UART.char_put(buffer[index]); // Send the character to the UART output
    }

    // Return the number of characters written. */
    return (index);
}

int  UART_DT_Driver::probe(void* dev)
{
}
 
int  UART_DT_Driver::init(void)
{
}
 
void  UART_DT_Driver::sync_state(void* dev)
{
}
 
int  UART_DT_Driver::remove(void* dev)
{
}
 
void  UART_DT_Driver::shutdown(void* dev)
{
}
 
int  UART_DT_Driver::suspend(void* dev)
{
}
 
int  UART_DT_Driver::resume(void* dev)
{
}

int  UART_DT_Driver::exit(void)
{
}

UART_DT_Driver uart_console(uart_0);
