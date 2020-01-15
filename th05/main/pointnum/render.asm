public POINTNUMS_RENDER
pointnums_render	proc near
	push	si
	push	di
	mov	di, offset _pointnums_alive
	mov	si, [di]
	or	si, si
	jz	short @@ret
	push	bp
	mov	ax, GRAM_400

	; grcg_setcolor(white)
	mov	es, ax
	mov	dx, 7Eh
	mov	al, 0FFh
	cli
	out	dx, al
	out	dx, al
	out	dx, al
	out	dx, al
	sti

@@number_loop:
	cmp	si, _pointnum_first_yellow_alive
	jnz	short @@set_coords

	; grcg_setcolor(yellow)
	mov	dx, 7Eh
	mov	al, 0FFh
	cli
	out	dx, al
	out	dx, al
	not	al
	out	dx, al
	not	al
	out	dx, al
	sti

@@set_coords:
	mov	bp, [si+pointnum_t.PN_width]
	shr	bp, 1	; BP = distance between leftmost pointnum and center_cur.x
	mov	dx, [si+pointnum_t.PN_center_cur.x]
	sar	dx, 4
	add	dx, PLAYFIELD_X
	sub	dx, bp
	shr	bp, 2	; BP = total number of digits to print

	; -1 for the trailing 0, -1 because the @@digit_loop ends based on the
	; sign flag, which is set once BP becomes negative
	sub	bp, 2

	mov	ax, [si+pointnum_t.PN_center_cur.y]
	add	ax, ((PLAYFIELD_Y - (POINTNUM_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	add	si, pointnum_t.PN_digits_lebcd
	add	si, bp

@@digit_loop:
	xor	ch, ch
	mov	cl, [si]
	call	@pointnum_put
	dec	si
	dec	bp
	jns	short @@digit_loop

	; Print the trailing 0
	xor	cx, cx
	call	@pointnum_put

@@next:
	add	di, word
	mov	si, [di]
	or	si, si
	jnz	short @@number_loop
	pop	bp

@@ret:
	pop	di
	pop	si
	retn
pointnums_render	endp
	even
