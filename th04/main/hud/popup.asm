public POPUP_UPDATE_AND_RENDER
popup_update_and_render	proc near

@@i	= byte ptr -1

	enter	2, 0
	mov	al, _popup_id_new
	cmp	al, _popup_id_cur
	jz	short @@needs_init?
	cmp	_popup_frame, 64
	jb	short @@needs_init?
	call	text_putsa pascal, (PLAYFIELD_TRAM_LEFT shl 16) + POPUP_TRAM_Y, _PLAYFIELD_BLANK_ROW, TX_WHITE
	call	text_putsa pascal, (PLAYFIELD_TRAM_LEFT shl 16) + 23, _PLAYFIELD_BLANK_ROW, TX_WHITE
	mov	_popup_frame, 0

@@needs_init?:
	cmp	_popup_frame, 0
	jnz	short @@done?
	mov	al, _popup_id_new
	mov	_popup_id_cur, al
	mov	[bp+@@i], 0
	jmp	short @@shiftbuf_init_more?
; ---------------------------------------------------------------------------

@@shiftbuf_init_loop:
	mov	al, [bp+@@i]
	mov	ah, 0
	mov	bx, ax
	mov	_popup_shiftbuf[bx], g_EMPTY
	inc	[bp+@@i]

@@shiftbuf_init_more?:
	cmp	[bp+@@i], POPUP_LEN
	jb	short @@shiftbuf_init_loop
	mov	al, _popup_id_cur
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	pushd	_POPUP_STRINGS[bx]
	call	_strlen
	add	sp, 4
	mov	_popup_gaiji_len, ax
	mov	bx, _popup_gaiji_len
	mov	_popup_shiftbuf[bx], 0
	add	ax, ax
	mov	dx, PLAYFIELD_TRAM_LEFT + PLAYFIELD_TRAM_W
	sub	dx, ax
	mov	_popup_cur_tram_x, dx
	cmp	_popup_id_new, POPUP_ID_BONUS
	jz	short @@enforce_bonus_text_width
	mov	ax, PLAYFIELD_TRAM_LEFT + (PLAYFIELD_TRAM_W / 2)
	sub	ax, _popup_gaiji_len
	mov	_popup_dest_tram_x, ax
	jmp	short @@finish_init
; ---------------------------------------------------------------------------

; Since we print the number of points separately...
@@enforce_bonus_text_width:
	mov	_popup_dest_tram_x, 16

@@finish_init:
	mov	_popup_dest_reached, 0

@@done?:
	cmp	_popup_frame, POPUP_DURATION
	jb	short @@shift_needed?
	call	text_putsa pascal, (PLAYFIELD_TRAM_LEFT shl 16) + POPUP_TRAM_Y, _PLAYFIELD_BLANK_ROW, TX_WHITE
	mov	_popup_frame, 0
	mov	_popup, offset nullfunc_near
	leave
	retn
; ---------------------------------------------------------------------------

@@shift_needed?:
	mov	al, _popup_frame
	mov	ah, 0
	mov	dx, _popup_gaiji_len
	dec	dx
	cmp	ax, dx
	jge	short @@use_unshifted_string
	mov	[bp+@@i], 0
	jmp	short @@shift_more?
; ---------------------------------------------------------------------------

@@shift_loop:
	mov	al, [bp+@@i]
	mov	ah, 0
	mov	bx, ax
	mov	al, _popup_shiftbuf[bx+1]
	mov	dl, [bp+@@i]
	mov	dh, 0
	mov	bx, dx
	mov	_popup_shiftbuf[bx], al
	inc	[bp+@@i]

@@shift_more?:
	mov	al, [bp+@@i]
	mov	ah, 0
	mov	dx, _popup_gaiji_len
	dec	dx
	cmp	ax, dx
	jl	short @@shift_loop
	mov	al, _popup_id_cur
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	les	bx, _POPUP_STRINGS[bx]
	assume es:nothing
	mov	al, _popup_frame
	mov	ah, 0
	add	bx, ax
	mov	al, es:[bx]
	mov	bx, offset _popup_shiftbuf
	dec	bx
	add	bx, _popup_gaiji_len
	mov	[bx], al
	call	gaiji_putsa pascal, _popup_cur_tram_x, POPUP_TRAM_Y, ds, offset _popup_shiftbuf, TX_WHITE
	jmp	@@ret
