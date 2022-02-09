;
;
;
.ORIG x3000
	
;your code goes here

EVAL_SAVE_R7 .BLKW #1







;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

	Addition
		JSR PLUS
	Subtraction
		JSR MIN
	Multiplication 
		JSR MUL
	Divide
		JSR DIV
	Exponent 
		JSR EXP


;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; addition
;input R3, R4
;out R0
PLUS	
	;your code goes here
	ADD R0, R3, R4	; adding R3 to R4 and putting the result into R0
	ST R7, EVAL_SAVE_R7
	JSR PUSH
	LD R7, EVAL_SAVE_R7
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; subtraction
;input R3, R4
;out R0
MIN
	NOT R4, R4
	ADD R4, R4, #1
	ADD R0, R3, R4
	ST R7, EVAL_SAVE_R7
	JSR PUSH
	LD R7, EVAL_SAVE_R7
;your code goes here
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; multiplication 
;input R3, R4
;out R0
MUL	
	AND R1, R1, #0	; initialize and clear R1
	ADD R1, R4, #0	; put R4 into R1
	ADD R3, R3, #0	; check if R3 is zero
	BRz Zero 
	ADD R1, R4, R1	; add R4 to R1 once
	ADD R3, R3, #-1	; decrement R3
	BRz BACK
	Zero 
	AND R0, R0, #0
	BACK
	ST R7, EVAL_SAVE_R7
	JSR PUSH
	LD R7, EVAL_SAVE_R7
	RET
;your code goes here

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; division
;input R3, R4
;out R0
DIV	
;your code goes here
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; exponents
;input R3, R4
;out R0
EXP
;your code goes here
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
