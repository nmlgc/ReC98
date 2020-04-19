ENEMY_CLIP_X = 01h
ENEMY_CLIP_Y = 10h

enemy_t	struc
	flag	db ?
	age	db ?
	pos	motion_t <?>
	E_hp	dw ?
	E_score	dw ?
	E_script	dw ?
	E_script_ip	dw ?
	E_speed	db ?
	E_patnum_base	db ?
	E_cur_instr_frame	db ?
	E_loop_i	db ?
	E_angle	db ?
	E_angle_delta	db ?
	E_anim_cels	db ?
	E_anim_frames_per_cel	db ?
	E_anim_cur_cel	db ?
	E_clip	db ?
	E_item	db ?
	E_damaged_this_frame	db ?
	E_can_be_damaged	db ?
	E_autofire	db ?
	E_kills_player_on_collision	db ?
	E_spawned_in_left_half	db ?
	E_autofire_cur_frame	db ?
	E_autofire_interval	db ?
	E_bullet_template	bullet_template_t <?>
	E_subtype	db ?
		db 9 dup(?)
enemy_t	ends
