public _hflip_lut_generate
_hflip_lut_generate proc
	push	di
	xor	ax, ax
	mov	di, offset _hflip_lut
	xor	dl, dl
	jmp	short @@check

@@outer:
	xor	dl, dl
	mov	cx, 8

@@inner:
	rol	al, 1
	rcr	dl, 1
	loop	@@inner

@@check:
	mov	[di], dl
	inc	di
	inc	al
	jnz	short @@outer
	pop	di
	ret
_hflip_lut_generate endp
