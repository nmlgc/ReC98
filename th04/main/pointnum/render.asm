public POINTNUMS_RENDER
pointnums_render proc near

@@digits_to_put equ <bp>

	push	bp
	push	si
	push	di
	; grcg_setcolor(white)
	mov	dx, 7Eh
	mov	al, 0FFh
	cli
	out	dx, al
	out	dx, al
	out	dx, al
	out	dx, al
	sti

	mov	ax, GRAM_400
	mov	es, ax
	mov	di, offset _pointnums_alive
	mov	si, [di]
	cmp	si, 0
	jz	short @@ret

@@number_loop:
	cmp	si, _pointnum_first_yellow_alive
	jnz	short @@set_coords

	; grcg_setcolor(yellow)
	mov	dx, 7Eh
	mov	al, 0FFh
	cli
	out	dx, al
	out	dx, al
	xor	al, al
	out	dx, al
	mov	al, 0FFh
	out	dx, al
	sti

@@set_coords:
	mov	dx, [si+pointnum_t.PN_center_cur.x]
	sar	dx, 4
	; DX = leftmost possible position
	add	dx, (PLAYFIELD_X - (((POINTNUM_DIGITS + 1) * POINTNUM_W) / 2))
	mov	ax, [si+pointnum_t.PN_center_cur.y]
	add	ax, ((PLAYFIELD_Y - (POINTNUM_H / 2)) shl 4)
	call	main_01:scroll_subpixel_y_to_vram_seg1 pascal, ax

	; Loop over the digits to find out how many of them should actually be put
	; on screen. Due to little-endian BCD, the leftmost digit on screen is the
	; rightmost non-zero one in [digits_lebcd]. Starting iteration from the
	; end of the array therefore optimizes for large digit numbers.
	mov	@@digits_to_put, POINTNUM_DIGITS
	add	si, (pointnum_t.PN_digits_lebcd + (POINTNUM_DIGITS - 1))

@@digit_len_loop:
	cmp	byte ptr [si], 0
	jnz	short @@last_digit_found
	add	dx, (POINTNUM_W / 2)	; since X is still center-aligned
	dec	si
	dec	@@digits_to_put
	jnz	short @@digit_len_loop

@@last_digit_found:
	mov	cx, @@digits_to_put
	inc	cx	; Include the trailing 0
	shl	cx, 3	; * POINTNUM_W
	mov	word ptr cs:@@set_width+3, cx

@@digit_loop:
	xor	cx, cx
	mov	cl, [si]
	call	main_01:@pointnum_put
	dec	si
	dec	@@digits_to_put
	jnz	short @@digit_loop

	; Print the trailing 0
	xor	cx, cx
	call	main_01:@pointnum_put

@@si_orig equ <(si - (pointnum_t.PN_digits_lebcd - 1))>
@@set_width:
	mov	[@@si_orig+pointnum_t.PN_width], ((POINTNUM_DIGITS + 1) * POINTNUM_W)
	cmp	[@@si_orig+pointnum_t.PN_times_2], 0
	jz	short @@next
	add	[@@si_orig+pointnum_t.PN_width], POINTNUM_TIMES_2_W
	mov	cx, POINTNUM_TIMES
	call	main_01:@pointnum_put
	mov	cx, POINTNUM_TIMES_2
	call	main_01:@pointnum_put

@@next:
	add	di, word
	mov	si, [di]
	or	si, si
	jnz	short @@number_loop

@@ret:
	pop	di
	pop	si
	pop	bp
	retn
pointnums_render endp
