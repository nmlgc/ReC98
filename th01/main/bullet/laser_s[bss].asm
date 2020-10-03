SHOOTOUT_LASER_COUNT = 10

CShootoutLaser struc
	SL_origin_left	dd ?
	SL_origin_y	dd ?
	SL_ray_start_left	dd ?
	SL_ray_start_y	dd ?
	SL_ray_i_left	dd ?
	SL_ray_i_y	dd ?
	SL_ray_length	dw ?
	SL_ray_moveout_speed	dw ?
	SL_target_x	dw ?
	SL_target_y	dw ?
	SL_unknown	dw ?
		dd ?
	SL_velocity_y	dd ?
	SL_step_y	dd ?
	SL_velocity_x	dd ?
	SL_step_x	dd ?
	SL_ray_extend_speed	dw ?
		dw ?
	SL_alive	dw ?
	SL_age	dw ?
	SL_moveout_at_age	dw ?
	SL_col	db ?
	SL_width_cel	db ?
	SL_damaging	db ?
	SL_id	db ?
		db ?
CShootoutLaser ends

_shootout_lasers	CShootoutLaser SHOOTOUT_LASER_COUNT dup(<?>)
shootout_laser_0	equ <_shootout_lasers[0 * size CShootoutLaser]>
shootout_laser_1	equ <_shootout_lasers[1 * size CShootoutLaser]>
shootout_laser_2	equ <_shootout_lasers[2 * size CShootoutLaser]>
shootout_laser_3	equ <_shootout_lasers[3 * size CShootoutLaser]>
shootout_laser_4	equ <_shootout_lasers[4 * size CShootoutLaser]>
shootout_laser_5	equ <_shootout_lasers[5 * size CShootoutLaser]>
shootout_laser_6	equ <_shootout_lasers[6 * size CShootoutLaser]>
shootout_laser_7	equ <_shootout_lasers[7 * size CShootoutLaser]>
shootout_laser_8	equ <_shootout_lasers[8 * size CShootoutLaser]>
shootout_laser_9	equ <_shootout_lasers[9 * size CShootoutLaser]>
