#include "utils.h"

static unsigned long int _next = 1;

// RAND_MAX assumed to be 32767
int random(void) 
{
    _next = _next * 1103515245 + 12345;
    return (unsigned int)(_next/65536) % 32768;
}

int rnd_max(int max)
{
    return (int)(((float)(max*random())) / 32767.0f);
}

uint16_t crc16_fill(const uint8_t *p_Buf, uint32_t len, uint16_t fill)
{
    register uint8_t Lo, Hi, uc_Sym;
 
    if (!len){
        return 1;
    }
   
    Lo = fill & 0xFF;
    Hi = (fill & 0xFF00) >> 8;
 
    do 
    {
        uc_Sym = *(p_Buf++);
        uc_Sym ^= Hi;
          
        Hi = ( uc_Sym & 0x02 ) ? (Lo - 0x80) : Lo;
          
        if ( uc_Sym & 0x01 )
            Hi ^= 0xC0;
          
        Lo = uc_Sym;
        Lo >>= 1;
        Lo ^= uc_Sym;
        Lo >>= 1;
        uc_Sym ^= Lo;
          
        if ( uc_Sym & 0x08 )
            --uc_Sym;
          
        if ( uc_Sym & 0x40 )
            --uc_Sym;
          
        uc_Sym &= 0x01;
  
        if (uc_Sym)
            Lo ^= 0xC0;
  
        Hi ^= uc_Sym;
    } while (--len);
  
    return (uint16_t)((((uint16_t)Hi)<<8) | Lo);
}

uint16_t crc16(const uint8_t *p_Buf, uint32_t len)
{
    return crc16_fill(p_Buf, len, 0xFFFF);
}

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

void  ienable() {}
void  idisable() {}
