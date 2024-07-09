// State
// -----

static int orb_frames_outside_portal = 0; // unused

screen_x_t orb_cur_left;
screen_y_t orb_cur_top;
screen_x_t orb_prev_left = ORB_LEFT_START;
screen_y_t orb_prev_top = ORB_TOP_START;
bool16 orb_in_portal = false;
int orb_rotation_frame = 0;
double orb_force = 0.0;
int orb_force_frame;
orb_velocity_x_t orb_velocity_x = OVX_0;
double orb_velocity_y = 0.0;
// -----

#define COEFFICIENT_OF_RESTITUTION 0.78

inline double gravity_for(const double& force) {
	return ((orb_force_frame / 5) + orb_force);
}

pixel_t orb_velocity_y_update(void)
{
	orb_velocity_y = gravity_for(orb_force);
	if(orb_velocity_y > 16.0f) {
		orb_velocity_y = 16.0f;
	} else if(orb_velocity_y < -16.0) {
		orb_velocity_y = -16.0;
	}
	return gravity_for(orb_force);
}

#define random_velocity_change(val, new_velocity) \
	if(orb_force_frame < 17) { \
		if((irand() % 50) == val) { \
			orb_velocity_x = new_velocity; \
		} \
	}

void orb_force_new(double immediate, orb_force_t force)
{
	if(force == OF_BOUNCE_FROM_SURFACE) {
		orb_force = (-orb_velocity_y * COEFFICIENT_OF_RESTITUTION);
		if(orb_velocity_x == OVX_0) {
			random_velocity_change(0, OVX_4_LEFT);
			random_velocity_change(1, OVX_4_RIGHT);
		}
	}
	if(force == OF_BOUNCE_FROM_TOP) {
		orb_force = ((-orb_velocity_y) - (orb_force_frame / 4));
	}
	if(force == OF_SHOT) {
		orb_force = (-10.0 + (orb_velocity_y / 2.0));
	}
	if(force == OF_IMMEDIATE) {
		orb_force = immediate;
	}
	orb_force_frame = 0;
}

void orb_move_x(orb_velocity_x_t velocity_x)
{
	switch(velocity_x) {
	case  OVX_4_LEFT:	orb_cur_left -= 4;	break;
	case OVX_4_RIGHT:	orb_cur_left += 4;	break;
	case  OVX_8_LEFT:	orb_cur_left -= 8;	break;
	case OVX_8_RIGHT:	orb_cur_left += 8;	break;
	}
	if(orb_cur_left <= ORB_LEFT_MIN) {
		if(orb_velocity_x == OVX_4_LEFT) {
			orb_velocity_x = OVX_4_RIGHT;
		} else if(orb_velocity_x == OVX_8_LEFT) {
			orb_velocity_x = OVX_8_RIGHT;
		}
	}
	if(orb_cur_left >= ORB_LEFT_MAX) {
		if(orb_velocity_x == OVX_4_RIGHT) {
			orb_velocity_x = OVX_4_LEFT;
		} else if(orb_velocity_x == OVX_8_RIGHT) {
			orb_velocity_x = OVX_8_LEFT;
		}
	}
}

inline main_ptn_id_t orb_anim_cel(void) {
	return static_cast<main_ptn_id_t>(
		PTN_ORB + (orb_rotation_frame / ORB_FRAMES_PER_CEL)
	);
}

void orb_and_pellets_and_stage_unput_update_render__vsync_wait(int stage_id)
{
	if(!orb_in_portal) {
		orb_move_x(orb_velocity_x);
		orb_cur_top += orb_velocity_y_update();
		orb_frames_outside_portal++;

		if(orb_is_moving_left()) {
			orb_rotation_frame++;
		}
		if(orb_is_moving_right()) {
			orb_rotation_frame--;
		}

		// ZUN quirk: The fourth cel is only visible for a single frame?
		if(orb_rotation_frame >= ((ORB_CELS * ORB_FRAMES_PER_CEL) - 2)) {
			orb_rotation_frame = 0;
		}
		if(orb_rotation_frame < 0) {
			orb_rotation_frame = ((ORB_CELS - 1) * ORB_FRAMES_PER_CEL);
		}

		if(orb_cur_top > ORB_TOP_MAX) {
			orb_force_new(COEFFICIENT_OF_RESTITUTION, OF_BOUNCE_FROM_SURFACE);
			orb_cur_top = ORB_TOP_MAX;
			cardcombo_cur = 0;
		}
		if(orb_cur_top < ORB_TOP_MIN) {
			orb_force_new(0, OF_BOUNCE_FROM_TOP);
			orb_cur_top = ORB_TOP_MIN;
		}
	}

	frame_delay(1);
	Pellets.unput_update_render();

	// Stage object collision is explicitly deactivated on boss stages? Since
	// there's still a card combo metric on the TOTLE screen though, these
	// lines add another piece of evidence that that screen was shown for
	// regular stages as well, at one point in development.
	if(!stage_is_boss(stage_id)) {
		cards_hittest(stage_id);
		obstacles_update_and_render(false);
	}

	if(!orb_in_portal) {
		orb_player_hittest(OR_NONE);
	}

	if(!orb_in_portal) {
		// ZUN landmine: Shouldn't you unblit *before* updating the rotation
		// frame? While it's OK (and even sort of essential) to assume that all
		// Orb sprites are shaped identically (as they are in the original
		// data), ordering the calls like this still violates common sense.
		ptn_unput_8(orb_prev_left, orb_prev_top, orb_anim_cel());
	}

	if(!stage_is_boss(stage_id)) {
		cards_update_and_render();
	}

	if(!orb_in_portal && !player_is_hit) {
		ptn_put_8(orb_cur_left, orb_cur_top, orb_anim_cel());
	}

	orb_prev_left = orb_cur_left;
	orb_prev_top = orb_cur_top;
}
