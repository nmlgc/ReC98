	public _vsync_Proc,vsync_Proc
vsync_Proc label dword
_vsync_Proc	dd	0

	public _vsync_Delay,vsync_Delay
vsync_Delay label word
_vsync_Delay	dw	0

	public vsync_OldMask,_vsync_OldMask
_vsync_OldMask label byte
vsync_OldMask	db	0
	EVEN
