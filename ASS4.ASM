.model large

 ;function to perform display operation
disp macro msg
lea dx,msg
mov ah,09h
int 21h
endm

.stack 100h
.data
        str1 db 100 dup('$')
        str2 db 100 dup('$')
        str3 db 100 dup('$')
        msg1 db 13,10,'Enter 1st string:$'
        msg2 db 13,10,'Enter 2nd string:$'
        msg3 db 13,10,'*******Strings are same!*******$'
        msg4 db 13,10,'*******Strings are not same!*******$'
        msg5 db 13,10,'Concatenated string is:$'
        msg6 db 13,10,'*******Invalid Entry!!*******$'
        msg7 db 13,10,'Enter the string whose occurence you want to check:$'
        msg8 db 13,10,'*******Given string occurs in main string!!*******$'
        msg9 db 13,10,'*******Given string does not occur in main string!$*******'
        menu1 db 13,10,'1)Input strings:$'
        menu2 db 13,10,'2)Compare strings$'
        menu3 db 13,10,'3)Concatenate strings$'
        menu4 db 13,10,'4)Check occurence$'
        menu5 db 13,10,'5)Exit$'
        menu6 db 13,10,'Enter your choice:$'
        
.code
     	        mov ax,@data
                mov ds,ax
                
                menu:
                	   ;making menu driven program
                	disp menu1
                	disp menu2
                	disp menu3
                	disp menu4
                	disp menu5
                	disp menu6
                	
                	mov ah,01h
                	int 21h			
                	
                	cmp al,31h		;option 1(taking input)
                	je input		
                	
                	cmp al,32h		;option 2(comparing strings)
                	je compare		
                	
                	cmp al,33h		;option 3(concatenate strings)
                	je concatenate1		
                	
                	cmp al,34h
                	je occurence		;option 4(check substring)
                	
                	cmp al,35h
                	je exit			;option 5(Exit the program)
                	disp msg6
                	jmp menu
                	
                occurence:
                	jmp occurence1		;making jump in two steps(single jump cannot be achieved since it is too far)

		input:
			;code for taking input from user
			
			disp msg1
			
			xor ax,ax
			xor dx,dx
			
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
                 	disp msg2

			xor ax,ax                 

                 	lea di,str2
                 	mov ah,01h

                 	mov bx,0h 

                 	loop2:
                 	       int 21h
                 	       mov[di],al
                 	       inc di
                 	       inc bx
                 	       cmp al,13
                 	       jne loop2
                 	       
		 	jmp menu		;jump back to menu after code is executed
		
		concatenate1:
			jmp concatenate 
		 	
		compare:
			;code for comparing two strings
				
		 	xor dx,dx
                 	xor ax,ax
                 	lea si,str1
                 	lea di,str2

                 	loop3:
                        	mov al,[si]
                        	mov ah,[di]
                        	cmp al,ah
                        	jne line
                        	inc si
                        	inc di
                        	cmp si,cx
                        	jne loop3
                        	 
		  	xor dx,dx
                  	disp msg3
                  	jmp menu

                  	line:
                        	disp msg4
                        	jmp menu
                 
                 exit:
			jmp exit1 
                        	
		concatenate:
				;code for concatenating two strings
			
		  	xor dx,dx
                  	xor ax,ax
                  
                  	disp msg5
                  
                  	xor dx,dx
                  	xor ax,ax
                  	
                  	lea si,str1
                  	lea di,str2
                  
                  	dec bx
		  	loop4:
		  		inc di
		  		dec bx
		  		cmp bx,0
		  		jne loop4
		  		
		  	loop5:
		  		mov al,[si]
		  		mov [di],al
		  		inc si
		  		inc di
		  		dec cx
		  		cmp cx,0
		  		jne loop5
		  		
		  	xor dx,dx
		  	xor ax,ax
		  	disp str2
		  	
		  	jmp menu
		  	
		occurence1:
				;code for checking substring occurence
			
			lea si,str1
			xor di,di
			disp msg7
			
			xor ax,ax
			xor dx,dx
			
			lea di,str3
			mov ah,01h
			
			mov bx,0h
			
			sub1:
				int 21h
				mov [di],al
				inc di
				inc bx
				cmp al,13
				jne sub1
				
			lea di,str3	
			
		  	check:
			
		  		mov al,[si]
		  		mov ah,[di]
		  		cmp al,ah
		  		je out2
		  		inc si
		  		dec cx
		  		cmp cx,0
		  		jne check		  		
		  		jmp out1
		  		
		  	out2:
		  		dec bx
		  		dec bx
		  		cmp bx,0
		  		jle out3
		  		dec cx
		  		cmp cx,0
		  		je out3
		  		inc si
		  		inc di
		  		mov al,[si]
		  		mov ah,[di]
		  		cmp al,ah
		  		je out2
		  		cmp al,ah
		  		jne out1
		  	
		  	out3:	
		  		xor dx,dx
		  		xor ax,ax
		  	
		  		disp msg8
		  		jmp menu
		  	
		  	out1:
		  		xor dx,dx
		  		xor ax,ax
		  		disp msg9
		  		jmp menu
		  		 
		exit1: 	
			;exiting the code
				
                  	mov ah,4ch
                  	int 21h
		
                  	end
	
                 	
















