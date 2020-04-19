enemy_t	struc
	flag	db ?
	age	db ?
	pos	motion_t <?>
	E_patnum_base	db ?
		db ?
	E_hp	dw ?
		db ?
		db ?
	E_score	dw ?
	E_script	dw ?
	E_script_ip	dw ?
	E_cur_instr_frame	db ?
	E_loop_i	db ?
	E_speed	dw ?
	E_angle	db ?
	E_angle_delta	db ?
	E_clip_x	db ?
	E_clip_y	db ?
		db ?
	E_item	db ?
	E_damaged_this_frame	db ?
	E_anim_cels	db ?
	E_anim_frames_per_cel	db ?
	E_anim_cur_cel	db ?
	E_can_be_damaged	db ?
	E_autofire	db ?
	E_kills_player_on_collision	db ?
	E_spawned_in_left_half	db ?
	E_bullet_template	bullet_template_t <?>
	E_autofire_cur_frame	db ?
	E_autofire_interval	db ?
enemy_t	ends
