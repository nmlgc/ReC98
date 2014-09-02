; int __cdecl setblock(unsigned	int segx, unsigned int newsize)
_setblock	proc DIST
@@segx		= word ptr 2 + dPtrSize
@@newsize		= word ptr 4 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 4Ah
		mov	bx, [bp+@@newsize]
		mov	es, [bp+@@segx]
		int	21h
		jc	short @@setblockFailed
		mov	ax, -1
		jmp	short @@ret

@@setblockFailed:
		push	bx
		push	ax
		call	__IOERROR
		pop	ax

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
_setblock	endp
