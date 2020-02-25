.model small
.stack 100h
.data
        string db 13,10,'hello$'
        msg1 db 13,10,'Enter string:$'
        msg2 db 'Reversed string is:',13,10,'$'
        str1 db 100 dup('$')
.code
                mov ax,@data
                mov ds,ax
		
		lea dx,msg1
		mov ah,09h
		int 21h
		
		lea si,str1
		mov ah,01h
		
                mov cx,0h

                loop1:
                        int 21h
                        mov [si],al  
                        inc si
                        inc cx
                        cmp al,13
                        jne loop1
                      
                xor dx,dx        
                lea dx,msg2
                mov ah,09h
                int 21h
		
		xor ax,ax
		
                 loop2:
                 	dec si
                        xor dx,dx
                        mov dx,[si]
                        mov ah,02h
                        int 21h
                        dec cx
                        cmp cx,0
                        jne loop2

                  mov ah,04ch
                  int 21h

                  end


