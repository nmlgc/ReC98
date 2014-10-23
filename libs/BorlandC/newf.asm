; void far *__cdecl operator new(unsigned long size)
		public @$bnew$qul
@$bnew$qul	proc DIST
@@p		= dword	ptr -4
@@size		= dword	ptr (cPtrSize + 2)

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	ax, word ptr [bp+@@size]
		or	ax, word ptr [bp+@@size+2]
		jz	short @@sizeInvalid
		mov	dx, word ptr [bp+@@size+2]
		mov	ax, word ptr [bp+@@size]
		jmp	short @@sizeValid

@@sizeInvalid:
		xor	dx, dx
		mov	ax, 1

@@sizeValid:
		mov	word ptr [bp+@@size+2],	dx
		mov	word ptr [bp+@@size], ax
		jmp	short @@check

@@new_handler:
		call	__new_handler

@@check:
		push	word ptr [bp+@@size+2]
		push	word ptr [bp+@@size]
		nopcall	_farmalloc
		pop	cx
		pop	cx
		mov	word ptr [bp+@@p+2], dx
		mov	word ptr [bp+@@p], ax
		or	ax, dx
		jnz	short @@ret
if LDATA
		mov	ax, word ptr ds:__new_handler
		or	ax, word ptr ds:__new_handler+2
else
		cmp	__new_handler, 0
endif
		jnz	short @@new_handler

@@ret:
		mov	dx, word ptr [bp+@@p+2]
		mov	ax, word ptr [bp+@@p]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
@$bnew$qul	endp
