public SCOREDAT_DECODE
scoredat_decode	proc near

@@byte		= byte ptr -1

	enter	2, 0
	push	si
	mov	si, scoredat_section_t.score
	jmp	short @@1_decode_more?
; ---------------------------------------------------------------------------

@@1_decode_loop:
	mov	al, byte ptr _hi+1[si]
	mov	[bp+@@byte], al
	mov	al, _hi.key2
	ror	[bp+@@byte], 3
	xor	[bp+@@byte], al
	mov	al, byte ptr _hi+0[si]
	mov	dl, _hi.key1
	add	dl, [bp+@@byte]
	add	al, dl
	mov	byte ptr _hi+0[si], al
	inc	si

@@1_decode_more?:
	cmp	si, size scoredat_section_t - 1
	jl	short @@1_decode_loop
	mov	al, _hi.key1
	add	byte ptr _hi+0[si], al
	xor	cx, cx
	mov	si, scoredat_section_t.score
	jmp	short @@1_sum_more?
; ---------------------------------------------------------------------------

@@1_sum_loop?:
	mov	al, byte ptr _hi+0[si]
	mov	ah, 0
	add	cx, ax
	inc	si

@@1_sum_more?:
	cmp	si, size scoredat_section_t
	jl	short @@1_sum_loop?
	mov	al, byte ptr _hi.sum
	sub	al, cl

@@ret:
	pop	si
	leave
	retn
scoredat_decode	endp
