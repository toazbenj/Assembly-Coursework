		TTL Assembly Instructions
;***************************************************************
Branching and looping
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
; Load constants
			LDR		R0, =0
			LDR		R1, =0x0
			LDR		R2, =0x1
			LDR		R7, =RAM_Data
		


another
			ADDS	R1, R1, #4  ;add 4 to existing value in R1
			CMP		R1, #16     ;CoMPare: test if value in R1 = 16
			BNE		another     ;Branch to 'another' if R1 Not Equal to 16, else continue
			STR R1, [R7]
			
			LDR		R1, =0x0	;reset R1 to 0			
			STR		R1, [R7,#4] ;initilize [RAM_Data+4]
loop1
			STR R2, [R7, #4]
			;ADDS R7, #4
			LSLS	R2, #1		;shift mask bit to left by 1
			BPL		loop1		;Branch to 'loop1' if R2 is PLus (positive), ie until mask bit shifts to bit-31, else contin
			;LDR		R7, =RAM_Data; RESET R7

			LDR		R2, =0x1	;reset R2 to 1
			LDR		R1, =0x0	;reset R1 to 0			
			STR		R1, [R7,#8] ;initilize [RAM_Data+8]
loop2
	
			LDR R1, [R7, #8]
			ORRS	R1, R1, R2	;bit set R1 with mask in R2
			
			STR R1, [R7, #8]
			LSLS	R2, #1		;shift mask bit to left by 1
			BPL		loop2		;Branch to 'loop2' if R2 is PLus (positive), ie until mask bit shifts to bit-31, else continue
		
			LDR		R2, =0x1	;reset R2 to 1
			LDR		R1, =0xFFFFFFFF	;reset R1 to all 1s
			STR		R1, [R7,#12] ;initilize [RAM_Data+12]
			
			
loop3
			LDR R1, [R7, #12]
			BICS	R1, R1, R2	;bit clear R1 with mask in R2
			
			STR R1, [R7, #12]
			LSLS	R2, #1		;shift mask bit to left by 1
			BPL		loop3		;Branch to 'loop3' if R2 is PLus (positive), ie until mask bit shifts to bit-31, else continue

			B .
			ALIGN
			END