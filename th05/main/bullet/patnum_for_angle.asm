public BULLET_PATNUM_FOR_ANGLE
bullet_patnum_for_angle proc near
arg_bx	near, @angle:byte, @patnum_base:word

	mov	al, @angle
	mov	bx, @patnum_base
	add	al, 3
	; Yes, this is intended to also cover Yumeko's swords, which start
	; at patnum 193.
	cmp	bx, PAT_BULLET16_V
	jnb	short @@is_vector_bullet
	and	al, 7Fh

@@is_vector_bullet:
	xor	ah, ah
	shr	al, 3
	add	ax, bx
	ret_bx
bullet_patnum_for_angle endp
	nop
