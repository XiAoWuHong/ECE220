.ORIG x3000
PRINT_HIST

; you will need to insert your code to print the histogram here

; R0 is used to print and hold values temporarily 
; R1 holds the address for the histogram data
; R2 holds the ASCII character
; R3 holds the data held in the address of the histogram data
; R4 is the loop counter
; R5 is the digit counter
; R6 is the bit counter 

; stuff from lab1
	AND R5, R5, #0		; initialize digit counter
	ADD R5, R5, #4 
	ST R7, EVAL_SAVE_R7	; saving R7 for nested subroutine use
	JSR POP 
	LD R7, EVAL_SAVE_R7	; reloading R7 to go back to evaluate
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




; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments




DONE	HALT			; done

; my constants
ASCIIStart	.FILL x40
NewLine		.FILL xA
ASCIIA		.FILL x41
ASCII_0		.FILL x30
ASCII_SP	.FILL x20


.END