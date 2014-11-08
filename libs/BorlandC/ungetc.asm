__Nungetc	label near
if LPROG
		pop	ax
		push	cs
		push	ax
endif

; int __cdecl ungetc(int c, FILE *fp)
_ungetc		proc
@@c		= word ptr (cPtrSize + 2)
@@fp		= DPTR_ (cPtrSize + 4)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, [bp+@@c]
		cmp	cx, EOF
		jz	short @@retC
		les	bx, [bp+@@fp]
		cmp	es:[bx+FILE.level], 0
		jge	short @@clearEOF
		mov	ax, EOF
		jmp	short @@ret

@@clearEOF:
		les	bx, [bp+@@fp]
		and	es:[bx+FILE.flags], not _F_EOF
		inc	es:[bx+FILE.level]
		mov	ax, es:[bx+FILE.level]
		cmp	ax, 1
		jle	short @@hold
		dec	word ptr es:[bx+FILE.curp]
		push	bx
		push	es
		mov	es, es:[bx+FILE.curp+2]
		mov	ax, es
		pop	es
		pop	bx
		mov	bx, word ptr es:[bx+FILE.curp]
		mov	dl, cl
		mov	es, ax
		mov	es:[bx], dl
		mov	al, dl

@@retHi0:
		mov	ah, 0
		jmp	short @@ret

@@hold:
		mov	dx, word ptr [bp+@@fp+2]
		mov	ax, word ptr [bp+@@fp]
		add	ax, FILE.hold
		les	bx, [bp+@@fp]
		mov	word ptr es:[bx+FILE.curp+2], dx
		mov	word ptr es:[bx+FILE.curp], ax
		mov	al, cl
		mov	es:[bx+FILE.hold], al
		jmp	short @@retHi0

@@retC:
		mov	ax, cx

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_ungetc		endp
