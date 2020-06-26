public VECTOR2_BETWEEN_PLUS
vector2_between_plus	proc far

@@r	= word ptr  6
@@_dx	= dword	ptr  8
@@_dy	= dword	ptr  0Ch
@@plus_angle	= byte ptr  10h
@@y2	= word ptr  12h
@@x2	= word ptr  14h
@@y1	= word ptr  16h
@@x1	= word ptr  18h

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@r]
	mov	ax, [bp+@@y2]
	sub	ax, [bp+@@y1]
	push	ax
	mov	ax, [bp+@@x2]
	sub	ax, [bp+@@x1]
	push	ax
	call	iatan2
	add	al, [bp+@@plus_angle]
	mov	dl, al
	movsx	eax, si
	mov	dh, 0
	add	dx, dx
	mov	bx, dx
	movsx	edx, _CosTable8[bx]
	movsx	ecx, _SinTable8[bx]
	imul	eax, edx
	sar	eax, 8
	les	bx, [bp+@@_dy]
	mov	es:[bx], ax
	movsx	eax, si
	imul	eax, ecx
	sar	eax, 8
	les	bx, [bp+@@_dx]
	mov	es:[bx], ax
	pop	si
	pop	bp
	retf	14h
vector2_between_plus	endp