; ---------------------------------------------------------------------------

@@use_unshifted_string:
	mov	ax, _popup_cur_tram_x
	cmp	ax, _popup_dest_tram_x
	jle	short @@dest_reached
	push	ax
	push	2
	mov	al, _popup_id_cur
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	pushd	_POPUP_STRINGS[bx]
	push	TX_WHITE
	call	gaiji_putsa
	mov	ax, _popup_gaiji_len
	add	ax, ax
	add	ax, _popup_cur_tram_x
	cmp	ax, PLAYFIELD_TRAM_LEFT + PLAYFIELD_TRAM_W - GAIJI_TRAM_W
	jg	short @@still_shifting
	mov	ax, _popup_gaiji_len
	add	ax, ax
	add	ax, _popup_cur_tram_x
	call	text_putca pascal, ax, (POPUP_TRAM_Y shl 16) or '  ', TX_WHITE

@@still_shifting:
	sub	_popup_cur_tram_x, GAIJI_TRAM_W
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@dest_reached:
	cmp	_popup_dest_reached, 0
	jnz	short @@put_regular
	mov	_popup_dest_reached, 1
	call	text_putsa pascal, (PLAYFIELD_TRAM_LEFT shl 16) + POPUP_TRAM_Y, _PLAYFIELD_BLANK_ROW, TX_WHITE

@@put_regular:
	push	_popup_dest_tram_x
	push	POPUP_TRAM_Y
	mov	al, _popup_id_cur
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	pushd	_POPUP_STRINGS[bx]
	push	TX_WHITE
	call	gaiji_putsa
	cmp	_popup_id_cur, POPUP_ID_BONUS
	jnz	short @@ret
if GAME eq 5
	call	hud_points_put pascal, ((PLAYFIELD_TRAM_LEFT + (PLAYFIELD_TRAM_W / 2)) shl 16) + 2, large [_popup_bonus]
else
	call	popup_points_put pascal, large [_popup_bonus]
endif

@@ret:
	inc	_popup_frame
	leave
	retn
popup_update_and_render	endp


if GAME eq 4
; Yes, specific to the bonus popup, due to the hardcoded position.

; void pascal near popup_points_put(unsigned long points);
public POPUP_POINTS_PUT
popup_points_put	proc pascal near
	arg  	@@points:dword
	local	@@digit:dword, @@divisor:dword, @@buf:byte:SCORE_DIGITS + 2 ; padding...

	push	si
	push	di
	mov	@@divisor, 1000000
	xor	si, si
	xor	di, di
	jmp	short @@more_digits?
; ---------------------------------------------------------------------------

@@digit_loop:
	mov	eax, @@points
	xor	edx, edx
	div	@@divisor
	mov	@@digit, eax
	mov	eax, @@points
	xor	edx, edx
	div	@@divisor
	mov	@@points, edx
	or	di, word ptr @@digit
	or	di, di
	jz	short @@omit_leading_zeroes
	mov	al, byte ptr @@digit
	add	al, GB_DIGITS
	mov	@@buf[si], al
	jmp	short @@divisor_next
; ---------------------------------------------------------------------------

@@omit_leading_zeroes:
	mov	@@buf[si], g_EMPTY

@@divisor_next:
	mov	ebx, 10
	mov	eax, @@divisor
	xor	edx, edx
	div	ebx
	mov	@@divisor, eax
	inc	si

@@more_digits?:
	cmp	@@divisor, 1
	ja	short @@digit_loop
	mov	al, byte ptr @@points
	add	al, gb_0_
	mov	@@buf[SCORE_DIGITS - 2], al   	; (ones)
	mov	@@buf[SCORE_DIGITS - 1], gb_0_	; ("continues used" digit)
	mov	@@buf[SCORE_DIGITS - 0], 0     	; (null terminator)
	push	((PLAYFIELD_TRAM_LEFT + (PLAYFIELD_TRAM_W / 2)) shl 16) + POPUP_TRAM_Y
	push	ss
	lea	ax, @@buf
	push	ax
	push	TX_WHITE
	call	gaiji_putsa
	pop	di
	pop	si
	ret
popup_points_put	endp
endif
