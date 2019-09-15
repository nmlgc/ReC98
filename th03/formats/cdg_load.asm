; TH03-specific note: All CDG images loaded by this game are assumed to have
; an alpha plane.

; Loads the [n]th image of the CDG file [fn] into [slot].

; void pascal cdg_load_single_forcealpha(int slot, const char *fn, int n)
cdg_load_single_forcealpha	proc far

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
	push	size CDGSlot
	call	file_read
	mov	ax, [si+CDGSlot.bitplane_size]
	imul	ax, 5
	movzx	eax, ax
	mov	[bp+@@image_size], eax
	movsx	eax, [bp+@@n]
	imul	eax, [bp+@@image_size]
	push	eax
	push	1
	call	file_seek
	push	[si+CDGSlot.bitplane_size]
	call	hmem_allocbyte
	mov	[si+CDGSlot.sgm_alpha], ax
	push	[si+CDGSlot.sgm_alpha]
	push	0
	push	[si+CDGSlot.bitplane_size]
	call	file_read
	mov	ax, [si+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[si+CDGSlot.sgm_colors], ax
	push	[si+CDGSlot.sgm_colors]
	push	0
	mov	ax, [si+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	file_read
	call	file_close
	pop	di
	pop	si
	leave
	retf	8
cdg_load_single_forcealpha	endp


; Loads the [n]th image of the CDG file [fn] into [slot], skipping the alpha
; plane.

; void pascal cdg_load_single_noalpha(int slot, const char *fn, int n)
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
	push	size CDGSlot
	call	file_read
	mov	ax, [si+CDGSlot.bitplane_size]
	imul	ax, 5
	movzx	eax, ax
	mov	[bp+@@image_size], eax
	movsx	eax, [bp+@@n]
	imul	eax, [bp+@@image_size]
	push	eax
	push	1
	call	file_seek
	movzx	eax, [si+CDGSlot.bitplane_size]
	push	eax
	push	1
	call	file_seek
	mov	[si+CDGSlot.sgm_alpha], 0
	mov	ax, [si+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[si+CDGSlot.sgm_colors], ax
	push	[si+CDGSlot.sgm_colors]
	push	0
	mov	ax, [si+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	file_read
	call	file_close
	pop	di
	pop	si
	leave
	retf	8
cdg_load_single_noalpha	endp


; Loads all images of the CDG file [fn], starting at [slot_first] and
; incrementing the slot number for every further image.

; void pascal cdg_load_all(int slot_first, const char *fn);
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
	push	size CDGSlot
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
	mov	al, [di+CDGSlot.num_images]
	mov	ah, 0
	cmp	ax, [bp+@@i]
	jg	short @@free
	mov	[bp+@@i], 0
	jmp	short @@load_loop

@@copy_header:
	mov	ax, [di+CDGSlot.bitplane_size]
	mov	[si+CDGSlot.bitplane_size], ax
	mov	ax, [di+CDGSlot.pixel_width]
	mov	[si+CDGSlot.pixel_width], ax
	mov	ax, [di+CDGSlot.pixel_height]
	mov	[si+CDGSlot.pixel_height], ax
	mov	ax, [di+CDGSlot.vram_byte_at_bottom_left]
	mov	[si+CDGSlot.vram_byte_at_bottom_left], ax
	mov	ax, [di+CDGSlot.width_divided_by_32]
	mov	[si+CDGSlot.width_divided_by_32], ax
	mov	al, [di+CDGSlot.num_images]
	mov	[si+CDGSlot.num_images], al
	mov	[si+CDGSlot.alpha], 0
	cmp	cdg_noalpha, 0
	jnz	short @@noalpha
	push	[si+CDGSlot.bitplane_size]
	call	hmem_allocbyte
	mov	[si+CDGSlot.sgm_alpha], ax
	push	[si+CDGSlot.sgm_alpha]
	push	0
	push	[si+CDGSlot.bitplane_size]
	call	file_read
	jmp	short @@alpha

@@noalpha:
	mov	[si+CDGSlot.sgm_alpha], 0
	movzx	eax, [si+CDGSlot.bitplane_size]
	push	eax
	push	1
	call	file_seek

@@alpha:
	mov	ax, [si+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[si+CDGSlot.sgm_colors], ax
	push	[si+CDGSlot.sgm_colors]
	push	0
	mov	ax, [si+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	file_read
	inc	[bp+@@i]
	add	si, size CDGSlot

@@load_loop:
	mov	al, [di+CDGSlot.num_images]
	mov	ah, 0
	cmp	ax, [bp+@@i]
	jg	@@copy_header
	call	file_close
	pop	di
	pop	si
	leave
	retf	6
cdg_load_all	endp


; Loads all images of the CDG file [fn], disregarding their alpha planes,
; starting at [slot_first] and incrementing the slot number for every further
; image.

; void pascal cdg_load_all_noalpha(int slot_first, const char *fn);
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


; Frees the CDG image in the given [slot].

; void cdg_free(int slot);
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
