.model small
.stack 100h
.data
        a db 09h
        b db 02h
        c db ?
.code
                mov ax,@data
                mov ds,ax

                mov al,a
                
                mov bl,b
 
                add al,bl
         	
                xor bx,bx
                mov bx,0Ah
                div bx
                int 21h
                
                add al,30h
                mov dl,al
                mov ah,02h
                int 21h

                mov ah,04ch
                int 21h

                end

