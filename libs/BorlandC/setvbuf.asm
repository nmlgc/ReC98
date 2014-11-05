; int __cdecl setvbuf(FILE *fp, char *buf, int type, size_t size)
_setvbuf	proc
@@fp		= DPTR_ dPtrSize + 2
@@buf		= DPTR_ dPtrSize + 2 + dPtrSize
@@type		= word ptr dPtrSize + 2 + (dPtrSize * 2)
@@size		= word ptr dPtrSize + 2 + (dPtrSize * 2) + 2

		push	bp
		mov	bp, sp
		push	si
		push	di
		LES_	bx, [bp+@@fp]
		mov	ax, ES_[bx+FILE.token]
		cmp	ax, word ptr [bp+@@fp]
		jz	short @@validType?
		jmp	@@retEOF

@@validType?:
		cmp	[bp+@@type], 2
		jle	short @@tooLarge?
		jmp	@@retEOF

@@tooLarge?:
		cmp	[bp+@@size], 7FFFh
		jbe	short @@stdoutStart?
		jmp	@@retEOF

@@stdoutStart?:
		cmp	_stdoutStarted,	0
		jnz	short @@stdinStart?
		cmp	word ptr [bp+@@fp], offset stdout
		jnz	short @@stdinStart?
		mov	_stdoutStarted,	1
		jmp	short @@reposition?

@@stdinStart?:
		cmp	_stdinStarted, 0
		jnz	short @@reposition?
		cmp	word ptr [bp+@@fp], offset stdin
		jnz	short @@reposition?
		mov	_stdinStarted, 1

@@reposition?:
		LES_	bx, [bp+@@fp]
		cmp	ES_[bx+FILE.level], 0
		jz	short @@freeBuffer?
		mov	ax, 1
		push	ax
		xor	ax, ax
		push	ax
		push	ax
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	bx
		nopcall	_fseek
		add	sp, 6 + dPtrSize

@@freeBuffer?:
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], 4
		jz	short @@resetBuffer
if LDATA
		push	word ptr ES_[bx+FILE._buffer+2]
endif
		push	word ptr ES_[bx+FILE._buffer]
		nopcall	_free
if LDATA
		pop	cx
endif
		pop	cx

@@resetBuffer:
		LES_	bx, [bp+@@fp]
		and	ES_[bx+FILE.flags], 0FFF3h
		mov	ES_[bx+FILE._bsize], 0
if LDATA
		mov	dx, word ptr [bp+@@fp+2]
endif
		mov	ax, word ptr [bp+@@fp]
		add	ax, FILE.hold
if LDATA
		mov	word ptr ES_[bx+FILE._buffer+2], dx
		mov	word ptr ES_[bx+FILE._buffer], ax
		mov	word ptr ES_[bx+FILE._curp+2], dx
else
		mov	word ptr ES_[bx+FILE._buffer], ax
endif
		mov	word ptr ES_[bx+FILE._curp], ax
		cmp	[bp+@@type], 2
		jz	short @@ret0
		cmp	[bp+@@size], 0
		jbe	short @@ret0
if LDATA		
		mov	word ptr _exitbuf+2, seg __xfflush
		mov	word ptr _exitbuf, offset __xfflush
		mov	ax, word ptr [bp+@@buf]
		or	ax, word ptr [bp+@@buf+2]
else
		mov	word ptr _exitbuf, offset __xfflush
		cmp	word ptr [bp+@@buf], 0
endif
		jnz	short @@setBuffer
		push	[bp+@@size]
		nopcall	_malloc
		pop	cx
if LDATA		
		mov	word ptr [bp+@@buf+2], dx
		mov	word ptr [bp+@@buf], ax
		or	ax, dx
else
		mov	word ptr [bp+@@buf], ax
		or	ax, ax
endif
		jz	short @@retEOF
		LES_	bx, [bp+@@fp]
		or	ES_[bx+FILE.flags], 4
		jmp	short @@setBuffer

@@retEOF:
		mov	ax, 0FFFFh
		jmp	short @@ret

@@setBuffer:
		LES_	bx, [bp+@@fp]
if LDATA
		mov	dx, word ptr [bp+@@buf+2]
		mov	ax, word ptr [bp+@@buf]
		mov	word ptr ES_[bx+FILE._curp+2], dx
		mov	word ptr ES_[bx+FILE._curp], ax
		mov	word ptr ES_[bx+FILE._buffer+2], dx
		mov	word ptr ES_[bx+FILE._buffer], ax
else
		mov	ax, word ptr [bp+@@buf]
		mov	word ptr ES_[bx+FILE._curp], ax
		mov	word ptr ES_[bx+FILE._buffer], ax
endif
		mov	ax, [bp+@@size]
		mov	ES_[bx+FILE._bsize], ax
		cmp	[bp+@@type], 1
		jnz	short @@ret0
		or	ES_[bx+FILE.flags], 8

@@ret0:
		xor	ax, ax

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_setvbuf	endp
