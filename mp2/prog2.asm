;
;
;
.ORIG x3000
	
;your code goes here

EVAL_SAVE_R7	.BLKW #1	; used to save R7 when nested subroutines are being used
SAVE_R5		.BLKW #1	; used to save R5 cuz I love it
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
ASCIIA		.FILL x41

JSR EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX ;taken from MP1
	ST R7, EVAL_SAVE_R7
	ST R5, SAVE_R5
	; stuff from lab1
		AND R5, R5, #0		; initialize digit counter
		ADD R5, R5, #4 
		ADD R3, R0, #0		; put data at histogram address into R3

	UghLoop
		AND R0, R0, #0		; clear R0 for reuse
		AND R6, R6, #0		; initialize bit counter
		ADD R6, R6, #4		; set bit counter to 4
		PPloop
		ADD R0, R0, R0		; left shift digit
		ADD R3, R3, #0		; setcc
		BRzp NoOne
		ADD R0, R0, #1		; add one to the LSB of digit
		NoOne
		ADD R3, R3, R3		; left shift R3 (data from histogram)
		ADD R6, R6, #-1		; decrement bit counter
		BRp PPloop			; does R6 (bit counter) equal zero? If not then go back up to PPloop

	;lab1
		ADD R0, R0, #-10
		AND R6, R6, #0
		ADD R6, R0, #0
		BRzp let
		BR Num 
		let
		LD R0, ASCIIA
		BR QuickSkip2
		Num
		LD R0, ASCII0
		ADD R6, R6, #10
		QuickSkip2
		ADD R0, R0, R6	
		OUT	
		ADD R5, R5, #-1		; decrement digit counter
		BRp UghLoop
	LD R5, SAVE_R5
	LD R7, EVAL_SAVE_R7	; reloading R7 to go back to evaluate
	RET
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
		BRz SuperFinish

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

		FindOperand
		LD R1, ASCII0
		NOT R1, R1
		ADD R1, R1, #1
		ADD R0, R0, R1
		JSR PUSH
		BR EVALUATE

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
			ADD R1, R1, #1	; 2s comp of "^"
			ADD R2, R1, R0	; is the inputed character "^"?
			BRz Exponent
			BR UhOh

		Operators
			Addition
				JSR POP				; get value for R4
				AND R4, R4, #0
				ADD R4, R0, #0
				JSR POP				; get value for R3
				AND R3, R3, #0
				ADD R3, R0, #0
				ADD R5, R5, #0
				BRp UhOh
				JSR PLUS			; execute PLUS subroutine
				BR EVALUATE			;back to evaluate

			Subtraction
				JSR POP				; get value for R4
				AND R4, R4, #0
				ADD R4, R0, #0
				JSR POP				; get value for R3
				AND R3, R3, #0
				ADD R3, R0, #0
				ADD R5, R5, #0
				BRp UhOh
				JSR MIN
				BR EVALUATE

			Multiplication 
				JSR POP				; get value for R4
				AND R4, R4, #0
				ADD R4, R0, #0
				JSR POP				; get value for R3
				AND R3, R3, #0
				ADD R3, R0, #0
				ADD R5, R5, #0
				BRp UhOh
				JSR MUL
				BR EVALUATE

			Divide
				JSR POP				; get value for R4
				AND R4, R4, #0
				ADD R4, R0, #0
				JSR POP				; get value for R3
				AND R3, R3, #0
				ADD R3, R0, #0
				ADD R5, R5, #0
				BRp UhOh
				JSR DIV
				BR EVALUATE

			Exponent 
				JSR POP				; get value for R4
				AND R4, R4, #0
				ADD R4, R0, #0
				JSR POP				; get value for R3
				AND R3, R3, #0
				ADD R3, R0, #0
				ADD R5, R5, #0
				BRp UhOh
				JSR EXP
				BR EVALUATE


; finish it
UhOh	
	LEA R0, INVALID
	PUTS
	BR SuperDuperFinish
SuperFinish
	JSR POP
	JSR POP
	ADD R5, R5, #0
	BRz UhOh
	ADD R5, R0, #0
	JSR PRINT_HEX
	SuperDuperFinish
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
	ADD R1, R4, #0	; put R4 into R1
	ADD R3, R3, #0	; check if R3 is zero
	BRz Zero 
	MultiRep
	ADD R3, R3, #-1	; decrement R3
	BRz MultiFin	; check if multiplication is done 
	ADD R1, R4, R1	; add R4 to R1 once
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
	ADD R1, R3, #0	; copy R3 into R1 so we can use R1 as a counter for the multplication loop
	ADD R5, R1, #0	; store the value of the counter for the multiplication loop in R5
	ADD R4, R4, #0	; check if R4 is 0 for the ZeroCase 
	BRz ZeroCase
	ADD R4, R4, #-1	; power becomes n-1
	BR QuickSkip
	PowerLoop
	AND R1, R1, #0	; clear multiplication counter
	ADD R1, R5, R1	; reload multiplication counter
		QuickSkip
		ADD R2, R3, #0	; copy current value of R3 into R2 for the power loop [R2 <- R3 (subtotal)]
		AND R3, R3, #0	; clear R3 
			MultiLoopEXP	; R3 <- R2 * R1
			ADD R3, R2, R3	; add value of R3 to itself via R2
			ADD R1, R1, #-1	; decrement multiplication counter
			BRp MultiLoopEXP
				ADD R0, R3, #0	; put R3 into R0 to store current resultant
			ADD R4, R4, #-1	; decrement powerloop
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
