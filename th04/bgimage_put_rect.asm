public BGIMAGE_PUT_RECT
bgimage_put_rect	proc far

@@h	= word ptr  6
@@w	= word ptr  8
@@y	= word ptr  0Ah
@@x	= word ptr  0Ch

	push	bp
	mov	bp, sp
	push	di
	push	si
	push	ds
	cld
	mov	ax, [bp+@@x]
	mov	dx, [bp+@@y]
	mov	bx, ax
	sar	bx, 4
	shl	bx, 1
	shl	dx, 6
	add	bx, dx
	shr	dx, 2
	add	bx, dx
	mov	word ptr cs:[@@vram_offset], bx
	and	ax, 0Fh
	mov	cx, ax
	add	ax, [bp+@@w]
	shr	ax, 4
	or	cx, cx
	jz	short @@x_on_word_boundary
	inc	ax

@@x_on_word_boundary:
	mov	word ptr cs:[@@width_words], ax
	jmp	short $+2
	mov	cx, (ROW_SIZE / 2)
	sub	cx, ax
	shl	cx, 1
	mov	ax, [bp+@@h]
	mov	bp, cx
	push	0E000h
	push	bgimage_PL_E
	push	0B800h
	push	bgimage_PL_G
	push	0B000h
	push	bgimage_PL_R
	push	0A800h
	push	bgimage_PL_B
	mov	dl, 4

@@next_plane:
	mov	bx, ax

@@vram_offset equ $+1
	mov	di, 1234h
	pop	ds
	assume es:nothing
	pop	es
@@next_row:
@@width_words equ $+1
	mov	cx, 1234h
	mov	si, di
	rep movsw
	add	di, bp
	dec	bx
if GAME eq 5
	jnz	short @@next_row
else
	jns	short @@next_row
endif
	dec	dl
	jnz	short @@next_plane
	pop	ds
	pop	si
	pop	di
	pop	bp
	retf	8
bgimage_put_rect	endp
	even
