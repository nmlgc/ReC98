/// Stage 3 midboss
/// ---------------

#include "th02/main/boss/b3.hpp"

// State
// -----

extern int16_t midboss3_kill_frames[MIDBOSS3_COUNT];

// Same as for regular bosses.
// ZUN bloat: We only need two for each of these, not 5.
extern screen_x_t midboss3_left_on_page[STONE_COUNT][2];
extern screen_y_t midboss3_top_on_page[STONE_COUNT][2];
extern screen_x_t* midboss3_left_on_back_page[STONE_COUNT];
extern screen_y_t* midboss3_top_on_back_page[STONE_COUNT];
// -----
