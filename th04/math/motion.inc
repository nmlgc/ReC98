motion_t	struc
	cur      	Point ?
	prev    	Point ?
	velocity	Point ?
motion_t	ends

MOTION_UPDATE_DEF macro instance
	public @PlayfieldMotion@update_seg&instance&$qv
	@PlayfieldMotion@update_seg&instance&$qv proc near
	arg_bx	near, @motion:word

		mov	bx, @motion
		mov	ax, word ptr [bx+motion_t.cur]
		mov	word ptr [bx+motion_t.prev], ax
		add	ax, word ptr [bx+motion_t.velocity]
		mov	word ptr [bx+motion_t.cur], ax
		add	bx, Point.y
		mov	dx, word ptr [bx+motion_t.cur]
		mov	word ptr [bx+motion_t.prev], dx
		add	dx, word ptr [bx+motion_t.velocity]
		mov	word ptr [bx+motion_t.cur], dx
		ret_bx
	@PlayfieldMotion@update_seg&instance&$qv endp
endm
