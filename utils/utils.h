#ifndef _UTILS_H
#define _UTILS_H

#ifdef __cplusplus
    #define UNUSED(x)  (x = x)
#else
    #define UNUSED(x)  ((void)(x))
#endif  //__cplusplus

#ifdef _cplusplus
extern "C" {
#endif
  
#include <stdint.h>
 
#define MY_RAND_MAX        (32767)
#define MY_RAND_MIN        (-32768)
  
#define M_PI 			   (3.141592653589f)

#if defined(NRF52)
    #define ISRENABLE  __enable_interrupt()
    #define ISRDISABLE __disable_interrupt()
#else
extern void  ienable();
extern void  idisable();
    #define ISRENABLE  ienable()
    #define ISRDISABLE idisable()
#endif
  
#define ASSERT(expr)                                                          \
if (expr)                                                                     \
{                                                                             \
}                                                                             \
else                                                                          \
{                                                                             \
    while (1);                                                                \
}

#define countof(a)              (sizeof(a) / sizeof(*(a)))
#define BIT(x)                  (1u << (x))
#define HIGH                    (1u)
#define LOW                     (0u)

#define     __R     volatile const       // 'read only' register
#define     __W     volatile             // 'write only' register 
#define     __RW    volatile             // 'read / write' register

#define DLY_100US    (10160)  //11830
#define DLY_10US     (1139) 
#define DLY_1US      (89)   

#define ever (;;)

extern     void  delay_100us(uint32_t delay);
extern     void  delay_10us(uint32_t delay);     
extern      int  random(void); // RAND_MAX assumed to be 32767
extern      int  rnd_max(int max);
extern     void  seed_random(unsigned int seed);
extern uint16_t  crc16_fill(const uint8_t *p_Buf, uint32_t len, uint16_t fill);
extern uint16_t  crc16(const uint8_t *p_Buf, uint32_t len);

#ifdef _cplusplus
}
#endif

#endif // _UTILS_H