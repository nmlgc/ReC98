public @shots_add$qv
@shots_add$qv proc near
	xor	ax, ax
	mov	bx, _shot_ptr

@@loop:
	cmp	bx, offset _shots_end
	jnb	short @@ret
	add	bx, size shot_t
	cmp	[bx+shot_t.flag], F_FREE
	jnz	short @@loop
	mov	word ptr [bx+shot_t.flag], F_ALIVE or (0 shl 8) ; flag = F_ALIVE, age = 0
	mov	eax, _player_pos.cur
	mov	dword ptr [bx+shot_t.pos.cur],	eax
	mov	dword ptr [bx+shot_t.pos.velocity], (-12 shl 4) shl 16 or (0)
	mov	word ptr [bx+shot_t.patnum_base], 20
	mov	ax, bx
	add	bx, size shot_t
	mov	_shot_ptr, bx

@@ret:
	retn
@shots_add$qv endp
	even
