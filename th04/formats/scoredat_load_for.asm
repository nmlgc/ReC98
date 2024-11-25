public SCOREDAT_LOAD_FOR
scoredat_load_for proc near

@@playchar		= byte ptr  4

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
	cmp	[bp+@@playchar], PLAYCHAR_REIMU
	jz	short @@read
	call	file_seek pascal, large RANK_COUNT * size scoredat_section_t, 1

@@read:
	call	file_read pascal, ds, offset _hi, size scoredat_section_t
	call	file_close
	call	scoredat_decode_func
	or	al, al
	jz	short @@success

@@recreate:
	call	@scoredat_recreate$qv
	mov	al, 1
	pop	bp
	retn	2
; ---------------------------------------------------------------------------

@@success:
	mov	al, 0
	pop	bp
	retn	2
scoredat_load_for endp
