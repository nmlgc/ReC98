void pascal near bullets_add_regular_raw(void);
void pascal near bullets_add_special_raw(void);

/// Per-spawn state
/// ---------------
/// Has no reason to be global.

extern bool group_fixedspeed;

// "(group_i * bullet_template.delta.spread_angle) is probably too expensive,
// let's rather do an addition for each additional spawned bullet :zunpet:"
extern unsigned char group_i_spread_angle;

extern unsigned char group_i_absolute_angle;
/// ---------------

#define tmpl bullet_template

void near tune_for_easy(void)
{
	switch(tmpl.group) {
	case BG_STACK:
	case BG_STACK_AIMED:
		tmpl.delta.stack_speed.v -= (tmpl.delta.stack_speed.v / 4);
		if(tmpl.count >= 2) {
			tmpl.count--;
		}
		break;

	case BG_SPREAD:
	case BG_SPREAD_AIMED:
		if(tmpl.count >= 3) {
			tmpl.count -= 2;
		}
		break;

	case BG_RANDOM_ANGLE:
	case BG_RING:
	case BG_RING_AIMED:
		tmpl.count /= 2;
		break;
	}
}

void near tune_for_hard(void)
{
	switch(tmpl.group) {
	case BG_SINGLE_AIMED:
		tmpl.group = BG_STACK_AIMED;
		tmpl.count = 2;
		tmpl.delta.stack_speed.set(0.375f);
		break;
	case BG_SINGLE:
		tmpl.group = BG_STACK;
		tmpl.count = 2;
		tmpl.delta.stack_speed.set(0.375f);
		break;

	case BG_STACK:
	case BG_STACK_AIMED:
		tmpl.delta.stack_speed.v += (tmpl.delta.stack_speed.v / 2);
		break;

	case BG_SPREAD:
	case BG_SPREAD_AIMED:
		tmpl.count += 2;
		break;

	case BG_RING:
	case BG_RING_AIMED:
		tmpl.count *= 3;
		tmpl.count /= 2;
		if(tmpl.count > 48) {
			tmpl.count = 48;
		}
		break;

	case BG_RANDOM_ANGLE:
	case BG_RANDOM_ANGLE_AND_SPEED:
		tmpl.count += (tmpl.count / 2);
		break;
	}
}

void near tune_for_lunatic(void)
{
	switch(tmpl.group) {
	case BG_SINGLE_AIMED:
		tmpl.group = BG_SPREAD_AIMED;
		tmpl.count = 3;
		tmpl.delta.spread_angle = +0x06;
		break;
	case BG_SINGLE:
		tmpl.group = BG_SPREAD;
		tmpl.count = 3;
		tmpl.delta.spread_angle = +0x06;
		break;

	case BG_STACK:
	case BG_STACK_AIMED:
		tmpl.delta.stack_speed.v += (tmpl.delta.stack_speed.v / 2);
		tmpl.count++;
		break;

	case BG_SPREAD:
	case BG_SPREAD_AIMED:
		tmpl.count += 4;
		break;

	case BG_RING:
	case BG_RING_AIMED:
		tmpl.count *= 2;
		if(tmpl.count > 48) {
			tmpl.count = 48;
		}
		break;

	case BG_RANDOM_ANGLE:
	case BG_RANDOM_ANGLE_AND_SPEED:
		tmpl.count *= 2;
		break;
	}
}

void near tune_for_playperf(void)
{
	switch(tmpl.group) {
	case BG_STACK:
	case BG_STACK_AIMED:
		if(playperf >= 24) {
			tmpl.count++;
		} else if((playperf <= 6) && (tmpl.count >= 2)) {
			tmpl.count--;
		}
		break;

	case BG_SPREAD:
	case BG_SPREAD_AIMED:
		if(playperf >= 24) {
			tmpl.count += 2;
		} else if((playperf <= 6) && (tmpl.count >= 3)) {
			tmpl.count -= 2;
		}
		break;

	case BG_RING:
	case BG_RING_AIMED:
		if(playperf >= 24) {
			tmpl.count += 4;
		} else if(playperf >= 20) {
			tmpl.count += 2;
		} else if(tmpl.count >= 5) {
			if(playperf <= 10) {
				tmpl.count -= 2;
			}
			if(playperf <= 4) {
				tmpl.count -= 4;
			}
		}
		break;
	}
}

