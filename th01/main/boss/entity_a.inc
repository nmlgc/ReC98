CBossEntity	struc
	BE_cur_left	dw ?
	BE_cur_top	dw ?
	BE_prev_left	dw ?
	BE_prev_top	dw ?
	BE_vram_w	dw ?
	BE_h	dw ?
	BE_move_clamp	area_t <?>
	BE_hitbox_orb	area_t <?>
	BE_prev_delta_y	dw ?
	BE_prev_delta_x	dw ?
	BE_bos_image_count	dw ?
	BE_zero_1	dw ?
	BE_bos_image	dw ?
	BE_unknown	dw ?
	BE_hitbox_orb_inactive	dw ?
	BE_loading	dw ?
	BE_move_lock_frame	dw ?
	BE_zero_2	dw ?
	BE_zero_3	db ?
	BE_bos_slot	db ?
CBossEntity	ends

CBossEntity__ctor	macro	that:req
	mov	that.BE_loading, 0
	mov	that.BE_zero_3, 0
endm
