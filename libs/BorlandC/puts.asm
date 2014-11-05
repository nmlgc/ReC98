; int __cdecl puts(const char *s)
_puts		proc
@@len		= word ptr -2
@@s		= DPTR_ (2 + cPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
if LDATA
		mov	ax, word ptr [bp+@@s]
		or	ax, word ptr [bp+@@s+2]
else
		cmp	word ptr [bp+@@s], 0
endif
		jnz	short @@valid
		xor	ax, ax
		jmp	short @@ret

@@valid:
if LDATA
		push	word ptr [bp+@@s+2]
endif		
		push	word ptr [bp+@@s]
		nopcall	_strlen
		pop	cx
if LDATA
		pop	cx
endif
		mov	[bp+@@len], ax
if LDATA
		push	word ptr [bp+@@s+2]
endif
		push	word ptr [bp+@@s]
		push	ax
		pushDS_
		mov	ax, offset stdout
		push	ax
		call	__fputn
		cmp	ax, [bp+@@len]
		jz	short @@fputc
		mov	ax, EOF
		jmp	short @@ret

@@fputc:
		pushDS_
		mov	ax, offset stdout
		push	ax
		mov	ax, 0Ah
		push	ax
		nopcall	_fputc
if LDATA		
		add	sp, 6
else
		pop	cx
		pop cx
endif
		cmp	ax, 0Ah
		jz	short @@retLF
		mov	ax, EOF
		jmp	short @@ret

@@retLF:
		mov	ax, 0Ah

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_puts		endp
