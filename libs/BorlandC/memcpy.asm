; void *__cdecl	memcpy(void *dst, const void *src, size_t n)
_memcpy		proc
@@dst		= DPTR_ 2 + dPtrSize
@@src		= DPTR_ 2 + (dPtrSize * 2)
@@n		= word ptr 2 + (dPtrSize * 3)

		push	bp
		mov	bp, sp
		push	si
		push	di
if LDATA
		mov	dx, ds
endif
		LES_	di, [bp+@@dst]
		LDS_	si, [bp+@@src]
		mov	cx, [bp+@@n]
		shr	cx, 1
		cld
		rep movsw
		jnb	short @@cpy_end
		movsb

@@cpy_end:
if LDATA
		mov	ds, dx
endif
		mov	dx, word ptr [bp+@@dst+2]
		mov	ax, word ptr [bp+@@dst]
		pop	di
		pop	si
		pop	bp
		ret
_memcpy		endp
