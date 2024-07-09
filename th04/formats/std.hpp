/// Map tile section order + enemy script format
/// --------------------------------------------

#include "th01/math/subpixel.hpp"

extern uint8_t __seg* std_seg;

#if (GAME == 5)
	// Within [std_seg]. TH05 doubles the map section ID so that can be
	// "directly" used as the byte offset into [TILE_SECTION_OFFSETS], saving a
	// grand total of one instruction for the lookup. *shrug*
	extern int std_map_section_p;
#else
	extern int std_map_section_id; // Within [std_seg]
#endif

extern SubpixelLength8 near* std_scroll_speed; // Within [std_seg]

#define STD_ENEMY_SCRIPT_COUNT 32

// TODO: Put the exact types once we RE'd them.
extern void near* std_enemy_scripts[STD_ENEMY_SCRIPT_COUNT]; // Within [std_seg]
extern void* std_ip;

extern farfunc_t_near stage_vm;

// Calls std_free(), then loads and allocates a new [std_seg] by reading the
// .STD file for the current stage.
void near std_load(void);

// Frees [std_seg] if previously allocated.
void near std_free(void);

// Runs the next stage instruction at [std_ip].
void pascal std_run();
