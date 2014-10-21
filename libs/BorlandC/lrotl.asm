; unsigned long __cdecl _lrotl(unsigned long val, int rotate_count)
__lrotl		proc DIST
@@val		= dword	ptr (cPtrSize + 2)
@@rotate_count	= word ptr (cPtrSize + 2 + 4)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+@@val]
		mov	dx, word ptr [bp+@@val+2]
		mov	cx, [bp+@@rotate_count]
		and	cx, 1Fh
		jz	short @@Rotated

@@Rotating:
		rcl	ax, 1
		rcl	dx, 1
		adc	ax, 0
		loop	@@Rotating

@@Rotated:
		pop	di
		pop	si
		pop	bp
		ret
__lrotl		endp
