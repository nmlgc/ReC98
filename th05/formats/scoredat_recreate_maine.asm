public SCOREDAT_RECREATE_MAINE
scoredat_recreate_maine	proc near

@@digit		= byte ptr -3
@@i		= word ptr -2

	enter	4, 0
	push	si
	mov	[bp+@@digit], gb_8_
	mov	[bp+@@i], 0
	jmp	short @@places_more?
; ---------------------------------------------------------------------------

@@place_loop:
	mov	_hi.score.cleared, SCOREDAT_NOT_CLEARED
	xor	si, si
	jmp	short @@digit_zero_more?
; ---------------------------------------------------------------------------

@@digit_zero_loop:
	mov	bx, [bp+@@i]
	shl	bx, 3
	mov	_hi.score.g_points[bx+si], gb_0_
	inc	si

@@digit_zero_more?:
	cmp	si, SCORE_DIGITS
	jl	short @@digit_zero_loop
	cmp	[bp+@@i], 0
	jnz	short @@not_first_place
	mov	bx, [bp+@@i]
	shl	bx, 3
	mov	_hi.score.g_points[bx][6], gb_1_
	jmp	short @@set_stage
; ---------------------------------------------------------------------------

@@not_first_place:
	mov	bx, [bp+@@i]
	shl	bx, 3
	mov	al, [bp+@@digit]
	mov	_hi.score.g_points[bx][5], al
	add	al, -2
	mov	[bp+@@digit], al

@@set_stage:
	mov	bx, [bp+@@i]
	mov	al, gb_6_
	sub	al, byte ptr [bp+@@i]
	mov	_hi.score.g_stage[bx], al
	xor	si, si
	jmp	short @@name_more?
; ---------------------------------------------------------------------------

@@name_loop:
	mov	bx, [bp+@@i]
	imul	bx, (SCOREDAT_NAME_LEN + 1)
	mov	_hi.score.g_name[bx+si], gs_DOT
	inc	si

@@name_more?:
	cmp	si, SCOREDAT_NAME_LEN
	jl	short @@name_loop
	mov	bx, [bp+@@i]
	imul	bx, (SCOREDAT_NAME_LEN + 1)
	mov	_hi.score.g_name[bx][SCOREDAT_NAME_LEN], 0
	inc	[bp+@@i]

@@places_more?:
	cmp	[bp+@@i], SCOREDAT_PLACES
	jl	short @@place_loop
	call	file_create pascal, ds, offset aGensou_scr ; "GENSOU.SCR"
	mov	[bp+@@i], 0
	jmp	short @@sections_more?
; ---------------------------------------------------------------------------

@@section_loop:
	call	scoredat_encode
	call	file_write pascal, ds, offset _hi, size scoredat_section_t
	call	scoredat_decode
	inc	[bp+@@i]

@@sections_more?:
	cmp	[bp+@@i], RANK_COUNT * PLAYCHAR_COUNT
	jl	short @@section_loop
	call	file_close
	pop	si
	leave
	retn
scoredat_recreate_maine	endp
