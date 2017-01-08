; int pascal far vector2_at(int angle, int length, int origin_y, int origin_x, Point *ret)
vector2_at	proc far

@@angle	= word ptr  6
@@length	= word ptr  8
@@origin_y	= word ptr  0Ah
@@origin_x	= word ptr  0Ch
@@ret	= Point ptr  0Eh

	push	bp
	mov	bp, sp
	push	si
	mov	si, word ptr [bp+@@ret]
	mov	bx, [bp+@@angle]
if GAME eq 5
	xor	bh, bh
endif
	add	bx, bx
	movsx	eax, [bp+@@length]
	movsx	edx, _CosTable8[bx]
	imul	eax, edx
	sar	eax, 8
	add	ax, [bp+@@origin_x]
	mov	[si], ax
	movsx	eax, [bp+@@length]
	movsx	edx, _SinTable8[bx]
	imul	eax, edx
	sar	eax, 8
	add	ax, [bp+@@origin_y]
	mov	[si+2],	ax
	pop	si
	pop	bp
	retf	0Ah
vector2_at	endp
