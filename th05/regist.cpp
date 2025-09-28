#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th04/gaiji/gaiji.h"
#include "th04/formats/scoredat/scoredat.hpp"

/// Pattern numbers for the super_*() functions
/// -------------------------------------------
static const int GLYPHBALL_CELS = 4;

typedef enum {
	// sctm0.bft
	// ---------
	PAT_GLYPHBALL_CLOUD = 20,
	PAT_GLYPHBALL_CLOUD_last = (PAT_GLYPHBALL_CLOUD + GLYPHBALL_CELS - 1),
	PAT_GLYPHBALL_SPLASH,
	PAT_GLYPHBALL_SPLASH_last = (PAT_GLYPHBALL_SPLASH + GLYPHBALL_CELS - 1),
	// ---------
	// sctm1.bft
	// ---------
	PAT_GLYPHBALL,
	PAT_GLYPHBALL_last = (PAT_GLYPHBALL + GLYPHBALL_CELS - 1),
	// ---------
} regist_patnum_t;
/// -------------------------------------------

/// Floating balls carrying the individual name glyphs
/// --------------------------------------------------
#define GLYPHBALL_CLOUD_SPLASH_W 32
#define GLYPHBALL_CLOUD_SPLASH_H 32
#define GLYPHBALL_W 16
#define GLYPHBALL_H 16

#if (GLYPHBALL_CLOUD_SPLASH_W < GLYPHBALL_W)
#error Original code assumes GLYPHBALL_CLOUD_SPLASH_W >= GLYPHBALL_W
#endif
#if (GLYPHBALL_CLOUD_SPLASH_H < GLYPHBALL_H)
#error Original code assumes GLYPHBALL_CLOUD_SPLASH_H >= GLYPHBALL_H
#endif

typedef enum {
	GBP_FREE = 0,
	GBP_CLOUD_AT_ORIGIN = 1,

	// Also writes [glyph] to the high score structure once it reached
	// [target], immediately before advancing to the next phase.
	GBP_FLOAT_TO_TARGET = 2,

	GBP_SPLASH_AT_TARGET = 3,
	GBP_DONE = 4,

	// Non-[GBP_FREE] glyph ball should be removed
	GBP_REMOVE_REQUEST = 5,

	_glyphball_phase_t_FORCE_UINT8 = 0xFF
} glyphball_phase_t;

struct glyphball_t {
	glyphball_phase_t phase;
	gaiji_th04_t glyph;
	MotionBase<SPPoint> pos; // Relative to the top-left corner of the screen.
	SPPoint target;
	unsigned char angle;
	SubpixelLength8 speed;
	int phase_frame;
	int8_t padding[6];
};

// 1 additional unused one, for some reason?
extern glyphball_t glyphballs[SCOREDAT_NAME_LEN + 1];
/// --------------------------------------------------
