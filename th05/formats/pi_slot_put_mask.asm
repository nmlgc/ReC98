public PI_SLOT_PUT_MASK
pi_slot_put_mask	proc far
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
	les	si, _pi_slot_buffers[si]
	assume es:nothing
	imul	di, size PiHeader
	push	[bp+@@left]
	push	[bp+@@top]
	mov	ax, _pi_slot_headers._xsize[di]
	push	ax
	shr	ax, 1
	push	ax
	mov	di, _pi_slot_headers._ysize[di]
	mov	ax, [bp+@@mask_id]
	call	pi_slot_put_mask_rowloop
	pop	di
	pop	si
	pop	bp
	retf	8
pi_slot_put_mask	endp

; ---------------------------------------------------------------------------

public PI_SLOT_PUT_QUARTER_MASK
pi_slot_put_quarter_mask	proc far

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
	les	si, _pi_slot_buffers[si]
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
	call	pi_slot_put_mask_rowloop
	pop	di
	pop	si
	pop	bp
	retf	0Ah
pi_slot_put_quarter_mask	endp
	even

; ---------------------------------------------------------------------------

; void pascal pi_slot_put_mask_rowloop(
;	int mask_id<ax>,
;	void far *pi_buf<es:si>,
;	int h<di>,
;	screen_x_t left, vram_y_t top, int w, size_t stride_packed
; );
pi_slot_put_mask_rowloop	proc near
@@stride_packed	= word ptr [bp+2]
@@w	= word ptr [bp+4]
@@top	= word ptr [bp+6]
@@left	= word ptr [bp+8]
@@mask_id equ ax
@@h equ di

TEMP_ROW = RES_Y

	shl	@@mask_id, 3
	add	@@mask_id, offset _PI_MASKS
	mov	_pi_mask_ptr, @@mask_id
	mov	bp, sp
	mov	dx, @@left
	shr	dx, 3
	mov	ax, @@top
	shl	ax, 6
	add	dx, ax
	shr	ax, 2
	add	dx, ax
	mov	_pi_put_mask_vram_offset, dx
	mov	_pi_mask_y, 0

@@put_row:
	push	es
	call	graph_pack_put_8_noclip pascal, 0, TEMP_ROW, es, si, @@w
	push	ds
	push	@@h
	push	si
	mov	di, _pi_put_mask_vram_offset
	add	_pi_put_mask_vram_offset, ROW_SIZE
	cmp	_pi_put_mask_vram_offset, PLANE_SIZE
	jb	short @@next_row
	sub	_pi_put_mask_vram_offset, PLANE_SIZE

@@next_row:
	call	pi_egc_mask
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	ds, ax
	assume ds:nothing
	mov	si, (ROW_SIZE * TEMP_ROW)
	mov	cx, @@w
	shr	cx, 4
	rep movsw
	call	egc_off
	pop	si
	pop	@@h
	pop	ds
	assume ds:_DATA
	pop	es
	assume es:nothing
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
pi_slot_put_mask_rowloop	endp


; ---------------------------------------------------------------------------


pi_egc_mask	proc near
	call	egc_on
	outw2	EGC_ACTIVEPLANEREG, 0FFF0h
	egc_selectpat
	egc_setrop	EGC_COMPAREREAD or EGC_WS_PATREG or EGC_RL_MEMREAD
	outw2	EGC_ADDRRESSREG, 0
	outw2	EGC_BITLENGTHREG, 0Fh
	mov	bx, _pi_mask_ptr
	mov	ax, _pi_mask_y
	and	ax, 3
	shl	ax, 1
	add	bx, ax
	outw2	EGC_MASKREG, [bx]
	inc	_pi_mask_y
	retn
pi_egc_mask	endp
