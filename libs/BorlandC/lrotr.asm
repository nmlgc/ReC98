; unsigned long __cdecl _lrotr(unsigned long val, int rotate_count)
__lrotr		proc
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
		mov	bx, dx
		shr	bx, 1
		rcr	ax, 1
		rcr	dx, 1
		loop	@@Rotating

@@Rotated:
		pop	di
		pop	si
		pop	bp
		ret
__lrotr		endp
