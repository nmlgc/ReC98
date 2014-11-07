; static int near pascal normalize(char far *cp)
_normalize	proc near

_size		= word ptr -2
cp		= dword ptr  4

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, word ptr [bp+cp+2]
		inc	ax
		mov	[bp+_size], ax
		mov	ax, __psp
		sub	[bp+_size], ax
		mov	ax, [bp+_size]
		add	ax, 3Fh	; '?'
		mov	cl, 6
		shr	ax, cl
		mov	[bp+_size], ax
		cmp	ax, xsize
		jz	short @@loc_4C8A
		mov	cl, 6
		shl	[bp+_size], cl
		mov	dx, word ptr __heaptop+2
		mov	ax, [bp+_size]
		add	ax, __psp
		cmp	ax, dx
		jbe	short @@loc_4C6B
		mov	ax, dx
		sub	ax, __psp
		mov	[bp+_size],	ax

@@loc_4C6B:
		push	[bp+_size]	; newsize
		push	__psp		; __psp
		nopcall	_setblock
		pop	cx
		pop	cx
		mov	dx, ax
		cmp	dx, 0FFFFh
		jnz	short @@loc_4C9C
		mov	ax, [bp+_size]
		mov	cl, 6
		shr	ax, cl
		mov	xsize, ax

@@loc_4C8A:
		mov	dx, word ptr [bp+cp+2]
		mov	ax, word ptr [bp+cp]
		mov	word ptr __brklvl+2, dx
		mov	word ptr __brklvl, ax
		mov	ax, 1
		jmp	short @@loc_4CAC
; ---------------------------------------------------------------------------

@@loc_4C9C:
		mov	ax, __psp
		add	ax, dx
		mov	word ptr __heaptop+2, ax
		mov	word ptr __heaptop, 0
		xor	ax, ax

@@loc_4CAC:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	4
_normalize	endp

; int cdecl near _brk(void huge *addr)
public __brk
__brk		proc near

@@addr		= dword ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, word ptr __heapbase+2
		mov	bx, word ptr __heapbase
		mov	dx, word ptr [bp+@@addr+2]
		mov	ax, word ptr [bp+@@addr]
		call	N_PCMP@
		jb	short @@loc_4CEC
		mov	cx, word ptr __heaptop+2
		mov	bx, word ptr __heaptop
		mov	dx, word ptr [bp+@@addr+2]
		mov	ax, word ptr [bp+@@addr]
		call	N_PCMP@
		ja	short @@loc_4CEC
		push	word ptr [bp+@@addr+2]
		push	word ptr [bp+@@addr]
		call	_normalize
		or	ax, ax
		jnz	short @@loc_4CF1

@@loc_4CEC:
		mov	ax, 0FFFFh
		jmp	short @@loc_4CF3
; ---------------------------------------------------------------------------

@@loc_4CF1:
		xor	ax, ax

@@loc_4CF3:
		pop	di
		pop	si
		pop	bp
		retn
__brk		endp

; void huge *cdecl near _sbrk(long incr)
public __sbrk
__sbrk		proc near

old		= dword ptr -8
cp		= dword ptr -4
incr		= dword ptr  4

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	ax, word ptr __brklvl+2
		xor	dx, dx
		mov	cl, 4
		call	near ptr N_LXLSH@
		add	ax, word ptr __brklvl
		adc	dx, 0
		add	ax, word ptr [bp+incr]
		adc	dx, word ptr [bp+incr+2]
		cmp	dx, 0Fh
		jl	short @@loc_4D22
		jg	short @@loc_4D72
		cmp	ax, 0FFFFh
		ja	short @@loc_4D72

@@loc_4D22:
		mov	dx, word ptr __brklvl+2
		mov	ax, word ptr __brklvl
		mov	cx, word ptr [bp+incr+2]
		mov	bx, word ptr [bp+incr]
		call	near ptr N_PADD@
		mov	word ptr [bp+cp+2], dx
		mov	word ptr [bp+cp], ax
		mov	cx, word ptr __heapbase+2
		mov	bx, word ptr __heapbase
		call	N_PCMP@
		jb	short @@loc_4D72
		mov	cx, word ptr __heaptop+2
		mov	bx, word ptr __heaptop
		mov	dx, word ptr [bp+cp+2]
		mov	ax, word ptr [bp+cp]
		call	N_PCMP@
		ja	short @@loc_4D72
		mov	dx, word ptr __brklvl+2
		mov	ax, word ptr __brklvl
		mov	word ptr [bp+old+2], dx
		mov	word ptr [bp+old], ax
		push	word ptr [bp+cp+2]
		push	word ptr [bp+cp]
		call	_normalize
		or	ax, ax
		jnz	short @@loc_4D7A

@@loc_4D72:
		mov	dx, 0FFFFh
		mov	ax, 0FFFFh
		jmp	short @@loc_4D80
; ---------------------------------------------------------------------------

@@loc_4D7A:
		mov	dx, word ptr [bp+old+2]
		mov	ax, word ptr [bp+old]

@@loc_4D80:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
__sbrk		endp
