public @BB_BOSS_LOAD$QNXC
@bb_boss_load$qnxc	proc near

@@fn	= dword	ptr  4

	push	bp
	mov	bp, sp
if GAME eq 5
	call	bb_load pascal, large [bp+@@fn]
	mov	_bb_boss_seg, ax
else
	call	file_ropen pascal, large [bp+@@fn]
	call	hmem_allocbyte pascal, BB_SIZE
	mov	_bb_boss_seg, ax
	call	file_read pascal, ax, large BB_SIZE
	call	file_close
endif
	pop	bp
	retn	4
@bb_boss_load$qnxc endp


public @bb_boss_free$qv
if GAME eq 5
	@bb_boss_free$qv	proc near
else
	@bb_boss_free$qv	proc far
endif
	push	bp
	mov	bp, sp
	cmp	_bb_boss_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_boss_seg
	mov	_bb_boss_seg, 0

@@ret:
	pop	bp
	ret
@bb_boss_free$qv endp
