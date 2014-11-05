; void _xfflush(void)
public __xfflush
__xfflush	proc
@@i		= word ptr -(dPtrSize + 2)
@@fp		= DPTR_ -(dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize + 2
		push	si
		push	di
		mov	[bp+@@i], 4
if LDATA
		mov	word ptr [bp+@@fp+2], ds
endif
		mov	word ptr [bp+@@fp], offset _streams
		jmp	short @@check_i

@@check_RDWR:
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], 3
		jz	short @@advance
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	bx
		nopcall	_fflush
		pop	cx
if LDATA
		pop	cx
endif

@@advance:
		dec	[bp+@@i]
		add	word ptr [bp+@@fp], size FILE

@@check_i:
		cmp	[bp+@@i], 0
		jnz	short @@check_RDWR
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__xfflush	endp
