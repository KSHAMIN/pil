.model small
.stack 100h
initz macro
        mov ax,@data
        mov ds,ax
endm

xyz macro
        mov ah,4ch
        int 21h
endm

.data
        msg db 'HELLO!',13,10,'$'
.code
                initz

                lea dx,msg
                mov ah,09h
                int 21h

                xyz
                end


