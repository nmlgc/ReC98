/// Stage 5 Boss - SinGyoku
/// -----------------------

extern "C" {
#include "platform.h"
}

#define boss_phase_frame	singyoku_phase_frame
#include "th01/main/boss/boss.hpp"

#define select_for_rank singyoku_select_for_rank
#include "th01/main/select_r.cpp"
