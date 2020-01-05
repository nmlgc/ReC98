public _z_palette_black
_z_palette_black	proc far
	push	bp
	mov	bp, sp
	push	si
	xor	si, si
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	call	_z_palette_show_single c, si, 0, large (0 shl 16) or 0
	inc	si

@@more?:
	cmp	si, COLOR_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retf
_z_palette_black	endp
