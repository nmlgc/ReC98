; int scanf(const char *fmt, ...)
_scanf		proc
@@fmt		= DPTR_ (2 + cPtrSize)
@@va		= word ptr (2 + cPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		pushSS_
		lea	ax, [bp+@@va]
		push	ax
if LDATA
		push	word ptr [bp+@@fmt+2]
endif
		push	word ptr [bp+@@fmt]
		pushDS_
		mov	ax, offset stdin
		push	ax
		mov	ax, offset __Nungetc
		push	ax
		mov	ax, offset __Nfgetc
		push	ax
		call	_scanner
		add	sp, 4 + (dPtrSize * 3)
		pop	di
		pop	si
		pop	bp
		ret
_scanf		endp
