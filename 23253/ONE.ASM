
.model small
.stack 100h
.data
.code
        mov ax,@data
        mov dx,ax

        mov cx,26

        mov dl,41h
        mov ah,02h

        @loop:
        int 21h
        inc dl
        dec cx
        jnz @loop

        mov ah,4ch
        int 21h
end
