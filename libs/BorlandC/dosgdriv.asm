; void _dos_getdrive(unsigned *drive)
public __dos_getdrive
__dos_getdrive	proc
@@drive		= DPTR_	2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 19h
		int	21h
		mov	ah, 0
		inc	ax
		les	bx, [bp+@@drive]
		mov	es:[bx], ax
		pop	di
		pop	si
		pop	bp
		ret
__dos_getdrive	endp

; void _dos_setdrive(unsigned drive, unsigned *ndrives)
public __dos_setdrive
__dos_setdrive	proc
@@drive		= word ptr 2 + dPtrSize
@@ndrives		= DPTR_ 4 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dl, byte ptr [bp+@@drive]
		dec	dl
		mov	ah, 0Eh
		int	21h
		mov	ah, 0
		les	bx, [bp+@@ndrives]
		mov	es:[bx], ax
		pop	di
		pop	si
		pop	bp
		ret
__dos_setdrive	endp
