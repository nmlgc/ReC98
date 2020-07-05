/// Constants
/// ---------
// Can't declare these as `static const` variables, because that would break
// compile-time Subpixel arithmetic
#define PELLET_LEFT_MIN (PLAYFIELD_LEFT)
#define PELLET_LEFT_MAX (PLAYFIELD_RIGHT - PELLET_W)
#define PELLET_TOP_MIN (PLAYFIELD_TOP)
#define PELLET_TOP_MAX (PLAYFIELD_BOTTOM)

#define PELLET_BOUNCE_TOP_MIN (PLAYFIELD_TOP + ((PELLET_H / 4) * 3))

#define PELLET_VELOCITY_MAX to_sp(8.0f)

static const unsigned int PELLET_DESTROY_SCORE = 10;
static const int PELLET_DECAY_FRAMES = 20;
static const int PELLET_DECAY_CELS = 2;
/// ---------

/// Globals
/// -------
pellet_t near *pellet_cur;
/// -------

CPellets::CPellets(void)
{
	int i;

	#define p pellet_cur
	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		p->moving = false;
		p->not_rendered = false;
	}
	#undef p

	alive_count = 0;
	for(i = 0; i < sizeof(unknown_zero) / sizeof(unknown_zero[0]); i++) {
		unknown_zero[i] = 0;
	}
}

void vector2_to_player_from(
	int x, int y, int &ret_x, int &ret_y, int length, unsigned char plus_angle
)
{
	plus_angle = iatan2(
		(player_center_y - y),
		((player_left + (PLAYER_W / 2) - (PELLET_W / 2)) - x)
	) + plus_angle;
	ret_x = (static_cast<long>(length) * Cos8(plus_angle)) >> 8;
	ret_y = (static_cast<long>(length) * Sin8(plus_angle)) >> 8;
}

// Sets the velocity for pellet #[i] in the given [pattern]. Returns true if
// this was the last pellet for this pattern.
bool16 pattern_velocity_set(
	Subpixel &ret_x,
	Subpixel &ret_y,
	pellet_pattern_t pattern,
	subpixel_t speed,
	int &i,
	int pellet_left,
	int pellet_top
)
{
	// ZUN bug: Due to this default, add_pattern() ends up repeatedly calling
	// this function for [pattern] values not covered by the switch below,
	// until it iterated over the entire pellet array...
	bool16 done = false;
	unsigned char angle = 0x00;
	unsigned char spread_delta = 0x00;

	#define to_aim_or_not_to_aim() \
		if(pattern >= PP_AIMED_SPREADS) { \
			goto aim; \
		} \
		/* Static pattern; add a 90° angle, so that 0° points downwards */ \
		angle += 0x40; \
		goto no_aim;

	switch(pattern) {
	case PP_1:
		ret_y.v = speed;
		ret_x = 0.0f;
		done = true;
		break;
	case PP_1_AIMED:
		vector2_between(
			pellet_left,
			pellet_top,
			player_left + 8,
			player_center_y,
			ret_x.v,
			ret_y.v,
			speed
		);
		done = true;
		break;

	case PP_2_SPREAD_WIDE:
	case PP_2_SPREAD_WIDE_AIMED:	spread_delta = 0x08;	// fallthrough
	case PP_2_SPREAD_NARROW:
	case PP_2_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle = (+0x04 + spread_delta); }
		else if(i == 1) { angle = (-0x04 - spread_delta); done = true; }
		to_aim_or_not_to_aim();

	case PP_3_SPREAD_WIDE:
	case PP_3_SPREAD_WIDE_AIMED:	spread_delta = 0x05;	// fallthrough
	case PP_3_SPREAD_NARROW:
	case PP_3_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle =   0x00; }
		else if(i == 1) { angle = (+0x04 + spread_delta); }
		else if(i == 2) { angle = (-0x04 - spread_delta); done = true; }
		to_aim_or_not_to_aim();

	case PP_4_SPREAD_WIDE:
	case PP_4_SPREAD_WIDE_AIMED:	spread_delta = 0x04;	// fallthrough
	case PP_4_SPREAD_NARROW:
	case PP_4_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle = (+0x04 +  spread_delta); }
		else if(i == 1) { angle = (-0x04 -  spread_delta); }
		else if(i == 2) { angle = (+0x0C + (spread_delta * 3)); }
		else if(i == 3) { angle = (-0x0C - (spread_delta * 3)); done = true; }
		to_aim_or_not_to_aim();

	case PP_5_SPREAD_WIDE:
	case PP_5_SPREAD_WIDE_AIMED:	spread_delta = 0x04;	// fallthrough
	case PP_5_SPREAD_NARROW:
	case PP_5_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle =   0x00; }
		else if(i == 1) { angle = (+0x04 +  spread_delta); }
		else if(i == 2) { angle = (-0x04 -  spread_delta); }
		else if(i == 3) { angle = (+0x08 + (spread_delta * 2)); }
		else if(i == 4) { angle = (-0x08 - (spread_delta * 2)); done = true; }
		to_aim_or_not_to_aim();

	case PP_1_RANDOM_NARROW_AIMED:
		angle = ((rand() & 0x0F) - 0x07);
		done = true;
		goto aim;

	case PP_1_RANDOM_WIDE:
		angle = ((rand() & 0x3F) + 0x20);
		done = true;
		goto no_aim;

	aim:
		vector2_to_player_from(
			pellet_left, pellet_top, ret_x.v, ret_y.v, speed, angle
		);
		break;

	no_aim:
		vector2(ret_x.v, ret_y.v, speed, angle);
		break;
	}
	i++;
	return done;
}

