#ifndef _AM335x_GPIO_H
#define _AM335x_GPIO_H

#include <stdint.h>
#include "GPIO.h"
#include "PRCM.h"
#include "INTC.h"

class am335x_gpio
{
public:
               typedef struct
                {
                    uint32_t ctrl;
                    uint32_t dir;
                    uint32_t data;
                } gpio_context_t;
public:

    am335x_gpio(REGS::GPIO::AM335x_GPIO_Type *p_gpio_regs);
    ~am335x_gpio() {}

    /**
     * @brief  This API performs the module reset of the GPIO module. It also
     *         waits until the reset process is complete.
     */
    void  module_reset();

    /**
     * @brief  This API is used to enable the GPIO module. When the GPIO module
     *         is enabled, the clocks to the module are not gated.
     * @note   Enabling the GPIO module is a primary step before any other
     *         configurations can be done.
     */
    void  module_enable();

    /**
     * @brief  This API is used to disable the GPIO module. When the GPIO module
     *         is disabled, the clocks to the module are gated.
     */
    void  module_disable();

    /**
     * @brief  This API configures the direction of a specified GPIO pin as being
     *         either input or output.
     * @param  pinnum     The number of the pin in the GPIO instance
     * @param  pindir  The required direction for the GPIO pin
     *
     *   'pinnum' can take one of the following values:
     *   (0 <= pinnum <= 31)\n
     *   'pinDirection' can take one of the following values:
     *  - GPIO_INPUT - pindir configure the pin as an input pin\n
     *  - GPIO_OUTPUT - to configure the pin as an output pin\n
     */
    void  dir_mode_set(uint32_t pinnum, REGS::GPIO::e_PINDIR pindir);

    /**
     * @brief   This API determines the direction of a specified GPIO pin.
     * @param   pinnum    The number of the pin in the GPIO instance
     *
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     * 
     * @return  The direction of the specified pin. This returns one of the
     *          following two values:
     *          - GPIO_DIR_INPUT - signifying that the pin is an input pin\n
     *          - GPIO_DIR_OUTPUT - signifying that the pin is an output pin\n
     *
     */
    REGS::GPIO::e_PINDIR  dir_mode_get(uint32_t pinnum);

    /**
     * @brief  This API drives an output GPIO pin to a logic HIGH or a logic LOW
     *         state.
     * @param  pinnum   The number of the pin in the GPIO instance
     * @param  value    This specifies whether a logic HIGH or a logic LOW
     *                     should be driven on the output pin
     *
     *   'pinnum' can take one of the following values:
     *   (0 <= pinnum <= 31)\n
     *   'value' can take one of the following values:
     *  - false - indicating to drive a logic LOW(logic 0) on the pin.
     *  - true - indicating to drive a logic HIGH(logic 1) on the pin.
     */
    void  pin_write(uint32_t pinnum, bool value);

    /**
     * @brief   This API determines the logic level(value) on a specified
     *          GPIO pin.
     * @param   pinnum   The number of the pin in the GPIO instance
     *
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     *
     * @return  The pin value of the specified pin of the GPIO instance.
     */
    uint32_t  pin_read(uint32_t pinnum);

    /**
     * @brief  This API is used to collectively set and collectively clear the
     *         specified output pins of a GPIO instance.
     * @param  setMask    The bit mask of the bits which have to be set in the
     *                    GPIO Data Output Register(GPIO_DATAOUT)
     * @param  clrMask    The bit mask of the bits which have to cleared in the
     *                    GPIO Data Output Register(GPIO_DATAOUT)
     */
    void  multiple_pins_write(uint32_t setmsk, uint32_t clrmsk);

    /**
     * @brief   This API reads the pin values of the specified pins of the GPIO
     *          instance.
     * @param   readmsk   The bit mask of the bits whose values have to be read
     *                     from the Data Input Register(GPIO_DATAIN).
     *
     * @return  The pin values of the specified pins of the GPIO instance.
     */
    uint32_t  multiple_pins_read(uint32_t readmsk);

