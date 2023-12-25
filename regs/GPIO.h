#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include "utils.h"

namespace REGS
{
    namespace GPIO
    {
        /********************************************************************************************************************/  
        
        /*********************************************** AM335x_GPIO_Type Registers **************************************/ 
            
        /********************************************************************************************************************/ 
        /*  [reset state = 50600801h]*/
        typedef union 
        { 
            struct 
            {                                /* The GPIO revision register is a read only register containing the revision number of the GPIO module. */
                                             /* A write to this register has no effect, the same as the reset transition between ON-ACTIVE and ON-INACTIVE states. */
                uint32_t    MINOR       :6;   // bit: 0..5          (R) Minor Revision
                uint32_t    CUSTOM      :2;   // bit: 6,7           (R) Indicates a special version for a particular device.
                uint32_t    MAJOR       :3;   // bit: 8..10         (R) Major Revision
                uint32_t    RTL         :5;   // bit: 11..15        (R) RTL version
                uint32_t    FUNC        :12;  // bit: 16..27        (R) Indicates a software compatible module family.
                uint32_t                :2;   // bit: 28,29         (R) Reserved 
                uint32_t    SCHEME      :2;   // bit: 30,31         (R) Used to distinguish between old Scheme and current.
            } b;                              // Structure used for bit access 
            uint32_t  reg;                    // Type used for register access 
        } GPIO_REVISION_reg_t;
    
        /*! @brief      The GPIO_SYSCONFIG register controls the various parameters of the L4 interconnect.  
        *   @details    When the AUTOIDLE bit is set, the GPIO_DATAIN read command has a 3 OCP cycle latency due to the data in sample gating mechanism. 
        *               When the AUTOIDLE bit is not set, the GPIO_DATAIN read command has a 2 OCP cycle latency. 
        [reset state = 0x0] */ 
        typedef union 
        { 
            struct 
            {
                uint32_t    AUTOIDLE    :1;   // bit: 0             (RW) Internal interface clock gating strategy 
                                              //                          [0x0 = Internal Interface OCP clock is free-running, 
                                              //                           0x1 = Automatic internal OCP clock gating, based on the OCP interface activity]
                uint32_t    SOFTRESET   :1;   // bit: 1             (RW) Software reset. This bit is automatically reset by the hardware. During reads, it always returns 0
                                              //                          [0x0 = Normal mode, 0x1 = The module is reset]
                uint32_t    ENAWAKEUP   :1;   // bit: 2             (RW) Enable wakeup 
                                              //                          [0x0 = Wakeup generation is disabled, 
                                              //                           0x1 = Wakeup capability is enabled upon expected transition on input GPIO pin]
                uint32_t    IDLEMODE    :2;   // bit: 3,4           (RW) Power Management, Req/Ack control. [see e_GPIO_IDLEMODE]
                uint32_t                :27;  // bit: 5..31         (R) Reserved 
            } b;                              // Structure used for bit access 
            uint32_t  reg;                    // Type used for register access 
        } GPIO_SYSCONFIG_reg_t;
    
        enum e_IDLEMODE : uint32_t
        {
            IDLEMODE_FORCEIDLE    = 0x0,    // Force-idle. An idle request is acknowledged unconditionally 
            IDLEMODE_NOIDLE       = 0x1,    // No-idle. An idle request is never acknowledged 
            IDLEMODE_SMARTIDLE    = 0x2,    // Smart-idle. Acknowledgment to an idle request is given based on the internal activity of the module 
            IDLEMODE_SMIDLEWAKEUP = 0x3     // Smart Idle Wakeup (GPIO0 only)
        };
    
