public DIALOG_BOX_FADE_IN
dialog_box_fade_in	proc near
	push	bp
	mov	bp, sp
	push	si
	mov	vsync_Count1, 0
	xor	si, si
	jmp	short @@tiles_more?
; ---------------------------------------------------------------------------

@@tile_loop:
	call	dialog_box_put pascal, (48 shl 16) or 192, si
	call	dialog_box_put pascal, (80 shl 16) or 320, si
	call	frame_delay pascal, 12
	inc	si

@@tiles_more?:
	cmp	si, DIALOG_BOX_TILE_COUNT
	jl	short @@tile_loop
	pop	si
	pop	bp
	retn
dialog_box_fade_in	endp