inline subpixel_t base_speed_for_rank(void)
{
	return
		(static_cast<int>(rank) == RANK_EASY) ? to_sp(0.0f) :
		(static_cast<int>(rank) == RANK_NORMAL) ? to_sp(0.375f) :
		(static_cast<int>(rank) == RANK_HARD) ? to_sp(0.75f) :
		to_sp(1.125f);
}

#define speed_set(speed) \
	speed += base_speed_for_rank(); \
	speed += ((resident->pellet_speed * speed) / to_sp(2.5f)); \
	if(speed < to_sp(1.0f)) { \
		speed = to_sp(1.0f); \
	}

#define pellet_init(pellet, left, top, pattern) \
	pellet->decay_frame = 0; \
	pellet->cur_left.v = TO_SP(left); \
	pellet->cur_top = top; \
	pellet->cloud_left = left; \
	pellet->cloud_top = top; \
	if(spawn_with_cloud) { \
		pellet->cloud_frame = 1; \
	} else { \
		pellet->moving = true; \
	} \
	pellet->from_pattern = pattern;

void CPellets::add_pattern(
	int left, int top, pellet_pattern_t pattern, subpixel_t speed
)
{
	int i;
	int pattern_i = 0;
	int pattern_done;
	Subpixel vel_x;
	Subpixel vel_y;

	// Should be >=, but yeah, it's just an inconsequential oversight.
	if(alive_count > PELLET_COUNT) {
		return;
	}
	if(
		(left >= PLAYFIELD_RIGHT) ||
		(top < (PLAYFIELD_TOP - PELLET_H)) ||
		(left < (PLAYFIELD_LEFT - PELLET_W)) ||
		(top > PLAYFIELD_BOTTOM)
	) {
		return;
	}
	speed_set(speed);

	#define p pellet_cur
	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->moving == true) {
			continue;
		}
		if(p->cloud_frame) {
			continue;
		}
		pellet_init(p, left, top, pattern);
		p->prev_left.v = -1;
		p->age = 0;
		alive_count++;
		pattern_done = pattern_velocity_set(
			vel_x, vel_y, pattern, speed, pattern_i, left, top
		);
		p->velocity.x.v = vel_x.v;
		p->velocity.y.v = vel_y.v;
		if(pattern_done == true) {
			return;
		}
	}
	#undef p
}