    /**
     * @brief  This API enables the configured interrupt event on a specified input
     *         GPIO pin to trigger an interrupt request.
     * @param  intline     This specifies the interrupt request line on which the
     *                     interrupt request due to the transitions on a specified
     *                     pin be propagated
     * @param  pinnum   The number of the pin in the GPIO instance
     *
     *   'intline' can take one of the following two values:
     *  - GPIO_INT_LINE_1 - interrupt request be propagated over interrupt line 1\n
     *  - GPIO_INT_LINE_2 - interrupt request be propagated over interrupt line 2\n
     * 
     *   'pinnum' can take one of the following values:
     *   (0 <= pinnum < 64)\n
     */
    void  pin_int_enable(uint32_t intline, uint32_t pinnum);

    /**
     * @brief  This API disables interrupt generation due to the detection
     *         of any event on a specified input GPIO pin.
     * @param  intline    This specifies the interrupt requeset line which has to
     *                    disabled to transmit interrupt requests due to transitions
     *                    on a specified pin
     * @param  pinnum  The number of the pin in the GPIO instance
     *
     *   'intline' can take one of the following two values:
     *  - GPIO_INT_LINE_1 - signifying that the Interrupt Line 1 be disabled to
     *    transmit interrupt requests due to transitions on specified pin\n
     *  - GPIO_INT_LINE_2 - signifying that the Interrupt Line 2 be disabled to
     *    transmit interrupt requests due to transitions on specified pin\n
     *
     *   'pinnum' can take one of the following values:
     *   (0 <= pinnum <= 31)\n
     */
    void  pin_int_disable(uint32_t intline, uint32_t pinnum);

    /**
     * @brief  This API configures the event type for a specified input GPIO pin.
     *         Whenever the selected event occurs on that GPIO pin and if interrupt
     *         generation is enabled for that pin, the GPIO module will send an
     *         interrupt to CPU.
     * @param  pinnum  The number of the pin in the GPIO instance
     * @param  evnt_type  This specifies the event type on whose detection,
     *                    the GPIO module will send an interrupt to CPU,
     *                    provided interrupt generation for that pin is enabled.
     *
     *   'pinnum' can take one of the following values:
     *   (0 <= pinnum <= 31)\n
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
    void  int_type_set(uint32_t pinnum, REGS::GPIO::e_INT_TYPE evnt_type);

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
    uint32_t  int_type_get(uint32_t pinnum);

    /**
     * @brief  This API determines the enabled interrupt status of a specified pin.
     * @param  intline    This specifies the interrupt line whose corresponding
     *                    enabled interrupt status register has to be accessed.
     *                    The status of the specified pin is returned in this API.
     * @param  pinnum  The number of the pin in the GPIO instance
     * 
     *  'intline' can take one of the following two values:
     * - GPIO_INT_LINE_1 - to read the enabled interrupt status register
     *   corresponding to interrupt line 1\n
     * - GPIO_INT_LINE_2 - to read the enabled interrupt status register
     *   corresponding to interrupt line 2\n
     *
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     *
     * @return The enabled interrupt status of the pin on the specified interrupt
     *         line. This could either be a non-zero or a zero value.
     */
    uint32_t  pin_int_status(uint32_t intline,uint32_t pinnum);

    /**
     * @brief  This API clears the enabled interrupt status of a specified GPIO
     *         pin.
     * @param  intline    This specifies the interrupt line whose corresponding
     *                    enabled interrupt status register has to be accessed.
     *                    The status of the specified bit in it is cleared in this
     *                    API.
     * @param  pinnum  The number of the pin in the GPIO instance
     *
     *  'intline' can take one of the following two values:
     * - GPIO_INT_LINE_1 - to access the enabled interrupt status register
     *   corresponding to interrupt line 1\n
     * - GPIO_INT_LINE_2 - to access the enabled interrupt status register
     *   corresponding to interrupt line 2\n * 
     *   'pinnum' can take one of the following values:
     *   (0 <= pinnum <= 31)\n
    */
    void  pin_int_clear(uint32_t intline, uint32_t pinnum);

