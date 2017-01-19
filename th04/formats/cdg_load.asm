; Loads the [n]th image of the CDG file [fn] into [slot].

; void pascal cdg_load_single_noalpha(int slot, const char *fn, int n);
; void pascal cdg_load_single(int slot, const char *fn, int n);
public _cdg_load_single_noalpha
public _cdg_load_single

_cdg_load_single_noalpha	label proc
	mov	cdg_noalpha, 1
	align	2

_cdg_load_single	proc far

@@n   	=  word ptr  6
@@fn  	= dword	ptr  8
@@slot	=  word ptr  12

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, [bp+@@slot]
	push	di
	nopcall	_cdg_free
	shl	di, 4
	add	di, offset _cdg_slots
	pushd	[bp+@@fn]
	call	file_ropen
	push	ds
	push	di
	push	size CDGSlot
	call	file_read
	mov	ax, [di+CDGSlot.bitplane_size]
	mov	dx, ax
	cmp	[di+CDGSlot.alpha], 0
	jz	short @@read
	shl	ax, 2
	cmp	[di+CDGSlot.alpha], 2
	jz	short @@read
	add	ax, dx

@@read:
	mul	[bp+@@n]
	movzx	eax, ax
	push	eax
	push	1
	call	file_seek
	call	_cdg_read_single
	call	file_close
	mov	cdg_noalpha, 0
	pop	di
	pop	si
	pop	bp
	retf	8
_cdg_load_single	endp
	align	2

; Reads a single CDG image from the master.lib file, which previously has been
; positioned at the beginning of the image data, into the slot in DI.
_cdg_read_single	proc near
	mov	al, [di+CDGSlot.alpha]
	or	al, al
	jz	short @@colors
	cmp	al, 2
	jz	short @@alpha
	cmp	cdg_noalpha, 0
	jnz	short @@skip_alpha

@@alpha:
	push	[di+CDGSlot.bitplane_size]
	call	hmem_allocbyte
	mov	[di+CDGSlot.sgm_alpha], ax
	push	ax
	push	0
	push	[di+CDGSlot.bitplane_size]
	call	file_read
	jmp	short @@colors

@@skip_alpha:
	movzx	eax, [di+CDGSlot.bitplane_size]
	push	eax
	push	1
	call	file_seek

@@colors:
	cmp	[di+CDGSlot.alpha], 2
	jz	short @@ret
	mov	ax, [di+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	hmem_allocbyte
	mov	[di+CDGSlot.sgm_colors], ax
	push	ax
	push	0
	mov	ax, [di+CDGSlot.bitplane_size]
	shl	ax, 2
	push	ax
	call	file_read

@@ret:
	retn
_cdg_read_single	endp


; Loads all images of the CDG file [fn], starting at [slot_first] and
; incrementing the slot number for every further image.

; void pascal _cdg_load_all_noalpha(int slot, const char *fn);
; void pascal _cdg_load_all(int slot, const char *fn);
public _cdg_load_all_noalpha
public _cdg_load_all

_cdg_load_all_noalpha	label proc
	mov	cdg_noalpha, 1
	align	2

_cdg_load_all	proc far

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
	push	size CDGSlot
	call	file_read
	mov	si, di
	mov	bp, [bp+@@slot_first]
	mov	al, CDGSlot.num_images[si]
	mov	cdg_images_to_load, al
	push	ds
	pop	es
	assume es:_DATA

@@loop:
	push	bp
	call	_cdg_free
	mov	cx, 3
	rep movsd
	sub	si, CDGSlot.sgm_alpha
	sub	di, CDGSlot.sgm_alpha
	call	_cdg_read_single
	inc	bp
	add	di, size CDGSlot
	dec	cdg_images_to_load
	jnz	short @@loop
	call	file_close
	mov	cdg_noalpha, 0
	pop	di
	pop	si
	pop	bp
	retf	6
_cdg_load_all	endp


; Frees the CDG image in the given [slot].

; void _cdg_free(int slot);
public _cdg_free
_cdg_free	proc far
	mov	bx, sp
	push	di
	mov	di, ss:[bx+4]
	shl	di, 4
	add	di, offset _cdg_slots.sgm_alpha
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
_cdg_free	endp
	align 2


; Frees the CDG images in all slots.

; void _cdg_freeall();
public _cdg_freeall
_cdg_freeall	proc far
	push	si
	mov	si, CDG_SLOT_COUNT - 1

@@loop:
	call	_cdg_free pascal, si
	dec	si
	jge	short @@loop
	pop	si
	retf
_cdg_freeall	endp
