public CDG_PUT_DISSOLVE_E_8
cdg_put_dissolve_e_8 proc near

@@h       	= word ptr -6
@@w       	= word ptr -4
@@p_offset	= word ptr -2
@@strength	= word ptr  4
@@slot    	= word ptr  6
@@center_y	= word ptr  8
@@center_x	= word ptr  0Ah

	enter	6, 0
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
	sub	[bp+@@center_y], ax
	cmp	byte_10BC7, 0
	jz	short @@put_noalpha
	cmp	byte_10BB5, 0
	jnz	short @@put_alpha

@@put_noalpha:
	call	cdg_put_noalpha_8 pascal, [bp+@@center_x], [bp+@@center_y], [bp+@@slot]
	jmp	short @@dissolve_prepare

@@put_alpha:
	call	cdg_put_8 pascal, [bp+@@center_x], [bp+@@center_y], [bp+@@slot]

@@dissolve_prepare:
	and	[bp+@@strength], 7
	cmp	[bp+@@strength], 0
	jz	short @@ret
	mov	bx, 16
	mov	ax, [bp+@@w]
	cwd
	idiv	bx
	mov	[bp+@@w], ax
	mov	ax, [bp+@@center_y]
	add	[bp+@@h], ax
	mov	ax, [bp+@@center_x]
	sar	ax, 3
	mov	dx, [bp+@@center_y]
	shl	dx, 6
	add	ax, dx
	mov	dx, [bp+@@center_y]
	shl	dx, 4
	add	ax, dx
	mov	[bp+@@p_offset], ax
	mov	ax, 0E000h
	mov	es, ax
	assume es:nothing
	mov	bx, [bp+@@strength]
	shl	bx, 3
	add	bx, offset CDG_DISSOLVE_PATTERN
	mov	dx, [bp+@@center_y]

@@dissolve_next_row:
	mov	si, dx
	; Hack (and si, 3)
	db 081h
	db 0e6h
	db 003h
	db 000h
	shl	si, 1
	mov	ax, [bx+si]
	not	ax
	mov	di, [bp+@@p_offset]
	mov	cx, [bp+@@w]

@@dissolve_apply:
	and	es:[di], ax
	add	di, 2
	loop	@@dissolve_apply
	add	[bp+@@p_offset], (640 / 8)
	inc	dx
	cmp	dx, [bp+@@h]
	jb	short @@dissolve_next_row

@@ret:
	pop	di
	pop	si
	leave
	retn	8
cdg_put_dissolve_e_8 endp
