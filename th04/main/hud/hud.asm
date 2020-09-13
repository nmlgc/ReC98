public hud_hp_update_and_render
hud_hp_update_and_render	proc near

@@hp_cur	= word ptr  4
@@hp_max	= word ptr  6

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, [bp+@@hp_max]
	or	di, di
	jg	short @@at_max?
	xor	si, si
	jmp	short @@larger_than_last?
; ---------------------------------------------------------------------------

@@at_max?:
	cmp	di, [bp+@@hp_cur]
	jl	short @@calculate_bar_value
	mov	si, BAR_MAX
	jmp	short @@larger_than_last?
; ---------------------------------------------------------------------------

@@calculate_bar_value:
	movsx	eax, di
	shl	eax, 7	; *= BAR_MAX
	movsx	ebx, [bp+@@hp_cur]
	cdq
	idiv	ebx
	mov	si, ax
	cmp	si, BAR_MAX
	jge	short @@larger_than_last?
	inc	si

@@larger_than_last?:
	cmp	_hud_hp_bar_value_prev, si
	jge	short @@smaller_than_last?
	inc	_hud_hp_bar_value_prev

@@smaller_than_last?:
	cmp	_hud_hp_bar_value_prev, si
	jle	short @@put_and_ret
	mov	_hud_hp_bar_value_prev, si

@@put_and_ret:
	call	hud_hp_put pascal, _hud_hp_bar_value_prev
	pop	di
	pop	si
	pop	bp
	retn	4
hud_hp_update_and_render endp
