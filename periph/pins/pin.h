#ifndef _PIN_H
#define _PIN_H

#include "am335x_gpio.h"
#include "CONTROL_MODULE.h"
#include "GPIO.h"
#include "am3358zcz_pins.hpp"


namespace PINS
{
    #define CTRLMREG(x)                              \
    (*((REGS::CONTROL_MODULE::conf_module_pin_reg_t *)(REGS::CONTROL_MODULE::AM335x_CONTROL_MODULE_BASE + x)))

    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin
    {
    private:

                       REGS::GPIO::AM335x_GPIO_Type &m_gpio_regs;
        REGS::CONTROL_MODULE::conf_module_pin_reg_t &m_cntrmdl_reg;
                                           uint32_t  m_pinnum;
                                           uint32_t  m_pinbitmsk;
    public:   
                      pin(REGS::GPIO::AM335x_GPIO_Type *gpio_module);
                     ~pin(){ }
            
                /**
                * @brief  This API configures the periph mode of the pin.
                * @param  pinmode     The enum pinmode of the pin 0..7 see datasheet
                *
                **/
                void  sel_pinmode(T pinmode);                
 
                /**
                * @brief  This API enables pullup of the pin.
                * @param  pull_en enables or disables pullup of the pin
                *
                *  'pull_en' can take one of the following values:
                *  - true - enables the pullup.
                *  - false - disable the pullup.
                **/
                void pullup_enable(bool pull_en);    

                /**
                * @brief  This API select pull type of the pin
                * @param  putypesel - type of the pull.
                *
                *  'putypesel' can take one of the following values:
                *  - REGS::GPIO::PULL_DOWN - pin pulled down
                *  - REGS::GPIO::PULL_UP - pin pulled up
                **/ 
                void sel_pull_type(REGS::CONTROL_MODULE::e_PUTYPESEL putypesel);    
 
                /**
                * @brief  This API enables input function of the pin
                * @param  rxactive enables or disables input function of the pin
                *
                *  'rxactive' can take one of the following values:
                *  - REGS::GPIO::INPUT_DISABLE - pin as a input
                *  - REGS::GPIO::INPUT_ENABLE - pin as a output
                **/ 
                void sel_rxactive(REGS::CONTROL_MODULE::e_RXACTIVE rxactive);

                /**
                * @brief  This API select slew rate of the pin
                * @param  slewctrl selsect the slew rate of the pin
                *
                *  'slewctrl' can take one of the following values:
                *  - REGS::GPIO::FAST - fast slew rate
                *  - REGS::GPIO::SLOW - slow slew rate
                **/
                void sel_slewrate(REGS::CONTROL_MODULE::e_SLEWCTRL slewctrl);

                /**
                * @brief  This API configures the direction of a specified GPIO pin as being
                *         either input or output.
                * @param  pindir  The required direction for the GPIO pin
                *
                *   'pindir' can take one of the following values:
                *  - REGS::GPIO::GPIO_INPUT - pindir configure the pin as an input pin\n
                *  - REGS::GPIO::GPIO_OUTPUT - to configure the pin as an output pin\n
                */
                void  dir_set(REGS::GPIO::e_PINDIR pindir);

                /**
                * @brief   This API determines the direction of a specified GPIO pin.
                * 
                * @return  The direction of the specified pin. This returns one of the
                *          following two values:
                *          - REGS::GPIO::GPIO_DIR_INPUT - signifying that the pin is an input pin\n
                *          - REGS::GPIO::GPIO_DIR_OUTPUT - signifying that the pin is an output pin\n
                *
                */
REGS::GPIO::e_PINDIR  dir_get();

                /**
                * @brief  This API drives an output GPIO pin to a logic HIGH state.
                **/
                void  set();

                /**
                * @brief  This API drives an output GPIO pin to a logic LOW state.
                **/
                void  clear();

                /**
                * @brief  This API toggle state an output GPIO pin .
                **/
                void  toggle();

                /**
                 * @brief  This API drives an output GPIO pin to a logic HIGH or a logic LOW
                 *         state.
                 * @param  value    This specifies whether a logic HIGH or a logic LOW
                 *                     should be driven on the output pin
                 *
                 *   'value' can take one of the following values:
                 *  - false - indicating to drive a logic LOW(logic 0) on the pin.
                 *  - true - indicating to drive a logic HIGH(logic 1) on the pin.
                 */
                void  write(bool value);

                /**
                * @brief   This API determines the logic level(value) on a specified
                *          GPIO pin configured as INPUT.
                *
                * @return  The pin value of the specified pin configured as input
                *  - false - indicating a logic LOW(logic 0) on the pin.
                *  - true  - indicating a logic HIGH(logic 1) on the pin.
                */
         inline bool  read_input() const { return (bool)(m_gpio_regs.DATAIN.reg & m_pinbitmsk); } 

                /**
                * @brief   This API determines the logic level(value) on a specified
                *          GPIO pin configured as OUTPUT.
                *
                * @return  The pin value of the specified pin configured as input
                *  - false - indicating a logic LOW(logic 0) on the pin.
                *  - true  - indicating a logic HIGH(logic 1) on the pin.
                */
         inline bool  read_output() const { return (bool)(m_gpio_regs.DATAOUT.reg & m_pinbitmsk); } 

                /**
                 * @brief  This API enables debouncing feature for a specified input
                 *         GPIO pin.Debounce time configured in the corresponding GPIO module
                 *         see debounce_time_config(uint32_t debounce_time).
                 */
                void  debounce_enable();  
                
                /**
                 * @brief  This API disables debouncing feature for a specified input
                 *         GPIO pin. Debounce time configured in the corresponding GPIO module
                 *         see debounce_time_config(uint32_t debounce_time).
                 */
                void  debounce_disable();  

                /**
                 * @brief  This API enables the configured interrupt event on a specified input
                 *         GPIO pin to trigger an interrupt request.
                 * @param  intline     This specifies the interrupt request line on which the
                 *                     interrupt request due to the transitions on a specified
                 *                     pin be propagated
                 *
                 *   'intline' can take one of the following two values:
                 *  - REGS::GPIO::GPIO_INT_LINE_1 - interrupt request be propagated over interrupt line 1\n
                 *  - REGS::GPIO::GPIO_INT_LINE_2 - interrupt request be propagated over interrupt line 2\n
                 */
                void  int_enable(uint32_t intline);

                /**
                 * @brief  This API disables interrupt generation due to the detection
                 *         of any event on a specified input GPIO pin.
                 *
                 *   'intline' can take one of the following two values:
                 *  - REGS::GPIO::GPIO_INT_LINE_1 - signifying that the Interrupt Line 1 be disabled to
                 *    transmit interrupt requests due to transitions on specified pin\n
                 *  - REGS::GPIO::GPIO_INT_LINE_2 - signifying that the Interrupt Line 2 be disabled to
                 *    transmit interrupt requests due to transitions on specified pin\n
                 */
                void  int_disable(uint32_t intline); 

                /**
                 * @brief  This API configures the event type for a specified input GPIO pin.
                 *         Whenever the selected event occurs on that GPIO pin and if interrupt
                 *         generation is enabled for that pin, the GPIO module will send an
                 *         interrupt to CPU.
                 * @param  evnt_type  This specifies the event type on whose detection,
                 *                    the GPIO module will send an interrupt to CPU,
                 *                    provided interrupt generation for that pin is enabled.
                 *
                 *   'evnt_type' can take one of the following values:
                 *  - INT_TYPE_NO_LEVEL - no interrupt request on occurence of either a
                 *    logic LOW or a logic HIGH on the input GPIO pin\n
                 *  - INT_TYPE_LEVEL_LOW - interrupt request on occurence of a LOW level
                 *    (logic 0) on the input GPIO pin\n
                 *  - INT_TYPE_LEVEL_HIGH - interrupt request on occurence of a HIGH level
                 *    (logic 1) on the input GPIO pin\n
                 *  - INT_TYPE_BOTH_LEVEL - interrupt request on the occurence of both the
                 *    LOW level and HIGH level on the input GPIO pin\n
                 *  - INT_TYPE_NO_EDGE -  no interrupt request on either rising or
                 *    falling edges on the pin\n
                 *  - INT_TYPE_RISE_EDGE - interrupt request on occurence of a rising edge
                 *    on the input GPIO pin\n
                 *  - INT_TYPE_FALL_EDGE - interrupt request on occurence of a falling edge
                 *    on the input GPIO pin\n
                 *  - INT_TYPE_BOTH_EDGE - interrupt request on occurence of both a rising
                 *    and a falling edge on the pin\n
                 * 
                 * @note  A typical use case of this API is explained below: 
                 *        If it is initially required that interrupt should be generated on a
                 *        LOW level only, then this API can be called with
                 *        'INT_TYPE_LEVEL_LOW' as the parameter.
                 *        At a later point of time, if logic HIGH level only should be made as
                 *        the interrupt generating event, then this API has to be first called
                 *        with 'INT_TYPE_NO_LEVEL' as the parameter and later with
                 *        'INT_TYPE_LEVEL_HIGH' as the parameter. Doing this ensures that
                 *        logic LOW level trigger for interrupts is disabled.
                 */
                void  int_type_set(REGS::GPIO::e_INT_TYPE evnt_type); 

                /**
                 * @brief  This API determines the programmed interrupt event type for a
                 *         specified input GPIO pin.
                 * @param  pinnum  The number of the pin in the GPIO instance
                 *              
                 * @return This returns one or a combination of the following values:
                 * - INT_TYPE_NO_LEVEL - level trigger for interrupt request is disabled\n
                 * - INT_TYPE_LEVEL_LOW - logic LOW level event for interrupt request is
                 *   enabled\n
                 * - INT_TYPE_LEVEL_HIGH - logic HIGH level event for interrupt request is
                 *   enabled\n
                 * - INT_TYPE_BOTH_LEVEL - both logic LOW and logic HIGH level events
                 *   for interrupt request are enabled\n
                 * - INT_TYPE_NO_EDGE - edge trigger for interrupt request is disabled\n
                 * - INT_TYPE_RISE_EDGE - rising edge event for interrupt request is
                 *   enabled\n
                 * - INT_TYPE_FALL_EDGE - falling edge event for interrupt request
                 *   is enabled\n
                 * - INT_TYPE_BOTH_EDGE - both rising and falling edge events for
                 *   interrupt request are enabled\n
                 */
            uint32_t  int_type_get();

                /**
                 * @brief  This API determines the enabled interrupt status of a specified pin.
                 * @param  intline    This specifies the interrupt line whose corresponding
                 *                    enabled interrupt status register has to be accessed.
                 *                    The status of the specified pin is returned in this API.
                 * 
                 *  'intline' can take one of the following two values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to read the enabled interrupt status register
                 *   corresponding to interrupt line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to read the enabled interrupt status register
                 *   corresponding to interrupt line 2\n
                 *
                 * @return The enabled interrupt status of the pin on the specified interrupt
                 *         line. This could either be a non-zero or a zero value.
                 */
                bool  int_status(uint32_t intline);

                /**
                 * @brief  This API determines the raw interrupt status of the specified GPIO
                 *         pins in the instance corresponding to the specified interrupt line.
                 * @param  intline    This specifies the interrupt line whose corresponding
                 *                    raw interrupt status register has to be read.
                 * 
                 *  'intline' can take one of the following two values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to read the raw interrupt status register corresponding
                 *   to interrupt line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to read the raw interrupt status register corresponding
                 *   to interrupt line 2\n
                 *
                 * @return  The raw interrupt status of the specified pins of the GPIO instance
                 *          corresponding to a specified interrupt line.
                 */
                bool  raw_int_status(uint32_t intline); 

                /**
                 * @brief  This API clears the enabled interrupt status of a specified GPIO
                 *         pin.
                 * @param  intline    This specifies the interrupt line whose corresponding
                 *                    enabled interrupt status register has to be accessed.
                 *                    The status of the specified bit in it is cleared in this
                 *                    API.
                 *
                 *  'intline' can take one of the following two values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to access the enabled interrupt status register
                 *   corresponding to interrupt line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to access the enabled interrupt status register
                 *   corresponding to interrupt line 2\n * 
                */
                void  int_clear(uint32_t intline);

                /**
                 * @brief  This API manually triggers an interrupt request due to a specified 
                 *         GPIO pin. 
                 * @param  intline    This specifies the interrupt line over which the
                 *                    manually triggered interrupt request has to be
                 *                    propogated
                 *
                 *  'intline' can take one of the following values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to propogate the interrupt request over interrupt
                 *   line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to propogate the interrupt request over interrupt
                 *   line 2\n
                 *
                 * @note  Here an interrupt request is manually triggered by writing to a
                 *        specified bit in the Raw Interrupt Status register. As a
                 *        pre-requisite, the interrupt generation should be enabled for the 
                 *        GPIO pin.
                 */
                void  trigger_int(uint32_t intline);

                /**
                 * @brief  This API enables the feature for the specified Input GPIO Pin
                 *         (Interrupt Request Source) to generate an asynchronous wakeup
                 *         signal to the CPU.
                 * @param  intline This specifies the Smart Wakeup Interrupt Line over
                 *         which the asynchrounous wakeup signal has to be
                 *         propogated due to the specified Input GPIO pin.
                 *
                 *  'intline' can take one of the following values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to propogate the wakeup request over Smart
                 *   Wakeup Interrupt Line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to propagate the wakeup request over Smart
                 *   Wakeup Interrupt Line 2\n
                 * @note  1> Make sure that the GPIO instance in context is allowed to generate
                 *           Wakeup interrupts to the CPU. If allowed, then enable Wakeup
                 *           interrupt generation feature for that GPIO instance in the Interrupt
                 *           Controller.\n
                 *        2> Usually an Input GPIO Pin acts as an Interrupt Request(IRQ) Source.
                 *           An expected transition on an Input GPIO Pin can generate a Wakeup
                 *           request.\n
                */
                void  int_wakeup_enable(uint32_t intline);

                /**
                 * @brief  This API disables the feature for the specified Input GPIO Pin
                 *         (Interrupt Request Source) to generate an asynchronous wakeup
                 *         signal to the CPU.
                 * @param  intline This specifies the Smart Wakeup Interupt Line which has
                 *                     to be disabled to propogate any asynchrounous wakeup
                 *                     signal due to the specified input GPIO Pin.
                 *
                 *  'intline' can take one of the following values:
                 * - REGS::GPIO::GPIO_INT_LINE_1 - to propogate the wakeup request over Smart
                 *   Wakeup Interrupt Line 1\n
                 * - REGS::GPIO::GPIO_INT_LINE_2 - to propagate the wakeup request over Smart
                 *   Wakeup Interrupt Line 2\n
                 */
                void  int_wakeup_disable(uint32_t intline); 
    };    

}  // namespace PINS

#endif // _PIN_H