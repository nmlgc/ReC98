public PI_FREE
func pi_free
@@slot	= word ptr 4

	mov	bx, sp
	mov	bx, ss:[bx+@@slot]
	mov	ax, bx
	shl	bx, 2
	add	bx, offset _pi_buffers
	cmp	dword ptr [bx], 0
	jz	short @@ret
	imul	ax, size PiHeader
	add	ax, offset _pi_headers
	push	ds
	push	ax
	push	word ptr [bx+2]
	push	word ptr [bx]
	mov	dword ptr [bx], 0
	call	graph_pi_free
@@ret:
	ret	2
endfunc
