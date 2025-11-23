// Common group implementations shared between TH02 and TH03.

// TH01 solved this more elegantly by moving all aimed groups past a certain
// value...
#define to_aim_or_not_to_aim(group, first_aimed) { \
	if(group <= (first_aimed - 1)) { /* ZUN bloat: `< first_aimed` */ \
		goto no_aim; \
	} \
	goto aim; \
}

#define bullet_group_2_3_4_5_spreads_impl(i_angle, done, group, i) \
	case BG_2_SPREAD_WIDE: \
	case BG_2_SPREAD_WIDE_AIMED:	i_angle += 0x03; /* fallthrough */ \
	case BG_2_SPREAD_MEDIUM: \
	case BG_2_SPREAD_MEDIUM_AIMED:	i_angle += 0x03; /* fallthrough */ \
	case BG_2_SPREAD_NARROW: \
	case BG_2_SPREAD_NARROW_AIMED: \
		/**/ if(i == 0) { i_angle = (+0x03 + i_angle); } \
		else if(i == 1) { i_angle = (-0x03 - i_angle); done = true; } \
		to_aim_or_not_to_aim(group, BG_2_SPREAD_NARROW_AIMED); \
	\
	case BG_3_SPREAD_WIDE: \
	case BG_3_SPREAD_WIDE_AIMED:	i_angle += 0x08; /* fallthrough */ \
	case BG_3_SPREAD_MEDIUM: \
	case BG_3_SPREAD_MEDIUM_AIMED:	i_angle += 0x08; /* fallthrough */ \
	case BG_3_SPREAD_NARROW: \
	case BG_3_SPREAD_NARROW_AIMED: \
		/**/ if(i == 0) { i_angle =   0x00; } \
		else if(i == 1) { i_angle = (+0x08 + i_angle); } \
		else if(i == 2) { i_angle = (-0x08 - i_angle); done = true; } \
		to_aim_or_not_to_aim(group, BG_3_SPREAD_NARROW_AIMED); \
	\
	case BG_4_SPREAD_WIDE: \
	case BG_4_SPREAD_WIDE_AIMED:	i_angle += 0x06; /* fallthrough */ \
	case BG_4_SPREAD_MEDIUM: \
	case BG_4_SPREAD_MEDIUM_AIMED:	i_angle += 0x06; /* fallthrough */ \
	case BG_4_SPREAD_NARROW: \
	case BG_4_SPREAD_NARROW_AIMED: \
		/**/ if(i == 0) { i_angle = (+0x03 +  i_angle); } \
		else if(i == 1) { i_angle = (-0x03 -  i_angle); } \
		else if(i == 2) { i_angle = (+0x09 + (i_angle * 3)); } \
		else if(i == 3) { i_angle = (-0x09 - (i_angle * 3)); done = true; } \
		to_aim_or_not_to_aim(group, BG_4_SPREAD_NARROW_AIMED); \
	\
	case BG_5_SPREAD_WIDE: \
	case BG_5_SPREAD_WIDE_AIMED:	i_angle += 0x06; /* fallthrough */ \
	case BG_5_SPREAD_MEDIUM: \
	case BG_5_SPREAD_MEDIUM_AIMED:	i_angle += 0x06; /* fallthrough */ \
	case BG_5_SPREAD_NARROW: \
	case BG_5_SPREAD_NARROW_AIMED: \
		/**/ if(i == 0) { i_angle =   0x00; } \
		else if(i == 1) { i_angle = (+0x06 +  i_angle); } \
		else if(i == 2) { i_angle = (-0x06 -  i_angle); } \
		else if(i == 3) { i_angle = (+0x0C + (i_angle * 2)); } \
		else if(i == 4) { i_angle = (-0x0C - (i_angle * 2)); done = true; } \
		to_aim_or_not_to_aim(group, BG_5_SPREAD_NARROW_AIMED);

#define bullet_groups_shared_between_th02_and_th03_impl( \
	i_angle, done, template_angle, i, count, rng \
) \
	case BG_2_SPREAD_HORIZONTALLY_SYMMETRIC: \
		if(i == 0) { \
			i_angle = 0x00; \
		} else { \
			/** \
			 * ZUN bloat: `bullet.angle = (0x80 - bullet.angle);` would have \
			 * been clearer than using a multiplication to counteract the \
			 * addition in the vector2() call. \
			 */ \
			i_angle = (0x80 - (template_angle * 2)); \
			done = true; \
		} \
		goto no_aim; \
	\
	case BG_1: \
		done = true; \
		goto no_aim; \
	\
	case BG_1_RANDOM_ANGLE: \
		i_angle = rng(); \
		done = true; \
		goto no_aim; \
	\
	case BG_RANDOM_ANGLE: \
		i_angle = rng(); \
		if(i >= count) { \
			done = true; \
		} \
		goto no_aim; \
	\
	case BG_RANDOM_ANGLE_AND_SPEED: \
		i_angle = rng(); \
		speed += randring2_next8_ge_lt_sp(0.0f, 2.0f); \
		if(i >= count) { \
			done = true; \
		} \
		goto no_aim; \

#define bullet_group_ring_impl(i_angle, done, i, count, aim_or_no_aim) { \
	i_angle = ((GAME >= 3) ? ((i * 0x100) / count) : (i * (0x100 / count))); \
	if(i >= (count - 1)) { \
		done = true; \
	} \
	goto aim_or_no_aim; \
}
