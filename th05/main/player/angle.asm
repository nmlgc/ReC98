public PLAYER_ANGLE_FROM
player_angle_from	proc near

@@plus_angle		= byte ptr  4
@@y		= word ptr  6
@@x		= word ptr  8

	push	bp
	mov	bp, sp
	mov	ax, _player_pos.cur.y
	sub	ax, [bp+@@y]
	push	ax
	mov	ax, _player_pos.cur.x
	sub	ax, [bp+@@x]
	push	ax
	call	iatan2
	add	al, [bp+@@plus_angle]
	pop	bp
	retn	6
player_angle_from	endp
	nop
