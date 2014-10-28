; int printf(const char	*format, ...)
_printf		proc DIST
@@format		= DPTR_ (2 + cPtrSize)
@@va		= byte ptr (2 + cPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, offset __fputn
		push	ax
		push	ds
		mov	ax, offset stdout
		push	ax
if LDATA
		push	word ptr [bp+@@format+2]
endif
		push	word ptr [bp+@@format]
		lea	ax, [bp+@@va]
		push	ax
		call	__vprinter
		pop	di
		pop	si
		pop	bp
		ret
_printf		endp
