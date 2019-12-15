proc_defconv pi_slot_put
@@slot	= word ptr [bp + (cPtrSize + 2)]
@@y	= word ptr [bp + (cPtrSize + 4)]
@@x	= word ptr [bp + (cPtrSize + 6)]

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, @@slot
	mov	di, si
	shl	si, 2
	les	si, _pi_slot_buffers[si]
	imul	di, size PiHeader
	push	@@x
	push	@@y
	mov	ax, _pi_slot_headers.PiHeader._xsize[di]
	push	ax
	shr	ax, 1
	push	ax
	mov	di, _pi_slot_headers.PiHeader._ysize[di]
	call	pi_slot_put_rowloop
	pop	di
	pop	si
	pop	bp
	ret	6
endp_defconv
	align	2

; ---------------------------------------------------------------------------

proc_defconv pi_slot_put_quarter
@@quarter	= byte ptr [bp + (cPtrSize + 2)]
@@slot	= word ptr [bp + (cPtrSize + 4)]
@@y	= word ptr [bp + (cPtrSize + 6)]
@@x	= word ptr [bp + (cPtrSize + 8)]

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
	les	si, _pi_slot_buffers[si]
	add	si, ax
	mov	ax, es
	add	ax, dx
	mov	es, ax
	push	@@x
	push	@@y
	push	320
	push	320
	mov	di, 200
	call	pi_slot_put_rowloop
	pop	di
	pop	si
	pop	bp
	ret	8
endp_defconv

; ---------------------------------------------------------------------------

; void pascal pi_slot_put_mask_rowloop(
;	void far *pi_buf<es:si>,
;	int h<di>,
;	int x, int y, int w, size_t stride_packed
; );
pi_slot_put_rowloop	proc near
@@stride_packed	= word ptr [bp+2]
@@w	= word ptr [bp+4]
@@y	= word ptr [bp+6]
@@x	= word ptr [bp+8]
@@h equ di

	mov	bp, sp

@@put_row:
	push	es
	call	graph_pack_put_8_noclip pascal, @@x, @@y, es, si, @@w
	pop	es
	inc	@@y
	cmp	@@y, RES_Y
	jb	short @@next_row
	sub	@@y, RES_Y

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
pi_slot_put_rowloop	endp
