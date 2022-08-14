// Input state of REIIDEN.EXE and FUUIN.EXE.

#include "platform.h"
#include "th01/hardware/input.hpp"

static bool input_unused = false; // ZUN bloat
bool input_lr = false;
bool input_mem_enter = false;
bool input_mem_leave = false;
bool input_shot = false;
bool player_is_hit = false;
bool input_bomb = false;
bool paused = false;
bool input_ok = false;
bool input_strike = false;
bool input_up = false;
bool input_down = false;
