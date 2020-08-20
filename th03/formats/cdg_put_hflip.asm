; Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top), flipped
; horizontally.

; void DEFCONV cdg_put_hflip(screen_x_t left, vram_y_t top, int slot);
proc_defconv cdg_put_hflip

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	ax, [bp+@@left]
	sar	ax, 3
	add	ax, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	bx, [si+CDGSlot.width_divided_by_32]
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
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
	assume es:nothing
	mov	bx, offset hflip_lut
	mov	fs, [si+CDGSlot.sgm_alpha]
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
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	fs, [si+CDGSlot.sgm_colors]
	xor	si, si

@@stride_colors:
	mov	dx, 1234h
	nop

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
	jns	short @@width_bytes_colors

@@last_x_colors:
	mov	di, 1234h
	mov	ax, es
	add	ax, 800h
	mov	es, ax
	assume es:nothing
	cmp	ax, 0C000h
	jb	short @@width_bytes_colors
	cmp	ax, 0C800h
	jnb	short @@ret
	add	ax, 2000h
	mov	es, ax
	assume es:nothing
	jmp	short @@width_bytes_colors

@@ret:
	pop	di
	pop	si
	pop	bp
	retf	6
endp_defconv
	align 2
