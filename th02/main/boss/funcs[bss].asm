; *_func() functions are "activated" by setting the regular function once the
; boss battle starts.
public _boss_bg_render
public _boss_update, _boss_update_func
public _boss_init, _boss_end

_boss_bg_render	dd ?
_boss_update	dd ?
_boss_update_func	dd ?
_boss_init	dd ?
_boss_end	dd ?
