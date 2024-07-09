public SCROLL_SUBPIXEL_Y_TO_VRAM_SEG1
scroll_subpixel_y_to_vram_seg1 proc near
arg_bx	near, @sy:word

	mov	ax, @sy
	sar	ax, 4
	cmp	_scroll_active, 0
	jz	short @@lt0?
	add	ax, _scroll_line

@@lt0?:
	or	ax, ax
	jge	short @@lt400?
	add	ax, RES_Y
	jmp	short @@ret

@@lt400?:
	cmp	ax, RES_Y
	jl	short @@ret
	sub	ax, RES_Y

@@ret:
	ret_bx
scroll_subpixel_y_to_vram_seg1 endp
