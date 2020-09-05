public CDG_LOAD_SINGLE
cdg_load_single	proc far

@@image_size	= dword	ptr -4
@@n         	=  word ptr  6
@@fn        	= dword	ptr  8
@@slot      	=  word ptr  12

	enter	4, 0
	push	si
	push	di
	mov	di, [bp+@@slot]
	push	di
	nopcall	cdg_free
	mov	ax, di
	shl	ax, 4
	add	ax, offset _cdg_slots
	mov	si, ax
	pushd	[bp+@@fn]
	call	file_ropen
	push	ds
	push	si
	push	size cdg_t
	call	file_read
	mov	ax, [si+cdg_t.CDG_plane_size]
	imul	ax, 5
	movzx	eax, ax
	mov	[bp+@@image_size], eax
	movsx	eax, [bp+@@n]
	imul	eax, [bp+@@image_size]
	push	eax
	push	1
	call	file_seek
	push	[si+cdg_t.CDG_plane_size]
	call	hmem_allocbyte
	mov	[si+cdg_t.seg_alpha], ax
	push	[si+cdg_t.seg_alpha]
	push	0
	push	[si+cdg_t.CDG_plane_size]
	call	file_read
	mov	ax, [si+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[si+cdg_t.seg_colors], ax
	push	[si+cdg_t.seg_colors]
	push	0
	mov	ax, [si+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	file_read
	call	file_close
	pop	di
	pop	si
	leave
	retf	8
cdg_load_single	endp


public CDG_LOAD_SINGLE_NOALPHA
cdg_load_single_noalpha	proc far

@@image_size	= dword	ptr -4
@@n         	=  word ptr  6
@@fn        	= dword	ptr  8
@@slot      	=  word ptr  12

	enter	4, 0
	push	si
	push	di
	mov	di, [bp+@@slot]
	push	di
	nopcall	cdg_free
	mov	ax, di
	shl	ax, 4
	add	ax, offset _cdg_slots
	mov	si, ax
	pushd	[bp+@@fn]
	call	file_ropen
	push	ds
	push	si
	push	size cdg_t
	call	file_read
	mov	ax, [si+cdg_t.CDG_plane_size]
	imul	ax, 5
	movzx	eax, ax
	mov	[bp+@@image_size], eax
	movsx	eax, [bp+@@n]
	imul	eax, [bp+@@image_size]
	push	eax
	push	1
	call	file_seek
	movzx	eax, [si+cdg_t.CDG_plane_size]
	push	eax
	push	1
	call	file_seek
	mov	[si+cdg_t.seg_alpha], 0
	mov	ax, [si+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[si+cdg_t.seg_colors], ax
	push	[si+cdg_t.seg_colors]
	push	0
	mov	ax, [si+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	file_read
	call	file_close
	pop	di
	pop	si
	leave
	retf	8
cdg_load_single_noalpha	endp


public CDG_LOAD_ALL
cdg_load_all	proc far

@@i         	=  word ptr -2
@@fn        	= dword	ptr  6
@@slot_first	=  word ptr  10

	enter	2, 0
	push	si
	push	di
	pushd	[bp+@@fn]
	call	file_ropen
	push	[bp+@@slot_first]
	nopcall	cdg_free
	mov	ax, [bp+@@slot_first]
	shl	ax, 4
	add	ax, offset _cdg_slots
	mov	si, ax
	push	ds
	push	ax
	push	size cdg_t
	call	file_read
	mov	di, si
	mov	[bp+@@i], 1
	jmp	short @@free_loop

@@free:
	mov	ax, [bp+@@slot_first]
	add	ax, [bp+@@i]
	push	ax
	nopcall	cdg_free
	inc	[bp+@@i]

@@free_loop:
	mov	al, [di+cdg_t.image_count]
	mov	ah, 0
	cmp	ax, [bp+@@i]
	jg	short @@free
	mov	[bp+@@i], 0
	jmp	short @@load_loop

@@copy_header:
	mov	ax, [di+cdg_t.CDG_plane_size]
	mov	[si+cdg_t.CDG_plane_size], ax
	mov	ax, [di+cdg_t.pixel_w]
	mov	[si+cdg_t.pixel_w], ax
	mov	ax, [di+cdg_t.pixel_h]
	mov	[si+cdg_t.pixel_h], ax
	mov	ax, [di+cdg_t.offset_at_bottom_left]
	mov	[si+cdg_t.offset_at_bottom_left], ax
	mov	ax, [di+cdg_t.vram_dword_w]
	mov	[si+cdg_t.vram_dword_w], ax
	mov	al, [di+cdg_t.image_count]
	mov	[si+cdg_t.image_count], al
	mov	[si+cdg_t.plane_layout], CDG_COLORS_AND_ALPHA
	cmp	cdg_noalpha, 0
	jnz	short @@noalpha
	push	[si+cdg_t.CDG_plane_size]
	call	hmem_allocbyte
	mov	[si+cdg_t.seg_alpha], ax
	push	[si+cdg_t.seg_alpha]
	push	0
	push	[si+cdg_t.CDG_plane_size]
	call	file_read
	jmp	short @@alpha

@@noalpha:
	mov	[si+cdg_t.seg_alpha], 0
	movzx	eax, [si+cdg_t.CDG_plane_size]
	push	eax
	push	1
	call	file_seek

@@alpha:
	mov	ax, [si+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[si+cdg_t.seg_colors], ax
	push	[si+cdg_t.seg_colors]
	push	0
	mov	ax, [si+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	file_read
	inc	[bp+@@i]
	add	si, size cdg_t

@@load_loop:
	mov	al, [di+cdg_t.image_count]
	mov	ah, 0
	cmp	ax, [bp+@@i]
	jg	@@copy_header
	call	file_close
	pop	di
	pop	si
	leave
	retf	6
cdg_load_all	endp


public CDG_LOAD_ALL_NOALPHA
cdg_load_all_noalpha	proc far

@@fn        	= dword	ptr  6
@@slot_first	=  word ptr  10

	push	bp
	mov	bp, sp
	mov	cdg_noalpha, 1
	push	[bp+@@slot_first]
	pushd	[bp+@@fn]
	call	cdg_load_all
	mov	cdg_noalpha, 0
	pop	bp
	retf	6
cdg_load_all_noalpha	endp


public CDG_FREE
cdg_free	proc far

@@slot		= word ptr  6

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	ax, [bp+@@slot]
	shl	ax, 4
	add	ax, offset _cdg_slots
	mov	di, ax
	xor	si, si
	jmp	short @@sgm_loop

@@free:
	mov	bx, si
	add	bx, bx
	cmp	word ptr [bx+di+0Ch], 0
	jz	short @@next_sgm
	mov	bx, si
	add	bx, bx
	push	word ptr [bx+di+0Ch]
	call	hmem_free
	mov	bx, si
	add	bx, bx
	mov	word ptr [bx+di+0Ch], 0

@@next_sgm:
	inc	si

@@sgm_loop:
	cmp	si, 2
	jl	short @@free
	pop	di
	pop	si
	pop	bp
	retf	2
cdg_free	endp
