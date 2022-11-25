#ifndef _APP_UTILS_H
#define _APP_UTILS_H

#include <stdint.h>

#define countof(x)              (sizeof(x) / sizeof(*(x)))
#define BIT(x)                  (1u << (x))
#define HIGH                    (1u)
#define LOW                     (0u)

#define     __R     volatile const       // 'read only' register
#define     __W     volatile             // 'write only' register 
#define     __RW    volatile             // 'read / write' register

#define DLY_100US               (10160)  //11830
#define DLY_10US                (1139) 
#define DLY_1US                 (89)   

extern void delay_100us(uint32_t delay);
extern void delay_10us(uint32_t delay);

#endif //_APP_UTILS_H