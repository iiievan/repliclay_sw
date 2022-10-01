;
;********************************************************************************************************
;                                    EXCEPTION VECTORS & STARTUP CODE
;
; File      : cstartup.s
; For       : ARM7 or ARM9
; Toolchain : IAR EWARM V5.10 and higher
;********************************************************************************************************
;

    MODULE  ?cstartup

;********************************************************************************************************
;                                           MACROS AND DEFINIITIONS
;********************************************************************************************************

                                                                ; Mode, correspords to bits 0-5 in CPSR
MODE_BITS	DEFINE	0x1F		                                ; Bit mask for mode bits in CPSR
USR_MODE	DEFINE	0x10		                                ; User mode
FIQ_MODE	DEFINE	0x11		                                ; Fast Interrupt Request mode
IRQ_MODE	DEFINE	0x12		                                ; Interrupt Request mode
SVC_MODE	DEFINE	0x13		                                ; Supervisor mode
ABT_MODE	DEFINE	0x17		                                ; Abort mode
UND_MODE	DEFINE	0x1B		                                ; Undefined Instruction mode
SYS_MODE	DEFINE	0x1F		                                ; System mode

                                                                ; Control register C1



CP_DIS_MASK DEFINE  0xFFFFEFFA


;********************************************************************************************************
;                                            ARM EXCEPTION VECTORS
;********************************************************************************************************

    SECTION .intvec:CODE:NOROOT(2)
    PUBLIC  __vector
    PUBLIC  __iar_program_start

    IMPORT  OS_CPU_ARM_ExceptUndefInstrHndlr
    IMPORT  OS_CPU_ARM_ExceptSwiHndlr
    IMPORT  OS_CPU_ARM_ExceptPrefetchAbortHndlr
    IMPORT  OS_CPU_ARM_ExceptDataAbortHndlr
    IMPORT  OS_CPU_ARM_ExceptIrqHndlr
    IMPORT  OS_CPU_ARM_ExceptFiqHndlr
    
    
                                   ; Level 1 page table descriptor templates
TTB_ENTRY_SUPERSEC_FAULT  EQU  0x50006
TTB_ENTRY_SUPERSEC_STRONG EQU  0x50C02
TTB_ENTRY_SUPERSEC_DEV    EQU  0x50C06
TTB_ENTRY_SUPERSEC_NORM   EQU  0x51C0E
TTB_ENTRY_SEC_NORM        EQU  0x0C0E

    ARM

__vector:

    LDR     PC,Reset_Addr           ; Reset
    LDR     PC,Undefined_Addr       ; Undefined instructions
    LDR     PC,SWI_Addr             ; Software interrupt (SWI/SVC)
    LDR     PC,Prefetch_Addr        ; Prefetch abort
    LDR     PC,Abort_Addr           ; Data abort
    LDR     PC,Unused_Addr          ; RESERVED
    LDR     PC,IRQ_Addr             ; IRQ
    LDR     PC,FIQ_Addr             ; FIQ

    DATA

Reset_Addr:     DCD   __iar_program_start

Undefined_Addr: DCD   OS_CPU_ARM_ExceptUndefInstrHndlr
SWI_Addr:       DCD   OS_CPU_ARM_ExceptSwiHndlr
Prefetch_Addr:  DCD   OS_CPU_ARM_ExceptPrefetchAbortHndlr
Abort_Addr:     DCD   OS_CPU_ARM_ExceptDataAbortHndlr
Unused_Addr:    DCD   .
IRQ_Addr:       DCD   OS_CPU_ARM_ExceptIrqHndlr
FIQ_Addr:       DCD   OS_CPU_ARM_ExceptFiqHndlr


;********************************************************************************************************
;                                   LOW-LEVEL INITIALIZATION
;********************************************************************************************************

    SECTION FIQ_STACK:DATA:NOROOT(3)
    SECTION IRQ_STACK:DATA:NOROOT(3)
    SECTION SVC_STACK:DATA:NOROOT(3)
    SECTION ABT_STACK:DATA:NOROOT(3)
    SECTION UND_STACK:DATA:NOROOT(3)
    SECTION CSTACK:DATA:NOROOT(3)
    SECTION MMU_TT:DATA:NOROOT(3)
    SECTION .bss:DATA:NOROOT(3)
    SECTION text:CODE:NOROOT(2)
    REQUIRE __vector
    EXTERN  __cmain
    EXTWEAK __iar_init_core
    EXTWEAK __iar_init_vfp
    PUBLIC  __iar_program_start
    EXTERN  lowlevel_init

    ARM
