#include "pc98.h"

#define PLAYER_W 32
#define PLAYER_H 48

static const pixel_t PLAYER_OPTION_W = 16;
static const pixel_t PLAYER_OPTION_H = 16;

// Center-to-center distance. Only directly used in TH04 and TH05, since TH02
// doesn't use center coordinates internally.
static const pixel_t PLAYER_OPTION_DISTANCE = (
	(PLAYER_W / 2) + (PLAYER_OPTION_W / 2)
);

static const pixel_t PLAYER_OPTION_TO_OPTION_DISTANCE = (
	PLAYER_OPTION_DISTANCE * 2
);

#if (GAME == 2)
#include "th02/main/playfld.hpp"
#include "th02/sprites/main_pat.h"

// Coordinates
// -----------

static const screen_x_t PLAYER_LEFT_START = (
	PLAYFIELD_LEFT + (PLAYFIELD_W / 2) - (PLAYER_W / 2)
);
static const screen_y_t PLAYER_TOP_START = (PLAYFIELD_BOTTOM - PLAYER_H);

static const pixel_t PLAYER_LEFT_TO_OPTION_LEFT_LEFT = (
	PLAYER_OPTION_DISTANCE - (PLAYER_W / 2) + (PLAYER_OPTION_W / 2)
);
// -----------

// Current position
// ----------------
// ZUN bloat: It's tracked quite redundantly in this game:
//
// 1) [player_(left|top)_on_page] contains the authoritative coordinates on
//    both VRAM pages, just like every other entity in this game.
// 2) [player_(left|top)_on_back_page] is set in player_invalidate() to avoid
//    repeated address calculations of the back page element in 1).
// 3) [player_topleft] is a set to 2)'s value in player_move(), probably to
//    then avoid dereferencing a pointer whenever the position is needed?
//
// For the most part, game logic can just use 3), which is why its name didn't
// receive any further qualifiers. However, the miss animation prevents
// player_move() from running and therefore needs to access the position
// through 2) after all, especially since it also calculates the spawn position
// of the sparks by temporarily mutating the position. This can definitely be
// done in a cleaner and less redundant way.

extern screen_x_t player_left_on_page[2];
extern screen_y_t player_top_on_page[2];
extern screen_x_t near* player_left_on_back_page;
extern screen_y_t near* player_top_on_back_page;
extern screen_point_t player_topleft;

extern screen_point_t player_option_left_topleft[2];
extern screen_x_t near* player_option_left_left_on_back_page;
extern screen_y_t near* player_option_left_top_on_back_page;

inline screen_x_t player_center_x(void) {
	return (player_topleft.x + (PLAYER_W / 2));
}
inline screen_x_t player_center_y(void) {
	return (player_topleft.y + (PLAYER_H / 2));
}
// ----------------

extern main_patnum_t player_option_patnum;

extern enum {
	PLAYER_NOT_HIT = false,
	PLAYER_HIT = true,
	PLAYER_HIT_GAMEOVER = 0xFF,
} player_is_hit;
#else
extern bool player_is_hit;
#endif

// Grants invincibility when >0. Decrements by 1 each frame in that case.
// In TH02, this works independently from [player_invincible_via_bomb].
extern unsigned char player_invincibility_time;

static const uint8_t POWER_MIN = 1;
#if (GAME == 2)
static const uint8_t POWER_MAX = 80;
static const uint8_t MISS_INVINCIBILITY_FRAMES = 220;

// Grants invincibility as long as it's true. Works independently from
// [player_invincibility_time].
extern bool player_invincible_via_bomb;

extern uint8_t miss_frames;
extern bool miss_active; // ZUN bloat: Same as ([miss_frames] != 0)
#endif

static const int SHOT_LEVEL_MAX = 9;

extern uint8_t power;

// Amount of power past POWER_MAX, capped to POWER_OVERFLOW_MAX. Determines the
// point value of any further power items collected.
extern int power_overflow;

extern uint8_t shot_level;

void near player_invalidate();
