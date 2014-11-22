; int __cdecl pi_slot_palette_apply(int slot)
pi_slot_palette_apply	proc
@@slot	= word ptr cPtrSize

	mov	bx, sp
	push	si
	push	di
	mov	si, ss:[bx+@@slot]
	imul	si, size PiHeader
	add	si, offset pi_slot_headers + PiHeader._palette
	mov	di, offset Palettes
	mov	ax, ds
	mov	es, ax
	mov	cx, (16 * 3) / 4
	rep movsd
	call	palette_show
	pop	di
	pop	si
	ret	2
pi_slot_palette_apply	endp
