; int __cdecl fclose(FILE *fp)
_fclose		proc DIST
@@res		= word ptr -2
@@fp		= dword	ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	[bp+@@res], 0FFFFh
		mov	ax, word ptr [bp+@@fp]
		or	ax, word ptr [bp+@@fp+2]
		jnz	short @@verifyToken
		jmp	@@ret

@@verifyToken:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE.token]
		cmp	ax, word ptr [bp+@@fp]
		jz	short @@buffered?
		jmp	@@ret

@@buffered?:
		les	bx, [bp+@@fp]
		cmp	es:[bx+FILE._bsize], 0
		jz	short @@close?
		cmp	es:[bx+FILE.level], 0
		jge	short @@free?
		push	word ptr [bp+@@fp+2]
		push	bx
		nopcall	_fflush
		pop	cx
		pop	cx
		or	ax, ax
		jnz	short @@ret

@@free?:
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags], 4
		jz	short @@close?
		push	word ptr es:[bx+FILE._buffer+2]
		push	word ptr es:[bx+FILE._buffer]
		nopcall	_farfree
		pop	cx
		pop	cx

@@close?:
		les	bx, [bp+@@fp]
		cmp	es:[bx+FILE.fd], 0
		jl	short @@reset
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_close
		pop	cx
		mov	[bp+@@res], ax

@@reset:
		les	bx, [bp+@@fp]
		mov	es:[bx+FILE.flags], 0
		mov	es:[bx+FILE._bsize], 0
		mov	es:[bx+FILE.level], 0
		mov	es:[bx+FILE.fd], -1
		cmp	es:[bx+FILE.istemp], 0
		jz	short @@ret
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		push	es:[bx+FILE.istemp]
		call	__MKNAME
		push	dx
		push	ax
		nopcall	_unlink
		pop	cx
		pop	cx
		les	bx, [bp+@@fp]
		mov	es:[bx+FILE.istemp], 0

@@ret:
		mov	ax, [bp+@@res]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_fclose		endp
