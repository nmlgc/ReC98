public SCOREDAT_RECREATE
scoredat_recreate	proc near

@@digit		= byte ptr -1

	enter	2, 0
	push	si
	push	di
	mov	[bp+@@digit], gb_9_
	xor	si, si
	jmp	short @@places_more?
; ---------------------------------------------------------------------------

@@place_loop:
	mov	_hi.score.cleared, SCOREDAT_NOT_CLEARED
	xor	di, di
	jmp	short @@digit_zero_more?
; ---------------------------------------------------------------------------

@@digit_zero_loop:
	mov	bx, si
	shl	bx, 3
	mov	_hi.score.g_points[bx+di], gb_0_
	inc	di

@@digit_zero_more?:
	cmp	di, SCORE_DIGITS
	jl	short @@digit_zero_loop
	or	si, si
	jnz	short @@not_first_place
	mov	bx, si
	shl	bx, 3
	mov	_hi.score.g_points[bx][5], gb_1_
	jmp	short @@set_stage
; ---------------------------------------------------------------------------

@@not_first_place:
	mov	bx, si
	shl	bx, 3
	mov	al, [bp+@@digit]
	mov	_hi.score.g_points[bx][4], al
	dec	[bp+@@digit]

@@set_stage:
	mov	ax, si
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	dl, gb_5_
	sub	dl, al
	mov	_hi.score.g_stage[si], dl
	xor	di, di
	jmp	short @@name_more?
; ---------------------------------------------------------------------------

@@name_loop:
	mov	bx, si
	imul	bx, (SCOREDAT_NAME_LEN + 1)
	mov	_hi.score.g_name[bx+di], gs_DOT
	inc	di

@@name_more?:
	cmp	di, SCOREDAT_NAME_LEN
	jl	short @@name_loop
	mov	bx, si
	imul	bx, (SCOREDAT_NAME_LEN + 1)
	mov	_hi.score.g_name[bx] + SCOREDAT_NAME_LEN, 0
	inc	si

@@places_more?:
	cmp	si, SCOREDAT_PLACES
	jl	short @@place_loop
	call	file_create pascal, ds, offset aGensou_scr	; "GENSOU.SCR"
	xor	si, si
	jmp	short @@sections_more?
; ---------------------------------------------------------------------------

@@section_loop:
	call	scoredat_encode_func
	call	file_write pascal, ds, offset _hi, size scoredat_section_t
	call	scoredat_decode_func
	inc	si

@@sections_more?:
	cmp	si, RANK_COUNT * PLAYCHAR_COUNT
	jl	short @@section_loop
	call	file_close
	pop	di
	pop	si
	leave
	retn
scoredat_recreate	endp
