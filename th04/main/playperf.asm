public PLAYPERF_RAISE
playperf_raise proc far
arg_bx	far, @delta:byte

	mov	al, @delta
	add	al, _playperf
	cmp	al, _playperf_max
	jbe	short @@ret
	mov	al, _playperf_max

@@ret:
	mov	_playperf, al
	ret_bx
playperf_raise endp
	even


public PLAYPERF_LOWER
playperf_lower proc far
arg_bx	far, @delta:byte

	mov	al, _playperf
	sub	al, @delta
	cmp	al, _playperf_min
	jge	short @@ret
	mov	al, _playperf_min

@@ret:
	mov	_playperf, al
	ret_bx
playperf_lower endp