void CPellets::add_single(
	int left,
	int top,
	int angle,
	subpixel_t speed_base,
	pellet_motion_t motion_type,
	subpixel_t speed_for_motion_fixed,
	int spin_center_x,
	int spin_center_y
)
{
	int i;
	Subpixel vel_x;
	Subpixel vel_y;

	// Should be >=, but yeah, it's just an inconsequential oversight.
	if(alive_count > PELLET_COUNT) {
		return;
	}
	speed_set(speed_base);

	#define p pellet_cur
	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->moving == true) {
			continue;
		}
		if(p->cloud_frame) {
			continue;
		}
		pellet_init(p, left, top, PP_NONE);
		p->motion_type = motion_type;
		p->prev_left.v = -1;
		p->age = 0;
		alive_count++;
		p->spin_center.x.v = TO_SP(spin_center_x);
		p->spin_center.y = spin_center_y;
		if(motion_type == PM_SPIN) {
			vector2(vel_x.v, vel_y.v, speed_for_motion_fixed, angle);
			p->spin_velocity.x.v = vel_x.v;
			p->spin_velocity.y.v = vel_y.v;
			p->angle = iatan2(
				(p->cur_top - p->spin_center.y),
				(p->cur_left - p->spin_center.x)
			);
		}
		vector2(vel_x.v, vel_y.v, speed_base, angle);
		p->speed.v = speed_for_motion_fixed;
		p->velocity.x.v = vel_x.v;
		p->velocity.y.v = vel_y.v;
		return;
	}
	#undef p
}

