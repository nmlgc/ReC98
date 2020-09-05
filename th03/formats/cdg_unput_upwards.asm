; Assuming that the CDG image in the given [slot] was previously displayed
; centered at (⌊center_x/8⌋*8, center_y), this function clears the two lines
; at the bottom of that image, as well as the one line immediately below, from
; the VRAM's E plane.

; void cdg_unput_for_upwards_motion_e(screen_x_t center_x, vram_y_t center_y, int slot);
public CDG_UNPUT_FOR_UPWARDS_MOTION_E
cdg_unput_for_upwards_motion_e	proc near

@@h	      	= word ptr -4
@@w       	= word ptr -2
@@slot    	= word ptr  4
@@center_y	= word ptr  6
@@center_x	= word ptr  8

	enter	4, 0
	push	si
	push	di
	mov	bx, [bp+@@slot]
	shl	bx, 4
	mov	ax, _cdg_slots.pixel_w[bx]
	mov	[bp+@@w], ax
	mov	bx, [bp+@@slot]
	shl	bx, 4
	mov	ax, _cdg_slots.pixel_h[bx]
	mov	[bp+@@h], ax
	mov	ax, [bp+@@w]
	cwd
	sub	ax, dx
	sar	ax, 1
	sub	[bp+@@center_x], ax
	mov	ax, [bp+@@h]
	cwd
	sub	ax, dx
	sar	ax, 1
	add	ax, -2
	add	[bp+@@center_y], ax
	mov	ax, [bp+@@center_x]
	sar	ax, 3
	mov	dx, [bp+@@center_y]
	shl	dx, 6
	add	ax, dx
	mov	dx, [bp+@@center_y]
	shl	dx, 4
	add	ax, dx
	mov	di, ax
	mov	ax, 0E000h
	mov	es, ax
	assume es:nothing
	mov	dx, [bp+@@w]
	shr	dx, 4
	mov	si, (640 / 8)
	sub	si, dx
	sub	si, dx
	xor	ax, ax
	mov	cx, dx
	rep stosw
	add	di, si
	mov	cx, dx
	rep stosw
	add	di, si
	mov	cx, dx
	rep stosw
	pop	di
	pop	si
	leave
	retn	6
cdg_unput_for_upwards_motion_e	endp
