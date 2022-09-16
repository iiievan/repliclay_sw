;******************************************************************************
;
; init.S - Init code routines
;
;******************************************************************************
;
; Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
;
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;
;    Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;******************************************************************************

        MODULE  startcode

;****************************** Forfard Declaration*********************************
        SECTION .bss:DATA:NOROOT(8)
        SECTION CSTACK:DATA:NOROOT(8)
        
        SECTION .startcode:CODE:NOROOT(8)
        ARM
        
;****************************** Global Symbols*********************************
        PUBLIC Entry
        EXTERN  __iar_program_start
        PUBLIC _stack                  
        PUBLIC _bss_start
        PUBLIC _bss_end
        PUBLIC start_boot
        EXTERN CopyVectorTable

;************************ Internal Definitions ********************************
;
; Define the stack sizes for different modes. The user/system mode will use
; the rest of the total stack size
;
UND_STACK_SIZE        EQU        0x1000
ABT_STACK_SIZE        EQU        0x1000
FIQ_STACK_SIZE        EQU        0x1000
IRQ_STACK_SIZE        EQU        0x1000
SVC_STACK_SIZE        EQU        0x1000

;
; to set the mode bits in CPSR for different modes
;        
MODE_USR        EQU      0x10            
MODE_FIQ        EQU      0x11
MODE_IRQ        EQU      0x12
MODE_SVC        EQU      0x13
MODE_ABT        EQU      0x17
MODE_UND        EQU      0x1B
MODE_SYS        EQU      0x1F            

I_F_BIT         EQU      0xC0               

;**************************** Code Seection ***********************************
        


;******************************************************************************
;
;******************************************************************************
;
; The reset handler in StarterWare is named as 'Entry'.
; The reset handler sets up the stack pointers for all the modes. The FIQ and
; IRQ shall be disabled during this. Then clear the BSS sections and finally
; switch to the function calling the main() function.
;

_bss_start: DC32 SFB(.bss)        
_bss_end:   DC32 SFE(.bss)        
_stack:     DC32 SFB(CSTACK)
        
Entry
;
; Set up the Stack for Undefined mode
;
         LDR   r0, =_stack                     ; Read the stack address
         MSR   cpsr_c, #MODE_UND|I_F_BIT       ; switch to undef  mode
         MOV   sp,r0                           ; write the stack pointer
         SUB   r0, r0, #UND_STACK_SIZE         ; give stack space
;
; Set up the Stack for abort mode
;        
         MSR   cpsr_c, #MODE_ABT|I_F_BIT       ; Change to abort mode
         MOV   sp, r0                          ; write the stack pointer
         SUB   r0,r0, #ABT_STACK_SIZE          ; give stack space
;
; Set up the Stack for FIQ mode
;       
         MSR   cpsr_c, #MODE_FIQ|I_F_BIT       ; change to FIQ mode
         MOV   sp,r0                           ; write the stack pointer
         SUB   r0,r0, #FIQ_STACK_SIZE          ; give stack space
;
; Set up the Stack for IRQ mode
;       
         MSR   cpsr_c, #MODE_IRQ|I_F_BIT       ; change to IRQ mode
         MOV   sp,r0                           ; write the stack pointer
         SUB   r0,r0, #IRQ_STACK_SIZE          ; give stack space
;
; Set up the Stack for SVC mode
;        
         MSR   cpsr_c, #MODE_SVC|I_F_BIT       ; change to SVC mode
         MOV   sp,r0                           ; write the stack pointer
         SUB   r0,r0, #SVC_STACK_SIZE          ; give stack space

;
; Set up the Stack for USer/System mode
;      
         MSR   cpsr_c, #MODE_SYS|I_F_BIT       ; change to system mode
         MOV   sp,r0                           ; write the stack pointer






; Invalidate and Enable Branch Prediction  
         MOV     r0, #0
         MCR     p15, #0, r0, c7, c5, #6
         ISB
         MRC     p15, #0, r0, c1, c0, #0
         ORR     r0, r0, #0x00000800
         MCR     p15, #0, r0, c1, c0, #0

;
; Enable Neon/VFP Co-Processor
;
        MRC p15, #0, r1, c1, c0, #2           ; r1 = Access Control Register
        ORR r1, r1, #(0xf << 20)              ; enable full access for p10,11
        MCR p15, #0, r1, c1, c0, #2           ; Access Control Register = r1
        MOV r1, #0
        MCR p15, #0, r1, c7, c5, #4           ;flush prefetch buffer
        MOV r0,#0x40000000
        FMXR FPEXC, r0                        ; Set Neon/VFP Enable bit

;
; Clear the BSS section here
;
Clear_Bss_Section

         LDR   r0, =_bss_start                 ; Start address of BSS
         LDR   r1, =(_bss_end - 0x04)          ; End address of BSS
         MOV   r2, #0  
Loop 
         STR   r2, [r0], #4                    ; Clear one word in BSS
         CMP   r0, r1
         BLE   Loop                            ; Clear till BSS end

;
; Enter the start_boot function. The execution still happens in system mode.
;
/**
 * \brief   This function does two operations:\n
 *          1> Copies an array which contains vector table values to the
 *             processor's vector table space.\n
 *          2> Then it calls the main() function.\n
 *
 * \param   None.
 *
 * \return  None.
 * 
 * \note    This function is the first function that needs to be called in a
 *          system. This should be set as the entry point in the linker script
 *          file if the ELF executable is to loaded via a debugger on the
 *          target. This function never returns, but gives control to the
 *          application entry point.
 **/        
Enter_main
         
         LDR   r10,=start_boot
         MOV   lr,pc                           ; Dummy return from start_boot
         BX    r10                             ; Branch to start_boot
         SUB   pc, pc, #0x08                   ; looping

start_boot
        LDR     R0, =CopyVectorTable
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

;
; End of the file
;
    END
    
    



