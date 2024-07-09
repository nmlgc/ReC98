		.8086
		.model tiny
		.code
		org 100h ;doesn't matter, needed for linker
start:
		cmp	byte ptr ds:80h, 0
		jz	short moveup
		mov	ax, word ptr ds:82h
		cmp	ax, 3F2Dh ; '-?'
		jz	short print_help
		cmp	ax, 0D3Fh ; '?\r'
		jnz	short moveup
print_help:
		mov	bx, 1 ;stdout
		mov	dx, word ptr ds:103h ; usage string
		mov	cx, word ptr ds:105h ; length
		mov	ah, 40h		; INT=21/AH=40h - WRITE TO FILE OR DEVICE
		int	21h
		mov	ax, 4C00h	; INT=21/AH=4Ch - TERMINATE WITH RETURN CODE
		int	21h
moveup:
		mov	di, 100h
		push	di
		mov	si, word ptr ds:103h ; location of usage str
		add	si, word ptr ds:105h ; length of usage str
		mov	cx, word ptr ds:107h ; length of inner com
		inc	cx
		shr	cx, 1
		rep movsw
		mov	ax, cx
		mov	si, ax
		mov	di, ax
		retn
		END start
