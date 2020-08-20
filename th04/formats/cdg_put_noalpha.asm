; Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top),
; disregarding its alpha plane.

; void pascal cdg_put_noalpha(screen_x_t left, vram_y_t top, int slot);
public CDG_PUT_NOALPHA
cdg_put_noalpha	proc far

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	push	ds
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
	add	ax, 3800h
	push	ax
	sub	ax, 2800h
	push	ax
	sub	ax, 800h
	push	ax
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	bx, [bp+@@left]
	sar	bx, 3
	add	bx, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	ax, [si+CDGSlot.width_divided_by_32]
	mov	bp, ax
	shl	ax, 2
	add	ax, (640 / 8)
	mov	dx, ax
	mov	ax, [si+CDGSlot.sgm_colors]
	mov	ds, ax
	xor	si, si
	mov	al, 4
	cld
	nop

@@plane:
	mov	di, bx

@@row:
	mov	cx, bp
	rep movsd
	sub	di, dx
	jns	short @@row
	dec	al
	jz	short @@ret
	pop	es
	jmp	short @@plane

@@ret:
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_noalpha	endp
	align 2
