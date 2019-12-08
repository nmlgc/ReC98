public BGIMAGE_SNAP
bgimage_snap	proc far
	push	si
	push	di
	cmp	bgimage_PL_B, 0
	jnz	short @@already_allocated
	call	hmem_allocbyte pascal, (ROW_SIZE * RES_Y)
	mov	bgimage_PL_B, ax
	call	hmem_allocbyte pascal, (ROW_SIZE * RES_Y)
	mov	bgimage_PL_R, ax
	call	hmem_allocbyte pascal, (ROW_SIZE * RES_Y)
	mov	bgimage_PL_G, ax
	call	hmem_allocbyte pascal, (ROW_SIZE * RES_Y)
	mov	bgimage_PL_E, ax

@@already_allocated:
	mov	dl, 4
	push	ds
	push	0E000h
	push	bgimage_PL_E
	push	0B800h
	push	bgimage_PL_G
	push	0B000h
	push	bgimage_PL_R
	push	0A800h
	push	bgimage_PL_B

@@next_plane:
	pop	es
	pop	ds
	xor	si, si
	xor	di, di
	mov	cx, (ROW_SIZE * RES_Y) / 4
	rep movsd
	dec	dl
	jnz	short @@next_plane
	pop	ds
	pop	di
	pop	si
	retf
bgimage_snap	endp


public BGIMAGE_PUT
bgimage_put	proc far
	push	si
	push	di
	mov	dl, 4
	push	ds
	push	0E000h
	push	bgimage_PL_E
	push	0B800h
	push	bgimage_PL_G
	push	0B000h
	push	bgimage_PL_R
	push	0A800h
	push	bgimage_PL_B

@@next_plane:
	pop	ds
	pop	es
	xor	si, si
	xor	di, di
	mov	cx, (ROW_SIZE * RES_Y) / 4
	rep movsd
	dec	dl
	jnz	short @@next_plane
	pop	ds
	pop	di
	pop	si
	retf
bgimage_put	endp
	even


public BGIMAGE_FREE
bgimage_free	proc far
	cmp	bgimage_PL_B, 0
	jz	short @@ret
	call	hmem_free pascal, bgimage_PL_B
	call	hmem_free pascal, bgimage_PL_R
	call	hmem_free pascal, bgimage_PL_G
	call	hmem_free pascal, bgimage_PL_E
	mov	bgimage_PL_B, 0

@@ret:
	retf
bgimage_free	endp
