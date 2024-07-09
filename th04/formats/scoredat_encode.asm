public SCOREDAT_ENCODE
scoredat_encode	proc near

@@byte		= byte ptr -1

	enter	2, 0
	push	si
	mov	_hi.sum, 0
	mov	si, scoredat_section_t.score
	jmp	short @@sum_more?
; ---------------------------------------------------------------------------

@@sum_loop:
	mov	al, byte ptr _hi[si]
	mov	ah, 0
	add	_hi.sum, ax
	inc	si

@@sum_more?:
	cmp	si, size scoredat_section_t
	jl	short @@sum_loop
	call	IRand
	mov	_hi.key1, al
	call	IRand
	mov	_hi.key2, al
	mov	[bp+@@byte], 0
	mov	si, size scoredat_section_t - 1
	jmp	short @@encode_more?
; ---------------------------------------------------------------------------

@@encode_loop:
	mov	al, byte ptr _hi[si]
	mov	dl, _hi.key1
	add	dl, [bp+@@byte]
	sub	al, dl
	mov	byte ptr _hi[si], al
	mov	al, byte ptr _hi[si]
	mov	[bp+@@byte], al
	mov	al, _hi.key2
	ror	[bp+@@byte], 3
	xor	[bp+@@byte], al
	dec	si

@@encode_more?:
	cmp	si, scoredat_section_t.score
	jge	short @@encode_loop
	pop	si
	leave
	retn
scoredat_encode	endp
