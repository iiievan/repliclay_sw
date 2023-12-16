#ifndef _INTC_H_
#define _INTC_H_

#include <stdint.h>
#include "utils.h"

namespace REGS
{
    //This is interrupt controller class and his namespace
    namespace INTC
    { 
    /***********************************************************************************************************************************************/  
    
    /**************************************************** AM335x_INTC_Type Registers ***************************************************************/ 
    
    /***********************************************************************************************************************************************/      
        
        /* [reset state = 0x50]*/
        typedef union 
        { 
            struct 
            {                                      /* This register contains the IP revision code */
                                                   /* IP revision
                                                    [7:4] Major revision
                                                    [3:0] Minor revision Examples: 0x10 for 1.0, 0x21 for 2.1 */
                 
                uint32_t    Rev        :8;         // bit: 0..7    (R) IP revision                    
                uint32_t               :24;        // bit: 8..31   Reserved  
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } REVISION_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                      /* This register controls the various parameters of the OCP interface */
                 
                uint32_t    Autoidle   :1;         // bit: 0       (RW) Internal OCP clock gating strategy [0x0 = clkfree, 0x1 = autoClkGate]
                uint32_t    SoftReset  :1;         // bit: 1       (RW) Software reset. [0x0 = always returns 0, 0x1 = never happens]                  
                uint32_t               :30;        // bit: 3..31   Reserved  
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } SYSCONFIG_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                      /* This register controls the various parameters of the OCP interface */
                 
                uint32_t    ResetDone  :1;         // bit: 0       (R) Internal reset monitoring [0x0 = reset is on-going, 0x1 = Reset completed]                 
                uint32_t               :31;        // bit: 1..31   Reserved  
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } SYSSTATUS_reg_t;
    
