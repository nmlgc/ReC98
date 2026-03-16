// Extra Attacks
// -------------

#include "th03/common.h"
#include "th01/math/subpixel.hpp"

typedef struct exatt_funcs_t {
	void (pascal *add)(subpixel_t center_x, subpixel_t center_y, pid_t pid);
	void (*update)(void);
	void (*render)(void);
};

extern exatt_funcs_t exatt_funcs[PLAYER_COUNT];

// ZUN bloat: Useless wrapper around [exatt_funcs[pid]].
void pascal exatt_add(Subpixel center_x, Subpixel center_y, pid_t pid);
