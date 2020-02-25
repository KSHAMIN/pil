.model small
.stack 100h
.data
	a db 215
	b db 125
	msg1 db 13,10,'Decimal addition:$'
	msg2 db 13,10,'Hex addition:$'
.code
		mov ax,@data
		mov ds,ax
		
		;------decimal value-------
		
		mov ax,215
		mov bx,125
		add ax,bx
		xor dx,dx
		
		mov bx,0Ah
		div bx
		mov cx,dx
		
		div bx
		xor bx,bx
		mov bx,dx
		
		xor dx,dx
		
		mov dx,offset msg1
		mov ah,09h
		int 21h
		
		xor dx,dx
		
		add ax,30h
		mov dx,ax
		mov ah,02h
		int 21h
		
		add bx,30h
		mov dx,bx
		mov ah,02h
		int 21h
		
		add cx,30h
		mov dx,cx
		mov ah,02h
		int 21h
		
		
		;------HEX VALUE-------
		
		xor ax,ax
		xor bx,bx
		xor cx,cx
		xor dx,dx
		
		mov ax,215
		mov bx,125
		add ax,bx
		xor dx,dx
		
		mov bx,10h
		div bx
		mov cx,dx
		
		div bx
		xor bx,bx
		mov bx,dx
		
		xor dx,dx
		
		mov dx,offset msg2
		mov ah,09h
		int 21h
		
		xor dx,dx 
		
		add ax,30h
		mov dx,ax
		mov ah,02h
		int 21h
		
		add bx,30h
		mov dx,bx
		mov ah,02h
		int 21h
		
		add cx,30h
		mov dx,cx
		mov ah,02h
		int 21h
		
		mov ah,4ch
		int 21h
		
		end
		
			
	
