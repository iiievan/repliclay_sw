#include "app_utils.h"

#pragma optimize=none
void delay_100us(uint32_t delay)
{
    for(; delay; delay--)
    {
        for(volatile uint32_t j = DLY_100US; j; j--)//7 operations per cycle
        {
        }
    }
}

#pragma optimize=none
void delay_10us(uint32_t delay)
{
    for(; delay; delay--)
    {
        for(volatile uint32_t j = DLY_10US; j; j--)//7 operations per cycle
        {
        }
    }
}