#include "th01/rank.h"

extern int8_t rank; // ACTUAL TYPE: rank_t
extern int8_t bgm_mode; // ACTUAL TYPE: bool
extern int8_t bombs;
extern int8_t credit_bombs;

// Current gameplay frame plus resident_t::rand, without any frame_delay().
// Displayed as "rand" in the debug output, but can't be /* ZUN symbol */'d
// like that, due to obviously colliding with the C standard library function.
extern unsigned long frame_rand;

extern int8_t lives_extra;

extern int8_t stage_num;
extern bool first_stage_in_scene;

extern uint32_t score;

extern int8_t game_cleared; // ACTUAL TYPE: bool
