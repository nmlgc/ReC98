public ITEMS_MISS_ADD
items_miss_add	proc far

@@unused_index	= word ptr -0Ah
@@type	= word ptr -8
@@bigpower_index	= word ptr -6
@@field	= word ptr -4
@@total_item_i	= word ptr -2

	enter	0Ah, 0
	push	si
	push	di
	call	randring2_next16_mod pascal, MISS_ITEM_COUNT
	mov	[bp+@@bigpower_index], ax

@@unused_loop:
	call	randring2_next16_mod pascal, MISS_ITEM_COUNT
	mov	[bp+@@unused_index], ax
	cmp	ax, [bp+@@bigpower_index]
	jz	short @@unused_loop
	cmp	_player_pos.cur.x, ((PLAYFIELD_W / 3) * 1) shl 4
	jge	short @@field_center?
	mov	[bp+@@field], MISS_FIELD_LEFT
	jmp	short @@field_decided

@@field_center?:
	cmp	_player_pos.cur.x, ((PLAYFIELD_W / 3) * 2) shl 4
	jg	short @@field_right
	mov	[bp+@@field], MISS_FIELD_CENTER
	jmp	short @@field_decided

@@field_right:
	mov	[bp+@@field], MISS_FIELD_RIGHT

@@field_decided:
	xor	di, di
	mov	si, offset _items
	mov	[bp+@@total_item_i], 0
	jmp	@@more_available?

@@loop:
	cmp	[si+item_t.flag], 0
	jnz	short @@next
	mov	[si+item_t.flag], 1
	mov	[si+item_t.ITEM_unknown], 0
	mov	ax, _player_pos.cur.x
	mov	[si+item_t.pos.cur.x], ax
	mov	ax, _player_pos.cur.y
	mov	[si+item_t.pos.cur.y],	ax
	mov	bx, [bp+@@field]
	imul	bx, MISS_ITEM_COUNT * word * 2
	mov	ax, di
	add	ax, ax
	add	bx, ax
	mov	ax, (_ITEM_MISS_VELOCITIES + (MISS_ITEM_COUNT * word * 0))[bx]
	mov	[si+item_t.pos.velocity.y], ax
	mov	bx, [bp+@@field]
	imul	bx, MISS_ITEM_COUNT * word * 2
	mov	ax, di
	add	ax, ax
	add	bx, ax
	mov	ax, (_ITEM_MISS_VELOCITIES + (MISS_ITEM_COUNT * word * 1))[bx]
	mov	[si+item_t.pos.velocity.x], ax
	mov	[si+item_t.pulled_to_player], 0
	cmp	[bp+@@bigpower_index], di
	jz	short @@set_bigpower
	call	randring2_next16_and pascal, IT_POINT
	mov	[bp+@@type], ax
	jmp	short @@last_life?

@@set_bigpower:
	mov	[bp+@@type], IT_BIGPOWER

@@last_life?:
if GAME eq 5
	cmp	_lives, 1
else
	les	bx, _resident
	cmp	byte ptr es:[bx+resident_t.rem_lives], 1
endif
	jnz	short @@set_rest
	mov	[bp+@@type], IT_FULLPOWER

@@set_rest:
	mov	al, byte ptr [bp+@@type]
	mov	[si+item_t.ITEM_type], al
	mov	bx, [bp+@@type]
	add	bx, bx
	mov	ax, _ITEM_TYPE_PATNUM[bx]
	mov	[si+item_t.ITEM_patnum], ax
	inc	di
	inc	_items_spawned
	cmp	di, MISS_ITEM_COUNT
	jge	short @@ret

@@next:
	inc	[bp+@@total_item_i]
	add	si, size item_t

@@more_available?:
	cmp	[bp+@@total_item_i], ITEM_COUNT
	jl	@@loop

@@ret:
	pop	di
	pop	si
	leave
	retf
items_miss_add	endp
