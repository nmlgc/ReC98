; int __cdecl _fputc(char ch, FILE *fp)
public __fputc
__fputc		proc
@@ch		= byte ptr dPtrSize + 2
@@fp		= dword	ptr dPtrSize + 4

		push	bp
		mov	bp, sp
		push	si
		push	di
		les	bx, [bp+@@fp]
		dec	es:[bx+FILE.level]
		push	word ptr [bp+@@fp+2]
		push	bx
		mov	al, [bp+@@ch]
		cbw
		push	ax
		nopcall	_fputc
		add	sp, 6
		pop	di
		pop	si
		pop	bp
		ret
__fputc		endp

; int __cdecl fputc(int	ch, FILE *fp)
public _fputc
_fputc		proc
@@ch		= byte ptr dPtrSize + 2
@@fp		= dword	ptr dPtrSize + 4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	al, [bp+@@ch]
		mov	fputc_c, al
		les	bx, [bp+@@fp]
		cmp	es:[bx+FILE.level], -1
		jge	short @@checkFlags
		inc	es:[bx+FILE.level]
		mov	dx, word ptr es:[bx+FILE.curp+2]
		mov	si, word ptr es:[bx+FILE.curp]
		inc	word ptr es:[bx+FILE.curp]
		mov	es, dx
		mov	es:[si], al
		mov	es, word ptr [bp+@@fp+2]
		test	byte ptr es:[bx+FILE.flags], 8
		jnz	short @@LBufFlush?
		jmp	@@retC

@@LBufFlush?:
		cmp	fputc_c, 0Ah
		jz	short @@LBufFlush
		cmp	fputc_c, 0Dh
		jz	short @@LBufFlush
		jmp	@@retC

@@LBufFlush:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp] ; stream
		nopcall	_fflush
		pop	cx
		pop	cx
		or	ax, ax
		jnz	short @@j1_retEOF
		jmp	@@retC

@@j1_retEOF:
		jmp	@@retEOF

@@checkFlags:
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags], 90h
		jnz	short @@setErr
		test	byte ptr es:[bx+FILE.flags], 2
		jnz	short @@setOut

@@setErr:
		les	bx, [bp+@@fp]
		or	es:[bx+FILE.flags], 10h
		jmp	@@retEOF

@@setOut:
		les	bx, [bp+@@fp]
		or	es:[bx+FILE.flags], 100h
		cmp	es:[bx+FILE._bsize], 0
		jz	short @@unbuffered
		cmp	es:[bx+FILE.level], 0
		jz	short @@bufferedPut
		push	word ptr [bp+@@fp+2]
		push	bx
		nopcall	_fflush
		pop	cx
		pop	cx
		or	ax, ax
		jz	short @@bufferedPut
		jmp	@@retEOF

@@bufferedPut:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE._bsize]
		neg	ax
		mov	es:[bx+FILE.level], ax
		mov	dx, word ptr es:[bx+FILE.curp+2]
		mov	si, word ptr es:[bx+FILE.curp]
		inc	word ptr es:[bx+FILE.curp]
		mov	al, fputc_c
		mov	es, dx
		mov	es:[si], al
		mov	es, word ptr [bp+@@fp+2]
		test	byte ptr es:[bx+FILE.flags], 8
		jnz	short @@bufferedFlush?
		jmp	@@retC

@@bufferedFlush?:
		cmp	fputc_c, 0Ah
		jz	short @@bufferedFlush
		cmp	fputc_c, 0Dh
		jz	short @@bufferedFlush
		jmp	@@retC

@@bufferedFlush:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		nopcall	_fflush
		pop	cx
		pop	cx
		or	ax, ax
		jnz	short @@j2_retEOF
		jmp	@@retC

@@j2_retEOF:
		jmp	@@retEOF

@@unbuffered:
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		add	ax, ax
		mov	bx, ax
		test	byte ptr (_openfd+1)[bx], 8
		jz	short @@unbufferedText
		mov	ax, 2
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	bx, word ptr [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8

@@unbufferedText:
		cmp	fputc_c, 0Ah
		jnz	short @@unbufferedPutC
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags], 40h
		jnz	short @@unbufferedPutC
		mov	ax, 1
		push	ax
		push	ds
		mov	ax, offset fputc_cr
		push	ax
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	__rtl_write
		add	sp, 8
		cmp	ax, 1
		jnz	short @@unbufferedFlag

@@unbufferedPutC:
		mov	ax, 1
		push	ax
		push	ds
		mov	ax, offset fputc_c
		push	ax
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	__rtl_write
		add	sp, 8
		cmp	ax, 1
		jz	short @@retC

@@unbufferedFlag:
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags+1], 2
		jnz	short @@retC
		or	es:[bx+FILE.flags], 10h

@@retEOF:
		mov	ax, 0FFFFh
		jmp	short @@ret

@@retC:
		mov	al, fputc_c
		mov	ah, 0

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_fputc		endp

; int __cdecl fputchar(int c)
public _fputchar
_fputchar	proc
@@ch		= word ptr dPtrSize + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		mov	ax, offset stdout
		push	ax
		push	[bp+@@ch]
		call	_fputc
		add	sp, 6
		pop	di
		pop	si
		pop	bp
		ret
_fputchar	endp

