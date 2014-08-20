; void (__cdecl	__interrupt far	*__cdecl getvect(int intr))()
public _getvect
_getvect	proc DIST
@@intr	= byte ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 35h
		mov	al, [bp+@@intr]
		int	21h
		xchg	ax, bx
		mov	dx, es
		pop	di
		pop	si
		pop	bp
		ret
_getvect	endp

; void __cdecl setvect(int intr, void (__interrupt far *func)())
public _setvect
_setvect	proc DIST
@@intr	= byte ptr  6
@@func	= dword	ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 25h
		mov	al, [bp+@@intr]
		push	ds
		lds	dx, [bp+@@func]
		int	21h
		pop	ds
		pop	di
		pop	si
		pop	bp
		ret
_setvect	endp
