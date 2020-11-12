public _hflip_lut_generate
_hflip_lut_generate proc far
	push	di
	xor	ax, ax
	mov	di, offset _hflip_lut
	xor	dl, dl
	jmp	short @@set_and_loop

@@permutation_loop:
	xor	dl, dl
	mov	cx, 8

@@generation_loop:
	rol	al, 1
	rcr	dl, 1
	loop	@@generation_loop

@@set_and_loop:
	mov	[di], dl
	inc	di
	inc	al
	jnz	short @@permutation_loop
	pop	di
	ret
_hflip_lut_generate endp
