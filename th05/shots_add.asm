; Searches and returns the next free shot slot, or NULL if there are no more
; free ones.

; shot_t* shots_add(void)
public _shots_add
_shots_add	proc near
	xor	ax, ax
	mov	bx, _shot_ptr

@@loop:
	cmp	bx, offset _shots_end
	jnb	short @@ret
	add	bx, size shot_t
	cmp	[bx+shot_t.flag], 0
	jnz	short @@loop
	mov	word ptr [bx+shot_t.flag], 1
	mov	eax, player_pos.cur
	mov	dword ptr [bx+shot_t.pos.cur],	eax
	mov	dword ptr [bx+shot_t.pos.velocity], (-12 shl 4) shl 16 or (0)
	mov	word ptr [bx+shot_t.patnum_base], 20
	mov	ax, bx
	add	bx, size shot_t
	mov	_shot_ptr, bx

@@ret:
	retn
_shots_add	endp
	even
