; Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top),
; disregarding its color planes.

; void pascal cdg_put_nocolors(screen_x_t left, vram_y_t top, int slot);
public CDG_PUT_NOCOLORS
cdg_put_nocolors	proc far

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
	mov	di, [bp+@@left]
	sar	di, 3
	add	di, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	ax, [si+CDGSlot.width_divided_by_32]
if GAME eq 4
	mov	word ptr cs:@@width+1, ax
	jmp	short $+2
else
	mov	bx, ax
endif
	shl	ax, 2
	add	ax, (640 / 8)
	mov	dx, ax
	mov	ax, [bp+@@top]
if GAME eq 4
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
else
	mov	cx, ax
	shl	ax, 2
	add	ax, cx
endif
	add	ax, 0A800h
	mov	es, ax
	push	ds
	mov	ds, [si+CDGSlot.sgm_alpha]
	xor	si, si
if GAME eq 4
	cld
endif
	align 2

@@width:
if GAME eq 4
	mov	cx, 1234h
else
	mov	cx, bx
endif
	rep movsd
	sub	di, dx
	jns	short @@width
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_nocolors	endp
	align 2
