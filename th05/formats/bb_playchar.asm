; void pascal near bb_playchar_load(void);
public BB_PLAYCHAR_LOAD
bb_playchar_load	proc near
	mov	al, playchar
	add	byte ptr _bb_playchar_fn+2, al
	call	bb_load pascal, ds, offset _bb_playchar_fn
	mov	_bb_playchar_seg, ax
	retn
bb_playchar_load	endp


; void pascal near bb_playchar_free(void);
public BB_PLAYCHAR_FREE
bb_playchar_free	proc near
	cmp	_bb_playchar_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_playchar_seg
	mov	_bb_playchar_seg, 0

@@ret:
	retn
bb_playchar_free	endp
	nop
