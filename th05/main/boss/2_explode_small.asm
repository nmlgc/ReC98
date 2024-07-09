public @BOSS2_EXPLODE_SMALL$QUI
@boss2_explode_small$qui proc near

@@y   	= word ptr -4
@@x   	= word ptr -2
@@type	= word ptr  4

	enter	4, 0
	mov	ax, _boss_pos.cur.x
	mov	[bp+@@x], ax
	mov	ax, _boss_pos.cur.y
	mov	[bp+@@y], ax
	mov	eax, _boss2_pos.cur
	mov	_boss_pos.cur, eax
	call	@boss_explode_small$q16explosion_type_t pascal, [bp+@@type]
	mov	ax, [bp+@@x]
	mov	_boss_pos.cur.x, ax
	mov	ax, [bp+@@y]
	mov	_boss_pos.cur.y, ax
	leave
	retn	2
@boss2_explode_small$qui endp
