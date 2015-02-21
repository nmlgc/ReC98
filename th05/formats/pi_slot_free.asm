; int __pascal pi_slot_free(int slot)
func pi_slot_free
@@slot	= word ptr 4

	mov	bx, sp
	mov	bx, ss:[bx+@@slot]
	mov	ax, bx
	shl	bx, 2
	add	bx, offset _pi_slot_buffers
	cmp	dword ptr [bx], 0
	jz	short @@ret
	imul	ax, size PiHeader
	add	ax, offset _pi_slot_headers
	push	ds
	push	ax
	push	word ptr [bx+2]
	push	word ptr [bx]
	mov	dword ptr [bx], 0
	call	graph_pi_free
@@ret:
	ret	2
endfunc
