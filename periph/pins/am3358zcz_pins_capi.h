#ifndef __AM2258ZCZ_PINS_CAPI_H
#define __AM2258ZCZ_PINS_CAPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
   GPMC_A5_pin = 0, 
   GPMC_A6_pin,
   GPMC_A7_pin,
   GPMC_A8_pin,
   GPMC_WAIT0_pin,
   UART1_RTSn_pin,
   UART1_CTSn_pin,
   UART0_TXD_pin,
   UART0_RXD_pin,
   XDMA_EVENT_INTR1_pin,
   LCD_DATA1_pin,
   LCD_DATA3_pin,
   LCD_DATA5_pin,
   LCD_DATA7_pin 
} e_AM3358_pins;

typedef enum 
{
   USR_LED_0_pin = 0, 
   USR_LED_1_pin = 1,
   USR_LED_2_pin = 2,
   USR_LED_3_pin = 3,
   DBG_PIN1_pin  = 10,  // LCD_DATA1_pin
   DBG_PIN2_pin  = 11,  // LCD_DATA3_pin
   DBG_PIN3_pin  = 12,  // LCD_DATA5_pin
   DBG_PIN4_pin  = 13   // LCD_DATA7_pin
} e_bbb_outputs;

void pin_set(e_AM3358_pins pin);

void pin_toggle(e_AM3358_pins pin);

void pin_clear(e_AM3358_pins pin);

#ifdef __cplusplus
}
#endif

#endif //__AM2258ZCZ_PINS_CAPI_H