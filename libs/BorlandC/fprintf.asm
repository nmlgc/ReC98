; int fprintf(FILE *F, const char *fmt, ...)
_fprintf	proc DIST
@@F		= DPTR_ (cPtrSize + 2)
@@fmt		= DPTR_ (cPtrSize + 2 + dPtrSize)
@@va		= byte ptr (cPtrSize + 2 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, offset __FPUTN
		push	ax
if LDATA
		push	word ptr [bp+@@F+2]
endif
		push	word ptr [bp+@@F]
if LDATA
		push	word ptr [bp+@@fmt+2]
endif
		push	word ptr [bp+@@fmt]
		lea	ax, [bp+@@va]
		push	ax
		call	__vprinter
		pop	di
		pop	si
		pop	bp
		ret
_fprintf	endp
