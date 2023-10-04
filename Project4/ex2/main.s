		TTL ASM Memory Access 
;***************************************************************
;Many variations of Load/Store/Move instructions
;copying data from ROM & storing to RAM

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
RAM_Data	SPACE	64			;Reserve space for variables in RAM @ label Ram_Data


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
			
;**********************************************************************
;**********************************************************************
;**********************************************************************
Main

			LDR		R0, =RAM_Data		;R0:= RAM address of RAM_Data from ROM
			LDR		R1, =ROM_Data		;R1:= ROM address of ROM_Data from ROM
			LDR		R2, =0xA1B1C1D1	;R2:=constant from ROM via PC-relative			
			

	;after compiling, the constant values above are stored starting at 0x0.0100 (in ROM)
			LDR		R3, [R1]		;R3:= word value @[R1]
			LDRH	R4, [R1,#4]		;R4:= halfword value @[R1+4], 2 upper bytes of R4 cleared (00)
			LDRB	R5, [R1,#6]		;R5:= byte @[R1+6], 3 upper bytes of R5 cleared (00)
			LDRB	R5, [R1]		;R5:= byte @[R1], 3 upper bytes of R5 cleared (00)
	;sign extending
	;ARMv6M only allows sign extended loads with register offsets
			LDR		R4, =0x0		;clear R4 as offset for next instruction
			LDRSB	R6, [R1,R4]		;R6:= byte @[R1], 3 upper bytes sign extended
			LDRSB	R7, [R1,R5]		;R7:= byte @[R1+4], 3 upper bytes sign extended
			LDR		R4, =10			;load R4 with offset for next instruction
			LDRSH	R3, [R1,R4]		;R3:= halfword @[R1+10], 2 upper bytes sign extended

	;stores
			STR		R2, [R0]		;store R2 to @[R0] (RAM)
			STRB	R2, [R0,#4]		;store lowest byte of R2 to @[R0+4] (RAM)
			STRH	R2, [R0,#8]		;store lower halfword of R2 to @[R0+8] (RAM)
			STRH	R3, [R0,#6]		;store lower halfword of R3 to @[R0+6] (RAM)
	;moves
			MOVS	R3, R2			;copy R2 value to R3
			MOVS	R4,#0xFF		;largest value available for this operation is 0xFF
			MVNS	R5, R2			;R5:= ~R2 (bit inverse of R2)

			B     	.       
            ALIGN
			
;**********************************************************************
;ROM Constants
;**********************************************************************
ROM_Data 

			DCD		0xFF00EE04
			DCD		0x22DD33CC
			DCD		0xB4A59687
;variations of constant storage directives
			DCB		0xAA,12,0xBB
			DCB		2_111010
	;after compiling, the constant values above are stored staring at 0x0.00F8 (in ROM)
			ALIGN 	
			END