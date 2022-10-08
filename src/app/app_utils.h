#ifndef _APP_UTILS_H
#define _APP_UTILS_H

#define countof(x)              (sizeof(x) / sizeof(*(x)))
#define BIT(x)                  (1u << (x))
#define HIGH                    (1u)
#define LOW                     (0u)

#define     __R     volatile const       // 'read only' register
#define     __W     volatile             // 'write only' register 
#define     __RW    volatile             // 'read / write' register

#endif //_APP_UTILS_H