; Tries to blit the entire laser, but fails hilariously.
shootout_laser_unput_and_reset_broken macro @@slot:req
	local @@skip

	mov	bx, @@slot
	imul	bx, size CShootoutLaser
	cmp	_shootout_lasers[bx].SL_alive, 0
	jz	short @@skip

	; Two ZUN bugs here:
	;
	; 1) Surely this should have unblitted from the start to the end of the
	;    ray instead? Except that CShootoutLaser doesn't explicitly store that
	;    end point... so the best alternative would be the target point. But
	;    given that CShootoutLaser has its own blitting routine, who knows how
	;    accurate that actually is?
	;
	; 2) graph_r_line_unput() takes screen_x_t and vram_y_t, not LaserPixels
	;    truncated to 16-bits :zunpet: As a result, these calls effectively
	;    unblit random 32-bit pixel chunks.
	;
	; Not that it matters a lot. This function is only called at the end of a
	; boss battle, immediately before transitioning to the tally screen.
	; Still, not doing anything would have been the better choice.

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
