; size_t __pascal __near strputn(char *S, size_t n, char **bufPP)
strputn		proc near
@@bufPP		= DPTR_ (4)
@@n		= word ptr (4 + dPtrSize)
@@S		= DPTR_ (4 + dPtrSize + 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@n]
		push	word ptr [bp+@@S+2]
		push	word ptr [bp+@@S]
		LES_	bx, [bp+@@bufPP]
		push	word ptr ES_[bx+2]
		push	word ptr ES_[bx]
		nopcall	_memcpy
		add	sp, (2 + dPtrSize + dPtrSize)
		mov	ax, [bp+@@n]
		LES_	bx, [bp+@@bufPP]
		add	ES_[bx], ax
		push	bx
		push	es
		mov	es, word ptr ES_[bx+2]
		mov	ax, es
		pop	es
		pop	bx
		mov	bx, ES_[bx]
		mov	es, ax
		mov	byte ptr ES_[bx], 0
		mov	ax, [bp+@@n]
		pop	di
		pop	si
		pop	bp
		ret	(4 + dPtrSize + 2)
strputn		endp

; int __far sprintf(char *bufP, const char *fmt, ...)
_sprintf	proc
@@bufP		= DPTR_ (cPtrSize + 2)
@@fmt		= DPTR_ (cPtrSize + 2 + dPtrSize)
@@va		= byte ptr (cPtrSize + 2 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		LES_	bx, [bp+@@bufP]
		mov	byte ptr ES_[bx], 0
		mov	ax, offset strputn
		push	ax
		push	ss
		lea	ax, [bp+@@bufP]
		push	ax
		push	word ptr [bp+@@fmt+2]
		push	word ptr [bp+@@fmt]
		lea	ax, [bp+@@va]
		push	ax
		call	__vprinter
		pop	di
		pop	si
		pop	bp
		ret
_sprintf	endp

; int __cdecl __far vsprintf(char *@@bufP, const char *@@fmt, va_list @@ap)
_vsprintf	proc
@@bufP		= DPTR_ (cPtrSize + 2)
@@fmt		= DPTR_ (cPtrSize + 2 + dPtrSize)
@@ap		= DPTR_ (cPtrSize + 2 + dPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		LES_	bx, [bp+@@bufP]
		mov	byte ptr ES_[bx], 0
		mov	ax, offset strputn
		push	ax
		push	ss
		lea	ax, [bp+@@bufP]
		push	ax
		push	word ptr [bp+@@fmt+2]
		push	word ptr [bp+@@fmt]
		push	word ptr [bp+@@ap]
		call	__vprinter
		pop	di
		pop	si
		pop	bp
		ret
_vsprintf	endp
