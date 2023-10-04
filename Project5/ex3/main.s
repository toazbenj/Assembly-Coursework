	TTL Calculate Average
;***************************************************************
; Averaging memory values
;***************************************************************
;Assembler directives
            THUMB
;***************************************************************
;EQUates
;Vectors
VECTOR_TABLE_SIZE EQU 0x000000C0  ;KL25Z
VECTOR_SIZE       EQU 4           ;Bytes per vector
;Memory
SSTACK_SIZE EQU  0x00000100
;NVIC
ICER		EQU	 0xE000E180
;**********************************************************************
;Vector Table Mapped to Address 0 at Reset
;Linker requires __Vectors to be exported
            AREA    RESET, DATA, READONLY
            EXPORT  __Vectors
__Vectors 
            DCD  SP_INIT        ;stack pointer value when stack is empty
            DCD  Reset_Handler  ;reset vector
			SPACE  (VECTOR_TABLE_SIZE - (2 * VECTOR_SIZE))
            ALIGN
;**********************************************************************
            AREA    RAM,DATA,READWRITE
;Allocate system stack
SSTACK      SPACE   SSTACK_SIZE
SP_INIT
;Variables go here
RAM_Data    SPACE   64    ;reserve space for 64 variables @ label Ram_Data

;**********************************************************************
;Program
;Linker requires Reset_Handler
            AREA    StudentCode,CODE,READONLY
            ENTRY
            EXPORT  Reset_Handler
			
Reset_Handler
			CPSID   I       ;Mask interrupts
; DISABLE INTERRUPTS
			LDR 	R0, =ICER 	;R0 = &ICER
			MOVS 	R1,	#0 		; R1 = 0
			MVNS 	R1, R1 		; R1 = 0xFFFFFFFF
			STR 	R1, [R0, #0]; ICER = 0xFFFFFFFF
; INIT STACK POINTER
			LDR R0, =SP_INIT 	; load base address
			MOV SP, R0		; set SP to base address
			
;**********************************************************************

Main

			LDR		R6, =ROM_Con 
			LDR		R7, =RAM_Data

			LDR R1, =0x0
another
			LDRB R3, [R6, R1]; get constant
			ADDS R2, R3 ; SUM VALUES
			ADDS R1, #1  ;add 1 to existing value in R1
			
			CMP		R1, #8     ;CoMPare: test if value in R1 = 8
			BNE		another     ;Branch to 'another' if R1 Not Equal to 1
			
			LSRS R2, #3; divide by 8

            B     	.       
            ALIGN
			
;**********************************************************************
;ROM Constants
;**********************************************************************
ROM_Con ;address label for constants stored in ROM
			DCB		1, 6, 2, 9	;will store each decimal value as a hex byte
			DCB		7, 0, 3, 4
			ALIGN 	
			END
