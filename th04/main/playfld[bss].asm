public _scroll_subpixel_line, _scroll_speed, _scroll_line, _scroll_active
_scroll_subpixel_line	db ?
_scroll_speed	db ?
_scroll_line	dw ?
_scroll_last_delta	dw ?
_scroll_active	db ?
	evendata

public _playfield_shake_x, _playfield_shake_y, _playfield_shake_anim_time
_playfield_shake_x	dw ?
_playfield_shake_y	dw ?
_playfield_shake_anim_time	dw ?
	dw ?
