#define PLAYER_COUNT 2

// Charge Shots
// ------------
typedef void (far pascal *near chargeshot_add_func_t)(
	Subpixel center_x, Subpixel center_y
);

extern farfunc_t_near chargeshot_update[PLAYER_COUNT];
extern farfunc_t_near chargeshot_render[PLAYER_COUNT];
// ------------

extern unsigned char pid_current;
extern unsigned char pid_other;
