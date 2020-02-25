     page 60,132
TITLE A04ASM2 (EXE) Move and add operations
;----------------------------------------------------------------------
         .MODEL  SMALL
         .STACK  64       ;Define stack
         .Data            ;Define data
 FLDD     DW     175
 FLDE     DW     150
 FLDF     DW     ?
 ;----------------------------------------------------------------------
          .CODE           ;Define code segment
 MAIN     PROC   FAR
          MOV    AX,@data ;Set address of data
          MOV    DS,AX    ; segment in DS
          MOV    AX,FLDD  ;MOVE 0175 TO AX
          ADD    AX,FLDE  ;ADD 0150 TO AX
          MOV    FLDF,AX  ;STORE SUM IN FLDF
          MOV    AX,4C00H ;End processing
          INT    21H
 MAIN     ENDP            ;End of procedure
          END    MAIN     ;End of program
