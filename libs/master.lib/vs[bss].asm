	public _vsync_Count1,vsync_Count1
vsync_Count1 label word
_vsync_Count1	dw	?
	public _vsync_Count2,vsync_Count2
vsync_Count2 label word
_vsync_Count2	dw	?

	public vsync_OldVect,_vsync_OldVect
_vsync_OldVect label dword
vsync_OldVect	dd	?	; int 0ah ( vsync )
