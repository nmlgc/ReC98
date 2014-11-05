		public _pow10
; double __cdecl pow10(int p)
_pow10		proc
@@p		= word ptr (2 + cPtrSize)

		push	bp
		mov	bp, sp
		push	[bp+@@p]
		call	__POW10
		pop	bp
		ret
_pow10		endp
