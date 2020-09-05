public CDG_FREE_ALL
cdg_free_all	proc near
	push	bp
	mov	bp, sp
	push	si
	xor	si, si
	jmp	short @@done?

@@loop:
	call	cdg_free pascal, si
	inc	si

@@done?:
	cmp	si, CDG_SLOT_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retn
cdg_free_all	endp
