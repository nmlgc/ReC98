; int __cdecl fputs(const char *s, FILE	*fp)
public _fputs
_fputs		proc
@@len		= word ptr -2
@@s		= DPTR_ dPtrSize + 2
@@fp		= DPTR_ dPtrSize + 2 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, word ptr [bp+@@s]
		or	ax, word ptr [bp+@@s+2]
		jz	short @@ret0
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]
		nopcall	_strlen
		pop	cx
		pop	cx
		mov	[bp+@@len], ax
		or	ax, ax
		jnz	short @@put

@@ret0:
		xor	ax, ax
		jmp	short @@ret

@@put:
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]
		push	[bp+@@len]
		push	word ptr [bp+@@fp+2]
		push	word ptr [bp+@@fp]
		call	__FPUTN
		or	ax, ax
		jz	short @@retEOF
		les	bx, [bp+@@s]
		add	bx, [bp+@@len]
		mov	al, es:[bx-1]
		mov	ah, 0
		jmp	short @@ret

@@retEOF:
		mov	ax, 0FFFFh

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_fputs		endp
