		TTL Writing Memory Access Instructions
;***************************************************************
; Memory access and manipulation
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
;**********************************************************************
;**********************************************************************
Main

	LDR		R0, =ROM_Data
	LDR		R1, =0x0
	LDR		R2, =0x4
	
	LDR		R3, =0x8
	LDR 	R4, [R0]
	LDRH	R5, [R0, R2]
	LDRSB	R6, [R0, R3]
			
	LDR R7, =RAM_Data
	STRB R6, [R7]
	STRH R5, [R7, #4]
	MOV R4, R6
	STR R4, [R7, #8]

            B     	.       
            ALIGN
			
;**********************************************************************
;ROM Constants
;**********************************************************************
ROM_Data 
			DCD		0xAABBCCDD
			DCD		0x12345678
			DCD		0xF0E1D2C3					
			ALIGN 	
			END
