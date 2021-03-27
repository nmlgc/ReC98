public CDG_PUT_8
cdg_put_8 proc far

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0

	cdg_slot_offset	si, [bp+@@slot]

	mov	ax, [si+cdg_t.seg_colors]
	mov	word ptr cs:@@seg_colors+1, ax

	cdg_dst_offset	ax, si, [bp+@@left]

	mov	di, ax
	mov	word ptr cs:@@offset_at_bottom_left+1, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	word ptr cs:@@width_1+1, ax
	mov	word ptr cs:@@width_2+1, ax
	shl	ax, 2
	add	ax, (640 / 8)
	mov	word ptr cs:@@stride+1, ax
	jmp	short $+2

	cdg_dst_segment	es, [bp+@@top], bx

	push	ds
	mov	ax, [si+cdg_t.seg_alpha]
	mov	ds, ax
	xor	si, si

@@stride:
	mov	dx, 1234h
	cld

@@width_1:
	mov	cx, 1234h
	rep movsd
	sub	di, dx
	jns	short @@width_1
	xor	al, al
	out	7Ch, al

@@offset_at_bottom_left:
	mov	bx, 1234h
	mov	di, bx
	xor	si, si

@@seg_colors:
	mov	ax, 1234h
	mov	ds, ax
	assume ds:nothing

@@row_loop:
@@width_2:
	mov	cx, 1234h

@@blit_dword:
	mov	eax, [si]
	or	es:[di], eax
	add	si, 4
	add	di, 4
	loop	@@blit_dword
	sub	di, dx
	jns	short @@row_loop
	mov	di, bx
	vram_plane_next es, @@row_loop

@@ret:
	pop	ds
	assume ds:_DATA
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_8 endp
	align 2
