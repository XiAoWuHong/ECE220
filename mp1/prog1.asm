;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; R0 is used to print and hold values temporarily 
; R1 holds the address for the histogram data
; R2 holds the ASCII character
; R3 holds the data held in the address of the histogram data
; R4 is the loop counter
; R5 is the digit counter
; R6 is the bit counter 

	AND R1, R1, #0		; clear R1
	AND R2, R2, #0		; clear R2
	LD R4, NUM_BINS		; Set loop counter
	LD R2, ASCIIStart	; ASCII @
	LD R1, HIST_ADDR	; address of histogram data
LoopLoop
	AND R0, R0, #0		; clear R0
	ADD R0, R0, R2		; put ASCII value
	OUT					; print R0
	LD R0, ASCII_SP		; load space character into R0
	OUT					; print space
	ADD R2, R2, #1		; increment ASCII value

; stuff from lab1
	AND R5, R5, #0		; initialize digit counter
	ADD R5, R5, #4 
	LDR R3, R1, #0		; put data at histogram address into R3
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


	ADD R0, R0, #-10
	AND R6, R6, #0
	ADD R6, R0, #0
	BRzp let
	BR Num 
let
	LD R0, ASCII_A
	BR QuickSkip
Num
	LD R0, ASCII_0
	ADD R6, R6, #10
	QuickSkip
	ADD R0, R0, R6
	OUT	
	ADD R5, R5, #-1
	BRp UghLoop

	LD R0, NewLine		; Load NewLine value into R0
	OUT
	ADD R1, R1, #1
	ADD R4, R4, #-1		; decrement loop counter
	BRp LoopLoop




; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments




DONE	HALT			; done

; my constants
ASCIIStart	.FILL x40
NewLine		.FILL xA
ASCII_A		.FILL x41
ASCII_0		.FILL x30
ASCII_SP	.FILL x20

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END

