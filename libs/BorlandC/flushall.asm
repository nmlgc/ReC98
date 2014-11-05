; int flushall(void)
_flushall	proc
@@Cpt		= word ptr -(dPtrSize + 4)
@@Nb		= word ptr -(dPtrSize + 2)
@@fp		= DPTR_ -(dPtrSize)
if LDATA
@@local_stack equ 8
else
@@local_stack equ 6
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
		jmp	short @@loop

@@RDWR?:
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], 3
		jz	short @@next
if LDATA
		push	word ptr [bp+@@fp+2]
endif
		push	bx
		nopcall	_fflush
if LDATA
		pop	cx
endif
		pop	cx
		inc	[bp+@@Cpt]

@@next:
		add	word ptr [bp+@@fp], size FILE

@@loop:
		mov	ax, [bp+@@Nb]
		dec	[bp+@@Nb]
		or	ax, ax
		jnz	short @@RDWR?
		mov	ax, [bp+@@Cpt]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_flushall	endp
