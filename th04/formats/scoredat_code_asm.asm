scoredat_func macro nam:req
	public nam
	nam	proc near
	if GAME eq 5
		push	si
		mov 	bx, offset _hi
	else
		mov 	bx, sp
		push	si
		mov 	bx, ss:[bx+2]
	endif
		mov	si, bx

	endfunc macro
		pop 	si
		if GAME eq 5
			retn
			nam endp
		else
			retn 2
			nam endp
			; TODO: Turn into unconditional EVEN once this is a separate
			; translation unit
			even
		endif
	endm
endm

scoredat_func SCOREDAT_DECODE
	mov	cx, size scoredat_t - 1

	if GAME eq 5
		mov	dx, word ptr [bx+scoredat_section_t.key1]
		add	bx, scoredat_section_t.score

	@@decode:
		mov	al, [bx+1]
		ror	al, 3
		xor	al, dh
		add	al, dl
		add	[bx], al
		inc	bx
		loop	@@decode
		add	[bx], dl
		mov	cx, size scoredat_t
		xor	bx, bx
	else
		mov	ah, [bx+scoredat_section_t.key2]
		add	bx, scoredat_section_t.score

	@@decode:
		mov	al, [bx+1]
		ror	al, 3
		xor	al, ah
		add	al, [si+scoredat_section_t.key1]
		add	[bx], al
		inc	bx
		loop	@@decode
		mov	al, [si+scoredat_section_t.key1]
		add	[bx], al
		xor	bx, bx
		mov	cx, size scoredat_t
	endif

	xor	dx, dx
	mov	ax, [si+scoredat_section_t.sum]
	add	si, scoredat_section_t.score

@@sum:
	mov	bl, [si]
	add	dx, bx
	inc	si
	loop	@@sum
	sub	ax, dx
endfunc


scoredat_func SCOREDAT_ENCODE
	xor	dx, dx
	xor	ax, ax
	add	bx, scoredat_section_t.score
	mov	cx, size scoredat_t

@@sum:
	mov	dl, [bx]
	add	ax, dx
	inc	bx
	loop	@@sum
	mov	[si+scoredat_section_t.sum], ax
	call	IRand
	mov	word ptr [si+scoredat_section_t.key1], ax
	xor	dx, dx
	add	si, size scoredat_section_t - 1
	mov	cx, size scoredat_t

@@encode:
	add	dl, al
	sub	[si], dl
	mov	dl, [si]
	ror	dl, 3
	xor	dl, ah
	dec	si
	loop	@@encode
endfunc

purge scoredat_func