void CPellets::motion_type_apply_for_cur(void)
{
	#define p pellet_cur
	Subpixel velocity_to_player_x;
	Subpixel velocity_to_player_y;

	switch(p->motion_type) {
	case PM_GRAVITY:
		p->velocity.y.v += p->speed.v;
		break;
	case PM_SLING_AIMED:
		if(p->sling_direction == PSD_NONE) {
			p->sling_direction = static_cast<pellet_sling_direction_t>(
				(rand() & 1) + PSD_CLOCKWISE
			);
		}
		if(p->sling_direction == PSD_CLOCKWISE) {
			vector2(p->velocity.x.v, p->velocity.y.v, p->speed.v, p->angle);
		} else /* PSD_COUNTERCLOCKWISE */ {
			vector2(p->velocity.y.v, p->velocity.x.v, p->speed.v, p->angle);
		}
		p->angle += PELLET_SLING_DELTA_ANGLE;
		if(p->angle > 0x100) {
			vector2_between(
				p->cur_left.to_screen(),
				p->cur_top.to_screen(),
				player_left + 8,
				player_center_y,
				p->velocity.x.v,
				p->velocity.y.v,
				p->speed.v
			);
			p->from_pattern = PP_1_AIMED;
			p->angle = 0x00;
		}
		break;
	case PM_BOUNCE_FROM_TOP_THEN_GRAVITY:
		// Wow... Three ZUN bugs in one single if() expression.
		// 1)
		// 2) Pellets are clipped at both the left (1) and the right (2)
		//    edge of the playfield at those exact same coordinates,
		//    *before* this code gets to run. Thus, they won't ever
		//    bounce from those two sides here.
		// 3) Comparing screen-space coordinates to subpixels. What's a
		//    type system? :zunpet:
		if(
			(p->cur_left.v <= PELLET_LEFT_MIN)
			|| (p->cur_left.to_screen() >= to_sp(PELLET_LEFT_MAX))
			|| (p->cur_top.v <= to_sp(PELLET_BOUNCE_TOP_MIN))
		) {
			p->velocity.x.v = -p->velocity.x.v;
			p->velocity.y = 0.0f;
			p->motion_type = PM_GRAVITY;
			// Nope, this doesn't help.
			if(p->cur_left.v <= to_sp(PELLET_LEFT_MIN)) {
				p->cur_left = (PELLET_LEFT_MIN + 1.0f);
			}
			if(p->cur_left.v >= to_sp(PELLET_LEFT_MAX)) {
				p->cur_left = (PELLET_LEFT_MAX - 1.0f);
			}
			if(p->cur_top.v <= to_sp(PELLET_TOP_MIN)) {
				p->cur_top = (PELLET_TOP_MIN + 1.0f);
			}
		}
		break;
	case PM_FALL_STRAIGHT_FROM_TOP_THEN_NORMAL:
		if(p->cur_top.to_screen() <= PELLET_BOUNCE_TOP_MIN) {
			p->velocity.x = 0.0f;
			p->velocity.y.v = p->speed.v;
			p->motion_type = PM_NORMAL;
			if(p->cur_top.to_screen() <= PLAYFIELD_TOP) {
				p->cur_top = (PLAYFIELD_TOP + 1.0f);
			}
		}
		break;
	case PM_SPIN:
		#define to_spin_circle(coord) \
			((static_cast<long>(coord) * PELLET_SPIN_CIRCLE_RADIUS) >> 8)
		p->cur_left.v = (to_spin_circle(Cos8(p->angle)) + p->spin_center.x.v);
		p->cur_top.v = (to_spin_circle(Sin8(p->angle)) + p->spin_center.y.v);
		p->spin_center.x.v += p->spin_velocity.x.v;
		p->spin_center.y.v += p->spin_velocity.y.v;
		p->velocity.x = 0.0f;
		p->velocity.y = 0.0f;
		p->angle += PELLET_SPIN_DELTA_ANGLE;
		#undef to_spin_circle
		break;
	case PM_CHASE:
		vector2_between(
			p->cur_left.to_screen(),
			p->cur_top.to_screen(),
			player_left + 8,
			player_center_y,
			velocity_to_player_x.v,
			velocity_to_player_y.v,
			p->speed.v
		);
		if(p->cur_top.v < PELLET_CHASE_TOP_MAX) {
			#define chase(cur, target) \
				(cur > target) ? to_sp(-0.0625f) : \
				(cur < target) ? to_sp( 0.0625f) : \
				to_sp(0.0f);
			p->velocity.x.v += chase(p->velocity.x.v, velocity_to_player_x.v);
			p->velocity.y.v += chase(p->velocity.y.v, velocity_to_player_y.v);
			#undef chase
		}
		break;
	}
	#undef p
}

void pellet_put(int left, int top, int cel)
{
	// Some `__asm` statements here look like they could be expressed using
	// register pseudovariables. However, TCC would then use a different
	// instruction than the one in ZUN's original binary.
	_ES = SEG_PLANE_B;

	_AX = (left >> 3);
	_DX = top;
	_DX <<= 6;
	__asm add	ax, dx;
	_DX >>= 2;
	__asm add	ax, dx;
	__asm mov	di, ax;

	_AX = (left & 7) << 4;
	_BX = cel;
	_BX <<= 7;
	__asm add	ax, bx;
	_AX += reinterpret_cast<uint16_t>(sPELLET);

	__asm mov	si, ax;
	_CX = PELLET_H;
	put_loop: {
		__asm movsw
		_DI += (ROW_SIZE - sizeof(dots16_t));
		if(static_cast<int16_t>(_DI) >= PLANE_SIZE) {
			return;
		}
	}
	__asm loop	put_loop;
}

void pellet_render(int left, int top, int cel)
{
	grcg_setcolor_rmw(7);
	pellet_put(left, top, cel);
	grcg_off();
}

inline bool16 overlaps_shot(int pellet_left, int pellet_top, int i)
{
	return overlap_lt_gt(
		pellet_left, pellet_top, PELLET_W, PELLET_H,
		Shots.left[i], Shots.top[i], SHOT_W, SHOT_H
	);
}

