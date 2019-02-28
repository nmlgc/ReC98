; void near bb_txt_load(void);
public bb_txt_load
bb_txt_load	proc near
	push	bp
	mov	bp, sp
	call	hmem_allocbyte pascal, BB_SIZE + (BB_SIZE / 2)
	mov	_bb_txt_seg, ax
	call	file_ropen pascal, ds, offset aTxt_bb
	call	file_read pascal, _bb_txt_seg, large BB_SIZE
	call	file_close
	call	file_ropen pascal, ds, offset aTxt2_bb
	call	file_read pascal, _bb_txt_seg, large (BB_SIZE shl 16) or (BB_SIZE / 2)
	call	file_close
	pop	bp
	retn
bb_txt_load	endp


; void near bb_txt_free(void);
public bb_txt_free
bb_txt_free	proc near
	push	bp
	mov	bp, sp
	cmp	_bb_txt_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_txt_seg
	mov	_bb_txt_seg, 0

@@ret:
	pop	bp
	retn
bb_txt_free	endp
