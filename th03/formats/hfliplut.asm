; Generates a lookup table for flipping one byte, interpreted as a horizontal
; line of 8 pixels in a single bitplane.

; int DEFCONV hflip_lut_generate()
proc_defconv hflip_lut_generate
	push	di
	xor	ax, ax
	mov	di, offset hflip_lut
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
endp_defconv
