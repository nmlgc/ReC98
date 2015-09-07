; int __stdcall	fgetn(FILE *fp, int n, void *ptr)
_fgetn		proc near
@@var_4		= word ptr -4
@@Temp		= word ptr -2
@@fp		= dword	ptr  4
@@n		= word ptr  8
@@ptr		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		jmp	@@while

@@loop:
		inc	[bp+@@n]
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE._bsize]
		cmp	ax, [bp+@@n]
		jbe	short @@len_bsize
		mov	ax, [bp+@@n]
		jmp	short @@bin?

@@len_bsize:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE._bsize]

@@bin?:
		mov	[bp+@@Temp], ax
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags], 40h
		jnz	short @@bsize?
		jmp	@@getc?

@@bsize?:
		cmp	es:[bx+FILE._bsize], 0
		jnz	short @@greater?
		jmp	@@getc?

@@greater?:
		mov	ax, es:[bx+FILE._bsize]
		cmp	ax, [bp+@@n]
		jnb	short @@getc?
		cmp	es:[bx+FILE.level], 0
		jnz	short @@getc?
		dec	[bp+@@n]
		mov	[bp+@@Temp], 0
		jmp	short @@adjust?

@@adjust:
		les	bx, [bp+@@fp]
		add	bx, FILE._bsize
		mov	[bp+@@var_4], bx
		mov	ax, es:[bx]
		add	[bp+@@Temp], ax
		sub	[bp+@@n], ax

@@adjust?:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE._bsize]
		cmp	ax, [bp+@@n]
		jbe	short @@adjust
		push	[bp+@@Temp]
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	__rtl_read
		add	sp, 8
		mov	dx, ax
		cmp	dx, 0FFFFh
		jnz	short @@advance
		xor	dx, dx
		les	bx, [bp+@@fp]
		or	es:[bx+FILE.flags], 10h

@@advance:
		add	word ptr [bp+@@ptr], dx
		cmp	dx, [bp+@@Temp]
		jz	short @@while
		mov	ax, [bp+@@Temp]
		sub	ax, dx
		add	[bp+@@n], ax

@@setEOF:
		les	bx, [bp+@@fp]
		or	es:[bx+FILE.flags], 20h
		jmp	short @@ret

@@writec:
		les	bx, [bp+@@ptr]
		mov	es:[bx], dl
		inc	word ptr [bp+@@ptr]

@@getc?:
		dec	[bp+@@n]
		mov	ax, [bp+@@n]
		or	ax, ax
		jz	short @@EOF?
		dec	[bp+@@Temp]
		jz	short @@EOF?
		les	bx, [bp+@@fp]
		dec	word ptr es:[bx]
		jl	short @@getc
		mov	dx, es:[bx+0Eh]
		mov	si, es:[bx+0Ch]
		inc	word ptr es:[bx+0Ch]
		mov	es, dx
		mov	al, es:[si]
		mov	ah, 0
		jmp	short @@gotEOF?

@@getc:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		nopcall	__fgetc
		pop	cx
		pop	cx

@@gotEOF?:
		mov	dx, ax
		cmp	ax, 0FFFFh
		jnz	short @@writec

@@EOF?:
		cmp	dx, 0FFFFh
		jz	short @@setEOF

@@while:
		cmp	[bp+@@n], 0
		jz	short @@ret
		jmp	@@loop

@@ret:
		mov	ax, [bp+@@n]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	0Ah
_fgetn		endp

; size_t __cdecl fread(void *ptr, size_t psize, size_t nitems, FILE *fp)
public _fread
_fread		proc
@@temp		= dword	ptr -6
@@n		= word ptr -2
@@ptr		= dword	ptr  6
@@psize		= word ptr  0Ah
@@nitems	= word ptr  0Ch
@@fp		= dword	ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		cmp	[bp+@@psize], 0
		jnz	short @@seg?
		xor	ax, ax
		jmp	@@ret

@@seg?:
		mov	bx, [bp+@@psize]
		xor	cx, cx
		mov	ax, [bp+@@nitems]
		xor	dx, dx
		call	N_LXMUL@
		mov	word ptr [bp+@@temp+2],	dx
		mov	word ptr [bp+@@temp], ax
		cmp	dx, 1
		ja	short @@huge
		jb	short @@segGet
		or	ax, ax
		jnb	short @@huge

@@segGet:
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		push	word ptr [bp+@@temp]
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		call	_fgetn
		mov	dx, word ptr [bp+@@temp]
		sub	dx, ax
		push	dx
		xor	dx, dx
		pop	ax
		div	[bp+@@psize]
		jmp	short @@ret

@@huge:
		mov	ax, [bp+@@nitems]
		inc	ax
		mov	[bp+@@n], ax
		jmp	short @@hugeGet

@@hugeAdvance:
		mov	bx, [bp+@@psize]
		xor	cx, cx
		mov	dx, word ptr [bp+@@ptr+2]
		mov	ax, word ptr [bp+@@ptr]
		call	near ptr N_PADD@
		mov	word ptr [bp+@@ptr+2], dx
		mov	word ptr [bp+@@ptr], ax

@@hugeGet:
		dec	[bp+@@n]
		mov	ax, [bp+@@n]
		or	ax, ax
		jz	short @@retItemsMinusN
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		push	[bp+@@psize]
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		call	_fgetn
		or	ax, ax
		jz	short @@hugeAdvance

@@retItemsMinusN:
		mov	ax, [bp+@@nitems]
		sub	ax, [bp+@@n]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_fread		endp
