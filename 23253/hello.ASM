.model small
.stack 100h
.data
        abc db 'Hello World!',13,10,'$'
        xyz db 'PICT',13,10,'$'
.code
                mov ax,@data
                mov ds,ax

                mov ah,09h
                mov dx,OFFSET abc
                int 21h

                LEA dx,xyz
                mov ah,09h
                int 21h

                mov ah,04ch
                int 21h

                end
