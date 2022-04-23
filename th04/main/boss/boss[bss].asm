boss_statebyte_t union
	if (GAME eq 5)
		BSB_yumeko_interval_phase4	db ?
		BSB_yumeko_interval_phase7	db ?
	else
		BSB_angle_mirror_y              	db ?
		BSB_bitless_pattern_started     	db ?
		BSB_cluster_angle               	db ?
		BSB_delta_angle_between_rings   	db ?
		BSB_direction                   	db ?
		BSB_gengetsu_started            	db ?
		BSB_flystep_pointreflected_frame	db ?
		BSB_orb_count                   	db ?
		BSB_orb_interval                	db ?
		BSB_origin_offset_x             	db ? ; pixel_t
		BSB_last_frame_with_bits_alive  	db ?
		BSB_pattern_num_prev            	db ?
		BSB_patterns_done               	db ?
		BSB_pellet_stack_angle          	db ?
		BSB_thicklaser_radius           	db ?
		BSB_spread                      	db ?
		BSB_spread_angle                	db ?
		BSB_spread_angle_range          	db ?
		BSB_spread_delta_angle          	db ?
		BSB_spread_interval             	db ?
		BSB_spread_speed                	db ?
		BSB_spread_turns_max            	db ?
		BSB_spin_ring                   	db ?
		BSB_stack                       	db ?
		BSB_stack_left_angle            	db ?
		BSB_stack_right_angle           	db ?
		BSB_stacks_fired                	db ?
		BSB_subpattern_id               	db ?
		BSB_subpattern_num              	db ?
	endif
boss_statebyte_t ends

public _boss_statebyte
_boss_statebyte	db 16 dup (?)
