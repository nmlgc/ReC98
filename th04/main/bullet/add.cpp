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
		tmpl.delta.stack_speed -= (tmpl.delta.stack_speed / 4);
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
		tmpl.delta.stack_speed = to_sp(0.375f);
		break;
	case BG_SINGLE:
		tmpl.group = BG_STACK;
		tmpl.count = 2;
		tmpl.delta.stack_speed = to_sp(0.375f);
		break;

	case BG_STACK:
	case BG_STACK_AIMED:
		tmpl.delta.stack_speed += (tmpl.delta.stack_speed / 2);
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
		tmpl.delta.stack_speed += (tmpl.delta.stack_speed / 2);
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
	unsigned char speed;
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
	unsigned char speed = bullet_template.speed.v;
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

#define last_bullet_in_group(group_ii) \
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
	unsigned char speed;
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
			// added the angle offset after the fact...
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
		speed += randring2_next16_and(to_sp(2.0f) - 1);
		if(last_bullet_in_group(group_i)) {
			done = true;
		}
		goto no_aim;
	case BG_RANDOM_CONSTRAINED_ANGLE_AIMED:
		angle = randring2_next16_and(0x1F);
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
