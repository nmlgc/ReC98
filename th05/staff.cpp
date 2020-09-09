/* ReC98
 * -----
 * TH05 Staff Roll
 */

#pragma codeseg maine_01__TEXT

extern "C" {
#include "ReC98.h"
#include "th01/math/subpixel.hpp"

/// Pattern numbers for the super_*() functions
/// -------------------------------------------
static const int ORB_PARTICLE_CELS = 6;

typedef enum {
	// stf01.bft
	// ---------
	// Ordered from big to small
	PAT_ORB_PARTICLE = 0,
	PAT_ORB_PARTICLE_last = (PAT_ORB_PARTICLE + ORB_PARTICLE_CELS - 1),
	// ---------
} staff_patnum_t;
/// -------------------------------------------

// Particle structure
// ------------------
// Below this [phase_value.radius], the orb is rendered as a monochrome filled
// circle.
static const pixel_t ORB_RADIUS_FULL = 16;
static const pixel_t ORB_W = 32;
static const pixel_t ORB_H = 32;

typedef enum {
	X_RIGHT = 0,
	X_LEFT = 1,
} x_direction_t;

struct orb_particle_t {
	SPPointBase< SubpixelBase< long, pixel_t > > center;
	SPPoint velocity;
	int patnum_tiny;
	Subpixel speed;
	int gather_frame;	// Only used during the orb gather phase.
	unsigned char angle;
	union {
		unsigned char radius;	// In pixels. Only used with the [orb] instance
		x_direction_t rain_sway_x_direction;
	} al;
};
// ------------------

// State
// -----
static const int ORB_PARTICLE_COUNT = 64;
static const int ORB_TRAIL_COUNT = 8;
static const int ORB_INDEX = ORB_PARTICLE_COUNT;

extern pixel_t space_window_w;
extern pixel_t space_window_h;
extern screen_point_t space_window_center;

// Effectively just moves all the entities into the opposite direction.
extern SPPoint space_camera_velocity;

// All coordinates of these are relative to the center of space.
extern orb_particle_t particles[ORB_PARTICLE_COUNT + 1];
#define orb particles[ORB_INDEX]

extern SPPoint orb_trails_center[ORB_TRAIL_COUNT];
// -----

void pascal near space_window_set(
	screen_x_t center_x, screen_y_t center_y, pixel_t w, pixel_t h
)
{
	space_window_center.x = center_x;
	space_window_center.y = center_y;
	space_window_w = w;
	space_window_h = h;
	grc_setclip(
		(space_window_center.x - (space_window_w / 2)) - 8,
		(space_window_center.y - (space_window_h / 2)) - 8,
		(space_window_center.x + (space_window_w / 2)) + 7,
		(space_window_center.y + (space_window_h / 2)) + 7
	);
}

}
