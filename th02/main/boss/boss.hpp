// Midboss and boss state
// ----------------------

#include "pc98.h"

extern int16_t boss_phase_frame;

// Same indirection as used for the player position. Unfortunately not
// contiguous in memory, or else we could have created a struct for both.
extern screen_x_t boss_left_on_page[2];
extern screen_y_t boss_top_on_page[2];
extern screen_x_t near* boss_left_on_back_page;
extern screen_y_t near* boss_top_on_back_page;

// TH02 tracks boss and midboss health via the increasing amount of damage
// dealt, instead of using a decreasing HP value.
extern int boss_damage;
// ----------------------
