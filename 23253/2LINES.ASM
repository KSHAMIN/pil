.model small
.data
        msg1 db "Hello World...!"
        msg2 db "Welcome."
.code
        move ax,@data
        mov ds,ax
        lea dx,msg1
        mov ah, 09h
        int 21h


