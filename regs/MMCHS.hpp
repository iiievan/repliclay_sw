 #ifndef _MMCHS_H_
#define _MMCHS_H_

#include <stdint.h>

namespace REGS
{
    //This is MMCHS namespace
    namespace MMCHS
    { 
    /******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_MMCHS_Type Registers **********************************************************************/ 
    
    /******************************************************************************************************************************************************************************/      
        
        /* SD_SYSCONFIG (offset = 0x110) [reset = 0x0] */
        typedef union
        {                                          /* System Configuration Register
                                                     */
            struct
            {
                uint32_t    AUTOIDLE      : 1;     // bit  0      (R/W) Automatic clock gating control
                                                   //                   Controls whether internal clocks are automatically gated when not in use
                                                   //                   [ 0x0 = Clocks free-running;
                                                   //                     0x1 = Automatic clock gating ]
                uint32_t    SOFTRESET     : 1;     // bit  1      (R/W) Software reset control
                                                   //                   Writing 1 triggers a software reset of the module
                                                   //                   [ 0x0 = No effect;
                                                   //                     0x1 = Trigger module reset ]
                uint32_t    ENAWAKEUP     : 1;     // bit  2      (R/W) Wake-up feature control
                                                   //                   Enables/disables wake-up capability
                                                   //                   [ 0x0 = Disabled;
                                                   //                     0x1 = Enabled ]
                uint32_t    SIDLEMODE     : 2;     // bits 3..4   (R/W) Smart-idle mode selection [see e_SIDLEMODE]
                uint32_t                  : 3;     // bits 5..7   (R)   Reserved
                uint32_t    CLOCKACTIVITY : 2;     // bits 8..9   (R/W) Clock activity during wake-up [see e_CLOCKACTIVITY]
                uint32_t                  :22;     // bits 10..31 (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SYSCONFIG_reg_t;
        
        /* Enums for multi-value fields */
        enum e_SIDLEMODE : uint32_t
        {
            /*  Controls how the module responds to idle requests
             *  Determines power management behavior when peripheral is idle
             */
            SIDLE_FORCE    = 0x0,  // Unconditionally acknowledge idle request
            SIDLE_NO       = 0x1,  // Ignore idle request
            SIDLE_SMART    = 0x2,  // Smart idle based on internal activity
            SIDLE_RESERVED = 0x3   // Reserved
        };
        
        enum e_CLOCKACTIVITY : uint32_t
        {
            /*  Controls which clocks remain active during wake-up
             *  Determines clock gating behavior during low-power states
             */
            CLKACT_BOTH_OFF   = 0x0,  // Interface and Functional clock may be switched off
            CLKACT_INTF_ON    = 0x1,  // Interface clock maintained
            CLKACT_FUNC_ON    = 0x2,  // Functional clock maintained
            CLKACT_BOTH_ON    = 0x3   // Both clocks maintained
        };
        
        /* SD_SYSSTATUS (offset = 0x114) [reset = 0x0] */
        typedef union
        {                                          /* System Status Register
                                                     */
            struct
            {
                uint32_t    RESETDONE    :1;       // bit  0      (R) Reset completion status
                                                   //                 Indicates whether software reset is completed
                                                   //                 [ 0x0 = Reset ongoing;
                                                   //                   0x1 = Reset completed ]
                uint32_t                :31;       // bits 1..31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SYSSTATUS_reg_t;
        
        /* SD_CSRE (offset = 0x124) [reset = 0x0] */
        typedef union
        {                                          /* Card Status Response Error Register
                                                     */
            struct
            {
                uint32_t    CSRE         :32;      // bits 0..31  (R/W) Card status response error bits
                                                   //                   Each bit corresponds to a status bit in card response
                                                   //                   Writing 1 clears corresponding error bit
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CSRE_reg_t;
        
        /* SD_SYSTEST (offset = 0x128) [reset = 0x0] */
        typedef union
        {                                          /* System Test Register
                                                     */
            struct
            {
                uint32_t    MCKD         :1;       // bit  0      (R/W) MMC clock output test control
                                                   //                   [ 0x0 = Clock output low;
                                                   //                     0x1 = Clock output high ]
                uint32_t    CDIR         :1;       // bit  1      (R/W) CMD pin direction control
                                                   //                   [ 0x0 = Output;
                                                   //                     0x1 = Input ]
                uint32_t    CDAT         :1;       // bit  2      (R/W) CMD pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    DDIR         :1;       // bit  3      (R/W) DAT pins direction control
                                                   //                   [ 0x0 = Output;
                                                   //                     0x1 = Input ]
                uint32_t    D0D          :1;       // bit  4      (R/W) DAT0 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D1D          :1;       // bit  5      (R/W) DAT1 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D2D          :1;       // bit  6      (R/W) DAT2 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D3D          :1;       // bit  7      (R/W) DAT3 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D4D          :1;       // bit  8      (R/W) DAT4 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D5D          :1;       // bit  9      (R/W) DAT5 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D6D          :1;       // bit  10     (R/W) DAT6 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    D7D          :1;       // bit  11     (R/W) DAT7 pin value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    SSB          :1;       // bit  12     (R/W) Status bit force control
                                                   //                  [ 0x0 = Clear;
                                                   //                    0x1 = Force status bits ]
                uint32_t    WAKD         :1;       // bit  13     (R/W) Wake request output
                                                   //                   [ 0x0 = Low;
                                                   //                    0x1 = High ]
                uint32_t    SDWP         :1;       // bit  14     (R/W) Write protect input value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    SDCD         :1;       // bit  15     (R/W) Card detect input value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t    OBI          :1;       // bit  16     (R/W) Out-of-band interrupt value
                                                   //                   [ 0x0 = Low;
                                                   //                     0x1 = High ]
                uint32_t                :15;       // bits 17..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SYSTEST_reg_t;
        
        /* SD_CON (offset = 0x12C) [reset = 0x0] */
        typedef union
        {                                          /* Control Register
                                                     */
            struct
            {
                uint32_t    OD           :1;       // bit  0      (R/W) Open drain mode control
                                                   //                   [ 0x0 = No open drain;
                                                   //                     0x1 = Open drain ]
                uint32_t    INIT         :1;       // bit  1      (R/W) Initialization control
                                                   //                   [ 0x0 = No init;
                                                   //                     0x1 = Send init ]
                uint32_t    HR           :1;       // bit  2      (R/W) Host response control
                                                   //                   [ 0x0 = No response;
                                                   //                     0x1 = Generate response ]
                uint32_t    STR          :1;       // bit  3      (R/W) Transfer mode selection
                                                   //                   [ 0x0 = Block transfer;
                                                   //                     0x1 = Stream transfer ]
                uint32_t    MODE         :1;       // bit  4      (R/W) Operating mode selection
                                                   //                   [ 0x0 = Functional;
                                                   //                     0x1 = System ]
                uint32_t    DW8          :1;       // bit  5      (R/W) Data width selection
                                                   //                   [ 0x0 = 1/4-bit;
                                                   //                     0x1 = 8-bit ]
                uint32_t    MIT          :1;       // bit  6      (R/W) MMC interrupt timeout control
                                                   //                   [ 0x0 = Timeout enabled;
                                                   //                     0x1 = Timeout disabled ]
                uint32_t    CDP          :1;       // bit  7      (R/W) Card detect polarity
                                                   //                   [ 0x0 = Active high;
                                                   //                     0x1 = Active low ]
                uint32_t    WPP          :1;       // bit  8      (R/W) Write protect polarity
                                                   //                   [ 0x0 = Active high;
                                                   //                     0x1 = Active low ]
                uint32_t    DVAL         :2;       // bits 9,10   (R/W) Debounce filter value [see e_DVAL]
                uint32_t    CTPL         :1;       // bit  11     (R/W) DAT1 line power control
                                                   //                   [ 0x0 = Disable all;
                                                   //                     0x1 = Keep DAT1 ]
                uint32_t    CEATA        :1;       // bit  12     (R/W) CE-ATA mode control
                                                   //                   [ 0x0 = Standard;
                                                   //                     0x1 = CE-ATA ]
                uint32_t                 :2;       // bits 13..14 (R)   Reserved
                uint32_t    PADEN        :1;       // bit  15     (R/W) MMC lines power control
                                                   //                   [ 0x0 = Automatic;
                                                   //                     0x1 = Forced active ]
                uint32_t    CLKEXTFREE   :1;       // bit  16     (R/W) External clock control
                                                   //                   [ 0x0 = Off outside transaction;
                                                   //                     0x1 = Maintained ]
                uint32_t    BOOT_ACK     :1;       // bit  17     (R/W) Boot acknowledge control
                                                   //                   [ 0x0 = No ack;
                                                   //                     0x1 = Ack expected ]
                uint32_t    BOOT_CF0     :1;       // bit  18     (R/W) Boot status support
                                                   //                   [ 0x0 = CMD line not forced;
                                                   //                     0x1 = CMD line forced to 0 ]
                uint32_t    DDR          :1;       // bit  19     (R/W) Dual Data Rate mode
                                                   //                   [ 0x0 = Standard;
                                                   //                     0x1 = DDR ]
                uint32_t    DMA_MnS      :1;       // bit  20     (R/W) DMA mode selection
                                                   //                   [ 0x0 = Slave;
                                                   //                     0x1 = Master ]
                uint32_t    SDMA_LnE     :1;       // bit  21     (R/W) Slave DMA trigger type
                                                   //                   [ 0x0 = Edge;
                                                   //                     0x1 = Level ]
                uint32_t                :10;       // bits 22..31 (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CON_reg_t;
        
        /* Enums for multi-value fields */
        enum e_DVAL : uint32_t
        {
            /*  Selects debounce filter time for card detection
             *  Determines how long signal must be stable before being recognized
             */
            DEBOUNCE_33US   = 0x0,  // 33 μs debounce time
            DEBOUNCE_231US  = 0x1,  // 231 μs debounce time
            DEBOUNCE_1MS    = 0x2,  // 1 ms debounce time
            DEBOUNCE_8_4MS  = 0x3   // 8.4 ms debounce time
        };
        
        /* SD_PWCNT (offset = 0x130) [reset = 0x0] */
        typedef union
        {                                          /* Power Control Register
                                                     */
            struct
            {
                uint32_t    PWRCNT      :16;       // bits 0..15  (R/W) Power counter value
                                                   //                   Controls power-up delay sequence timing
                uint32_t                :16;       // bits 16..31 (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PWCNT_reg_t;
        
        /* SD_SDMASA (offset = 0x200) [reset = 0x0] */
        typedef union
        {                                          /* SDMA System Address Register
                                                     */
            struct
            {
                uint32_t    SDMA_SYSADDR :32;      // bits 0..31  (R) SDMA system address
                                                   //                 Contains current SDMA buffer address
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDMASA_reg_t;
        
        /* SD_BLK (offset = 0x204) [reset = 0x0] */
        typedef union
        {                                          /* Block Register
                                                     */
            struct
            {
                uint32_t    BLEN         :12;      // bits 0..11  (R/W) Transfer block size
                                                   //                   Specifies block length in bytes for data transfer
                uint32_t                 : 4;      // bits 12..15 (R)   Reserved
                uint32_t    NBLK         :16;      // bits 16..31 (R/W) Number of blocks to transfer
                                                   //                   Specifies number of blocks in current transfer
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } BLK_reg_t;
        
        /* SD_ARG (offset = 0x208) [reset = 0x0] */
        typedef union
        {                                          /* Argument Register
                                                     */
            struct
            {
                uint32_t    ARG          :32;      // bits 0..31  (R/W) Command argument
                                                   //                   Contains argument for next command
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ARG_reg_t;
        
        /* SD_CMD (offset = 0x20C) [reset = 0x0] */
        typedef union
        {                                          /* Command Register
                                                     */
            struct
            {
                uint32_t    DE           : 1;      // bit  0      (R/W) DMA Enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BCE          : 1;      // bit  1      (R/W) Block Count Enable
                                                   //                   [ 0x0 = Disabled;
                                                   //                     0x1 = Enabled ]
                uint32_t    ACEN         : 1;      // bit  2      (R/W) Auto CMD12 Enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 : 1;      // bit  3      (R)   Reserved
                uint32_t    DDIR         : 1;      // bit  4      (R/W) Data transfer Direction
                                                   //                   [ 0x0 = Write;
                                                   //                     0x1 = Read ]
                uint32_t    MSBS         : 1;      // bit  5      (R/W) Block transfer mode
                                                   //                   [ 0x0 = Single;
                                                   //                     0x1 = Multi ]
                uint32_t                 :10;      // bits 6..15  (R)   Reserved
                uint32_t    RSP_TYPE     : 2;      // bits 16,17  (R/W) Response type [see e_RSP_TYPE]
                uint32_t                 : 1;      // bit  18     (R)   Reserved
                uint32_t    CCCE         : 1;      // bit  19     (R/W) Command CRC check enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CICE         : 1;      // bit  20     (R/W) Command index check enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DP           : 1;      // bit  21     (R/W) Data present select
                                                   //                   [ 0x0 = No data;
                                                   //                     0x1 = Data present ]
                uint32_t    CMD_TYPE     : 2;      // bits 22,23  (R/W) Command type [see e_CMD_TYPE]
                uint32_t    INDX         : 6;      // bits 24..29 (R/W) Command index
                                                   //                   Contains command index for next command
                uint32_t                 : 2;      // bits 30,31  (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CMD_reg_t;
        
        /* Enums for multi-value fields */
        enum e_RSP_TYPE : uint32_t
        {
            /*  Defines expected response format from card
             *  Determines how controller interprets response from MMC/SD card
             */
            RSP_NONE       = 0x0,  // No response expected
            RSP_136BIT     = 0x1,  // 136-bit response expected
            RSP_48BIT      = 0x2,  // 48-bit response expected
            RSP_48BIT_BUSY = 0x3   // 48-bit response with busy signal
        };
        
        enum e_CMD_TYPE : uint32_t
        {
            /*  Defines command type for current operation
             *  Determines special handling for different command categories
             */
            CMD_NORMAL     = 0x0,  // Normal command (no special handling)
            CMD_SUSPEND    = 0x1,  // Suspend command (pause current operation)
            CMD_RESUME     = 0x2,  // Resume command (continue paused operation)
            CMD_ABORT      = 0x3   // Abort command (terminate current operation)
        };
        
        /* SD_RSP10 (offset = 0x210) [reset = 0x0] */
        typedef union
        {                                          /* Response Register 0-1
                                                     */
            struct
            {
                uint32_t    RSP0         :16;      // bits 0..15  (R) Command Response bits [15:0]
                                                   //                 Contains first 16 bits of card response
                uint32_t    RSP1         :16;      // bits 16..31 (R) Command Response bits [31:16]
                                                   //                 Contains next 16 bits of card response
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } RSP10_reg_t;
        
        /* SD_RSP32 (offset = 0x214) [reset = 0x0] */
        typedef union
        {                                          /* Response Register 2-3
                                                     */
            struct
            {
                uint32_t    RSP2         :16;      // bits 0..15  (R) Command Response bits [47:32]
                                                   //                 Contains next 16 bits of card response
                uint32_t    RSP3         :16;      // bits 16..31 (R) Command Response bits [63:48]
                                                   //                 Contains next 16 bits of card response
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } RSP32_reg_t;
        
        /* SD_RSP54 (offset = 0x218) [reset = 0x0] */
        typedef union
        {                                          /* Response Register 4-5
                                                     */
            struct
            {
                uint32_t    RSP4         :16;      // bits 0..15  (R) Command Response bits [79:64]
                                                   //                 Contains next 16 bits of card response
                uint32_t    RSP5         :16;      // bits 16..31 (R) Command Response bits [95:80]
                                                   //                 Contains next 16 bits of card response
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } RSP54_reg_t;
        
        /* SD_RSP76 (offset = 0x21C) [reset = 0x0] */
        typedef union
        {                                          /* Response Register 6-7
                                                     */
            struct
            {
                uint32_t    RSP6         :16;      // bits 0..15  (R) Command Response bits [111:96]
                                                   //                 Contains next 16 bits of card response
                uint32_t    RSP7         :16;      // bits 16..31 (R) Command Response bits [127:112]
                                                   //                 Contains final 16 bits of card response
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } RSP76_reg_t;
        
        /* SD_DATA (offset = 0x220) [reset = 0x0] */
        typedef union
        {                                          /* Data Register
                                                     */
            struct
            {
                uint32_t    DATA         :32;      // bits 0..31  (R/W) Data register
                                                   //                   Contains data being read or written
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } DATA_reg_t;
        
        /* SD_PSTATE (offset = 0x224) [reset = 0x0] */
        typedef union
        {                                          /* Present State Register
                                                     */
            struct
            {
                uint32_t    CMDI         :1;       // bit  0      (R) Command inhibit status
                                                   //                 [ 0x0 = Command allowed;
                                                   //                   0x1 = Command inhibited ]
                uint32_t    DATI         :1;       // bit  1      (R) Data inhibit status
                                                   //                 [ 0x0 = Data transfer allowed;
                                                   //                   0x1 = Data transfer inhibited ]
                uint32_t    DLA          :1;       // bit  2      (R) Data line active status
                                                   //                 [ 0x0 = Data line idle;
                                                   //                   0x1 = Data line active ]
                uint32_t                 :5;       // bit  3..7   (R) Reserved
                uint32_t    WTA          :1;       // bit  8      (R) Write transfer active
                                                   //                 [ 0x0 = No write transfer;
                                                   //                   0x1 = Write transfer in progress ]
                uint32_t    RTA          :1;       // bit  9      (R) Read transfer active
                                                   //                 [ 0x0 = No read transfer;
                                                   //                   0x1 = Read transfer in progress ]
                uint32_t    BWE          :1;       // bit  10     (R) Buffer write enable
                                                   //                 [ 0x0 = Buffer not ready for write;
                                                   //                   0x1 = Buffer ready for write ]
                uint32_t    BRE          :1;       // bit  11     (R) Buffer read enable
                                                   //                 [ 0x0 = Buffer not ready for read;
                                                   //                   0x1 = Buffer ready for read ]
                uint32_t                 :4;       // bits 12..15 (R) Reserved
                uint32_t    CINS         :1;       // bit  16     (R) Card inserted status
                                                   //                 [ 0x0 = No card;
                                                   //                   0x1 = Card present ]
                uint32_t    CSS          :1;       // bit  17     (R) Card state stable
                                                   //                 [ 0x0 = Unstable;
                                                   //                   0x1 = Stable ]
                uint32_t    CDPL         :1;       // bit  18     (R) Card detect pin level
                                                   //                 [ 0x0 = Low;
                                                   //                   0x1 = High ]
                uint32_t    WP           :1;       // bit  19     (R) Write protect status
                                                   //                 [ 0x0 = Not protected;
                                                   //                   0x1 = Protected ]
                uint32_t    DLEV         :4;       // bits 20..23 (R) Data line signal level
                                                   //                 Each bit represents one data line
                uint32_t    CLEV         :1;       // bit  24     (R) Command line signal level
                                                   //                 [ 0x0 = Low;
                                                   //                   0x1 = High ]
                uint32_t                 :7;       // bits 25..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PSTATE_reg_t;
        
        /* SD_HCTL (offset = 0x228) [reset = 0x0] */
        typedef union
        {                                          /* Host Control Register
                                                     */
            struct
            {
                uint32_t                 :1;       // bit  0      (R)   Reserved
                uint32_t    DTW          :1;       // bit  1      (R/W) Data transfer width
                                                   //                   [ 0x0 = 1-bit;
                                                   //                     0x1 = 4-bit ]
                uint32_t    HSPE         :1;       // bit  2      (R/W) High Speed Enable
                                                   //                   [ 0x0 = Normal speed;
                                                   //                     0x1 = High speed ]
                uint32_t    DMAS         :2;       // bits 3,4    (R/W) DMA Select [see e_DMAS]
                uint32_t                 :1;       // bit  5      (R)   Reserved
                uint32_t    CDTL         :1;       // bit  6      (R/W) Card detect test level
                                                   //                   [ 0x0 = No card;
                                                   //                     0x1 = Card inserted ]
                uint32_t    CDSS         :1;       // bit  7      (R/W) Card detect signal source
                                                   //                   [ 0x0 = SDCD# pin;
                                                   //                     0x1 = Test level ]
                uint32_t    SDBP         :1;       // bit  8      (R/W) SD bus power control
                                                   //                   [ 0x0 = Off;
                                                   //                     0x1 = On ]
                uint32_t    SDVS         :3;       // bits 9..11  (R/W) SD bus voltage select [see e_SDVS]
                uint32_t                 :4;       // bits 12..15 (R)   Reserved
                uint32_t    SBGR         :1;       // bit  16     (R/W) Stop at block gap request
                                                   //                   [ 0x0 = Continue transfer;
                                                   //                     0x1 = Stop at gap ]
                uint32_t    CR           :1;       // bit  17     (R/W) Continue request
                                                   //                   [ 0x0 = No effect;
                                                   //                     0x1 = Transfer restart ]
                uint32_t    RWC          :1;       // bit  18     (R/W) Read wait control
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    IBG          :1;       // bit  19     (R/W) Interrupt at block gap
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :4;       // bits 20..23 (R)   Reserved
                uint32_t    IWE          :1;       // bit  24     (R/W) Card interrupt wake-up enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    INS          :1;       // bit  25     (R/W) Card insertion wake-up enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    REM          :1;       // bit  26     (R/W) Card removal wake-up enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    OBWE         :1;       // bit  27     (R/W) Out-of-band interrupt wake-up
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :4;       // bits 28..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } HCTL_reg_t;
        
        /* Enums for multi-value fields */
        enum e_DMAS : uint32_t
        {
            /*  Selects DMA mode for data transfers
             *  Determines which DMA engine is used for data movement
             */
            DMA_RESERVED0  = 0x0,  // Reserved value 0
            DMA_RESERVED1  = 0x1,  // Reserved value 1
            DMA_ADMA2_32   = 0x2,  // 32-bit Address ADMA2
            DMA_RESERVED3  = 0x3   // Reserved value 3
        };
        
        enum e_SDVS : uint32_t
        {
            /*  Selects operating voltage for SD bus
             *  Must match card's supported voltage range
             */
            VS_1_8V        = 0x5,  // 1.8V (Typical)
            VS_3_0V        = 0x6,  // 3.0V (Typical)
            VS_3_3V        = 0x7   // 3.3V (Typical)
        };
        
        /* SD_SYSCTL (offset = 0x22C) [reset = 0x0] */
        typedef union
        {                                          /* System Control Register
                                                     */
            struct
            {
                uint32_t    ICE          :1;       // bit  0      (R/W) Internal clock enable
                                                   //                   [ 0x0 = Stopped;
                                                   //                     0x1 = Oscillates ]
                uint32_t    ICS          :1;       // bit  1      (R)   Internal clock stable
                                                   //                   [ 0x0 = Not stable;
                                                   //                     0x1 = Stable ]
                uint32_t    CEN          :1;       // bit  2      (R/W) Clock enable
                                                   //                   [ 0x0 = Not provided;
                                                   //                     0x1 = Provided ]
                uint32_t                 :3;       // bits 3..5   (R)   Reserved
                uint32_t    CLKD         :10;      // bits 6..15  (R/W) Clock frequency select
                                                   //                   Controls clock divider for SD clock
                uint32_t    DTO          :4;       // bits 16..19 (R/W) Data timeout counter [see e_DTO]
                uint32_t                 :4;       // bits 20..23 (R)   Reserved
                uint32_t    SRA          :1;       // bit  24     (R/W) Software reset all
                                                   //                   [ 0x0 = Reset completed;
                                                   //                     0x1 = Reset ]
                uint32_t    SRC          :1;       // bit  25     (R/W) Software reset CMD line
                                                   //                   [ 0x0 = Reset completed;
                                                   //                     0x1 = Reset ]
                uint32_t    SRD          :1;       // bit  26     (R/W) Software reset DAT line
                                                   //                   [ 0x0 = Reset completed;
                                                   //                     0x1 = Reset ]
                uint32_t                 :5;       // bits 27..31 (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SYSCTL_reg_t;
        
        /* Enums for multi-value fields */
        enum e_DTO : uint32_t
        {
            /*  Selects data timeout period
             *  Determines how long controller waits for response before timing out
             */
            DTO_2_13       = 0x0,  // TCF x 2^13 (8.192 ms at 100 kHz)
            DTO_2_14       = 0x1,  // TCF x 2^14 (16.384 ms at 100 kHz)
            DTO_2_15       = 0x2,  // TCF x 2^15 (32.768 ms at 100 kHz)
            DTO_2_16       = 0x3,  // TCF x 2^16 (65.536 ms at 100 kHz)
            DTO_2_17       = 0x4,  // TCF x 2^17 (131.072 ms at 100 kHz)
            DTO_2_18       = 0x5,  // TCF x 2^18 (262.144 ms at 100 kHz)
            DTO_2_19       = 0x6,  // TCF x 2^19 (524.288 ms at 100 kHz)
            DTO_2_20       = 0x7,  // TCF x 2^20 (1.048576 s at 100 kHz)
            DTO_2_21       = 0x8,  // TCF x 2^21 (2.097152 s at 100 kHz)
            DTO_2_22       = 0x9,  // TCF x 2^22 (4.194304 s at 100 kHz)
            DTO_2_23       = 0xA,  // TCF x 2^23 (8.388608 s at 100 kHz)
            DTO_2_24       = 0xB,  // TCF x 2^24 (16.777216 s at 100 kHz)
            DTO_2_25       = 0xC,  // TCF x 2^25 (33.554432 s at 100 kHz)
            DTO_2_26       = 0xD,  // TCF x 2^26 (67.108864 s at 100 kHz)
            DTO_2_27       = 0xE   // TCF x 2^27 (134.217728 s at 100 kHz)
        };
        
        /* SD_STAT (offset = 0x230) [reset = 0x0] */
        typedef union
        {                                          /* Status Register
                                                     */
            struct
            {
                uint32_t    CC           :1;       // bit  0      (R/W) Command complete
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t    TC           :1;       // bit  1      (R/W) Transfer completed
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t    BGE          :1;       // bit  2      (R/W) Block gap event
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t    DMA          :1;       // bit  3      (R/W) DMA interrupt
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t    BWR          :1;       // bit  4      (R/W) Buffer write ready
                                                   //                   [ 0x0 = Not ready;
                                                   //                     0x1 = Ready ]
                uint32_t    BRR          :1;       // bit  5      (R/W) Buffer read ready
                                                   //                   [ 0x0 = Not ready;
                                                   //                     0x1 = Ready ]
                uint32_t    CINS         :1;       // bit  6      (R/W) Card Insertion
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t    CREM         :1;       // bit  7      (R/W) Card Removal
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t    CIRQ         :1;       // bit  8      (R)   Card interrupt
                                                   //                   [ 0x0 = No interrupt;
                                                   //                     0x1 = Interrupt pending ]
                uint32_t    OBI          :1;       // bit  9      (R)   Out-of-band interrupt
                                                   //                   [ 0x0 = No interrupt;
                                                   //                     0x1 = Interrupt pending ]
                uint32_t    BSR          :1;       // bit  10     (R/W) Boot Status Received
                                                   //                   [ 0x0 = No event;
                                                   //                     0x1 = Event occurred ]
                uint32_t                 :4;       // bits 11..14 (R)   Reserved
                uint32_t    ERRI         :1;       // bit  15     (R)   Error interrupt
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    CTO          :1;       // bit  16     (R/W) Command timeout error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    CCRC         :1;       // bit  17     (R/W) Command CRC error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    CEB          :1;       // bit  18     (R/W) Command end bit error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    CIE          :1;       // bit  19     (R/W) Command index error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    DTO          :1;       // bit  20     (R/W) Data timeout error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    DCRC         :1;       // bit  21     (R/W) Data CRC Error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    DEB          :1;       // bit  22     (R/W) Data End Bit error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t                 :1;       // bit  23     (R)   Reserved
                uint32_t    ACE          :1;       // bit  24     (R/W) Auto CMD12 error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    ADMAE        :1;       // bit  25     (R/W) ADMA Error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t                 :2;       // bit  26,27  (R)   Reserved
                uint32_t    CERR         :1;       // bit  28     (R/W) Card error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t    BADA         :1;       // bit  29     (R/W) Bad access to data space
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t                 :2;       // bits 30,31  (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } STAT_reg_t;
        
        /* SD_IE (offset = 0x234) [reset = 0x0] */
        typedef union
        {                                          /* Interrupt Enable Register
                                                     */
            struct
            {
                uint32_t    CC_ENABLE    :1;       // bit  0      (R/W) Command completed interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    TC_ENABLE    :1;       // bit  1      (R/W) Transfer completed interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BGE_ENABLE   :1;       // bit  2      (R/W) Block gap event interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DMA_ENABLE   :1;       // bit  3      (R/W) DMA interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BWR_ENABLE   :1;       // bit  4      (R/W) Buffer write ready interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BRR_ENABLE   :1;       // bit  5      (R/W) Buffer read ready interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CINS_ENABLE  :1;       // bit  6      (R/W) Card Insertion Interrupt Enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CREM_ENABLE  :1;       // bit  7      (R/W) Card Removal interrupt Enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CIRQ_ENABLE  :1;       // bit  8      (R/W) Card interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    OBI_ENABLE   :1;       // bit  9      (R/W) Out-of-band interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BSR_ENABLE   :1;       // bit  10     (R/W) Boot Status Interrupt Enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :4;       // bits 11..14 (R)   Reserved
                uint32_t    NULL_        :1;       // bit  15     (R)   Fixed to 0
                uint32_t    CTO_ENABLE   :1;       // bit  16     (R/W) Command timeout error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CCRC_ENABLE  :1;       // bit  17     (R/W) Command CRC error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CEB_ENABLE   :1;       // bit  18     (R/W) Command end bit error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CIE_ENABLE   :1;       // bit  19     (R/W) Command index error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DTO_ENABLE   :1;       // bit  20     (R/W) Data timeout error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DCRC_ENABLE  :1;       // bit  21     (R/W) Data CRC error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DEB_ENABLE   :1;       // bit  22     (R/W) Data end bit error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :1;       // bit  23     (R)   Reserved
                uint32_t    ACE_ENABLE   :1;       // bit  24     (R/W) Auto CMD12 error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    ADMA_ENABLE  :1;       // bit  25     (R/W) ADMA error interrupt Enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :2;       // bit  26,27  (R)   Reserved
                uint32_t    CERR_ENABLE  :1;       // bit  28     (R/W) Card error interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BADA_ENABLE  :1;       // bit  29     (R/W) Bad access to data space interrupt enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :2;       // bits 30,31  (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IE_reg_t;
        
        /* SD_ISE (offset = 0x238) [reset = 0x0] */
        typedef union
        {                                          /* Interrupt Signal Enable Register
                                                     */
            struct
            {
                uint32_t    CC_SIGEN     :1;       // bit  0      (R/W) Command completed signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    TC_SIGEN     :1;       // bit  1      (R/W) Transfer completed signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BGE_SIGEN    :1;       // bit  2      (R/W) Block gap event signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DMA_SIGEN    :1;       // bit  3      (R/W) DMA signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BWR_SIGEN    :1;       // bit  4      (R/W) Buffer write ready signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BRR_SIGEN    :1;       // bit  5      (R/W) Buffer read ready signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CINS_SIGEN   :1;       // bit  6      (R/W) Card Insertion signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CREM_SIGEN   :1;       // bit  7      (R/W) Card Removal signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CIRQ_SIGEN   :1;       // bit  8      (R/W) Card interrupt signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    OBI_SIGEN    :1;       // bit  9      (R/W) Out-of-band interrupt signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BSR_SIGEN    :1;       // bit  10     (R/W) Boot Status signal status enable
                                                   //                  [ 0x0 = Disable;
                                                   //                    0x1 = Enable ]
                uint32_t                 :4;       // bits 11..14 (R)   Reserved
                uint32_t    NULL_        :1;       // bit  15     (R)   Fixed to 0
                uint32_t    CTO_SIGEN    :1;       // bit  16     (R/W) Command timeout error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CCRC_SIGEN   :1;       // bit  17     (R/W) Command CRC error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CEB_SIGEN    :1;       // bit  18     (R/W) Command end bit error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    CIE_SIGEN    :1;       // bit  19     (R/W) Command index error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DTO_SIGEN    :1;       // bit  20     (R/W) Data timeout error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DCRC_SIGEN   :1;       // bit  21     (R/W) Data CRC error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    DEB_SIGEN    :1;       // bit  22     (R/W) Data end bit error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :1;       // bit  23     (R)   Reserved
                uint32_t    ACE_SIGEN    :1;       // bit  24     (R/W) Auto CMD12 error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    ADMA_SIGEN   :1;       // bit  25     (R/W) ADMA error signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :2;       // bit  26,27  (R)   Reserved
                uint32_t    CERR_SIGEN   :1;       // bit  28     (R/W) Card error interrupt signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t    BADA_SIGEN   :1;       // bit  29     (R/W) Bad access to data space interrupt signal status enable
                                                   //                   [ 0x0 = Disable;
                                                   //                     0x1 = Enable ]
                uint32_t                 :2;       // bits 30,31  (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ISE_reg_t;
        
        /* SD_AC12 (offset = 0x23C) [reset = 0x0] */
        typedef union
        {                                          /* Auto CMD12 Error Register
                                                     */
            struct
            {
                uint32_t    ACNE         : 1;      // bit  0      (R) Auto CMD12 not executed
                                                   //                 [ 0x0 = No error;
                                                   //                   0x1 = Error occurred ]
                uint32_t    ACTO         : 1;      // bit  1      (R) Auto CMD12 timeout error
                                                   //                 [ 0x0 = No error;
                                                   //                   0x1 = Error occurred ]
                uint32_t    ACCE         : 1;      // bit  2      (R) Auto CMD12 CRC error
                                                   //                 [ 0x0 = No error;
                                                   //                   0x1 = Error occurred ]
                uint32_t    ACEB         : 1;      // bit  3      (R) Auto CMD12 end bit error
                                                   //                 [ 0x0 = No error;
                                                   //                   0x1 = Error occurred ]
                uint32_t    ACIE         : 1;      // bit  4      (R) Auto CMD12 index error
                                                   //                 [ 0x0 = No error;
                                                   //                   0x1 = Error occurred ]
                uint32_t                 : 2;      // bits 5..6   (R) Reserved
                uint32_t    ONI          : 1;      // bit  7      (R) Command not issue by auto CMD12 error
                                                   //                 [ 0x0 = No error;
                                                   //                   0x1 = Error occurred ]
                uint32_t                 :24;      // bits 8..31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } AC12_reg_t;
        
        /* SD_CAPA (offset = 0x240) [reset = 0x0] */
        typedef union
        {                                          /* Capabilities Register
                                                     */
            struct
            {
                uint32_t    TCF          :6;       // bits 0..5   (R) Timeout clock frequency
                                                   //                 Base timeout clock frequency in kHz/MHz
                uint32_t                 :1;       // bits 6      (R) Reserved
                uint32_t    TCU          :1;       // bit  7      (R) Timeout clock unit
                                                   //                 [ 0x0 = kHz;
                                                   //                   0x1 = MHz ]
                uint32_t    BCF          :1;       // bit  8..13  (R) Base clock frequency
                                                   //                 SD clock base frequency in MHz
                uint32_t                 :1;       // bits 14,15  (R) Reserved
                uint32_t    MBL          :2;       // bits 16..17 (R) Maximum block length [see e_MBL]
                uint32_t                 :1;       // bit  18     (R) Reserved
                uint32_t    AD2S         :1;       // bit  19     (R) ADMA2 support
                                                   //                 [ 0x0 = Not supported;
                                                   //                   0x1 = Supported ]
                uint32_t                 :1;       // bit  20     (R) Reserved
                uint32_t    HSS          :1;       // bit  21     (R) High-speed support
                                                   //                 [ 0x0 = Not supported;
                                                   //                   0x1 = Supported ]
                uint32_t    DS           :1;       // bit  22     (R) DMA support
                                                   //                 [ 0x0 = Not supported;
                                                   //                   0x1 = Supported ]
                uint32_t    SRS          :1;       // bit  23     (R) Suspend/resume support
                                                   //                 [ 0x0 = Not supported;
                                                   //                   0x1 = Supported ]
                uint32_t    VS33         :1;       // bit  24     (R/W) Voltage support 3.3V
                                                   //                   [ 0x0 = Not supported;
                                                   //                     0x1 = Supported ]
                uint32_t    VS30         :1;       // bit  25     (R/W) Voltage support 3.0V
                                                   //                   [ 0x0 = Not supported;
                                                   //                     0x1 = Supported ]
                uint32_t    VS18         :1;       // bit  26     (R/W) Voltage support 1.8V
                                                   //                   [ 0x0 = Not supported;
                                                   //                     0x1 = Supported ]
                uint32_t                 :1;       // bit  27     (R) Reserved
                uint32_t    BUS_64BIT    :1;       // bit  28     (R/W) 64 Bit System Bus Support
                                                   //                   [ 0x0 = Not supported;
                                                   //                     0x1 = Supported ]
                uint32_t                 :3;       // bits 29..31 (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CAPA_reg_t;
        
        /* Enums for multi-value fields */
        enum e_MBL : uint32_t
        {
            /*  Maximum block length supported by controller
             *  Determines largest single block that can be transferred
             */
            MBL_512        = 0x0,  // 512 bytes maximum block length
            MBL_1024       = 0x1,  // 1024 bytes maximum block length
            MBL_2048       = 0x2   // 2048 bytes maximum block length
        };
        
        /* SD_CUR_CAPA (offset = 0x248) [reset = 0x0] */
        typedef union
        {                                          /* Current Capabilities Register
                                                     */
            struct
            {
                uint32_t    CUR_3V3      :8;       // bits 0..7   (R/W) Maximum current for 3.3V
                                                   //                   Maximum current in mA at 3.3V
                uint32_t    CUR_3V0      :8;       // bits 8..15  (R/W) Maximum current for 3.0V
                                                   //                   Maximum current in mA at 3.0V
                uint32_t    CUR_1V8      :8;       // bits 16..23 (R/W) Maximum current for 1.8V
                                                   //                   Maximum current in mA at 1.8V
                uint32_t                 :8;       // bits 24..31 (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } CUR_CAPA_reg_t;
        
        /* SD_FE (offset = 0x250) [reset = 0x0] */
        typedef union
        {                                          /* Force Event Register
                                                     */
            struct
            {
                uint32_t    FE_ACNE      :1;       // bit  0      (W) Force Event Auto CMD12 not executed
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_ACTO      :1;       // bit  1      (W) Force Event Auto CMD12 timeout error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_ACCE      :1;       // bit  2      (W) Force Event Auto CMD12 CRC error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_ACEB      :1;       // bit  3      (W) Force Event Auto CMD12 end bit error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_ACIE      :1;       // bit  4      (W) Force Event Auto CMD12 index error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t                 :2;       // bits 5..6   (R) Reserved
                uint32_t    FE_CNI       :1;       // bit  7      (W) Force Event Command not issue by Auto CMD12 error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t                 :8;       // bits 8..15  (R) Reserved
                uint32_t    FE_CTO       :1;       // bit  16     (W) Force Event Command Timeout error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_CCRC      :1;       // bit  17     (W) Force Event Command CRC error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_CEB       :1;       // bit  18     (W) Force Event Command end bit error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_CIE       :1;       // bit  19     (W) Force Event Command index error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_DTO       :1;       // bit  20     (W) Force Event Data timeout error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ] 
                uint32_t    FE_DCRC      :1;       // bit  21     (W) Force Event Data CRC error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_DEB       :1;       // bit  22     (W) Force Event Data End Bit error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t                 :1;       // bit  23     (R) Reserved
                uint32_t    FE_ACE       :1;       // bit  24     (W) Force Event Auto CMD12 error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_ADMAE     :1;       // bit  25     (W) Force Event ADMA error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t                 :2;       // bit  26,27  (R) Reserved
                uint32_t    FE_CERR      :1;       // bit  28     (W) Force Event Card error
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t    FE_BADA      :1;       // bit  29     (W) Force Event Bad access to data space
                                                   //                 [ 0x0 = No effect;
                                                   //                   0x1 = Force event ]
                uint32_t                 :2;       // bits 30,31  (R) Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } FE_reg_t;

        /* SD_ADMAES (offset = 0x254) [reset = 0x0] */
        typedef union
        {                                          /* ADMA Error Status Register
                                                     */
            struct
            {
                uint32_t    AES          : 2;      // bits 0..1   (R/W) ADMA Error State [see e_AES]
                uint32_t    LME          : 1;      // bit  2      (W)   ADMA Length Mismatch Error
                                                   //                   [ 0x0 = No error;
                                                   //                     0x1 = Error occurred ]
                uint32_t                 :29;      // bits 3..31  (R)   Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ADMAES_reg_t;
        
        /* Enums for multi-value fields */
        enum e_AES : uint32_t
        {
            /*  ADMA Error State indicates current state when error occurred
             *  Helps diagnose ADMA transfer failures
             */
            AES_ST_STOP    = 0x0,  // Stop DMA (error occurred in idle state)
            AES_ST_FDS     = 0x1,  // Fetch Descriptor (error during descriptor fetch)
            AES_RESERVED   = 0x2,  // Never set (reserved value)
            AES_ST_TFR     = 0x3   // Transfer Data (error during data transfer)
        };
        
        /* SD_ADMASAL (offset = 0x258) [reset = 0x0] */
        typedef union
        {                                          /* ADMA System Address Low Register
                                                     */
            struct
            {
                uint32_t    ADMA_A32B    :32;      // bits 0..31  (R/W) ADMA System Address Low bits
                                                   //                   Lower 32 bits of ADMA system address
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ADMASAL_reg_t;
        
        /* SD_ADMASAH (offset = 0x25C) [reset = 0x0] */
        typedef union
        {                                          /* ADMA System Address High Register
                                                     */
            struct
            {
                uint32_t    ADMA_A32B    :32;      // bits 0..31  (R/W) ADMA System Address High bits
                                                   //                   Upper 32 bits of ADMA system address
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ADMASAH_reg_t;
        
        /* SD_REV (offset = 0x2FC) [reset = 0x31010000] */
        typedef union
        {                                          /* Revision Register
                                                     */
            struct
            {
                uint32_t    SIS          : 1;      // bit  0      (R) Slot Interrupt Status
                                                   //                 [ 0x0 = No slot interrupt;
                                                   //                   0x1 = Slot interrupt pending ]
                uint32_t                 :15;      // bits 1..15  (R) Reserved
                uint32_t    SREV         : 8;      // bits 16..23 (R) Specification Version Number
                                                   //                 SD Host Controller Spec version
                uint32_t    VREV         : 8;      // bits 24..31 (R) Vendor Version Number
                                                   //                 Vendor-specific version number
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } REV_reg_t;
      

        struct AM335x_MMCHS_Type
        {     
            __R    uint32_t         RESERVED[68];                                                                                 
            __RW   SYSCONFIG_reg_t  SYSCONFIG;        // (0x110)  
            __R    SYSSTATUS_reg_t  SYSSTATUS;        // (0x114)
            __R    uint32_t         RESERVED1[3];
            __RW   CSRE_reg_t       CSRE;             // (0x124)
            __RW   SYSTEST_reg_t    SYSTEST;          // (0x128)
            __RW   CON_reg_t        CON;              // (0x12C)
            __RW   PWCNT_reg_t      PWCNT;            // (0x130)
            __R    uint32_t         RESERVED2[51];
            __R    SDMASA_reg_t     SDMASA;           // (0x200)
            __RW   BLK_reg_t        BLK;              // (0x204)
            __RW   ARG_reg_t        ARG;              // (0x208)
            __RW   CMD_reg_t        CMD;              // (0x20C)
            __R    RSP10_reg_t      RSP10;            // (0x210)
            __R    RSP32_reg_t      RSP32;            // (0x214)
            __R    RSP54_reg_t      RSP54;            // (0x218)
            __R    RSP76_reg_t      RSP76;            // (0x21C)
            __RW   DATA_reg_t       DATA;             // (0x220)
            __R    PSTATE_reg_t     PSTATE;           // (0x224)
            __RW   HCTL_reg_t       HCTL;             // (0x228)
            __RW   SYSCTL_reg_t     SYSCTL;           // (0x22C)
            __RW   STAT_reg_t       STAT;             // (0x230)
            __RW   IE_reg_t         IE;               // (0x234)
            __RW   ISE_reg_t        ISE;              // (0x238)
            __R    AC12_reg_t       AC12;             // (0x23C)
            __RW   CAPA_reg_t       CAPA;             // (0x240)
            __R    uint32_t         RESERVED3[1];
            __RW   CUR_CAPA_reg_t   CUR_CAPA;         // (0x248) 
            __R    uint32_t         RESERVED4[1];           
            __W    FE_reg_t         FE;               // (0x250)
            __RW   ADMAES_reg_t     ADMAES;           // (0x254)
            __RW   ADMASAL_reg_t    ADMASAL;          // (0x258)
            __RW   ADMASAH_reg_t    ADMASAH;          // (0x25C)
            __R    uint32_t         RESERVED5[39];
            __R    REV_reg_t        REV;              // (0x2FC)            
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
