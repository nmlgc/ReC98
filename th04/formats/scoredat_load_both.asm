public _scoredat_load_both
_scoredat_load_both proc near
	push	bp
	mov	bp, sp
	call	file_exist pascal, ds, offset aGensou_scr ; "GENSOU.SCR"
	or	ax, ax
	jz	short @@recreate
	call	file_ropen pascal, ds, offset aGensou_scr ; "GENSOU.SCR"
	mov	al, _rank
	mov	ah, 0
	imul	ax, size scoredat_section_t
	movzx	eax, ax
	call	file_seek pascal, large eax, 0
	call	file_read pascal, ds, offset _hi, size scoredat_section_t
	call	file_seek pascal, large (RANK_COUNT - 1) * size scoredat_section_t, 1
	call	file_read pascal, ds, offset _hi2, size scoredat_section_t
	call	file_close
	call	scoredat_decode_func
	or	al, al
	jz	short @@success

@@recreate:
	call	scoredat_recreate
	mov	al, 1
	pop	bp
	retn
; ---------------------------------------------------------------------------

@@success:
	mov	al, 0
	pop	bp
	retn
_scoredat_load_both endp
