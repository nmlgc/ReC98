public _boss2_explode_big_circle
_boss2_explode_big_circle proc near

@@y	= word ptr -4
@@x	= word ptr -2

	enter	4, 0
	mov	ax, _boss_pos.cur.x
	mov	[bp+@@x], ax
	mov	ax, _boss_pos.cur.y
	mov	[bp+@@y], ax
	mov	eax, _boss2_pos.cur
	mov	_boss_pos.cur, eax
	call	_boss_explode_big_circle
	mov	ax, [bp+@@x]
	mov	_boss_pos.cur.x, ax
	mov	ax, [bp+@@y]
	mov	_boss_pos.cur.y, ax
	leave
	retn
_boss2_explode_big_circle endp