    /**
     * @brief  This API determines the raw interrupt status of the specified GPIO
     *         pins in the instance corresponding to the specified interrupt line.
     * @param  intline    This specifies the interrupt line whose corresponding
     *                    raw interrupt status register has to be read.
     * @param  readmsk   The bit mask of the bits whose values have to be read
     *                    from the Raw Interrupt Status Register
     *                    (GPIO_IRQSTATUS_RAW).
     * 
     *  'intline' can take one of the following two values:
     * - GPIO_INT_LINE_1 - to read the raw interrupt status register corresponding
     *   to interrupt line 1\n
     * - GPIO_INT_LINE_2 - to read the raw interrupt status register corresponding
     *   to interrupt line 2\n
     *
     * @return  The raw interrupt status of the specified pins of the GPIO instance
     *          corresponding to a specified interrupt line.
     */
    uint32_t  raw_int_status(uint32_t intline,uint32_t readmsk);

    /**
     * @brief  This API manually triggers an interrupt request due to a specified 
     *         GPIO pin. 
     * @param  intline    This specifies the interrupt line over which the
     *                    manually triggered interrupt request has to be
     *                    propogated
     * @param  pinnum  The number of the pin in the GPIO instance.
     *
     *  'intline' can take one of the following values:
     * - GPIO_INT_LINE_1 - to propogate the interrupt request over interrupt
     *   line 1\n
     * - GPIO_INT_LINE_2 - to propogate the interrupt request over interrupt
     *   line 2\n
     *
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     * @note  Here an interrupt request is manually triggered by writing to a
     *        specified bit in the Raw Interrupt Status register. As a
     *        pre-requisite, the interrupt generation should be enabled for the
     *        GPIO pin.
     */
    void  trigger_pin_int(uint32_t intline, uint32_t pinnum);

    /**
     * @brief  This API enables the GPIO Wakeup Generation feature for all
     *         the pins of the GPIO module.
     * @note   1> A Wakeup signal is generated by an Input GPIO pin when an
     *            expected transition happens on that GPIO pin.\n
     *         2> For any Input pin of the GPIO module to generate Wakeup
     *            signal, the respective global feature for the module has
     *            to be enabled by invoking this API.\n
     */
    void  wakeup_global_enable();

    /**
     * @brief  This API disables the GPIO Wakeup generation feature for all
     *         the pins of the GPIO module.
     */
    void  wakeup_global_disable();

    /**
     * @brief  This API enables the feature for the specified Input GPIO Pin
     *         (Interrupt Request Source) to generate an asynchronous wakeup
     *         signal to the CPU.
     * @param  intline This specifies the Smart Wakeup Interrupt Line over
     *                     which the asynchrounous wakeup signal has to be
     *                     propogated due to the specified Input GPIO pin.
     * @param  pinnum   The number of the pin in the GPIO instance.
     *
     *  'intline' can take one of the following values:
     * - GPIO_INT_SWAKEUP_LINE_1 - to propogate the wakeup request over Smart
     *   Wakeup Interrupt Line 1\n
     * - GPIO_INT_SWAKEUP_LINE_2 - to propagate the wakeup request over Smart
     *   Wakeup Interrupt Line 2\n
     *
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     * @note  1> Make sure that the GPIO instance in context is allowed to generate
     *           Wakeup interrupts to the CPU. If allowed, then enable Wakeup
     *           interrupt generation feature for that GPIO instance in the Interrupt
     *           Controller.\n
     *        2> Usually an Input GPIO Pin acts as an Interrupt Request(IRQ) Source.
     *           An expected transition on an Input GPIO Pin can generate a Wakeup
     *           request.\n
     */
    void  pin_int_wakeup_enable(uint32_t intline, uint32_t pinnum);

    /**
     * @brief  This API disables the feature for the specified Input GPIO Pin
     *         (Interrupt Request Source) to generate an asynchronous wakeup
     *         signal to the CPU.
     * @param  intline This specifies the Smart Wakeup Interupt Line which has
     *                     to be disabled to propogate any asynchrounous wakeup
     *                     signal due to the specified input GPIO Pin.
     * @param  pinnum   The number of the pin in the GPIO instance.
     *
     *  'intline' can take one of the following values:
     * - GPIO_INT_SWAKEUP_LINE_1 - to propogate the wakeup request over Smart
     *   Wakeup Interrupt Line 1\n
     * - GPIO_INT_SWAKEUP_LINE_2 - to propagate the wakeup request over Smart
     *   Wakeup Interrupt Line 2\n
     *
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     */
    void  pin_int_wakeup_disable(uint32_t intline, uint32_t pinnum);

