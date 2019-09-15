; For increased precision, all values are stored in units of 1/16th of a pixel.
motion_t	struc
	cur      	Point ?
	prev    	Point ?
	velocity	Point ?
motion_t	ends

MOTION_UPDATE_DEF macro instance
	; Returns the new current position in AX (X) and DX (Y).
	;
	; Point pascal near motion_update(motion_t near *motion);
	public _MOTION_UPDATE_&instance
	_motion_update_&instance	proc near
	motion	= word ptr 2

		mov	bx, sp
		mov	bx, ss:[bx+motion]
		mov	ax, word ptr [bx+motion_t.cur]
		mov	word ptr [bx+motion_t.prev], ax
		add	ax, word ptr [bx+motion_t.velocity]
		mov	word ptr [bx+motion_t.cur], ax
		add	bx, Point.y
		mov	dx, word ptr [bx+motion_t.cur]
		mov	word ptr [bx+motion_t.prev], dx
		add	dx, word ptr [bx+motion_t.velocity]
		mov	word ptr [bx+motion_t.cur], dx
		retn	2
	_motion_update_&instance	endp
endm
