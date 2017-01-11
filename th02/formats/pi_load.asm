proc_defconv pi_load
	arg @@slot:word, @@fn:dword
	local @@ret

	push	si
	mov	si, @@slot
if GAME ge 3
	mov	ax, si
	imul	ax, size PiHeader
	add	ax, offset _pi_headers
	push	ds
	push	ax
	mov	bx, si
	shl	bx, 2
	pushd	_pi_buffers[bx]
	call	graph_pi_free
endif
	pushd	@@fn
	mov	ax, si
	imul	ax, size PiHeader
	add	ax, offset _pi_headers
	push	ds
	push	ax
	mov	ax, si
	shl	ax, 2
	add	ax, offset _pi_buffers
	push	ds
	push	ax
	call	graph_pi_load_pack
	mov	@@ret, ax
	pop	si
	ret
endp_defconv
