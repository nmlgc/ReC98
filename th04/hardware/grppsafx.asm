glyph_weight_1	label near
	mov	dx, ax
	add	dx, dx
	or	ax, dx
glyph_weight_0	label near
	retn

glyph_weight_3	label near
	mov	dx, ax
	shl	dx, 1
	or	ax, dx
glyph_weight_2	label near
	mov	dx, ax
	mov	bp, ax
	add	bp, bp
	or	ax, bp
	xor	dx, ax
	add	dx, dx
	not	dx
	and	ax, dx
	retn

glyph_double_and_mask	proc near
	call	glyph_weight_2
	mov	bl, ch
	and	bx, 3
	add	bx, bx

grppsafx_glyph_mask equ $+3
	and	ax, fs:[bx+1234h]
	retn
glyph_double_and_mask	endp
