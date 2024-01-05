#ifndef __BOARD_H
#define __BOARD_H

#include "am3358zcz_pins.hpp"
#include "pin.h"

/********************************************************************************************************************/  

/********************************************** beaglebone black board pins ***********************************************/ 
    
/********************************************************************************************************************/

#define USR_LED_0        (PINS::gpmc_a5)    // gpio1_21
#define USR_LED_1        (PINS::gpmc_a6)    // gpio1_22
#define USR_LED_2        (PINS::gpmc_a7)    // gpio1_23
#define USR_LED_3        (PINS::gpmc_a8)    // gpio1_24

#define APP_LED USR_LED_3
//#define APP_PIN (PINS::e_GPMC_A5::gpio1_21)
//#define APP_PIN (PINS::e_GPMC_A6::gpio1_22)
//#define APP_PIN (PINS::e_GPMC_A7::gpio1_23)
#define APP_PIN (PINS::e_GPMC_A8::gpio1_24)


/********************************************************************************************************************/  

/********************************************** repliclay board pins ***********************************************/ 
    
/********************************************************************************************************************/

#define  END_STOP_X_2    (PINS::gpmc_wait0)          // gpio0_30
#define  PCA9685PW_EN    (PINS::xdma_event_intr1)    // gpio0_20
#define  PCA9685PW_SDA   (PINS::uart1_ctsn)          // gpio0_12
#define  PCA9685PW_SCL   (PINS::uart1_rtsn)          // gpio0_13

#endif  //__BOARD_H

