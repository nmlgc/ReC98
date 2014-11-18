; TH02: int __cdecl pi_slot_load(int slot, char *fn)
; TH03: int __cdecl pi_slot_load(char *fn, int slot)
pi_slot_load	proc
@@ret	= word ptr -2
if GAME ge 3
@@fn	= DPTR_ (cPtrSize + 2)
@@slot	= word ptr (cPtrSize + 2 + dPtrSize)
else
@@slot	= word ptr (cPtrSize + 2)
@@fn	= DPTR_ (cPtrSize + 4)
endif

	enter	2, 0
	push	si
	mov	si, [bp+@@slot]
if GAME ge 3
	mov	ax, si
	imul	ax, size PiHeader
	add	ax, offset pi_slot_headers
	push	ds
	push	ax
	mov	bx, si
	shl	bx, 2
	push	large pi_slot_buffers[bx]
	call	graph_pi_free
endif
	push	large [bp+@@fn]
	mov	ax, si
	imul	ax, size PiHeader
	add	ax, offset pi_slot_headers
	push	ds
	push	ax
	mov	ax, si
	shl	ax, 2
	add	ax, offset pi_slot_buffers
	push	ds
	push	ax
	call	graph_pi_load_pack
	mov	[bp+@@ret], ax
	pop	si
	leave
if GAME ge 3
	ret	6
else
	ret
endif
pi_slot_load	endp
