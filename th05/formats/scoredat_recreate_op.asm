public SCOREDAT_RECREATE_OP
scoredat_recreate_op	proc near

@@digit		= byte ptr -3
@@i		= word ptr -2

	enter	4, 0
	push	si
	mov	[bp+@@digit], gb_8_
	xor	si, si
	jmp	short @@places_more?
; ---------------------------------------------------------------------------

@@place_loop:
	mov	_hi.score.cleared, SCOREDAT_NOT_CLEARED
	mov	[bp+@@i], 0
	jmp	short @@digit_zero_more?
; ---------------------------------------------------------------------------

@@digit_zero_loop:
	mov	bx, si
	shl	bx, 3
	add	bx, [bp+@@i]
	mov	_hi.score.g_points[bx], gb_0_
	inc	[bp+@@i]

@@digit_zero_more?:
	cmp	[bp+@@i], SCORE_DIGITS
	jl	short @@digit_zero_loop
	or	si, si
	jnz	short @@not_first_place
	mov	bx, si
	shl	bx, 3
	mov	_hi.score.g_points[bx][6], gb_1_
	jmp	short @@set_name
; ---------------------------------------------------------------------------

@@not_first_place:
	mov	bx, si
	shl	bx, 3
	mov	al, [bp+@@digit]
	mov	_hi.score.g_points[bx][5], al
	add	al, -2
	mov	[bp+@@digit], al

@@set_name:
	mov	[bp+@@i], 0
	jmp	short @@name_more?
; ---------------------------------------------------------------------------

@@name_loop:
	mov	bx, si
	imul	bx, (SCOREDAT_NAME_LEN + 1)
	add	bx, [bp+@@i]
	mov	_hi.score.g_name[bx], gs_DOT
	inc	[bp+@@i]

@@name_more?:
	cmp	[bp+@@i], SCOREDAT_NAME_LEN
	jl	short @@name_loop
	mov	bx, si
	imul	bx, (SCOREDAT_NAME_LEN + 1)
	mov	_hi.score.g_name[bx][SCOREDAT_NAME_LEN], 0
	inc	si

@@places_more?:
	cmp	si, SCOREDAT_PLACES
	jl	short @@place_loop
	call	file_create pascal, ds, offset _SCOREDAT_FN ; "GENSOU.SCR"
	xor	si, si
	jmp	short @@sections_more?
; ---------------------------------------------------------------------------

@@section_loop:
	mov	[bp+@@i], 0
	jmp	short @@stage_more?
; ---------------------------------------------------------------------------

@@stage_loop:
	mov	ax, si
	mov	bx, RANK_COUNT
	cwd
	idiv	bx
	cmp	dx, RANK_EXTRA
	jnz	short @@not_extra_section
	mov	bx, [bp+@@i]
	mov	_hi.score.g_stage[bx], gb_1_
	jmp	short @@stage_next
; ---------------------------------------------------------------------------

@@not_extra_section:
	mov	bx, [bp+@@i]
	mov	al, gb_6_
	sub	al, byte ptr [bp+@@i]
	mov	_hi.score.g_stage[bx], al

@@stage_next:
	inc	[bp+@@i]

@@stage_more?:
	cmp	[bp+@@i], SCOREDAT_PLACES
	jl	short @@stage_loop
	call	scoredat_encode
	call	file_write pascal, ds, offset _hi, size scoredat_section_t
	call	scoredat_decode_func
	inc	si

@@sections_more?:
	cmp	si, RANK_COUNT * PLAYCHAR_COUNT
	jl	short @@section_loop
	call	file_close
	pop	si
	leave
	retn
scoredat_recreate_op	endp
