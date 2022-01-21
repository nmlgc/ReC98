; Tries to blit the entire laser, but fails hilariously.
shootout_laser_unput_and_reset_broken macro @@slot:req
	local @@skip

	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	cmp	_shootout_lasers[bx].SL_alive, 0
	jz	short @@skip
	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	push	word ptr _shootout_lasers[bx].SL_origin_y
	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	push	word ptr _shootout_lasers[bx].SL_origin_left
	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	push	word ptr _shootout_lasers[bx].SL_ray_start_y
	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	push	word ptr _shootout_lasers[bx].SL_ray_start_left
	call	_graph_r_line_unput
	add	sp, 8
	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	mov	_shootout_lasers[bx].SL_alive, 0
	jmp	short @@skip

@@skip:
endm
