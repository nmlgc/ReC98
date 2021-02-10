public PI_PALETTE_APPLY
pi_palette_apply proc
arg_bx	far, @slot:word

	push	si
	push	di
	mov	si, @slot
	imul	si, size PiHeader
	add	si, offset _pi_headers + PiHeader._palette
	mov	di, offset Palettes
	mov	ax, ds
	mov	es, ax
	mov	cx, (16 * 3) / 4
	rep movsd
	call	palette_show
	pop	di
	pop	si
	ret_bx
pi_palette_apply endp
