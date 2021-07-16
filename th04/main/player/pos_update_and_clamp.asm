public PLAYER_POS_UPDATE_AND_CLAMP
player_pos_update_and_clamp	proc near
	push	bp
	mov	bp, sp
	call	motion_update_seg1 pascal, offset _player_pos
	cmp	ax, ((0 + PLAYER_MOVE_MARGIN_LEFT) shl 4)
	jge	short @@clamp_right?
	mov	ax, ((0 + PLAYER_MOVE_MARGIN_LEFT) shl 4)
	jmp	short @@clamp_top?
; ---------------------------------------------------------------------------

@@clamp_right?:
	cmp	ax, ((PLAYFIELD_W - PLAYER_MOVE_MARGIN_RIGHT) shl 4)
	jle	short @@clamp_top?
	mov	ax, ((PLAYFIELD_W - PLAYER_MOVE_MARGIN_RIGHT) shl 4)

@@clamp_top?:
	cmp	dx, ((0 + PLAYER_MOVE_MARGIN_TOP) shl 4)
	jge	short @@clamp_bottom?
	mov	dx, ((0 + PLAYER_MOVE_MARGIN_TOP) shl 4)
	jmp	short @@set
; ---------------------------------------------------------------------------

@@clamp_bottom?:
	cmp	dx, ((PLAYFIELD_H - PLAYER_MOVE_MARGIN_BOTTOM) shl 4)
	jle	short @@set
	mov	dx, ((PLAYFIELD_H - PLAYER_MOVE_MARGIN_BOTTOM) shl 4)

@@set:
	mov	_player_pos.cur.x, ax
	mov	_player_pos.cur.y, dx
	pop	bp
	retn
player_pos_update_and_clamp	endp
