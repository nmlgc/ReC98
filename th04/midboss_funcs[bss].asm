; *_func() functions are "activated" by setting the regular function once the
; midboss battle starts.
public _midboss_active, _midboss_invalidate?
public _midboss_update, _midboss_update_func
public _midboss_render, _midboss_render_func

_midboss_active	db ?
		db ?
_midboss_invalidate?	dw ?
_midboss_update	dd ?
_midboss_render	dw ?
_midboss_update_func	dd ?
_midboss_render_func	dw ?
