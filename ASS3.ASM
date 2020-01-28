.model medium

disp macro msg
lea dx,msg
mov ah,09h
int 21h
endm

.stack 100h
.data
	str1 db 100 dup('$')
        msg1 db 13,10,'Enter string:$'
        msg2 db 13,10,'*******It is a palindrome!*******$'
        msg3 db 13,10,'*******It is not a palindrome!!*******$'
        msg4 db 13,10,'     String length is:$'
        msg5 db 13,10,'     Reversed string is:$'
        msg6 db 13,10,'*******Invalid Entery*******$'
        menu1 db 13,10,'*****MENU*****$'
        menu2 db 13,10,'1)Enter string$'
        menu3 db 13,10,'2)Find string length$'
        menu4 db 13,10,'3)Check palindrome$'
        menu5 db 13,10,'4)Reverse the string$'
        menu6 db 13,10,'5)Exit$'
        menu7 db 13,10,'6)Enter your choice$'
.code
                mov ax,@data
                mov ds,ax
		
		menu:
			disp menu1
			disp menu2
			disp menu3
			disp menu4
			disp menu5
			disp menu6
			disp menu7
			
			mov ah,01h
			int 21h
			
			cmp al,31h
			je input
			
			cmp al,32h
			je length
			
			cmp al,33h
			je palindrome
			
			cmp al,34h
			je reverse
			
			cmp al,35h
			je exit
			
			disp msg6
			jmp menu
			
		input:
                	disp msg1
                	
                	lea si,str1
                	mov ah,01h
	
  		loop1:
			int 21h
			mov [si],al
			inc si
			inc count
			cmp al,13
			jne loop1
		dec count








                        












