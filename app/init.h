#ifndef __INIT_H
#define __INIT_H

#include "soc_AM335x.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "am335x_intc.h"
#include "gpio_v2.h"

#define GPIO_INSTANCE_ADDRESS           (SOC_GPIO_1_REGS)
#define GPIO_INSTANCE_PIN_NUMBER        (23)

void init_board(void);

#endif  //__INIT_H

