// Charge Shots
// ------------

#include "th03/common.h"
#include "th01/math/subpixel.hpp"

typedef void (far pascal *near chargeshot_add_func_t)(
	Subpixel center_x, Subpixel center_y
);
typedef uint8_t (far *near chargeshot_hittest_func_t)(void);

extern farfunc_t_near chargeshot_update[PLAYER_COUNT];
extern farfunc_t_near chargeshot_render[PLAYER_COUNT];
extern chargeshot_hittest_func_t chargeshot_hittest[PLAYER_COUNT];