inline bool16 overlaps_orb(int pellet_left, int pellet_top)
{
	return overlap_lt_gt(
		pellet_left, pellet_top, PELLET_W, PELLET_H,
		orb_cur_left, orb_cur_top, ORB_W, ORB_H
	);
}

bool16 CPellets::visible_after_hittests_for_cur(int pellet_left, int pellet_top)
{
	#define p pellet_cur
	// Well, well. Since ZUN uses this super sloppy 16x8 rectangle to unblit
	// 8x8 pellets, there's now the (completely unnecessary) possibility of
	// accidentally unblitting parts of a sprite that was previously drawn
	// into the 8 pixels right of a pellet.
	// "Oh, I know! Let's test the entire 16 pixels, and in case we got an
	// entity there, we simply make the *pellet* invisible for this frame!
	// Then we don't even have to unblit it later! :tannedcirno:"
	//
	// Except that the only entity type this is done for are the player shots,
	// and also only for 3 basically random ones? Note that indices 0, 1, and
	// 2 in the shot array don't necessarily have to be the 3 ones that
	// spawned last... although given the sheer ~quality~ of all this code, it
	// might very well have been intended like that? Or maybe this code was
	// written when the intended SHOT_COUNT was still 3. Urgh.
	//
	// Also note that the code is still testing the left 8 pixels that make up
	// the actual pellet, despite already having hit-tested them with a call
	// to CShots::hittest_pellet() before. Turns out that the check there
	// (which actually does affect gameplay) is more precise and excludes the
	// transparent edges of the shot sprite, which the blitting-related check
	// here shouldn't do. (This entire paragraph would have been unnecessary
	// if this code had just tested all 16 pixels at once, rather than having
	// this weird, bloated, and slow split into two 8-pixel checks.)
	//
	// This is certainly a contender for the most stupid piece of code in this
	// game. What about the player sprite, the Orb (for which we *do* the same
	// test, but always return `true` regardless), or, heck, *other pellets*?
	// It's just so hilarious how these mitigations don't help fixing the
	// underlying problem, at all.
	for(int i = 0; i < 3; i++) {
		if(
			(Shots.is_moving(i) == true) &&
			(overlaps_shot(pellet_left, pellet_top, i) == true)
		) {
			return false;
		} else if(overlaps_shot((pellet_left + 8), pellet_top, i) == true) {
			return false;
		}
	}
	if(p->decay_frame) {
		return true;
	}
	if(
		(overlaps_orb(pellet_left, pellet_top) == true) ||
		(overlaps_orb((pellet_left + 8), pellet_top) == true)
	) {
		// Hey, let's also process a collision! Why not?! This is one magical
		// Orb, after all. Even collides with pellets it doesn't actually hit.
		p->velocity.y.v >>= 1;
		p->velocity.x.v >>= 1;
		p->decay_frame = 1;
		pellet_destroy_score_delta += PELLET_DESTROY_SCORE;
		return true;
	}
	if((player_deflecting == true) && (overlap_lt_gt(
		pellet_left,
		pellet_top,
		PELLET_W,
		PELLET_H,
		(player_left - PELLET_W),
		(player_top - (PELLET_H * 2)),
		(PLAYER_W + (PELLET_W * 2)),
		(PLAYER_H + (PELLET_H * 2))
	) == true)) {
		char deflect_angle;
		if(p->cur_left.to_screen() <= (player_left + 12)) {
			deflect_angle = 0x80;
		} else {
			deflect_angle = 0x00;
		}
		vector2(p->velocity.x.v, p->velocity.y.v, to_sp(8.0f), deflect_angle);
		if(!p->from_pattern) {
			p->motion_type = PM_NORMAL;
		}
		// Yes, deflected pellets aren't rendered on the frames they're
		// deflected on!
		return false;
	}
	return true;
	#undef p
}

void CPellets::decay_tick_for_cur(void)
{
	#define p pellet_cur
	p->decay_frame++;
	if(p->decay_frame > (PELLET_DECAY_FRAMES + 1)) {
		p->decay_frame = 0;
		p->moving = false;
		alive_count--;
	}
	#undef p
}

