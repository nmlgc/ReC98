public _bullet_turn_count_max, _bullet_template_turn_angle
_bullet_turn_count_max	db ?
_bullet_template_turn_angle	db ?

public _bullet_zap, _bullet_clear_time
label _bullet_zap_frames byte
label _bullet_zap_active byte
_bullet_zap       	db ?
_bullet_clear_time	db ?

if GAME eq 4
	db ?
endif

public _stage_graze, _graze_score
_stage_graze	dw ?
_graze_score	dw ?
