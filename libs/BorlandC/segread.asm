; void __cdecl segread(struct SREGS *segp)
_segread	proc
@@segp		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
if LDATA
		mov	bx, es
endif
		LES_	si, [bp+@@segp]
if LDATA
		mov	es:[si], bx
else
		mov	[si]._es, es
endif
if LPROG
		mov	ax, [bp+4]
		mov	ES_[si]._cs, ax
else
		mov	ES_[si]._cs, cs
endif
		mov	word ptr ES_[si]._ss, ss
ifdef __HUGE__
		mov	ax, [bp+4]
		mov	ES_[si]._ds, ax
else
		mov	word ptr ES_[si]._ds, ds
endif
if LDATA
		mov	es, bx
endif
		pop	di
		pop	si
		pop	bp
		ret
_segread	endp
