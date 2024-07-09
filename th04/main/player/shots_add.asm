public @shots_add$qv
@shots_add$qv proc near
	xor	ax, ax

@@loop:
	cmp	_shot_last_id, SHOT_COUNT
	jnb	short @@ret
	mov	bx, _shot_ptr
	add	_shot_ptr, size shot_t
	cmp	[bx+shot_t.flag], F_FREE
	jz	short @@found
	inc	_shot_last_id
	jmp	short @@loop

@@found:
	mov	word ptr [bx+shot_t.flag], F_ALIVE or (0 shl 8) ; flag = F_ALIVE, age = 0
	mov	eax, _player_pos.cur
	mov	dword ptr [bx+shot_t.pos.cur], eax
	mov	dword ptr [bx+shot_t.pos.velocity], (-12 shl 4) shl 16 or (0)
	mov	ax, bx

@@ret:
	retn
@shots_add$qv endp
