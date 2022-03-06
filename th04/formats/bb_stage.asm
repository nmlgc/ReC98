public @BB_STAGE_LOAD$QNXC
@bb_stage_load$qnxc proc near

@@fn	= dword	ptr  4

	push	bp
	mov	bp, sp
if GAME eq 5
	call	bb_load pascal, large [bp+@@fn]
	mov	_bb_stage_seg, ax
else
	call	file_ropen pascal, large [bp+@@fn]
	call	hmem_allocbyte pascal, BB_SIZE
	mov	_bb_stage_seg, ax
	call	file_read pascal, ax, large BB_SIZE
	call	file_close
endif
	pop	bp
	retn	4
@bb_stage_load$qnxc endp


public @bb_stage_free$qv
if GAME eq 5
	@bb_stage_free$qv	proc near
else
	@bb_stage_free$qv	proc far
endif
	push	bp
	mov	bp, sp
	cmp	_bb_stage_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_stage_seg
	mov	_bb_stage_seg, 0

@@ret:
	pop	bp
	ret
@bb_stage_free$qv endp