        /* [reset state = 0xFFFFFF80]*/
        typedef union 
        { 
            struct 
            {                                         /* This register supplies the currently active IRQ interrupt number. */
                 
                uint32_t    ActiveIRQ    :7;         // bit: 0..6    (RW) Active IRQ number   
                uint32_t    SpuriousIRQ  :25;        // bit: 7..31   (RW) Spurious IRQ flag             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } SIR_IRQ_reg_t;
    
        /* [reset state = 0xFFFFFF80]*/
        typedef union 
        { 
            struct 
            {                                         /* This register supplies the currently active FIQ interrupt number */
                 
                uint32_t    ActiveFIQ    :7;         // bit: 0..6    (R) Active FIQ number   
                uint32_t    SpuriousFIQ  :25;        // bit: 7..31   (R) Spurious FIQ flag             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } SIR_FIQ_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* This register contains the new interrupt agreement bits */
                 
                uint32_t    NewIRQAgr  :1;         // bit: 0        (W) Reset IRQ output and enable new IRQ generation  [0x0 = no function effect, 0x1 = generate IRQ]
                uint32_t    NewFIQAgr  :1;         // bit: 1        (W) Reset FIQ output and enable new FIQ generation [0x0 = no function effect, 0x1 = generate FIQ]
                uint32_t               :30;        // bit: 2..31    Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } CONTROL_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                      /* This register controls protection of the other registers. This register can only be accessed in priviledged */
                                                   /* mode, regardless of the curent value of the protection bit.                                                 */
                 
                uint32_t    Protection  :1;         // bit: 0       (RW) Protection mode [0x0 = disabled(def), 0x1 = enabled]                 
                uint32_t                :31;        // bit: 1..31   Reserved  
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PROTECTION_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* This register controls the clock auto-idle for the functional clock and the input synchronisers */
                 
                uint32_t    FuncIdle   :1;         // bit: 0        (RW) Functional clock auto-idle mode  [0x0 = is applied, 0x1 = auto-gated based on interrupt input activity]
                uint32_t    Turbo      :1;         // bit: 1        (RW) Input synchroniser clock auto-gating [0x0 = is free running (default), 0x1 = generate IRQ]
                uint32_t               :30;        // bit: 2..31    Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } IDLE_reg_t;
    
        /* [reset state = 0xFFFFFFC0]*/
        typedef union 
        { 
            struct 
            {                                         /* This register supplies the currently active IRQ priority level */
                 
                uint32_t    IRQPriority      :7;     // bit: 0..6    (R) Current IRQ priority  
                uint32_t    SpuriousIRQflag  :25;    // bit: 7..31   (R) Spurious IRQ flag             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } IRQ_PRIORITY_reg_t;
    
        /* [reset state = 0xFFFFFFC0]*/
        typedef union 
        { 
            struct 
            {                                         /* This register supplies the currently active FIQ priority level */
                 
                uint32_t    FIQPriority      :7;     // bit: 0..6    (R) Current FIQ priority  
                uint32_t    SpuriousFIQflag  :25;    // bit: 7..31   (R) Spurious FIQ flag            
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } FIQ_PRIORITY_reg_t;
    
        /* [reset state = 0xFF]*/
        typedef union 
        { 
            struct 
            {                                          /* This register sets the priority threshold */
                 
                uint32_t    PriorityThreshold  :8;     // bit: 0..7     (RW) Priority threshold. Values used are 00h to 3Fh. Value FFh disables the threshold.  
                uint32_t                       :24;    // bit: 8..31    Reserved           
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } THRESHOLD_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register sets the priority threshold */
                 
                uint32_t    Itr             :32;       // bit: 0..31     (R) Interrupt status before masking          
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } ITR_reg_t;
    
        /* [reset state = 0xFFFFFFFF]*/
        typedef union 
        { 
            struct 
            {                                          /* This register contains the interrupt mask */
                 
                uint32_t    Mir             :32;       // bit: 0..31     (RW) Interrupt mask          
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } MIR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register is used to clear the interrupt mask bits. */
                 
                uint32_t    MirClear       :32;        // bit: 0..31     (W) Write 1 clears the mask bit to 0, reads return 0         
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } MIR_CLEAR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register is used to set the interrupt mask bits. */
                 
                uint32_t    MirSet        :32;         // bit: 0..31     (W) Write 1 sets the mask bit to 1, reads return 0         
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } MIR_SET_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /*This register is used to set the software interrupt bits. It is also   */
                                                       /* used to read the currently active software interrupts.                 */
                 
                uint32_t    IsrSet         :32;        // bit: 0..31     (RW) Reads returns the currently active software interrupts, Write 1 sets the software interrupt bits to 1        
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } ISR_SET_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register is used to clear the software interrupt bits   */
                 
                uint32_t    IsrClear        :32;       // bit: 0..31     (W) Write 1 clears the software interrupt bits to 0, reads return 0        
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } ISR_CLEAR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register contains the IRQ status after masking */
                 
                uint32_t    PendingIRQ        :32;     // bit: 0..31     (R) IRQ status after masking       
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } PENDING_IRQ_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register contains the FIQ status after masking */
                 
                uint32_t    PendingFIQ        :32;     // bit: 0..31     (R) FIQ status after masking       
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } PENDING_FIQ_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* The INTC_ILRx registers contain the priority for the interrupts and the FIQ/IRQ steering. */
                 
                uint32_t    FIQnIRQ    :1;         // bit: 0        (RW) Interrupt IRQ FiQ mapping  [0x0 = Interrupt is routed to IRQ, 0x1 = Interrupt is routed to FIQ]
                                                   //                    (this selection is reserved onGP devices).
                uint32_t               :1;         // bit: 1        Reserved
                uint32_t    Priority   :6;         // bit: 2..7     (RW) Interrupt priority
                uint32_t               :24;        // bit: 8..31    Reserved      
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } INTC_ILR_reg_t;
    
        struct AM335x_INTC_Type
        {                                                                                      
            __R   REVISION_reg_t        REVISION;           // (0x00)
            __R   uint32_t              RESERVED[3];  
            __RW  SYSCONFIG_reg_t       SYSCONFIG;          // (0x10) 
            __R   SYSSTATUS_reg_t       SYSSTATUS;          // (0x14) 
            __R   uint32_t              RESERVED1[10];  
            __RW  SIR_IRQ_reg_t         SIR_IRQ;            // (0x40)  
            __R   SIR_FIQ_reg_t         SIR_FIQ;            // (0x44)  
            __W   CONTROL_reg_t         CONTROL;            // (0x48)  
            __RW  PROTECTION_reg_t      PROTECTION;         // (0x4C)  
            __RW  IDLE_reg_t            IDLE;               // (0x50) 
            __R   uint32_t              RESERVED2[3]; 
            __RW  IRQ_PRIORITY_reg_t    IRQ_PRIORITY;       // (0x60)  
            __RW  FIQ_PRIORITY_reg_t    FIQ_PRIORITY;       // (0x64)
            __RW  THRESHOLD_reg_t       THRESHOLD;          // (0x68)
            __R   uint32_t              RESERVED3[5];   
    
            __R   ITR_reg_t             ITR0;               // (0x80)  
            __RW  MIR_reg_t             MIR0;               // (0x84)  
            __W   MIR_CLEAR_reg_t       MIR_CLEAR0;         // (0x88)  
            __W   MIR_SET_reg_t         MIR_SET0;           // (0x8C)  
            __RW  ISR_SET_reg_t         ISR_SET0;           // (0x90)  
            __W   ISR_CLEAR_reg_t       ISR_CLEAR0;         // (0x94) 
            __R   PENDING_IRQ_reg_t     PENDING_IRQ0;       // (0x98)   
            __R   PENDING_FIQ_reg_t     PENDING_FIQ0;       // (0x9C) 
    
            __R   ITR_reg_t             ITR1;               // (0xA0)
            __RW  MIR_reg_t             MIR1;               // (0xA4)  
            __W   MIR_CLEAR_reg_t       MIR_CLEAR1;         // (0xA8)  
            __W   MIR_SET_reg_t         MIR_SET1;           // (0xAC)  
            __RW  ISR_SET_reg_t         ISR_SET1;           // (0xB0)  
            __W   ISR_CLEAR_reg_t       ISR_CLEAR1;         // (0xB4)  
            __R   PENDING_IRQ_reg_t     PENDING_IRQ1;       // (0xB8)  
            __R   PENDING_FIQ_reg_t     PENDING_FIQ1;       // (0xBC) 
    
            __R   ITR_reg_t             ITR2;               // (0xC0)   
            __RW  MIR_reg_t             MIR2;               // (0xC4)  
            __W   MIR_CLEAR_reg_t       MIR_CLEAR2;         // (0xC8)
            __W   MIR_SET_reg_t         MIR_SET2;           // (0xCC)
            __RW  ISR_SET_reg_t         ISR_SET2;           // (0xD0)  
            __W   ISR_CLEAR_reg_t       ISR_CLEAR2;         // (0xD4)  
            __R   PENDING_IRQ_reg_t     PENDING_IRQ2;       // (0xD8)
            __R   PENDING_FIQ_reg_t     PENDING_FIQ2;       // (0xDC) 
    
            __R   ITR_reg_t             ITR3;               // (0xE0)  
            __RW  MIR_reg_t             MIR3;               // (0xE4)  
            __W   MIR_CLEAR_reg_t       MIR_CLEAR3;         // (0xE8)  
            __W   MIR_SET_reg_t         MIR_SET3;           // (0xEC) 
            __RW  ISR_SET_reg_t         ISR_SET3;           // (0xF0)
            __W   ISR_CLEAR_reg_t       ISR_CLEAR3;         // (0xF4)  
            __R   PENDING_IRQ_reg_t     PENDING_IRQ3;       // (0xF8)  
            __R   PENDING_FIQ_reg_t     PENDING_FIQ3;       // (0xFC)
    
            __RW  INTC_ILR_reg_t        INTC_ILR_0;         // (0x100)      EMUINT
            __RW  INTC_ILR_reg_t        INTC_ILR_1;         // (0x104)      COMMTX
            __RW  INTC_ILR_reg_t        INTC_ILR_2;         // (0x108)      COMMRX
            __RW  INTC_ILR_reg_t        INTC_ILR_3;         // (0x10C)      BENCH
            __RW  INTC_ILR_reg_t        INTC_ILR_4;         // (0x110)      ELM_IRQ 
            __RW  INTC_ILR_reg_t        INTC_ILR_5;         // (0x114)      SSM_WFI_IRQ
            __RW  INTC_ILR_reg_t        INTC_ILR_6;         // (0x118)      SSM_IRQ
            __RW  INTC_ILR_reg_t        INTC_ILR_7;         // (0x11C)      NMI
            __RW  INTC_ILR_reg_t        INTC_ILR_8;         // (0x120)      SEC_EVNT
            __RW  INTC_ILR_reg_t        INTC_ILR_9;         // (0x124)      L3DEBUG
    
            __RW  INTC_ILR_reg_t        INTC_ILR_10;         // (0x128)     L3APPINT
            __RW  INTC_ILR_reg_t        INTC_ILR_11;         // (0x12C)     PRCMINT
            __RW  INTC_ILR_reg_t        INTC_ILR_12;         // (0x130)     EDMACOMPINT
            __RW  INTC_ILR_reg_t        INTC_ILR_13;         // (0x134)     EDMAMPERR
            __RW  INTC_ILR_reg_t        INTC_ILR_14;         // (0x138)     EDMAERRINT
            __RW  INTC_ILR_reg_t        INTC_ILR_15;         // (0x13C)     WDT0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_16;         // (0x140)     ADC_TSC_GENINT
            __RW  INTC_ILR_reg_t        INTC_ILR_17;         // (0x144)     USBSSINT
            __RW  INTC_ILR_reg_t        INTC_ILR_18;         // (0x148)     USBINT0
            __RW  INTC_ILR_reg_t        INTC_ILR_19;         // (0x14C)     USBINT1
    
            __RW  INTC_ILR_reg_t        INTC_ILR_20;         // (0x150)     PRU_ICSS_EVTOUT0
            __RW  INTC_ILR_reg_t        INTC_ILR_21;         // (0x154)     PRU_ICSS_EVTOUT1
            __RW  INTC_ILR_reg_t        INTC_ILR_22;         // (0x158)     PRU_ICSS_EVTOUT2
            __RW  INTC_ILR_reg_t        INTC_ILR_23;         // (0x15C)     PRU_ICSS_EVTOUT3
            __RW  INTC_ILR_reg_t        INTC_ILR_24;         // (0x160)     PRU_ICSS_EVTOUT4
            __RW  INTC_ILR_reg_t        INTC_ILR_25;         // (0x164)     PRU_ICSS_EVTOUT5
            __RW  INTC_ILR_reg_t        INTC_ILR_26;         // (0x168)     PRU_ICSS_EVTOUT6 
            __RW  INTC_ILR_reg_t        INTC_ILR_27;         // (0x16C)     PRU_ICSS_EVTOUT7
            __RW  INTC_ILR_reg_t        INTC_ILR_28;         // (0x170)     MMCSD1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_29;         // (0x174)     MMCSD2INT
    
            __RW  INTC_ILR_reg_t        INTC_ILR_30;         // (0x178)     I2C2INT
            __RW  INTC_ILR_reg_t        INTC_ILR_31;         // (0x17C)     eCAP0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_32;         // (0x180)     GPIOINT2A
            __RW  INTC_ILR_reg_t        INTC_ILR_33;         // (0x184)     GPIOINT2B 
            __RW  INTC_ILR_reg_t        INTC_ILR_34;         // (0x188)     USBWAKEUP
            __RW  INTC_ILR_reg_t        INTC_ILR_35;         // (0x18C)     Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_36;         // (0x190)     LCDCINT
            __RW  INTC_ILR_reg_t        INTC_ILR_37;         // (0x194)     GFXINT
            __RW  INTC_ILR_reg_t        INTC_ILR_38;         // (0x198)     2DHWAINT
            __RW  INTC_ILR_reg_t        INTC_ILR_39;         // (0x19C)     ePWM2INT
    
            __RW  INTC_ILR_reg_t        INTC_ILR_40;         // (0x1A0)     3PGSWRXTHR0(RX_THRESH_PULSE)
            __RW  INTC_ILR_reg_t        INTC_ILR_41;         // (0x1A4)     3PGSWRXINT0 (RX_PULSE)
            __RW  INTC_ILR_reg_t        INTC_ILR_42;         // (0x1A8)     3PGSWTXINT0 (TX_PULSE)
            __RW  INTC_ILR_reg_t        INTC_ILR_43;         // (0x1AC)     3PGSWMISC0 (MISC_PULSE)
            __RW  INTC_ILR_reg_t        INTC_ILR_44;         // (0x1B0)     UART3INT
            __RW  INTC_ILR_reg_t        INTC_ILR_45;         // (0x1B4)     UART4INT
            __RW  INTC_ILR_reg_t        INTC_ILR_46;         // (0x1B8)     UART5INT
            __RW  INTC_ILR_reg_t        INTC_ILR_47;         // (0x1BC)     eCAP1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_48;         // (0x1C0)     Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_49;         // (0x1C4)     Reserved
    
            __RW  INTC_ILR_reg_t        INTC_ILR_50;         // (0x1C8)     Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_51;         // (0x1CC)     Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_52;         // (0x1D0)     DCAN0_INT0
            __RW  INTC_ILR_reg_t        INTC_ILR_53;         // (0x1D4)     DCAN0_INT1
            __RW  INTC_ILR_reg_t        INTC_ILR_54;         // (0x1D8)     DCAN0_PARITY
            __RW  INTC_ILR_reg_t        INTC_ILR_55;         // (0x1DC)     DCAN1_INT0
            __RW  INTC_ILR_reg_t        INTC_ILR_56;         // (0x1E0)     DCAN1_INT1
            __RW  INTC_ILR_reg_t        INTC_ILR_57;         // (0x1E4)     DCAN1_PARITY
            __RW  INTC_ILR_reg_t        INTC_ILR_58;         // (0x1E8)     ePWM0_TZINT
            __RW  INTC_ILR_reg_t        INTC_ILR_59;         // (0x1EC)     ePWM1_TZINT
    
            __RW  INTC_ILR_reg_t        INTC_ILR_60;         // (0x1F0)     ePWM2_TZINT
            __RW  INTC_ILR_reg_t        INTC_ILR_61;         // (0x1F4)     eCAP2INT
            __RW  INTC_ILR_reg_t        INTC_ILR_62;         // (0x1F8)     GPIOINT3A
            __RW  INTC_ILR_reg_t        INTC_ILR_63;         // (0x1FC)     GPIOINT3B
            __RW  INTC_ILR_reg_t        INTC_ILR_64;         // (0x200)     MMCSD0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_65;         // (0x204)     McSPI0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_66;         // (0x208)     TINT0
            __RW  INTC_ILR_reg_t        INTC_ILR_67;         // (0x20C)     TINT1_1MS
            __RW  INTC_ILR_reg_t        INTC_ILR_68;         // (0x210)     TINT2
            __RW  INTC_ILR_reg_t        INTC_ILR_69;         // (0x214)     TINT3
    
            __RW  INTC_ILR_reg_t        INTC_ILR_70;         // (0x218)     I2C0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_71;         // (0x21C)     I2C1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_72;         // (0x220)     UART0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_73;         // (0x224)     UART1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_74;         // (0x228)     UART2INT
            __RW  INTC_ILR_reg_t        INTC_ILR_75;         // (0x22C)     RTCINT
            __RW  INTC_ILR_reg_t        INTC_ILR_76;         // (0x230)     RTCALARMINT
            __RW  INTC_ILR_reg_t        INTC_ILR_77;         // (0x234)     MBINT0
            __RW  INTC_ILR_reg_t        INTC_ILR_78;         // (0x238)     M3_TXEV
            __RW  INTC_ILR_reg_t        INTC_ILR_79;         // (0x23C)     eQEP0INT
    
            __RW  INTC_ILR_reg_t        INTC_ILR_80;         // (0x240)     MCATXINT0
            __RW  INTC_ILR_reg_t        INTC_ILR_81;         // (0x244)     MCARXINT0
            __RW  INTC_ILR_reg_t        INTC_ILR_82;         // (0x248)     MCATXINT1
            __RW  INTC_ILR_reg_t        INTC_ILR_83;         // (0x24C)     MCARXINT1
            __RW  INTC_ILR_reg_t        INTC_ILR_84;         // (0x250)     Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_85;         // (0x254)     Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_86;         // (0x258)     ePWM0INT
            __RW  INTC_ILR_reg_t        INTC_ILR_87;         // (0x25C)     ePWM1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_88;         // (0x260)     eQEP1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_89;         // (0x264)     eQEP2INT
    
            __RW  INTC_ILR_reg_t        INTC_ILR_90;         // (0x268)     DMA_INTR_PIN2
            __RW  INTC_ILR_reg_t        INTC_ILR_91;         // (0x26C)     WDT1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_92;         // (0x270)     TINT4   
            __RW  INTC_ILR_reg_t        INTC_ILR_93;         // (0x274)     TINT5    
            __RW  INTC_ILR_reg_t        INTC_ILR_94;         // (0x278)     TINT6   
            __RW  INTC_ILR_reg_t        INTC_ILR_95;         // (0x27C)     TINT7
            __RW  INTC_ILR_reg_t        INTC_ILR_96;         // (0x280)     GPIOINT0A
            __RW  INTC_ILR_reg_t        INTC_ILR_97;         // (0x284)     GPIOINT0B
            __RW  INTC_ILR_reg_t        INTC_ILR_98;         // (0x288)     GPIOINT1A
            __RW  INTC_ILR_reg_t        INTC_ILR_99;         // (0x28C)     GPIOINT1B
    
            __RW  INTC_ILR_reg_t        INTC_ILR_100;         // (0x290)    GPMCINT
            __RW  INTC_ILR_reg_t        INTC_ILR_101;         // (0x294)    DDRERR0
            __RW  INTC_ILR_reg_t        INTC_ILR_102;         // (0x298)    AES0_IRQ_S
            __RW  INTC_ILR_reg_t        INTC_ILR_103;         // (0x29C)    AES0_IRQ_P
            __RW  INTC_ILR_reg_t        INTC_ILR_104;         // (0x2A0)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_105;         // (0x2A4)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_106;         // (0x2A8)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_107;         // (0x2AC)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_108;         // (0x2B0)    SHA_IRQ_S
            __RW  INTC_ILR_reg_t        INTC_ILR_109;         // (0x2B4)    SHA_IRQ_P
    
            __RW  INTC_ILR_reg_t        INTC_ILR_110;         // (0x2B8)    FPKA_SINTREQUEST_S
            __RW  INTC_ILR_reg_t        INTC_ILR_111;         // (0x2BC)    RNG_IRQ
            __RW  INTC_ILR_reg_t        INTC_ILR_112;         // (0x2C0)    TCERRINT0
            __RW  INTC_ILR_reg_t        INTC_ILR_113;         // (0x2C4)    TCERRINT1
            __RW  INTC_ILR_reg_t        INTC_ILR_114;         // (0x2C8)    TCERRINT2
            __RW  INTC_ILR_reg_t        INTC_ILR_115;         // (0x2CC)    ADC_TSC_PENINT
            __RW  INTC_ILR_reg_t        INTC_ILR_116;         // (0x2D0)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_117;         // (0x2D4)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_118;         // (0x2D8)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_119;         // (0x2DC)    Reserved
    
            __RW  INTC_ILR_reg_t        INTC_ILR_120;         // (0x2E0)    SMRFLX_Sabertooth
            __RW  INTC_ILR_reg_t        INTC_ILR_121;         // (0x2E4)    SMRFLX_Core
            __RW  INTC_ILR_reg_t        INTC_ILR_122;         // (0x2E8)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_123;         // (0x2EC)    DMA_INTR_PIN0
            __RW  INTC_ILR_reg_t        INTC_ILR_124;         // (0x2F0)    DMA_INTR_PIN1
            __RW  INTC_ILR_reg_t        INTC_ILR_125;         // (0x2F4)    SPI1INT
            __RW  INTC_ILR_reg_t        INTC_ILR_126;         // (0x2F8)    Reserved
            __RW  INTC_ILR_reg_t        INTC_ILR_127;         // (0x2FC)    Reserved                                                                                 
        }; 
    
        enum e_INT_ID : uint32_t
        {                                // interrupt source
    
            EMUINT              = 0,     // MPU Subsystem Internal
            COMMTX              = 1,     // MPU Subsystem Internal
            COMMRX              = 2,     // MPU Subsystem Internal 
            BENCH               = 3,     // MPU Subsystem Internal
            ELM_IRQ             = 4,     // ELM
            SSM_WFI_IRQ         = 5,     // MPU Subsystem Internal(SSM)
            SSM_IRQ             = 6,     // MPU Subsystem Internal(SSM)
            NMI                 = 7,     // External Pin (active low)
            SEC_EVNT            = 8,     // Firewalls
            L3DEBUG             = 9,     // L3
            L3APPINT            = 10,    // L3
            PRCMINT             = 11,    // PRCM
            EDMACOMPINT         = 12,    // TPCC (EDMA)
            EDMAMPERR           = 13,    // TPCC (EDMA)
            EDMAERRINT          = 14,    // TPCC (EDMA)
            WDT0INT             = 15,    // WDTIMER0
            ADC_TSC_GENINT      = 16,    // ADC_TSC (Touchscreen Controller)
            USBSSINT            = 17,    // USBSS
            USB0                = 18,    // USBSS
            USB1                = 19,    // USBSS
            PRUSS1_EVTOUT0      = 20,    // pr1_host[0] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT1      = 21,    // pr1_host[1] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT2      = 22,    // pr1_host[2] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT3      = 23,    // pr1_host[3] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT4      = 24,    // pr1_host[4] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT5      = 25,    // pr1_host[5] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT6      = 26,    // pr1_host[6] output/eventsexported from PRU-ICSS
            PRUSS1_EVTOUT7      = 27,    // pr1_host[7] output/eventsexported from PRU-ICSS
            MMCSD1INT           = 28,    // MMCSD1
            MMCSD2INT           = 29,    // MMCSD2
            I2C2INT             = 30,    // I2C2
            eCAP0INT            = 31,    // eCAP0 event/interrupt
            GPIOINT2A           = 32,    // GPIO 2
            GPIOINT2B           = 33,    // GPIO 2
            USBWAKEUP           = 34,    // USBSS
            LCDCINT             = 36,    // LCDC
            GFXINT              = 37,    // SGX530
            DHWA2INT            = 38,    // DHWA2INT
            ePWM2INT            = 39,    // eHRPWM2 (PWM Subsystem)
            PGSW3RXTHR0         = 40,    // CPSW (Ethernet)
            PGSW3RXINT0         = 41,    // CPSW (Ethernet)
            PGSW3TXINT0         = 42,    // CPSW (Ethernet)
            PGSW3MISC0          = 43,    // CPSW (Ethernet)
            UART3INT            = 44,    // UART3
            UART4INT            = 45,    // UART4
            UART5INT            = 46,    // UART5
            eCAP1INT            = 47,    // eCAP1 (PWM Subsystem)
            DCAN0_INT0          = 52,    // DCAN0
            DCAN0_INT1          = 53,    // DCAN0
            DCAN0_PARITY        = 54,    // DCAN0
            DCAN1_INT0          = 55,    // DCAN1
            DCAN1_INT1          = 56,    // DCAN1
            DCAN1_PARITY        = 57,    // DCAN1
            ePWM0_TZINT         = 58,    // eHRPWM0 TZ interrupt (PWM Subsystem)
            ePWM1_TZINT         = 59,    // eHRPWM1 TZ interrupt (PWM Subsystem)
            ePWM2_TZINT         = 60,    // eHRPWM2 TZ interrupt (PWM Subsystem)
            eCAP2INT            = 61,    // eCAP2 (PWM Subsystem)
            GPIOINT3A           = 62,    // GPIO3
            GPIOINT3B           = 63,    // GPIO3
            MMCSD0INT           = 64,    // MMCSD0
            SPI0INT             = 65,    // SPI0
            TINT0               = 66,    // DMTIMER0
            TINT1_1MS           = 67,    // DMTIMER_1ms
            TINT2               = 68,    // DMTIMER2
            TINT3               = 69,    // DMTIMER3
            I2C0INT             = 70,    // I2C0
            I2C1INT             = 71,    // I2C1
            UART0INT            = 72,    // UART0
            UART1INT            = 73,    // UART1
            UART2INT            = 74,    // UART2
            RTCINT              = 75,    // RTC
            RTCALARMINT         = 76,    // RTC
            MBINT0              = 77,    // Mailbox0 (mail_u0_irq)
            M3_TXEV             = 78,    // Wake M3 Subsystem
            eQEP0INT            = 79,    // eQEP0 (PWM Subsystem)
            MCATXINT0           = 80,    // McASP0
            MCARXINT0           = 81,    // McASP0
            MCATXINT1           = 82,    // McASP1
            MCARXINT1           = 83,    // McASP1
            ePWM0INT            = 86,    // eHRPWM0 (PWM Subsystem)
            ePWM1INT            = 87,    // eHRPWM1 (PWM Subsystem)
            eQEP1INT            = 88,    // eQEP1 (PWM Subsystem)
            eQEP2INT            = 89,    // eQEP2 (PWM Subsystem)
            DMA_INTR_PIN2       = 90,    // External DMA/Interrupt Pin2(xdma_event_intr2)
            WDT1INT             = 91,    // WDTIMER1
            TINT4               = 92,    // DMTIMER4
            TINT5               = 93,    // DMTIMER5
            TINT6               = 94,    // DMTIMER6
            TINT7               = 95,    // DMTIMER7
            GPIOINT0A           = 96,    // GPIO 0
            GPIOINT0B           = 97,    // GPIO 0
            GPIOINT1A           = 98,    // GPIO 1
            GPIOINT1B           = 99,    // GPIO 1
            GPMCINT             = 100,   // GPMC
            DDRERR0             = 101,   // EMIF
            AES0_IRQ_S          = 102,   // AES module 0 Interrupt secure side
            AES0_IRQ_P          = 103,   // AES module 0 Interrupt public side
            SHA_IRQ_S           = 108,   // SHA2 crypto-accelerator secure side
            SHA_IRQ_P           = 109,   // SHA2 crypto-accelerator public side 
            FPKA_SINTREQUEST_S  = 110,   // PKA
            RNG_IRQ             = 111,   // RNG
            TCERRINT0           = 112,   // TPTC0
            TCERRINT1           = 113,   // TPTC1
            TCERRINT2           = 114,   // TPTC2
            SMRFLX_Sabertooth   = 120,   // Smart Reflex 0
            SMRFLX_Core         = 121,   // Smart Reflex 1
            DMA_INTR_PIN0       = 123,   // External DMA/Interrupt Pin0 (xdma_event_intr0)
            DMA_INTR_PIN1       = 124,   // External DMA/Interrupt Pin1 (xdma_event_intr1)
            SPI1INT             = 125,   // SPI1
            INT_NUM_MAX         = 128       
        };
    
        constexpr         uint32_t  AM335x_INTC_BASE     = 0x48200000;
        constexpr AM335x_INTC_Type *AM335x_INTC          = ((AM335x_INTC_Type *) AM335x_INTC_BASE); 
        
        constexpr  uint8_t PRIORITY_THRESHOLD = 0xFF;
        constexpr uint32_t MAX_IRQ_PRIORITIES = 0x3F;
        
        constexpr uint8_t IRQFIQ_HIGHEST_PRIORITY = 0x00;
        constexpr uint8_t IRQFIQ_LOWEST_PRIORITY  = 0x7F;  // 127        
    
        constexpr uint32_t HOSTINT_ROUTE_IRQ = 0;  // To route an interrupt to IRQ    
        constexpr uint32_t HOSTINT_ROUTE_FIQ = 1;  // To route an interrupt to FIQ       
        
                uint32_t debug_dump_INTC(AM335x_INTC_Type &sINTC = *AM335x_INTC);
     
             ITR_reg_t*& get_ITR_reference(e_INT_ID int_id);
             MIR_reg_t*& get_MIR_reference(e_INT_ID int_id);
       MIR_CLEAR_reg_t*& get_MIR_CLEAR_reference(e_INT_ID int_id);
         MIR_SET_reg_t*& get_MIR_SET_reference(e_INT_ID int_id);            
         ISR_SET_reg_t*& get_ISR_SET_reference(e_INT_ID int_id);
       ISR_CLEAR_reg_t*& get_ISR_CLEAR_reference(e_INT_ID int_id);
     PENDING_IRQ_reg_t*& get_pending_IRQ_reference(e_INT_ID int_id);
     PENDING_FIQ_reg_t*& get_pending_FIQ_reference(e_INT_ID int_id);
        INTC_ILR_reg_t*& get_ILR_reference(e_INT_ID int_id);
        
        /* for testing purpose */
        inline uint32_t debug_dump_INTC(AM335x_INTC_Type &sINTC)
        {
            constexpr uint32_t COUNTOF_INTC = sizeof(AM335x_INTC_Type)/sizeof(uint32_t);
            volatile  uint32_t TSTREG[COUNTOF_INTC] = {0};          
            uint32_t  *pAM335x_INTC = (uint32_t *)&sINTC;
            volatile uint32_t SIZEOF_INTC = sizeof(AM335x_INTC_Type); 
            
            for(uint32_t i = 0 ; i < COUNTOF_INTC; i++)
            {   
                TSTREG[i] = pAM335x_INTC[i];
            }
            
            return SIZEOF_INTC;
        }
        
        inline ITR_reg_t*& get_ITR_reference(e_INT_ID int_id) 
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t ITR = (AM335x_INTC_BASE + 0x80 + (n * 0x20));
            return (ITR_reg_t*&)ITR;
        }
        
