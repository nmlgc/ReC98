; Identical to the barely decompilable TH05 version, which doesn't rely on
; self-modifying code for the width.
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
	mov	word ptr cs:@@width+1, ax
	jmp	short $+2
	shl	ax, 2
	add	ax, (640 / 8)
	mov	dx, ax
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, 0A800h
	mov	es, ax
	push	ds
	mov	ds, [si+cdg_t.seg_alpha]
	xor	si, si
	cld
	align 2

@@width:
	mov	cx, 1234h
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
