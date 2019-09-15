; Frees the CDG images in all slots.

; void pascal cdg_freeall(void);
public CDG_FREEALL
cdg_freeall	proc near
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
cdg_freeall	endp
