area_t	struc
	A_left	dw ?
	A_right	dw ?
	A_top	dw ?
	A_bottom	dw ?
area_t	ends

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

copy16	macro	dst:req, src:req, member:req
	mov	ax,	src.member
	mov	dst.member, ax
endm

copy8	macro	dst:req, src:req, member:req
	mov	al,	src.member
	mov	dst.member, al
endm

area_t__copy	macro	dst:req, src:req
	copy16	dst, src, A_left
	copy16	dst, src, A_right
	copy16	dst, src, A_top
	copy16	dst, src, A_bottom
endm

CBossEntity__ctor	macro	that:req
	mov	that.BE_loading, 0
	mov	that.BE_zero_3, 0
endm

CBossEntity__copy	macro	dst:req, src:req
	copy16	dst, src, BE_cur_left
	copy16	dst, src, BE_cur_top
	copy16	dst, src, BE_prev_left
	copy16	dst, src, BE_prev_top
	copy16	dst, src, BE_vram_w
	copy16	dst, src, BE_h
	area_t__copy	dst.BE_move_clamp, src.BE_move_clamp
	area_t__copy	dst.BE_hitbox_orb, src.BE_hitbox_orb
	copy16	dst, src, BE_prev_delta_y
	copy16	dst, src, BE_prev_delta_x
	copy16	dst, src, BE_bos_image_count
	copy16	dst, src, BE_zero_1
	copy16	dst, src, BE_bos_image
	copy16	dst, src, BE_unknown
	copy16	dst, src, BE_hitbox_orb_inactive
	copy16	dst, src, BE_loading
	copy16	dst, src, BE_move_lock_frame
	copy16	dst, src, BE_zero_2
	copy8 	dst, src, BE_zero_3
	copy8  	dst, src, BE_bos_slot
endm

CBossEntity__bos_load	macro that:req, slot:req, fn:req
	mov that.BE_loading, 1
	call	@CBossEntity@bos_load$qxnxci stdcall, offset that, ds, offset fn, ds, slot
	mov that.BE_loading, 0
endm

CBossEntity__hitbox_set	macro that:req, left:req, top:req, right:req, bottom:req
	mov	that.BE_hitbox_orb.A_left, left
	mov	that.BE_hitbox_orb.A_right, right
	mov	that.BE_hitbox_orb.A_top, top
	mov	that.BE_hitbox_orb.A_bottom, bottom
endm
