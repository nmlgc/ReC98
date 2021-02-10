public SCROLL_SUBPIXEL_Y_TO_VRAM_SEG3
scroll_subpixel_y_to_vram_seg3 proc near
arg_bx	near, @sy:word

	mov	ax, @sy
	sar	ax, 4
	cmp	_scroll_active, 0
	jz	short @@lt400?
	add	ax, _scroll_line

@@lt400?:
	cmp	ax, RES_Y
	jl	short @@lt0?
	sub	ax, RES_Y
	jmp	short @@ret

@@lt0?:
	or	ax, ax
	jge	short @@ret
	add	ax, RES_Y

@@ret:
	ret_bx
scroll_subpixel_y_to_vram_seg3 endp


public SCROLL_SUBPIXEL_Y_TO_VRAM_ALWAYS
scroll_subpixel_y_to_vram_always proc near
arg_bx	near, @sy:word

	mov	ax, @sy
	sar	ax, 4
	add	ax, _scroll_line
	cmp	ax, RES_Y
	jl	short @@lt0?
	sub	ax, RES_Y
	jmp	short @@ret

@@lt0?:
	or	ax, ax
	jge	short @@ret
	add	ax, RES_Y

@@ret:
	ret_bx
scroll_subpixel_y_to_vram_always endp
	nop
