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
		mov	ax, seg	___path_dbcs_default

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
___path_isdbcsleadbyte proc far
@@arg_0		= byte ptr  6

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
___path_issbcs	proc far
var_4		= dword	ptr -4
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		xor	cx, cx
		mov	dx, [bp+arg_2]
		mov	ax, [bp+arg_0]
		mov	word ptr [bp+var_4+2], dx
		mov	word ptr [bp+var_4], ax

@@pathops_10094:
		les	bx, [bp+var_4]
		cmp	byte ptr es:[bx], 0
		jnz	short @@pathops_100A1
		xor	cx, cx
		jmp	short @@pathops_100CF

@@pathops_100A1:
		cmp	cx, 1
		jnz	short @@pathops_100AB
		mov	cx, 2
		jmp	short @@pathops_100C2

@@pathops_100AB:
		les	bx, [bp+var_4]
		mov	al, es:[bx]
		push	ax
		call	___path_isdbcsleadbyte
		pop	cx
		or	ax, ax
		jz	short @@pathops_100C0
		mov	cx, 1
		jmp	short @@pathops_100C2

@@pathops_100C0:
		xor	cx, cx

@@pathops_100C2:
		mov	ax, word ptr [bp+var_4]
		cmp	ax, [bp+arg_4]
		jnb	short @@pathops_100CF
		inc	word ptr [bp+var_4]
		jmp	short @@pathops_10094

@@pathops_100CF:
		or	cx, cx
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