        inline MIR_reg_t*& get_MIR_reference(e_INT_ID int_id) 
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t MIR = (AM335x_INTC_BASE + 0x84 + (n * 0x20));
            return (MIR_reg_t*&)MIR;
        }
        
        inline MIR_CLEAR_reg_t*& get_MIR_CLEAR_reference(e_INT_ID int_id)
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t sMIR_CLEAR = (AM335x_INTC_BASE + 0x88 + (n * 0x20));
            return (MIR_CLEAR_reg_t*&)sMIR_CLEAR;
        }
        
        inline MIR_SET_reg_t*& get_MIR_SET_reference(e_INT_ID int_id)
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t sMIR_SET = (AM335x_INTC_BASE + 0x8c + (n * 0x20));
            return (MIR_SET_reg_t*&)sMIR_SET;
        }
        
        inline ISR_SET_reg_t*& get_ISR_SET_reference(e_INT_ID int_id) 
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t sISR_SET= (AM335x_INTC_BASE + 0x90 + (n * 0x20));
            return (ISR_SET_reg_t*&)sISR_SET;
        }
        
        inline ISR_CLEAR_reg_t*& get_ISR_CLEAR_reference(e_INT_ID int_id) 
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t sISR_CLEAR = (AM335x_INTC_BASE + 0x94 + (n * 0x20));
            return (ISR_CLEAR_reg_t*&)sISR_CLEAR;
        } 
          
        inline PENDING_IRQ_reg_t*& get_pending_IRQ_reference(e_INT_ID int_id) 
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t PENDING = (AM335x_INTC_BASE + 0x98 + (n * 0x20));
            return (PENDING_IRQ_reg_t*&)PENDING;
        }
        
        inline PENDING_FIQ_reg_t*& get_pending_FIQ_reference(e_INT_ID int_id) 
        {
            uint32_t n = ((uint32_t)int_id)/32;
            uint32_t PENDING = (AM335x_INTC_BASE + 0x9c + (n * 0x20));
            return (PENDING_FIQ_reg_t*&)PENDING;
        }
        
        inline INTC_ILR_reg_t*& get_ILR_reference(e_INT_ID int_id) 
        {
            uint32_t ILR = (AM335x_INTC_BASE + 0x100 + (((uint32_t)int_id) * 0x04));
            return (INTC_ILR_reg_t*&)ILR;
        }

    }   // namespace INTC

}   // namespace REGS



#endif //_INTC_H_