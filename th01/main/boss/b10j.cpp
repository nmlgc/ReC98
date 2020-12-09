/// Jigoku Stage 10 Boss - Mima
/// ---------------------------

extern "C" {
#include "platform.h"
}

#define initial_hp_rendered	mima_initial_hp_rendered
extern bool initial_hp_rendered;

#define select_for_rank mima_select_for_rank
#include "th01/main/select_r.cpp"
