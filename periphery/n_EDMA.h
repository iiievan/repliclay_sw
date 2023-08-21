#ifndef __N_EDMA_H
#define __N_EDMA_H

#include <stdint.h>
#include "utils.h"

namespace n_EDMA
{  
/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_EDMA3CC_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t PID    :16;         // bit: 0..15   (R) .  
            uint32_t        :16;         // bit: 16..31   Reserved.         
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } PIDCC_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t    NUM_DMACH   :3;         // bit: 0..2      (R) .  
            uint32_t                :1;         // bit: 3         (R) . 
            uint32_t    NUM_QDMACH  :3;         // bit: 4..6      (R) . 
            uint32_t                :1;         // bit: 7         (R) . 
            uint32_t    NUM_INTCH   :3;         // bit: 8..10     (R) . 
            uint32_t                :1;         // bit: 11        (R) . 
            uint32_t    NUM_PAENTRY :3;         // bit: 12..14    (R) . 
            uint32_t                :1;         // bit: 15        (R) . 
            uint32_t    NUM_EVQUE   :3;         // bit: 16..18    (R) . 
            uint32_t                :1;         // bit: 19        (R) . 
            uint32_t    NUM_REGN    :2;         // bit: 20,21     (R) . 
            uint32_t                :2;         // bit: 22,23     (R) . 
            uint32_t    CHMAP_EXIST :1;         // bit: 24        (R) . 
            uint32_t    MP_EXIST    :1;         // bit: 25        (R) . 
            uint32_t                :6;         // bit: 26..31   Reserved.         
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } CCCFG_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t                  :2;         // bit: 0,1     Reserved.
            uint32_t    IDLEMODE      :2;         // bit: 2,3     (RW)    
            uint32_t                  :28;        // bit: 4..31   Reserved.         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } SYSCONFIGCC_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t              :5;         // bit: 0..4        Reserved.
            uint32_t    PAENTRY   :9;         // bit: 5..13       (RW) Bitfield description.  
            uint32_t              :18;        // bit: 14..31      Reserved.         
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } DCHMAP_reg_t;
    
    /*! @brief      Each QDMA channel in EDMA3CC can be associated with any PaRAM set available on the device.
    *   @details    Furthermore, the specific trigger word (0-7) of the PaRAM set can be programmed. The PaRAM set
    *               association and trigger word for every QDMA channel register is configurable using the QDMA channel
    *               map register (QCHMAPn). At reset the QDMA channel map registers for all QDMA channels point to
    *               PaRAM set 0. If an application makes use of both a DMA channel that points to PaRAM set 0 and any
    *               QDMA channels, ensure that QCHMAP is programmed appropriately to point to a different PaRAM entry.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            uint32_t                  :2;         // bit: 0,1     Reserved
            uint32_t    TRWORD        :3;         // bit: 2..4    (RW) Points to the specific trigger word of the PaRAM set defined by PAENTRY.
                                                  //                   A write to the trigger word results in a QDMA event being recognized.
            uint32_t    PAENTRY       :9;         // bit: 5..13   (RW) PAENTRY points to the PaRAM set number for QDMA channel .
                                                  //                  [0x0 = Parameter entry 0 through 255, from 0 to FFh.
                                                  //                   0x1 = Reserved, from 100h to 1FFh. Always write 0 to this bit. Writes
                                                  //                         of 1 to this bit are not supported and attempts to do so may result in undefine behavior.]
            uint32_t                  :18;        // bit: 14..31  Reserved.         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } QCHMAP_reg_t;
    
    /*! @brief      The DMA channel queue number register (DMAQNUMn) allows programmability of each of the 64 DMA
    *               channels in the EDMA3CC to submit its associated synchronization event to any event queue in the EDMA3CC 
    *   @details   At reset, all channels point to event queue 0. Because the event queues in EDMA3CC have a
    * fixed association to the transfer controllers, that is, Q0 TRs are submitted to TC0, Q1 TRs are submitted
    * to TC1, etc., by programming DMAQNUM for a particular DMA channel also dictates which transfer
    * controller is utilized for the data movement (or which EDMA3TC receives the TR request).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            /**  DMA queue number. Contains the event queue number to be used for the corresponding
                 DMA channel. Programming DMAQNUM for an event queue number to a value more then the number of queues available in the EDMA3CC results
                in undefined behavior. 
            **/             
            uint32_t    E0  :3;     // bit: 0..2     (RW) . On DMAQNUM[0], E[2] to E[0] is E0.
                                    //                      On DMAQNUM[1], E[2] to E[0] is E8.
                                    //                      On DMAQNUM[2], E[2] to E[0] is E16.
                                    //                      On DMAQNUM[3], E[2] to E[0] is E24.
                                    //                      On DMAQNUM[4], E[2] to E[0] is E32.
                                    //                      On DMAQNUM[5], E[2] to E[0] is E40.
                                    //                      On DMAQNUM[6], E[2] to E[0] is E48.
                                    //                      On DMAQNUM[7], E[2] to E[0] is E56.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 3        Reserved.
            uint32_t    E1  :3;     // bit: 4..6     (RW) . On DMAQNUM[0], E[6] to E[4] is E1.
                                    //                      On DMAQNUM[1], E[6] to E[4] is E9.
                                    //                      On DMAQNUM[2], E[6] to E[4] is E17.
                                    //                      On DMAQNUM[3], E[6] to E[4] is E25.
                                    //                      On DMAQNUM[4], E[6] to E[4] is E33.
                                    //                      On DMAQNUM[5], E[6] to E[4] is E41.
                                    //                      On DMAQNUM[6], E[6] to E[4] is E49.
                                    //                      On DMAQNUM[7], E[6] to E[4] is E57.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 7        Reserved                        
            uint32_t    E2  :3;     // bit: 8..10    (RW) . On DMAQNUM[0], E[10] to E[8] is E2.
                                    //                      On DMAQNUM[1], E[10] to E[8] is E10.
                                    //                      On DMAQNUM[2], E[10] to E[8] is E18.
                                    //                      On DMAQNUM[3], E[10] to E[8] is E26.
                                    //                      On DMAQNUM[4], E[10] to E[8] is E34.
                                    //                      On DMAQNUM[5], E[10] to E[8] is E42.
                                    //                      On DMAQNUM[6], E[10] to E[8] is E50.
                                    //                      On DMAQNUM[7], E[10] to E[8] is E58.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 11       Reserved
            uint32_t    E3  :3;     // bit: 12..14   (RW) . On DMAQNUM[0], E[14] to E[12] is E3.
                                    //                      On DMAQNUM[1], E[14] to E[12] is E11.
                                    //                      On DMAQNUM[2], E[14] to E[12] is E19.
                                    //                      On DMAQNUM[3], E[14] to E[12] is E27.
                                    //                      On DMAQNUM[4], E[14] to E[12] is E35.
                                    //                      On DMAQNUM[5], E[14] to E[12] is E43.
                                    //                      On DMAQNUM[6], E[14] to E[12] is E51.
                                    //                      On DMAQNUM[7], E[14] to E[12] is E59.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 15       Reserved
            uint32_t    E4  :3;     // bit: 16..18   (RW) . On DMAQNUM[0], E[18] to E[16] is E4.
                                    //                      On DMAQNUM[1], E[18] to E[16] is E12.
                                    //                      On DMAQNUM[2], E[18] to E[16] is E20.
                                    //                      On DMAQNUM[3], E[18] to E[16] is E28.
                                    //                      On DMAQNUM[4], E[18] to E[16] is E36.
                                    //                      On DMAQNUM[5], E[18] to E[16] is E44.
                                    //                      On DMAQNUM[6], E[18] to E[16] is E52.
                                    //                      On DMAQNUM[7], E[18] to E[16] is E60.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 19       Reserved
            uint32_t    E5  :3;     // bit: 20..21   (RW) . On DMAQNUM[0], E[22] to E[20] is E5.
                                    //                      On DMAQNUM[1], E[22] to E[20] is E13.
                                    //                      On DMAQNUM[2], E[22] to E[20] is E21.
                                    //                      On DMAQNUM[3], E[22] to E[20] is E29.
                                    //                      On DMAQNUM[4], E[22] to E[20] is E37.
                                    //                      On DMAQNUM[5], E[22] to E[20] is E45.
                                    //                      On DMAQNUM[6], E[22] to E[20] is E53.
                                    //                      On DMAQNUM[7], E[22] to E[20] is E61.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 23       Reserved
            uint32_t    E6  :3;     // bit: 24..26   (RW) . On DMAQNUM[0], E[26] to E[24] is E6.
                                    //                      On DMAQNUM[1], E[26] to E[24] is E14.
                                    //                      On DMAQNUM[2], E[26] to E[24] is E22.
                                    //                      On DMAQNUM[3], E[26] to E[24] is E30.
                                    //                      On DMAQNUM[4], E[26] to E[24] is E38.
                                    //                      On DMAQNUM[5], E[26] to E[24] is E46.
                                    //                      On DMAQNUM[6], E[26] to E[24] is E54.
                                    //                      On DMAQNUM[7], E[26] to E[24] is E62.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 27       Reserved.
            uint32_t    E7  :3;     // bit: 28..30   (RW) . On DMAQNUM[0], E[30] to E[28] is E7.
                                    //                      On DMAQNUM[1], E[30] to E[28] is E15.
                                    //                      On DMAQNUM[2], E[30] to E[28] is E23.
                                    //                      On DMAQNUM[3], E[30] to E[28] is E39.
                                    //                      On DMAQNUM[4], E[30] to E[28] is E47.
                                    //                      On DMAQNUM[5], E[30] to E[28] is E45.
                                    //                      On DMAQNUM[6], E[30] to E[28] is E55.
                                    //                      On DMAQNUM[7], E[30] to E[28] is E63.  [see e_DMA_EVENT]
            uint32_t        :1;     // bit: 31       Reserved        
        } b;                        // Structure used for bit access 
        uint32_t  reg;              // Type used for register access 
    } DMAQNUM_reg_t;
    
    enum e_DMA_QUEUE : uint32_t
    {
        EVENT_Q0 = 0x00,    // Event n is queued on Q0.
        EVENT_Q1 = 0x01,    // Event n is queued on Q1.
        EVENT_Q2 = 0x02     // Event n is queued on Q2.
                            // 0x03 = Reserved, from 3h to 7h. Always write 0 to this bit; writes of 1
                            // to this bit are not supported and attempts to do so may result in
                            // undefined behavior.
                            // 7h = Reserved. Always write 0 to this bit; writes of 1 to this bit are
                            // not supported and attempts to do so may result in undefined
                            // behavior.
    };
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
          
            uint32_t    E0  :3;    // bit: 0..2     (RW) .
            uint32_t        :1;    // bit: 3        Reserved.
            uint32_t    E1  :3;    // bit: 4..6     (RW) .
            uint32_t        :1;    // bit: 7        Reserved
            uint32_t    E2  :3;    // bit: 8..10    (RW) .
            uint32_t        :1;    // bit: 11       Reserved
            uint32_t    E3  :3;    // bit: 12..14   (RW) .
            uint32_t        :1;    // bit: 15       Reserved
            uint32_t    E4  :3;    // bit: 16..18   (RW) .
            uint32_t        :1;    // bit: 19       Reserved
            uint32_t    E5  :3;    // bit: 20..21   (RW) .
            uint32_t        :1;    // bit: 23       Reserved
            uint32_t    E6  :3;    // bit: 24..26   (RW) .
            uint32_t        :1;    // bit: 27       Reserved.
            uint32_t    E7  :3;    // bit: 28..30   (RW) .
            uint32_t        :1;    // bit: 31       Reserved           
        } b;                       // Structure used for bit access 
        uint32_t  reg;             // Type used for register access 
    } QDMAQNUM_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    PRIQ0      :3;        // bit: 0..2    (RW) . 
            uint32_t               :1;        // bit: 3        Reserved
            uint32_t    PRIQ1      :3;        // bit: 4..6    (RW) .
            uint32_t               :1;        // bit: 7        Reserved.    
            uint32_t    PRIQ2      :3;        // bit: 8..10   (RW) .
            uint32_t               :21;       // bit: 11..31   Reserved.
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } QUEPRI_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;        // bit: 0..31        (R) .         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;        // bit: 0..31      (R) .        
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;        // bit: 0..31    (W) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMCR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;        // bit: 0..31        (W) . 
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMCRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :8;         // bit: 0..7        (R) .
            uint32_t            :24;        // bit: 8..31       (R) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEMR_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7        (W) .
            uint32_t            :24;        // bit: 8..31       (R) .        
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEMCR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    QTHRXCD0      :1;         // bit: 0        (R) .
            uint32_t    QTHRXCD1      :1;         // bit: 1        (R) 
            uint32_t    QTHRXCD2      :1;         // bit: 2        (R) 
            uint32_t                  :13;        // bit: 3..15    (R) 
            uint32_t    TCCERR        :1;         // bit: 16       (R)  
            uint32_t                  :15;        // bit: 17..31   (R) .         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } CCERR_reg_t;

    enum e_CCERR_flags: uint32_t
    {       
        F_QTHRXCD0 = BIT(0),
        F_QTHRXCD1 = BIT(1),
        F_QTHRXCD2 = BIT(2),
        F_TCCERR   = BIT(16)
    };
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    QTHRXCD0      :1;         // bit: 0        (W) .
            uint32_t    QTHRXCD1      :1;         // bit: 1        (W) 
            uint32_t    QTHRXCD2      :1;         // bit: 2        (W) 
            uint32_t                  :13;        // bit: 3..15    (R) 
            uint32_t    TCCERR        :1;         // bit: 16       (W)  
            uint32_t                  :15;        // bit: 17..31   (R) .         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } CCERRCLR_reg_t;
 
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t    EVAL      :1;         // bit: 0       (W).  
            uint32_t              :31;        // bit: 1..31   Reserved.         
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } EEVAL_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access  
    } DRAEH_reg_t;
       
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :8;         // bit: 0..7       (RW) .  
            uint32_t            :24;        // bit: 8..31      Reserved.
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } QRAE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    ENUM      :6;         // bit: 0..5      (R) .  
            uint32_t    ETYPE     :2;         // bit: 6,7       (R) .
            uint32_t              :24;        // bit: 8..31     Reserved.
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } QE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    STRTPTR     :4;         // bit: 0..3      (R) .  
            uint32_t                :4;         // bit: 4..7      Reserved.
            uint32_t    NUMVAL      :5;         // bit: 8..12     (R) .  
            uint32_t                :3;         // bit: 13..15    Reserved.
            uint32_t    WM          :5;         // bit: 16..20    (R) .  
            uint32_t                :3;         // bit: 21..23    Reserved.
            uint32_t    THRXCD      :1;         // bit: 24        (R) .
            uint32_t                :7;         // bit: 25..31     Reserved.
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access  
    } QSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    Q0      :5;         // bit: 0..4      (RW) .  
            uint32_t            :3;         // bit: 5..7      Reserved.
            uint32_t    Q1      :5;         // bit: 8..12     (RW) .  
            uint32_t            :3;         // bit: 13..15    Reserved.
            uint32_t    Q2      :5;         // bit: 16..20    (RW) .  
            uint32_t            :11;        // bit: 21..31    Reserved.       
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QWMTHRA_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    EVTACTV      :1;         // bit: 0        (R) . 
            uint32_t    QEVTACTV     :1;         // bit: 1        (R) .
            uint32_t    TRACTV       :1;         // bit: 2        (R) .
            uint32_t                 :1;         // bit: 3        Reserved.
            uint32_t    ACTV         :1;         // bit: 4        (R) . 
            uint32_t                 :3;         // bit: 5..7     Reserved.
            uint32_t    COMPACTV     :6;         // bit: 8..13    (R) .
            uint32_t                 :2;         // bit: 14,15    Reserved. 
            uint32_t    QUEACTV0     :1;         // bit: 16       (R) . 
            uint32_t    QUEACTV1     :1;         // bit: 17       (R) .
            uint32_t    QUEACTV2     :1;         // bit: 18       (R) .
            uint32_t                 :13;        // bit: 19..31   Reserved.        
        } b;                                     // Structure used for bit access 
        uint32_t  reg;                           // Type used for register access 
    } CCSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    FADDR      :32;         // bit: 0..31       (R) .          
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } MPFAR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    UXE      :1;         // bit: 0        (R) .
            uint32_t    UWE      :1;         // bit: 1        (R) .
            uint32_t    URE      :1;         // bit: 2        (R) .
            uint32_t    SXE      :1;         // bit: 3        (R) .
            uint32_t    SWE      :1;         // bit: 4        (R) .
            uint32_t    SRE      :1;         // bit: 5        (R) .
            uint32_t             :1;         // bit: 6..8     Reserved. 
            uint32_t    FID      :4;         // bit: 9..12    (R) . 
            uint32_t             :19;        // bit: 13..31   Reserved.         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } MPFSR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    MPFCLR      :1;         // bit: 0       (W) .  
            uint32_t                :31;        // bit: 1..31   Reserved.         
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } MPFCR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x676] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    UX      :1;         // bit: 0        (RW) Bitfield description. 
            uint32_t    UW      :1;         // bit: 1        (RW) Bitfield description.
            uint32_t    UR      :1;         // bit: 2        (RW) Bitfield description.
            uint32_t    SX      :1;         // bit: 3        (RW) Bitfield description. 
            uint32_t    SW      :1;         // bit: 4        (RW) Bitfield description. 
            uint32_t    SR      :1;         // bit: 5        (RW) Bitfield description.
            uint32_t            :3;         // bit: 6..8     Reserved.
            uint32_t    EXT     :1;         // bit: 9        (RW) Bitfield description. 
            uint32_t    AIDm    :6;         // bit: 10..15   (RW) Bitfield description.
            uint32_t            :16;        // bit: 16..31   Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } MPPAG_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x676] */ 
    typedef union 
    { 
        struct
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    UX      :1;         // bit: 0        (RW) Bitfield description. 
            uint32_t    UW      :1;         // bit: 1        (RW) Bitfield description.
            uint32_t    UR      :1;         // bit: 2        (RW) Bitfield description.
            uint32_t    SX      :1;         // bit: 3        (RW) Bitfield description. 
            uint32_t    SW      :1;         // bit: 4        (RW) Bitfield description. 
            uint32_t    SR      :1;         // bit: 5        (RW) Bitfield description.
            uint32_t            :3;         // bit: 6..8     Reserved.
            uint32_t    EXT     :1;         // bit: 9        (RW) Bitfield description. 
            uint32_t    AIDm    :6;         // bit: 10..15   (RW) Bitfield description.
            uint32_t            :16;        // bit: 16..31   Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } MPPA_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ER_reg_t;
    
        /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ERH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ECRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (RW) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } ESR_reg_t;
 
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31       (RW) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ESRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (RW) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } CER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } CERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } EER_reg_t;
    
        /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } EERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } EECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } EECRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } EESR_reg_t;
    
