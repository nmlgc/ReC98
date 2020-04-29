public @playperf_adjust_speed
@playperf_adjust_speed	proc near
	shr	al, 1
	mov	cl, al
	mul	_playperf
	shr	ax, 5
	add	al, cl
	cmp	al, 128
	jbe	short @@below_8?
	mov	al, 128

@@below_8?:
	cmp	al, 8
	jnb	short @@ret
	mov	al, 8

@@ret:
	ret
@playperf_adjust_speed	endp
