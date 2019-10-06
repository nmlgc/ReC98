public SHOT_VELOCITY_SET
shot_velocity_set	proc near
@@velocity	= word ptr 4
@@angle   	= byte ptr 2

	mov	bx, sp
	push	si
	mov	si, ss:[bx+@@velocity]
if GAME eq 5
	movzx	bx, ss:[bx+@@angle]
	mov	byte ptr [si+shot_t.SHOT_angle - shot_t.pos.velocity], bl
else
	mov	bl, ss:[bx+@@angle]
	xor	bh, bh
endif
	shl	bx, 2
	mov	eax, _VELOCITY_192_AT_ANGLE[bx]
	mov	[si], eax
	pop	si
	retn	4
shot_velocity_set	endp
