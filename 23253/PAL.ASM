.model medium
.stack 100h
.data
        msg1 db 13,10,'Enter string:$'
        msg2 db 13,10,'It is a palindrome!$'
        msg3 db 13,10,'It is not a palindrome!!$'
        str1 db 100 dup('$')
        str2 db 100 dup('$')
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
		xor ax,ax
		
		lea di,str2
                
                loop2:
                        dec si
                        mov al,[si]
                        mov [di],al                     
                        inc di  
                        dec cx
                        cmp cx,0
                        jne loop2
                        
                xor ax,ax
                xor dx,dx
                
                lea dx,str2
                mov ah,09h
                int 21h
                
                xor ax,ax
                xor dx,dx

                lea si,str1
                lea di,str2
                
                loop3:
                	xor ax,ax
                        mov al,[si]
                        mov ah,[di]
                        cmp al,ah
                        jne line1
                        inc si
                        inc di
			cmp al,'$'
			jne loop3

                xor dx,dx
                
                lea dx,msg2
                mov ah,09h
                int 21h
                jmp exit

                line1:
                        xor dx,dx
                        lea dx,msg3
                        mov ah,09h
                        int 21h

		 exit:
                 mov ah,04ch
                 int 21h

                 end










                        












