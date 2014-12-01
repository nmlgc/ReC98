if LDATA
	issbcsValXOR macro
		xor	cx, cx
	endm
else
	issbcsValXOR macro
		xor	dx, dx
	endm
endif

pathops_10010	proc near
		push	ax
		push	cx
		push	dx
		push	bx
		push	sp
		push	bp
		push	si
		push	di
		push	ds
		push	es
		mov	bp, sp
		mov	ax, word ptr ___path_dbcs_vector
		or	ax, word ptr ___path_dbcs_vector+2
		jnz	short @@pathops_1004C
		mov	si, 0FFFFh
		push	ds
		mov	ax, 6300h
		clc
		int	21h
		mov	ax, ds
		pop	ds
		jb	short @@pathops_1003F
		mov	dx, ds
		cmp	ax, dx
		jz	short @@pathops_1003F
		cmp	si, 0FFFFh
		jnz	short @@pathops_10045

@@pathops_1003F:
		mov	si, offset ___path_dbcs_default
if LDATA
		mov	ax, seg	___path_dbcs_default
else
		mov	ax, ds
endif

@@pathops_10045:
		mov	word ptr ___path_dbcs_vector, si
		mov	word ptr ___path_dbcs_vector+2,	ax

@@pathops_1004C:
		mov	sp, bp
		pop	es
		pop	ds
		pop	di
		pop	si
		pop	bp
		pop	bx
		pop	bx
		pop	dx
		pop	cx
		pop	ax
		ret
pathops_10010	endp


		public ___path_isdbcsleadbyte
___path_isdbcsleadbyte proc
@@arg_0		= byte ptr (cPtrSize + 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	al, [bp+@@arg_0]
		xor	cx, cx
		les	bx, ___path_dbcs_vector

@@pathops_10067:
		mov	dx, es:[bx]
		or	dx, dx
		jz	short @@pathops_10079
		cmp	al, dl
		jb	short @@pathops_10079
		inc	bx
		inc	bx
		cmp	al, dh
		ja	short @@pathops_10067
		inc	cx

@@pathops_10079:
		xchg	ax, cx
		pop	di
		pop	si
		pop	bp
		ret
___path_isdbcsleadbyte endp


		public ___path_issbcs
___path_issbcs	proc
var_4		= DPTR_ -(dPtrSize)
arg_0		= DPTR_ +(cPtrSize + 2)
arg_4		= word ptr +(cPtrSize + 2 + dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize
		push	si
		push	di
		issbcsValXOR
if LDATA
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		mov	word ptr [bp+var_4+2], dx
		mov	word ptr [bp+var_4], ax
else
		mov	ax, [bp+arg_0]
		mov	word ptr [bp+var_4], ax
endif

@@pathops_10094:
		LES_	bx, [bp+var_4]
		cmp	byte ptr ES_[bx], 0
		jnz	short @@pathops_100A1
		issbcsValXOR
		jmp	short @@pathops_100CF

@@pathops_100A1:
if LDATA
		cmp	cx, 1
		jnz	short @@pathops_100AB
		mov	cx, 2
else
		cmp	dx, 1
		jnz	short @@pathops_100AB
		mov	dx, 2
endif
		jmp	short @@pathops_100C2

@@pathops_100AB:
		LES_	bx, [bp+var_4]
if LDATA
		mov	al, ES_[bx]
		push	ax
else
		push	word ptr [bx]
endif
		call	___path_isdbcsleadbyte
		pop	cx
		or	ax, ax
		jz	short @@pathops_100C0
if LDATA
		mov	cx, 1
else
		mov	dx, 1
endif
		jmp	short @@pathops_100C2

@@pathops_100C0:
		issbcsValXOR

@@pathops_100C2:
		mov	ax, word ptr [bp+var_4]
		cmp	ax, [bp+arg_4]
		jnb	short @@pathops_100CF
		inc	word ptr [bp+var_4]
		jmp	short @@pathops_10094

@@pathops_100CF:
if LDATA
		or	cx, cx
else
		or	dx, dx
endif
		jnz	short @@pathops_100D8
		mov	ax, 1
		jmp	short @@pathops_100DA

@@pathops_100D8:
		xor	ax, ax

@@pathops_100DA:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
___path_issbcs	endp
