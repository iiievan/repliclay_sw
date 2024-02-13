#ifndef __SYSTIMER_CAPI_H
#define __SYSTIMER_CAPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

float fsm_tmr_get_ms(void);

 void fsm_tmr_reboot(void);

#ifdef __cplusplus
}
#endif

#endif //__SYSTIMER_CAPI_H