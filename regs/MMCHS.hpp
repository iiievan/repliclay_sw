#ifndef _MMCHS_H_
#define _MMCHS_H_

#include <stdint.h>

namespace REGS
{
    //This is MMCHS namespace
    namespace MMCHS
    { 
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_MMCHS_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      
        
        /* [reset state = 0x0] [offset = 0x110]*/
        typedef union 
        {                                 /* This register allows controlling various parameters of the OCP interface.
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SYSCONFIG_reg_t;  

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SYSSTATUS_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CSRE_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SYSTEST_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CON_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PWCNT_reg_t;

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SDMASA_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } BLK_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ARG_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CMD_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RSP10_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RSP32_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RSP54_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } RSP76_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DATA_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } PSTATE_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } HCTL_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } SYSCTL_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } STAT_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } IE_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ISE_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } AC12_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CAPA_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } CUR_CAPA_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } FE_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ADMAES_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ADMASAL_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ADMASAH_reg_t; 

        /* [reset state = 0x] [offset = 0x]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    R   :1;     // bit: 0..3  (W) 
                uint32_t                    :31;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } REV_reg_t; 
      

        struct AM335x_MMCHS_Type
        {     
            __R   uint32_t        RESERVED[];                                                                                 
            __   SYSCONFIG_reg_t  SYSCONFIG;        // (0x110)  
            __   SYSSTATUS_reg_t  SYSSTATUS;        // (0x114)
            __R   uint32_t        RESERVED1[];
            __   CSRE_reg_t       CSRE;             // (0x124)
            __   SYSTEST_reg_t    SYSTEST;          // (0x128)
            __   CON_reg_t        CON;              // (0x12C)
            __   PWCNT_reg_t      PWCNT;            // (0x130)
            __R   uint32_t        RESERVED2[];
            __   SDMASA_reg_t     SDMASA;           // (0x200)
            __   BLK_reg_t        BLK;              // (0x204)
            __   ARG_reg_t        ARG;              // (0x208)
            __   CMD_reg_t        CMD;              // (0x20C)
            __   RSP10_reg_t      RSP10;            // (0x210)
            __   RSP32_reg_t      RSP32;            // (0x214)
            __   RSP54_reg_t      RSP54;            // (0x218)
            __   RSP76_reg_t      RSP76;            // (0x21C)
            __   DATA_reg_t       DATA;             // (0x220)
            __   PSTATE_reg_t     PSTATE;           // (0x224)
            __   HCTL_reg_t       HCTL;             // (0x228)
            __   SYSCTL_reg_t     SYSCTL;           // (0x22C)
            __   STAT_reg_t       STAT;             // (0x230)
            __   IE_reg_t         IE;               // (0x234)
            __   ISE_reg_t        ISE;              // (0x238)
            __   AC12_reg_t       AC12;             // (0x23C)
            __   CAPA_reg_t       CAPA;             // (0x240)
            __   CUR_CAPA_reg_t   CUR_CAPA;         // (0x248)
            __R   uint32_t        RESERVED3[];
            __   FE_reg_t         FE;               // (0x250)
            __   ADMAES_reg_t     ADMAES;           // (0x254)
            __   ADMASAL_reg_t    ADMASAL;          // (0x258)
            __   ADMASAH_reg_t    ADMASAH;          // (0x25C)
            __R   uint32_t        RESERVED1[];
            __   REV_reg_t        REV;              // (0x2FC)            
        };

        constexpr uint32_t AM335x_MMCHS_0_BASE = 0x48060000;
        constexpr uint32_t AM335x_MMCHS_1_BASE = 0x481D8000;
        constexpr uint32_t AM335x_MMCHS_2_BASE = 0x47810000;

        constexpr AM335x_MMCHS_Type * AM335x_MMCHS_0_regs = reinterpret_cast<AM335x_MMCHS_Type *>(AM335x_MMCHS_0_BASE);
        constexpr AM335x_MMCHS_Type * AM335x_MMCHS_1_regs = reinterpret_cast<AM335x_MMCHS_Type *>(AM335x_MMCHS_1_BASE);
        constexpr AM335x_MMCHS_Type * AM335x_MMCHS_2_regs = reinterpret_cast<AM335x_MMCHS_Type *>(AM335x_MMCHS_2_BASE);     

    } // namespace MMCHS
} // namespace REGS

#endif //_MMCHS_H_
