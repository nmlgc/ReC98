; void pascal near bb_playchar_load(void);
public BB_PLAYCHAR_LOAD
bb_playchar_load	proc near
	push	bp
	mov	bp, sp
	les	bx, _resident
	mov	al, es:[bx+resident_t.playchar_ascii]
	les	bx, _bb_playchar_bb_fn
	mov	es:[bx+2], al
	les	bx, _resident
	les	bx, _bb_playchar_cdg_fn
	mov	es:[bx+2], al
	call	file_ropen pascal, large [_bb_playchar_bb_fn]
	call	hmem_allocbyte pascal, BB_SIZE
	mov	_bb_playchar_seg, ax
	call	file_read pascal, ax, large BB_SIZE
	call	file_close
	call	cdg_load_single_noalpha pascal, CDG_BG_PLAYCHAR_BOMB, [_bb_playchar_cdg_fn], 0
	pop	bp
	retn
bb_playchar_load	endp


; void pascal near bb_playchar_free(void);
public BB_PLAYCHAR_FREE
bb_playchar_free	proc near
	push	bp
	mov	bp, sp
	cmp	_bb_playchar_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_playchar_seg
	mov	_bb_playchar_seg, 0

@@ret:
	pop	bp
	retn
bb_playchar_free	endp
