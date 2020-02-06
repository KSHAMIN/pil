.model medium

disp macro msg
lea dx,msg
mov ah,09h
int 21h
endm

.stack 100h
.data
	str1 db 100 dup('$')
	str2 db 100 dup('$')
        msg1 db 'Enter string:',13,10,'$'
        msg2 db '*******It is a palindrome!*******',13,10,'$'
        msg3 db '*******It is not a palindrome!!*******',13,10,'$'
        msg4 db '*****String length is:',13,10,'$'
        msg5 db '*****Reversed string is:',13,10,'$'
        msg6 db '*******Invalid Entery*******',13,10,'$'
        menu1 db '*****MENU*****',13,10,'$'
        menu2 db '1)Enter string',13,10,'$'
        menu3 db '2)Find string length',13,10,'$'
        menu4 db '3)Reverse the string',13,10,'$'
        menu5 db '4)Check palindrome',13,10,'$'
        menu6 db '5)Exit',13,10,'$'
        menu7 db '6)Enter your choice:',13,10,'$'
        count dw 0
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
			je length1
			
			cmp al,33h
			je reverse
			
			;cmp al,34h
			;je palindrome
			
			cmp al,35h
			je exit
			
		;	disp msg6
		;	jmp menu
			
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
		jmp menu
		
		length1:
			xor ax,ax
			xor dx,dx
			
			disp msg4
			
			xor ax,ax
			xor dx,dx
	
			mov ax,count
			add ax,30h
			mov dx,ax
			mov ah,02h
			int 21h
		jmp menu
		
		exit:
			jmp exit1
		
		reverse:

			
			xor ax,ax
			xor dx,dx
			
			lea di,str2
			mov cx,0h
			inc count
			
			rloop1:
				dec si
				mov al,[si]
				mov [di],al
				inc di
				inc cx
				dec count
				cmp count,0
				jne rloop1
				
			xor ax,ax
			xor dx,dx
				
			disp msg5
			
			xor ax,ax
			xor dx,dx
			
			lea dx,str2
			mov ah,09h
			int 21h
			
		jmp menu
		
		exit1:
			mov ah,4ch
			int 21h
			
			end
	





                        












