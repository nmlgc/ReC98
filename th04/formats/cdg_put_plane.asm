; Displays the given [plane] of the CDG image in the given [slot] at (x, y).
; (Unlike other CDG displaying functions, this one actually accepts any value
; for X.) Assumes the GRCG to be set to monochrome mode.
;
; (This is used for the "dissolution effect" in the staff roll, but it
; actually doesn't apply any sort of effect on the pixel data, and relies on
; the individual planes being pre-dissolved.)

; void pascal cdg_put_plane(int x, int y, int slot, int plane)
public cdg_put_plane
cdg_put_plane	proc far

@@plane	= word ptr  6
@@slot 	= word ptr  8
@@y    	= word ptr  0Ah
@@x    	= word ptr  0Ch

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	cx, [bp+@@x]
	mov	di, cx
	sar	di, 4
	shl	di, 1
	add	di, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	ax, [si+CDGSlot.width_divided_by_32]
	shl	ax, 1
	mov	byte ptr cs:@@width_words+1, al
	and	cx, 15
	mov	bx, cx
	shl	bx, 1
	mov	bx, WORD_PUT_PATTERN[bx]
	mov	word ptr cs:@@put_pattern_1+1, bx
	mov	word ptr cs:@@put_pattern_2+1, bx
	jmp	short $+2
	shl	ax, 1
	add	ax, (640 / 8)
	mov	dx, ax
	mov	ax, [bp+@@y]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
	push	ds
	mov	ax, [si+CDGSlot.sgm_colors]
	mov	si, [si+CDGSlot.bitplane_size]
	mov	ds, ax
	mov	ax, [bp+@@plane]
	mov	bp, dx
	mul	si
	mov	si, ax
	cld

@@width_words:
	mov	ch, 80h
	lodsw
	ror	ax, cl
	mov	dx, ax

@@put_pattern_1:
	and	ax, 1234h
	xor	dx, ax
	stosw
	dec	ch

@@blit_word:
	lodsw
	ror	ax, cl
	mov	bx, ax

@@put_pattern_2:
	and	ax, 1234h
	xor	bx, ax
	or	ax, dx
	mov	dx, bx
	stosw
	dec	ch
	jnz	short @@blit_word
	or	dx, dx
	jz	short @@next_row
	mov	es:[di], dx
	xor	dx, dx

@@next_row:
	sub	di, bp
	jns	short @@width_words
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	8
cdg_put_plane	endp
