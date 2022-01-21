.ORIG x3000
; write your code here
        AND R1, R1, #0 ;initializing digit counter
        ADD R1, R1, #4 ;make digit counter equal to 4
        BRz Done
        

Done    HALT ;End of the program