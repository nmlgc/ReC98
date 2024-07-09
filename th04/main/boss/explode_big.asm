public @BOSS_EXPLODE_BIG$QUI
@boss_explode_big$qui proc near

@@type	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _explosions_big
	EXPLOSION_TYPED
@boss_explode_big$qui endp
