#include "th01/ranks.h"

extern rank_t rank;
extern bool bgm_mode;
extern char bombs;
extern char credit_bombs;

// Current gameplay frame plus resident_t::rand, without any frame_delay().
// Displayed as "rand" in the debug output, but can't be /* ZUN symbol */'d
// like that, due to obviously colliding with the C standard library function.
extern unsigned long frame_rand;

extern char lives_extra;

extern char stage_num;
extern bool first_stage_in_scene;

extern unsigned long score;

extern bool game_cleared;
