#include "th02/main/bullet/bullet.hpp"
#include "th02/main/entity.hpp"

// Conceptually identical to the same constants in TH04, but not worth their
// own header to avoid the duplication. (And indeed named "size type" so that
// the variants would abbreviate the same as they would for "spawn types"!)
enum bullet_size_type_t {
	BST_PELLET = 1,
	BST_BULLET16 = 2,
};

struct bullet_t {
	int8_t flag; // ACTUAL TYPE: entity_flag_t
	int8_t size_type; // ACTUAL TYPE: bullet_size_type_t

	// Stores the current and previous position, indexed with the currently
	// rendered VRAM page.
	SPPoint screen_topleft[2];

	SPPoint velocity;
	main_patnum_t patnum; // Only used with `BST_BULLET16`.

	// Only used with `BST_BULLET16`.
	bullet_group_or_special_motion_t group_or_special_motion;

	unsigned char angle;
	SubpixelLength8 speed;

	// ZUN bloat: There's a padding byte to store a second value...
	union {
		uint8_t special_frames;
		uint8_t turns_done;
		uint8_t v;
	} u1;
	int8_t padding;
};

// State
// -----

#define cur_left   	bullet_cur_left
#define cur_top    	bullet_cur_top
#define screen_left	bullet_screen_left
#define screen_top 	bullet_screen_top
#define stack      	bullet_stack

extern bullet_t bullets[BULLET_COUNT];

extern screen_x_t screen_left;
extern screen_y_t screen_top;
extern Subpixel8 rank_base_speed;
extern Subpixel near* cur_left;
extern Subpixel near* cur_top;

extern uint8_t rank_base_stack;
extern uint8_t stack;
// -----