#undef tmpl

void pascal near bullet_template_tune_easy(void)
{
	tune_for_playperf();
	tune_for_easy();
}

void pascal near bullet_template_tune_normal(void)
{
	tune_for_playperf();
}

void pascal near bullet_template_tune_hard(void)
{
	tune_for_playperf();
	tune_for_hard();
}

void pascal near bullet_template_tune_lunatic(void)
{
	tune_for_playperf();
	tune_for_lunatic();
}

void pascal near bullets_add_regular_easy(void)
{
	subpixel_length_8_t speed;
	unsigned char count;

	if(bullet_zap.active) {
		return;
	}
	count = bullet_template.count;
	speed = bullet_template.speed.v;
	bullets_add_regular_raw();
	bullet_template.count = count;
	bullet_template.speed.v = speed;
}

inline void keep_speed_from_being_mutated_when_calling(nearfunc_t_near func) {
	subpixel_length_8_t speed = bullet_template.speed.v;
	func();
	bullet_template.speed.v = speed;
}

void pascal near bullets_add_regular_normal(void)
{
	if(bullet_zap.active) {
		return;
	}
	keep_speed_from_being_mutated_when_calling(bullets_add_regular_raw);
}

void pascal near bullets_add_regular_hard_lunatic(void)
{
	if(bullet_zap.active) {
		return;
	}
	keep_speed_from_being_mutated_when_calling(bullets_add_regular_raw);
}

void pascal near bullets_add_special_easy(void)
{
	if(bullet_zap.active) {
		return;
	}
	keep_speed_from_being_mutated_when_calling(bullets_add_special_raw);
}

void pascal near bullets_add_special_normal(void)
{
	if(bullet_zap.active) {
		return;
	}
	keep_speed_from_being_mutated_when_calling(bullets_add_special_raw);
}

void pascal near bullets_add_special_hard_lunatic(void)
{
	if(bullet_zap.active) {
		return;
	}
	keep_speed_from_being_mutated_when_calling(bullets_add_special_raw);
}

void near bullets_add_regular_fixedspeed(void)
{
	group_fixedspeed = true;
	bullets_add_regular();
	group_fixedspeed = false;
}

void near bullets_add_special_fixedspeed(void)
{
	group_fixedspeed = true;
	bullets_add_special();
	group_fixedspeed = false;
}

#define last_bullet_in_group(group_i) \
	(group_i >= (bullet_template.count - 1))

// Necessary to compile the switch statement in bullet_velocity_and_angle_set()
// to a binary search. Strangely, it's not used for the functions above?
#pragma option -G

