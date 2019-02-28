; void bb_playchar_load(void);
public bb_playchar_load
bb_playchar_load	proc near
	mov	al, playchar
	add	byte ptr _bb_playchar_fn+2, al
	call	bb_load pascal, ds, offset _bb_playchar_fn
	mov	_bb_playchar_seg, ax
	retn
bb_playchar_load	endp


; void bb_playchar_free(void);
public bb_playchar_free
bb_playchar_free	proc near
	cmp	_bb_playchar_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_playchar_seg
	mov	_bb_playchar_seg, 0

@@ret:
	retn
bb_playchar_free	endp
	nop
