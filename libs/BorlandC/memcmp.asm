; int __cdecl memcmp(const void	*s1, const void	*s2, size_t n)
public _memcmp
_memcmp		proc DIST
@@s1		= DPTR_ 2 + dPtrSize
@@s2		= DPTR_ 2 + (dPtrSize * 2)
@@n		= word ptr 2 + (dPtrSize * 3)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		mov	ax, [bp+@@n]
		mov	cx, ax
		jcxz	short @@mcm_end
		LDS_	si, [bp+@@s1]
		LES_	di, [bp+@@s2]
ife LDATA
		mov	ax, ds
		mov	es, ax
endif
		cld
		repe cmpsb
		mov	al, [si-1]
		xor	ah, ah
		mov	cl, ES_ [di-1]
		xor	ch, ch

@@mcm_end:
		popDS_
		sub	ax, cx
		pop	di
		pop	si
		pop	bp
		ret
_memcmp		endp
