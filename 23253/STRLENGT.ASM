.model small
.stack 100h
.data
        msg1 db 13,10,'Enter string:$'
        msg2 db 13,10,'String is:$'
        msg3 db 13,10,'Length is:$'
        str1 db 100 dup('$')
        count dw 0
.code
	mov ax,@data
	mov ds,ax
	
	lea dx,msg1
	mov ah,09h
	int 21h
	
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
		
		
	lea dx,msg2
	mov ah,09h
	int 21h
	
	lea dx,str1
	mov ah,09h
	int 21h
	
	lea dx,msg3
	mov ah,09h
	int 21h

	mov ax,count
	add ax,30h
	mov dx,ax
	mov ah,02h
	int 21h
	
	mov ah,04ch
	int 21h 
	
	end
