#ifndef __INIT_H
#define __INIT_H

#include "soc_AM335x.h"
#include "beaglebone.h"
#include "gpio_v2.h"

#define GPIO_INSTANCE_ADDRESS           (SOC_GPIO_1_REGS)
#define USR_LED_0        (21)
#define USR_LED_1        (22)
#define USR_LED_2        (23)
#define USR_LED_3        (24)

#define APP_LED USR_LED_3

void init_board(void);
void dmtimer_setup(void);

#endif  //__INIT_H

