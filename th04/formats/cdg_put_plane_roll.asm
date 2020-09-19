public CDG_PUT_PLANE_ROLL_8
cdg_put_plane_roll_8 proc far

@@plane_dst	= word ptr [bp+6]
@@plane_src	= word ptr [bp+8]
@@slot     	= word ptr [bp+10]
@@top      	= word ptr [bp+12]
@@left     	= word ptr [bp+14]

@@stride_backwards equ dx
@@h equ bx

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	ax, @@plane_dst
	mov	es, ax
	mov	si, @@slot
	shl	si, 4
	add	si, offset _cdg_slots
	mov	di, @@left
	sar	di, 3
	mov	@@h, [si+cdg_t.pixel_h]
	mov	ax, @@top
	add	ax, @@h
	dec	ax
	shl	ax, 6
	add	di, ax
	shr	ax, 2
	add	di, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	word ptr cs:@@width_dwords, ax
	jmp	short $+2
	shl	ax, 2
	add	ax, ROW_SIZE
	mov	@@stride_backwards, ax
	push	ds
	mov	ax, [si+cdg_t.seg_colors]
	mov	si, [si+cdg_t.CDG_plane_size]
	mov	ds, ax
	mov	cx, @@plane_src
	inc	cx
	mov	ax, si
	neg	si

@@plane_src_num_to_offset:
	add	si, ax
	loop	@@plane_src_num_to_offset
	cmp	di, PLANE_SIZE
	jb	short @@start_blitting
	sub	di, PLANE_SIZE

@@start_blitting:
	cld
	nop

@@next_row:
@@width_dwords equ $+1
	mov	cx, 1234h

@@blit_dword:
	mov	eax, [si]
	or	es:[di], eax
	add	si, 4
	add	di, 4
	loop	@@blit_dword
	sub	di, @@stride_backwards
	jge	short @@more_rows?
	add	di, PLANE_SIZE

@@more_rows?:
	dec	@@h
	jnz	short @@next_row
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	0Ah
cdg_put_plane_roll_8 endp
