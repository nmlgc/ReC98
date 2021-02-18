PI_PUT_MASKED_8_ROWLOOP procdesc near

public PI_PUT_MASKED_8
pi_put_masked_8 proc far
@@mask_id	= word ptr  6
@@slot	= word ptr  8
@@top	= word ptr  0Ah
@@left	= word ptr  0Ch

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@slot]
	mov	di, si
	shl	si, 2
	les	si, _pi_buffers[si]
	assume es:nothing
	imul	di, size PiHeader
	push	[bp+@@left]
	push	[bp+@@top]
	mov	ax, _pi_headers._xsize[di]
	push	ax
	shr	ax, 1
	push	ax
	mov	di, _pi_headers._ysize[di]
	mov	ax, [bp+@@mask_id]
	call	pi_put_masked_8_rowloop
	pop	di
	pop	si
	pop	bp
	retf	8
pi_put_masked_8 endp

; ---------------------------------------------------------------------------

public PI_PUT_QUARTER_MASKED_8
pi_put_quarter_masked_8 proc far

@@mask_id	= word ptr  6
@@quarter	= byte ptr  8
@@slot	= word ptr  0Ah
@@top	= word ptr  0Ch
@@left	= word ptr  0Eh

	push	bp
	mov	bp, sp
	push	si
	push	di
	xor	ax, ax
	xor	dx, dx
	mov	si, [bp+@@slot]
	mov	cl, [bp+@@quarter]
	test	cl, 1
	jz	short @@bottom_quarter?
	mov	ax, 160

@@bottom_quarter?:
	test	cl, 2
	jz	short @@put
	mov	dx, ((640 * 200) / 2) / 16

@@put:
	shl	si, 2
	les	si, _pi_buffers[si]
	add	si, ax
	mov	ax, es
	add	ax, dx
	mov	es, ax
	assume es:nothing
	mov	di, 200
	push	[bp+@@left]
	push	[bp+@@top]
	push	320
	push	320
	mov	ax, [bp+@@mask_id]
	call	pi_put_masked_8_rowloop
	pop	di
	pop	si
	pop	bp
	retf	0Ah
pi_put_quarter_masked_8 endp
	even
