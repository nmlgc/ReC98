public CDG_PUT_NOCOLORS_8
cdg_put_nocolors_8 proc far

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@slot]
	shl	si, 4
	add	si, offset _cdg_slots
	mov	di, [bp+@@left]
	sar	di, 3
	add	di, [si+cdg_t.offset_at_bottom_left]
	mov	ax, [si+cdg_t.vram_dword_w]
if GAME eq 4
	mov	word ptr cs:@@width+1, ax
	jmp	short $+2
else
	mov	bx, ax
endif
	shl	ax, 2
	add	ax, (640 / 8)
	mov	dx, ax
	mov	ax, [bp+@@top]
if GAME eq 4
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
else
	mov	cx, ax
	shl	ax, 2
	add	ax, cx
endif
	add	ax, 0A800h
	mov	es, ax
	push	ds
	mov	ds, [si+cdg_t.seg_alpha]
	xor	si, si
if GAME eq 4
	cld
endif
	align 2

@@width:
if GAME eq 4
	mov	cx, 1234h
else
	mov	cx, bx
endif
	rep movsd
	sub	di, dx
	jns	short @@width
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_nocolors_8 endp
	align 2
