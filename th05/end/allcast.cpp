#include "th05/playchar.h"
#include "pc98.h"

// Constants
// ---------

// ZUN bloat: Should be 7 (「Project of TOUHOU」 + 5 games + Credits), but ZUN
// sets it to 8, presumably for micro-optimization reasons.
static const int SCREEN_COUNT = 8;
// ---------

// State
// -----

#define playchar allcast_playchar

int measure_cur;
int frames_half;
int measure_target;
extern page_t page_shown;
int loaded_screen_id;
int line_id_total;
extern int line_id_on_screen;
playchar_t playchar;
// -----
