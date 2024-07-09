public _pause
_pause	proc near
	push	bp
	mov	bp, sp
	push	si
	xor	si, si
	jmp	short @@inp_reset_sense_for_start
; ---------------------------------------------------------------------------

@@inp_reset_sense_for:
	call	input_reset_sense_interface

@@inp_reset_sense_for_start:
	cmp	_key_det, INPUT_NONE
	jnz	short @@inp_reset_sense_for
	call	gaiji_putsa pascal, (26 shl 16) + 12, ds, offset gsCHUUDAN, TX_YELLOW
	call	gaiji_putsa pascal, (26 shl 16) + 14, ds, offset gsSAIKAI, TX_WHITE + TX_UNDERLINE
	call	gaiji_putsa pascal, (26 shl 16) + 15, ds, offset gsSHUURYOU, TX_YELLOW

@@menu_loop_start:
	call	@input_wait_for_change$qi pascal, 0
	test	_key_det.lo, low INPUT_UP
	jnz	short @@select
	test	_key_det.lo, low INPUT_DOWN
	jz	short @@not_select

@@select:
	mov	ax, 1
	sub	ax, si
	mov	si, ax
	or	si, si
	jnz	short @@sel_quit
	call	gaiji_putsa pascal, (26 shl 16) + 14, ds, offset gsSAIKAI, TX_WHITE + TX_UNDERLINE
	push	(26 shl 16) + 15
	push	ds
	push	offset gsSHUURYOU ; strp
	push	TX_YELLOW
	jmp	short @@sel_gaiji_putsa
; ---------------------------------------------------------------------------

@@sel_quit:
	call	gaiji_putsa pascal, (26 shl 16) + 14, ds, offset gsSAIKAI, TX_YELLOW
	push	(26 shl 16) + 15
	push	ds
	push	offset gsSHUURYOU ; strp
	push	TX_WHITE + TX_UNDERLINE

@@sel_gaiji_putsa:
	call	gaiji_putsa

@@not_select:
	test	_key_det.hi, high INPUT_Q
	jz	short @@sel_confirm_cancel_check
	mov	ax, 1
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@sel_confirm_cancel_check:
	test	_key_det.hi, high INPUT_CANCEL
	jz	short @@sel_confirm_check
	xor	si, si
	jmp	short @@menu_loop_end
; ---------------------------------------------------------------------------

@@sel_confirm_check:
	test	_key_det.lo, low INPUT_SHOT
	jnz	short @@menu_loop_end
	test	_key_det.hi, high INPUT_OK
	jz	@@menu_loop_start
	jmp	short @@menu_loop_end
; ---------------------------------------------------------------------------

@@inp_reset_sense_for_func_end:
	call	input_reset_sense_interface

@@menu_loop_end:
	if GAME eq 5
		test	_key_det.hi, high INPUT_CANCEL
	else
		cmp	_key_det, INPUT_NONE
	endif
	jnz	short @@inp_reset_sense_for_func_end

	call	text_putsa pascal, (26 shl 16) + 12, ds, offset _aGAME_PAUSE_SPACES_1, TX_WHITE
	call	text_putsa pascal, (26 shl 16) + 14, ds, offset _aGAME_PAUSE_SPACES_2, TX_WHITE
	call	text_putsa pascal, (26 shl 16) + 15, ds, offset _aGAME_PAUSE_SPACES_3, TX_WHITE
	mov	ax, si

@@ret:
	pop	si
	pop	bp
	retn
_pause	endp
