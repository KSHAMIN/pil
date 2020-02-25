.model small
.stack 100h
.data
        msg1 db 'Enter 1st no.:',13,10,'$'
        msg2 db 'Enter 2nd no.:',13,10,'$'
        msg3 db 'Result is:$'
        

.code
                mov ax,@data
                mov ds,ax

                LEA dx,msg1
                mov ah,09h
                int 21h
                mov ah,01h
                mov bl,al
                sub bl,30h
                int 21h

                LEA dx,msg2
                mov ah,09h
                int 21h
                mov ah,01h
                sub al,30h
                int 21h

                LEA dx,msg3
                mov ah,09h
                int 21h

                add al,bl
                add al,30h   
                mov dl,al
                mov ah,02h
                int 21h

                mov ah,04ch
                int 21h
                end



                
                
