; void boss_explode_big(unsigned int type);
public boss_explode_big
boss_explode_big	proc near

@@type	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _explosions_big
	EXPLOSION_TYPED
boss_explode_big	endp
