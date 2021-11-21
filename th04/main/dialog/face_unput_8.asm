public @DIALOG_FACE_UNPUT_8$QUIUI
@dialog_face_unput_8$quiui	proc near

@@top		= word ptr  4
@@left		= word ptr  6

	push	bp
	mov	bp, sp
	push	di
	call	egc_start_copy_inlined_noframe
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, GRAM_400
	mov	es, ax	; ES = (GRAM_400 + (top * (ROW_SIZE / 16)))
	assume es:nothing
	mov	di, ((FACE_H - 1) * ROW_SIZE)
	mov	ax, [bp+@@left]
	shr	ax, 3
	add	di, ax
	mov	dx, 0A6h
	mov	al, _page_back

@@y_loop:
	mov	cx, (FACE_W / (2 * BYTE_DOTS))

@@x_loop:
	out	dx, al	; graph_accesspage(page_back)
	xor	al, 1
	mov	bx, es:[di]
	out	dx, al	; graph_accesspage(page_back ^ 1)
	xor	al, 1
	mov	es:[di], bx
	add	di, 2
	loop	@@x_loop
	sub	di, (ROW_SIZE + (FACE_W / BYTE_DOTS))
	jge	short @@y_loop
	call	egc_off
	pop	di
	pop	bp
	retn	4
@dialog_face_unput_8$quiui endp
