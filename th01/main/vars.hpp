#include "th01/rank.h"

extern int8_t rank; // ACTUAL TYPE: rank_t
extern bgm_mode_t bgm_mode;
extern int8_t rem_bombs;
extern int8_t credit_bombs;

extern int8_t stage_num;
extern bool bgm_change_blocked;

// Current gameplay frame plus resident_t::rand, without any frame_delay().
// Displayed as "rand" in the debug output, but can't be /* ZUN symbol */'d
// like that, due to obviously colliding with the C standard library function.
extern unsigned long frame_rand;

extern int8_t credit_lives_extra;
extern bool first_stage_in_scene;
extern uscore_t score;
extern int8_t game_cleared; // ACTUAL TYPE: bool
