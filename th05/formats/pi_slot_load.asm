; int __stdcall pi_load(char *fn, int slot)
func pi_slot_load
@@fn	= DPTR_ (cPtrSize + 2)
@@slot	= word ptr (cPtrSize + 2 + dPtrSize)

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, [bp+@@slot]
	push	di
	call	pi_slot_free
	mov	si, di
	shl	si, 2
	add	si, offset _pi_slot_buffers
	imul	di, size PiHeader
	add	di, offset _pi_slot_headers
	push	word ptr [bp+@@fn+2]
	push	word ptr [bp+@@fn]
	push	ds
	push	di
	push	ds
	push	si
	call	graph_pi_load_pack
	pop	di
	pop	si
	pop	bp
	ret	6
endfunc
