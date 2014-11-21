; int flushall(void)
_flushall	proc
@@Cpt		= word ptr -(dPtrSize + 4)
@@Nb		= word ptr -(dPtrSize + 2)
@@fp		= DPTR_ -(dPtrSize)
if LDATA
	@@local_stack = 8
else
	@@local_stack = 6
endif

		push	bp
		mov	bp, sp
		sub	sp, @@local_stack
		push	si
		push	di
		mov	[bp+@@Cpt], 0
		mov	ax, __nfile
		mov	[bp+@@Nb], ax
if LDATA
		mov	word ptr [bp+@@fp+2], ds
endif
		mov	word ptr [bp+@@fp], offset _streams
		jmp	short flushall_loop

flushall_RDWR?:
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], 3
		jz	short flushall_next
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	bx
		nopcall	_fflush
		popCX_
		pop	cx
		inc	[bp+@@Cpt]

flushall_next:
		add	word ptr [bp+@@fp], size FILE

flushall_loop:
		mov	ax, [bp+@@Nb]
		dec	[bp+@@Nb]
		or	ax, ax
		jnz	short flushall_RDWR?
		mov	ax, [bp+@@Cpt]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_flushall	endp