// Sets the bullet template's velocity for bullet #[group_i] in the template's
// current group, as well as [group_i_absolute_angle]. Returns true if this
// was the last bullet for this group.
bool16 pascal near bullet_velocity_and_angle_set(int group_i)
{
	int angle = 0x00;
	subpixel_length_8_t speed;
	bool done;

	// Due to this default, invalid group values lead to the spawn functions
	// repeatedly calling this function, until they completely filled the
	// pellet / 16×16 part of the array with identical bullets using the given
	// angle and speed.
	// (Not really a ZUN bug until we can discover a game state where this can
	// actually happen.)
	done = false;
	speed = bullet_template.speed.v;

	switch(bullet_template.group) {
	case BG_SPREAD:
	case BG_SPREAD_AIMED:
		if(bullet_template.count & 1) {
			// Odd-numbered spreads always contain a bullet in the center.
			if(group_i == 0) {
				group_i_spread_angle = 0x00;
				angle = 0x00;
			} else if(group_i & 1) {
				// Symmetric version of even-numbered bullets
				group_i_spread_angle += bullet_template.delta.spread_angle;
				angle = (0x100 - group_i_spread_angle);
			} else {
				angle = group_i_spread_angle;
			}
		} else {
			// Even-numbered spreads are aimed around the 0° point, and
			// therefore need to be shifted by half of the angle. Yes, this
			// whole separate branch, with its whole pointlessly mirrored
			// logic, wouldn't have been necessary, and ZUN could have just
			// added the angle offset after the fact. Or heck, even leaving it
			// at that one branch and using the same code for odd- and
			// even-numbered spreads beyond the first bullet would have been
			// better. (He did the latter in TH05.)
			if(group_i == 0) {
				group_i_spread_angle = (bullet_template.delta.spread_angle / 2);
				angle = group_i_spread_angle;
			} else if(group_i & 1) {
				// Symmetric version of even-numbered bullets
				angle = (0x100 - group_i_spread_angle);
			} else {
				group_i_spread_angle += bullet_template.delta.spread_angle;
				angle = group_i_spread_angle;
			}
		}
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		if(bullet_template.group == BG_SPREAD) {
			goto no_aim;
		}
		goto aim;

	case BG_RING:
		angle = ((group_i * 0x100) / bullet_template.count);
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		goto no_aim;
	case BG_RING_AIMED:
		angle = ((group_i * 0x100) / bullet_template.count);
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		goto aim;

	// All these 16-bit randring operations seem to waste 8 bits of randomness,
	// but each next16 call only advances the pointer by one byte anyway.
	case BG_FORCESINGLE_RANDOM_ANGLE:
		angle = randring2_next16();
		done = true;
		goto no_aim;

	case BG_FORCESINGLE:
	case BG_SINGLE:
		done = true;
		goto no_aim;

	case BG_RANDOM_ANGLE:
		angle = randring2_next16();
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		goto no_aim;
	case BG_RANDOM_ANGLE_AND_SPEED:
		angle = randring2_next16();
		speed += randring2_next8_and_ge_lt_sp(0.0f, 2.0f);
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		goto no_aim;
	case BG_RANDOM_CONSTRAINED_ANGLE_AIMED:
		angle = randring2_next16_and_ge_lt(0x00, 0x20);
		angle -= 0x10;
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		goto aim;

	case BG_FORCESINGLE_AIMED:
	case BG_SINGLE_AIMED:
		done = true;
		goto aim;

	case BG_STACK:
	case BG_STACK_AIMED:
		speed += (bullet_template.delta.stack_speed * group_i);
		if(
			last_bullet_in_group(group_i) ||
			(bullet_template.speed >= to_sp8(10.0f))
		) {
			done = true;
		}
		if(bullet_template.group == BG_STACK) {
			goto no_aim;
		}
		goto aim;
	}
aim:
	angle += iatan2(
		(player_pos.cur.y - bullet_template.origin.y),
		(player_pos.cur.x - bullet_template.origin.x)
	);

no_aim:
	vector2_near(
		bullet_template.velocity, (angle + bullet_template.angle), speed
	);
	group_i_absolute_angle = (angle + bullet_template.angle);
	return done;
}

void near bullet_template_speedtune_for_playperf(void)
{
	bullet_template.speed.v /= 2;
	subpixel_t speed_from_playperf = bullet_template.speed.v;
	speed_from_playperf *= playperf;
	speed_from_playperf /= 16;

	bullet_template.speed.v += speed_from_playperf;
	if(bullet_template.speed > to_sp8(8.0f)) {
		bullet_template.speed.set(8.0f);
	} else if(bullet_template.speed < to_sp8(0.5f)) {
		bullet_template.speed.set(0.5f);
	}
}

unsigned char pascal near bullet_patnum_for_angle(unsigned char angle)
{
	return (
		((angle + (ANGLE_PER_SPRITE / 2) - 1) & (0x80 - 1)) / ANGLE_PER_SPRITE
	);
}

bool near bullet_template_clip(void)
{
	if(
		(bullet_clear_time > 0) &&
		// If a newly spawned bullet wouldn't fully decay during the remaining
		// time, let's simply not spawn it at all? This way, they don't award
		// score points either.
		(bullet_clear_time <= (BMS_DECAY_FRAMES + 1)) // differs from TH05!
	) {
		return true;
	}
	// Also applies to 8×8 pellets, because why wouldn't you combine both
	// cases. #goodcode
	if(!playfield_encloses_point(
		bullet_template.origin, BULLET16_W, BULLET16_H
	)) {
		return true;
	}
	if(overlap_points_wh_fast(
		bullet_template.origin,
		player_pos.cur,
		BULLET_KILLBOX_W,
		BULLET_KILLBOX_H
	)) {
		player_is_hit = true;
		return true;
	}
	if(!group_fixedspeed) {
		bullet_template_speedtune_for_playperf();
	}
	return false;
}

