public BB_PLAYCHAR_PUT
bb_playchar_put	proc near

@@cel		= word ptr  4

	push	bp
	mov	bp, sp

	if (GAME eq 4)
		cmp	_playchar, PLAYCHAR_REIMU
		jnz	short @@marisa
		mov	al, 15
		jmp	short @@set_col

	@@marisa:
		mov	al, 2

	@@set_col:
		mov	_tiles_bb_col, al
	endif

	mov	ax, _bb_playchar_seg
	mov	_tiles_bb_seg, ax
	call	@tiles_bb_put_raw$qi pascal, [bp+@@cel]
	pop	bp
	retn	2
bb_playchar_put endp
