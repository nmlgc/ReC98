; int __cdecl strcmp(const char	*s1, const char	*s2)
public _strcmp
_strcmp		proc far

@@s1		= dword	ptr  6
@@s2		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, ds
		cld
		xor	ax, ax
		mov	bx, ax
		les	di, [bp+@@s2]
		mov	si, di
		xor	al, al
		mov	cx, 0FFFFh
		repne scasb
		not	cx
		mov	di, si
		lds	si, [bp+@@s1]
		repe cmpsb
		mov	al, [si-1]
		mov	bl, es:[di-1]
		sub	ax, bx
		mov	ds, dx
		pop	di
		pop	si
		pop	bp
		retf
_strcmp		endp