; int __stdcall	_FPUTN(FILE *fp, size_t n, void *ptr)
__FPUTN		proc near
@@len		= word ptr -2
@@fp		= dword	ptr  4
@@n		= word ptr  8
@@ptr		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, [bp+@@n]
		mov	[bp+@@len], ax
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags], 8
		jz	short @@NoBuf
		jmp	short @@LBufLoop

@@LBufPut:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		les	bx, [bp+@@ptr]
		inc	word ptr [bp+@@ptr]
		mov	al, es:[bx]
		cbw
		push	ax
		call	_fputc
		add	sp, 6
		cmp	ax, 0FFFFh
		jnz	short @@LBufLoop
		jmp	@@ret0

@@LBufLoop:
		mov	ax, [bp+@@n]
		dec	[bp+@@n]
		or	ax, ax
		jnz	short @@LBufPut
		jmp	@@retLen

@@NoBuf:
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+FILE.flags], 40h
		jnz	short @@bin
		jmp	@@text

@@bin:
		cmp	es:[bx+FILE._bsize], 0
		jnz	short @@binBuffered
		jmp	@@binUnbuffered

@@binBuffered:
		mov	ax, es:[bx+FILE._bsize]
		cmp	ax, [bp+@@n]
		jnb	short @@binBufferedFit
		cmp	es:[bx+FILE.level], 0
		jz	short @@binAppend?
		push	word ptr [bp+@@fp+2]
		push	bx
		nopcall	_fflush
		pop	cx
		pop	cx
		or	ax, ax
		jz	short @@binAppend?
		jmp	@@ret0

@@binAppend?:
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		add	ax, ax
		mov	bx, ax
		test	byte ptr (_openfd+1)[bx], 8
		jz	short @@binWrite
		mov	ax, 2
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	bx, word ptr [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8

@@binWrite:
		push	[bp+@@n]
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	__rtl_write
		add	sp, 8
		cmp	ax, [bp+@@n]
		jnz	short @@j1_ret0
		jmp	@@retLen

@@j1_ret0:
		jmp	@@ret0

@@binBufferedFit:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE.level]
		add	ax, [bp+@@n]
		jl	short @@binBufferedStuff
		cmp	word ptr es:[bx], 0
		jnz	short @@binBufferedFlush
		mov	ax, 0FFFFh
		sub	ax, es:[bx+FILE._bsize]
		mov	es:[bx+FILE.level], ax
		jmp	short @@binBufferedStuff

@@binBufferedFlush:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		nopcall	_fflush
		pop	cx
		pop	cx
		or	ax, ax
		jz	short @@binBufferedStuff
		jmp	@@ret0

@@binBufferedStuff:
		push	[bp+@@n]
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		les	bx, [bp+@@fp]
		push	word ptr es:[bx+FILE.curp+2]
		push	word ptr es:[bx+FILE.curp]
		nopcall	_memcpy
		add	sp, 0Ah
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+FILE.level]
		add	ax, [bp+@@n]
		mov	es:[bx+FILE.level], ax
		mov	ax, [bp+@@n]
		add	word ptr es:[bx+FILE.curp], ax
		jmp	@@retLen

@@binUnbuffered:
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		add	ax, ax
		mov	bx, ax
		test	byte ptr (_openfd+1)[bx], 8
		jz	short @@binUnbufferedWrite
		mov	ax, 2
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	bx, word ptr [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_lseek
		add	sp, 8

@@binUnbufferedWrite:
		push	[bp+@@n]
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	__rtl_write
		add	sp, 8
		cmp	ax, [bp+@@n]
		jnz	short @@j2_ret0
		; Hack (jmp	long @@retLen)
		db	0e9h, 07fh, 000h

@@j2_ret0:
		jmp	short @@ret0

@@text:
		les	bx, [bp+@@fp]
		cmp	es:[bx+FILE._bsize], 0
		jz	short @@textUnbuffered
		jmp	short @@textBufferedLoop

@@textBuffered:
		les	bx, [bp+@@fp]
		inc	word ptr es:[bx]
		jge	short @@textBufferedPut
		mov	dx, word ptr es:[bx+FILE.curp+2]
		mov	si, word ptr es:[bx+FILE.curp]
		inc	word ptr es:[bx+FILE.curp]
		les	bx, [bp+@@ptr]
		inc	word ptr [bp+@@ptr]
		mov	al, es:[bx]
		mov	es, dx
		mov	es:[si], al
		mov	ah, 0
		jmp	short @@textBufferedEOF?

@@textBufferedPut:
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		les	bx, [bp+@@ptr]
		inc	word ptr [bp+@@ptr]
		mov	al, es:[bx]
		push	ax
		call	__fputc
		add	sp, 6

@@textBufferedEOF?:
		cmp	ax, 0FFFFh
		jz	short @@ret0

@@textBufferedLoop:
		mov	ax, [bp+@@n]
		dec	[bp+@@n]
		or	ax, ax
		jnz	short @@textBuffered
		jmp	short @@retLen

@@textUnbuffered:
		push	[bp+@@n]
		push	word ptr [bp+@@ptr+2]
		push	word ptr [bp+@@ptr]
		les	bx, [bp+@@fp]
		mov	al, es:[bx+FILE.fd]
		cbw
		push	ax
		nopcall	___write
		add	sp, 8
		cmp	ax, [bp+@@n]
		jz	short @@retLen

@@ret0:
		xor	ax, ax
		jmp	short @@ret

@@retLen:
		mov	ax, [bp+@@len]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	0Ah
__FPUTN		endp
