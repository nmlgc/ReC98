; size_t __cdecl strlen(const char *s)
public _strlen

ifdef __LARGE__

_strlen		proc far

@@s		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		les	di, [bp+@@s]
		xor	ax, ax
		cmp	ax, word ptr [bp+@@s+2]
		jnz	short @@start
		cmp	ax, di
		jz	short @@return

@@start:
		cld
		mov	cx, 0FFFFh
		repne scasb
		xchg	ax, cx
		not	ax
		dec	ax

@@return:
		pop	di
		pop	si
		pop	bp
		retf
_strlen		endp

else

_strlen		proc near

s		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, ds
		mov	es, ax
		mov	di, [bp+s]
		xor	ax, ax
		cld
		mov	cx, 0FFFFh
		repne scasb
		xchg	ax, cx
		not	ax
		dec	ax
		pop	di
		pop	si
		pop	bp
		retn
_strlen		endp

endif
