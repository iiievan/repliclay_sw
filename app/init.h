#ifndef __INIT_H
#define __INIT_H

#include "soc_AM335x.h"
#include "beaglebone.h"
#include "gpio_v2.h"
#include "pin.h"

#define USR_LED_0        (PINS::gpmc_a5)    // gpio1_21
#define USR_LED_1        (PINS::gpmc_a6)    // gpio1_22
#define USR_LED_2        (PINS::gpmc_a7)    // gpio1_23
#define USR_LED_3        (PINS::gpmc_a8)    // gpio1_24

#define APP_LED USR_LED_3
//#define APP_PIN (PINS::e_GPMC_A5::gpio1_21)
//#define APP_PIN (PINS::e_GPMC_A6::gpio1_22)
//#define APP_PIN (PINS::e_GPMC_A7::gpio1_23)
#define APP_PIN (PINS::e_GPMC_A8::gpio1_24)



void init_board(void);
void dmtimer_setup(void);

#endif  //__INIT_H

