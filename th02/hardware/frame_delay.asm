; int pascal frame_delay(int frames)
public FRAME_DELAY
frame_delay proc
	arg @@frames:word

	push	bp
	mov	bp, sp
	mov	vsync_Count1, 0

@@loop:
	mov	ax, vsync_Count1
	cmp	ax, @@frames
	jb	short @@loop
	pop	bp
	ret	2
frame_delay endp
