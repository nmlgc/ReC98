; void __cdecl movmem(const void *src, void *dst, unsigned int len)
_movmem		proc
@@src		= DPTR_ 2 + dPtrSize
@@dst		= DPTR_ 2 + (dPtrSize * 2)
@@len		= word ptr 2 + (dPtrSize * 3)

		push	bp
		mov	bp, sp
		push	si
		push	di
ifndef __HUGE
		push	ds
endif
		mov	cx, word ptr [bp+@@dst+2]
		mov	bx, word ptr [bp+@@dst]
		mov	dx, word ptr [bp+@@src+2]
		mov	ax, word ptr [bp+@@src]
		call	N_PCMP@
		jnb	short @@forward
		std
		mov	ax, 1
		jmp	short @@prepare

@@forward:
		cld
		xor	ax, ax

@@prepare:
		LDS_	si, [bp+@@src]
		LES_	di, [bp+@@dst]
		mov	cx, [bp+@@len]
		or	ax, ax
		jz	short @@movit
		add	si, cx
		dec	si
		add	di, cx
		dec	di

@@movit:
		test	di, 1
		jz	short @@isAligned
		jcxz	short @@done
		movsb
		dec	cx

@@isAligned:
		sub	si, ax
		sub	di, ax
		shr	cx, 1
		rep movsw
		jnb	short @@noOdd
		add	si, ax
		add	di, ax
		movsb

@@noOdd:
@@done:
		cld
if LDATA
		pop	ds
endif
		pop	di
		pop	si
		pop	bp
		ret
_movmem		endp

; void *__cdecl	memmove(void *dest, const void *src, size_t n)
public _memmove
_memmove	proc
@@dst		= DPTR_ 2 + dPtrSize
@@src		= DPTR_ 2 + (dPtrSize * 2)
@@len		= word ptr 2 + (dPtrSize * 3)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@len]
		push	word ptr [bp+@@dst+2]
		push	word ptr [bp+@@dst]
		push	word ptr [bp+@@src+2]
		push	word ptr [bp+@@src]
		call	_movmem
		add	sp, 0Ah
		mov	dx, word ptr [bp+@@dst+2]
		mov	ax, word ptr [bp+@@dst]
		pop	di
		pop	si
		pop	bp
		ret
_memmove	endp