    /**
     * @brief   This API is used to control(enable/disable) the Auto-Idle mode
     *          for GPIO.
     * @param  mode_flag   This specifies whether to enable or disable the
     *                    Auto-Idle mode for the GPIO instance
     *
     *  'mode_flag' can take one of the following two values:
     * - true - to enable the Auto-Idle mode, OCP gating\n
     * - false - to disable the Auto-Idle mode, OCP clock freerun\n
     */
    void  auto_idle_mode_control(bool mode_flag);

    /**
     * @brief  This API is used to configure the Power Management
     *         Request/Acknowledgement process for GPIO.
     * @param  mode_flag   This specifies the Power Management Request/Acknowledge
     *                    mode(Idle Mode Request and Response) to be enabled for
     *                    the GPIO instance
     *
     *  'mode_flag' can take one of the following values:
     * - IDLEMODE_FORCEIDLE - to enable Force-Idle mode\n
     * - IDLEMODE_NOIDLE - to enable No-Idle mode\n
     * - IDLEMODE_SMARTIDLE - to enable Smart-Idle mode\n
     * - IDLEMODE_SMIDLEWAKEUP - to enable Smart-Idle-Wakeup modse\n
     */
    void  idle_mode_configure(REGS::GPIO::e_IDLEMODE mode_flag);

    /**
     * @brief  This API configures the clock gating ratio for the event detection
     *         logic.
     * @param  config_flag This specifies the clock gating ratio value to be
     *                    programmed
     *
     *  'config_flag' can take one of the following values:
     * - GPIO_CTRL_DIVCLK1 - to program the functional clock as
     *   interface clock frequeny divided by 1\n
     * - GPIO_CTRL_DIVCLK2 - to program the functional clock as
     *   interface clock frequency divided by 2\n
     * - GPIO_CTRL_DIVCLK4 - to program the functional clock as
     *   interface clock frequency divided by 4\n
     * - GPIO_CTRL_DIVCLK8 - to program the functional clock as
     *   interface clock frequency divided by 8\n
     */
    void  gating_ratio_configure(REGS::GPIO::e_GATINGRATIO config_flag); 

    /**
     * @brief  This API enables/disables debouncing feature for a specified input
     *         GPIO pin.
     * @param  pinnum    The number of the pin in the GPIO instance
     * @param  ctrl_flag  This specifies whether to enable/disable Debouncing
     *                      feature for the specified input pin
     * 
     *  'pinnum' can take one of the following values:
     *  (0 <= pinnum <= 31)\n
     *
     *  'ctrl_flag' can take one of the following values:
     * - true - to enable the debouncing feature for the
     *   specified input GPIO pin\n
     * - false - to disable the debouncing feature for the
     *   specified input GPIO pin\n
     */
    void  debounce_func_control(uint32_t pinnum, bool ctrl_flag);

    /**
     * @brief  This API configures the debouncing time for all the input pins of
     *         a GPIO instance.
     * @param  debounce_time  This specifies the number of debouncing clock pulses
     *                       each of 31 microseconds long to be used for debouncing
     *                       time. The formula for debouncing time is:
     *                       debounce time = ((debounce_time + 1) * 31) microseconds
     *
     *  'debounce_time' can take a value as per below limits:
     * - (0x00 <= debounce_time <= 0xFF)
     */
    void  debounce_time_config(uint32_t debounce_time);

    /**
     * @brief  This API reads the contents in the Revision register of the GPIO
     *         module.
     * @return The contents of the GPIO_REVISION register.
     */
    REGS::GPIO::GPIO_REVISION_reg_t  revision_info_get();

    /**
     * @brief   This API stores the context of the gpio
     * @param   contextPtr    Pointer to the structure where the GPIO context
     *                        need to be saved.
     **/
    void  gpio_context_save();
    
    /**
     * @brief   This API restores the context of the GPIO
     **/
    void  gpio_context_restore();

private:

                gpio_context_t  m_context;  // gpio context for rebooting
  REGS::GPIO::AM335x_GPIO_Type &m_regs;
};

extern am335x_gpio gpio0;
extern am335x_gpio gpio1;
extern am335x_gpio gpio2;
extern am335x_gpio gpio3;

#endif // _AM335x_GPIO_H