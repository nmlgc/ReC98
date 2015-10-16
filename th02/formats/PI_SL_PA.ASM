; int DEFCONV pi_slot_palette_apply(int slot)
if GAME ge 3
	align	2
endif

proc_defconv pi_slot_palette_apply
@@slot	= word ptr (cPtrSize + 2)

	push	bp
	mov	bp, sp
	push	(16 * 3)
	push	ds
	mov	ax, [bp+@@slot]
	imul	ax, size PiHeader
	add	ax, offset _pi_slot_headers + PiHeader._palette
	push	ax
	push	ds
	push	offset Palettes
	call	_memcpy
	add	sp, 10
	call	palette_show
	pop	bp
if GAME ge 3
	retf	2
else
	ret
endif
endp_defconv