void CPellets::unput_update_render(void)
{
	int i;

	interlace_field = (interlace_field == false) ? true : false;
	/* TODO: Replace with the decompiled call
	 * clouds_unput_update_render();
	 * once that function is part of this translation unit */
	__asm {
		push	word ptr [bp+8];
		push	bx;
		nop;
		push	cs;
		db  	0xE8, 0x2A, 0x04;
		add 	sp, 4;
	}

	#define p pellet_cur
	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->moving == false) {
			continue;
		}
		if(!pellet_interlace || (interlace_field == (i % 2))) {
			if(p->not_rendered == false && (p->prev_left.v != -1)) {
				p->sloppy_wide_unput();
			}
		}
		if(p->from_pattern == PP_NONE && p->motion_type) {
			motion_type_apply_for_cur();
		}
		if(p->velocity.y.v > PELLET_VELOCITY_MAX) {
			p->velocity.y.v = PELLET_VELOCITY_MAX;
		}
		if(p->velocity.x.v > PELLET_VELOCITY_MAX) {
			p->velocity.x.v = PELLET_VELOCITY_MAX;
		}
		p->cur_top.v += p->velocity.y.v;
		p->cur_left.v += p->velocity.x.v;

		// Shot<->Pellet hit testing
		if(p->decay_frame == 0) {
			if(Shots.hittest_pellet(
				p->cur_left.to_screen(), p->cur_top.to_screen()
			)) {
				p->decay_frame = 0;
				p->moving = false;
				alive_count--;
				p->sloppy_wide_unput();
			}
		}
		// Clipping
		if(
			p->cur_top.v >= to_sp(PELLET_TOP_MAX) ||
			p->cur_top.v < to_sp(PELLET_TOP_MIN) ||
			p->cur_left.v >= to_sp(PELLET_LEFT_MAX) ||
			p->cur_left.v <= to_sp(PELLET_LEFT_MIN)
		) {
			p->moving = false;
			alive_count--;
			p->decay_frame = 0;
			p->sloppy_wide_unput();
		}
	}

	Shots.unput_update_render();

	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->moving == false) {
			continue;
		}
		if(!pellet_interlace || ((interlace_field & 1) == (i % 2))) {
			if(visible_after_hittests_for_cur(
				p->cur_left.to_screen(), p->cur_top.to_screen()
			) == true) {
				if(p->not_rendered == true) {
					p->not_rendered = false;
				}
				#define render pellet_render
				#define decay_frames_for_cel(cel) \
					((PELLET_DECAY_FRAMES / PELLET_DECAY_CELS) * cel)
				if(p->decay_frame == 0) {
					render(p->cur_left.to_screen(), p->cur_top.to_screen(), 0);
				} else if(p->decay_frame <= decay_frames_for_cel(1)) {
					render(p->cur_left.to_screen(), p->cur_top.to_screen(), 1);
				}  else if(p->decay_frame < decay_frames_for_cel(2)) {
					render(p->cur_left.to_screen(), p->cur_top.to_screen(), 2);
				}
				#undef decay_frames_for_cel
				#undef render
			} else {
				p->not_rendered = true;
			}
			p->prev_left.v = p->cur_left.v;
			p->prev_top.v = p->cur_top.v;
		}
		p->age++;
		if(p->decay_frame) {
			decay_tick_for_cur();
			continue;
		}
		/* TODO: Replace with the decompiled call
		 * if(hittest_player_for_cur())
		 * once that function is part of this translation unit */
		__asm {
			db 0x66, 0xFF, 0x76, 0x06, 0x90, 0x0E, 0xE8, 0x6D, 0x01; add sp, 4;
		}
		if(_AX) {
			if(p->not_rendered == false) {
				p->sloppy_wide_unput();
			}
			p->moving = false;
			alive_count--;
			p->decay_frame = 0;
		}
	}
	#undef p
}
