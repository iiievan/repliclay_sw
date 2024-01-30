#ifndef __BOARD_H
#define __BOARD_H

#include "am3358zcz_pins.hpp"
#include "pin.h"

/********************************************************************************************************************/  

/********************************************** beaglebone black board pins ***********************************************/ 
    
/********************************************************************************************************************/

#define USR_LED_0        (PINS::gpmc_a5)    // PINS::e_GPMC_A5::gpio1_21
#define USR_LED_1        (PINS::gpmc_a6)    // PINS::e_GPMC_A6::gpio1_22
#define USR_LED_2        (PINS::gpmc_a7)    // PINS::e_GPMC_A7::gpio1_23
#define USR_LED_3        (PINS::gpmc_a8)    // PINS::e_GPMC_A8::gpio1_24

#define DBG_PIN1         (PINS::lcd_data1)  // PINS::e_LCD_DATA1::gpio2_7
#define DBG_PIN2         (PINS::lcd_data3)  // PINS::e_LCD_DATA3::gpio2_9
#define DBG_PIN3         (PINS::lcd_data5)  // PINS::e_LCD_DATA5::gpio2_11
#define DBG_PIN4         (PINS::lcd_data7)  // PINS::e_LCD_DATA7::gpio2_13

#define UART0_TX         (PINS::uart0_txd)  // PINS::e_UART0_TXD::gpio1_11
#define UART0_RX         (PINS::uart0_rxd)  // PINS::e_UART0_RXD::gpio1_10

/********************************************************************************************************************/  

/********************************************** repliclay board pins ***********************************************/ 
    
/********************************************************************************************************************/

#define  END_STOP_X_2    (PINS::gpmc_wait0)          // gpio0_30
#define  PCA9685PW_EN    (PINS::xdma_event_intr1)    // gpio0_20
#define  PCA9685PW_SDA   (PINS::uart1_ctsn)          // gpio0_12
#define  PCA9685PW_SCL   (PINS::uart1_rtsn)          // gpio0_13

#endif  //__BOARD_H

