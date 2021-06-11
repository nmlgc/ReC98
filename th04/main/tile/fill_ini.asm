public TILES_FILL_INITIAL
tiles_fill_initial	proc near

@@section	equ <bx>
@@std_seg	equ <fs>

	push	di
	push	si
	push	ds
if GAME eq 5
	mov	@@section, _tile_section_ptr
	sub	@@section, (TILE_ROWS_PER_SECTION - 1)
else
	xor	@@section, @@section
endif
	mov	di, offset _tile_ring
	add	di, TILES_MEMORY_X * (TILES_Y - 1) * word
	xor	dx, dx
	mov	ax, ds
	mov	es, ax
	assume es:_DATA
	mov	ax, _std_seg
	mov	@@std_seg, ax
	mov	ax, map_seg
	mov	ds, ax
	mov	al, (TILES_Y / TILE_ROWS_PER_SECTION)

@@section_in_screen_loop:
	xor	dx, dx
	mov	dl, @@std_seg:[@@section]
	mov	si, dx
	if GAME ne 5
		; Since TILE_SECTION_OFFSETS is a 16-bit array, we have to double the
		; section ID read from the .STD …except that in TH05's version of the
		; format, we don't, and simply assume that the .STD file's section IDs
		; already come pre-multiplied by the element size of the lookup table.
		; Way to go. Making the format more annoying just to save a single
		; instruction for a table lookup that is pointless to begin with.
		add	si, si
	endif
	mov	si, es:_TILE_SECTION_OFFSETS[si]
	add	si, ((TILE_ROWS_PER_SECTION - 1) * TILES_MEMORY_X * word)
	mov	ah, TILE_ROWS_PER_SECTION

@@row_in_section_loop:
	mov	cx, (TILES_X / 2)
	rep movsd
	sub	di, ((TILES_MEMORY_X + TILES_X) * word)
	sub	si, ((TILES_MEMORY_X + TILES_X) * word)
	dec	ah
	jnz	short @@row_in_section_loop
	inc	@@section
	dec	al
	jnz	short @@section_in_screen_loop
	pop	ds
	pop	si
	pop	di
	retn
tiles_fill_initial	endp
	even
