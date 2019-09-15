; Displays the CDG image in the given [slot] at (⌊x/8⌋*8, y).

; void pascal cdg_put(int x, int y, int slot);
public cdg_put
cdg_put proc far

@@slot	= word ptr  6
@@y   	= word ptr  8
@@x   	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	ax, [si+CDGSlot.sgm_colors]
	mov	word ptr cs:@@sgm_colors+1, ax
	mov	ax, [bp+@@x]
	sar	ax, 3
	add	ax, [si+CDGSlot.vram_byte_at_bottom_left]
	mov	di, ax
	mov	word ptr cs:@@vram_byte_at_bottom_left+1, ax
	mov	ax, [si+CDGSlot.width_divided_by_32]
	mov	word ptr cs:@@width_1+1, ax
	mov	word ptr cs:@@width_2+1, ax
	shl	ax, 2
	add	ax, (640 / 8)
	mov	word ptr cs:@@stride+1, ax
	jmp	short $+2
	mov	ax, [bp+@@y]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
	push	ds
	mov	ax, [si+CDGSlot.sgm_alpha]
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

@@vram_byte_at_bottom_left:
	mov	bx, 1234h
	mov	di, bx
	xor	si, si

@@sgm_colors:
	mov	ax, 1234h
	mov	ds, ax
	assume ds:nothing

@@width_2:
	mov	cx, 1234h

@@blit_dword:
	mov	eax, [si]
	or	es:[di], eax
	add	si, 4
	add	di, 4
	loop	@@blit_dword
	sub	di, dx
	jns	short @@width_2
	mov	di, bx
	mov	ax, es
	add	ax, 800h
	mov	es, ax
	assume es:nothing
	cmp	ax, 0C000h
	jb	short @@width_2
	cmp	ax, 0C800h
	jnb	short @@ret
	add	ax, 2000h
	mov	es, ax
	assume es:nothing
	jmp	short @@width_2

@@ret:
	pop	ds
	assume ds:_DATA
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put endp
	align 2
