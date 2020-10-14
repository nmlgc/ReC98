/* ReC98
 * -----
 * TH05 Staff Roll
 */

#pragma codeseg maine_01__TEXT

extern "C" {
#include "libs/master.lib/master.h"
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
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
	PAT_STAR_BIG,
	PAT_STAR_SMALL,
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
static const int STAR_COUNT = 48;
static const int ORB_INDEX = ORB_PARTICLE_COUNT;

static const pixel_t VERDICT_BITMAP_W = 320;
static const pixel_t VERDICT_SCREEN_H = 352;
static const vram_byte_amount_t VERDICT_BITMAP_VRAM_W = (
	VERDICT_BITMAP_W / BYTE_DOTS
);
static const size_t VERDICT_SCREEN_SIZE = (
	VERDICT_SCREEN_H * VERDICT_BITMAP_VRAM_W
);

extern pixel_t space_window_w;
extern pixel_t space_window_h;
extern screen_point_t space_window_center;

// Effectively just moves all the entities into the opposite direction.
extern SPPoint space_camera_velocity;

// All coordinates of these are relative to the center of space.
orb_particle_t particles[ORB_PARTICLE_COUNT + 1];
#define orb particles[ORB_INDEX]

SPPoint orb_trails_center[ORB_TRAIL_COUNT];

// Elements at even indices are rendered as PAT_STAR_BIG, elements at odd
// indices are rendered as PAT_STAR_SMALL.
SPPoint stars_center[STAR_COUNT];

dots8_t verdict_bitmap[2][VERDICT_SCREEN_H][VERDICT_BITMAP_W / BYTE_DOTS];
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

// Copies a single verdict screen from
//	(0, 0) - (VERDICT_BITMAP_W, VERDICT_SCREEN_H)
// on the E plane in VRAM to ([verdict_bitmap] + [bitmap_offset]).
void pascal near verdict_bitmap_snap(size_t bitmap_offset)
;

// Blits a single verdict screen starting at
// ([verdict_bitmap] + [bitmap_offset]) to
//	(0, 0) - (VERDICT_BITMAP_W, VERDICT_SCREEN_H)
// in VRAM.
void pascal near verdict_bitmap_put(size_t bitmap_offset)
;

}
