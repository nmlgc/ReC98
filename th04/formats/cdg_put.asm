; Displays the CDG image in the given [slot] at (⌊x/8⌋*8, y).

; void pascal cdg_put(int x, int y, int slot);
public CDG_PUT
cdg_put	proc far

@@slot	= word ptr  6
@@y   	= word ptr  8
@@x   	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	push	ds
	cli
	mov	al, GC_RMW
	out	7Ch, al
	mov	dx, 7Eh
	xor	al, al
	out	dx, al
	out	dx, al
	out	dx, al
	out	dx, al
	sti
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
if GAME eq 4
	mov	ax, [si+CDGSlot.sgm_colors]
	mov	word ptr cs:@@sgm_colors+1, ax
	jmp	short $+2
	mov	ax, [bp+@@y]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
else
	mov	ax, [bp+@@y]
	shl	ax, 2
	add	ax, [bp+@@y]
endif
	add	ax, 0A800h
	mov	es, ax
	assume es:nothing
	push	0
	add	ax, 3800h
	push	ax
	sub	ax, 2800h
	push	ax
	sub	ax, 800h
	push	ax
	mov	ax, [bp+@@x]
	shr	ax, 3
	add	ax, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	di, ax
	mov	bx, ax
	mov	ax, [si+CDGSlot.width_divided_by_32]
	mov	bp, ax
	shl	ax, 2
	add	ax, (640 / 8)
	mov	dx, ax
if GAME eq 4
	mov	ax, [si+CDGSlot.sgm_alpha]
	mov	ds, ax
else
	mov	ax, [si+CDGSlot.sgm_colors]
	mov	cx, [si+CDGSlot.sgm_alpha]
	mov	ds, cx
endif
	xor	si, si
	cld
	align 2

@@alpha:
	mov	cx, bp
	rep movsd
	sub	di, dx
	jns	short @@alpha
if GAME eq 5
	mov	ds, ax
endif
	xor	al, al
	out	7Ch, al
	xor	si, si
if GAME eq 5
	align 2
endif

if GAME eq 4
@@sgm_colors:
	mov	ax, 1234h
	mov	ds, ax
	assume ds:nothing
endif

@@next_plane:
	mov	di, bx

@@next_row:
	mov	cx, bp

@@blit_dword:
	lodsd
	or	es:[di], eax
	add	di, 4
	loop	@@blit_dword
	sub	di, dx
	jns	short @@next_row
	pop	ax
	mov	es, ax
	or	ax, ax
	jnz	short @@next_plane
	pop	ds
	assume ds:_DATA
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put	endp
	align 2
