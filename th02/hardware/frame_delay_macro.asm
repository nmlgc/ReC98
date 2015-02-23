; This needs to be in a separate file because there's a second copy of that
; function in TH02's, TH03's and TH04's OP.EXE, and TASM requires macros to be
; defined *before* they are invoked, even with two-pass assembly.

; int __cdecl frame_delay(int frames)
frame_delay_macro	macro
	local	_loop
@@frames	= word ptr (cPtrSize + 2)

	push	bp
	mov	bp, sp
	mov	vsync_Count1, 0

_loop:
	mov	ax, vsync_Count1
	cmp	ax, [bp+@@frames]
	jb	short _loop
	pop	bp
	ret	2
endm
