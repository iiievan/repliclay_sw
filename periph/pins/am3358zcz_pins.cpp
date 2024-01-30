#ifndef _AM3358ZCZ_PINS_H
#define _AM3358ZCZ_PINS_H

#include "GPIO.h"
#include "am3358zcz_pins.hpp"
#include "pin.h"

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



} // namespace PINS

#endif // _AM3358ZCZ_PINS_H