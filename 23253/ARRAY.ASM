
.model small
.stack 100h
.data
        arr db 50 dup(?)
        a db 'Define size of array:',13,10,'$'
        b db 13,10,'Enter element:$'
        c db 13,10,'Output:$'
.code
                mov ax,@data
                mov ds,ax

                lea dx,a
                mov ah,09h
                int 21h

                mov ah,01h
                int 21h
                sub al,30h

                mov cl,al
                mov bl,al
                mov si,0

                l1:
                        lea dx,b
                        mov ah,09h
                        int 21h

                        mov ah,01h
                        int 21h
                        mov arr[si],al
                        inc si
                        loop l1
                 lea dx,c
                 mov ah,09h
                 int 21h

                 mov cx,bx
                 mov si,0

                 l2:
                        mov dl,arr[si]
                        mov ah,2h
                        int 21h
                        inc si
                        loop l2

                  mov ah,4ch
                  int 21h

                  end



