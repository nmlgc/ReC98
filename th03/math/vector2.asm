public VECTOR2
vector2	proc far

@@r		= word ptr  6
@@angle		= byte ptr  8
@@_dy		= dword	ptr  0Ah
@@_dx		= dword	ptr  0Eh

	push	bp
	mov	bp, sp
	push	si
	mov	dl, [bp+@@angle]
	mov	si, [bp+@@r]
	movsx	eax, si
	mov	dh, 0
	add	dx, dx
	mov	bx, dx
	movsx	edx, _CosTable8[bx]
	movsx	ecx, _SinTable8[bx]
	imul	eax, edx
	sar	eax, 8
	les	bx, [bp+@@_dx]
	mov	es:[bx], ax
	movsx	eax, si
	imul	eax, ecx
	sar	eax, 8
	les	bx, [bp+@@_dy]
	mov	es:[bx], ax
	pop	si
	pop	bp
	retf	0Ch
vector2	endp
