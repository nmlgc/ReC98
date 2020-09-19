public FRAME_DELAY
frame_delay	proc
@@frames	= word ptr (cPtrSize + 2)

	mov	bx, sp
	mov	bx, ss:[bx+4]
	mov	vsync_Count1, 0

@@loop:
	cmp	vsync_Count1, bx
	jb	short @@loop
	ret	2
frame_delay	endp
