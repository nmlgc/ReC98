public _bullet_turn_count_max, _bullet_template_turn_angle
_bullet_turn_count_max	db ?
_bullet_template_turn_angle	db ?

public _bullet_clear_trigger, _bullet_clear_time
; Set to non-zero to clear all on-screen bullets, giving out bonus points for
; each one.
_bullet_clear_trigger	db ?
; # of frames left during which all on-screen bullets should decay.
; Does not give a point bonus when used on its own. (unsigned)
_bullet_clear_time   	db ?
