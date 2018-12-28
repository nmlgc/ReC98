public _scroll_subpixel_line, _scroll_speed, _scroll_line, _scroll_active
; [scroll_line] is advanced by 1 for every 16 units.
_scroll_subpixel_line	db ?
; Amount to add to [_scroll_subpixel_line] every frame.
_scroll_speed	db ?
; Current line at the top of VRAM.
_scroll_line	dw ?
; Amount of 1/16th-pixel units scrolled in the last frame.
_scroll_last_delta	dw ?
; If set to 0, the game assumes that the background is drawn by someone else!
_scroll_active	db ?
		db ?
