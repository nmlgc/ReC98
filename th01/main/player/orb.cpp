#include "th01/main/playfld.hpp"
#include "th01/main/player/orb.hpp"

extern const double ORB_VELOCITY_Y_MIN;
extern const float ORB_VELOCITY_Y_MAX;
extern const double ORB_COEFFICIENT_OF_RESTITUTION;

inline double gravity_for(const double& force)
{
	return ((orb_force_frame / 5) + orb_force);
}
/// Temporary data segment workarounds
/// ----------------------------------
// Also needs to be spelled out in ASM to avoid the unwanted WAIT instruction
// afterwards.
#define GRAVITY_FOR(force) \
	_AX = orb_force_frame / 5; \
	asm mov	[bp-2], ax; \
	asm fild	word ptr [bp-2]; \
	asm fadd	force;

// Neither WAIT nor FWAIT emit the emulated WAIT we want...
#define FWAIT db 0xCD, 0x3D;
/// ----------------------------------

int orb_velocity_y_update(void)
{
	/* TODO: Proper decompilation, once data can be emitted here:
	 * ----------------------------------------------------------
	orb_velocity_y = gravity_for(orb_force);
	if(orb_velocity_y > ORB_VELOCITY_Y_MAX) {
		orb_velocity_y = ORB_VELOCITY_Y_MAX;
	} else if(orb_velocity_y < ORB_VELOCITY_Y_MIN) {
		orb_velocity_y = ORB_VELOCITY_Y_MIN;
	}
	return gravity_for(orb_force);
	 * ----------------------------------------------------------
	 * Performing arithmetic or comparisons between a double (orb_velocity_y)
	 * and a float (ORB_VELOCITY_Y_MAX) variable always FLDs the float first,
	 * before emitting the corresponding FPU instruction with the double,
	 * which is not what we want here.
	*/
	GRAVITY_FOR(orb_force);
	asm {
		fstp 	orb_velocity_y;
		fld  	orb_velocity_y;
		fcomp	ORB_VELOCITY_Y_MAX;
		fstsw	[bp-2];
		FWAIT;
		mov  	ax, [bp-2];
		sahf;
		jbe  	min_velocity_check;
		fld  	ORB_VELOCITY_Y_MAX;
	}
	goto set_velocity;
min_velocity_check:
	if(orb_velocity_y < ORB_VELOCITY_Y_MIN) asm {
		fld 	ORB_VELOCITY_Y_MIN;
set_velocity:
		fstp	orb_velocity_y;
		FWAIT;
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
	extern const float ORB_FORCE_2_0;
	extern const double ORB_FORCE_SHOT_BASE;

	if(force == OF_BOUNCE_FROM_GROUND) {
		orb_force = (-orb_velocity_y * ORB_COEFFICIENT_OF_RESTITUTION);
		if(orb_velocity_x == OVX_0) {
			random_velocity_change(0, OVX_4_LEFT);
			random_velocity_change(1, OVX_4_RIGHT);
		}
	}
	if(force == OF_BOUNCE_FROM_TOP) {
		orb_force = ((-orb_velocity_y) - (orb_force_frame / 4));
	}
	if(force == OF_SHOT) {
		/* TODO: Proper decompilation, once data can be emitted here:
		 * ----------------------------------------------------------
		orb_force = ((orb_velocity_y / ORB_FORCE_2_0) + ORB_FORCE_SHOT_BASE);
		 * ----------------------------------------------------------
		 * Performing arithmetic or comparisons between a double
		 * (orb_velocity_y) and a float (ORB_FORCE_2_0) variable always FLDs
		 * the float first, before emitting the corresponding FPU instruction
		 * with the double, which is not what we want here.
		*/
		asm {
			fld 	orb_velocity_y;
			fdiv	ORB_FORCE_2_0;
			fadd	ORB_FORCE_SHOT_BASE;
			fstp	orb_force;
			FWAIT;
		}
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
