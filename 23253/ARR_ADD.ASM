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

                mov dx,offset a
                mov ah,09h
                int 21h

                mov ah,01h
                int 21h
                sub al,30h

                mov cl,al
                mov bl,al
                mov si,0

                l1:
                        mov dx,offset b
                        mov ah,09h
                        int 21h

                        mov ah,01h
                        int 21h
                        sub al,30h
                        mov arr[si],al
                        inc si
                        dec cx
                        jnz l1

                  
                 
                  mov dx,offset c
                  mov ah,09h
                  int 21h

                 
                  mov cx,bx
                  mov si,0
                  xor dx,dx
                  

                  l2:
                        add dl,arr[si]
                        int 21h
                        inc si
                        loop l2

                   
                        
                  add dl,30h
                  mov ah,02h
                  int 21h

                  mov ah,04ch
                  int 21h

                  end


