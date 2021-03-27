public CDG_PUT_HFLIP_8
cdg_put_hflip_8 proc

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0

	cdg_slot_offset	si, [bp+@@slot]
	cdg_dst_offset	ax, si, [bp+@@left]

	mov	bx, [si+cdg_t.vram_dword_w]
	shl	bx, 2
	add	ax, bx
	dec	ax
	mov	di, ax
	mov	word ptr cs:@@last_x_alpha+1, ax
	mov	word ptr cs:@@last_x_colors+1, ax
	mov	word ptr cs:@@width_bytes_alpha+1, bx
	mov	word ptr cs:@@width_bytes_colors+1, bx
	mov	ax, (640 / 8)
	sub	ax, bx
	mov	word ptr cs:@@stride_alpha+1, ax
	mov	word ptr cs:@@stride_colors+1, ax
	jmp	short $+2

	cdg_dst_segment es, [bp+@@top], bx

	mov	bx, offset _hflip_lut
	mov	fs, [si+cdg_t.seg_alpha]
	xor	si, si

@@stride_alpha:
	mov	dx, 1234h
	nop

@@width_bytes_alpha:
	mov	cx, 1234h

@@blit_hflip_alpha:
	mov	al, fs:[si]
	xlat
	mov	es:[di], al
	inc	si
	dec	di
	loop	@@blit_hflip_alpha
	sub	di, dx
	jns	short @@width_bytes_alpha
	xor	al, al
	out	7Ch, al

@@last_x_alpha:
	mov	di, 1234h

	cdg_slot_offset	si, [bp+@@slot]

	mov	fs, [si+cdg_t.seg_colors]
	xor	si, si

@@stride_colors:
	mov	dx, 1234h
	nop

@@row_loop:
@@width_bytes_colors:
	mov	cx, 1234

@@blit_hflip_colors:
	mov	al, fs:[si]
	xlat
	or	es:[di], al
	inc	si
	dec	di
	loop	@@blit_hflip_colors
	sub	di, dx
	jns	short @@row_loop

@@last_x_colors:
	mov	di, 1234h
	vram_plane_next es, @@row_loop

@@ret:
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_hflip_8 endp
	align 2
