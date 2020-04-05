public SHOTS_ADD
shots_add	proc near
	xor	ax, ax

@@loop:
	cmp	_shot_last_id, SHOT_COUNT
	jnb	short @@ret
	mov	bx, _shot_ptr
	add	_shot_ptr, size shot_t
	cmp	[bx+shot_t.flag], 0
	jz	short @@found
	inc	_shot_last_id
	jmp	short @@loop

@@found:
	mov	word ptr [bx+shot_t.flag], 1
	mov	eax, _player_pos.cur
	mov	dword ptr [bx+shot_t.pos.cur], eax
	mov	dword ptr [bx+shot_t.pos.velocity], (-12 shl 4) shl 16 or (0)
	mov	ax, bx

@@ret:
	retn
shots_add	endp
