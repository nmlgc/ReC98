motion_t	struc
	cur      	Point ?
	prev    	Point ?
	velocity	Point ?
motion_t	ends

MOTION_UPDATE_DEF macro instance
	public MOTION_UPDATE_SEG&instance
	motion_update_seg&instance proc near
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
	motion_update_seg&instance endp
endm
