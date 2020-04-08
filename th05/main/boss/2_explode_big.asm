public BOSS2_EXPLODE_BIG
boss2_explode_big	proc near

@@y	= word ptr -4
@@x	= word ptr -2

	enter	4, 0
	mov	ax, _boss_pos.cur.x
	mov	[bp+@@x], ax
	mov	ax, _boss_pos.cur.y
	mov	[bp+@@y], ax
	mov	eax, _boss2_pos.cur
	mov	_boss_pos.cur, eax
	call	boss_explode_big
	mov	ax, [bp+@@x]
	mov	_boss_pos.cur.x, ax
	mov	ax, [bp+@@y]
	mov	_boss_pos.cur.y, ax
	leave
	retn
boss2_explode_big	endp
