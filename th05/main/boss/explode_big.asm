public @boss_explode_big_circle$qv
@boss_explode_big_circle$qv proc near
	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _explosions_big
	mov	[si+explosion_t.EXPLOSION_alive], 1
	mov	[si+explosion_t.age], 0
	mov	ax, _boss_pos.cur.x
	mov	[si+explosion_t.center.x], ax
	mov	ax, _boss_pos.cur.y
	mov	[si+explosion_t.center.y], ax
	mov	[si+explosion_t.EXPLOSION_radius_cur.x], 8
	mov	[si+explosion_t.EXPLOSION_radius_cur.y], 8
	mov	[si+explosion_t.EXPLOSION_radius_delta.x], (12 shl 4)
	mov	[si+explosion_t.EXPLOSION_radius_delta.y], (12 shl 4)
	mov	[si+explosion_t.angle_offset], 0
	call	snd_se_play pascal, 12
	pop	si
	pop	bp
	retn
@boss_explode_big_circle$qv endp
