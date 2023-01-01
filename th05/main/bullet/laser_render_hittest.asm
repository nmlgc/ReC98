	@vector2_at_opt$qv procdesc near

public @LASER_HITTEST$QR7LASER_T
@laser_hittest$qr7laser_t proc near
testrect_center		= byte ptr -4
laser		= word ptr  4

	enter	8, 0
	push	di
	push	si
	mov	di, [bp+laser]
	mov	bx, [di+laser_t.coords.ends_at_distance]
	mov	si, [di+laser_t.coords.starts_at_distance]
	sub	bp, size Point
	mov	eax, dword ptr [di+laser_t.coords.origin]
	mov	[bp+0],	eax
	mov	cl, [di+laser_t.coords.angle]
	xor	ch, ch
	lea	di, [bp+testrect_center]

@@loop:
	call	@vector2_at_opt$qv
	add	ax, (6 shl 4)
	sub	ax, _player_pos.cur.y
	cmp	ax, (12 shl 4)
	jnb	short @@testrect_move_up
	mov	ax, ss:[di+Point.x]
	add	ax, (6 shl 4)
	sub	ax, _player_pos.cur.x
	cmp	ax, (12 shl 4)
	jnb	short @@testrect_move_up
	mov	_player_is_hit, 1
	jmp	short @@ret

@@testrect_move_up:
	sub	bx, (16 shl 4)
	cmp	bx, si
	jge	short @@loop

@@ret:
	add	bp, 4
	pop	si
	pop	di
	leave
	ret	2
@laser_hittest$qr7laser_t endp
