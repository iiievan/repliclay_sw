#ifndef _AM3358ZCZ_PINS_H
#define _AM3358ZCZ_PINS_H

#include "GPIO.h"
#include "am3358zcz_pins.hpp"
#include "pin.h"
#include "am3358zcz_pins_capi.h"

namespace PINS
{
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin;
    
    enum class e_GPMC_A5    : uint8_t;
    enum class e_GPMC_A6    : uint8_t;
    enum class e_GPMC_A7    : uint8_t;
    enum class e_GPMC_A8    : uint8_t;
    enum class e_GPMC_WAIT0 : uint8_t;
    enum class e_UART1_RTSn : uint8_t;
    enum class e_UART1_CTSn : uint8_t;
    enum class e_UART0_TXD  : uint8_t;
    enum class e_UART0_RXD  : uint8_t;
    enum class e_XDMA_EVENT_INTR1 : uint8_t;
    enum class e_LCD_DATA1 : uint8_t;
    enum class e_LCD_DATA3 : uint8_t;
    enum class e_LCD_DATA5  : uint8_t;
    enum class e_LCD_DATA7  : uint8_t;

    
             pin<e_GPMC_A5, 21U, 0x854>  gpmc_a5(REGS::GPIO::AM335x_GPIO_1);
             pin<e_GPMC_A6, 22U, 0x858>  gpmc_a6(REGS::GPIO::AM335x_GPIO_1);
             pin<e_GPMC_A7, 23U, 0x85C>  gpmc_a7(REGS::GPIO::AM335x_GPIO_1);
             pin<e_GPMC_A8, 24U, 0x860>  gpmc_a8(REGS::GPIO::AM335x_GPIO_1);

          pin<e_GPMC_WAIT0, 30U, 0x870>  gpmc_wait0(REGS::GPIO::AM335x_GPIO_0);
          pin<e_UART1_RTSn, 13U, 0x97C>  uart1_rtsn(REGS::GPIO::AM335x_GPIO_0);
          pin<e_UART1_CTSn, 12U, 0x978>  uart1_ctsn(REGS::GPIO::AM335x_GPIO_0);
           pin<e_UART0_TXD, 11U, 0x974>  uart0_txd(REGS::GPIO::AM335x_GPIO_1);
           pin<e_UART0_RXD, 10U, 0x970>  uart0_rxd(REGS::GPIO::AM335x_GPIO_1);
    pin<e_XDMA_EVENT_INTR1, 20U, 0x9B4>  xdma_event_intr1(REGS::GPIO::AM335x_GPIO_0);

            pin<e_LCD_DATA1, 7U, 0x8A4>  lcd_data1(REGS::GPIO::AM335x_GPIO_2);
            pin<e_LCD_DATA3, 9U, 0x8AC>  lcd_data3(REGS::GPIO::AM335x_GPIO_2);
           pin<e_LCD_DATA5, 11U, 0x8B4>  lcd_data5(REGS::GPIO::AM335x_GPIO_2);
           pin<e_LCD_DATA7, 13U, 0x8BC>  lcd_data7(REGS::GPIO::AM335x_GPIO_2);

} // namespace PINS

/**********************************  pins using capi  ********************************/

void pin_set(e_AM3358_pins pin)
{
    switch(pin)
    {
        case GPMC_A5_pin:
            PINS::gpmc_a5.set();
            break;
        case GPMC_A6_pin:
            PINS::gpmc_a6.set();
            break;
        case GPMC_A7_pin:
            PINS::gpmc_a7.set();
            break;
        case GPMC_A8_pin:
            PINS::gpmc_a8.set();
            break;
        case GPMC_WAIT0_pin:
            PINS::gpmc_wait0.set();
            break;
        case UART1_RTSn_pin:
            PINS::uart1_rtsn.set();
            break;
        case UART1_CTSn_pin:
            PINS::uart1_ctsn.set();
            break;
        case UART0_TXD_pin:
            PINS::uart0_txd.set();
            break;
        case UART0_RXD_pin:
            PINS::uart0_rxd.set();
            break;
        case XDMA_EVENT_INTR1_pin:
            PINS::xdma_event_intr1.set();
            break;
        case LCD_DATA1_pin:
            PINS::lcd_data1.set();
            break;
        case LCD_DATA3_pin:
            PINS::lcd_data3.set();
            break;
        case LCD_DATA5_pin:
            PINS::lcd_data5.set();
            break;
        case LCD_DATA7_pin:
            PINS::lcd_data7.set();
            break;
        default:
            break;
    }
}

void pin_toggle(e_AM3358_pins pin)
{
    switch(pin)
    {
        case GPMC_A5_pin:
            PINS::gpmc_a5.toggle();
            break;
        case GPMC_A6_pin:
            PINS::gpmc_a6.toggle();
            break;
        case GPMC_A7_pin:
            PINS::gpmc_a7.toggle();
            break;
        case GPMC_A8_pin:
            PINS::gpmc_a8.toggle();
            break;
        case GPMC_WAIT0_pin:
            PINS::gpmc_wait0.toggle();
            break;
        case UART1_RTSn_pin:
            PINS::uart1_rtsn.toggle();
            break;
        case UART1_CTSn_pin:
            PINS::uart1_ctsn.toggle();
            break;
        case UART0_TXD_pin:
            PINS::uart0_txd.toggle();
            break;
        case UART0_RXD_pin:
            PINS::uart0_rxd.toggle();
            break;
        case XDMA_EVENT_INTR1_pin:
            PINS::xdma_event_intr1.toggle();
            break;
        case LCD_DATA1_pin:
            PINS::lcd_data1.toggle();
            break;
        case LCD_DATA3_pin:
            PINS::lcd_data3.toggle();
            break;
        case LCD_DATA5_pin:
            PINS::lcd_data5.toggle();
            break;
        case LCD_DATA7_pin:
            PINS::lcd_data7.toggle();
            break;
        default:
            break;
    }
}

void pin_clear(e_AM3358_pins pin)
{
    switch(pin)
    {
        case GPMC_A5_pin:
            PINS::gpmc_a5.clear();
            break;
        case GPMC_A6_pin:
            PINS::gpmc_a6.clear();
            break;
        case GPMC_A7_pin:
            PINS::gpmc_a7.clear();
            break;
        case GPMC_A8_pin:
            PINS::gpmc_a8.clear();
            break;
        case GPMC_WAIT0_pin:
            PINS::gpmc_wait0.clear();
            break;
        case UART1_RTSn_pin:
            PINS::uart1_rtsn.clear();
            break;
        case UART1_CTSn_pin:
            PINS::uart1_ctsn.clear();
            break;
        case UART0_TXD_pin:
            PINS::uart0_txd.clear();
            break;
        case UART0_RXD_pin:
            PINS::uart0_rxd.clear();
            break;
        case XDMA_EVENT_INTR1_pin:
            PINS::xdma_event_intr1.clear();
            break;
        case LCD_DATA1_pin:
            PINS::lcd_data1.clear();
            break;
        case LCD_DATA3_pin:
            PINS::lcd_data3.clear();
            break;
        case LCD_DATA5_pin:
            PINS::lcd_data5.clear();
            break;
        case LCD_DATA7_pin:
            PINS::lcd_data7.clear();
            break;
        default:
            break;
    }
}

#endif // _AM3358ZCZ_PINS_H