public VECTOR2_NEAR
vector2_near	proc near

@@r	= word ptr  4
@@angle	= byte ptr  6
@@_ret	= word ptr  8

	push	bp
	mov	bp, sp
	movsx	edx, [bp+@@r]
	mov	bl, [bp+@@angle]
	mov	bh, 0
	add	bx, bx
	movsx	eax, _CosTable8[bx]
	movsx	ecx, _SinTable8[bx]
	imul	eax, edx
	sar	eax, 8
	imul	edx, ecx
	sar	edx, 8
	mov	bx, [bp+@@_ret]
	mov	[bx], ax
	mov	[bx+2],	dx
	pop	bp
	retn	6
vector2_near	endp
