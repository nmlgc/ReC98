public BULLET_PATNUM_FOR_ANGLE
bullet_patnum_for_angle	proc near
@@angle      	= byte ptr 2
@@patnum_base	= word ptr 4

	mov	bx, sp
	mov	al, ss:[bx+@@angle]
	mov	bx, ss:[bx+@@patnum_base]
	add	al, 3
	; Yes, this is intended to also cover Yumeko's knife bullets, which start
	; at patnum 193.
	cmp	bx, PAT_BULLET16_V
	jnb	short @@is_vector_bullet
	and	al, 7Fh

@@is_vector_bullet:
	xor	ah, ah
	shr	al, 3
	add	ax, bx
	retn	4
bullet_patnum_for_angle	endp
	nop
