public _scoredat_load_for_cur
_scoredat_load_for_cur proc near
	push	bp
	mov	bp, sp
	call	file_exist pascal, ds, offset aGensou_scr_0 ; "GENSOU.SCR"
	or	ax, ax
	jz	short @@recreate
	call	file_ropen pascal, ds, offset aGensou_scr_1 ; "GENSOU.SCR"
	mov	al, _rank
	mov	ah, 0
	imul	ax, size scoredat_section_t
	movzx	eax, ax
	call	file_seek pascal, large eax, 0
	les	bx, _resident
	assume es:nothing
	cmp	es:[bx+resident_t.playchar_ascii], '0' + PLAYCHAR_MARISA
	jnz	short @@read
	call	file_seek pascal, large RANK_COUNT * size scoredat_section_t, 1

@@read:
	call	file_read pascal, ds, offset _hi, size scoredat_section_t
	call	file_close
	call	scoredat_decode_func
	or	al, al
	jz	short @@ret

@@recreate:
	call	scoredat_recreate_func

@@ret:
	pop	bp
	retn
_scoredat_load_for_cur endp
