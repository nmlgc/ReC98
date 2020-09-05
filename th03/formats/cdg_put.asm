; Displays the CDG image in the given [slot] at (⌊left/8⌋*8, top).

; void pascal cdg_put(screen_x_t left, vram_y_t top, int slot);
public CDG_PUT
cdg_put proc far

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	ax, [si+cdg_t.seg_colors]
	mov	word ptr cs:@@seg_colors+1, ax
	mov	ax, [bp+@@left]
	sar	ax, 3
	add	ax, [si+cdg_t.offset_at_bottom_left]
	mov	di, ax
	mov	word ptr cs:@@offset_at_bottom_left+1, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	word ptr cs:@@width_1+1, ax
	mov	word ptr cs:@@width_2+1, ax
	shl	ax, 2
	add	ax, (640 / 8)
	mov	word ptr cs:@@stride+1, ax
	jmp	short $+2
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
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
