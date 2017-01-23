; Frees the CDG images in all slots.

; void cdg_freeall(void);
public _cdg_freeall
_cdg_freeall	proc near
	push	bp
	mov	bp, sp
	push	si
	xor	si, si
	jmp	short @@done?

@@loop:
	call	_cdg_free pascal, si
	inc	si

@@done?:
	cmp	si, CDG_SLOT_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retn
_cdg_freeall	endp
