/// Stage 4 Boss - Reimu
/// --------------------

#include "platform.h"
#include "pc98.h"
#include "th04/main/playfld.hpp"
#include "th04/main/custom.hpp"

// Constants
// ---------

static const pixel_t ORB_W = 32;
static const pixel_t ORB_H = 32;
// ---------

// Structures
// ----------

#define ORB_COUNT CUSTOM_COUNT

enum orb_flag_t {
	OF_FREE = 0,

	// Moves out the orb from [origin] with a fixed speed (ignoring [velocity])
	// to a fixed distance away from Reimu, then transitions to OF_MOVE once
	// [spin_time] hits 0.
	OF_MOVEOUT_SPIN = 1,

	// Adds [velocity] to [center].
	OF_MOVE = 2,
};

struct orb_t {
	orb_flag_t flag;
	unsigned char angle;
	PlayfieldPoint center;
	PlayfieldPoint origin;
	PlayfieldPoint velocity;
	unsigned int spin_time;
	Subpixel distance;
	/* ------------------------- */ int16_t unknown;
	/* ------------------------- */ int8_t unused[4];
	SubpixelLength8 move_speed;
	char angle_speed;	// ACTUAL TYPE: unsigned char
};

#define orbs (reinterpret_cast<orb_t *>(custom_entities))
// ----------

// State
// -----

extern uint8_t orb_patnum_base; // ACTUAL TYPE: main_patnum_t
extern orb_t orb_template;

unsigned char reimu_pattern8_angle = 0x00;
int8_t reimu_bg_pulse_direction = false;
// -----

void pascal near orbs_add_moving(void)
;
void pascal near orbs_add_spinning(unsigned char angle_offset, int count)
;