__iar_program_start:
?cstartup:

                                                ; Add initialization needed before ...
                                                ; ... setup of stack pointers here.
                                                ; Disable Addr translation, D cache ...
                                                ; ... and enable I cache
    MRC         p15,0,R1,C1,C0,0	 ; Read System Control Register (SCTLR)
    LDR         R0,=CP_DIS_MASK      ; 0xFFFFEFFA
    AND         R1,R1,R0
    ORR         R1,R1,#(1<<12)
    MCR         p15,0,R1,C1,C0,0	 ; Write System Control Register (SCTLR)


;********************************************************************************************************
;                                    STACK POINTER INITIALIZATION
;********************************************************************************************************

    MRS     r0,CPSR                                             ; Original PSR value
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#SVC_MODE                                     ; Set Supervisor mode bits
    MSR     CPSR_c,r0                                           ; Change the mode
    LDR     sp,=SFE(SVC_STACK)                                  ; End of SVC_STACK
  
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#ABT_MODE                                     ; Set Abort mode bits
    MSR     CPSR_c,r0                                           ; Change the mode
    LDR     sp,=SFE(ABT_STACK)                                  ; End of ABT_STACK
  
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#UND_MODE                                     ; Set Undefined mode bits
    MSR     CPSR_c,r0                                           ; Change the mode
    LDR     sp,=SFE(UND_STACK)                                  ; End of UND_STACK
  
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#FIQ_MODE                                     ; Set FIR mode bits
    MSR     CPSR_c,r0                                           ; Change the mode
    LDR     sp,=SFE(FIQ_STACK)                                  ; End of FIQ_STACK
  
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#IRQ_MODE                                     ; Set IRQ mode bits
    MSR     CPSR_c,r0                                           ; Change the mode
    LDR     sp,=SFE(IRQ_STACK)                                  ; End of IRQ_STACK
  
    BIC     r0,r0,#MODE_BITS                                    ; Clear the mode bits
    ORR     r0,r0,#SYS_MODE                                     ; Set System mode bits
    MSR     CPSR_c,r0                                           ; Change the mode
    LDR     sp,=SFE(CSTACK)                                     ; End of CSTACK
  
  
    LDR     r0,=SFB(.intvec)
    MCR     p15, 0, r0, c12, c0, 0								; Set vector address in CP15 VBAR register
        
        
    MOV     r0, #0x0
    MCR     p15, 0, r0, c7, c5, 6                               ; Invalidate branch predictor

    MOV     r0, #0x0
    MCR     p15, 0, r0, c8, c7, 0                               ; Invalidate TLB

    MOV     r0, #0
    MCR     p15, 0, r0, c7, c5, 0                               ; Invalidate instruction cache
    
    BL      BSP_DCacheInvalidateAll
	
	; Set domain access
    MRC     p15, 0, r0, c3, c0, 0								; Read Domain Access Control Register
    LDR     r0, =0x55555555										; Set all Domains to Client
    MCR     p15, 0, r0, c3, c0, 0								; Write Domain Access Control Register


    ; Turn on core features assumed to be enabled.
    BL      __iar_init_core

    ; Initialize VFP (if needed).
    BL      __iar_init_vfp

Clear_Bss_Section:

         LDR   r0, =SFB(.bss)                 ; Start address of BSS
         LDR   r1, =SFE(.bss)           	  ; End address of BSS
         MOV   r2, #0  
Loop: 
         STR   r2, [r0], #4                    ; Clear one word in BSS
         CMP   r0, r1
         BLE   Loop                            ; Clear till BSS end


; Add more initialization here

; Continue to ?main for more IAR specific system startup
        B       __cmain

BSP_DCacheInvalidateAll:
    ; Invalidate L1 data cache
    MOV32     r0, #0x1FF            ; Load set index
BSP_DCacheInvalidateAll_loop_1:
    MOV     r1, #0x00000003         ; Load number of ways
BSP_DCacheInvalidateAll_loop_2:
    MOV     r2, r1, LSL #30
    ADD     r2, r2, r0, LSL #5
    MCR     p15, 0, r2, c7, c6, 2
    SUBS    r1, r1, #1
    BGE     BSP_DCacheInvalidateAll_loop_2
    SUBS    r0, r0, #1
    BGE     BSP_DCacheInvalidateAll_loop_1
    DSB

    BX      lr
    
                END
    
    



