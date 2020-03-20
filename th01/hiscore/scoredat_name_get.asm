public _scoredat_name_get
_scoredat_name_get	proc far

@@place		= word ptr  6
@@str		= dword	ptr  8

	push	bp
	mov	bp, sp
	xor	dx, dx
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	mov	bx, [bp+@@place]
	shl	bx, 4
	add	bx, dx
	mov	es, word ptr _scoredat_names+2
	add	bx, word ptr _scoredat_names
	mov	al, es:[bx]
	les	bx, [bp+@@str]
	add	bx, dx
	mov	es:[bx], al
	inc	dx

@@more?:
	cmp	dx, SCOREDAT_NAME_BYTES
	jl	short @@loop
	les	bx, [bp+@@str]
	mov	byte ptr es:[bx+SCOREDAT_NAME_BYTES], 0
	pop	bp
	retf
_scoredat_name_get	endp
