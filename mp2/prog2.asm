;
;
;
.ORIG x3000
	
;your code goes here

EVAL_SAVE_R7	.BLKW #1	; used to save R7 when nested subroutines are being used
INVALID			.STRINGZ "INVALID EXPRESSION"
AddOp			.FILL x2B	; +
SubOp			.FILL x2D	; -
MulOp			.FILL x2A	; *
DivOp			.FILL x2F	; /
ExpOp			.FILL x5E	; ^
Equal			.FILL x3D	; =
SPACE			.FILL x20	; " "
ASCII9			.FILL x39	; 9
ASCII0			.FILL x30	; 0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX ;taken from MP1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
	GETC	; get character from keyboard
	OUT		; echo character to monitor
	Finding
		LD R1, Equal
		NOT R1, R1
		ADD R1, R1, #1	; find the 2s comp additive inverse of "="
		AND R2, R2, #0
		ADD R2, R1, R0	; is the inputed character "="?
		BRz SuperDuperFinish

		LD R1, SPACE
		NOT R1, R1
		ADD R1, R1, #1	; find the 2s comp additive inverse of " "
		ADD R2, R1, R0	; is the inputed character " "?
		BRz EVALUATE

		LD R1, ASCII0
		NOT R1, R1
		ADD R1, R1, #1	; 2s comp of ASCII0
		AND R2, R2, #0
		ADD R2, R1, R0	; is the inputed character below 0 on the ASCII table?
		BRn CheckOperators

		LD R1, ASCII9
		NOT R1, R1
		ADD R1, R1, #1	; 2s comp of ASCII9
		AND R2, R2, #0	
		ADD R2, R1, R0	; is the inputed character above 9 on the ASCII table?
		BRp CheckOperators

		FindOperandand
		LD R1, ASCII0
		NOT R1, R1
		ADD R1, R1, #1
		ADD R0, R0, R1
		JSR PUSH
		JSR EVALUATE

		CheckOperators

			LD R1, AddOp
			NOT R1, R1
			ADD R1, R1, #1	; 2s comp of "+"
			ADD R2, R1, R0	; is the inputed character "+"?
			BRz Addition

			LD R1, SubOp
			NOT R1, R1
			ADD R1, R1, #1	; 2s comp of "-"
			ADD R2, R1, R0	; is the inputed character "-"?
			BRz Subtraction

			LD R1, MulOp
			NOT R1, R1
			ADD R1, R1, #1	; 2s comp of "*"
			ADD R2, R1, R0	; is the inputed character "*"
			BRz Multiplication

			LD R1, DivOp
			NOT R1, R1
			ADD R1, R1, #1	; 2s comp of "/"
			ADD R2, R1, R0	; is the inputed character "/"?
			BRz Divide

			LD R1, ExpOp
			NOT R1, R1
			ADD R1, R1, #1
			ADD R2, R1, R0
			BRz Exponent
			BR UhOh

	Addition
		ST 
		JSR PLUS
		
	Subtraction
		JSR MIN

	Multiplication 
		JSR MUL

	Divide
		JSR DIV

	Exponent 
		JSR EXP



; finish it
UhOh	
	LD R0, INVALID
	PUTS
SuperDuperFinish
	JSR PRINT_HEX
	HALT
;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; addition
;input R3, R4
;out R0
PLUS
	;your code goes here
	ADD R0, R3, R4	; adding R3 to R4 and putting the result into R0
	ST R7, EVAL_SAVE_R7	; saving R7 for nested subroutine use
	JSR PUSH
	LD R7, EVAL_SAVE_R7	; reloading R7 to go back to evaluate
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; subtraction
;input R3, R4
;out R0
MIN
	NOT R4, R4
	ADD R4, R4, #1	;2s comp of R4
	ADD R0, R3, R4	; subtracting R4 from R3
	ST R7, EVAL_SAVE_R7	; saving R7 so we can go into a nested subroutine
	JSR PUSH
	LD R7, EVAL_SAVE_R7	; reload R7 to go back to evaluate
	RET
;your code goes here
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; multiplication 
;input R3, R4
;out R0
MUL	
	AND R1, R1, #0	; initialize and clear R1
	ADD R1, R4, #0	; put R4 into R1
	ADD R3, R3, #0	; check if R3 is zero
	BRz Zero 
	MultiRep
	ADD R1, R4, R1	; add R4 to R1 once
	ADD R3, R3, #-1	; decrement R3
	BRz MultiFin	; check if multiplication is done 
	BR MultiRep	
	Zero 
	AND R0, R0, #0	; if R3 is zero
	BR BACK
	MultiFin
	AND R0, R0, #0	; clear R0
	ADD R0, R1, R0	; put value of R1 into R0
	BACK
	ST R7, EVAL_SAVE_R7	; save R7 so we can go to nested subroutine
	JSR PUSH
	LD R7, EVAL_SAVE_R7	; reload R7 so we can go back to evaluate
	RET
;your code goes here

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; division
;input R3, R4
;out R0
DIV	
	AND R0, R0, #0	; clear R0
	NOT R4, R4
	ADD R4, R4, #1	; get the 2s comp of R4
	DivRep
	ADD R3, R4, R3	; subtracting R4 from R3
	BRn DivDone 	; if there is a remainder or the division has completed then back to eval
	ADD R0, R0, #1	; if R4 goes into R3 add 1 to R0
	BRnzp DivRep
	DivDone			; repeat subtration process to continue dividing
	ST R7, EVAL_SAVE_R7	; save R7 to go to nested subroutine
	JSR PUSH
	LD R7, EVAL_SAVE_R7	; reload the R7 value that would take you back to eval
	RET
;your code goes here
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; exponents
;input R3, R4
;out R0
EXP
	AND R1, R1, #1
	ADD R1, R1, R3	; copy R3 into R1 so we can use R1 as a counter for the multplication loop
	AND R5, R5, #0
	ADD R5, R5, R1	; store the value of the counter for the multiplication loop in R5
	ADD R4, R4, #0	; check if R4 is 0 for the ZeroCase 
	BRz ZeroCase
	BR QuickSkip
	PowerLoop
	AND R1, R1, #0	; clear multiplication counter
	ADD R1, R5, R1	; reload multiplication counter
		QuickSkip
		AND R2, R2, #0	; clear R2	
		ADD R2, R3, R2	; copy current value of R3 into R2 for the power loop
			MultiLoopEXP
			ADD R3, R2, R3	; add value of R3 to itself via R2
			ADD R1, R1, #-1	; decrement multiplication counter
			BRp MultiLoopEXP
			ADD R4, R4, #-1
			BRz BackExp
			BR PowerLoop

	ZeroCase
	AND R0, R0, #0
	ADD R0, R0, #1
	BackExp
	ST R7, EVAL_SAVE_R7
	JSR PUSH
	LD R7, EVAL_SAVE_R7
	RET

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
