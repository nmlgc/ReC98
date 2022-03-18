public _boss_items_drop
_boss_items_drop	proc near

@@top		= word ptr -4
@@left		= word ptr -2

@@DROP_COUNT = 5

@@DROP_AREA_W = (128 shl 4)
@@DROP_AREA_H = (128 shl 4)

	enter	4, 0
	push	si
	push	di
	if GAME eq 5
		@@DROP_SET_FULLPOWER = 1

		cmp	_power, 128
		jnb	short @@set_fullpower
		xor	di, di
		jmp	short @@coords
	else
		@@DROP_SET_FIVE_FROM_FULLPOWER = 1
		@@DROP_SET_FULLPOWER = 2

		cmp	_power, 123
		ja	short @@set_fullpower?
		xor	di, di
		jmp	short @@coords
	@@set_fullpower?:
		cmp	_power, 128
		jnb	short @@set_fullpower
		mov	di, @@DROP_SET_FIVE_FROM_FULLPOWER
		jmp	short @@coords
	endif

@@set_fullpower:
	mov	di, @@DROP_SET_FULLPOWER

@@coords:
	mov	ax, _boss_pos.cur.x
	add	ax, -(@@DROP_AREA_W / 2)
	mov	[bp+@@left], ax
	mov	ax, _boss_pos.cur.y
	add	ax, -(@@DROP_AREA_H / 2)
	mov	[bp+@@top], ax
	xor	si, si
	jmp	short @@items_more?
; ---------------------------------------------------------------------------

@@item_loop:
	call	randring2_next16_mod pascal, @@DROP_AREA_W
	add	ax, [bp+@@left]
	push	ax
	call	randring2_next16_mod pascal, @@DROP_AREA_H
	add	ax, [bp+@@top]
	push	ax
	mov	bx, di
	imul	bx, @@DROP_COUNT
	mov	al, _BOSS_ITEM_DROPS[bx+si]
	push	ax
	call	items_add
	inc	si

@@items_more?:
	cmp	si, @@DROP_COUNT
	jl	short @@item_loop
	pop	di
	pop	si
	leave
	retn
_boss_items_drop	endp


public BOSS_PHASE_END
boss_phase_end	proc near

@@next_phase_end_hp		= word ptr  4
@@explosion_type		= word ptr  6

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@explosion_type]
	cmp	si, ET_NONE
	jz	short @@set
	call	boss_explode_small pascal, si
	cmp	_boss_phase_timed_out, 0
	jnz	short @@set
	cmp	_bullet_clear_time, 20
	jnb	short @@already_clearing
	mov	_bullet_clear_time, 20

@@already_clearing:
	call	_boss_items_drop

@@set:
	mov	_boss_phase_timed_out, 1
	inc	_boss_phase
	mov	_boss_phase_frame, 0
	mov	_boss_mode, 0
	mov	_boss_mode_change, 0
	mov	ax, _boss_phase_end_hp
	mov	_boss_hp, ax
	mov	ax, [bp+@@next_phase_end_hp]
	mov	_boss_phase_end_hp, ax
	pop	si
	pop	bp
	retn	4
boss_phase_end	endp