        /*! @brief      This module supports DMA events with its interrupt signal.  
        *   @details    This register must be written to after the DMA completes in order for subsequent DMA events to be triggered from this module. 
        [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {
                uint32_t    DMAEvent_Ack    :1;  // bit: 0          (RW) Write 0 to acknowledge DMA event has been completed.
                                                 //                      Module will be able to generate another DMA event only when the 
                                                 //                      previous one has been acknowledged using this register. Reads always returns 0.
                uint32_t                    :31; // bit: 1..31      (R) Reserved 
            } b;                                 // Structure used for bit access 
            uint32_t  reg;                       // Type used for register access 
        } GPIO_EOI_reg_t;
    
    
        /*! @brief      The GPIO_IRQSTATUS_RAW_0 register provides core status information for the interrupt handling, 
        *               showing all active events (enabled and not enabled).  
        *   @details    The fields are read-write. Writing a 1 to a bit sets it to 1, that is, triggers the IRQ (mostly for debug). 
        *               Writing a 0 has no effect, that is, the register value is not be modified. 
        *               Only enabled, active events trigger an actual interrupt request on the IRQ output line. 
        [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n status. [0x0 = No effect, 0x1 = IRQ is triggered] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_RAW_0_reg_t;
    
        /*! @brief      The GPIO_IRQSTATUS_RAW_1 register provides core status information for the interrupt handling, 
        *               showing all active events (enabled and not enabled).  
        *   @details    The fields are read-write. Writing a 1 to a bit sets it to 1, that is, triggers the IRQ (mostly for debug). 
        *               Writing a 0 has no effect, that is, the register value is not be modified. 
        *               Only enabled, active events trigger an actual interrupt request on the IRQ output line. 
         [reset state = 0x0]*/ 
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n status. [0x0 = No effect, 0x1 = IRQ is triggered] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_RAW_1_reg_t;
    
        /*! @brief      The GPIO_IRQSTATUS_0 register provides core status information for the interrupt handling, showing all
        *               active events which have been enabled.  
        *   @details    The fields are read-write. Writing a 1 to a bit clears the bit to 0, that is, clears the IRQ. 
        *               Writing a 0 has no effect, that is, the register value is not modified. 
        *               Only enabled, active events trigger an actual interrupt request on the IRQ output line. 
        [reset state = 0x0] */ 
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW1C) Interrupt n status. 
                                                //                  [0x0 (W) = No effect, 0x0 (R) = IRQ is not triggered.
                                                //                   0x1 (W) = Clears the IRQ, 0x1 (R) = IRQ is triggered.]
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_0_reg_t;
    
