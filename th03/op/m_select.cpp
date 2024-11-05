/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "pc98.h"
#include "libs/master.lib/master.hpp"
#include "th03/common.h"
#include "th03/playchar.hpp"
#include "th03/formats/scoredat.hpp"

/// State
/// -----

extern bool input_locked[PLAYER_COUNT];
extern playchar_t sel[PLAYER_COUNT];
extern bool sel_confirmed[PLAYER_COUNT];
extern page_t page_shown;
extern unsigned int fadeout_frames;
/// -----

#include "th03/formats/score_ld.cpp"
