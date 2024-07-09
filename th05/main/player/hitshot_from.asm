; Creates a hit animation at the position of [shot], invalidating [shot] in
; the process.

; void pascal near hitshot_from(shot_t near *shot)
public HITSHOT_FROM
hitshot_from	proc near

@@shot	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, [bp+@@shot]
	mov	ax, _hitshot_next_free_id
	imul	ax, size hitshot_t
	add	ax, offset _hitshots
	mov	si, ax
	cmp	_hitshot_next_free_id, HITSHOT_COUNT - 1
	jnb	short @@wrap_id
	inc	_hitshot_next_free_id
	jmp	short @@convert_age

@@wrap_id:
	mov	_hitshot_next_free_id, 0

@@convert_age:
	mov	[di+shot_t.flag], F_REMOVE
	cmp	[si+hitshot_t.HITSHOT_AGE], 0
	jnz	short @@ret	; Wat?
	mov	[si+hitshot_t.HITSHOT_AGE], 1
	cmp	[di+shot_t.patnum_base], 20
	jnz	short @@patnum_32
	mov	[si+hitshot_t.patnum], 28
	jmp	short @@convert_pos_and_brake

@@patnum_32:
	mov	[si+hitshot_t.patnum], 32

@@convert_pos_and_brake:
	mov	eax, dword ptr [di+hitshot_t.pos.cur]
	mov	dword ptr [si+hitshot_t.pos.cur], eax
	mov	eax, dword ptr [di+shot_t.pos.prev]
	mov	dword ptr [si+hitshot_t.pos.prev], eax
	mov	ax, [di+shot_t.pos.velocity.x]
	mov	bx, 6
	cwd
	idiv	bx
	mov	[si+hitshot_t.pos.velocity.x], ax
	mov	ax, [di+shot_t.pos.velocity.y]
	cwd
	idiv	bx
	mov	[si+hitshot_t.pos.velocity.y], ax

@@ret:
	pop	di
	pop	si
	pop	bp
	retn	2
hitshot_from	endp
