; void __ErrorMessage(const char *msg)
public ___ErrorMessage
___ErrorMessage	proc DIST
@@msg		= DPTR_	2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
if LDATA
		push	word ptr [bp+@@msg+2]
		push	word ptr [bp+@@msg]
		nop
		call	_strlen
		pop	cx
else
		push	[bp+@@msg]
		call	_strlen
endif
		pop	cx
		push	ax
if LDATA
		push	word ptr [bp+@@msg+2]
endif
		push	word ptr [bp+@@msg]
		mov	al, stderr.fd
		cbw
		push	ax
if LDATA
		nop
		call	__rtl_write
		add	sp, 8
else
		call	__rtl_write
		add	sp, 6
endif
		pop	di
		pop	si
		pop	bp
		ret
___ErrorMessage	endp
