; void pascal near bb_stage_load(const char far* fn);
public BB_STAGE_LOAD
bb_stage_load	proc near

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
bb_stage_load	endp


; void pascal bb_stage_free(void);
public BB_STAGE_FREE
if GAME eq 5
bb_stage_free	proc near
else
bb_stage_free	proc far
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
bb_stage_free	endp
