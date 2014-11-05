; size_t __cdecl strlen(const char *s)
public _strlen
_strlen		proc
@@s		= DPTR_ (2 + cPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
ife LDATA
		mov	ax, ds
		mov	es, ax
		mov	di, [bp+@@s]
		xor	ax, ax
else
		les	di, [bp+@@s]
		xor	ax, ax
		cmp	ax, word ptr [bp+@@s+2]
		jnz	short @@start
		cmp	ax, di
		je	short @@out
endif

@@start:
		cld
		mov	cx, -1
		repne scasb
		xchg	ax, cx
		not	ax
		dec	ax

@@out:
		pop	di
		pop	si
		pop	bp
		ret
_strlen		endp
