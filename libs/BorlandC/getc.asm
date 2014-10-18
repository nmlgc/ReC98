; void __pascal __near FlushOutStreams(void)
_FlushOutStreams proc near
@@Ndx		= word ptr -(dPtrSize + 2)
@@fp		= DPTR_ -(dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize + 2
		push	si
		push	di
		mov	[bp+@@Ndx], FOPEN_MAX
		mov	word ptr [bp+@@fp+2], ds
		mov	word ptr [bp+@@fp], offset _streams
		jmp	short @@loop

@@outstream?:
		LES_	bx, [bp+@@fp]
		mov	ax, ES_[bx+FILE.flags]
		and	ax, _F_TERM or _F_OUT
		cmp	ax, _F_TERM or _F_OUT
		jnz	short @@next
		push	word ptr [bp+@@fp+2]
		push	bx
		nopcall	_fflush
		pop	cx
		pop	cx

@@next:
		add	word ptr [bp+@@fp], size FILE

@@loop:
		mov	ax, [bp+@@Ndx]
		dec	[bp+@@Ndx]
		or	ax, ax
		jnz	short @@outstream?
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_FlushOutStreams endp

; int __pascal __near _ffill(FILE *fp)
__ffill		proc near
@@fp		= DPTR_ 4

		push	bp
		mov	bp, sp
		push	si
		push	di
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags+1], _F_TERM shr 8
		jz	short @@fill
		call	_FlushOutStreams

@@fill:
		LES_	bx, [bp+@@fp]
		push	ES_[bx+FILE._bsize]
		mov	dx, word ptr ES_[bx+FILE.buffer+2]
		mov	ax, word ptr ES_[bx+FILE.buffer]
		mov	word ptr ES_[bx+FILE.curp+2], dx
		mov	word ptr ES_[bx+FILE.curp], ax
		push	dx
		push	ax
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	___read
		add	sp, 8
		LES_	bx, [bp+@@fp]
		mov	ES_[bx+FILE.level], ax
		or	ax, ax
		jle	short @@empty?
		and	ES_[bx+FILE.flags], not	_F_EOF
		xor	ax, ax
		jmp	short @@ret

@@empty?:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
		jnz	short @@error
		mov	ax, ES_[bx+FILE.flags]
		and	ax, not	(_F_IN or _F_OUT)
		or	ax, _F_EOF
		mov	ES_[bx+FILE.flags], ax
		jmp	short @@retMinus1

@@error:
		LES_	bx, [bp+@@fp]
		mov	ES_[bx+FILE.level], 0
		or	ES_[bx+FILE.flags], _F_ERR

@@retMinus1:
		mov	ax, -1

@@ret:
		pop	di
		pop	si
		pop	bp
		ret	4
__ffill		endp

; int __cdecl _fgetc(FILE *stream)
__fgetc		proc DIST
@@fp		= DPTR_ (2 + cPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		LES_	bx, [bp+@@fp]
		inc	ES_[bx+FILE.level]
		push	word ptr [bp+@@fp+2]
		push	bx
		call	_fgetc
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
__fgetc		endp

__Nfgetc:
		pop	ax
		push	cs
		push	ax

; int __cdecl fgetc(FILE *@@fp)
_fgetc		proc DIST
@@fp		= DPTR_ (2 + cPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+@@fp]
		or	ax, word ptr [bp+@@fp+2]
		jnz	short @@filled?
		jmp	@@retEOF

@@filled?:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
		jle	short @@validFile?
		dec	ES_[bx+FILE.level]
		jmp	short @@retBufferedC

@@validFile?:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
		jl	short @@error
		test	ES_[bx+FILE.flags], _F_OUT or _F_ERR
		jnz	short @@error
		test	byte ptr ES_[bx+FILE.flags], _F_READ
		jnz	short @@buffered?

@@error:
		LES_	bx, [bp+@@fp]
		or	ES_[bx+FILE.flags], _F_ERR
		jmp	@@retEOF

@@buffered?:
		LES_	bx, [bp+@@fp]
		or	ES_[bx+FILE.flags], _F_IN
		cmp	ES_[bx+FILE._bsize], 0
		jz	short @@flushTerm
		push	word ptr [bp+@@fp+2]
		push	bx
		call	__ffill
		or	ax, ax
		jnz	short @@retEOF
		LES_	bx, [bp+@@fp]
		dec	ES_[bx+FILE.level]

@@retBufferedC:
		LES_	bx, [bp+@@fp]
		mov	dx, word ptr ES_[bx+FILE.curp+2]
		mov	si, word ptr ES_[bx+FILE.curp]
		inc	word ptr ES_[bx+FILE.curp]
		mov	es, dx
		mov	al, ES_[si]
		jmp	short @@ret0

@@flushTerm:
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags+1], _F_TERM shr 8
		jz	short @@readc
		call	_FlushOutStreams

@@readc:
		mov	ax, 1
		push	ax
		push	ds
		mov	ax, offset fgetc_c
		push	ax
		LES_	bx, [bp+@@fp]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	___read
		add	sp, 8
		or	ax, ax
		jnz	short @@textLoop
		LES_	bx, [bp+@@fp]
		mov	al, ES_[bx+FILE.fd]
		cbw
		push	ax
		nopcall	_eof
		pop	cx
		cmp	ax, 1
		jz	short @@eof
		LES_	bx, [bp+@@fp]
		or	ES_[bx+FILE.flags], _F_ERR
		jmp	short @@retEOF

@@eof:
		LES_	bx, [bp+@@fp]
		mov	ax, ES_[bx+FILE.flags]
		and	ax, not	(_F_IN or _F_OUT)
		or	ax, _F_EOF
		mov	ES_[bx+FILE.flags], ax

@@retEOF:
		mov	ax, EOF
		jmp	short @@ret

@@textLoop:
		cmp	fgetc_c, 0Dh ; '\r'
		jnz	short @@unsetEOF
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], _F_BIN
		jz	short @@flushTerm

@@unsetEOF:
		LES_	bx, [bp+@@fp]
		and	ES_[bx+FILE.flags], not	_F_EOF
		mov	al, fgetc_c

@@ret0:
		mov	ah, 0

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_fgetc		endp

; int fgetchar(void)
_fgetchar	proc DIST
		push	si
		push	di
		push	ds
		mov	ax, offset stdin
		push	ax
		call	_fgetc
		pop	cx
		pop	cx
		pop	di
		pop	si
		ret
_fgetchar	endp
