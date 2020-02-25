
.model small
.stack 100h
.data
        msg db 10,13, 'Enter input:$'
        a db 10,13,'Output:$'
        arr db 5 dup(?)
.code
                mov ax,@data
                mov ds,ax

           

                mov cx,5
                mov si,0

                l1:
                        mov dx,offset msg
                        mov ah,09h
                        int 21h
                        mov ah,01h
                        int 21h
                        mov arr[si],al
                        inc si
                        dec cx
                        jnz l1

                 mov cx,5
                 mov si,0

                 l2:
                        lea dx,a
                        mov ah,09h
                        int 21h
                        mov dl,arr[si]
                        mov ah,2h
                        int 21h
                        inc si
                        loop l2

                 mov ah,4ch
                 int 21h

                 end

