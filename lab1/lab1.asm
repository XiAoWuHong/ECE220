.ORIG x3000
; write your code here
        AND R1, R1, #0 ;initializing digit counter
        ADD R1, R1, #4 ;make digit counter equal to 4
Loop2   ADD R1, R1, #0 ;Setcc
        BRz Done
        AND R2, R2, #0
        ADD R2, R2, #4 ;initialize bit counter to 4
LoopIn  BRz BitEnd



BitEnd  ADD R3, R3, #-8
        ADD R3, R3, #-1
        BRnz ZeroAdd


Done    HALT ;End of the program