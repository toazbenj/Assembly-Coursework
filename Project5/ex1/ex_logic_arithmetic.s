		TTL		Logic & Arithmetic Examples			;Name of program
;***************************************************************
;Examples of all format variations of logic and shift instructions
;Several examples of assembly arithmetic instructions  
; //By A.Mason, 2015 //
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
			LDR		R0, =0x00000000	;load constants into R0-R3
			LDR		R1, =0xFFFFFFFF	
			LDR		R2, =0xAAAA5555
	;logic functions
Logic		MVNS	R3, R2			;bit inverse
			MOVS 	R4, R1 			;initialize R4, prepare for ANDS
			ANDS	R4, R2	 		;logic AND, R4 is both Rd and Rn
; can also write this as ANDS  R4,R4,R2
			MOVS 	R5, R2			;initialize R5, prepare for ORRS
			ORRS	R5, R3 			;logic OR, A|~A=1
			MOVS 	R6, #0xFF		;initialize R6, prepare for EORS
			EORS	R6, R2			;exclusive OR
	;bit set
			MOVS 	R7, R0			;clear R7, prepare for bit set
			ORRS	R7, R2 			;observe the bits being set (high) in R7
	;bit clear
			MOVS 	R0, R1 			;initialize R0 with 0xFFFFFFFF
			BICS 	R0, R2 			;observe the bits being cleared in R7
;**********************************************************************
Shift
;logic shift left
		LDR		R0, =0x4		;number of bit shifts
		LDR		R1, =0xF00FF00F	;test value to shift (reference)
		LDR		R2, =0xF00FF00F	;copy test value to shift
		LSLS	R2, R2, R0		;shift left by 4

		LDR		R3, =0xF		;another test value to shift
		LSLS	R4, R3, #28		;shift R1(0xF) to far left

;logic shift right
		LDR		R0, =0x8		;number of bit shifts
		LDR		R1, =0xF00FF00F	;test value to shift (reference)
		LDR		R2, =0xF00FF00F	;copy test value to shift
		LSRS	R2, R0			;shift right by 8
		LSRS	R3, R2, #1		;shift right by 1

;arithmetic shift right
		LDR		R0, =0x10		;number of bit shifts (16)
		LDR		R1, =0xF00FF00F	;test value to shift (reference)
		LDR		R2, =0xF00FF00F	;copy test value to shift
		ASRS	R2, R0			;shift right 16, sign extend

		LDR		R3, =0xF		;another test value to shift
		ASRS	R4, R3, #3		;shift R1(0xF) right 3, sign extend
;**********************************************************************
Math
		LDR		R0, =0xFFFFFFFF	;load constants into R0-R3
		LDR		R1, =0xA5
		LDR		R2, =0x08
		LDR		R3, =0x00000000	
;additions
		ADDS	R3, #255	;R3 = R3 + 255
		ADDS	R4,R1,R2	;R5=R1+R2
		ADDS	R5,R2,#1	;R5 = increment (add 1 to) R2
;subtracts
		LDR		R3, =0x00000001	;reset R3
		SUBS	R3,#1		;R3 = R3 - 1 (max subtractant = 255)
		SUBS	R4,R0,#0x7	;R4 = R0 - 7 (max subtractant = 7)
		LDR		R5, =0xA4	;preset R5
		SUBS	R5,R1		;R5 = R5 - R1
		LDR		R6, =0x80000000	;preset R6
		SUBS	R7,R6,R2
;compare
		CMP		R2,R1
		CMP		R2, #0x8
		CMN		R3,R0
;multiply			
		LDR		R4, =0x2	;preset R5
		MULS	R4,R2,R4	;R4 = R2 * R4
		LDR		R5, =0x2	;preset R5
		MULS	R5,R5		;R5 = R5 * R5

;stop
			B     	.       		;infinite loop
		ALIGN
			END