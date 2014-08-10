; char *__cdecl	strcpy(char *dest, const char *src)
public _strcpy
_strcpy		proc far

@@dest		= dword	ptr  6
@@src		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		cld
		les	di, [bp+@@src]
		mov	si, di
		xor	al, al
		mov	cx, 0FFFFh
		repne scasb
		not	cx
		push	ds
		mov	ax, es
		mov	ds, ax
		les	di, [bp+@@dest]
		rep movsb
		pop	ds
		mov	dx, word ptr [bp+@@dest+2]
		mov	ax, word ptr [bp+@@dest]
		pop	di
		pop	si
		pop	bp
		retf
_strcpy		endp
