;********************************************************************************************************
;                                                uC/CPU
;                                    CPU CONFIGURATION & PORT LAYER
;
;                          (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
;
;               All rights reserved.  Protected by international copyright laws.
;
;               uC/CPU is provided in source form to registered licensees ONLY.  It is
;               illegal to distribute this source code to any third party unless you receive
;               written permission by an authorized Micrium representative.  Knowledge of
;               the source code may NOT be used to develop a similar product.
;
;               Please help us continue to provide the Embedded community with the finest
;               software available.  Your honesty is greatly appreciated.
;
;               You can find our product's user manual, API reference, release notes and
;               more information at https://doc.micrium.com.
;               You can contact us at www.micrium.com.
;********************************************************************************************************

;********************************************************************************************************
;
;                                            CPU PORT FILE
;
;                                        Generic ARM-Cortex-A
;                                              IAR EWARM
;
; Filename      : cpu_a.s
; Version       : V1.30.02.00
; Programmer(s) : JBL
;********************************************************************************************************


;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

   PUBLIC  CPU_SR_Save
   PUBLIC  CPU_SR_Restore

   PUBLIC  CPU_IntDis
   PUBLIC  CPU_IntEn

   PUBLIC  CPU_WaitForInt
   PUBLIC  CPU_WaitForEvent

   PUBLIC  CPU_CntLeadZeros
   PUBLIC  CPU_CntTrailZeros


;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    RSEG CODE:CODE:NOROOT(2)
    CODE32
    PRESERVE8


;********************************************************************************************************
;                                    DISABLE and ENABLE INTERRUPTS
;
; Description : Disable/Enable interrupts.
;
; Prototypes  : void  CPU_IntDis(void);
;               void  CPU_IntEn (void);
;********************************************************************************************************

CPU_IntDis
        CPSID   IF
        DSB
        BX      LR


CPU_IntEn
        DSB
        CPSIE   IF
        BX      LR


;********************************************************************************************************
;                                      CRITICAL SECTION FUNCTIONS
;
; Description : Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking, the
;               state of the interrupt disable flag is stored in the local variable 'cpu_sr' & interrupts
;               are then disabled ('cpu_sr' is allocated in all functions that need to disable interrupts).
;               The previous interrupt state is restored by copying 'cpu_sr' into the CPU's status register.
;
; Prototypes  : CPU_SR  CPU_SR_Save   (void);
;               void    CPU_SR_Restore(CPU_SR  cpu_sr);
;
; Note(s)     : (1) These functions are used in general like this :
;
;                       void  Task (void  *p_arg)
;                       {
;                           CPU_SR_ALLOC();                     /* Allocate storage for CPU status register */
;                               :
;                               :
;                           CPU_CRITICAL_ENTER();               /* cpu_sr = CPU_SR_Save();                  */
;                               :
;                               :
;                           CPU_CRITICAL_EXIT();                /* CPU_SR_Restore(cpu_sr);                  */
;                               :
;                       }
;********************************************************************************************************

CPU_SR_Save
        MRS     R0, CPSR
        CPSID   IF                                              ; Set IRQ & FIQ bits in CPSR to DISABLE all interrupts
        DSB
        BX      LR                                              ; DISABLED, return the original CPSR contents in R0


CPU_SR_Restore
        DSB
        MSR     CPSR_c, R0
        BX      LR


;********************************************************************************************************
;                                         WAIT FOR INTERRUPT
;
; Description : Enters sleep state, which will be exited when an interrupt is received.
;
; Prototypes  : void  CPU_WaitForInt (void)
;
; Argument(s) : none.
;********************************************************************************************************

CPU_WaitForInt
        DSB
        WFI                                     ; Wait for interrupt
        BX      LR


;********************************************************************************************************
;                                         WAIT FOR EXCEPTION
;
; Description : Enters sleep state, which will be exited when an exception is received.
;
; Prototypes  : void  CPU_WaitForExcept (void)
;
; Argument(s) : none.
;********************************************************************************************************

CPU_WaitForEvent
        DSB
        WFE                                     ; Wait for exception
        BX      LR


;********************************************************************************************************
;                                         CPU_CntLeadZeros()
;                                        COUNT LEADING ZEROS
;
; Description : Counts the number of contiguous, most-significant, leading zero bits before the first
;               binary one bit in a data value.
;
; Prototype   : CPU_DATA  CPU_CntLeadZeros(CPU_DATA  val);
;
; Argument(s) : val         Data value to count leading zero bits.
;
; Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
;
; Caller(s)   : Application.
;
;               This function is an INTERNAL CPU module function but MAY be called by application function(s).
;
; Note(s)     : (1) If the argument is zero, the value 32 is returned.
;
;               (2) MUST be implemented in cpu_a.asm if and only if CPU_CFG_LEAD_ZEROS_ASM_PRESENT is
;                   #define'd in 'cpu_cfg.h' or 'uC_cpu.h'.
;********************************************************************************************************

CPU_CntLeadZeros
        CLZ     R0, R0                                          ; Count leading zeros
        BX      LR


;********************************************************************************************************
;                                         CPU_CntTrailZeros()
;                                        COUNT TRAILING ZEROS
;
; Description : Counts the number of contiguous, least-significant, trailing zero bits before the
;                   first binary one bit in a data value.
;
; Prototype   : CPU_DATA  CPU_CntTrailZeros(CPU_DATA  val);
;
; Argument(s) : val         Data value to count trailing zero bits.
;
; Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
;
; Caller(s)   : Application.
;
;               This function is an INTERNAL CPU module function but MAY be called by application
;               function(s).
;
; Note(s)     : (1) (a) Supports 32-bit data value size as configured by 'CPU_DATA' (see 'uC_cpu.h
;                       CPU WORD CONFIGURATION  Note #1').
;
;                   (b) For 32-bit values :
;
;                             b31  b30  b29  b28  b27  ...  b02  b01  b00    # Trailing Zeros
;                             ---  ---  ---  ---  ---       ---  ---  ---    ----------------
;                              x    x    x    x    x         x    x    1            0
;                              x    x    x    x    x         x    1    0            1
;                              x    x    x    x    x         1    0    0            2
;                              :    :    :    :    :         :    :    :            :
;                              :    :    :    :    :         :    :    :            :
;                              x    x    x    x    1         0    0    0           27
;                              x    x    x    1    0         0    0    0           28
;                              x    x    1    0    0         0    0    0           29
;                              x    1    0    0    0         0    0    0           30
;                              1    0    0    0    0         0    0    0           31
;                              0    0    0    0    0         0    0    0           32
;
;
;               (2) MUST be defined in 'cpu_a.asm' (or 'cpu_c.c') if CPU_CFG_TRAIL_ZEROS_ASM_PRESENT is
;                   #define'd in 'cpu_cfg.h' or 'uC_cpu.h'.
;********************************************************************************************************

CPU_CntTrailZeros
        RBIT    R0, R0                          ; Reverse bits
        CLZ     R0, R0                          ; Count trailing zeros
        BX      LR


;********************************************************************************************************
;                                     CPU ASSEMBLY PORT FILE END
;********************************************************************************************************

    END

