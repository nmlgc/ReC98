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
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	ax, [bp+@@left]
	sar	ax, 3
	add	ax, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	di, ax
	mov	ax, [si+CDGSlot.width_divided_by_32]
	mov	word ptr cs:@@width+1,	ax
	jmp	short $+2
	shl	ax, 2
	add	ax, (640 / 8)
	mov	dx, ax
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
	push	ds
	mov	ax, [si+CDGSlot.sgm_colors]
	mov	ds, ax
	xor	si, si
	mov	bx, di
	cld
	nop

@@width:
	mov	cx, 1234h
	rep movsd
	sub	di, dx
	jns	short @@width
	mov	di, bx
	mov	ax, es
	add	ax, 800h
	mov	es, ax
	assume es:nothing
	cmp	ax, 0C000h
	jb	short @@width
	cmp	ax, 0C800h
	jnb	short @@ret
	add	ax, 2000h
	mov	es, ax
	assume es:nothing
	jmp	short @@width

@@ret:
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_noalpha	endp
	align	2
