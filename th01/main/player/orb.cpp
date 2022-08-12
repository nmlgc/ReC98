#include "th01/main/player/orb.hpp"

extern double orb_velocity_y;

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
		if((rand() % 50) == val) { \
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
