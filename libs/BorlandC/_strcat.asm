; char *__cdecl	strcat(char *dest, const char *src)
public _strcat
_strcat		proc far

@@dest		= dword	ptr  6
@@src		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		cld
		push	ds
		les	di, [bp+@@dest]
		mov	dx, di
		xor	al, al
		mov	cx, 0FFFFh
		repne scasb
		push	es
		lea	si, [di-1]
		les	di, [bp+@@src]
		mov	cx, 0FFFFh
		repne scasb
		not	cx
		sub	di, cx
		push	es
		pop	ds
		pop	es
		xchg	si, di
		test	si, 1
		jz	short @@move_rest
		movsb
		dec	cx

@@move_rest:
		shr	cx, 1
		rep movsw
		jnb	short @@move_last
		movsb

@@move_last:
		xchg	ax, dx
		mov	dx, es
		pop	ds
		pop	di
		pop	si
		pop	bp
		retf
_strcat		endp
