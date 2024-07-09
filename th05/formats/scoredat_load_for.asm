public SCOREDAT_LOAD_FOR
scoredat_load_for	proc near

@@playchar	= word ptr  4

	push	bp
	mov	bp, sp
	call	file_exist pascal, ds, offset _SCOREDAT_FN_0
	or	ax, ax
	jz	short @@recreate
	call	file_ropen pascal, ds, offset _SCOREDAT_FN_1
	mov	ax, [bp+@@playchar]
	imul	ax, RANK_COUNT
	mov	dl, _rank
	mov	dh, 0
	add	ax, dx
	imul	ax, size scoredat_section_t
	movzx	eax, ax
	call	file_seek pascal, large eax, 0
	call	file_read pascal, ds, offset _hi, size scoredat_section_t
	call	file_close
	call	scoredat_decode_func
	or	al, al
	jz	short @@success

@@recreate:
	call	scoredat_recreate_func
	mov	al, 1
	pop	bp
	retn	2
; ---------------------------------------------------------------------------

@@success:
	mov	al, 0
	pop	bp
	retn	2
scoredat_load_for endp
