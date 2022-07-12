public @explosions_small_reset$qv
@explosions_small_reset$qv proc far
	push	bp
	mov	bp, sp
	mov	_explosions_small[0 * size explosion_t].flag, 0
	mov	_explosions_small[1 * size explosion_t].flag, 0
	pop	bp
	retf
@explosions_small_reset$qv endp