        /*! @brief      The GPIO_IRQSTATUS_1 register provides core status information for the interrupt handling, showing all
        *               active events which have been enabled.  
        *   @details    The fields are read-write. Writing a 1 to a bit clears the bit to 0, that is, clears the IRQ. 
        *               Writing a 0 has no effect, that is, the register value is not modified. 
        *               Only enabled, active events trigger an actual interrupt request on the IRQ output line. 
        [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW1C) Interrupt n status. 
                                                //                          [0x0 (W) = No effect, 0x0 (R) = IRQ is not triggered.
                                                //                           0x1 (W) = Clears the IRQ, 0x1 (R) = IRQ is triggered.]
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_1_reg_t;
    
        /*! @brief      All 1-bit fields in the GPIO_IRQSTATUS_SET_0 register enable a specific interrupt event to trigger an interrupt request.  
        *   @details    Writing a 1 to a bit enables the interrupt field. Writing a 0 has no effect, that is, the register value is not modified. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n enable. [0x0 = No effect, 0x1 = Enable IRQ generation] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_SET_0_reg_t;
    
        /*! @brief      All 1-bit fields in the GPIO_IRQSTATUS_SET_1 register enable a specific interrupt event to trigger an interrupt request.  
        *   @details    Writing a 1 to a bit enables the interrupt field. Writing a 0 has no effect, that is, the register value is not modified. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n enable. [0x0 = No effect, 0x1 = Enable IRQ generation] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_SET_1_reg_t;
    
        /*! @brief      All 1-bit fields in the GPIO_IRQSTATUS_CLR_0 register clear a specific interrupt event.  
        *   @details    Writing a 1 to a bit disables the interrupt field. Writing a 0 has no effect, that is, the register value is not modified. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n enable. [0x0 = No effect, 0x1 = Disable IRQ generation] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_CLR_0_reg_t;
    
        /*! @brief      All 1-bit fields in the GPIO_IRQSTATUS_CLR_1 register clear a specific interrupt event.  
        *   @details    Writing a 1 to a bit disables the interrupt field. Writing a 0 has no effect, that is, the register value is not modified. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n enable. [0x0 = No effect, 0x1 = Disable IRQ generation] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQSTATUS_CLR_1_reg_t;
    
    
        
        /*! @brief      Per-event wakeup enable vector (corresponding to first line of interrupt).  
        *   @details    This register allows the user to mask the expected transition on input GPIO from generating a wakeup request. 
        *               The GPIO_IRQWAKEN_0 is programmed synchronously with the interface clock before any Idle mode request coming from the host
        *               processor. Note: In Force-Idle mode, the module wake-up feature is totally inhibited. The wake-up generation can also be 
        *               gated at module level using the EnaWakeUp bit from GPIO_SYSCONFIG register 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n enable. [0x0 = No effect, 0x1 = Disable IRQ generation] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQWAKEN_0_reg_t;
        
        /*! @brief      Per-event wakeup enable vector (corresponding to first line of interrupt).  
        *   @details    This register allows the user to mask the expected transition on input GPIO from generating a wakeup request. 
        *               The GPIO_IRQWAKEN_1 is programmed synchronously with the interface clock before any Idle mode request coming from the host
        *               processor. Note: In Force-Idle mode, the module wake-up feature is totally inhibited. The wake-up generation can also be 
        *               gated at module level using the EnaWakeUp bit from GPIO_SYSCONFIG register 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE     :32;    // bit: 0..31       (RW) Interrupt n enable. [0x0 = No effect, 0x1 = Disable IRQ generation] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_IRQWAKEN_1_reg_t;
        
        /*! @brief      The GPIO_SYSSTATUS register provides the reset status information about the GPIO module.  
        *   @details    It is a read-only register; a write to this register has no effect. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    RESETDONE   :1;     // bit: 0           (R) Reset status information. [0x0 = Internal Reset is on-going, 0x1 = Reset completed] 
                uint32_t                :31;    // bit: 1..31       (R) Reserved 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_SYSSTATUS_reg_t;
        
        /*! @brief      The GPIO_CTRL register controls the clock gating functionality.  
        *   @details    The DISABLEMODULE bit controls a clock gating feature at the module level. When set, this bit forces the clock gating for all internal clock
        *               paths. Module internal activity is suspended. System interface is not affected by this bit. System interface clock gating is controlled with 
        *               the AUTOIDLE bit in the system configuration register (GPIO_SYSCONFIG). This bit is to be used for power saving when the module is not used 
        *               because of the multiplexing configuration selected at the chip level. This bit has precedence over all other internal configuration bits. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    DISABLEMODULE   :1;     // bit: 0       (RW) Module Disable [0x0 = Module is enabled, clk are not gated, 0x1 = Module is disabled, clk are gated] 
                uint32_t    GATINGRATIO     :2;     // bit: 1..2    (RW) Gating Ratio. Controls the clock gating for the event detection logic. [see e_GPIO_GATINGRATIO]
                uint32_t                    :29;    // bit: 3..31   (R) Reserved 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_CTRL_reg_t;
        
        enum e_GATINGRATIO  : uint32_t
        {
            GPIO_CTRL_DIVCLK1   = 0x0,              // Functional clock is interface clock 
            GPIO_CTRL_DIVCLK2   = 0x1,              // Functional clock is interface clock divided by 2 
            GPIO_CTRL_DIVCLK4   = 0x2,              // Functional clock is interface clock divided by 4 
            GPIO_CTRL_DIVCLK8   = 0x3               // Functional clock is interface clock divided by 8 
        };
        
        /*! @brief      The GPIO_OE register is used to enable the pins output capabilities.  
        *   @details    At reset, all the GPIO related pins are configured as input and output capabilities are disabled. This register is not used within the module, 
        *               its only function is to carry the pads configuration. 
        [reset state = 0xFFFFFFFF]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    OUTPUTEN    :32;    // bit: 0..31   (RW) Output Data Enable [0x0 = The corresponding GPIO port is configured as an output, 0x1 = configured as an input] 
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } GPIO_OE_reg_t;
        
        enum e_PINDIR : uint32_t
        {
            GPIO_OUTPUT = 0x0,
            GPIO_INPUT = 0x1
        };
    
        /*! @brief      The GPIO_DATAIN register is used to register the data that is read from the GPIO pins.  
        *   @details    The GPIO_DATAIN register is a read-only register. The input data is sampled synchronously with the interface clock and then captured in the GPIO_DATAIN 
        *               register synchronously with the interface clock. So, after changing, GPIO pin levels are captured into this register after two interface clock cycles 
        *               (the required cycles to synchronize and to write the data). When the AUTOIDLE bit in the system configuration register (GPIO_SYSCONFIG) is set, 
        *               the GPIO_DATAIN read command has a 3 OCP cycle latency due to the data in sample gating mechanism. When the AUTOIDLE bit is not set, the GPIO_DATAIN 
        *               read command has a 2 OCP cycle latency. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    DATAIN  :32;    // bit: 0..31   (R) Sampled Input Data 
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } GPIO_DATAIN_reg_t;
    
        /*! @brief      The GPIO_DATAOUT register is used for setting the value of the GPIO output pins.  
        *   @details    Data is written to the GPIO_DATAOUT register synchronously with the interface clock. This register can be accessed with direct read/write operations 
        *               or using the alternate Set/Clear feature. This feature enables to set or clear specific bits of this register with a single write access to the set data 
        *               output register (GPIO_SETDATAOUT) or to the clear data output register (GPIO_CLEARDATAOUT) address. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    DATAOUT :32;    // bit: 0..31   (RW) Data to set on output pins
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } GPIO_DATAOUT_reg_t;
    
        /*! @brief      The GPIO_LEVELDETECT0 register is used to enable/disable for each input lines the low-level (0) detection to be used for the interrupt 
        *               request generation.  
        *   @details    Enabling at the same time high-level detection and low-level detection for one given pin makes 
        *               a constant interrupt generator. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {   // see e_INT_TYPE
                uint32_t    LEVELDETECT0    :32;    // bit: 0..31   (RW) Low Level Interrupt Enable [0x0 = Disable the IRQ assertion on low-level detect, 0x1 = Enable] 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_LEVELDETECT0_reg_t;
        
        enum e_INT_TYPE : uint32_t
        {
            INT_TYPE_NO_LEVEL   = 0x01,
            INT_TYPE_LEVEL_LOW  = 0x04,
            INT_TYPE_LEVEL_HIGH = 0x08,
            INT_TYPE_BOTH_LEVEL = 0x0C,            
            INT_TYPE_RISE_EDGE  = 0x10,
            INT_TYPE_FALL_EDGE  = 0x20,
            INT_TYPE_BOTH_EDGE  = 0x30,
            INT_TYPE_NO_EDGE    = 0x80
        };        
        
    
        /*! @brief      The GPIO_LEVELDETECT1 register is used to enable/disable for each input lines the high-level (1) detection to be used for the interrupt 
        *               request generation.  
        *   @details    Enabling at the same time high-level detection and low-level detection for one given pin makes 
        *               a constant interrupt generator 
        [reset state = 0x0]*/  
        typedef union 
        {   // see e_INT_TYPE
            struct 
            {
                uint32_t    LEVELDETECT1    :32;    // bit: 0..31   (RW) High Level Interrupt Enable [0x0 = Disable the IRQ assertion on high-level detect, 0x1 = Enable] 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_LEVELDETECT1_reg_t;
    
        /*! @brief      The GPIO_RISINGDETECT register is used to enable/disable for each input lines the rising-edge (transition 0 to 1) detection to be used 
        *               for the interrupt request generation  
        *   @details 
        [reset state = 0x0]*/  
        typedef union 
        {   // see e_INT_TYPE
            struct 
            {
                uint32_t    RISINGDETECT    :32;    // bit: 0..31   (RW) Rising Edge Interrupt Enable [0x0 = Disable IRQ on rising-edge detect, 0x1 = Enable] 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_RISINGDETECT_reg_t;
        
        /*! @brief      The GPIO_FALLINGDETECT register is used to enable/disable for each input lines the falling-edge (transition 1 to 0) detection to be used 
        *               for the interrupt request generation.  
        *   @details 
        [reset state = 0x0]*/  
        typedef union 
        {   // see e_INT_TYPE
            struct 
            {
                uint32_t    FALLINGDETECT   :32;    // bit: 0..31   (RW) Falling Edge Interrupt Enable [0x0 = Disable IRQ on falling-edge detect, 0x1 = Enable] 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_FALLINGDETECT_reg_t;
    
        /*! @brief      The GPIO_DEBOUNCENABLE register is used to enable/disable the debouncing feature for each input line  
        *   @details 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    DEBOUNCEENABLE  :32;    // bit: 0..31   (RW) Input Debounce Enable [0x0 = Disable debouncing feature on the corresponding input port, 0x1 = Enable] 
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_DEBOUNCENABLE_reg_t;
    
        /*! @brief      The GPIO_DEBOUNCINGTIME register controls debouncing time (the value is global for all ports).  
        *   @details    The debouncing cell is running with the debouncing clock (32 kHz), this register represents the number of the clock cycle(s) (31 s long) to be used. 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    DEBOUNCETIME    :8;     // bit: 0..7    (RW) Input Debouncing Value in 31 microsecond steps. Debouncing Value = (DEBOUNCETIME + 1) * 31 microseconds 
                uint32_t                    :24;    // bit: 8..31   (RW) Reserved 
    
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } GPIO_DEBOUNCINGTIME_reg_t;
    
        /*! @brief      The GPIO_CLEARDATAOUT register clears to 0 the corresponding bit in the GPIO_DATAOUT register.  
        *   @details    Writing a 1 to a bit in the GPIO_CLEARDATAOUT register clears to 0 the corresponding bit in the GPIO_DATAOUT register; writing a 0 has no effect. 
        *               A read of the GPIO_CLEARDATAOUT register returns the value of the data output register (GPIO_DATAOUT). 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE :32;    // bit: 0..31    (RW) Clear Data Output Register [0x0 = No effect, 0x1 = Clear the corresponding bit in the GPIO_DATAOUT register] 
            } b;                            // Structure used for bit access 
            uint32_t  reg;                   // Type used for register access 
        } GPIO_CLEARDATAOUT_reg_t;
    
        /*! @brief      The GPIO_SETDATAOUT register sets to 1 the corresponding bit in the GPIO_DATAOUT registe.  
        *   @details    Writing a 1 to a bit in the GPIO_SETDATAOUT register sets to 1 the corresponding bit in the GPIO_DATAOUT register; writing a 0 has no effect. 
        *               A read of the GPIO_SETDATAOUT register returns the value of the data output register (GPIO_DATAOUT). 
        [reset state = 0x0]*/  
        typedef union 
        { 
            struct 
            {
                uint32_t    INTLINE :32;    // bit: 0..7    (RW) Set Data Output Register [0x0 = No effect, 0x1 = Set the corresponding bit in the GPIO_DATAOUT register] 
            } b;                            // Structure used for bit access 
            uint32_t  reg;                   // Type used for register access 
        } GPIO_SETDATAOUT_reg_t;
    
    
        struct AM335x_GPIO_Type
        {                                                                                      
            __R     GPIO_REVISION_reg_t         REVISION;          // (0x0)  GPIOx register containing the revision number of the module (page 4991, 25.4.1.1 dataheets)
            __RW    uint32_t                    RESERVED1[3];
            __RW    GPIO_SYSCONFIG_reg_t        SYSCONFIG;         // (0x10) GPIOx register controls the various parameters of the L4 interconnect. 
            __RW    uint32_t                    RESERVED2[3];
            __RW    GPIO_EOI_reg_t              EOI;               // (0x20) GPIOx module supports DMA events with its interrupt signal. 
            __RW    GPIO_IRQSTATUS_RAW_0_reg_t  IRQSTATUS_RAW_0;   // (0x24) GPIOx register 0 provides core status info for the IRQ, showing all active events (enabled and not enabled). 
            __RW    GPIO_IRQSTATUS_RAW_1_reg_t  IRQSTATUS_RAW_1;   // (0x28) GPIOx register 1 provides core status info for the IRQ, showing all active events (enabled and not enabled). 
            __RW    GPIO_IRQSTATUS_0_reg_t      IRQSTATUS_0;       // (0x2C) GPIOx IRQ register 0 provides core status information for the interrupt handling (RW1C) 
            __RW    GPIO_IRQSTATUS_1_reg_t      IRQSTATUS_1;       // (0x30) GPIOx IRQ register 1 provides core status information for the interrupt handling (RW1C) 
            __RW    GPIO_IRQSTATUS_SET_0_reg_t  IRQSTATUS_SET_0;   // (0x34) GPIOx IRQ register 0 enable a specific interrupt event to trigger an interrupt request.
            __RW    GPIO_IRQSTATUS_SET_1_reg_t  IRQSTATUS_SET_1;   // (0x38) GPIOx IRQ register 1 enable a specific interrupt event to trigger an interrupt request. 
            __RW    GPIO_IRQSTATUS_CLR_0_reg_t  IRQSTATUS_CLR_0;   // (0x3C) GPIOx IRQ register 0 clear a specific interrupt event. 
            __RW    GPIO_IRQSTATUS_CLR_1_reg_t  IRQSTATUS_CLR_1;   // (0x40) GPIOx IRQ register 1 clear a specific interrupt event. 
            __RW    GPIO_IRQWAKEN_0_reg_t       IRQWAKEN_0;        // (0x44) GPIOx IRQ per-event wakeup enable vector (corresponding to first line of interrupt). 
            __RW    GPIO_IRQWAKEN_1_reg_t       IRQWAKEN_1;        // (0x48) GPIOx IRQ per-event wakeup enable vector (corresponding to first line of interrupt). 
            __RW    uint32_t                    RESERVED3[50];
            __R     GPIO_SYSSTATUS_reg_t        SYSSTATUS;         // (0x114) GPIOx register provides the reset status information 
            __RW    uint32_t                    RESERVED4[6];
            __RW    GPIO_CTRL_reg_t             CTRL;              // (0x130) GPIOx register controls the clock gating functionality. 
            __RW    GPIO_OE_reg_t               OE;                // (0x134) GPIOx register is used to enable the pins output capabilities. 
            __RW    GPIO_DATAIN_reg_t           DATAIN;            // (0x138) GPIOx register is used for read pins 
            __RW    GPIO_DATAOUT_reg_t          DATAOUT;           // (0x13C) GPIOx register is used for setting the value of the output pins 
            __RW    GPIO_LEVELDETECT0_reg_t     LEVELDETECT0;      // (0x140) GPIOx register is used for each input lines the low-level (0) detection to be used for the IRQ 
            __RW    GPIO_LEVELDETECT1_reg_t     LEVELDETECT1;      // (0x144) GPIOx register is used for each input lines the high-level (1) detection to be used for the IRQ 
            __RW    GPIO_RISINGDETECT_reg_t     RISINGDETECT;      // (0x148) GPIOx register is used to set for each input lines the rising-edge (transition 0 to 1) detection to be used for the IRQ 
            __RW    GPIO_FALLINGDETECT_reg_t    FALLINGDETECT;     // (0x14C) GPIOx register is used to set for each input lines the falling-edge (transition 1 to 0) detection to be used for the IRQ 
            __RW    GPIO_DEBOUNCENABLE_reg_t    DEBOUNCENABLE;     // (0x150) GPIOx register is used to enable/disable the debouncing feature for each input line
            __RW    GPIO_DEBOUNCINGTIME_reg_t   DEBOUNCINGTIME;    // (0x154) GPIOx register controls debouncing time 
            __RW    uint32_t                    RESERVED5[14];
            __RW    GPIO_CLEARDATAOUT_reg_t     CLEARDATAOUT;      // (0x190) GPIOx register clears to 0 the corresponding bit in the GPIO_DATAOUT register. 
            __RW    GPIO_SETDATAOUT_reg_t       SETDATAOUT;        // (0x194) GPIOx register sets to 1 the corresponding bit in the GPIO_DATAOUT registe. 
        };
        
        enum e_int_line_num : uint32_t
        {
            INT_LINE_1 = 0x0,
            INT_LINE_2 = 0x1
        };
    
        constexpr uint32_t AM335x_GPIO_0_BASE      = 0x44E07000; // 0x44E08000 - RESERVED
        constexpr uint32_t AM335x_GPIO_1_BASE      = 0x4804C000; // 0x4804D000 - RESERVED
        constexpr uint32_t AM335x_GPIO_2_BASE      = 0x481AC000; // 0x481AD000 - RESERVED
        constexpr uint32_t AM335x_GPIO_3_BASE      = 0x481AE000; // 0x481AF000 - RESERVED
    
        constexpr AM335x_GPIO_Type *AM335x_GPIO_0 = ((AM335x_GPIO_Type *) AM335x_GPIO_0_BASE); 
        constexpr AM335x_GPIO_Type *AM335x_GPIO_1 = ((AM335x_GPIO_Type *) AM335x_GPIO_1_BASE); 
        constexpr AM335x_GPIO_Type *AM335x_GPIO_2 = ((AM335x_GPIO_Type *) AM335x_GPIO_2_BASE);
        constexpr AM335x_GPIO_Type *AM335x_GPIO_3 = ((AM335x_GPIO_Type *) AM335x_GPIO_3_BASE);
    
    } //end of namespace GPIO
} // end of namespace REGS 

#endif //_GPIO_H_
