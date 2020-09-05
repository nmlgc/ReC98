public CDG_LOAD_SINGLE_NOALPHA
public CDG_LOAD_SINGLE

cdg_load_single_noalpha	label proc
	mov	cdg_noalpha, 1
	align	2

cdg_load_single	proc far

@@n   	=  word ptr  6
@@fn  	= dword	ptr  8
@@slot	=  word ptr  12

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, [bp+@@slot]
	push	di
	nopcall	cdg_free
	shl	di, 4
	add	di, offset _cdg_slots
	pushd	[bp+@@fn]
	call	file_ropen
	push	ds
	push	di
	push	size cdg_t
	call	file_read
	mov	ax, [di+cdg_t.CDG_plane_size]
	mov	dx, ax
	cmp	[di+cdg_t.plane_layout], CDG_COLORS
	jz	short @@read
	shl	ax, 2
	cmp	[di+cdg_t.plane_layout], CDG_ALPHA
	jz	short @@read
	add	ax, dx

@@read:
	mul	[bp+@@n]
	movzx	eax, ax
	push	eax
	push	1
	call	file_seek
	call	cdg_read_single
	call	file_close
	mov	cdg_noalpha, 0
	pop	di
	pop	si
	pop	bp
	retf	8
cdg_load_single	endp
	align	2

; Reads a single CDG image from the master.lib file, which previously has been
; positioned at the beginning of the image data, into the slot in DI.
cdg_read_single	proc near
	mov	al, [di+cdg_t.plane_layout]
	or	al, al	; AL == CDG_COLORS?
	jz	short @@colors
	cmp	al, CDG_ALPHA
	jz	short @@alpha
	cmp	cdg_noalpha, 0
	jnz	short @@skip_alpha

@@alpha:
	push	[di+cdg_t.CDG_plane_size]
	call	hmem_allocbyte
	mov	[di+cdg_t.seg_alpha], ax
	push	ax
	push	0
	push	[di+cdg_t.CDG_plane_size]
	call	file_read
	jmp	short @@colors

@@skip_alpha:
	movzx	eax, [di+cdg_t.CDG_plane_size]
	push	eax
	push	1
	call	file_seek

@@colors:
	cmp	[di+cdg_t.plane_layout], CDG_ALPHA
	jz	short @@ret
	mov	ax, [di+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[di+cdg_t.seg_colors], ax
	push	ax
	push	0
	mov	ax, [di+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	file_read

@@ret:
	retn
cdg_read_single	endp


public CDG_LOAD_ALL_NOALPHA
public CDG_LOAD_ALL

cdg_load_all_noalpha	label proc
	mov	cdg_noalpha, 1
	align	2

cdg_load_all	proc far

@@fn        	= dword	ptr  6
@@slot_first	=  word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	pushd	[bp+@@fn]
	call	file_ropen
	mov	di, [bp+@@slot_first]
	shl	di, 4
	add	di, offset _cdg_slots
	push	ds
	push	di
	push	size cdg_t
	call	file_read
	mov	si, di
	mov	bp, [bp+@@slot_first]
	mov	al, cdg_t.image_count[si]
	mov	cdg_images_to_load, al
	push	ds
	pop	es
	assume es:_DATA

@@loop:
	push	bp
	call	cdg_free
	mov	cx, 3
	rep movsd
	sub	si, cdg_t.seg_alpha
	sub	di, cdg_t.seg_alpha
	call	cdg_read_single
	inc	bp
	add	di, size cdg_t
	dec	cdg_images_to_load
	jnz	short @@loop
	call	file_close
	mov	cdg_noalpha, 0
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_load_all	endp


public CDG_FREE
cdg_free	proc far
	mov	bx, sp
	push	di
	mov	di, ss:[bx+4]
	shl	di, 4
	add	di, offset _cdg_slots.seg_alpha
	cmp	word ptr [di], 0
	jz	short @@colors
	push	word ptr [di]
	call	hmem_free
	mov	word ptr [di], 0

@@colors:
	add	di, 2
	cmp	word ptr [di], 0
	jz	short @@ret
	push	word ptr [di]
	call	hmem_free
	mov	word ptr [di], 0

@@ret:
	pop	di
	retf	2
cdg_free	endp
	align 2


public CDG_FREE_ALL
cdg_free_all	proc far
	push	si
	mov	si, CDG_SLOT_COUNT - 1

@@loop:
	call	cdg_free pascal, si
	dec	si
	jge	short @@loop
	pop	si
	retf
cdg_free_all	endp
