.ORIG x3000
; write your code here
        AND R1, R1, #0 ;initializing digit counter
        ADD R1, R1, #4 ;make digit counter equal to 4
Loop2   ADD R1, R1, #0 ;Setcc
        BRz Done
        AND R2, R2, #0
        ADD R2, R2, #4 ;initialize bit counter to 4
LoopIn  BRz BitEnd



BitEnd  ADD R3, R3, #9
        BRnz ZeroAdd
        ADD R3, R3, #9
        ADD R3, R3, #-10
        BR OutCom
ZeroAdd ADD R3, R3, #9
        
OutCom  AND R0, R0, #0 ; initialize and clear R0
        ADD R0, R3, R0 ; Put character in R3 into R0
        OUT            ; Print Character in R0


Done    HALT ;End of the program