#define bullet_set_spawn_vars(ptr, available, spawn_state, spawn_type) \
	spawn_state = BSS_GRAZEABLE; \
	switch(spawn_type) { \
	case BST_PELLET: \
		ptr = &pellets[PELLET_COUNT - 1]; \
		available = PELLET_COUNT; \
		break; \
	case BST_BULLET16_CLOUD_BACKWARDS: \
		spawn_state = BSS_CLOUD_BACKWARDS; \
		goto bullet16; \
	case BST_BULLET16_CLOUD_FORWARDS: \
		spawn_state = BSS_CLOUD_FORWARDS; \
		goto bullet16; \
	default: \
	bullet16: \
		ptr = &bullets16[BULLET16_COUNT - 1]; \
		available = BULLET16_COUNT; \
		break; \
	}

#define bullet_init_from_template(bullet, group_done, group_i, spawn_state) \
	bullet->age = 0; \
	bullet->pos.cur = bullet_template.origin; \
	bullet->from_group = bullet_template.group; \
	bullet->patnum = bullet_template.patnum; \
	bullet->spawn_state = static_cast<bullet_spawn_state_t>(spawn_state); \
	\
	group_done = bullet_velocity_and_angle_set(group_i); \
	\
	if(bullet_template.patnum >= PAT_BULLET16_D) { \
		bullet->patnum += bullet_patnum_for_angle(group_i_absolute_angle); \
	} \
	\
	bullet->pos.velocity = bullet_template.velocity; \
	bullet->angle = group_i_absolute_angle; \
	bullet->speed_final = bullet_template.speed; \
	bullet->speed_cur = bullet_template.speed; \

void pascal near bullets_add_regular_raw(void)
{
	bullet_t near *bullet;
	int group_i;
	int bullets_available;
	unsigned char move_state;
	bool group_done;
	unsigned char spawn_state; // MODDERS: Should be bullet_spawn_state_t

	if(bullet_template.spawn_type == BST_GATHER_PELLET) {
		gather_template.center = bullet_template.origin;
		gather_template.velocity.set_long(0.0f, 0.0f);
		gather_template.radius.set(GATHER_RADIUS_START);
		gather_template.angle_delta = 0x02;
		gather_template.col = 9;
		gather_template.ring_points = 8;
		bullet_template.spawn_type = BST_PELLET;
		gather_add_bullets();
		return;
	}
	if(bullet_template_clip()) {
		return;
	}

	bullet_set_spawn_vars(
		bullet, bullets_available, spawn_state, bullet_template.spawn_type
	);

	move_state = BMS_REGULAR;
	if(
		(bullet_template.speed < to_sp8(BMS_DECELERATE_THRESHOLD)) ||
		bullet_clear_time
	) {
		if(
			(bullet_template.group != BG_STACK) &&
			(bullet_template.group != BG_STACK_AIMED)
		) {
			move_state = BMS_DECELERATE;
		}
	}

	group_i = 0;
	while(bullets_available > 0) {
		if(bullet->flag == F_FREE) {
			bullet->flag = F_ALIVE;
			bullet->move_state = static_cast<bullet_move_state_t>(move_state);
			bullet->u1.decelerate_time = BMS_DECELERATE_FRAMES;
			bullet->u2.decelerate_speed_delta.v = (
				to_sp8(BMS_DECELERATE_BASE_SPEED) - bullet_template.speed
			);
			bullet_init_from_template(bullet, group_done, group_i, spawn_state);
			if(group_done) {
				break;
			}
			group_i++;
		}
		bullets_available--;
		bullet--;
	}
}

void pascal near bullets_add_special_raw(void)
{
	bullet_t near *bullet;
	int group_i;
	int bullets_available;
	bool group_done;
	bullet_spawn_state_t spawn_state;

	if(bullet_template_clip()) {
		return;
	}

	bullet_set_spawn_vars(
		bullet, bullets_available, spawn_state, bullet_template.spawn_type
	);
	group_i = 0;
	while(bullets_available > 0) {
		if(bullet->flag == F_FREE) {
			bullet->flag = F_ALIVE;
			bullet->move_state = BMS_SPECIAL;
			bullet->special_motion = bullet_template.special_motion;
			bullet->u1.turns_done = 0;
			bullet->u2.angle.v = bullet_template_special_angle.v;
			bullet_init_from_template(bullet, group_done, group_i, spawn_state);
			if(group_done) {
				break;
			}
			group_i++;
		}
		bullets_available--;
		bullet--;
	}
}
