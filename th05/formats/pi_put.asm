public PI_PUT_8
pi_put_8 proc
@@slot	= word ptr [bp + (cPtrSize + 2)]
@@top	= word ptr [bp + (cPtrSize + 4)]
@@left	= word ptr [bp + (cPtrSize + 6)]

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, @@slot
	mov	di, si
	shl	si, 2
	les	si, _pi_buffers[si]
	imul	di, size PiHeader
	push	@@left
	push	@@top
	mov	ax, _pi_headers.PiHeader._xsize[di]
	push	ax
	shr	ax, 1
	push	ax
	mov	di, _pi_headers.PiHeader._ysize[di]
	call	pi_put_8_rowloop
	pop	di
	pop	si
	pop	bp
	ret	6
pi_put_8 endp
	align	2

; ---------------------------------------------------------------------------

public PI_PUT_QUARTER_8
pi_put_quarter_8 proc
@@quarter	= byte ptr [bp + (cPtrSize + 2)]
@@slot	= word ptr [bp + (cPtrSize + 4)]
@@top	= word ptr [bp + (cPtrSize + 6)]
@@left	= word ptr [bp + (cPtrSize + 8)]

	push	bp
	mov	bp, sp
	push	si
	push	di
	xor	ax, ax
	xor	dx, dx
	mov	si, @@slot
	mov	cl, @@quarter
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
	push	@@left
	push	@@top
	push	320
	push	320
	mov	di, 200
	call	pi_put_8_rowloop
	pop	di
	pop	si
	pop	bp
	ret	8
pi_put_quarter_8 endp

; ---------------------------------------------------------------------------

; void pascal pi_put_8_rowloop(
;	void far *pi_buf<es:si>,
;	pixel_t h<di>,
;	screen_x_t x, vram_y_t y, pixel_t w, size_t stride_packed
; );
pi_put_8_rowloop proc near
@@stride_packed	= word ptr [bp+2]
@@w	= word ptr [bp+4]
@@top	= word ptr [bp+6]
@@left	= word ptr [bp+8]
@@h equ di

	mov	bp, sp

@@put_row:
	push	es
	call	graph_pack_put_8_noclip pascal, @@left, @@top, es, si, @@w
	pop	es
	inc	@@top
	cmp	@@top, RES_Y
	jb	short @@next_row
	sub	@@top, RES_Y

@@next_row:
	add	si, @@stride_packed
	mov	ax, si
	shr	ax, 4
	mov	dx, es
	add	dx, ax
	mov	es, dx
	and	si, 0Fh
	dec	@@h
	jnz	short @@put_row
	retn	8
pi_put_8_rowloop endp
