#ifndef _PRCM_H_
#define _PRCM_H_

#include <stdint.h>
#include "utils.h"
#include "DMTIMER.h"

namespace REGS
{  
    //This is power reset clock manager class and his namespace
    namespace PRCM
    { 
    /********************************************************************************************************************/  
    
    /*********************************************** AM335x_CM_PER_Type Registers **************************************/ 
        
    /********************************************************************************************************************/
       
       /* [reset state = 0xC0102]*/
        typedef union 
        { 
            struct 
            {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                       /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                   :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                :6;   // bit: 2..7     Reserved                
                uint32_t    CLKACTIVITY_L4LS_GCLK       :1;   // bit: 8        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]
                uint32_t                                :1;   // bit: 9        Reserved
                uint32_t    CLKACTIVITY_UART_GFCLK      :1;   // bit: 10       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_CAN_CLK         :1;   // bit: 11       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :1;   // bit: 12       Reserved
                uint32_t    CLKACTIVITY_TIMER7_GCLK     :1;   // bit: 13       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_TIMER2_GCLK     :1;   // bit: 14       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]   
                uint32_t    CLKACTIVITY_TIMER3_GCLK     :1;   // bit: 15       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_TIMER4_GCLK     :1;   // bit: 16       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]  
                uint32_t    CLKACTIVITY_LCDC_GCLK       :1;   // bit: 17       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :1;   // bit: 18       Reserved
                uint32_t    CLKACTIVITY_GPIO_1_GDBCLK   :1;   // bit: 19       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_GPIO_2_GDBCLK   :1;   // bit: 20       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_GPIO_3_GDBCLK   :1;   // bit: 21       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :2;   // bit: 22,23    Reserved
                uint32_t    CLKACTIVITY_I2C_FCLK        :1;   // bit: 24       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_SPI_GCLK        :1;   // bit: 25       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :1;   // bit: 26       Reserved
                uint32_t    CLKACTIVITY_TIMER5_GCLK     :1;   // bit: 27       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_TIMER6_GCLK     :1;   // bit: 28       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :3;   // bit: 29..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4LS_CLKSTCTRL_reg_t;
    
        enum e_PRCM_CLKTRCTRL : uint32_t
        {
            NO_SLEEP           = 0x0,
            SW_SLEEP           = 0x1,
            SW_WKUP            = 0x2,
            CLKTRCTRL_RESERVED = 0x3        
        };
    
        /* [reset state = 0xA]*/
        typedef union 
        { 
            struct 
            {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                       /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL            :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL]     
                uint32_t                         :1;   // bit: 2        Reserved            
                uint32_t    CLKACTIVITY_L3S_GCLK :1;   // bit: 3        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]     
                uint32_t                         :28;  // bit: 4..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } L3S_CLKSTCTRL_reg_t; 
    
        /* [reset state = 0x12]*/
        typedef union 
        { 
            struct 
            {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                       /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                 :2;   // bit: 0,1      (RW)Clock state transition[see e_PRCM_CLKTRCTRL]         
                uint32_t    CLKACTIVITY_EMIF_GCLK     :1;   // bit: 2        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t    CLKACTIVITY_MMC_FCLK      :1;   // bit: 3        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_L3_GCLK       :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                              :1;   // bit: 5        Reserved
                uint32_t    CLKACTIVITY_CPTS_RFT_GCLK :1;   // bit: 6        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_MCASP_GCLK    :1;   // bit: 7        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                              :24;  // bit: 8..31
            } b;                                      
            uint32_t  reg;                           
        } L3_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the CPSW clocks. */ 
                                             /* These bits is warm reset insensitively when CPSW RESET_ISO enabled */
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } CPGMAC0_CLKCTRL_reg_t;
    
        enum e_PRCM_MODULEMODE : uint32_t
        {
            MODULEMODE_DISABLED  = 0x0,     // Module is disable by SW. Any OCP access to module results in an error, except if resulting from a module wakeup(asynchronous wakeup).
            MODULEMODE_RESERVED  = 0x1,     // Reserved
            MODULEMODE_ENABLE    = 0x2,     // Module is explicitly enabled. Interface clock (if not used for functions) may be gated according to the clock domain state.
            MODULEMODE_RESERVED1 = 0x3      // Reserved       
        };
        
        enum e_PRCM_IDLEST : uint32_t
        {
            IDLEST_FUNC    = 0x0,   // Module is fully functional, including OCP
            IDLEST_TRANS   = 0x1,   // Module is performing transition: wakeup, or sleep, or sleep abortion
            IDLEST_IDLE    = 0x2,   // Module is in Idle mode (only OCP part). It is functional if using separate functional clock
            IDLEST_DISABLE = 0x3    // Module is disabled and cannot be accessed
        };
    
        enum e_PRCM_STBYST : uint32_t
        {
            STBYST_FUNC    = 0x0,
            STBYST_STNDBY  = 0x1      
        };
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the LCD clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } LCDC_CLKCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the USB clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } USB0_CLKCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TPTC clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TPTC0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the EMIF clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } EMIF_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the OCMC(on chip memmory controller) clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } OCMCRAM_CLKCTRL_reg_t;
    
        /* [reset state = 0x30002]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the GPMC clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GPMC_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MCASP0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MCASP0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the UART5 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } UART5_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MMC0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MMC0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the ELM clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } ELM_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the I2C2 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } I2C2_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the I2C1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } I2C1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the SPI0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } SPI0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the SPI1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } SPI1_CLKCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the L4LS clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4LS_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MCASP1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MCASP1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the UART1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } UART1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the UART2 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } UART2_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the UART3 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } UART3_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the UART4 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } UART4_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER7 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER7_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER2 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER2_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER3 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER3_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER4 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER4_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                                                /* This register manages the GPIO1 clocks. */ 
                uint32_t    MODULEMODE              :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t                            :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST                  :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    OPTFCLKEN_GPIO_1_GDBCLK :1;   // bit: 18         (RW)Optional functional clock control [0x0 = FCLK_DIS; 0x1 = FCLK_EN]
                uint32_t                            :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GPIO1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                                                /* This register manages the GPIO2 clocks. */ 
                uint32_t    MODULEMODE              :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t                            :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST                  :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    OPTFCLKEN_GPIO_2_GDBCLK :1;   // bit: 18         (RW)Optional functional clock control [0x0 = FCLK_DIS; 0x1 = FCLK_EN]
                uint32_t                            :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GPIO2_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                                                /* This register manages the GPIO3 clocks. */ 
                uint32_t    MODULEMODE              :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t                            :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST                  :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    OPTFCLKEN_GPIO_3_GDBCLK :1;   // bit: 18         (RW)Optional functional clock control [0x0 = FCLK_DIS; 0x1 = FCLK_EN]
                uint32_t                            :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GPIO3_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TPCC clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TPCC_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the DCAN0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } DCAN0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the DCAN1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } DCAN1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the PWMSS1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } EPWMSS1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the PWMSS0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } EPWMSS0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the PWMSS2 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[right_interpreter] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } EPWMSS2_CLKCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the L3 INSTR clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW,0x2)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } L3_INSTR_CLKCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the L3 Interconnect clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } L3_CLKCTRL_reg_t;
    
        /* [reset state = 0x70002]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the IEEE1500 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } IEEE5000_CLKCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the PRU-ICSS clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } PRU_ICSS_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER5 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER5_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER6 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER6_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MMC1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MMC1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MMC2 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MMC2_CLKCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TPTC1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TPTC1_CLKCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TPTC2 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TPTC2_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the SPINLOCK clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } SPINLOCK_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MAILBOX0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MAILBOX0_CLKCTRL_reg_t;
    
        /* [reset state = 0x7A]*/
        typedef union 
        { 
            struct 
            {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                  /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :1;   // bit: 2        Reserved        
                uint32_t    CLKACTIVITY_L4HS_GCLK           :1;   // bit: 3        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t    CLKACTIVITY_CPSW_250MHZ_GCLK    :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_CPSW_50MHZ_GCLK     :1;   // bit: 5        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_CPSW_5MHZ_GCLK      :1;   // bit: 6        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                    :25;  // bit: 7..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4HS_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the L4 Fast clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4HS_CLKCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                                   /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :2;   // bit: 2,3      Reserved        
                uint32_t    CLKACTIVITY_OCPWP_L3_GCLK       :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t    CLKACTIVITY_OCPWP_L4_GCLK       :1;   // bit: 5        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                    :26;  // bit: 6..31    Reserved 
            } b;                                      
            uint32_t  reg;                           
        } OCPWP_L3_CLKSTCTRL_reg_t;
    
    
        /* [reset state = 0x70002]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the OCPWP clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } OCPWP_CLKCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                                   /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :2;   // bit: 2,3      Reserved        
                uint32_t    CLKACTIVITY_PRU_ICSS_OCP_GCLK   :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t    CLKACTIVITY_PRU_ICSS_IEP_GCLK   :1;   // bit: 5        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_PRU_ICSS_UART_GCLK  :1;   // bit: 6        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                    :25;  // bit: 7..31    Reserved 
            } b;                                      
            uint32_t  reg;                           
        } PRUICSS_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                                   /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :2;   // bit: 2,3      Reserved        
                uint32_t    CLKACTIVITY_CPSW_125MHz_GCLK    :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t                                    :27;  // bit: 5..31    Reserved 
            } b;                                      
            uint32_t  reg;                           
        } CPSW_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                  /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :2;   // bit: 2,3      Reserved        
                uint32_t    CLKACTIVITY_LCDC_L3_OCP_GCLK    :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t    CLKACTIVITY_LCDC_L4_OCP_GCLK    :1;   // bit: 5        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                    :26;  // bit: 6..31    Reserved 
            } b;                                      
            uint32_t  reg;                           
        } LCDC_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the CLKDIV32K clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } CLKDIV32K_CLKCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                  /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :2;   // bit: 2,3      Reserved        
                uint32_t    CLKACTIVITY_CLK_24MHZ_GCLK      :1;   // bit: 4        (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]             
                uint32_t                                    :27;  // bit: 5..31    Reserved 
            } b;                                      
            uint32_t  reg;                           
        } CLKSTCTRL_24MHz_reg_t;
    
    /********************************************************************************************************************/  
    
    /*********************************************** AM335x_CM_WKUP_Type Registers **************************************/ 
        
    /********************************************************************************************************************/   
    
       /* [reset state = 0x6] */
        typedef union 
        { 
            struct 
            {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                       /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                   :2;   // bit: 0,1     (RW)Clock state transition [see e_PRCM_CLKTRCTRL]              
                uint32_t    CLKACTIVITY_L4_WKUP_GCLK    :1;   // bit: 2       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]
                uint32_t    CLKACTIVITY_SR_SYSCLK       :1;   // bit: 3       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_WDT1_GCLK       :1;   // bit: 4       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :3;   // bit: 5..7    Reserved
                uint32_t    CLKACTIVITY_GPIO0_GDBCLK    :1;   // bit: 8       (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :1;   // bit: 9       Reserved   
                uint32_t    CLKACTIVITY_TIMER0_GCLK     :1;   // bit: 10      (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_I2C0_GFCLK      :1;   // bit: 11      (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST]  
                uint32_t    CLKACTIVITY_UART0_GFCLK     :1;   // bit: 12      (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t    CLKACTIVITY_TIMER1_GCLK     :1;   // bit: 13      Reserved
                uint32_t    CLKACTIVITY_ADC_FCLK        :1;   // bit: 14      (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
                uint32_t                                :17;  // bit: 15..31  (R)state of the clock in domain [see e_PRCM_CLK_DOMAIN_ST] 
            } b;                                      
            uint32_t  reg;                           
        } CLKSTCTRL_reg_t;
    
        enum e_PRCM_CLK_DOMAIN_ST : uint32_t
        {
            CLK_INACT = 0x0,
            CLK_ACT   = 0x1
        };
    
        /* [reset state = 0x30000] */
        typedef union 
        { 
            struct 
            {                                /* This register manages the Control Module clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } CONTROL_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000] */
        typedef union 
        { 
            struct 
            {                                                /* This register manages the GPIO0 clocks. */ 
                uint32_t    MODULEMODE                 :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t                               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST                     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    OPTFCLKEN_GPIO0_GDBCLK     :1;   // bit: 18         (RW)Optional functional clock control.[0x0 = disabled; 0x1= enabled]
                uint32_t                               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GPIO0_CLKCTRL_reg_t;
    
        /* [reset state = 0x2] */
        typedef union 
        { 
            struct 
            {                                /* This register manages the L4WKUP clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (R)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4WKUP_CLKCTRL_reg_t;
    
        /* [reset state = 0x30002] */
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (R)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER0_CLKCTRL_reg_t;
    
        /* [reset state = 0x52580002] */
        typedef union 
        { 
            struct 
            {                                                /* This register manages the DEBUGSS clocks. */ 
                uint32_t    MODULEMODE                 :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t                               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST                     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST                     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t    OPTFCLKEN_DBGSYSCLK        :1;   // bit: 19         (RW)Optional functional clock control.[0x0 = disabled; 0x1= enabled]
                uint32_t    TRC_PMD_CLKSEL             :2;   // bit: 20,21         
                uint32_t    STM_PMD_CLKSEL             :2;   // bit: 22,23         
                uint32_t    TRC_PMD_CLKDIVSEL          :3;   // bit: 24..26         
                uint32_t    STM_PMD_CLKDIVSEL          :3;   // bit: 27..29         
                uint32_t    OPTCLK_DEBUG_CLKA          :1;   // bit: 30         (RW)Optional functional clock control.[0x0 = disabled.; 0x1= enabled.]
                uint32_t                               :1;   // bit: 31         Reserved
            } b;                                      
            uint32_t  reg;                           
        } DEBUGSS_CLKCTRL_reg_t;
    
        /* [reset state = 0x1A]*/
        typedef union 
        { 
            struct 
            {                                                 /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                              /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
                uint32_t    CLKTRCTRL                   :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL]               
                uint32_t    CLKACTIVITY_DBGSYSCLK       :1;   // bit: 2        (R)state of the Debugss clock in domain [0x0 = gated; 0x1= active]
                uint32_t    CLKACTIVITY_L3_AON_GCLK     :1;   // bit: 3        (R)state of the L3_AON clock in domain [0x0 = gated; 0x1= active] 
                uint32_t    CLKACTIVITY_DEBUG_CLKA      :1;   // bit: 4        (R)state of the Debugss CLKA clock in domain [0x0 = gated; 0x1= active] 
                uint32_t                                :27;  // bit: 5..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } L3_AON_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x1A]*/
        typedef union 
        { 
            struct 
            {                                                 /* This register provides automatic control over the DPLL activity. */
                uint32_t    AUTO_DPLL_MODE              :3;   // bit: 0..2      (RW)This feature is not supported.              
                uint32_t                                :29;  // bit: 3..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } AUTOIDLE_DPLL_MPU_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /* This register allows monitoring the master clock activity. This register is read only and automatically updated */
                uint32_t    DPLL              :1;   // bit: 0       (RW)DPLL clock activity [0x0 = in bypass or in stop mode; 0x1= locked]              
                uint32_t                      :7;   // bit: 1..7    Reserved
                uint32_t    ST_MN_BYPASS      :8;   // bit: 8       (RW)DPLL MN_BYPASS status [0x0 = not bypass; 0x1= bypass]            
                uint32_t                      :16;  // bit: 9..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } IDLEST_DPLL_MPU_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the DeltaMStep parameter for Spread Spectrum Clocking technique DeltaMStep is split Interconnect     */
                                                        /*  fractional and integer part.                                                                                */
                uint32_t    DELTAMSTEP_FRACTION :18;   // bit: 0..17    (RW)Fractional part for DeltaM coefficient              
                uint32_t    DELTAMSTEP_INTEGER  :2;    // bit: 18,19    (RW)Integer part for DeltaM coefficient  
                uint32_t                        :12;   // bit: 20..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_DELTAMSTEP_DPLL_MPU_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the Modulation Frequency (Fm) for Spread Spectrum Clocking technique by defining it as a ratio       */
                                                        /* of DPLL_REFCLK/4 Fm = [DPLL_REFCLK/4]/MODFREQDIV MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT    */
                uint32_t    MODFREQDIV_MANTISSA :7;    // bit: 0..6     (RW)Set the Mantissa component of MODFREQDIV factor 
                uint32_t                        :1;    // bit: 7        Reserved              
                uint32_t    MODFREQDIV_EXPONENT :3;    // bit: 8..10    (RW)Set the Exponent component of MODFREQDIV factor  
                uint32_t                        :21;   // bit: 11..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_MODFREQDIV_DPLL_MPU_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the DPLL.      */
                uint32_t    DPLL_DIV            :7;     // bit: 0..6     DPLL divider factor (0 to 127) (equal to input N of DPLL actual division factor is N+1). 
                uint32_t                        :1;     // bit: 7        Reserved              
                uint32_t    DPLL_MULT           :11;    // bit: 8..18    DPLL multiplier factor (2 to 2047). [0x0 = 0 reserved; 0x1= 1 reserved] 
                uint32_t                        :4;     // bit: 19..22   Reserved  
                uint32_t    DPLL_BYP_CLKSEL     :1;     // bit: 23       [ 0x0 = Selects CLKINP Clock as BYPASS Clock; 0x1 = Selects CLKINPULOW as Bypass Clock ]
                uint32_t                        :8;     // bit: 24..31   Reserved 
            } b;                                      
            uint32_t  reg;                           
        } CLKSEL_DPLL_MPU_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides automatic control over the DPLL activity.       */
                uint32_t    AUTO_DPLL_MODE      :3;     // bit: 0..2     AUTO_DPLL_MODE is not supported. 
                uint32_t                        :29;    // bit: 3..31    Reserved              
            } b;                                      
            uint32_t  reg;                           
        } AUTOIDLE_DPLL_DDR_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /*This register allows monitoring the master clock activity. This register is read only and automatically updated */
                uint32_t    ST_DPLL_CLK      :1;     // bit: 0          DPLL clock activity [0x0 = in bypass or in stop mode; 0x1 = locked ] 
                uint32_t                     :7;     // bit: 1..7       Reserved 
                uint32_t    ST_MN_BYPASS     :1;     // bit: 8          DPLL MN_BYPASS status [0x0 = not in bypass; 0x1 = bypass ] 
                uint32_t                     :23;    // bit: 9..31      Reserved             
            } b;                                      
            uint32_t  reg;                           
        } IDLEST_DPLL_DDR_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the DeltaMStep parameter for Spread Spectrum Clocking technique DeltaMStep is split Interconnect     */
                                                        /*  fractional and integer part.                                                                                */
                uint32_t    DELTAMSTEP_FRACTION :18;   // bit: 0..17    Fractional part for DeltaM coefficient              
                uint32_t    DELTAMSTEP_INTEGER  :2;    // bit: 18,19    Integer part for DeltaM coefficient  
                uint32_t                        :12;   // bit: 20..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_DELTAMSTEP_DPLL_DDR_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the Modulation Frequency (Fm) for Spread Spectrum Clocking technique by defining it as a ratio       */
                                                        /* of DPLL_REFCLK/4 Fm = [DPLL_REFCLK/4]/MODFREQDIV MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT    */
                uint32_t    MODFREQDIV_MANTISSA :7;    // bit: 0..6     Set the Mantissa component of MODFREQDIV factor 
                uint32_t                        :1;    // bit: 7        Reserved              
                uint32_t    MODFREQDIV_EXPONENT :3;    // bit: 8..10    Set the Exponent component of MODFREQDIV factor  
                uint32_t                        :21;   // bit: 11..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_MODFREQDIV_DPLL_DDR_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the DPLL.      */
                uint32_t    DPLL_DIV            :7;     // bit: 0..6     DPLL divider factor (0 to 127) (equal to input N of DPLL actual division factor is N+1). 
                uint32_t                        :1;     // bit: 7        Reserved              
                uint32_t    DPLL_MULT           :11;    // bit: 8..18    DPLL multiplier factor (2 to 2047). [0x0 = 0 reserved; 0x1= 1 reserved] 
                uint32_t                        :4;     // bit: 19..22   Reserved  
                uint32_t    DPLL_BYP_CLKSEL     :1;     // bit: 23       [ 0x0 = Selects CLKINP Clock as BYPASS Clock; 0x1 = Selects CLKINPULOW as Bypass Clock ]
                uint32_t                        :8;     // bit: 24..31   Reserved 
            } b;                                      
            uint32_t  reg;                           
        } CLKSEL_DPLL_DDR_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides automatic control over the DPLL activity.       */
                uint32_t    AUTO_DPLL_MODE      :3;     // bit: 0..2     AUTO_DPLL_MODE is not supported. 
                uint32_t                        :29;    // bit: 3..31    Reserved              
            } b;                                      
            uint32_t  reg;                           
        } AUTOIDLE_DPLL_DISP_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /*This register allows monitoring the master clock activity. This register is read only and automatically updated */
                uint32_t    ST_DPLL_CLK      :1;     // bit: 0          DPLL clock activity [0x0 = in bypass or in stop mode; 0x1 = locked ] 
                uint32_t                     :7;     // bit: 1..7       Reserved 
                uint32_t    ST_MN_BYPASS     :1;     // bit: 8          DPLL MN_BYPASS status [0x0 = not in bypass; 0x1 = bypass ] 
                uint32_t                     :23;    // bit: 9..31      Reserved             
            } b;                                      
            uint32_t  reg;                           
        } IDLEST_DPLL_DISP_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the DeltaMStep parameter for Spread Spectrum Clocking technique DeltaMStep is split Interconnect     */
                                                        /*  fractional and integer part.                                                                                */
                uint32_t    DELTAMSTEP_FRACTION :18;   // bit: 0..17    (RW)Fractional part for DeltaM coefficient              
                uint32_t    DELTAMSTEP_INTEGER  :2;    // bit: 18,19    (RW)Integer part for DeltaM coefficient  
                uint32_t                        :12;   // bit: 20..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_DELTAMSTEP_DPLL_DISP_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the Modulation Frequency (Fm) for Spread Spectrum Clocking technique by defining it as a ratio       */
                                                        /* of DPLL_REFCLK/4 Fm = [DPLL_REFCLK/4]/MODFREQDIV MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT    */
                uint32_t    MODFREQDIV_MANTISSA :7;    // bit: 0..6     (RW)Set the Mantissa component of MODFREQDIV factor 
                uint32_t                        :1;    // bit: 7        Reserved              
                uint32_t    MODFREQDIV_EXPONENT :3;    // bit: 8..10    (RW)Set the Exponent component of MODFREQDIV factor  
                uint32_t                        :21;   // bit: 11..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_MODFREQDIV_DPLL_DISP_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the DPLL.      */
                uint32_t    DPLL_DIV            :7;     // bit: 0..6     (RW)DPLL divider factor (0 to 127) (equal to input N of DPLL actual division factor is N+1). 
                uint32_t                        :1;     // bit: 7        Reserved              
                uint32_t    DPLL_MULT           :11;    // bit: 8..18    (RW)DPLL multiplier factor (2 to 2047). [0x0 = 0 reserved; 0x1= 1 reserved] 
                uint32_t                        :4;     // bit: 19..22   Reserved  
                uint32_t    DPLL_BYP_CLKSEL     :1;     // bit: 23       (RW)SSC_MODFREQDIV_DPLL_DISP_reg_t[ 0x0 = Selects CLKINP Clock as BYPASS Clock; 0x1 = Selects CLKINPULOW as Bypass Clock ]
                uint32_t                        :8;     // bit: 24..31   Reserved 
            } b;                                      
            uint32_t  reg;                           
        } CLKSEL_DPLL_DISP_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides automatic control over the DPLL activity.       */
                uint32_t    AUTO_DPLL_MODE      :3;     // bit: 0..2     AUTO_DPLL_MODE is not supported. 
                uint32_t                        :29;    // bit: 3..31    Reserved              
            } b;                                      
            uint32_t  reg;                           
        } AUTOIDLE_DPLL_CORE_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                        /*This register allows monitoring the master clock activity. This register is read only and automatically updated */
                uint32_t    ST_DPLL_CLK      :1;     // bit: 0          DPLL clock activity [0x0 = in bypass or in stop mode; 0x1 = locked ] 
                uint32_t                     :7;     // bit: 1..7       Reserved 
                uint32_t    ST_MN_BYPASS     :1;     // bit: 8          DPLL MN_BYPASS status [0x0 = not in bypass; 0x1 = bypass ] 
                uint32_t                     :23;    // bit: 9..31      Reserved             
            } b;                                      
            uint32_t  reg;                           
        } IDLEST_DPLL_CORE_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the DeltaMStep parameter for Spread Spectrum Clocking technique DeltaMStep is split Interconnect     */
                                                        /*  fractional and integer part.                                                                                */
                uint32_t    DELTAMSTEP_FRACTION :18;   // bit: 0..17    (RW)Fractional part for DeltaM coefficient              
                uint32_t    DELTAMSTEP_INTEGER  :2;    // bit: 18,19    (RW)Integer part for DeltaM coefficient  
                uint32_t                        :12;   // bit: 20..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_DELTAMSTEP_DPLL_CORE_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the Modulation Frequency (Fm) for Spread Spectrum Clocking technique by defining it as a ratio       */
                                                        /* of DPLL_REFCLK/4 Fm = [DPLL_REFCLK/4]/MODFREQDIV MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT    */
                uint32_t    MODFREQDIV_MANTISSA :7;    // bit: 0..6     (RW)Set the Mantissa component of MODFREQDIV factor 
                uint32_t                        :1;    // bit: 7        Reserved              
                uint32_t    MODFREQDIV_EXPONENT :3;    // bit: 8..10    (RW)Set the Exponent component of MODFREQDIV factor  
                uint32_t                        :21;   // bit: 11..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_MODFREQDIV_DPLL_CORE_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the DPLL.      */
                uint32_t    DPLL_DIV            :7;     // bit: 0..6     (RW)DPLL divider factor (0 to 127) (equal to input N of DPLL actual division factor is N+1). 
                uint32_t                        :1;     // bit: 7        Reserved              
                uint32_t    DPLL_MULT           :11;    // bit: 8..18    (RW)DPLL multiplier factor (2 to 2047). [0x0 = 0 reserved; 0x1= 1 reserved] 
                uint32_t                        :13;    // bit: 19..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } CLKSEL_DPLL_CORE_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides automatic control over the DPLL activity.       */
                uint32_t    AUTO_DPLL_MODE      :3;     // bit: 0..2     AUTO_DPLL_MODE is not supported. 
                uint32_t                        :29;    // bit: 3..31    Reserved              
            } b;                                      
            uint32_t  reg;                           
        } AUTOIDLE_DPLL_PER_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /*This register allows monitoring the master clock activity. This register is read only and automatically updated */
                uint32_t    ST_DPLL_CLK      :1;     // bit: 0          DPLL clock activity [0x0 = in bypass or in stop mode; 0x1 = locked ] 
                uint32_t                     :7;     // bit: 1..7       Reserved 
                uint32_t    ST_MN_BYPASS     :1;     // bit: 8          DPLL MN_BYPASS status [0x0 = not in bypass; 0x1 = bypass ] 
                uint32_t                     :23;    // bit: 9..31      Reserved             
            } b;                                      
            uint32_t  reg;                           
        } IDLEST_DPLL_PER_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the DeltaMStep parameter for Spread Spectrum Clocking technique DeltaMStep is split Interconnect     */
                                                        /*  fractional and integer part.                                                                                */
                uint32_t    DELTAMSTEP_FRACTION :18;   // bit: 0..17    (RW)Fractional part for DeltaM coefficient              
                uint32_t    DELTAMSTEP_INTEGER  :2;    // bit: 18,19    (RW)Integer part for DeltaM coefficient  
                uint32_t                        :12;   // bit: 20..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_DELTAMSTEP_DPLL_PER_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* Control the Modulation Frequency (Fm) for Spread Spectrum Clocking technique by defining it as a ratio       */
                                                        /* of DPLL_REFCLK/4 Fm = [DPLL_REFCLK/4]/MODFREQDIV MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT    */
                uint32_t    MODFREQDIV_MANTISSA :7;    // bit: 0..6     (RW)Set the Mantissa component of MODFREQDIV factor 
                uint32_t                        :1;    // bit: 7        Reserved              
                uint32_t    MODFREQDIV_EXPONENT :3;    // bit: 8..10    (RW)Set the Exponent component of MODFREQDIV factor  
                uint32_t                        :21;   // bit: 11..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } SSC_MODFREQDIV_DPLL_PER_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the DPLL.      */
                uint32_t                              :8;     // bit: 0..7     Reserved
                uint32_t    DPLL_CLKDCOLDO_GATE_CTRL  :1;     // bit: 8        (RW) Control gating of DPLL CLKDCOLDO [0x0 = Automatically gate;0x1 = Force this clock]             
                uint32_t    ST_DPLL_CLKDCOLDO         :1;     // bit: 9        (R) DPLL CLKDCOLDO status[0x0 = gated;0x1 = enabled]  
                uint32_t                              :2;     // bit: 10,11    Reserved 
                uint32_t    DPLL_CLKDCOLDO_PWDN       :1;     // bit: 12       (RW)Automatic power down for CLKDCOLDO o/p when it is gated [0x0 = keep powered;0x1 = powerdown] 
                uint32_t                              :19;    // bit: 13..31   Reserved 
            } b;                                      
            uint32_t  reg;                           
        } CLKDCOLDO_DPLL_PER_reg_t;
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the CLKOUT1 o/p of the HSDIVIDER.*/
                uint32_t    HSDIVIDER_CLKOUT1_DIV       :5;     // bit: 0..4     (RW)DPLL post-divider factor, M4, for internal clock generation.Divide values from 1 to 31. [0x0 = reserved]
                uint32_t    HSDIVIDER_CLKOUT1_DIVCHACK  :1;     // bit: 5        (R)indicates that the change in divider HSDIVIDER_CLKOUT1_DIV value has taken effect.           
                uint32_t                                :2;     // bit: 6,7      Reserved  
                uint32_t    HSDIVIDER_CLKOUT1_GATE_CTRL :1;     // bit: 8        (RW)Control gating of HSDIVIDER CLKOUT1 [0x0 = auto gated;0x1 = force enabled] 
                uint32_t    ST_HSDIVIDER_CLKOUT1        :1;     // bit: 9        (R)HSDIVIDER CLKOUT1 status  [0x0 = gated;0x1 = enabled]
                uint32_t                                :2;     // bit: 10,11    Reserved
                uint32_t    HSDIVIDER_CLKOUT1_PWDN      :1;     // bit: 12       Automatic power down for HSDIVIDER M4 divider and henceCLKOUT1 output when the o/p clock is gated [0x0 = keep powered;0x1 = powerdown] 
                uint32_t                                :19;    // bit: 13..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M4_DPLL_CORE_reg_t;
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                           /* This register provides controls over the CLKOUT1 o/p of the HSDIVIDER.*/
                uint32_t    HSDIVIDER_CLKOUT2_DIV       :5;     // bit: 0..4     (RW)DPLL post-divider factor, M5, for internal clock generation.Divide values from 1 to 31. [0x0 = reserved]
                uint32_t    HSDIVIDER_CLKOUT2_DIVCHACK  :1;     // bit: 5        (R)indicates that the change in divider HSDIVIDER_CLKOUT2_DIV value has taken effect.           
                uint32_t                                :2;     // bit: 6,7      Reserved  
                uint32_t    HSDIVIDER_CLKOUT2_GATE_CTRL :1;     // bit: 8        (RW)Control gating of HSDIVIDER CLKOUT2 [0x0 = auto gated;0x1 = force enabled] 
                uint32_t    ST_HSDIVIDER_CLKOUT2        :1;     // bit: 9        (R)HSDIVIDER CLKOUT2 status  [0x0 = gated;0x1 = enabled]
                uint32_t                                :2;     // bit: 10,11    Reserved
                uint32_t    HSDIVIDER_CLKOUT2_PWDN      :1;     // bit: 12       Automatic power down for HSDIVIDER M5 divider and henceCLKOUT2 output when the o/p clock is gated [0x0 = keep powered;0x1 = powerdown] 
                uint32_t                                :19;    // bit: 13..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M5_DPLL_CORE_reg_t;
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                          /* This register allows controlling the DPLL modes */
                uint32_t    DPLL_EN             :3;    // bit: 0..2     (RW) DPLL control.[see e_MPU_DPLL_EN]    
                uint32_t    DPLL_RAMP_LEVEL     :2;    // bit: 3,4      (RW) clock frequency ramping feature [variants:0x0;0x1;0x2;0x3]see datasheet and e_DPLL_RAMP_LEVEL                
                uint32_t    DPLL_RAMP_RATE      :3;    // bit: 5..7     (RW) selects the time in terms of DPLL REFCLKs spent at each stage of the clock ramping process. see e_DPLL_RAMP_RATE               
                uint32_t    DPLL_DRIFTGUARD_EN  :1;    // bit: 8        (RW) This bit allows to enable or disable the automatic recalibration feature of the DPLL. DRIFTGUARD feature [0x0 = disabled; 0x1 = enabled]            
                uint32_t    DPLL_RELOCK_RAMP_EN :1;    // bit: 9        (RW) If enabled, the clock ramping feature is used applied during the lock process, as well as the relock process            
                uint32_t    DPLL_LPMODE_EN      :1;    // bit: 10       (RW) Set the DPLL in Low Power mode.           
                uint32_t    DPLL_REGM4XEN       :1;    // bit: 11       (Retrun 0) Enable the REGM4XEN mode of the DPLL.              
                uint32_t    DPLL_SSC_EN         :1;    // bit: 12       (RW) Enable or disable Spread Spectrum Clocking [0x0 = SSC disabled; 0x1 = SSC enabled] 
                uint32_t    DPLL_SSC_ACK        :1;    // bit: 13       (R)  Acknowledgement from the DPLL regarding start and stop of Spread Spectrum Clocking feature  [0x0 = SSC turned off; 0x1 = SSC turned on]   
                uint32_t    DPLL_SSC_DOWNSPREAD :1;    // bit: 14       (RW) Control if only low frequency spread is required  [0x0 = spread on both sides of the programmed frequency; 0x1 = spread only on the lower side of the programmed frequency]           
                uint32_t    DPLL_SSC_TYPE       :1;    // bit: 15       (RW) Select Triangular Spread Spectrum clocking. [0x0 = is selected; 0x1 = Reserved]
                uint32_t                        :16;   // bit: 16..31   Reserved      
            } b;                                      
            uint32_t  reg;                           
        } CLKMODE_DPLL_MPU_reg_t;
    
        enum e_DPLL_EN: uint32_t 
        {
            DPLL_RESERVED1           = 0x0,
            DPLL_RESERVED2           = 0x1,
            DPLL_RESERVED3           = 0x2,
            DPLL_RESERVED4           = 0x3,
            DPLL_MNBYPASS            = 0x4,
            DPLL_IDLEBYPLOWPOWER     = 0x5,
            DPLL_IDLEBYPFASTRELOCK   = 0x6,
            DPLL_LOCKMODE            = 0x7
        };
    
        // see datasheet for more inforamtion
        enum e_DPLL_RAMP_LEVEL: uint32_t 
        {
            CLKOUT_NORAMPCLKOUTX2_NORAMP  = 0x0,
            CLKOUT_BYPASS_CLK_FOUT2_8     = 0x1,
            CLKOUT_BYPASS_CLK_FOUT1_5     = 0x2,
            RAMP_RESERVED                 = 0x3   
        };
    
        // see datasheet for more inforamtion
        enum e_DPLL_RAMP_RATE: uint32_t 
        {
            REFCLKx2     = 0x0,
            REFCLKx4     = 0x1,
            REFCLKx8     = 0x2,
            REFCLKx16    = 0x3,
            REFCLKx32    = 0x4,
            REFCLKx64    = 0x5,
            REFCLKx128   = 0x6,
            REFCLKx512   = 0x7
        };
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                          /* This register allows controlling the DPLL modes */
                uint32_t    DPLL_EN             :3;    // bit: 0..2     (RW) DPLL control.[see e_PER_DPLL_EN]    
                uint32_t                        :9;    // bit: 3..11    Reserved                
                uint32_t    DPLL_SSC_EN         :1;    // bit: 12       (RW) Enable or disable Spread Spectrum Clocking [0x0 = SSC disabled; 0x1 = SSC enabled]               
                uint32_t    DPLL_SSC_ACK        :1;    // bit: 13       (R)  Acknowledgement from the DPLL regarding start and stop of Spread Spectrum Clocking feature  [0x0 = SSC turned off; 0x1 = SSC turned on]            
                uint32_t    DPLL_SSC_DOWNSPREAD :1;    // bit: 14       (RW) Control if only low frequency spread is required  [0x0 = spread on both sides of the programmed frequency; 0x1 = spread only on the lower side of the programmed frequency]            
                uint32_t    DPLL_SSC_TYPE       :1;    // bit: 15       (RW) Select Triangular Spread Spectrum clocking. [0x0 = is selected; 0x1 = Reserved]          
                uint32_t                        :16;   // bit: 16..31   Reserved      
            } b;                                      
            uint32_t  reg;                           
        } CLKMODE_DPLL_PER_reg_t;
    
        enum e_PER_DPLL_EN: uint32_t 
        {
            PER_RESERVED1           = 0x0,
            PER_LOWPOWERSTOPMODE    = 0x1,
            PER_RESERVED2           = 0x2,
            PER_RESERVED3           = 0x3,
            PER_MNBYPASS            = 0x4,
            PER_IDLEBYPLOWPOWER     = 0x5,
            PER_PER_RESERVED6       = 0x6,
            PER_LOCKMODE            = 0x7
        };
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                          /* This register allows controlling the DPLL modes */
                uint32_t    DPLL_EN             :3;    // bit: 0..2     (RW) DPLL control.[see e_DPLL_EN]    
                uint32_t    DPLL_RAMP_LEVEL     :2;    // bit: 3,4      (RW) clock frequency ramping feature [variants:0x0;0x1;0x2;0x3]see datasheet and e_DPLL_RAMP_LEVEL                
                uint32_t    DPLL_RAMP_RATE      :3;    // bit: 5..7     (RW) selects the time in terms of DPLL REFCLKs spent at each stage of the clock ramping process. see e_DPLL_RAMP_RATE               
                uint32_t    DPLL_DRIFTGUARD_EN  :1;    // bit: 8        (RW) This bit allows to enable or disable the automatic recalibration feature of the DPLL. DRIFTGUARD feature [0x0 = disabled; 0x1 = enabled]            
                uint32_t    DPLL_RELOCK_RAMP_EN :1;    // bit: 9        (RW) If enabled, the clock ramping feature is used applied during the lock process, as well as the relock process            
                uint32_t    DPLL_LPMODE_EN      :1;    // bit: 10       (RW) Set the DPLL in Low Power mode.           
                uint32_t    DPLL_REGM4XEN       :1;    // bit: 11       (Retrun 0) Enable the REGM4XEN mode of the DPLL.              
                uint32_t    DPLL_SSC_EN         :1;    // bit: 12       (RW) Enable or disable Spread Spectrum Clocking [0x0 = SSC disabled; 0x1 = SSC enabled] 
                uint32_t    DPLL_SSC_ACK        :1;    // bit: 13       (R)  Acknowledgement from the DPLL regarding start and stop of Spread Spectrum Clocking feature  [0x0 = SSC turned off; 0x1 = SSC turned on]   
                uint32_t    DPLL_SSC_DOWNSPREAD :1;    // bit: 14       (RW) Control if only low frequency spread is required  [0x0 = spread on both sides of the programmed frequency; 0x1 = spread only on the lower side of the programmed frequency]           
                uint32_t    DPLL_SSC_TYPE       :1;    // bit: 15       (RW) Select Triangular Spread Spectrum clocking. [0x0 = is selected; 0x1 = Reserved]
                uint32_t                        :16;   // bit: 16..31   Reserved      
            } b;                                      
            uint32_t  reg;                           
        } CLKMODE_DPLL_CORE_reg_t;
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                          /* This register allows controlling the DPLL modes */
                uint32_t    DPLL_EN             :3;    // bit: 0..2     (RW) DPLL control.[see e_DPLL_EN]    
                uint32_t    DPLL_RAMP_LEVEL     :2;    // bit: 3,4      (RW) clock frequency ramping feature [variants:0x0;0x1;0x2;0x3]see datasheet and e_DPLL_RAMP_LEVEL                
                uint32_t    DPLL_RAMP_RATE      :3;    // bit: 5..7     (RW) selects the time in terms of DPLL REFCLKs spent at each stage of the clock ramping process. see e_DPLL_RAMP_RATE               
                uint32_t    DPLL_DRIFTGUARD_EN  :1;    // bit: 8        (RW) This bit allows to enable or disable the automatic recalibration feature of the DPLL. DRIFTGUARD feature [0x0 = disabled; 0x1 = enabled]            
                uint32_t    DPLL_RELOCK_RAMP_EN :1;    // bit: 9        (RW) If enabled, the clock ramping feature is used applied during the lock process, as well as the relock process            
                uint32_t    DPLL_LPMODE_EN      :1;    // bit: 10       (RW) Set the DPLL in Low Power mode.           
                uint32_t    DPLL_REGM4XEN       :1;    // bit: 11       (Retrun 0) Enable the REGM4XEN mode of the DPLL.              
                uint32_t    DPLL_SSC_EN         :1;    // bit: 12       (RW) Enable or disable Spread Spectrum Clocking [0x0 = SSC disabled; 0x1 = SSC enabled] 
                uint32_t    DPLL_SSC_ACK        :1;    // bit: 13       (R)  Acknowledgement from the DPLL regarding start and stop of Spread Spectrum Clocking feature  [0x0 = SSC turned off; 0x1 = SSC turned on]   
                uint32_t    DPLL_SSC_DOWNSPREAD :1;    // bit: 14       (RW) Control if only low frequency spread is required  [0x0 = spread on both sides of the programmed frequency; 0x1 = spread only on the lower side of the programmed frequency]           
                uint32_t    DPLL_SSC_TYPE       :1;    // bit: 15       (RW) Select Triangular Spread Spectrum clocking. [0x0 = is selected; 0x1 = Reserved]
                uint32_t                        :16;   // bit: 16..31   Reserved      
            } b;                                      
            uint32_t  reg;                           
        } CLKMODE_DPLL_DDR_reg_t;
    
        /* [reset state = 0x4] */
        typedef union 
        { 
            struct 
            {                                          /* This register allows controlling the DPLL modes */
                uint32_t    DPLL_EN             :3;    // bit: 0..2     (RW) DPLL control.[see e_DPLL_EN]    
                uint32_t    DPLL_RAMP_LEVEL     :2;    // bit: 3,4      (RW) clock frequency ramping feature [variants:0x0;0x1;0x2;0x3]see datasheet and e_DPLL_RAMP_LEVEL                
                uint32_t    DPLL_RAMP_RATE      :3;    // bit: 5..7     (RW) selects the time in terms of DPLL REFCLKs spent at each stage of the clock ramping process. see e_DPLL_RAMP_RATE               
                uint32_t    DPLL_DRIFTGUARD_EN  :1;    // bit: 8        (RW) This bit allows to enable or disable the automatic recalibration feature of the DPLL. DRIFTGUARD feature [0x0 = disabled; 0x1 = enabled]            
                uint32_t    DPLL_RELOCK_RAMP_EN :1;    // bit: 9        (RW) If enabled, the clock ramping feature is used applied during the lock process, as well as the relock process            
                uint32_t    DPLL_LPMODE_EN      :1;    // bit: 10       (RW) Set the DPLL in Low Power mode.           
                uint32_t    DPLL_REGM4XEN       :1;    // bit: 11       (Retrun 0) Enable the REGM4XEN mode of the DPLL.              
                uint32_t    DPLL_SSC_EN         :1;    // bit: 12       (RW) Enable or disable Spread Spectrum Clocking [0x0 = SSC disabled; 0x1 = SSC enabled] 
                uint32_t    DPLL_SSC_ACK        :1;    // bit: 13       (R)  Acknowledgement from the DPLL regarding start and stop of Spread Spectrum Clocking feature  [0x0 = SSC turned off; 0x1 = SSC turned on]   
                uint32_t    DPLL_SSC_DOWNSPREAD :1;    // bit: 14       (RW) Control if only low frequency spread is required  [0x0 = spread on both sides of the programmed frequency; 0x1 = spread only on the lower side of the programmed frequency]           
                uint32_t    DPLL_SSC_TYPE       :1;    // bit: 15       (RW) Select Triangular Spread Spectrum clocking. [0x0 = is selected; 0x1 = Reserved]
                uint32_t                        :16;   // bit: 16..31   Reserved      
            } b;                                      
            uint32_t  reg;                           
        } CLKMODE_DPLL_DISP_reg_t;
    
        /* [reset state = 0x0] */
        typedef union 
        { 
            struct 
            {                                          /* This register provides controls over the DPLL */
                uint32_t    DPLL_DIV            :8;    // bit: 0..7     (RW)DPLL divider factor (0 to 255)  
                uint32_t    DPLL_MULT           :12;   // bit: 8..19    (RW)DPLL multiplier factor (2 to 4095)[0x0,0x1 - reserved]..               
                uint32_t                        :4;    // bit: 20..23   Reserved              
                uint32_t    DPLL_SD_DIV         :8;    // bit: 24..31   (RW)Sigma-Delta divider select (2-255)[0x0,0x1 - reserved].                           
            } b;                                      
            uint32_t  reg;                           
        } CLKSEL_DPLL_PERIPH_reg_t;
    
        /* [reset state = 0x1] */
        typedef union 
        { 
            struct 
            {                                             /* This register provides controls over the M2 divider of the DPLL..*/
                uint32_t    DPLL_CLKOUT_DIV       :5;     // bit: 0..4     (RW)DPLL M2 post-divider factor (1 to 31). [0x0 = reserved]
                uint32_t    DPLL_CLKOUT_DIVCHACK  :1;     // bit: 5        (R)indicates that the change in divider DPLL_CLKOUT_DIV value has taken effect.           
                uint32_t                          :2;     // bit: 6,7      Reserved  
                uint32_t    DPLL_CLKOUT_GATE_CTRL :1;     // bit: 8        (RW)Control gating of DPLL CLKOUT [0x0 = auto gated;0x1 = force enabled] 
                uint32_t    ST_DPLL_CLKOUT        :1;     // bit: 9        (R)DPLL CLKOUT status  [0x0 = gated;0x1 = enabled]
                uint32_t                          :22;    // bit: 10..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M2_DPLL_DDR_reg_t;
    
        /* [reset state = 0x1] */
        typedef union 
        { 
            struct 
            {                                             /* This register provides controls over the M2 divider of the DPLL..*/
                uint32_t    DPLL_CLKOUT_DIV       :5;     // bit: 0..4     (RW)DPLL M2 post-divider factor (1 to 31). [0x0 = reserved]
                uint32_t    DPLL_CLKOUT_DIVCHACK  :1;     // bit: 5        (R)indicates that the change in divider DPLL_CLKOUT_DIV value has taken effect.           
                uint32_t                          :2;     // bit: 6,7      Reserved  
                uint32_t    DPLL_CLKOUT_GATE_CTRL :1;     // bit: 8        (RW)Control gating of DPLL CLKOUT [0x0 = auto gated;0x1 = force enabled] 
                uint32_t    ST_DPLL_CLKOUT        :1;     // bit: 9        (R)DPLL CLKOUT status  [0x0 = gated;0x1 = enabled]
                uint32_t                          :22;    // bit: 10..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M2_DPLL_DISP_reg_t;
    
        /* [reset state = 0x1] */
        typedef union 
        { 
            struct 
            {                                             /* This register provides controls over the M2 divider of the DPLL..*/
                uint32_t    DPLL_CLKOUT_DIV       :5;     // bit: 0..4     (RW)DPLL M2 post-divider factor (1 to 31). [0x0 = reserved]
                uint32_t    DPLL_CLKOUT_DIVCHACK  :1;     // bit: 5        (R)indicates that the change in divider DPLL_CLKOUT_DIV value has taken effect.           
                uint32_t                          :2;     // bit: 6,7      Reserved  
                uint32_t    DPLL_CLKOUT_GATE_CTRL :1;     // bit: 8        (RW)Control gating of DPLL CLKOUT [0x0 = auto gated;0x1 = force enabled] 
                uint32_t    ST_DPLL_CLKOUT        :1;     // bit: 9        (R)DPLL CLKOUT status  [0x0 = gated;0x1 = enabled]
                uint32_t                          :22;    // bit: 10..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M2_DPLL_MPU_reg_t;
    
        /* [reset state = 0x1] */
        typedef union 
        { 
            struct 
            {                                             /* This register provides controls over the M2 divider of the DPLL..*/
                uint32_t    DPLL_CLKOUT_DIV       :7;     // bit: 0..6     (RW)DPLL M2 post-divider factor (1 to 31). [0x0 = reserved]
                uint32_t    DPLL_CLKOUT_DIVCHACK  :1;     // bit: 7        (R)indicates that the change in divider DPLL_CLKOUT_DIV value has taken effect.           
                uint32_t    DPLL_CLKOUT_GATE_CTRL :1;     // bit: 8        (RW)Control gating of DPLL CLKOUT [0x0 = auto gated;0x1 = force enabled] 
                uint32_t    ST_DPLL_CLKOUT        :1;     // bit: 9        (R)DPLL CLKOUT status  [0x0 = gated;0x1 = enabled]
                uint32_t                          :22;    // bit: 10..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M2_DPLL_PER_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the WKUP M3 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :16;  // bit: 2..17      Reserved                    
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } WKUP_M3_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the UART0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } UART0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the I2C0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } I2C0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the ADC clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } ADC_TSC_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the SmartReflex0 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } SMARTREFLEX0_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the TIMER1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } TIMER1_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the SmartReflex1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } SMARTREFLEX1_CLKCTRL_reg_t;
    
        /* [reset state = 0x6]*/
        typedef union 
        { 
            struct 
            {                                                  /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                               /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL                    :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL]               
                uint32_t    CLKACTIVITY_L4_WKUP_AON_GCLK :1;   // bit: 2        (R)state of the clock in domain [0x0 = gated; 0x1= Act]     
                uint32_t                                 :29;  // bit: 3..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4_WKUP_AON_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x30002]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the SmartReflex1 clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } WDT1_CLKCTRL_reg_t;
    
        /* [reset state = 0x4]*/
        typedef union 
        { 
            struct 
            {                                                /* This register provides controls over the CLKOUT3 o/p of the HSDIVIDER. [warm reset insensitive] */ 
                uint32_t    HSDIVIDER_CLKOUT3_DIV       :5;  // bit: 0..4    (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t    HSDIVIDER_CLKOUT3_DIVCHACK  :1;  // bit: 5       (R)indicates that the change in divider HSDIVIDER_CLKOUT3_DIV value has taken effect 
                uint32_t                                :2;  // bit: 6,7     Reserved                    
                uint32_t    HSDIVIDER_CLKOUT3_GATE_CTRL :1;  // bit: 8       (RW)Control gating of HSDIVIDER CLKOUT3 [0x0 = autogate; 0x1 = force enabled;] 
                uint32_t    ST_HSDIVIDER_CLKOUT3        :1;  // bit: 9       (R)HSDIVIDER CLKOUT3 status [0x0 = gated; 0x1 = enabled;]
                uint32_t                                :2;  // bit: 10,11   Reserved 
                uint32_t    HSDIVIDER_CLKOUT3_PWDN      :1;  // bit: 12      (RW)Automatic power down for HSDIVIDER M6 divider [0x0 = Keep powered on; 0x1 = Automatically power down;]
                uint32_t                                :19; // bit: 13..31  Reserved
            } b;                                      
            uint32_t  reg;                           
        } DIV_M6_DPLL_CORE_reg_t;

    /********************************************************************************************************************/  
    
    /*********************************************** AM335x_CM_DPLL_Type Registers **************************************/ 
        
    /********************************************************************************************************************/    
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER7 clock [warm reset insensitive] */ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for TIMER7 clock[see e_TIMER_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER7_CLK_reg_t;
    
        enum e_TIMER_CLKSEL : uint32_t
        {
            TCLKIN          = 0x0,  // SEL1: Select TCLKIN clock
            CLK_M_OSC       = 0x1,  // SEL2: Select CLK_M_OSC clock
            CLK_32KHZ       = 0x2,  // SEL3: Select CLK_32KHZ clock
            CLKSEL_RESERVED = 0x3   // SEL4 : Reserved
        };
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER2 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for TIMER2 clock[see e_TIMER_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER2_CLK_reg_t;
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER3 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for TIMER3 clock[see e_TIMER_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER3_CLK_reg_t;
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER4 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for TIMER4 clock[see e_TIMER_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER4_CLK_reg_t;
    
        /* [reset state = 0x4]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the clock divide ration for MII clock [warm reset insensitive]*/ 
                uint32_t                :2;   // bit: 0,1       Reserved 
                uint32_t    MII_CLK_SEL :1;   // bit: 2         (RW)MII Clock Divider Selection.[0x0 = Selects 1/2 divider of SYSCLK2;0x1 = Selects 1/5 divide ratio of SYSCLK2] 
                uint32_t                :29;  // bit: 3..31     Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } MAC_CLKSEL_reg_t;
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER5 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for TIMER5 clock[see e_TIMER_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER5_CLK_reg_t;
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER6 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for TIMER6 clock[see e_TIMER_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER6_CLK_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for CPTS RFT clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :1;   // bit: 0,1        (RW)Selects the Mux select line for cpgmac rft clock [0x0 = Selects CORE_CLKOUTM5;0x1 = Selects CORE_CLKOUTM4] 
                uint32_t           :31;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } CPTS_RFT_CLKSEL_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for TIMER1 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :3;   // bit: 0..2       (RW)Selects the Mux select line for TIMER1 clock[see e_TIMER1MS_CLKSEL] 
                uint32_t           :29;  // bit: 3..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } TIMER1MS_CLK_reg_t;
    
        enum e_TIMER1MS_CLKSEL : uint32_t
        {
            MS1_M_OSC   = 0x0,      // Select CLK_M_OSC clock
            MS1_32KHZ   = 0x1,      // Select CLK_32KHZ clock
            MS1_TCLKIN  = 0x2,      // Select TCLKIN clock
            MS1_RC32K   = 0x3,      // Select CLK_RC32K clock
            MS1_32768HZ = 0x4       // Selects the CLK_32768 from 32KHz Crystal Osc
        };
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                         /* Selects the divider value for GFX clock [warm reset insensitive]*/ 
                uint32_t    CLKDIV_SEL_GFX_FCLK :1;   // bit: 0       (RW)Selects the divider value on gfx fclk  [0x0 = L3 Clock or 192MHz Clock; 0x1 =L3 clock/2 or 192Mhz/2]
                uint32_t    CLKSEL_GFX_FCLK     :1;   // bit: 1       (RW)Selects the clock on gfx fclk  [0x0 = from CORE PLL;0x1 = from PER PLL]
                uint32_t                        :30;  // bit: 2..31   Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } GFX_FCLK_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                            /* Controls the Mux select line for PRU-ICSS OCP clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :1;   // bit: 0,1        (RW)Controls Mux Select of PRU-ICSS OCP clock mux[0x0 = L3F clock as OCP;0x1 = DISP DPLL clock as OCP] 
                uint32_t           :31;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } PRU_ICSS_OCP_CLK_reg_t;
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Controls the Mux select line for LCDC PIXEL clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Controls the Mux Select of LCDC PIXEL clock[see e_LCDC_PIXEL_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } LCDC_PIXEL_CLK_reg_t;
    
        enum e_LCDC_PIXEL_CLKSEL : uint32_t
        {
            LCD_DISP_PLL_CLKOUTM2 = 0x0,
            LCD_CORE_PLL_CLKOUTM5 = 0x1,
            LCD_PER_PLL_CLKOUTM2  = 0x2,
            LCD_PLL_RESERVED      = 0x3
        };
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for Watchdog1 clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :1;   // bit: 0,1        (RW)Selects the Mux select line for WDT1 clock[0x0 = 32KHZ clock from RC Oscillator;0x1 = 32KHZ from 32K Clock divider] 
                uint32_t           :31;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } WDT1_CLK_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                            /* Selects the Mux select line for GPIO0 debounce clock [warm reset insensitive]*/ 
                uint32_t    CLKSEL :2;   // bit: 0,1        (RW)Selects the Mux select line for GPIO0 debounce clock[see e_GPIO0_CLKSEL] 
                uint32_t           :30;  // bit: 2..31      Reserved                    
            } b;                                      
            uint32_t  reg;                           
        } GPIO0_DBCLK_reg_t;
    
        enum e_GPIO0_CLKSEL : uint32_t
        {
            GPIO0_32KHZ_RC          = 0x0,  // Select 32KHZ clock from RC Oscillator
            GPIO0_32KHZ_CRYSTAL     = 0x1,  // Select 32KHZ from 32K Crystal Oscillator
            GPIO0_32KHZ_CLOCK_DIV   = 0x2,  // Select 32KHz from Clock Divider
        };

    /********************************************************************************************************************/  
    
    /*********************************************** AM335x_CM_MPU_Type Registers ***************************************/ 
        
    /********************************************************************************************************************/   
   
        /* [reset state = 0x6]*/
        typedef union 
        { 
            struct 
            {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                       /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL            :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL]               
                uint32_t    CLKACTIVITY_MPU_CLK  :1;   // bit: 2        (R)This field indicates the state of the MPU Clock [see e_PRCM_CLK_DOMAIN_ST]     
                uint32_t                         :28;  // bit: 3..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } MPU_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the CPSW clocks. */ 
                                             /* These bits is warm reset insensitively when CPSW RESET_ISO enabled */
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } MPU_CLKCTRL_reg_t;
    
    /********************************************************************************************************************/  
    
    /********************************************** AM335x_CM_DEVICE_Type Registers *************************************/ 
        
    /********************************************************************************************************************/   
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                   /* This register manages the CPSW clocks. */ 
                                                /* These bits is warm reset insensitively when CPSW RESET_ISO enabled */
                uint32_t    CLKOUT2SOURCE :3;   // bit: 0..2      (RW)This field selects the external output clock source. [see e_MPU_CLKOUT2SOURCE]
                uint32_t    CLKOUT2DIV    :3;   // bit: 3..5      (RW)THis field controls the external clock divison factor [see e_MPU_CLKOUT2DIV]                    
                uint32_t                  :1;   // bit: 6         Reserved
                uint32_t    CLKOUT2EN     :1;   // bit: 7         (RW)This bit controls the external clock activity [0x0 = SYS_CLKOUT2 is disabled; 0x1 = SYS_CLKOUT2 is enabled]
                uint32_t                  :24;  // bit: 19..31    Reserved
            } b;                                      
            uint32_t  reg;                           
        } CLKOUT_CTRL_reg_t;
    
        enum e_MPU_CLKOUT2DIV : uint32_t
        {
            MPU_SYS_CLKOUT2_1         = 0x0,
            MPU_SYS_CLKOUT2_2         = 0x1,
            MPU_SYS_CLKOUT2_3         = 0x2,
            MPU_SYS_CLKOUT2_4         = 0x3,
            MPU_SYS_CLKOUT2_5         = 0x4,
            MPU_SYS_CLKOUT2_6         = 0x5,
            MPU_SYS_CLKOUT2_7         = 0x6,
            MPU_RESERVED              = 0x7
        };
    
        enum e_MPU_CLKOUT2SOURCE : uint32_t
        {
            MPU_32KHz_OSCILLATOR_O_P  = 0x0,
            MPU_L3_CLOCK              = 0x1,
            MPU_DDR_PHY_CLOCK         = 0x2,
            MPU_192MHz_PER_PLL        = 0x3,
            MPU_LCD_PIXEL_CLOCK       = 0x4
        };
    
    /********************************************************************************************************************/  
    
    /********************************************** AM335x_CM_RTC_Type Registers ****************************************/ 
        
    /********************************************************************************************************************/   
      
        /* [reset state = 0x30002]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the RTC clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } RTC_CLKCTRL_reg_t;
    
        /* [reset state = 0x102]*/
        typedef union 
        { 
            struct 
            {                                              /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                           /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL                :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                             :6;   // bit: 2..7     Reserved              
                uint32_t    CLKACTIVITY_L4_RTC_GCLK  :1;   // bit: 8        (R)This field indicates the state of the L4 RTC clock in the domain. [0x0 = Inact; 0x1 = Act]  
                uint32_t    CLKACTIVITY_RTC_32KCLK   :1;   // bit: 9        (R)This field indicates the state of the 32K RTC clock in the domain [0x0 = Inact; 0x1 = Act]     
                uint32_t                             :22;  // bit: 10..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } RTC_CLKSTCTRL_reg_t;
 
    /********************************************************************************************************************/  
    
    /********************************************** AM335x_CM_GFX_Type Registers ****************************************/ 
        
    /********************************************************************************************************************/   
    
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                              /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                           /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL                :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                             :6;   // bit: 2..7     Reserved              
                uint32_t    CLKACTIVITY_GFX_L3_GCLK  :1;   // bit: 8        (R)This field indicates the state of the GFX_L3_GCLK clock in the domain.[0x0 = Inact; 0x1 = Act]  
                uint32_t    CLKACTIVITY_GFX_FCLK     :1;   // bit: 9        (R)This field indicates the state of the GFX_GCLK clock in the domain. [0x0 = Inact; 0x1 = Act]     
                uint32_t                             :22;  // bit: 10..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } GFX_L3_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x70000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the GFX clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[see e_PRCM_STBYST]
                uint32_t               :13;  // bit: 19..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GFX_CLKCTRL_reg_t;
    
    
        /* [reset state = 0x102]*/
        typedef union 
        { 
            struct 
            {                                              /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                           /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL                  :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                               :6;   // bit: 2..7     Reserved              
                uint32_t    CLKACTIVITY_L4LS_GFX_GCLK  :1;   // bit: 8        (R)This field indicates the state of the L4_LS clock in the domain.[0x0 = Inact; 0x1 = Act]     
                uint32_t                               :23;  // bit: 9..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } L4LS_GFX_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MMU CFG clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GFX_MMUCFG_CLKCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the MMU clocks. */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } GFX_MMUDATA_CLKCTRL_reg_t;

    /********************************************************************************************************************/  
    
    /********************************************* AM335x_CM_CEFUSE_Type Registers **************************************/ 
        
    /********************************************************************************************************************/    
         
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                                  /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
                uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition [see e_PRCM_CLKTRCTRL] 
                uint32_t                                    :6;   // bit: 2..7     Reserved              
                uint32_t    CLKACTIVITY_L4_CEFUSE_GICLK     :1;   // bit: 8        (R)This field indicates the state of the L4_CEFUSE_GCLK clock input of the domain.[0x0 = Inact; 0x1 = Act]  
                uint32_t    CLKACTIVITY_CUST_EFUSE_SYS_CLK  :1;   // bit: 9        (R)This field indicates the state of the Cust_Efuse_SYSCLK clock input of the domain.[0x0 = Inact; 0x1 = Act]     
                uint32_t                                    :22;  // bit: 10..31   Reserved
            } b;                                      
            uint32_t  reg;                           
        } CEFUSE_CLKSTCTRL_reg_t;
    
        /* [reset state = 0x30000]*/
        typedef union 
        { 
            struct 
            {                                /* This register manages the CEFUSE clocks */ 
                uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[see e_PRCM_MODULEMODE] 
                uint32_t               :14;  // bit: 2..15      Reserved                    
                uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[see e_PRCM_IDLEST] 
                uint32_t               :14;  // bit: 18..31     Reserved
            } b;                                      
            uint32_t  reg;                           
        } CEFUSE_CLKCTRL_reg_t;
    
    /********************************************************************************************************************/  
    
    /********************************************* AM335x_PRM_IRQ_Type Registers ****************************************/ 
        
    /********************************************************************************************************************/     
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                           /* This register contains the IP revision code for the PRCM */ 
                uint32_t    REV :8;     // bit: 0..7       (RW)IP revision [7:4] Major revision [3:0] Minor revision Examples: 0x10 for 1.0, 0x21 for 2.1                 
                uint32_t        :24;    // bit: 8..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } REVISION_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /* This register provides status on MPU interrupt events. */ 
                uint32_t                    :8;     // bit: 0..7    Reserved 
                uint32_t Transition_st      :1;     // bit: 8       (RW)Software supervised transition completed event interrupt status [0x0 = IRQ_fal : No interrupt; 0x1 = IRQ_tru : Interrupt is pending;]
                uint32_t                    :1;     // bit: 9       Reserved
                uint32_t ForceWkup_st       :1;     // bit: 10      (RW)Software supervised wakeup completed event interrupt status [0x0 = IRQ_fal : No interrupt; 0x1 = IRQ_tru : Interrupt is pending;] 
                uint32_t dpll_mpu_recal_st  :1;     // bit: 11      (RW)interrupt status for mpu dpll recaliberation  [0x0 = disable; 0x1 = enable;] 
                uint32_t dpll_core_recal_st :1;     // bit: 12      (RW)interrupt status for core dpll recaliberation [0x0 = disable; 0x1 = enable;] 
                uint32_t dpll_disp_recal_st :1;     // bit: 13      (RW)interrupt status for disp dpll recaliberation [0x0 = disable; 0x1 = enable;] 
                uint32_t dpll_ddr_recal_st  :1;     // bit: 14      (RW)interrupt status for ddr dpll recaliberation  [0x0 = disable; 0x1 = enable;]
                uint32_t dpll_per_recal_st  :1;     // bit: 15      (RW)interrupt status for usb dpll recaliberation  [0x0 = disable; 0x1 = enable;]               
                uint32_t                    :16;    // bit: 16..31  Reserved     
            } b;                                      
            uint32_t  reg;                           
        } IRQSTATUS_MPU_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /* This register is used to enable and disable events used to trigger MPU interrupt activation */ 
                uint32_t                    :8;     // bit: 0..7    Reserved 
                uint32_t Transition_en      :1;     // bit: 8       (RW)Software supervised transition completed event interrupt enable (anydomain) [0x0 = masked; 0x1 = enabled]
                uint32_t                    :1;     // bit: 9       Reserved
                uint32_t ForceWkup_en       :1;     // bit: 10      (RW)Software supervised Froce Wakeup completed event interruptenable [0x0 = masked; 0x1 = enabled] 
                uint32_t dpll_mpu_recal_en  :1;     // bit: 11      (RW)Interrupt enable for mpu dpll recaliberation  [0x0 = disable ; 0x1 = enable ;] 
                uint32_t dpll_core_recal_en :1;     // bit: 12      (RW)interrupt status for core dpll recaliberation [0x0 = disable ; 0x1 = enable ;] 
                uint32_t dpll_per_recal_en  :1;     // bit: 13      (RW)interrupt status for disp dpll recaliberation [0x0 = disable ; 0x1 = enable ;] 
                uint32_t dpll_ddr_recal_en  :1;     // bit: 14      (RW)interrupt status for ddr dpll recaliberation  [0x0 = disable ; 0x1 = enable ;]
                uint32_t dpll_disp_recal_en :1;     // bit: 15      (RW)interrupt status for usb dpll recaliberation  [0x0 = disable ; 0x1 = enable ;]               
                uint32_t                    :16;    // bit: 16..31  Reserved    
            } b;                                      
            uint32_t  reg;                           
        } IRQENABLE_MPU_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /* This register provides status on MPU interrupt events. */ 
                uint32_t                    :8;     // bit: 0..7    Reserved 
                uint32_t Transition_st      :1;     // bit: 8       (RW)Software supervised transition completed event interrupt status [0x0 = IRQ_fal : No interrupt; 0x1 = IRQ_tru : Interrupt is pending;]
                uint32_t                    :1;     // bit: 9       Reserved
                uint32_t ForceWkup_st       :1;     // bit: 10      (RW)Software supervised wakeup completed event interrupt status [0x0 = IRQ_fal : No interrupt; 0x1 = IRQ_tru : Interrupt is pending;] 
                uint32_t dpll_mpu_recal_st  :1;     // bit: 11      (RW)interrupt status for mpu dpll recaliberation  [0x0 = disable; 0x1 = enable;] 
                uint32_t dpll_core_recal_st :1;     // bit: 12      (RW)interrupt status for core dpll recaliberation [0x0 = disable; 0x1 = enable;] 
                uint32_t dpll_disp_recal_st :1;     // bit: 13      (RW)interrupt status for disp dpll recaliberation [0x0 = disable; 0x1 = enable;] 
                uint32_t dpll_ddr_recal_st  :1;     // bit: 14      (RW)interrupt status for ddr dpll recaliberation  [0x0 = disable; 0x1 = enable;]
                uint32_t dpll_per_recal_st  :1;     // bit: 15      (RW)interrupt status for usb dpll recaliberation  [0x0 = disable; 0x1 = enable;]               
                uint32_t                    :16;    // bit: 16..31  Reserved      
            } b;                                      
            uint32_t  reg;                           
        } IRQSTATUS_M3_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                       /* This register is used to enable and disable events used to trigger MPU interrupt activation. */ 
                uint32_t                    :8;     // bit: 0..7    Reserved 
                uint32_t Transition_en      :1;     // bit: 8       (RW)Software supervised transition completed event interrupt enable (anydomain) [0x0 = masked; 0x1 = enabled]
                uint32_t                    :1;     // bit: 9       Reserved
                uint32_t ForceWkup_en       :1;     // bit: 10      (RW)Software supervised Froce Wakeup completed event interruptenable [0x0 = masked; 0x1 = enabled] 
                uint32_t dpll_mpu_recal_en  :1;     // bit: 11      (RW)Interrupt enable for mpu dpll recaliberation  [0x0 = disable ; 0x1 = enable ;] 
                uint32_t dpll_core_recal_en :1;     // bit: 12      (RW)interrupt status for core dpll recaliberation [0x0 = disable ; 0x1 = enable ;] 
                uint32_t dpll_per_recal_en  :1;     // bit: 13      (RW)interrupt status for disp dpll recaliberation [0x0 = disable ; 0x1 = enable ;] 
                uint32_t dpll_ddr_recal_en  :1;     // bit: 14      (RW)interrupt status for ddr dpll recaliberation  [0x0 = disable ; 0x1 = enable ;]
                uint32_t dpll_disp_recal_en :1;     // bit: 15      (RW)interrupt status for usb dpll recaliberation  [0x0 = disable ; 0x1 = enable ;]               
                uint32_t                    :16;    // bit: 16..31  Reserved     
            } b;                                      
            uint32_t  reg;                           
        } IRQENABLE_M3_reg_t;
    
    /********************************************************************************************************************/  
    
    /********************************************* AM335x_PRM_PER_Type Registers ****************************************/ 
        
    /********************************************************************************************************************/   
        
        /* [reset state = 0x2]*/
        typedef union 
        { 
            struct 
            {                                    /* This register controls the release of the PER Domain resets. */ 
                uint32_t                  :1;    // bit: 0       Reserved
                uint32_t    PRU_ICSS_LRST :1;    // bit: 1       (RW)PER domain PRU-ICSS local reset control [0x0 = CLEAR; 0x1 = ASSERT]                 
                uint32_t                  :30;   // bit: 2..31   Reserved      
            } b;                                      
            uint32_t  reg;                           
        } PER_RSTCTRL_reg_t;
    
        /* [reset state = 0x1E60007]*/
        typedef union 
        { 
            struct 
            {                                            /* This register controls the release of the PER Domain resets. */ 
                uint32_t    PowerStateSt          :2;    // bit: 0,1     (R)Current Power State Status [see e_PWRSTST_MPU]
                uint32_t    LogicStateSt          :1;    // bit: 2       (R)Logic state status [0x0 = logic in domain OFF; 0x1 = logic in domain ON]                
                uint32_t                          :14;   // bit: 3..16   Reserved  
                uint32_t    PER_mem_statest       :2;    // bit: 17,18   (R)PER domain memory state status [see e_PWRSTST_MPU] 
                uint32_t                          :1;    // bit: 19      Reserved  
                uint32_t    InTransition          :1;    // bit: 20      (R)Domain transition status [0x0 = No on-going transition on power domain; 0x1 = Power domain transition is in progress] 
                uint32_t    ram_mem_statest       :2;    // bit: 21,22   (R)OCMC(on chip memmory controller) RAM memory state status [see e_PWRSTST_MPU] 
                uint32_t    pru_icss_mem_statest  :2;    // bit: 23,24   (R)PRU-ICSS memory state status [see e_PWRSTST_MPU]  
                uint32_t                          :7;    // bit: 25..31  Reserved 
            } b;                                      
            uint32_t  reg;                           
        } PER_PWRSTST_reg_t;
    
        enum e_PWRSTST_MPU : uint32_t
        {
            MEMORY_OFF          = 0x0,
            MEMORY_RETENTION    = 0x1,
            MEMORY_RESERVED     = 0x2,
            MEMORY_ON           = 0x3
        };
    
        /* [reset state = 0xEE0000EB]*/
        typedef union 
        { 
            struct 
            {                                            /* This register controls the release of the PER Domain resets. */ 
                uint32_t    PowerState            :2;    // bit: 0,1     (RW) PER domain power state control [see e_PWRSTST_PER]
                uint32_t                          :1;    // bit: 2       Reserved 
                uint32_t    LogicRETState         :1;    // bit: 3       (RW) Logic state when power domain is RETENTION [0x0 = logic_off; 0x1 = logic_ret] 
                uint32_t    LowPowerStateChange   :1;    // bit: 4       (RW) Power state change request when domain has already performed asleep transition [0x0 = Do not request; 0x1 = Req] 
                uint32_t    pru_icss_mem_ONState  :2;    // bit: 5,6     (RW) PRU-ICSS memory ON state [0x0..0x2 = Reserved; 0x3 = Memory is ON]
                uint32_t    pru_icss_mem_RETState :1;    // bit: 7       (RW) PRU-ICSS memory RET state [0x0 = off; 0x1 = ret]      
                uint32_t                          :17;   // bit: 8..24   Reserved  
                uint32_t    PER_mem_ONState       :2;    // bit: 25,26   (RW) Other memories in PER Domain ON state [0x0..0x2 = Reserved; 0x3 = Memory is ON]
                uint32_t    ram_mem_RETState      :1;    // bit: 27      (RW) OCMC(on chip memmory controller) RAM memory RET state [0x0 = off; 0x1 = ret]   
                uint32_t                          :1;    // bit: 28      Reserved  
                uint32_t    PER_mem_RETState      :1;    // bit: 29      (RW) Other memories in PER Domain RET state [0x0 = off; 0x1 = ret]  
                uint32_t    ram_mem_ONState       :2;    // bit: 30,31   (RW) OCMC(on chip memmory controller) RAM memory on state [see e_PWRSTST_PER]  
            } b;                                      
            uint32_t  reg;                           
        } PER_PWRSTCTRL_reg_t;
    
        enum e_PWRSTST_PER : uint32_t
        {
            PWR_OFF          = 0x0,
            PWR_RETENTION    = 0x1,
            PWR_RESERVED     = 0x2,
            PWR_ON           = 0x3
        };

    /********************************************************************************************************************/  
    
    /********************************************* AM335x_PRM_WKUP_Type Registers ***************************************/ 
        
    /********************************************************************************************************************/
    
        /* [reset state = 0x8]*/
        typedef union 
        { 
            struct 
            {                                   /* This register controls the release of the ALWAYS ON Domain resets. */ 
                uint32_t                 :3;    // bit: 0..2       Reserved
                uint32_t    WKUP_M3_LRST :1;    // bit: 3          (RW)Assert Reset to WKUP_M3 [0x0 = CLEAR; 0x1 = ASSERT]                
                uint32_t                 :28;   // bit: 4..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } WKUP_RSTCTRL_reg_t;
    
        /* [reset state = 0x8]*/
        typedef union 
        { 
            struct 
            {                                          /* Controls power state of WKUP power domain */ 
                uint32_t                        :3;    // bit: 0..2       Reserved
                uint32_t    LogicRETState       :1;    // bit: 3          (RW) Logic state when power domain is RETENTION [0x0 = logic off; 0x1 = logic_ret]   
                uint32_t    LowPowerStateChange :1;    // bit: 4          (RW) Power state change request when domain has already performed a sleep transition [0x0 = Do not request; 0x1 = Request a low power state change]               
                uint32_t                        :27;   // bit: 5..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } WKUP_PWRSTCTRL_reg_t;
    
        /* [reset state = 0x60004]*/
        typedef union 
        { 
            struct 
            {                                          /* This register provides a status on the current WKUP power domain state. [warm reset insensitive] */ 
                uint32_t                        :2;    // bit: 0..1       Reserved
                uint32_t    LogicStateSt        :1;    // bit: 2          (RW) Logic state status [0x0 = Logic in domain is OFF; 0x1 = Logic in domain is ON]  
                uint32_t                        :14;   // bit: 3..16      Reserved 
                uint32_t    Debugss_mem_statest :2;    // bit: 17,18      (RW) WKUP domain memory state status [see e_WKUP_DOMAIN_MEM_STATE]               
                uint32_t                        :1;    // bit: 19          Reserved 
                uint32_t    InTransition        :1;    // bit: 20          (RW) Domain transition status [0x0 = No on-going transition; 0x1 = Power domain transition is in progress]
                uint32_t                        :11;   // bit: 21..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } WKUP_PWRSTST_reg_t;
    
        enum e_WKUP_DOMAIN_MEM_STATE : uint32_t
        {
            WKUP_MEMORY_IS_OFF   = 0x0,
            WKUP_DOMAIN_Reserved = 0x2,
            WKUP_MEMORY_IS_ON    = 0x3       
        };
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /*This register logs the different reset sources of the ALWON domain */ 
                uint32_t                        :5;    // bit: 0..4       Reserved
                uint32_t    WKUP_M3_LRST        :1;    // bit: 5          (RW) M3 Processor has been reset [0x0 = No reset; 0x1 = M3 Processor has been reset]  
                uint32_t    EMULATION_M3_RST    :1;    // bit: 6          (RW) M3 Processor has been reset due to emulation reset source e.g.assert reset command initiated by the icepick module [0x0 = No reset; 0x1 = M3 Processor has been reset] 
                uint32_t    ICECRUSHER_M3_RST   :1;    // bit: 7          (RW) M3 Processor has been reset due to M3 ICECRUSHER1 reset event [0x0 = No reset; 0x1 = M3 Processor has been reset]               
                uint32_t                        :24;   // bit: 8..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } WKUP_RSTST_reg_t;
    
    /********************************************************************************************************************/  
    
    /********************************************* AM335x_PRM_MPU_Type Registers ****************************************/ 
        
    /********************************************************************************************************************/    
        
        /* [reset state = 0x1FF0007]*/
        typedef union 
        { 
            struct 
            {                                            /* This register controls the MPU power state to reach upon mpu domain sleep transition */ 
                uint32_t    PowerState            :2;    // bit: 0,1     (RW) Power state control [see e_PWR_STATE_CTRL]
                uint32_t    LogicRETState         :1;    // bit: 2       (RW) Logic state when power domain is RETENTION [0x0 = logic_off; 0x1 = logic_ret]  
                uint32_t                          :1;    // bit: 3       Reserved 
                uint32_t    LowPowerStateChange   :1;    // bit: 4       (RW) Power state change request when domain has already performed a sleep transition [0x0 = Do not request; 0x1 = Request a low power state change]  
                uint32_t                          :11;   // bit: 5..15   Reserved 
                uint32_t    MPU_RAM_ONState       :2;    // bit: 16,17   (RW) Default power domain memory state when domain is ON [see e_PWR_CTRL_MEM_STATE] 
                uint32_t    MPU_L1_ONState        :2;    // bit: 18,19   (R) Default power domain memory state when domain is ON. 
                uint32_t    MPU_L2_ONState        :2;    // bit: 20,21   (R) Default power domain memory state when domain is ON.   
                uint32_t    mpu_l1_RETState       :1;    // bit: 22      Reserved  
                uint32_t    mpu_l2_RETState       :1;    // bit: 23      (RW) Default power domain memory(L1) retention state when power domain is in retention
                uint32_t    mpu_ram_RETState      :1;    // bit: 24      (RW) Default power domain memory(L2) retention state when power domain is in retention  
                uint32_t                          :7;    // bit: 25..31  (RW) Default power domain memory(ram) retention state when power domain is in retention 
            } b;                                      
            uint32_t  reg;                           
        } MPU_PWRSTCTRL_reg_t;
    
        enum e_PWR_STATE_CTRL : uint32_t
        {
            PWR_CTRL_OFF_STATE  = 0x0,
            PWR_CTRL_RET        = 0x1, 
            PWR_CTRL_RESERVED   = 0x2,
            PWR_CTRL_ON_STATE   = 0x3      
        };
    
        enum e_PWR_CTRL_MEM_STATE : uint32_t
        {
            PWR_CTRL_MEMORY_IS_OFF   = 0x0,
            PWR_CTRL_RESERVED2       = 0x2,
            PWR_CTRL_MEMORY_IS_ON    = 0x3       
        };
    
        /* [reset state = 0x157]*/
        typedef union 
        { 
            struct 
            {                                            /* This register provides a status on the current MPU power domain state0. [warm reset insensitive] */ 
                uint32_t    PowerStateSt          :2;    // bit: 0,1     (R) Current Power State Status [see e_PWR_STATE_STS]
                uint32_t    LogicStateSt          :1;    // bit: 2       (R) Logic state status [0x0 = logic_off; 0x1 = logic_on]  
                uint32_t                          :1;    // bit: 3       Reserved 
                uint32_t    MPU_RAM_StateSt       :2;    // bit: 5,4     (R) MPU_RAM memory state status [see e_PWR_STATE_MEM_STS]  
                uint32_t    MPU_L1_StateSt        :2;    // bit: 6,7     (R) MPU L1 memory state status [see e_PWR_STATE_MEM_STS] 
                uint32_t    MPU_L2_StateSt        :2;    // bit: 8,9     (R) MPU L2 memory state status [see e_PWR_STATE_MEM_STS] 
                uint32_t                          :10;   // bit: 10..19  Reserved
                uint32_t    InTransition          :1;    // bit: 20      (R) Domain transition status [0x0 = No on-going transition; 0x1 = transition is in progress.]  
                uint32_t                          :11;   // bit: 22      Reserved  
            } b;                                      
            uint32_t  reg;                           
        } MPU_PWRSTST_reg_t;
    
        enum e_PWR_STATE_STS : uint32_t
        {
            PWR_STS_OFF_STATE   = 0x0,
            PWR_STS_RET_STATE   = 0x1,
            PWR_STS_ON_STATE    = 0x3       
        };
    
        enum e_PWR_STATE_MEM_STS : uint32_t
        {
            PWR_STS_MEMORY_IS_OFF   = 0x0,
            PWR_STS_RESERVED        = 0x2,
            PWR_STS_MEMORY_IS_ON    = 0x3       
        };
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                          /* This register logs the different reset sources of the ALWON domain. Each bit is set upon release of the domain reset signal. */
                                                       /*  Must be cleared by software. [warm reset insensitive] */ 
                uint32_t                        :5;    // bit: 0..4       Reserved
                uint32_t    EMULATION_MPU_RST   :1;    // bit: 5          (RW) MPU Processor has been reset due to emulation reset source e.g. assert reset command initiated by the icepick module [0x0 = RESET_NO; 0x1 = RESET_YES] 
                uint32_t    ICECRUSHER_MPU_RST  :1;    // bit: 6          (RW) MPU Processor has been reset due to MPU ICECRUSHER1 resetevent [0x0 = RESET_NO; 0x1 = RESET_YES]               
                uint32_t                        :25;   // bit: 7..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } MPU_RSTST_reg_t;
    
    
    /********************************************************************************************************************/  
    
    /******************************************* AM335x_PRM_DEVICE_Type Registers ***************************************/ 
        
    /********************************************************************************************************************/ 
        
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                           /* Global software cold and warm reset control. This register is auto-cleared. Only write 1 is possible. A readreturns 0 only. */
                uint32_t    RST_GLOBAL_WARM_SW   :1;    // bit: 0          (W) Global WARM software reset control. [0x0 = Global COLD; 0x1 = Asserts a global COLD software reset.] 
                uint32_t    RST_GLOBAL_COLD_SW   :1;    // bit: 1          (W) Global COLD software reset control. [0x0 = Global warm software reset is cleared.; 0x1 = Asserts a global warm software reset.]                
                uint32_t                         :30;   // bit: 2..31      Reserved   
            } b;                                      
            uint32_t  reg;                           
        } PRM_RSTCTRL_reg_t;
    
        /* [reset state = 0x1006]*/
        typedef union 
        { 
            struct 
            {                                 /* Reset duration control. [warm reset insensitive] */
                uint32_t    RSTTIME1   :8;    // bit: 0..7      (RW) (Power domain) reset duration 2 (number of CLK_M_OSC clockcycles) 
                uint32_t    RSTTIME2   :5;    // bit: 8..12     (RW) (Global) reset duration 1 (number of CLK_M_OSC clock cycles)               
                uint32_t               :19;   // bit: 13..31    Reserved   
            } b;                                      
            uint32_t  reg;                           
        } PRM_RSTTIME_reg_t;
    
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                                            /* This register logs the global reset sources. Each bit is set upon release of the domain reset signal. Must  */
                                                         /* be cleared by software. [warm reset insensitive]                                                            */ 
                uint32_t    GLOBAL_COLD_RST       :1;    // bit: 0          (RW) Power-on (cold) reset event [warm reset insensitive] [0x0 = No power-on reset.; 0x1 = Power-on reset has occurred.]
                uint32_t    GLOBAL_WARM_SW_RS     :1;    // bit: 1          (RW) Global warm software reset event [warm reset insensitive] [0x0 = No global warm SW reset; 0x1 = Global warm SW reset has occurred.] 
                uint32_t                          :2;    // bit: 2,3        Reserved 
                uint32_t    WDT1_RST              :1;    // bit: 4          (RW) Watchdog1 timer reset event. [0x0 = No watchdog reset.; 0x1 = watchdog reset has occurred.]
                uint32_t    EXTERNAL_WARM_RST     :2;    // bit: 5          (RW) External warm reset event [warm reset insensitive] [0x0 = No global warm reset.; 0x1 = Global external warm reset has occurred.]
                uint32_t                          :3;    // bit: 6..8       Reserved
                uint32_t    ICEPICK_RST           :1;    // bit: 9          (RW) IcePick reset event. [0x0 = No ICEPICK reset.; 0x1 = IcePick reset has occurred.]
                uint32_t                          :22;   // bit: 10..31     Reserved        
            } b;                                      
            uint32_t  reg;                           
        } PRM_RSTST_reg_t;
    
        /* [reset state = 0x78000017]*/
        typedef union 
        { 
            struct 
            {                                            /* Common setup for SRAM LDO transition counters. Applies to all voltage domains. [warm reset insensitive]  */
                uint32_t    PCHARGECNT_VALUE      :6;    // bit: 0..5       (RW) Delay between de-assertion of standby_rta_ret_on and standby_rta_ret_good. Counting on system clock.Target is 600ns.
                uint32_t                          :2;    // bit: 6,7        Reserved  
                uint32_t    VSETUPCNT_VALUE       :8;    // bit: 8..15      (RW) SRAM LDO rampup time from retention to active mode.The duration is computed as 8 x NbCycles of system clock cycles.Target is 30us.
                uint32_t    SLPCNT_VALUE          :8;    // bit: 16..23     (RW) Delay between retention/off assertion of last SRAM bank and SRAMALLRET signal to LDO is driven high. Counting on system clock.Target is 2us.
                uint32_t    StartUp_Count         :8;    // bit: 24.31      (RW) Determines the start-up duration of SRAM and ABB LDO.The duration is computed as 16 x NbCycles of system clock cycles.Target is 50us.     
            } b;                                      
            uint32_t  reg;                           
        } PRM_SRAM_COUNT_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                            /* Setup of the SRAM LDO for CORE voltage domain. [warm reset insensitive] */
                uint32_t    DISABLE_RTA_EXPORT    :1;    // bit: 0     (RW) Control for HD memory RTA feature. [0x0 = RTA_ENABLED; 0x1 = RTA_DISABLED]
                uint32_t    ABBOFF_ACT_EXPORT     :1;    // bit: 1     (RW) Determines whether SRAMNWA is supplied by VDDS or VDDAR during active mode. [0x0 = SRAMNWA supplied with VDDS; 0x1 = SRAMNW_ACT_VDDASRAMNWA supplied with VDDAR]
                uint32_t    ABBOFF_SLEEP_EXPORT   :1;    // bit: 2     (RW) Determines whether SRAMNWA is supplied by VDDS or VDDAR during deep-sleep. [0x0 = SRAMNWA supplied with VDDS; 0x1 = SRAMNW_ACT_VDDASRAMNWA supplied with VDDAR]
                uint32_t    ENFUNC1_EXPORT        :1;    // bit: 3     (RW) ENFUNC1 input of SRAM LDO. [0x0 = Short_prot_disabled; 0x1 = Short_prot_enabled]
                uint32_t    ENFUNC2_EXPORT        :1;    // bit: 4     (RW) ENFUNC2 input of SRAM LDO. [0x0 = Ext_cap; 0x1 = No_ext_cap]
                uint32_t    ENFUNC3_EXPORT        :1;    // bit: 5     (RW) ENFUNC3 input of SRAM LDO. [0x0 = Sub_regul_disabled; 0x1 = Sub_regul_enabled]
                uint32_t    ENFUNC4               :1;    // bit: 6     (RW) ENFUNC4 input of SRAM LDO. [0x0 = Ext_clock; 0x1 = No_ext_clock]
                uint32_t    ENFUNC5               :1;    // bit: 7     (RW) ENFUNC5 input of SRAM LDO. [0x0 = One_step; 0x1 = Two_step]
                uint32_t    AIPOFF                :1;    // bit: 8     (RW) Override on AIPOFF input of SRAM LDO.  [0x0 = AIPOFF signal is not overriden; 0x1 = AIPOFF signal is overriden to '1'.]
                uint32_t                          :23;   // bit: 9..31 Reserved   
            } b;                                      
            uint32_t  reg;                           
        } PRM_LDO_SRAM_CORE_SETUP_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                            /* Setup of the SRAM LDO for CORE voltage domain. [warm reset insensitive] */
                uint32_t    RETMODE_ENABLE        :1;    // bit: 0      (RW) Control if the SRAM LDO retention mode is used or not. [0x0 = Disabled; 0x1 = Enabled]
                uint32_t                          :7;    // bit: 1..7   Reserve
                uint32_t    SRAMLDO_STATUS        :1;    // bit: 8      (R)  SRAMLDO status [0x0 = ACTIVE; 0x1 = RETENTION]
                uint32_t    SRAM_IN_TRANSITION    :1;    // bit: 9      (R)  Status indicating SRAM LDO state machine state. [0x0 = IDLE; 0x1 = IN_TRANSITION]
                uint32_t                          :22;   // bit: 10..31 Reserved   
            } b;                                      
            uint32_t  reg;                           
        } PRM_LDO_SRAM_CORE_CTRL_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                            /* Setup of the SRAM LDO for MPU voltage domain. [warm reset insensitive] */
                uint32_t    DISABLE_RTA_EXPORT    :1;    // bit: 0     (RW) Control for HD memory RTA feature. [0x0 = RTA_ENABLED; 0x1 = RTA_DISABLED]
                uint32_t    ABBOFF_ACT_EXPORT     :1;    // bit: 1     (RW) Determines whether SRAMNWA is supplied by VDDS or VDDAR during active mode. [0x0 = SRAMNWA supplied with VDDS; 0x1 = SRAMNW_ACT_VDDASRAMNWA supplied with VDDAR]
                uint32_t    ABBOFF_SLEEP_EXPORT   :1;    // bit: 2     (RW) Determines whether SRAMNWA is supplied by VDDS or VDDAR during deep-sleep. [0x0 = SRAMNWA supplied with VDDS; 0x1 = SRAMNW_ACT_VDDASRAMNWA supplied with VDDAR]
                uint32_t    ENFUNC1_EXPORT        :1;    // bit: 3     (RW) ENFUNC1 input of SRAM LDO. [0x0 = Short_prot_disabled; 0x1 = Short_prot_enabled]
                uint32_t    ENFUNC2_EXPORT        :1;    // bit: 4     (RW) ENFUNC2 input of SRAM LDO. [0x0 = Ext_cap; 0x1 = No_ext_cap]
                uint32_t    ENFUNC3_EXPORT        :1;    // bit: 5     (RW) ENFUNC3 input of SRAM LDO. [0x0 = Sub_regul_disabled; 0x1 = Sub_regul_enabled]
                uint32_t    ENFUNC4               :1;    // bit: 6     (RW) ENFUNC4 input of SRAM LDO. [0x0 = Ext_clock; 0x1 = No_ext_clock]
                uint32_t    ENFUNC5               :1;    // bit: 7     (RW) ENFUNC5 input of SRAM LDO. [0x0 = One_step; 0x1 = Two_step]
                uint32_t    AIPOFF                :1;    // bit: 8     (RW) Override on AIPOFF input of SRAM LDO.  [0x0 = AIPOFF signal is not overriden; 0x1 = AIPOFF signal is overriden to '1'.]
                uint32_t                          :23;   // bit: 9..31 Reserved   
            } b;                                      
            uint32_t  reg;                           
        } PRM_LDO_SRAM_MPU_SETUP_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                            /* Control and status of the SRAM LDO for MPU voltage domain. [warm reset insensitive] */
                uint32_t    RETMODE_ENABLE        :1;    // bit: 0      (RW) Control if the SRAM LDO retention mode is used or not. [0x0 = Disabled; 0x1 = Enabled]
                uint32_t                          :7;    // bit: 1..7   Reserve
                uint32_t    SRAMLDO_STATUS        :1;    // bit: 8      (R)  SRAMLDO status [0x0 = ACTIVE; 0x1 = RETENTION]
                uint32_t    SRAM_IN_TRANSITION    :1;    // bit: 9      (R)  Status indicating SRAM LDO state machine state. [0x0 = IDLE; 0x1 = IN_TRANSITION]
                uint32_t                          :22;   // bit: 10..31 Reserved   
            } b;                                      
            uint32_t  reg;                           
        } PRM_LDO_SRAM_MPU_CTRL_reg_t;
    
    
    /********************************************************************************************************************/  
    
    /******************************************* AM335x_PRM_RTC_Type Registers ******************************************/ 
        
    /********************************************************************************************************************/ 
        /* [reset state = 0x4]*/
        typedef union 
        { 
            struct 
            {                                            /* This register controls the RTC power state to reach upon mpu domain sleep transition */
                uint32_t                          :2;    // bit: 0,1    Reserve
                uint32_t    LogicRETState         :1;    // bit: 2      (RW) Logic state when power domain is RETENTION [0x0 = logic_off; 0x1 = logic_on]
                uint32_t                          :1;    // bit: 3      Reserve
                uint32_t    LowPowerStateChange   :1;    // bit: 4      (RW)  Power state change request when domain has already performed a sleep transition. [0x0 = Do not request; 0x1 = Request a low power state change]
                uint32_t                          :27;   // bit: 5..31 Reserved   
            } b;                                      
            uint32_t  reg;                           
        } RTC_PWRSTCTRL_reg_t;
    
        /* [reset state = 0x4]*/
        typedef union 
        { 
            struct 
            {                                            /* This register provides a status on the current RTC power domain state0. [warm reset insensitive] */
                uint32_t                          :2;    // bit: 0,1    Reserved
                uint32_t    LogicStateSt          :1;    // bit: 2      (R) Logic state status [0x0 = Logic in domain is OFF; 0x1 = Logic in domain is ON]
                uint32_t                          :17;   // bit: 3..19  Reserve
                uint32_t    InTransition          :1;    // bit: 20     (R)Domain transition status [ 0x0 = No on-going transition; 0x1 = transition is in progress.]
                uint32_t                          :11;   // bit: 5..31  Reserved   
            } b;                                      
            uint32_t  reg;                           
        } RTC_PWRSTST_reg_t;
    
    /********************************************************************************************************************/  
    
    /******************************************* AM335x_PRM_GFX_Type Registers ***************************************/ 
        
    /********************************************************************************************************************/   
        
        /* [reset state = 0x60044]*/
        typedef union 
        { 
            struct 
            {                                            /* This register controls the GFX power state to reach upon a domain sleep transition */ 
                uint32_t    PowerState            :2;    // bit: 0,1     (RW) Power state control [see e_PWR_STATE_CTRL]
                uint32_t    LogicRETState         :1;    // bit: 2       (RW) Logic state when power domain is RETENTION [0x0 = logic_off; 0x1 = logic_ret]  
                uint32_t                          :1;    // bit: 3       Reserved 
                uint32_t    LowPowerStateChange   :1;    // bit: 4       (RW) Power state change request when domain has already performed a sleep transition [0x0 = Do not request; 0x1 = Request a low power state change]  
                uint32_t                          :1;    // bit: 5       Reserved 
                uint32_t    GFX_MEM_RETState      :1;    // bit: 6       (RW) 
                uint32_t                          :10;   // bit: 7..16   Reserved
                uint32_t    GFX_MEM_ONState       :2;    // bit: 17,18   (R) GFX memory state when domain is ON.   
                uint32_t                          :13;   // bit: 19..31  Reserved  
            } b;                                      
            uint32_t  reg;                           
        } PM_GFX_PWRSTCTRL_reg_t;   
    
        enum e_GFX_POWER_STATE : uint32_t
        {
            GFX_OFF_STATE  = 0x0,
            GFX_RET        = 0x1, 
            GFX_RESERVED   = 0x2,
            GFX_ON_STATE   = 0x3      
        };
    
        /* [reset state = 0x1]*/
        typedef union 
        { 
            struct 
            {                              /* This register controls the release of the GFX Domain resets. */ 
                uint32_t    GFX_RST :1;    // bit: 0       (RW) GFX domain local reset control for (SGX 530) [0x0 = CLEAR; 0x1 = ASSERT]
                uint32_t            :31;   // bit: 1..31   Reserved
     
            } b;                                      
            uint32_t  reg;                           
        } RM_GFX_RSTCTRL_reg_t; 
    
        /* [reset state = 0x17]*/
        typedef union 
        { 
            struct 
            {                                            /* This register provides a status on the current GFX power domain state. [warm reset insensitive] */ 
                uint32_t    PowerStateSt          :2;    // bit: 0,1     (R)Current Power State Status [see e_GFX_PWRSTST]
                uint32_t    LogicStateSt          :1;    // bit: 2       (R)Logic state status [0x0 = logic in domain OFF; 0x1 = logic in domain ON]                
                uint32_t                          :1;    // bit: 3       Reserved  
                uint32_t    GFX_MEM_StateSt       :2;    // bit: 4,5     (R)GFX memory state status [see e_GFX_MEMSTST] 
                uint32_t                          :14;   // bit: 6..19   Reserved  
                uint32_t    InTransition          :1;    // bit: 20      (R)Domain transition status [0x0 = No on-going transition on power domain; 0x1 = Power domain transition is in progress] 
                uint32_t                          :11;   // bit: 21..31  Reserved
    
            } b;                                      
            uint32_t  reg;                           
        } PM_GFX_PWRSTST_reg_t;
    
        enum e_GFX_PWRSTST : uint32_t
        {
            GFX_PWRSTS_OFF          = 0x0,
            GFX_PWRSTS_RETENTION    = 0x1,
            GFX_PWRSTS_ON           = 0x3
        };
    
        enum e_GFX_MEMSTST : uint32_t
        {
            GFX_MEM_OFF          = 0x0,
            GFX_MEM_RESERVED     = 0x2,
            GFX_MEM_ON           = 0x3
        };
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                              /* This register logs the different reset sources of the GFX domain. */ 
                uint32_t    GFX_RST :1;    // bit: 0       (RW) GFX Domain Logic Reset [0x0 = RESET_NO; 0x1 = RESET_YES]
                uint32_t            :31;   // bit: 1..31   Reserved
     
            } b;                                      
            uint32_t  reg;                           
        } RM_GFX_RSTST_reg_t;  
    
    /********************************************************************************************************************/  
    
    /******************************************* AM335x_PRM_CEFUSE_Type Registers ***************************************/ 
        
    /********************************************************************************************************************/
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                            /* This register controls the CEFUSE power state to reach upon a domain sleep transition */ 
                uint32_t    PowerState            :2;    // bit: 0,1     (RW) Power state control [see e_CEFUSE_PWRSTATE_CTRL]
                uint32_t                          :2;    // bit: 2,3     Reserved 
                uint32_t    LowPowerStateChange   :1;    // bit: 4       (RW) Power state change request when domain has already performed a sleep transition [0x0 = Do not request; 0x1 = Request a low power state change]  
                uint32_t                          :27;   // bit: 5..31   Reserved  
            } b;                                      
            uint32_t  reg;                           
        } CEFUSE_PWRSTCTRL_reg_t;   
    
        enum e_CEFUSE_PWRSTATE_CTRL : uint32_t
        {
            CEFUSE_OFF_STATE  = 0x0,
            CEFUSE_RESERVED   = 0x1, 
            CEFUSE_INACTIVE   = 0x2,
            CEFUSE_ON_STATE   = 0x3      
        };
    
        /* [reset state = 0x7]*/
        typedef union 
        { 
            struct 
            {                                            /* This register provides a status on the current CEFUSE power domain state. [warm reset insensitive] */ 
                uint32_t    PowerStateSt          :2;    // bit: 0,1     (R)Current Power State Status [see e_CEFUSE_PWRSTST]
                uint32_t    LogicStateSt          :1;    // bit: 2       (R)Logic state status [0x0 = logic in domain OFF; 0x1 = logic in domain ON]                
                uint32_t                          :17;   // bit: 3..19   Reserved  
                uint32_t    InTransition          :1;    // bit: 20      (R)Domain transition status [0x0 = No on-going transition; 0x1 = transition is in progress.] 
                uint32_t                          :3;    // bit: 21..23  Reserved  
                uint32_t    LastPowerStateEntered :2;    // bit: 24,25   (RW)Last low power state entered.Set to 0x3 upon write of the same only.  [0x0 = OFF; 0x1 = ON] 
                uint32_t                          :6;    // bit: 26..31  Reserved
    
            } b;                                      
            uint32_t  reg;                           
        } CEFUSE_PWRSTST_reg_t;
    
        enum e_CEFUSE_PWRSTST : uint32_t
        {
            CEFUSE_STS_OFF_STATE  = 0x0,
            CEFUSE_STS_RETENTION  = 0x1, 
            CEFUSE_STS_INACTIVE   = 0x2,
            CEFUSE_STS_ON_STATE   = 0x3      
        };
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////    ALL PRCM MODULE REGISTERS BLOCKS   //////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
        struct AM335x_CM_PER_Type
        {                                                                                      
            __RW  L4LS_CLKSTCTRL_reg_t        L4LS_CLKSTCTRL;      // (0x00)  
            __RW  L3S_CLKSTCTRL_reg_t         L3S_CLKSTCTRL;       // (0x04) 
            __R   uint32_t                    RESERVED1[1]; 
            __RW  L3_CLKSTCTRL_reg_t          L3_CLKSTCTRL;        // (0x0C) 
            __R   uint32_t                    RESERVED2[1];  
            __RW  CPGMAC0_CLKCTRL_reg_t       CPGMAC0_CLKCTRL;     // (0x14)  
            __RW  LCDC_CLKCTRL_reg_t          LCDC_CLKCTRL;        // (0x18)  
            __RW  USB0_CLKCTRL_reg_t          USB0_CLKCTRL;        // (0x1C)
            __R   uint32_t                    RESERVED3[1];   
            __RW  TPTC0_CLKCTRL_reg_t         TPTC0_CLKCTRL;       // (0x24)  
            __RW  EMIF_CLKCTRL_reg_t          EMIF_CLKCTRL;        // (0x28)  
            __RW  OCMCRAM_CLKCTRL_reg_t       OCMCRAM_CLKCTRL;     // (0x2C)  
            __RW  GPMC_CLKCTRL_reg_t          GPMC_CLKCTRL;        // (0x30)  
            __RW  MCASP0_CLKCTRL_reg_t        MCASP0_CLKCTRL;      // (0x34)  
            __RW  UART5_CLKCTRL_reg_t         UART5_CLKCTRL;       // (0x38)  
            __RW  MMC0_CLKCTRL_reg_t          MMC0_CLKCTRL;        // (0x3C)  
            __RW  ELM_CLKCTRL_reg_t           ELM_CLKCTRL;         // (0x40)  
            __RW  I2C2_CLKCTRL_reg_t          I2C2_CLKCTRL;        // (0x44)  
            __RW  I2C1_CLKCTRL_reg_t          I2C1_CLKCTRL;        // (0x48)  
            __RW  SPI0_CLKCTRL_reg_t          SPI0_CLKCTRL;        // (0x4C) 
            __RW  SPI1_CLKCTRL_reg_t          SPI1_CLKCTRL;        // (0x50) 
            __R   uint32_t                    RESERVED4[3];  
            __RW  L4LS_CLKCTRL_reg_t          L4LS_CLKCTRL;        // (0x60)
            __R   uint32_t                    RESERVED5[1];   
            __RW  MCASP1_CLKCTRL_reg_t        MCASP1_CLKCTRL;      // (0x68)  
            __RW  UART1_CLKCTRL_reg_t         UART1_CLKCTRL;       // (0x6C)  
            __RW  UART2_CLKCTRL_reg_t         UART2_CLKCTRL;       // (0x70)  
            __RW  UART3_CLKCTRL_reg_t         UART3_CLKCTRL;       // (0x74)  
            __RW  UART4_CLKCTRL_reg_t         UART4_CLKCTRL;       // (0x78)  
            __RW  TIMER7_CLKCTRL_reg_t        TIMER7_CLKCTRL;      // (0x7C)  
            __RW  TIMER2_CLKCTRL_reg_t        TIMER2_CLKCTRL;      // (0x80)  
            __RW  TIMER3_CLKCTRL_reg_t        TIMER3_CLKCTRL;      // (0x84)  
            __RW  TIMER4_CLKCTRL_reg_t        TIMER4_CLKCTRL;      // (0x88)
            __R   uint32_t                    RESERVED6[8];   
            __RW  GPIO1_CLKCTRL_reg_t         GPIO1_CLKCTRL;       // (0xAC)  
            __RW  GPIO2_CLKCTRL_reg_t         GPIO2_CLKCTRL;       // (0xB0)  
            __RW  GPIO3_CLKCTRL_reg_t         GPIO3_CLKCTRL;       // (0xB4)
            __R   uint32_t                    RESERVED7[1];
            __RW  TPCC_CLKCTRL_reg_t          TPCC_CLKCTRL;        // (0xBC)  
            __RW  DCAN0_CLKCTRL_reg_t         DCAN0_CLKCTRL;       // (0xC0)  
            __RW  DCAN1_CLKCTRL_reg_t         DCAN1_CLKCTRL;       // (0xC4)
            __R   uint32_t                    RESERVED8[1];
            __RW  EPWMSS1_CLKCTRL_reg_t       EPWMSS1_CLKCTRL;     // (0xCC) 
            __R   uint32_t                    RESERVED9[1]; 
            __RW  EPWMSS0_CLKCTRL_reg_t       EPWMSS0_CLKCTRL;     // (0xD4)  
            __RW  EPWMSS2_CLKCTRL_reg_t       EPWMSS2_CLKCTRL;     // (0xD8)  
            __RW  L3_INSTR_CLKCTRL_reg_t      L3_INSTR_CLKCTRL;    // (0xDC)  
            __RW  L3_CLKCTRL_reg_t            L3_CLKCTRL;          // (0xE0) 
            __RW  IEEE5000_CLKCTRL_reg_t      IEEE5000_CLKCTRL;    // (0xE4)  
            __RW  PRU_ICSS_CLKCTRL_reg_t      PRU_ICSS_CLKCTRL;    // (0xE8)  
            __RW  TIMER5_CLKCTRL_reg_t        TIMER5_CLKCTRL;      // (0xEC)  
            __RW  TIMER6_CLKCTRL_reg_t        TIMER6_CLKCTRL;      // (0xF0)  
            __RW  MMC1_CLKCTRL_reg_t          MMC1_CLKCTRL;        // (0xF4)  
            __RW  MMC2_CLKCTRL_reg_t          MMC2_CLKCTRL;        // (0xF8) 
            __RW  TPTC1_CLKCTRL_reg_t         TPTC1_CLKCTRL;       // (0xFC)  
            __RW  TPTC2_CLKCTRL_reg_t         TPTC2_CLKCTRL;       // (0x100)  
            __R   uint32_t                    RESERVED10[2]; 
            __RW  SPINLOCK_CLKCTRL_reg_t      SPINLOCK_CLKCTRL;    // (0x10C)  
            __RW  MAILBOX0_CLKCTRL_reg_t      MAILBOX0_CLKCTRL;    // (0x110)
            __R   uint32_t                    RESERVED11[2];  
            __RW  L4HS_CLKSTCTRL_reg_t        L4HS_CLKSTCTRL;      // (0x11C)  
            __RW  L4HS_CLKCTRL_reg_t          L4HS_CLKCTRL;        // (0x120)
            __R   uint32_t                    RESERVED12[2];  
            __RW  OCPWP_L3_CLKSTCTRL_reg_t    OCPWP_L3_CLKSTCTRL;  // (0x12C) 
            __RW  OCPWP_CLKCTRL_reg_t         OCPWP_CLKCTRL;       // (0x130) 
            __R   uint32_t                    RESERVED13[3];  
            __RW  PRUICSS_CLKSTCTRL_reg_t     PRUICSS_CLKSTCTRL;   // (0x140)  
            __RW  CPSW_CLKSTCTRL_reg_t        CPSW_CLKSTCTRL;      // (0x144) 
            __RW  LCDC_CLKSTCTRL_reg_t        LCDC_CLKSTCTRL;      // (0x148)  
            __RW  CLKDIV32K_CLKCTRL_reg_t     CLKDIV32K_CLKCTRL;   // (0x14C) 
            __RW  CLKSTCTRL_24MHz_reg_t       CLKSTCTRL_24MHz;     // (0x150)                                                                                     
        }; 
    
        struct AM335x_CM_WKUP_Type 
        {                                                                                      
            __RW   CLKSTCTRL_reg_t                    CLKSTCTRL;                 // (0x00)  
            __RW   CONTROL_CLKCTRL_reg_t              CONTROL_CLKCTRL;           // (0x04) 
            __RW   GPIO0_CLKCTRL_reg_t                GPIO0_CLKCTRL;             // (0x08) 
            __RW   L4WKUP_CLKCTRL_reg_t               L4WKUP_CLKCTRL;            // (0x0C) 
            __RW   TIMER0_CLKCTRL_reg_t               TIMER0_CLKCTRL;            // (0x10) 
            __RW   DEBUGSS_CLKCTRL_reg_t              DEBUGSS_CLKCTRL;           // (0x14) 
            __RW   L3_AON_CLKSTCTRL_reg_t             L3_AON_CLKSTCTRL;          // (0x18) 
            __RW   AUTOIDLE_DPLL_MPU_reg_t            AUTOIDLE_DPLL_MPU;         // (0x1C)  //This feature is not supported!
            __R    IDLEST_DPLL_MPU_reg_t              IDLEST_DPLL_MPU;           // (0x20) 
            __RW   SSC_DELTAMSTEP_DPLL_MPU_reg_t      SSC_DELTAMSTEP_DPLL_MPU;   // (0x24) 
            __RW   SSC_MODFREQDIV_DPLL_MPU_reg_t      SSC_MODFREQDIV_DPLL_MPU;   // (0x28)  
            __RW   CLKSEL_DPLL_MPU_reg_t              CLKSEL_DPLL_MPU;           // (0x2C) 
            __RW   AUTOIDLE_DPLL_DDR_reg_t            AUTOIDLE_DPLL_DDR;         // (0x30)  //AUTO_DPLL_MODE is not supported!    
            __R    IDLEST_DPLL_DDR_reg_t              IDLEST_DPLL_DDR;           // (0x34) 
            __RW   SSC_DELTAMSTEP_DPLL_DDR_reg_t      SSC_DELTAMSTEP_DPLL_DDR;   // (0x38) 
            __RW   SSC_MODFREQDIV_DPLL_DDR_reg_t      SSC_MODFREQDIV_DPLL_DDR;   // (0x3C) 
            __RW   CLKSEL_DPLL_DDR_reg_t              CLKSEL_DPLL_DDR;           // (0x40) 
            __RW   AUTOIDLE_DPLL_DISP_reg_t           AUTOIDLE_DPLL_DISP;        // (0x44)  //AUTO_DPLL_MODE is not supported!
            __R    IDLEST_DPLL_DISP_reg_t             IDLEST_DPLL_DISP;          // (0x48) 
            __RW   SSC_DELTAMSTEP_DPLL_DISP_reg_t     SSC_DELTAMSTEP_DPLL_DISP;  // (0x4C) 
            __RW   SSC_MODFREQDIV_DPLL_DISP_reg_t     SSC_MODFREQDIV_DPLL_DISP;  // (0x50)  
            __RW   CLKSEL_DPLL_DISP_reg_t             CLKSEL_DPLL_DISP;          // (0x54) 
            __RW   AUTOIDLE_DPLL_CORE_reg_t           AUTOIDLE_DPLL_CORE;        // (0x58)  //AUTO_DPLL_MODE is not supported! 
            __R    IDLEST_DPLL_CORE_reg_t             IDLEST_DPLL_CORE;          // (0x5C) 
            __RW   SSC_DELTAMSTEP_DPLL_CORE_reg_t     SSC_DELTAMSTEP_DPLL_CORE;  // (0x60) 
            __RW   SSC_MODFREQDIV_DPLL_CORE_reg_t     SSC_MODFREQDIV_DPLL_CORE;  // (0x64) 
            __RW   CLKSEL_DPLL_CORE_reg_t             CLKSEL_DPLL_CORE;          // (0x68) 
            __RW   AUTOIDLE_DPLL_PER_reg_t            AUTOIDLE_DPLL_PER;         // (0x6C)  //AUTO_DPLL_MODE is not supported. 
            __R    IDLEST_DPLL_PER_reg_t              IDLEST_DPLL_PER;           // (0x70) 
            __RW   SSC_DELTAMSTEP_DPLL_PER_reg_t      SSC_DELTAMSTEP_DPLL_PER;   // (0x74) 
            __RW   SSC_MODFREQDIV_DPLL_PER_reg_t      SSC_MODFREQDIV_DPLL_PER;   // (0x78)  
            __RW   CLKDCOLDO_DPLL_PER_reg_t           CLKDCOLDO_DPLL_PER;        // (0x7C) 
            __RW   DIV_M4_DPLL_CORE_reg_t             DIV_M4_DPLL_CORE;          // (0x80) 
            __RW   DIV_M5_DPLL_CORE_reg_t             DIV_M5_DPLL_CORE;          // (0x84) 
            __RW   CLKMODE_DPLL_MPU_reg_t             CLKMODE_DPLL_MPU;          // (0x88) 
            __RW   CLKMODE_DPLL_PER_reg_t             CLKMODE_DPLL_PER;          // (0x8C) 
            __RW   CLKMODE_DPLL_CORE_reg_t            CLKMODE_DPLL_CORE;         // (0x90) 
            __RW   CLKMODE_DPLL_DDR_reg_t             CLKMODE_DPLL_DDR;          // (0x94) 
            __RW   CLKMODE_DPLL_DISP_reg_t            CLKMODE_DPLL_DISP;         // (0x98) 
            __RW   CLKSEL_DPLL_PERIPH_reg_t           CLKSEL_DPLL_PERIPH;        // (0x9C) 
            __RW   DIV_M2_DPLL_DDR_reg_t              DIV_M2_DPLL_DDR;           // (0xA0)  
            __RW   DIV_M2_DPLL_DISP_reg_t             DIV_M2_DPLL_DISP;          // (0xA4) 
            __RW   DIV_M2_DPLL_MPU_reg_t              DIV_M2_DPLL_MPU;           // (0xA8) 
            __RW   DIV_M2_DPLL_PER_reg_t              DIV_M2_DPLL_PER;           // (0xAC) 
            __RW   WKUP_M3_CLKCTRL_reg_t              WKUP_M3_CLKCTRL;           // (0xB0) 
            __RW   UART0_CLKCTRL_reg_t                UART0_CLKCTRL;             // (0xB4) 
            __RW   I2C0_CLKCTRL_reg_t                 I2C0_CLKCTRL;              // (0xB8) 
            __RW   ADC_TSC_CLKCTRL_reg_t              ADC_TSC_CLKCTRL;           // (0xBC) 
            __RW   SMARTREFLEX0_CLKCTRL_reg_t         SMARTREFLEX0_CLKCTRL;      // (0xC0) 
            __RW   TIMER1_CLKCTRL_reg_t               TIMER1_CLKCTRL;            // (0xC4)
            __RW   SMARTREFLEX1_CLKCTRL_reg_t         SMARTREFLEX1_CLKCTRL;      // (0xC8) 
            __RW   L4_WKUP_AON_CLKSTCTRL_reg_t        L4_WKUP_AON_CLKSTCTRL;     // (0xCC) 
            __R    uint32_t                           RESERVED[1];
            __RW   WDT1_CLKCTRL_reg_t                 WDT1_CLKCTRL;              // (0xD4) 
            __RW   DIV_M6_DPLL_CORE_reg_t             DIV_M6_DPLL_CORE;          // (0xD8)
        };
    
        struct AM335x_CM_DPLL_Type
        {    
            __R    uint32_t                   RESERVED1[1];       // (0x00)                                                              
            __RW   TIMER7_CLK_reg_t           TIMER7_CLK;         // (0x04)  
            __RW   TIMER2_CLK_reg_t           TIMER2_CLK;         // (0x08) 
            __RW   TIMER3_CLK_reg_t           TIMER3_CLK;         // (0x0C) 
            __RW   TIMER4_CLK_reg_t           TIMER4_CLK;         // (0x10) 
            __RW   MAC_CLKSEL_reg_t           MAC_CLKSEL;         // (0x14) 
            __RW   TIMER5_CLK_reg_t           TIMER5_CLK;         // (0x18) 
            __RW   TIMER6_CLK_reg_t           TIMER6_CLK;         // (0x1C) 
            __RW   CPTS_RFT_CLKSEL_reg_t      CPTS_RFT_CLKSEL;    // (0x20)
            __R    uint32_t                   RESERVED2[1];       // (0x24)  
            __RW   TIMER1MS_CLK_reg_t         TIMER1MS_CLK;       // (0x28) 
            __RW   GFX_FCLK_reg_t             GFX_FCLK;           // (0x2C) 
            __RW   PRU_ICSS_OCP_CLK_reg_t     PRU_ICSS_OCP_CLK;   // (0x30) 
            __RW   LCDC_PIXEL_CLK_reg_t       LCDC_PIXEL_CLK;     // (0x34)  
            __RW   WDT1_CLK_reg_t             WDT1_CLK;           // (0x38) 
            __RW   GPIO0_DBCLK_reg_t          GPIO0_DBCLK;        // (0x3C)     
        };
    
        struct AM335x_CM_MPU_Type
        {                                                                 
            __RW   MPU_CLKSTCTRL_reg_t  MPU_CLKSTCTRL;  // (0x00)  
            __RW   MPU_CLKCTRL_reg_t    MPU_CLKCTRL;    // (0x04)      
        };
    
        struct AM335x_CM_DEVICE_Type
        {                                                                 
            __RW   CLKOUT_CTRL_reg_t  CLKOUT_CTRL;  // (0x00)       
        };
    
        struct AM335x_CM_RTC_Type
        {                                                                 
            __RW   RTC_CLKCTRL_reg_t      RTC_CLKCTRL;  // (0x00)  
            __RW   RTC_CLKSTCTRL_reg_t    CLKSTCTRL;    // (0x04)      
        };
    
        struct AM335x_CM_GFX_Type 
        {                                                                 
            __RW   GFX_L3_CLKSTCTRL_reg_t       GFX_L3_CLKSTCTRL;       // (0x00)  
            __RW   GFX_CLKCTRL_reg_t            GFX_CLKCTRL;            // (0x04) 
            __R    uint32_t                     RESERVED[1];            // (0x08) 
            __RW   L4LS_GFX_CLKSTCTRL_reg_t     L4LS_GFX_CLKSTCTRL;     // (0x0Ñ)  
            __RW   GFX_MMUCFG_CLKCTRL_reg_t     GFX_MMUCFG_CLKCTRL;     // (0x10)
            __RW   GFX_MMUDATA_CLKCTRL_reg_t    CLKSTCTRL;              // (0x14)     
        };
    
        struct AM335x_CM_CEFUSE_Type 
        {                                                                 
            __RW   CEFUSE_CLKSTCTRL_reg_t       CEFUSE_CLKSTCTRL;   // (0x00)
            __R    uint32_t                     RESERVED[7];        // (0x04..0x1C) 
            __RW   CEFUSE_CLKCTRL_reg_t         CEFUSE_CLKCTRL;     // (0x20)      
        };
    
        struct AM335x_PRM_IRQ_Type
        {                                                                 
            __RW   REVISION_reg_t           REVISION;           // (0x00)  
            __RW   IRQSTATUS_MPU_reg_t      IRQSTATUS_MPU;      // (0x04) 
            __RW   IRQENABLE_MPU_reg_t      IRQENABLE_MPU;      // (0x08)
            __RW   IRQSTATUS_M3_reg_t       IRQSTATUS_M3;       // (0x0C)
            __RW   IRQENABLE_M3_reg_t       IRQENABLE_M3;       // (0x10)     
        };
    
        struct AM335x_PRM_PER_Type
        {                                                                 
            __RW   PER_RSTCTRL_reg_t      PER_RSTCTRL;      // (0x00)
            __R    uint32_t               RESERVED[1];      // (0x04)   
            __R    PER_PWRSTST_reg_t      PER_PWRSTST;      // (0x08) 
            __RW   PER_PWRSTCTRL_reg_t    PER_PWRSTCTRL;    // (0x0C)     
        };
    
        struct AM335x_PRM_WKUP_Type
        {                                                                 
            __RW   WKUP_RSTCTRL_reg_t          WKUP_RSTCTRL;       // (0x00)
            __RW   WKUP_PWRSTCTRL_reg_t        WKUP_PWRSTCTRL;      // (0x04)   
            __RW   WKUP_PWRSTST_reg_t          WKUP_PWRSTST;       // (0x08) 
            __RW   WKUP_RSTST_reg_t            WKUP_RSTST;         // (0x0C)     
        };
    
        struct AM335x_PRM_MPU_Type
        {                                                                 
            __RW   MPU_PWRSTCTRL_reg_t      MPU_PWRSTCTRL;    // (0x00)
            __RW   MPU_PWRSTST_reg_t        MPU_PWRSTST;      // (0x04)   
            __RW   MPU_RSTST_reg_t          MPU_RSTST;        // (0x08)      
        };
    
        struct AM335x_PRM_DEVICE_Type
        {                                                                 
            __W    PRM_RSTCTRL_reg_t                  PRM_RSTCTRL;                 // (0x00)
            __RW   PRM_RSTTIME_reg_t                  PRM_RSTTIME;                 // (0x04)   
            __RW   PRM_RSTST_reg_t                    PRM_RSTST;                   // (0x08)
            __RW   PRM_SRAM_COUNT_reg_t               PRM_SRAM_COUNT;              // (0x0C)
            __RW   PRM_LDO_SRAM_CORE_SETUP_reg_t      PRM_LDO_SRAM_CORE_SETUP;     // (0x10)   
            __RW   PRM_LDO_SRAM_CORE_CTRL_reg_t       PRM_LDO_SRAM_CORE_CTRL;      // (0x14) 
            __RW   PRM_LDO_SRAM_MPU_SETUP_reg_t       PRM_LDO_SRAM_MPU_SETUP;      // (0x18)   
            __RW   PRM_LDO_SRAM_MPU_CTRL_reg_t        PRM_LDO_SRAM_MPU_CTRL;       // (0x1C)      
        };
    
        struct AM335x_PRM_RTC_Type
        {                                                                 
            __RW    RTC_PWRSTCTRL_reg_t     RTC_PWRSTCTRL; // (0x00)
            __R     RTC_PWRSTST_reg_t       RTC_PWRSTST;   // (0x04)        
        };
    
        struct AM335x_PRM_GFX_Type
        {                                                                 
            __RW    PM_GFX_PWRSTCTRL_reg_t    PM_GFX_PWRSTCTRL; // (0x00)
            __RW    RM_GFX_RSTCTRL_reg_t      RM_GFX_RSTCTRL;   // (0x04)
            __R     uint32_t                  RESERVED[2];
            __R     PM_GFX_PWRSTST_reg_t      PM_GFX_PWRSTST;   // (0x10)
            __RW    RM_GFX_RSTST_reg_t        RM_GFX_RSTST;     // (0x14)         
        };
    
        struct AM335x_PRM_CEFUSE_Type
        {                                                                 
            __RW    CEFUSE_PWRSTCTRL_reg_t    CEFUSE_PWRSTCTRL; // (0x00)
            __RW    CEFUSE_PWRSTST_reg_t      CEFUSE_PWRSTST;   // (0x04)         
        };
    
        constexpr uint32_t AM335x_PRCM_BASE         = 0x44E00000; 
        constexpr uint32_t AM335x_CM_PER_BASE       = AM335x_PRCM_BASE;       
        constexpr uint32_t AM335x_CM_WKUP_BASE      = 0x44E00400;
        constexpr uint32_t AM335x_CM_DPLL_BASE      = 0x44E00500;
        constexpr uint32_t AM335x_CM_MPU_BASE       = 0x44E00600;
        constexpr uint32_t AM335x_CM_DEVICE_BASE    = 0x44E00700;
        constexpr uint32_t AM335x_CM_RTC_BASE       = 0x44E00800;
        constexpr uint32_t AM335x_CM_GFX_BASE       = 0x44E00900;
        constexpr uint32_t AM335x_CM_CEFUSE_BASE    = 0x44E00A00;
        
        constexpr uint32_t AM335x_PRM_IRQ_BASE      = 0x44E00B00;    
        constexpr uint32_t AM335x_PRM_PER_BASE      = 0x44E00C00;    
        constexpr uint32_t AM335x_PRM_WKUP_BASE     = 0x44E00D00;
        constexpr uint32_t AM335x_PRM_MPU_BASE      = 0x44E00E00;
        constexpr uint32_t AM335x_PRM_DEVICE_BASE   = 0x44E00F00;
        constexpr uint32_t AM335x_PRM_RTC_BASE      = 0x44E01000;
        constexpr uint32_t AM335x_PRM_GFX_BASE      = 0x44E01100;
        constexpr uint32_t AM335x_PRM_CEFUSE_BASE   = 0x44E01200;
    
        /******************************** ALL POINTERS ON PRCM MODULE BLOCKS ***********************************************/
    
        constexpr AM335x_CM_PER_Type        *AM335x_CM_PER      = ((AM335x_CM_PER_Type *) AM335x_CM_PER_BASE); 
        constexpr AM335x_CM_WKUP_Type       *AM335x_CM_WKUP     = ((AM335x_CM_WKUP_Type *) AM335x_CM_WKUP_BASE); 
        constexpr AM335x_CM_DPLL_Type       *AM335x_CM_DPLL     = ((AM335x_CM_DPLL_Type *) AM335x_CM_DPLL_BASE);
        constexpr AM335x_CM_MPU_Type        *AM335x_CM_MPU      = ((AM335x_CM_MPU_Type *) AM335x_CM_MPU_BASE);
        constexpr AM335x_CM_DEVICE_Type     *AM335x_CM_DEVICE   = ((AM335x_CM_DEVICE_Type *) AM335x_CM_DEVICE_BASE);
        constexpr AM335x_CM_RTC_Type        *AM335x_CM_RTC      = ((AM335x_CM_RTC_Type *) AM335x_CM_RTC_BASE);
        constexpr AM335x_CM_GFX_Type        *AM335x_CM_GFX      = ((AM335x_CM_GFX_Type *) AM335x_CM_GFX_BASE);
        constexpr AM335x_CM_CEFUSE_Type     *AM335x_CM_CEFUSE   = ((AM335x_CM_CEFUSE_Type *) AM335x_CM_CEFUSE_BASE); 
        
        constexpr AM335x_PRM_IRQ_Type       *AM335x_PRM_IRQ     = ((AM335x_PRM_IRQ_Type *) AM335x_PRM_IRQ_BASE);  
        constexpr AM335x_PRM_PER_Type       *AM335x_PRM_PER     = ((AM335x_PRM_PER_Type *) AM335x_PRM_PER_BASE);
        constexpr AM335x_PRM_WKUP_Type      *AM335x_PRM_WKUP    = ((AM335x_PRM_WKUP_Type *) AM335x_PRM_WKUP_BASE); 
        constexpr AM335x_PRM_MPU_Type       *AM335x_PRM_MPU     = ((AM335x_PRM_MPU_Type *) AM335x_PRM_MPU_BASE); 
        constexpr AM335x_PRM_DEVICE_Type    *AM335x_PRM_DEVICE  = ((AM335x_PRM_DEVICE_Type *) AM335x_PRM_DEVICE_BASE); 
        constexpr AM335x_PRM_RTC_Type       *AM335x_PRM_RTC     = ((AM335x_PRM_RTC_Type *) AM335x_PRM_RTC_BASE); 
        constexpr AM335x_PRM_GFX_Type       *AM335x_PRM_GFX     = ((AM335x_PRM_GFX_Type *) AM335x_PRM_GFX_BASE); 
        constexpr AM335x_PRM_CEFUSE_Type    *AM335x_PRM_CEFUSE  = ((AM335x_PRM_CEFUSE_Type *) AM335x_PRM_CEFUSE_BASE);
        
        uint32_t debug_dump_CM_PER(AM335x_CM_PER_Type &sCM_PER = *AM335x_CM_PER);
        uint32_t debug_dump_CM_WKUP(AM335x_CM_WKUP_Type &sCM_WKUP = *AM335x_CM_WKUP);
        /* for testing purpose */
        inline uint32_t debug_dump_CM_PER(AM335x_CM_PER_Type &sCM_PER)
        {
              constexpr uint32_t COUNTOF_CM_PER = sizeof(AM335x_CM_PER_Type)/sizeof(uint32_t);
              volatile uint32_t TSTREG[COUNTOF_CM_PER] = {0};          
              uint32_t *pAM335x_CM_PER = (uint32_t *)&sCM_PER;
              
              //volatile uint32_t TSTREG1 = (uint32_t)m_sCM_PER.GPIO1_CLKCTRL.reg;
              //volatile uint32_t TSTREG2 = (uint32_t)m_sCM_PER.GPIO2_CLKCTRL.reg;
              //volatile uint32_t TSTREG3 = (uint32_t)sCM_PER.GPIO3_CLKCTRL.reg;
              //volatile uint32_t TSTREG4 = (uint32_t)sCM_PER.EPWMSS1_CLKCTRL.reg;
              volatile uint32_t SIZEOF_CM_PER = sizeof(AM335x_CM_PER_Type); 
              
              for(uint32_t i = 0 ; i < COUNTOF_CM_PER; i++)
              {   
                    TSTREG[i] = pAM335x_CM_PER[i];
              }
              
              return SIZEOF_CM_PER;
        }
        
        /* for testing purpose */
        inline uint32_t debug_dump_CM_WKUP(AM335x_CM_WKUP_Type &sCM_WKUP)
        {
              constexpr uint32_t COUNTOF_CM_WKUP = sizeof(AM335x_CM_WKUP_Type)/sizeof(uint32_t);
              volatile uint32_t TSTREG[COUNTOF_CM_WKUP] = {0};          
              uint32_t *pAM335x_CM_WKUP = (uint32_t *)&sCM_WKUP;
              
              volatile uint32_t TSTREG1 = (uint32_t)sCM_WKUP.IDLEST_DPLL_MPU.reg;
              volatile uint32_t TSTREG2 = (uint32_t)sCM_WKUP.SSC_DELTAMSTEP_DPLL_MPU.reg;
              volatile uint32_t TSTREG3 = (uint32_t)sCM_WKUP.SSC_MODFREQDIV_DPLL_MPU.reg;
              volatile uint32_t TSTREG4 = (uint32_t)sCM_WKUP.CLKSEL_DPLL_MPU.reg;
              
              volatile uint32_t SIZEOF_CM_WKUP = sizeof(AM335x_CM_WKUP_Type); 
              
              for(uint32_t i = 0 ; i < COUNTOF_CM_WKUP; i++)
              {   
                    TSTREG[i] = pAM335x_CM_WKUP[i];
              }
              
              return SIZEOF_CM_WKUP;
        }

        /**
        * @brief run L3S,L3,L4,L4LS interconnects clock
        */
        void  run_clk_interconnects(); 
         
        void  run_clk_DMTIMER(DMTIMER::e_TIMER_NUM tmr_num);

        /**
        * @brief run clocks only for DMTIMER 1
        */
        void  run_clk_DMTIMER_1ms(e_TIMER1MS_CLKSEL clk_sel); 

        void  run_clk_DMTIMER_5(); 

        void  run_clk_DMTIMER_6(); 
        
        void  run_clk_GPIO0(); 

        void  run_clk_GPIO1();  
        
        void  run_clk_GPIO2();
        
        void  run_clk_GPIO3();
   
        void  run_I2C0_clk();

        void  run_I2C1_clk();

        void  run_I2C2_clk();
        
        void  run_clk_UART0();

        void run_RTC_clk();

        //void  run_EDMA_clk(void* p_Obj);

    } // namespace PRCM

} // namespace REGS

#endif //_PRCM_H_