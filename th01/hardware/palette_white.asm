public _z_palette_white
_z_palette_white	proc far
	push	bp
	mov	bp, sp
	push	si
	xor	si, si
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	call	_z_palette_show_single c, si, 0Fh, large (0Fh shl 16) or 0Fh
	inc	si

@@more?:
	cmp	si, COLOR_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retf
_z_palette_white	endp
