public @std_free$qv
@std_free$qv proc near
	push	bp
	mov	bp, sp
	cmp	_std_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _std_seg
	mov	_std_seg, 0

@@ret:
	pop	bp
	retn
@std_free$qv endp