/*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31       (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } EESRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } SER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } SERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } SECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } SECRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In_      :32;        // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } IERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IECR_reg_t;
  
/*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IECRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IESR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IESRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) Interrupt pending for TCC = 0 to 31.
                                             //                      [0x0 = Interrupt transfer completion code is not detected or was cleared. 
                                             //                       0x1 = Interrupt transfer completion code is detected (In = 1, n = EDMA3TC[2:0]).]           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IPR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) Interrupt pending for TCC = 32 to 63.
                                             //                      [0x0 = Interrupt transfer completion code is not detected or was cleared. 
                                             //                       0x1 = Interrupt transfer completion code is detected (In = 1, n = EDMA3TC[2:0]).]         
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } IPRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ICR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ICRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    EVAL      :1;         // bit: 0       (W) .  
            uint32_t              :31;        // bit: 1..31   Reserved.         
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } IEVAL_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEESR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QSER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (W) . 
            uint32_t            :24;        // bit: 8..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } QSECR_reg_t;

/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_EDMA3TC_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/
 
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PID      :16;   // bit: 0..15     (R) . 
            uint32_t             :16;   // bit: 16..31    Reserved.          
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access
    } PIDTC_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    FIFOSIZE       :3;   // bit: 0..2     (R) . 
            uint32_t                   :1;   // bit: 3        Reserved 
            uint32_t    BUSWIDTH       :2;   // bit: 4,5      (R) .
            uint32_t                   :2;   // bit: 6,7      Reserved 
            uint32_t    DREGDEPTH      :2;   // bit: 8,9      (R) .
            uint32_t                   :22;  // bit: 10..31   Reserved.          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } TCCFG_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            uint32_t                  :2;   // bit: 0,1       Reserved. 
            uint32_t    IDLEMODE      :2;   // bit: 2,3      (RW) [ see e_SYSC_IDLEMODE ]
            uint32_t    STANDBYMODE   :2;   // bit: 4,5      (RW) [ see e_SYSC_STANDBYMODE ]
            uint32_t                  :26;  // bit: 6..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SYSCONFIGTC_reg_t;

    enum e_SYSC_IDLEMODE : uint32_t
    {
        SYSC_FORCE_IDLE     = 0x0,  // Force-idle mode:
        SYSC_NOIDLE         = 0x1,  // No-idle 
        SYSC_SMARTIDLE      = 0x2,  // Smart-idle
    };

    enum e_SYSC_STANDBYMODE : uint32_t
    {
        SYSC_FORCE_STBY     = 0x0,  // Force-standby mode;
        SYSC_NOSTBY         = 0x1,  // No-standby; 
        SYSC_SMARTSTBY      = 0x2,  // Smart-standby;
    };
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PROGBUSY      :1;   // bit: 0        (R) . 
            uint32_t    SRCACTV       :1;   // bit: 1        (R) .
            uint32_t    WSACTV        :1;   // bit: 2        (R) .
            uint32_t                  :1;   // bit: 3        Reserved.
            uint32_t    DSTACTV       :3;   // bit: 4..6     (R) .
            uint32_t                  :1;   // bit: 7..11    Reserved.
            uint32_t    DFSTRTPTR     :1;   // bit: 12,13    (R) .
            uint32_t                  :18;  // bit: 14..31   Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } TCSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    BUSERR      :1;   // bit: 0        (R) .
            uint32_t                :1;   // bit: 1        Reserved. 
            uint32_t    TRERR       :1;   // bit: 2        (R) . 
            uint32_t    MMRAERR     :1;   // bit: 3        (R) .
            uint32_t                :28;  // bit: 4..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } ERRSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    BUSERR      :1;   // bit: 0        (RW) .
            uint32_t                :1;   // bit: 1        Reserved. 
            uint32_t    TRERR       :1;   // bit: 2        (RW) . 
            uint32_t    MMRAERR     :1;   // bit: 3        (RW) .
            uint32_t                :28;  // bit: 4..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } ERREN_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    BUSERR      :1;   // bit: 0        (W) .
            uint32_t                :1;   // bit: 1        Reserved. 
            uint32_t    TRERR       :1;   // bit: 2        (W) . 
            uint32_t    MMRAERR     :1;   // bit: 3        (W) . 
            uint32_t                :28;  // bit: 4..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } ERRCLR_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    STAT      :4;   // bit: 0..3      (R) .
            uint32_t              :4;   // bit: 4..7      Reserved.
            uint32_t    TCC       :6;   // bit: 8..13     (R) .
            uint32_t              :2;   // bit: 14,15     Reserved.
            uint32_t    TCINTEN   :1;   // bit: 16        (R) .
            uint32_t    TCCHEN    :1;   // bit: 17        (R) .
            uint32_t              :14;  // bit: 18..31    Reserved.          
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access
    } ERRDET_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    EVAL      :1;   // bit: 0        (W) . 
            uint32_t              :31;  // bit: 1..31    Reserved.          
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access
    } ERRCMD_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    RDRATE      :3;   // bit: 0..2        (W) . 
            uint32_t                :29;  // bit: 3..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } RDRATE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } SAOPT_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SADDR      :32;   // bit: 0..31       (R) .         
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } SASRC_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15       (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31      (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } SACNT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t  R_BITFIELD       :32;  // bit: 0..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SADST_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } SABIDX_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SAMPPRXY_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNTRLD      :16;   // bit: 0        (R) . 
            uint32_t                 :16;   // bit: 1..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SACNTRLD_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SADDRBREF      :32;   // bit: 0..31        (R) .           
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access
    } SASRCBREF_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t   R_BITFIELD      :32;  // bit: 0..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SADSTBREF_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNTRLD      :16;   // bit: 0..15     (R) .
            uint32_t                 :16;   // bit: 16..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFCNTRLD_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t   R_BITFIELD    :32;    // bit: 0..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRCBREF_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t   DADDRBREF  :32;   // bit: 0..31        (R) .           
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFDSTBREF_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFOPT0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD    :32;  // bit: 0..32       (R) .         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRC0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .         
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFCNT0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;   // bit: 0..31        (W) .           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFDST0_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;  // bit: 0..15     (R) . 
            uint32_t    DBIDX      :16;  // bit: 16..31    (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFBIDX0_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFMPPRXY0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFOPT1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD      :32;   // bit: 0..31        Reserved.           
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access
    } DFSRC1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFCNT1_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;   // bit: 0..31       (R) .        
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFDST1_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .         
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFBIDX1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.         
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFMPPRXY1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFOPT2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD   :32;   // bit: 0..31       Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRC2_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFCNT2_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;  // bit: 0..31       (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFDST2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFBIDX2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFMPPRXY2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFOPT3_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD   :32;   // bit: 0..31       Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRC3_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFCNT3_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;     // bit: 0        (R) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFDST3_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .         
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFBIDX3_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFMPPRXY3_reg_t;
    
    struct AM335x_EDMA3CC_Type
    {                                                                                      
        __R   PIDCC_reg_t           PID;            // (0x00)  Peripheral Identification Register
        __R   CCCFG_reg_t           CCCFG;          // (0x04)  EDMA3CC Configuration Register
        __R   uint32_t              RESERVED1[2];
        __RW  SYSCONFIGCC_reg_t     SYSCONFIG;      // (0x10)  EDMA3CC System Configuration Register
        __R   uint32_t              RESERVED2[59]; 
        __RW  DCHMAP_reg_t          DCHMAP[64];     // (0x100..0x1FC) DMA Channel Mapping Register 0..63
        __RW  QCHMAP_reg_t          QCHMAP[8];      // (0x200..0x21C) QDMA Channel Mapping Register 0..7
        __R   uint32_t              RESERVED3[8]; 
        __RW  DMAQNUM_reg_t         DMAQNUM[8];     // (0x240..0x25C) DMA Queue Number Register 0..7
        __RW  QDMAQNUM_reg_t        QDMAQNUM;       // (0x260) QDMA Queue Number Register
        __R   uint32_t              RESERVED4[8];  
        __RW  QUEPRI_reg_t          QUEPRI;         // (0x284) Queue Priority Register
        __R   uint32_t              RESERVED5[30]; 
        __R   EMR_reg_t             EMR;            // (0x300) Event Missed Register
        __R   EMRH_reg_t            EMRH;           // (0x304) Event Missed Register High 
        __W   EMCR_reg_t            EMCR;           // (0x308) Event Missed Clear Register
        __W   EMCRH_reg_t           EMCRH;          // (0x30C) Event Missed Clear Register High 
        __R   QEMR_reg_t            QEMR;           // (0x310) QDMA Event Missed Register 
        __W   QEMCR_reg_t           QEMCR;          // (0x314) QDMA Event Missed Clear Register 
        __R   CCERR_reg_t           CCERR;          // (0x318) EDMA3CC Error Register 
        __W   CCERRCLR_reg_t        CCERRCLR;       // (0x31C) EDMA3CC Error Clear Register 
        __W   EEVAL_reg_t           EEVAL;          // (0x320) Error Evaluate Register
        __R   uint32_t              RESERVED6[7]; 
        __RW  DRAE_reg_t            DRAE0;          // (0x340) DMA Region Access Enable Register for Region 0    
        __RW  DRAEH_reg_t           DRAEH0;         // (0x344) DMA Region Access Enable Register High for Region 0 
        __RW  DRAE_reg_t            DRAE1;          // (0x348) DMA Region Access Enable Register for Region 1 
        __RW  DRAEH_reg_t           DRAEH1;         // (0x34C) DMA Region Access Enable Register High for Region 1
        __RW  DRAE_reg_t            DRAE2;          // (0x350) DMA Region Access Enable Register for Region 2
        __RW  DRAEH_reg_t           DRAEH2;         // (0x354) DMA Region Access Enable Register High for Region 2  
        __RW  DRAE_reg_t            DRAE3;          // (0x358) DMA Region Access Enable Register for Region 3
        __RW  DRAEH_reg_t           DRAEH3;         // (0x35C) DMA Region Access Enable Register High for Region 3
        __RW  DRAE_reg_t            DRAE4;          // (0x360) DMA Region Access Enable Register for Region 4 
        __RW  DRAEH_reg_t           DRAEH4;         // (0x364) DMA Region Access Enable Register High for Region 4
        __RW  DRAE_reg_t            DRAE5;          // (0x368) DMA Region Access Enable Register for Region 5 
        __RW  DRAEH_reg_t           DRAEH5;         // (0x36C) DMA Region Access Enable Register High for Region 5 
        __RW  DRAE_reg_t            DRAE6;          // (0x370) DMA Region Access Enable Register for Region 6
        __RW  DRAEH_reg_t           DRAEH6;         // (0x374) DMA Region Access Enable Register High for Region 6
        __RW  DRAE_reg_t            DRAE7;          // (0x378) DMA Region Access Enable Register for Region 7
        __RW  DRAEH_reg_t           DRAEH7;         // (0x37C) DMA Region Access Enable Register High for Region 7
        __RW  QRAE_reg_t            QRAE[8];        // (0x380..0x39Ñ) QDMA Region Access Enable Registers for Region 0..7
        __R   uint32_t              RESERVED7[24];  
        __R   QE_reg_t              Q0E0;           // (0x400) Event Queue 0 Entry 0 Register 
        __R   QE_reg_t              Q0E1;           // (0x404) Event Queue 0 Entry 1 Register 
        __R   QE_reg_t              Q0E2;           // (0x408) Event Queue 0 Entry 2 Register 
        __R   QE_reg_t              Q0E3;           // (0x40C) Event Queue 0 Entry 3 Register 
        __R   QE_reg_t              Q0E4;           // (0x410) Event Queue 0 Entry 4 Register 
        __R   QE_reg_t              Q0E5;           // (0x414) Event Queue 0 Entry 5 Register 
        __R   QE_reg_t              Q0E6;           // (0x418) Event Queue 0 Entry 6 Register
        __R   QE_reg_t              Q0E7;           // (0x41C) Event Queue 0 Entry 7 Register 
        __R   QE_reg_t              Q0E8;           // (0x420) Event Queue 0 Entry 8 Register 
        __R   QE_reg_t              Q0E9;           // (0x424) Event Queue 0 Entry 9 Register 
        __R   QE_reg_t              Q0E10;          // (0x428) Event Queue 0 Entry 10 Register 
        __R   QE_reg_t              Q0E11;          // (0x42C) Event Queue 0 Entry 11 Register
        __R   QE_reg_t              Q0E12;          // (0x430) Event Queue 0 Entry 12 Register 
        __R   QE_reg_t              Q0E13;          // (0x434) Event Queue 0 Entry 13 Register
        __R   QE_reg_t              Q0E14;          // (0x438) Event Queue 0 Entry 14 Register 
        __R   QE_reg_t              Q0E15;          // (0x43C) Event Queue 0 Entry 15 Register 
        __R   QE_reg_t              Q1E0;           // (0x440) Event Queue 1 Entry 0 Register   
        __R   QE_reg_t              Q1E1;           // (0x444) Event Queue 1 Entry 1 Register   
        __R   QE_reg_t              Q1E2;           // (0x448) Event Queue 1 Entry 2 Register   
        __R   QE_reg_t              Q1E3;           // (0x44C) Event Queue 1 Entry 3 Register   
        __R   QE_reg_t              Q1E4;           // (0x450) Event Queue 1 Entry 4 Register  
        __R   QE_reg_t              Q1E5;           // (0x454) Event Queue 1 Entry 5 Register   
        __R   QE_reg_t              Q1E6;           // (0x458) Event Queue 1 Entry 6 Register  
        __R   QE_reg_t              Q1E7;           // (0x45C) Event Queue 1 Entry 7 Register   
        __R   QE_reg_t              Q1E8;           // (0x460) Event Queue 1 Entry 8 Register   
        __R   QE_reg_t              Q1E9;           // (0x464) Event Queue 1 Entry 9 Register   
        __R   QE_reg_t              Q1E10;          // (0x468) Event Queue 1 Entry 10 Register  
        __R   QE_reg_t              Q1E11;          // (0x46C) Event Queue 1 Entry 11 Register 
        __R   QE_reg_t              Q1E12;          // (0x470) Event Queue 1 Entry 12 Register  
        __R   QE_reg_t              Q1E13;          // (0x474) Event Queue 1 Entry 13 Register  
        __R   QE_reg_t              Q1E14;          // (0x478) Event Queue 1 Entry 14 Register  
        __R   QE_reg_t              Q1E15;          // (0x47C) Event Queue 1 Entry 15 Register  
        __R   QE_reg_t              Q2E0;           // (0x480) Event Queue 2 Entry 0 Register   
        __R   QE_reg_t              Q2E1;           // (0x484) Event Queue 2 Entry 1 Register   
        __R   QE_reg_t              Q2E2;           // (0x488) Event Queue 2 Entry 2 Register  
        __R   QE_reg_t              Q2E3;           // (0x48C) Event Queue 2 Entry 3 Register   
        __R   QE_reg_t              Q2E4;           // (0x490) Event Queue 2 Entry 4 Register   
        __R   QE_reg_t              Q2E5;           // (0x494) Event Queue 2 Entry 5 Register   
        __R   QE_reg_t              Q2E6;           // (0x498) Event Queue 2 Entry 6 Register  
        __R   QE_reg_t              Q2E7;           // (0x49C) Event Queue 2 Entry 7 Register   
        __R   QE_reg_t              Q2E8;           // (0x4A0) Event Queue 2 Entry 8 Register   
        __R   QE_reg_t              Q2E9;           // (0x4A4) Event Queue 2 Entry 9 Register  
        __R   QE_reg_t              Q2E10;          // (0x4A8) Event Queue 2 Entry 10 Register  
        __R   QE_reg_t              Q2E11;          // (0x4AC) Event Queue 2 Entry 11 Register  
        __R   QE_reg_t              Q2E12;          // (0x4B0) Event Queue 2 Entry 12 Register 
        __R   QE_reg_t              Q2E13;          // (0x4B4) Event Queue 2 Entry 13 Register  
        __R   QE_reg_t              Q2E14;          // (0x4B8) Event Queue 2 Entry 14 Register  
        __R   QE_reg_t              Q2E15;          // (0x4BC) Event Queue 2 Entry 15 Register 
        __R   uint32_t              RESERVED8[80]; 
        __R   QSTAT_reg_t           QSTAT_0;        // (0x600) Queue Status Registers 0
        __R   QSTAT_reg_t           QSTAT_1;        // (0x604) Queue Status Registers 1 
        __R   QSTAT_reg_t           QSTAT_2;        // (0x608) Queue Status Registers 2
        __R   uint32_t              RESERVED9[5]; 
        __RW  QWMTHRA_reg_t         QWMTHRA;        // (0x620) Queue Watermark Threshold A Register
        __R   uint32_t              RESERVED10[7]; 
        __R   CCSTAT_reg_t          CCSTAT;         // (0x640) EDMA3CC Status Register
        __R   uint32_t              RESERVED11[111]; 
        __R   MPFAR_reg_t           MPFAR;          // (0x800) Memory Protection Fault Address Register
        __R   MPFSR_reg_t           MPFSR;          // (0x804) Memory Protection Fault Status Register
        __W   MPFCR_reg_t           MPFCR;          // (0x808) Memory Protection Fault Command Register 
        __RW  MPPAG_reg_t           MPPAG;          // (0x80C) Memory Protection Page Attribute Register Global 
        __RW  MPPA_reg_t            MPPA_0;         // (0x810) Memory Protection Page Attribute Register 0
        __RW  MPPA_reg_t            MPPA_1;         // (0x814) Memory Protection Page Attribute Register 1
        __RW  MPPA_reg_t            MPPA_2;         // (0x818) Memory Protection Page Attribute Register 2 
        __RW  MPPA_reg_t            MPPA_3;         // (0x81C) Memory Protection Page Attribute Register 3 
        __RW  MPPA_reg_t            MPPA_4;         // (0x820) Memory Protection Page Attribute Register 4
        __RW  MPPA_reg_t            MPPA_5;         // (0x824) Memory Protection Page Attribute Register 5 
        __RW  MPPA_reg_t            MPPA_6;         // (0x828) Memory Protection Page Attribute Register 6
        __RW  MPPA_reg_t            MPPA_7;         // (0x82C) Memory Protection Page Attribute Register 7
        __R   uint32_t              RESERVED12[500]; 
        __R   ER_reg_t              ER;             // (0x1000) Event Register  
        __R   ERH_reg_t             ERH;            // (0x1004) Event Register High 
        __W   ECR_reg_t             ECR;            // (0x1008) Event Clear Register 
        __W   ECRH_reg_t            ECRH;           // (0x100C) Event Clear Register High 
        __RW  ESR_reg_t             ESR;            // (0x1010) Event Set Register 
        __RW  ESRH_reg_t            ESRH;           // (0x1014) Event Set Register High 
        __R   CER_reg_t             CER;            // (0x1018) Chained Event Register  
        __R   CERH_reg_t            CERH;           // (0x101C) Chained Event Register High 
        __R   EER_reg_t             EER;            // (0x1020) Event Enable Register
        __R   EERH_reg_t            EERH;           // (0x1024) Event Enable Register High 
        __W   EECR_reg_t            EECR;           // (0x1028) Event Enable Clear Register  
        __W   EECRH_reg_t           EECRH;          // (0x102C) Event Enable Clear Register High 
        __W   EESR_reg_t            EESR;           // (0x1030) Event Enable Set Register 
        __W   EESRH_reg_t           EESRH;          // (0x1034) Event Enable Set Register High
        __R   SER_reg_t             SER;            // (0x1038) Secondary Event Register 
        __R   SERH_reg_t            SERH;           // (0x103C) Secondary Event Register High 
        __W   SECR_reg_t            SECR;           // (0x1040) Secondary Event Clear Register 
        __W   SECRH_reg_t           SECRH;          // (0x1044) Secondary Event Clear Register High
        __R   uint32_t              RESERVED13[2]; 
        __R   IER_reg_t             IER;            // (0x1050) Interrupt Enable Register
        __R   IERH_reg_t            IERH;           // (0x1054) Interrupt Enable Register High 
        __W   IECR_reg_t            IECR;           // (0x1058) Interrupt Enable Clear Register
        __W   IECRH_reg_t           IECRH;          // (0x105C) Interrupt Enable Clear Register High  
        __W   IESR_reg_t            IESR;           // (0x1060) Interrupt Enable Set Register 
        __W   IESRH_reg_t           IESRH;          // (0x1064) Interrupt Enable Set Register High 
        __R   IPR_reg_t             IPR;            // (0x1068) Interrupt Pending Register 
        __R   IPRH_reg_t            IPRH;           // (0x106C) Interrupt Pending Register High 
        __W   ICR_reg_t             ICR;            // (0x1070) Interrupt Clear Register 
        __W   ICRH_reg_t            ICRH;           // (0x1074) Interrupt Clear Register High
        __W   IEVAL_reg_t           IEVAL;          // (0x1078) Interrupt Evaluate Register
        __R   uint32_t              RESERVED14[1]; 
        __R   QER_reg_t             QER;            // (0x1080) QDMA Event Register 
        __R   QEER_reg_t            QEER;           // (0x1084) QDMA Event Enable Register
        __W   QEECR_reg_t           QEECR;          // (0x1088) QDMA Event Enable Clear Register 
        __W   QEESR_reg_t           QEESR;          // (0x108C) QDMA Event Enable Set Register  
        __R   QSER_reg_t            QSER;           // (0x1090) QDMA Secondary Event Register 
        __W   QSECR_reg_t           QSECR;          // (0x1094) QDMA Secondary Event Clear Register
    };

    struct AM335x_EDMA3TC_Type
    {                                                                                      
        __R   PIDTC_reg_t         PID;                // (0x00)   Peripheral Identification Register
        __R   TCCFG_reg_t         TCCFG;              // (0x04)   EDMA3TC Configuration Register
        __R   uint32_t            RESERVED1[2];
        __RW  SYSCONFIGTC_reg_t   SYSCONFIG;          // (0x10)   EDMA3TC System Configuration Register  
        __R   uint32_t            RESERVED2[59];
        __R   TCSTAT_reg_t        TCSTAT;             // (0x100)  EDMA3TC Channel Status Register
        __R   uint32_t            RESERVED3[7];  
        __R   ERRSTAT_reg_t       ERRSTAT;            // (0x120)  Error Register 
        __RW  ERREN_reg_t         ERREN;              // (0x124)  Error Enable Register 
        __W   ERRCLR_reg_t        ERRCLR;             // (0x128)  Error Clear Register 
        __R   ERRDET_reg_t        ERRDET;             // (0x12C)  Error Details Register 
        __W   ERRCMD_reg_t        ERRCMD;             // (0x130)  Error Interrupt Command Register 
        __R   uint32_t            RESERVED4[3]; 
        __RW  RDRATE_reg_t        RDRATE;             // (0x140)  Read Rate Register
        __R   uint32_t            RESERVED5[63];
        __R   SAOPT_reg_t         SAOPT;              // (0x240)  Source Active Options Register 
        __R   SASRC_reg_t         SASRC;              // (0x244)  Source Active Source Address Register
        __R   SACNT_reg_t         SACNT;              // (0x248)  Source Active Count Register  
        __R   SADST_reg_t         SADST;              // (0x24C)  Source Active Destination Address Register 
        __R   SABIDX_reg_t        SABIDX;             // (0x250)  Source Active Source B-Index Register
        __R   SAMPPRXY_reg_t      SAMPPRXY;           // (0x254)  Source Active Memory Protection Proxy Register  
        __R   SACNTRLD_reg_t      SACNTRLD;           // (0x258)  Source Active Count Reload Register
        __R   SASRCBREF_reg_t     SASRCBREF;          // (0x25C)  Source Active Source Address B-Reference Register 
        __R   SADSTBREF_reg_t     SADSTBREF;          // (0x260)  Source Active Destination Address B-Reference Register
        __R   uint32_t            RESERVED6[7];
        __R   DFCNTRLD_reg_t      DFCNTRLD;           // (0x280)  Destination FIFO Set Count Reload
        __R   DFSRCBREF_reg_t     DFSRCBREF;          // (0x284)  Destination FIFO Set Destination Address B Reference Register
        __R   DFDSTBREF_reg_t     DFDSTBREF;          // (0x288)  Destination FIFO Set Destination Address B Reference Register
        __R   uint32_t            RESERVED7[29];
        __R   DFOPT0_reg_t        DFOPT0;             // (0x300)  Destination FIFO Options Register 0
        __R   DFSRC0_reg_t        DFSRC0;             // (0x304)  Destination FIFO Source Address Register 0
        __R   DFCNT0_reg_t        DFCNT0;             // (0x308)  Destination FIFO Count Register 0
        __R   DFDST0_reg_t        DFDST0;             // (0x30C)  Destination FIFO Destination Address Register 0
        __R   DFBIDX0_reg_t       DFBIDX0;            // (0x310)  Destination FIFO BIDX Register 0
        __R   DFMPPRXY0_reg_t     DFMPPRXY0;          // (0x314)  Destination FIFO Memory Protection Proxy Register 0
        __R   uint32_t            RESERVED8[10];
        __R   DFOPT1_reg_t        DFOPT1;             // (0x340)  Destination FIFO Options Register 1
        __R   DFSRC1_reg_t        DFSRC1;             // (0x344)  Destination FIFO Source Address Register 1
        __R   DFCNT1_reg_t        DFCNT1;             // (0x348)  Destination FIFO Count Register 1
        __R   DFDST1_reg_t        DFDST1;             // (0x34C)  Destination FIFO Destination Address Register 1
        __R   DFBIDX1_reg_t       DFBIDX1;            // (0x350)  Destination FIFO BIDX Register 1
        __R   DFMPPRXY1_reg_t     DFMPPRXY1;          // (0x354)  Destination FIFO Memory Protection Proxy Register 1
        __R   uint32_t            RESERVED9[10];
        __R   DFOPT2_reg_t        DFOPT2;             // (0x380)  Destination FIFO Options Register 2
        __R   DFSRC2_reg_t        DFSRC2;             // (0x384)  Destination FIFO Source Address Register 2
        __R   DFCNT2_reg_t        DFCNT2;             // (0x388)  Destination FIFO Count Register 2
        __R   DFDST2_reg_t        DFDST2;             // (0x38C)  Destination FIFO Destination Address Register 2
        __R   DFBIDX2_reg_t       DFBIDX2;            // (0x390)  Destination FIFO BIDX Register 2
        __R   DFMPPRXY2_reg_t     DFMPPRXY2;          // (0x394)  Destination FIFO Memory Protection Proxy Register 2
        __R   uint32_t            RESERVED10[10];
        __R   DFOPT3_reg_t        DFOPT3;             // (0x3C0)  Destination FIFO Options Register 3
        __R   DFSRC3_reg_t        DFSRC3;             // (0x3C4)  Destination FIFO Source Address Register 3
        __R   DFCNT3_reg_t        DFCNT3;             // (0x3C8)  Destination FIFO Count Register 3
        __R   DFDST3_reg_t        DFDST3;             // (0x3CC)  Destination FIFO Destination Address Register 3
        __R   DFBIDX3_reg_t       DFBIDX3;            // (0x3D0)  Destination FIFO BIDX Register 3
        __R   DFMPPRXY3_reg_t     DFMPPRXY3;          // (0x3D4)  Destination FIFO Memory Protection Proxy Register 3 
    };
    
    constexpr uint32_t PARAM_ENTRY_FIELDS = 0x8u;
              uint32_t* get_paRAM_ptr(uint32_t n);
        
    struct paRAM_entry_t
    {
        // Transfer configuration options
        union 
        {
            struct 
            {  
                uint32_t    SAM       :1;   // bit: 0          (RW) Source address mode. [0x0 = Increment (INCR) mode; 0x1 = Constant addressing (CONST) mode.]
                                            //                      Increment (INCR) mode. Source addressing within an array increments. Source is not a FIFO.
                                            //                      Constant addressing (CONST) mode. Source addressing within an array wraps around upon reaching FIFO width.
                uint32_t    DAM       :1;   // bit: 1          (RW) Destination address mode. [ 0x0 = Increment (INCR) mode; 0x1 = Constant addressing (CONST) mode. ]
                                            //                      Increment (INCR) mode. Destination addressing within an array increments. Destination is not a FIFO.
                                            //                      Constant addressing (CONST) mode. Destination addressing within an array wraps around upon reaching FIFO width.
                uint32_t    SYNCDIM   :1;   // bit: 2          (RW) Transfer synchronization dimension. [ 0x0 = A-synchronized; 0x1 = AB-synchronized. ]
                uint32_t    STATIC    :1;   // bit: 3          (RW) Static set. [0x0 = Set is not static; 0x1 = Set is static. ]
                                            //                      Set is not static. The PaRAM set is updated or linked after a TR is submitted. A value of 0 should be
                                            //                      used for DMA channels and for non-final transfers in a linked list of QDMA transfers.
                                            //                      1 Set is static. The PaRAM set is not updated or linked after a TR is submitted. A value of 1 should be
                                            //                      used for isolated QDMA transfers or for the final transfer in a linked list of QDMA transfers.
                uint32_t              :4;   // bit: 4..7       Reserved 
                uint32_t    FWID      :3;   // bit: 8..10      (RW) FIFO Width. Applies if either SAM or DAM is set to constant addressing mode. [ see e_paRAM_FIFO_MODE ]
                uint32_t    TCCMODE   :1;   // bit: 11         (RW) Transfer complete code mode. Indicates the point at which a transfer is considered completed for
                                            //                      chaining and interrupt generation.
                                            //                      [0x0 = Normal completion; 0x1 = Early completion]
                uint32_t    TCC       :6;   // bit: 12..17     (RW) Transfer complete code. This 6-bit code sets the relevant bit in the chaining enable register (CER [TCC]
                                            //                      CERH [TCC]) for chaining or in the interrupt pending register (IPR [TCC] / IPRH [TCC]) for interrupts.
                                            //                      [ 0-3Fh]
                uint32_t              :2;   // bit: 18,19      Reserved          
                uint32_t    TCINTEN   :1;   // bit: 20         (RW) Transfer complete interrupt enable. [ 0x0 = disabled; 0x1 = enabled ] 
                uint32_t    ITCINTEN  :1;   // bit: 21         (RW) Intermediate transfer completion interrupt enable. [ 0x0 = disabled; 0x1 = enabled ] 
                uint32_t    TCCHEN    :1;   // bit: 22         (RW) Transfer complete chaining enable. [ 0x0 = disabled; 0x1 = enabled ]
                uint32_t    ITCCHEN   :1;   // bit: 23         (RW) Intermediate transfer completion chaining enable. [ 0x0 = disabled; 0x1 = enabled ]
                uint32_t    PRIVID    :4;   // bit: 24..27     (R) Privilege identification for the external host/CPU/DMA that programmed this PaRAM set. This value is
                                            //                     set with the EDMA3 master’s privilege identification value when any part of the PaRAM set is written.
                uint32_t              :3;   // bit: 28..30     Reserved
                uint32_t    PRIV      :1;   // bit: 31         (R) Privilege level (supervisor versus user) for the host/CPU/DMA that programmed this PaRAM set. This
                                            //                     value is set with the EDMA3 master’s privilege value when any part of the PaRAM set is written.
                                            //                     [ 0x0 = User level privilege.; 0x1 = Supervisor level privilege. ] 
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access
        } OPT;

        uint32_t  SRC { 0 };    // The byte address from which data is transferred 
        
        uint16_t  ACNT { 0 };   // Unsigned value specifying the number of contiguous bytes
                                // within an array (first dimension of the transfer). Valid values
                                // range from 1 to 65 535.
        
        uint16_t  BCNT { 0 };   // Unsigned value specifying the number of arrays in a frame,
                                // where an array is ACNT bytes. Valid values range from 1 to 65 535.
        
        uint32_t  DST { 0 };    // The byte address to which data is transferred
        
         int16_t  SRCBIDX { 0 };// Signed value specifying the byte address offset between
                                // source arrays within a frame (2nd dimension). Valid values range from –32 768 and 32 767.
         
         int16_t  DSTBIDX { 0 };// Signed value specifying the byte address offset between
                                // destination arrays within a frame (2nd dimension). Valid
                                // values range from –32 768 and 32 767.
         
        uint16_t  LINK { 0 };   // The PaRAM address containing the PaRAM set to be linked
                                // (copied from) when the current PaRAM set is exhausted. A
                                // value of FFFFh specifies a null link.
        
        uint16_t  BCNTRLD { 0 };// The count value used to reload BCNT when BCNT
                                // decrements to 0 (TR is submitted for the last array in 2nd
                                // dimension). Only relevant in A-synchronized transfers.
        
         int16_t  SRCCIDX { 0 };// Signed value specifying the byte address offset between
                                // frames within a block (3rd dimension). Valid values range
                                // from –32 768 and 32 767.
                                // A-synchronized transfers: The byte address offset from the
                                // beginning of the last source array in a frame to the
                                // beginning of the first source array in the next frame.
                                // AB-synchronized transfers: The byte address offset from the
                                // beginning of the first source array in a frame to the
                                // beginning of the first source array in the next frame.
         
         int16_t  DSTCIDX { 0 };// Signed value specifying the byte address offset between
                                // frames within a block (3rd dimension). Valid values range
                                // from –32 768 and 32 767.
                                // A-synchronized transfers: The byte address offset from the
                                // beginning of the last destination array in a frame to the
                                // beginning of the first destination array in the next frame.
                                // AB-synchronized transfers: The byte address offset from the
                                // beginning of the first destination array in a frame to the
                                // beginning of the first destination array in the next frame.
         
        uint16_t  CCNT { 0 };   // Unsigned value specifying the number of frames in a block,
                                // where a frame is BCNT arrays of ACNT bytes. Valid values range from 1 to 65 535.
        
        uint16_t  RESERVED;     // Reserved. Always write 0 to this bit; writes of 1 to this bit are
                                // not supported and attempts to do so may result in undefined behavior.

        paRAM_entry_t() { OPT.reg = 0; }

        paRAM_entry_t& operator =(const paRAM_entry_t &right)
        {
            OPT.reg  = right.OPT.reg;
                SRC  = right.SRC;
               ACNT  = right.ACNT;
               BCNT  = right.BCNT;
                DST  = right.DST;
            SRCBIDX  = right.SRCBIDX;
            DSTBIDX  = right.DSTBIDX;
               LINK  = right.LINK;
            BCNTRLD  = right.BCNTRLD;
            SRCCIDX  = right.SRCCIDX;
            DSTCIDX  = right.DSTCIDX;
               CCNT  = right.CCNT;
        
           return *this;
        }
    };

    enum e_paRAM_FIFO_WIDTH : uint32_t
    {
        FIFO_WIDTH_8BIT     = 0x0,
        FIFO_WIDTH_16BIT    = 0x1,
        FIFO_WIDTH_32BIT    = 0x2,
        FIFO_WIDTH_64BIT    = 0x3,
        FIFO_WIDTH_128BIT   = 0x4,
        FIFO_WIDTH_256BIT   = 0x5
    };

    constexpr uint32_t AM335x_EDMA3CC_BASE     = 0x49000000;   
    constexpr uint32_t AM335x_EDMA3TC0_BASE    = 0x49800000;
    constexpr uint32_t AM335x_EDMA3TC1_BASE    = 0x49900000;
    constexpr uint32_t AM335x_EDMA3TC2_BASE    = 0x49A00000;
    constexpr uint32_t PARAM_BASE              = 0x4000;
    constexpr uint32_t COMPL_HANDLER_RETRY_COUNT = 10u;
    constexpr uint32_t ERR_HANDLER_RETRY_COUNT   = 10u;
    
    constexpr uint32_t EVTQUE_AVAIL  = 2u;  // Number of Event Queues available 

    constexpr AM335x_EDMA3CC_Type * AM335X_EDMA3CC_regs  = reinterpret_cast<AM335x_EDMA3CC_Type *>(AM335x_EDMA3CC_BASE);
    constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC0_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC0_BASE);
    constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC1_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC1_BASE);
    constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC2_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC2_BASE);

    constexpr uint32_t SET_ALL_BITS = 0xFFFFFFFFu;
    constexpr uint32_t CLR_ALL_BITS = 0x00000000u;
    
    enum e_REGION_ID : uint32_t
    {
        REGION_0 = 0x0,
        REGION_1 = 0x1,
        REGION_2 = 0x2,
        REGION_3 = 0x3,
        REGION_4 = 0x4,
        REGION_5 = 0x5,
        REGION_6 = 0x6,
        REGION_7 = 0x7        
    };

    enum e_EDMA3_CH_TYPE : uint32_t
    {
        CHANNEL_TYPE_DMA  = 0u,
        CHANNEL_TYPE_QDMA = 1u
    };

    enum e_EDMA3_TRIG_MODE_TYPE : uint32_t
    {
        TRIG_MODE_MANUAL = 0x0,
        TRIG_MODE_QDMA   = 0x1,
        TRIG_MODE_EVENT  = 0x2
    };

    enum e_EDMA3_CHANNEL_MAP : uint32_t
    {        
        CH_MCASP1_TX             = 10, // Events for McASP 1
        CH_MCASP1_RX             = 11, // Events for McASP 1
        CH_MCSPI0_CH0_TX  = 16, // MCSPI0 Channel 0 transmit event 
        CH_MCSPI0_CH0_RX  = 17, // MCSPI0 Channel 0 receive event 
        CH_MCSPI0_CH1_TX  = 18, // MCSPI0 Channel 1 transmit event 
        CH_MCSPI0_CH1_RX  = 19, // MCSPI0 Channel 1 receive event 
        CH_MMCSD0_TX      = 24, // MMCSD0 transmit event. 
        CH_MMCSD0_RX      = 25, // MMCSD0 receive event.
        CH_UART0_TX       = 26, // UART0 Transmit Event.
        CH_UART0_RX       = 27, // UART0 Receive Event. 
        CH_UART1_TX       = 28, // UART1 Transmit Event.
        CH_UART1_RX       = 29, // UART1 Receive Event.
        CH_UART2_TX       = 30, // UART2 Transmit Event.
        CH_UART2_RX       = 31, // UART2 Receive Event.
        CH_MCSPI1_CH0_TX  = 42, // MCSPI1 Channel 0 transmit event  
        CH_MCSPI1_CH0_RX  = 43, // MCSPI1 Channel 0 receive event
        CH_MCSPI1_CH1_TX  = 44, // MCSPI1 Channel 1 transmit event
        CH_MCSPI1_CH1_RX  = 45, // MCSPI1 Channel 1 receive event 
        CH_I2C0_TX        = 58, // I2C0 Transmit Event 
        CH_I2C0_RX        = 59, // I2C0 Receive Event 
        CH_I2C1_TX        = 60, // I2C1 Receive Event
        CH_I2C1_RX        = 61  // I2C1 Transmit Event 
    };
    
   constexpr uint32_t  EDMA_REVID                = 0x01u;
   constexpr uint32_t  AM335X_DMACH_MAX          = 64;
   constexpr uint32_t  AM335X_QDMACH_MAX         = 8; 

   constexpr uint32_t  PARAM_ENTRY_OPT            = 0x0u;       //The OPT field (Offset Address 0x0 Bytes)
   constexpr uint32_t  PARAM_ENTRY_SRC            = 0x1u;       //The SRC field (Offset Address 0x4 Bytes)
   constexpr uint32_t  PARAM_ENTRY_ACNT_BCNT      = 0x2u;       //The (ACNT+BCNT) field (Offset Address 0x8 Bytes)
   constexpr uint32_t  PARAM_ENTRY_DST            = 0x3u;       //The DST field (Offset Address 0xC Bytes)
   constexpr uint32_t  PARAM_ENTRY_SRC_DST_BIDX   = 0x4u;       //The (SRCBIDX+DSTBIDX) field (Offset Address 0x10 Bytes)
   constexpr uint32_t  PARAM_ENTRY_LINK_BCNTRLD   = 0x5u;       //The (LINK+BCNTRLD) field (Offset Address 0x14 Bytes)
   constexpr uint32_t  PARAM_ENTRY_SRC_DST_CIDX   = 0x6u;       //The (SRCCIDX+DSTCIDX) field (Offset Address 0x18 Bytes)
   constexpr uint32_t  PARAM_ENTRY_CCNT           = 0x7u;       //The (CCNT+RSVD) field (Offset Address 0x1C Bytes)
   constexpr uint32_t  PARAM_FIELD_OFFSET         = 0x4u;       //The offset for each PaRAM Entry field
    
    // Structure to store the EDMA context
    typedef struct edma_context 
    {    
         uint32_t  dch_map[AM335X_DMACH_MAX];       // Channel mapping reg Val      
         uint32_t  dma_Qnum[AM335X_QDMACH_MAX];     // DMA Queue Number Register Val
         
         uint32_t  reg_acc_enable_low;       // DMA Region Access Enable Register val    
         uint32_t  reg_acc_enable_high;      // DMA Region Access Enable Register val 
           
         uint32_t  event_set_reg_low;        // Event Set Register value  
         uint32_t  event_set_reg_high;       // Event Set Register value 
            
         uint32_t  enable_evt_set_reg_low;    // Enable Event Set Register value 
         uint32_t  enable_evt_set_reg_high;   // Enable Event Set Register value 
                  
         uint32_t  int_enable_set_reg_low;    // Interrupt Enable Set Register value      
         uint32_t  int_enable_set_reg_high;   // Interrupt Enable Set Register value   
        
    paRAM_entry_t  dma_par_entry[256];    
        
    } EDMACONTEXT_t;

     DRAE_reg_t*& get_DRAE_ptr(e_REGION_ID region_id);
    DRAEH_reg_t*& get_DRAEH_ptr(e_REGION_ID region_id);    
        uint32_t  DMAQNUM_CLR(uint32_t count);
        uint32_t  DMAQNUM_SET(uint32_t count, e_DMA_QUEUE que_num);
        uint32_t  QDMAQNUM_CLR(uint32_t count);
        uint32_t  QDMAQNUM_SET(uint32_t count, e_DMA_QUEUE que_num);

       ER_reg_t*& get_S_ER_ptr(e_REGION_ID region_id);
    //ERH_reg_t*& get_S_ERH_ptr(e_REGION_ID region_id); 
      ECR_reg_t*& get_S_ECR_ptr(e_REGION_ID region_id); 
     ECRH_reg_t*& get_S_ECRH_ptr(e_REGION_ID region_id); 
      ESR_reg_t*& get_S_ESR_ptr(e_REGION_ID region_id);
     ESRH_reg_t*& get_S_ESRH_ptr(e_REGION_ID region_id); 
      CER_reg_t*& get_S_CER_ptr(e_REGION_ID region_id); 
   //CERH_reg_t*& get_S_CERH_ptr(e_REGION_ID region_id); 
      EER_reg_t*& get_S_EER_ptr(e_REGION_ID region_id);
     EERH_reg_t*& get_S_EERH_ptr(e_REGION_ID region_id); 
     EECR_reg_t*& get_S_EECR_ptr(e_REGION_ID region_id); 
    EECRH_reg_t*& get_S_EECRH_ptr(e_REGION_ID region_id); 
     EESR_reg_t*& get_S_EESR_ptr(e_REGION_ID region_id); 
    EESRH_reg_t*& get_S_EESRH_ptr(e_REGION_ID region_id);
      SER_reg_t*& get_S_SER_ptr(e_REGION_ID region_id); 
     SERH_reg_t*& get_S_SERH_ptr(e_REGION_ID region_id);
     SECR_reg_t*& get_S_SECR_ptr(e_REGION_ID region_id); 
    SECRH_reg_t*& get_S_SECRH_ptr(e_REGION_ID region_id);
      IER_reg_t*& get_S_IER_ptr(e_REGION_ID region_id);    
     IERH_reg_t*& get_S_IERH_ptr(e_REGION_ID region_id);   
     IECR_reg_t*& get_S_IECR_ptr(e_REGION_ID region_id);   
    IECRH_reg_t*& get_S_IECRH_ptr(e_REGION_ID region_id);  
     IESR_reg_t*& get_S_IESR_ptr(e_REGION_ID region_id);   
    IESRH_reg_t*& get_S_IESRH_ptr(e_REGION_ID region_id);  
      IPR_reg_t*& get_S_IPR_ptr(e_REGION_ID region_id);    
     IPRH_reg_t*& get_S_IPRH_ptr(e_REGION_ID region_id);   
      ICR_reg_t*& get_S_ICR_ptr(e_REGION_ID region_id);    
     ICRH_reg_t*& get_S_ICRH_ptr(e_REGION_ID region_id);   
    IEVAL_reg_t*& get_S_IEVAL_ptr(e_REGION_ID region_id);  
      QER_reg_t*& get_S_QER_ptr(e_REGION_ID region_id);   
     QEER_reg_t*& get_S_QEER_ptr(e_REGION_ID region_id);  
    QEECR_reg_t*& get_S_QEECR_ptr(e_REGION_ID region_id); 
    QEESR_reg_t*& get_S_QEESR_ptr(e_REGION_ID region_id); 
     QSER_reg_t*& get_S_QSER_ptr(e_REGION_ID region_id);  
    QSECR_reg_t*& get_S_QSECR_ptr(e_REGION_ID region_id);
    
        uint32_t* get_paRAM_ptr(uint32_t n);                
        uint32_t* get_SRC_ptr(uint32_t n);                
        uint32_t* get_A_B_CNT_ptr(uint32_t n);            
        uint32_t* get_DST_ptr(uint32_t n);                
        uint32_t* get_SRC_DST_BIDX_ptr(uint32_t n);       
        uint32_t* get_LINK_BCNTRLD_ptr(uint32_t n);       
        uint32_t* get_SRC_DST_CIDX_ptr(uint32_t n);       
        uint32_t* get_CCNT_ptr(uint32_t n);

    inline DRAE_reg_t*& get_DRAE_ptr(e_REGION_ID region_id) 
    {
        uint32_t DRAE = (AM335x_EDMA3CC_BASE + 0x340 + (region_id * 8));      
        return (DRAE_reg_t*&)DRAE;
    }
    
    inline DRAEH_reg_t*& get_DRAEH_ptr(e_REGION_ID region_id) 
    {
        uint32_t DRAEH = (AM335x_EDMA3CC_BASE + 0x344 + (region_id * 8));        
        return (DRAEH_reg_t*&)DRAEH;
    }

    inline uint32_t  DMAQNUM_CLR(uint32_t ch_num)
    { return (~(0x7u << (((ch_num)%8u)*4u))); }

    inline uint32_t  DMAQNUM_SET(uint32_t ch_num, e_DMA_QUEUE que_num)
    { return ((0x7u & ((uint32_t)que_num)) << (((ch_num)%8u)*4u)); }

    inline uint32_t  QDMAQNUM_CLR(uint32_t ch_num)
    { return (~(0x7u << (ch_num*4u))); }

    inline uint32_t  QDMAQNUM_SET(uint32_t ch_num, e_DMA_QUEUE que_num)
    { return ((0x7u & ((uint32_t)que_num)) << (ch_num*4u)); }

    inline   ER_reg_t*& get_S_ER_ptr(e_REGION_ID region_id)
    {
        uint32_t ER = AM335x_EDMA3CC_BASE + 0x2000 +  (0X200*region_id);        
        return (ER_reg_t*&)ER;
    }

    inline  ECR_reg_t*& get_S_ECR_ptr(e_REGION_ID region_id) 
    {
        uint32_t ECR = AM335x_EDMA3CC_BASE + 0x2008 +  (0X200*region_id);        
        return (ECR_reg_t*&)ECR;
    }

    inline ECRH_reg_t*& get_S_ECRH_ptr(e_REGION_ID region_id) 
    {
        uint32_t ECRH = AM335x_EDMA3CC_BASE + 0x200C +  (0X200*region_id);        
        return (ECRH_reg_t*&)ECRH;
    }

    inline  ESR_reg_t*& get_S_ESR_ptr(e_REGION_ID region_id)
    {
        uint32_t ESR = AM335x_EDMA3CC_BASE + 0x2010 +  (0X200*region_id);        
        return (ESR_reg_t*&)ESR;
    }

    inline ESRH_reg_t*& get_S_ESRH_ptr(e_REGION_ID region_id)
    {
        uint32_t ESRH = AM335x_EDMA3CC_BASE + 0x2014 +  (0X200*region_id);        
        return (ESRH_reg_t*&)ESRH;
    }

    inline  CER_reg_t*& get_S_CER_ptr(e_REGION_ID region_id) 
    {
        uint32_t CER = AM335x_EDMA3CC_BASE + 0x2018 +  (0X200*region_id);        
        return (CER_reg_t*&)CER;
    }

    inline  EER_reg_t*& get_S_EER_ptr(e_REGION_ID region_id)
    {
        uint32_t EER = AM335x_EDMA3CC_BASE + 0x2020 +  (0X200*region_id);        
        return (EER_reg_t*&)EER;
    }

    inline EERH_reg_t*& get_S_EERH_ptr(e_REGION_ID region_id)
    {
        uint32_t EERH = AM335x_EDMA3CC_BASE + 0x2024 +  (0X200*region_id);        
        return (EERH_reg_t*&)EERH;
    }

    inline EECR_reg_t*& get_S_EECR_ptr(e_REGION_ID region_id)
    {
        uint32_t EECR = AM335x_EDMA3CC_BASE + 0x2028 +  (0X200*region_id);        
        return (EECR_reg_t*&)EECR;
    }

    inline EECRH_reg_t*& get_S_EECRH_ptr(e_REGION_ID region_id)
    {
        uint32_t EECRH = AM335x_EDMA3CC_BASE + 0x202C +  (0X200*region_id);        
        return (EECRH_reg_t*&)EECRH;
    }

    inline EESR_reg_t*& get_S_EESR_ptr(e_REGION_ID region_id)
    {
        uint32_t EESR = AM335x_EDMA3CC_BASE + 0x2030 +  (0X200*region_id);        
        return (EESR_reg_t*&)EESR;
    }

    inline EESRH_reg_t*& get_S_EESRH_ptr(e_REGION_ID region_id)
    {
        uint32_t EESRH = AM335x_EDMA3CC_BASE + 0x2034 +  (0X200*region_id);        
        return (EESRH_reg_t*&)EESRH;
    }

    inline  SER_reg_t*& get_S_SER_ptr(e_REGION_ID region_id) 
    {
        uint32_t SER = AM335x_EDMA3CC_BASE + 0x2038 +  (0X200*region_id);        
        return (SER_reg_t*&)SER;
    }

    inline SERH_reg_t*& get_S_SERH_ptr(e_REGION_ID region_id)
    {
        uint32_t SERH = AM335x_EDMA3CC_BASE + 0x203C +  (0X200*region_id);        
        return (SERH_reg_t*&)SERH;
    }

    inline SECR_reg_t*& get_S_SECR_ptr(e_REGION_ID region_id)
    {
        uint32_t SECR = AM335x_EDMA3CC_BASE + 0x2040 +  (0X200*region_id);        
        return (SECR_reg_t*&)SECR;
    }

    inline SECRH_reg_t*& get_S_SECRH_ptr(e_REGION_ID region_id)
    {
        uint32_t SECRH = AM335x_EDMA3CC_BASE + 0x2044 +  (0X200*region_id);        
        return (SECRH_reg_t*&)SECRH;
    }

    inline  IER_reg_t*& get_S_IER_ptr(e_REGION_ID region_id)
    {
        uint32_t IER = AM335x_EDMA3CC_BASE + 0x2050 +  (0X200*region_id);        
        return (IER_reg_t*&)IER;
    }

    inline IERH_reg_t*& get_S_IERH_ptr(e_REGION_ID region_id)
    {
        uint32_t IERH = AM335x_EDMA3CC_BASE + 0x2054 +  (0X200*region_id);        
        return (IERH_reg_t*&)IERH;
    }

    inline IECR_reg_t*& get_S_IECR_ptr(e_REGION_ID region_id)
    {
        uint32_t IECR = AM335x_EDMA3CC_BASE + 0x2058 +  (0X200*region_id);        
        return (IECR_reg_t*&)IECR;
    }

    inline IECRH_reg_t*& get_S_IECRH_ptr(e_REGION_ID region_id) 
    {
        uint32_t IECRH = AM335x_EDMA3CC_BASE + 0x205C +  (0X200*region_id);        
        return (IECRH_reg_t*&)IECRH;
    }

    inline IESR_reg_t*& get_S_IESR_ptr(e_REGION_ID region_id)
    {
        uint32_t IESR = AM335x_EDMA3CC_BASE + 0x2060 +  (0X200*region_id);        
        return (IESR_reg_t*&)IESR;
    }

    inline IESRH_reg_t*& get_S_IESRH_ptr(e_REGION_ID region_id)
    {
        uint32_t IESRH = AM335x_EDMA3CC_BASE + 0x2064 +  (0X200*region_id);        
        return (IESRH_reg_t*&)IESRH;
    }

    inline  IPR_reg_t*& get_S_IPR_ptr(e_REGION_ID region_id)
    {
        uint32_t IPR = AM335x_EDMA3CC_BASE + 0x2068 +  (0X200*region_id);        
        return (IPR_reg_t*&)IPR;
    }

    inline IPRH_reg_t*& get_S_IPRH_ptr(e_REGION_ID region_id)
    {
        uint32_t IPRH = AM335x_EDMA3CC_BASE + 0x206C +  (0X200*region_id);        
        return (IPRH_reg_t*&)IPRH;
    }

    inline  ICR_reg_t*& get_S_ICR_ptr(e_REGION_ID region_id)
    {
        uint32_t ICR = AM335x_EDMA3CC_BASE + 0x2070 +  (0X200*region_id);        
        return (ICR_reg_t*&)ICR;
    }

    inline ICRH_reg_t*& get_S_ICRH_ptr(e_REGION_ID region_id)
    {
        uint32_t ICRH = AM335x_EDMA3CC_BASE + 0x2074 +  (0X200*region_id);        
        return (ICRH_reg_t*&)ICRH;
    }

    inline IEVAL_reg_t*& get_S_IEVAL_ptr(e_REGION_ID region_id)
    {
        uint32_t IEVAL = AM335x_EDMA3CC_BASE + 0x2078 +  (0X200*region_id);        
        return (IEVAL_reg_t*&)IEVAL;
    }

    inline  QER_reg_t*& get_S_QER_ptr(e_REGION_ID region_id) 
    {
        uint32_t QER = AM335x_EDMA3CC_BASE + 0x2080 +  (0X200*region_id);        
        return (QER_reg_t*&)QER;
    }

    inline QEER_reg_t*& get_S_QEER_ptr(e_REGION_ID region_id)
    {
        uint32_t QEER = AM335x_EDMA3CC_BASE + 0x2084 +  (0X200*region_id);        
        return (QEER_reg_t*&)QEER;
    }

    inline QEECR_reg_t*& get_S_QEECR_ptr(e_REGION_ID region_id)
    {
        uint32_t QEECR = AM335x_EDMA3CC_BASE + 0x2088 +  (0X200*region_id);        
        return (QEECR_reg_t*&)QEECR;
    }

    inline QEESR_reg_t*& get_S_QEESR_ptr(e_REGION_ID region_id)
    {
        uint32_t QEESR = AM335x_EDMA3CC_BASE + 0x208C +  (0X200*region_id);        
        return (QEESR_reg_t*&)QEESR;
    }

    inline QSER_reg_t*& get_S_QSER_ptr(e_REGION_ID region_id)
    {
        uint32_t QSER = AM335x_EDMA3CC_BASE + 0x2090 +  (0X200*region_id);        
        return (QSER_reg_t*&)QSER;
    }

    inline QSECR_reg_t*& get_S_QSECR_ptr(e_REGION_ID region_id)
    {
        uint32_t QSECR = AM335x_EDMA3CC_BASE + 0x2094 +  (0X200*region_id);        
        return (QSECR_reg_t*&)QSECR;
    }

    inline uint32_t* get_paRAM_ptr(uint32_t n)         
    { 
        return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + (0x20 * n)); 
    }
    
    inline uint32_t* get_SRC_ptr(uint32_t n)           
    { 
      return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x4 + (0x20 * n)); 
    }
    inline uint32_t* get_A_B_CNT_ptr(uint32_t n)       { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x8 + (0x20 * n)); }
    inline uint32_t* get_DST_ptr(uint32_t n)           { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0xC + (0x20 * n)); }
    inline uint32_t* get_SRC_DST_BIDX_ptr(uint32_t n)  { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x10 + (0x20 * n)); }
    inline uint32_t* get_LINK_BCNTRLD_ptr(uint32_t n)  { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x14 + (0x20 * n)); }
    inline uint32_t* get_SRC_DST_CIDX_ptr(uint32_t n)  { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x18 + (0x20 * n)); }
    inline uint32_t* get_CCNT_ptr(uint32_t n)          { return (uint32_t*)(AM335x_EDMA3CC_BASE + PARAM_BASE + 0x1C + (0x20 * n)); }
}


class AM335x_EDMA
{
public:
    n_EDMA::e_REGION_ID  region_id;
void (*cb_fx[n_EDMA::AM335X_DMACH_MAX]) (uint32_t tcc);  // function callbacks for n_EDMA channels and events
             
public:
              AM335x_EDMA()
                : m_EDMA3CC_regs(*(n_EDMA::AM335X_EDMA3CC_regs)),
                m_EDMA3TC0_regs(*(n_EDMA::AM335X_EDMA3TC0_regs)),
                m_EDMA3TC1_regs(*(n_EDMA::AM335X_EDMA3TC1_regs)),
                m_EDMA3TC2_regs(*(n_EDMA::AM335X_EDMA3TC2_regs)) 
              { 
                #ifdef _TMS320C6X        
                    region_id = n_EDMA::REGION_1;   // For DSP, region_id is assigned here and used globally in the driver
                #else   
                    region_id = n_EDMA::REGION_0;   // FOR ARM, region_id is assigned here and used globally in the driver
                #endif
              }
             ~AM335x_EDMA() { }

        void  init(n_EDMA::e_DMA_QUEUE que_num);
        void  set_non_idle_mode();
        void  enable_ch_in_shadow_reg(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num);
        void  disable_ch_in_shadow_reg(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num);
        void  map_ch_to_evtQ(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, n_EDMA::e_DMA_QUEUE evt_Qnum);
        void  unmap_ch_to_evtQ(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num);
        void  map_QDMA_ch_to_paRAM(uint32_t ch_num, uint32_t *paRAM_id);
        void  set_QDMA_trig_word(uint32_t ch_num, uint8_t trig_word);
        void  clr_miss_evt(uint32_t ch_num);
        void  QDMA_clr_miss_evt(uint32_t ch_num);
        void  clr_CCERR(uint32_t flags);
        void  set_evt(uint32_t ch_num);
        void  clr_evt(uint32_t ch_num);
        void  enable_DMA_evt(uint32_t ch_num);
        void  disable_DMA_evt(uint32_t ch_num);
        void  enable_QDMA_evt(uint32_t ch_num);
        void  disable_QDMA_evt(uint32_t ch_num);
    uint32_t  get_intr_status();
        void  enable_evt_intr(uint32_t ch_num);
        void  disable_evt_intr(uint32_t ch_num);
        void  clr_intr(uint32_t value);
n_EDMA::paRAM_entry_t* get_paRAM(uint32_t paRAM_id);
n_EDMA::paRAM_entry_t* QDMA_get_paRAM(uint32_t paRAM_id);
        void  set_paRAM(uint32_t ch_num, n_EDMA::paRAM_entry_t* new_paRAM);
        void  QDMA_set_paRAM(uint32_t paRAM_id, n_EDMA::paRAM_entry_t* new_paRAM);
        void  QDMA_set_paRAM_entry(uint32_t paRAM_id, uint32_t paRAM_entry, uint32_t new_paRAM_entry_val);
    uint32_t  QDMA_get_paRAM_entry(uint32_t paRAM_id, uint32_t paRAM_entry);
        bool  request_channel(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, uint32_t tcc_num, n_EDMA::e_DMA_QUEUE evt_Qnum);
        bool  free_channel(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, uint32_t trig_mode, uint32_t tcc_num, n_EDMA::e_DMA_QUEUE evt_Qnum);
        bool  enable_transfer(uint32_t ch_num, uint32_t trig_mode);
        bool  disable_transfer(uint32_t ch_num, uint32_t trig_mode);
        void  clear_error_bits(uint32_t ch_num, n_EDMA::e_DMA_QUEUE evt_Qnum);
    uint32_t  get_CCERR_status();
    uint32_t  get_ERR_intr_status();
 n_EDMA::QEMR_reg_t  QDMA_get_ERR_intr_status();
        void  CCERR_evaluate();
        void  deinit(uint32_t que_num);
    uint32_t  version_get(void) const { return 1; } // This returns a number '2' which is unique to EDMA IP in AM335x.
    uint32_t  peripheral_id_get();
    uint32_t  intr_status_high_get();
    uint32_t  ERR_intr_high_status_get();
        void  channel_to_param_map(uint32_t channel, uint32_t param_set);
        void  context_save(n_EDMA::EDMACONTEXT_t *p_edma_cntx);
        void  context_restore(n_EDMA::EDMACONTEXT_t *p_edma_cntx);
        
        
private:
    n_EDMA::AM335x_EDMA3CC_Type &m_EDMA3CC_regs;
    n_EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC0_regs;
    n_EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC1_regs;
    n_EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC2_regs;
};

extern AM335x_EDMA eDMA;

#endif //__N_EDMA_H