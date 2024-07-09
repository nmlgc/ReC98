public _bullet_special_motion, _bullet_template_special_angle
_bullet_special_motion_turns_max	label byte
_bullet_special_motion_speed_delta	label byte
_bullet_special_motion	db ?
_bullet_template_special_angle 	bullet_special_angle_t <?>

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
