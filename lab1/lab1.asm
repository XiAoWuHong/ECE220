.ORIG x3000
; write your code here
        AND R6, R6, #0 ;initializing digit counter
        ADD R6, R6, #4 ;make digit counter equal to 4
        AND R4, R4, #0 ;initializing digit register
Loop2   ADD R6, R6, #0 ;Setcc
        BRz Done
        AND R2, R2, #0
        ADD R2, R2, #4 ;initialize bit counter to 4
LoopIn  BRz BitEnd

        ADD R3, R3, R3
        BRzp False
        ADD R4, R4, #1
False   ADD R4, R4, R4
        ADD R2, R2, #-2
        BR LoopIn

BitEnd  ADD R3, R3, #9
        BRnz ZeroAdd
        ADD R3, R3, #9
        ADD R3, R3, #-10
        BR OutCom
ZeroAdd ADD R3, R3, #9
        
OutCom  AND R0, R0, #0 ; initialize and clear R0
        ADD R0, R3, R0 ; Put character in R3 into R0
        OUT            ; Print Character in R0
        ADD R6, R6, #-1
        BR Loop2

Done    HALT ;End of the program
.END