		TTL		Logic & Arithmetic 
;***************************************************************
;Logic_arithmetic 
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
			MOV SP, R0			; set SP to base address
			MOVS R1, #0	;clear R1
			MOVS R0, #0	;clear R0


;**Register assignments:
;R0 = results register, store task results here
;R1, R2, R3, user registers
;R4, R5, R6, pre-set values
;R7 = pointer to constants in ROM @ ROM_Con
;
Main
			LDR		R7, =ROM_Con	;load address of ROM constants to R7
;load constant values into R6:4. binary equivalent shown in comment
			LDR		R6, =0xFFFF7310 ;1111.1111.1111.1111.0111.0011.0001.0000	
			LDR		R5, =0xAAAA5555 ;1010.1010.1010.1010.0101.0101.0101.0101	
			LDR		R4, =0x1E1E1E1E ;0001.1110.0001.1110.0001.1110.0001.1110
			

			MVNS R0, R5; inverse of R5 in the results register (R0)
			LDR R1, =0xFFFFFFFF 

			MOV R0, R1; R0 SUBS FOR R1
			EORS R0, R4; R0 DESTINATION AND ARGUMENT

			MOV R0, R1
			BICS R0, R6
			ORRS R0, R4

			LDRB R4, [R7]
			ADDS R0, R4, #3

			MOV R0, R5
			LDR R2, =0x333333
			SUBS R0, R2

			LDR R2, [R7, #4]
			CMP R6, R2

			LDR R0, [R7, #8]
			LSLS R0, #4
			LSRS R0, #7

			ASRS R6, #16


			B     	.       		
		ALIGN
;**********************************************************************
;ROM Constants
;**********************************************************************
ROM_Con ;address label for constants stored in ROM

con1		DCD	0xE
con2		DCD	0xFFFF7310
con3		DCD	0x01010101	
			ALIGN 	
			END