/// Jigoku Stage 20 Boss - Konngara
/// -------------------------------

extern "C" {
#include "platform.h"
}

#define initial_hp_rendered	konngara_initial_hp_rendered
extern bool initial_hp_rendered;

#define select_for_rank konngara_select_for_rank
#include "th01/main/select_r.cpp"
