public @item_splash_dot_render
@item_splash_dot_render	proc near
	mov	cx, ax
	sar	ax, 3
	shl	dx, 6
	add	ax, dx
	shr	dx, 2
	add	ax, dx
	mov	bx, ax
	mov	al, 10000000b
	and	cl, 7
	shr	al, cl
	mov	es:[bx], al
	retn
@item_splash_dot_render	endp
