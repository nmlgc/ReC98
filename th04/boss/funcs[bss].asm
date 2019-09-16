; *_func() functions are "activated" by setting the regular function once the
; boss battle starts.
public _boss_update, _boss_update_func
public _boss_bg_render_func, _boss_fg_render, _boss_fg_render_func

_boss_update	dd ?
_boss_fg_render	dw ?
if GAME eq 5
	public _boss_custombullets_render
	_boss_custombullets_render	dw ?
endif
_boss_bg_render_func	dw ?
_boss_update_func	dd ?
_boss_fg_render_func	dw ?
