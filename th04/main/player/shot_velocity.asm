public SHOT_VELOCITY_SET
shot_velocity_set proc near
arg_bx	near, @angle:byte, @velocity:word

	push	si
	mov	si, @velocity
if GAME eq 5
	movzx	bx, @angle
	mov	byte ptr [si+shot_t.SHOT_angle - shot_t.pos.velocity], bl
else
	mov	bl, @angle
	xor	bh, bh
endif
	shl	bx, 2
	mov	eax, _VELOCITY_192_AT_ANGLE[bx]
	mov	[si], eax
	pop	si
	ret_bx
shot_velocity_set endp
