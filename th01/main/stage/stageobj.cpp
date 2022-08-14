#include <stddef.h>
#include <stdlib.h>
#include <malloc.h>
#include "platform.h"
#include "pc98.h"
#include "decomp.hpp"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/main/playfld.hpp"
#include "th01/hardware/egc.h"
#include "th01/formats/ptn.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/vars.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/stage/stages.hpp"
#include "th01/main/stage/stageobj.hpp"

// Globals
// -------

struct stage_t {
	StupidBytewiseWrapperAround<stagedat_stage_t> dat;
	int8_t padding[5];
};

// ZUN bloat: The scene data is immediately converted to an internal
// representation anyway. This could have easily been a local variable… then
// again, storing it in global data is what gives negative "glitch stages"
// their deterministic appearance.
extern stage_t scene_stage[STAGES_PER_SCENE];

char default_grp_fn[15] = "ST .GRP";
char default_bgm_fn[15] = "ST .MDT";

uint8_t CARD_ANIM[CARD_HP_MAX][CARD_CELS] = { {
	PTN_CARD_0HP,
	PTN_CARD_0HP_HALF,
	PTN_CARD_0HP_EDGE,
	PTN_CARD_REMOVED_HALF,
	PTN_CARD_REMOVED,
}, {
	PTN_CARD_1HP,
	PTN_CARD_1HP_HALF,
	PTN_CARD_1HP_EDGE,
	PTN_CARD_0HP_HALF,
	PTN_CARD_0HP,
}, {
	PTN_CARD_2HP,
	PTN_CARD_2HP_HALF,
	PTN_CARD_2HP_EDGE,
	PTN_CARD_1HP_HALF,
	PTN_CARD_1HP,
}, {
	PTN_CARD_3HP,
	PTN_CARD_3HP_HALF,
	PTN_CARD_3HP_EDGE,
	PTN_CARD_2HP_HALF,
	PTN_CARD_2HP,
}, {
	PTN_CARD_3HP,
	PTN_CARD_3HP_HALF,
	PTN_CARD_3HP_EDGE,
	PTN_CARD_3HP_HALF,
	PTN_CARD_3HP,
} };

ptn_t *stageobj_bgs;
unsigned long stageobj_bgs_size;
CCards cards;
CObstacles obstacles;
unsigned long *cards_score;
// -------

// Byte-wise iterators for STAGE?.DAT arrays
// -----------------------------------------

inline int cards_begin() {
	return offsetof(stagedat_stage_t, cards);
}

inline int cards_end() {
	return (cards_begin() + sizeof(((stagedat_stage_t*)0)->cards));
}

inline int obstacles_begin() {
	return offsetof(stagedat_stage_t, obstacles);
}

inline int obstacles_end() {
	return (obstacles_begin() + sizeof(((stagedat_stage_t*)0)->obstacles));
}
// -----------------------------------------

// On-screen positions
// -------------------

inline screen_x_t stageobj_left(int col) {
	return ((col * STAGEOBJ_W) + PLAYFIELD_LEFT);
}

inline vram_y_t stageobj_top(int row) {
	return ((row * STAGEOBJ_H) + PLAYFIELD_TOP);
}

#define card_left_from(dat_offset, card_bit) \
	( \
		((dat_offset - cards_begin()) * (STAGEOBJ_W * CARDS_PER_BYTE)) % \
		PLAYFIELD_W \
	) + stageobj_left(card_bit)

#define card_top_from(dat_offset) \
	stageobj_top((dat_offset - cards_begin()) / (STAGEOBJS_X / CARDS_PER_BYTE))

#define obstacle_left_from(dat_offset) \
	stageobj_left((dat_offset - obstacles_begin()) % STAGEOBJS_X)

#define obstacle_top_from(dat_offset) \
	stageobj_top((dat_offset - obstacles_begin()) / STAGEOBJS_X)
// -------------------

// Function ordering fails
// -----------------------

void portal_enter_update_and_render_or_reset(int obstacle_i, bool16 reset);
void turret_fire_update_and_render_or_reset(int obstacle_i, bool16 reset);

// Only called for the entered portal, not the destination one. (The obstacle
// slot of the latter is fact unavailable outside this function.)
#define portal_enter_update_and_render(obstacle_i) { \
	portal_enter_update_and_render_or_reset(obstacle_i, false); \
}

// Kicks the Orb out of any portal it might still be in.
#define portals_reset() { \
	/* MODDERS: Pass `0` and `true` instead. */ \
	portal_enter_update_and_render_or_reset(i, reset); \
}

#define turret_fire_update_and_render(obstacle_i) { \
	turret_fire_update_and_render_or_reset(obstacle_i, false); \
}

#define turrets_reset() { \
	/* MODDERS: Pass `0` and `true` instead. */ \
	turret_fire_update_and_render_or_reset(i, reset); \
}
// -----------------------

// Frees [stageobj_bgs] if previously allocated, then allocates new memory for
// the given number of stage object backgrounds.
ptn_error_t stageobj_bgs_new(int image_count)
{
	if(image_count <= 0) {
		return PE_IMAGE_COUNT_INVALID;
	}
	if(stageobj_bgs) {
		farfree(stageobj_bgs);
	}

	// I suppose calloc() was chosen to conveniently reset the alpha planes?
	// It's not like they're used anywhere, though...
	//
	// Using a far*() function here is actually correct, as it allows more
	// than 64 KB to be allocated. Except that [stageobj_bgs] should have also
	// been a `huge` pointer, to allow all this memory to be accessed using
	// regular array subscripts... This way, the game can still only display
	// up to 102 stage objects without glitches, and the wrap-around when
	// writing to the 103rd background is guaranteed to corrupt the memory
	// block header at the beginning of the returned segment.
	stageobj_bgs = reinterpret_cast<ptn_t *>(
		farcalloc(image_count, sizeof(ptn_t))
	);
	if(!stageobj_bgs) {
		return PE_OUT_OF_MEMORY;
	}
	// Also, these factors should have maybe been casted to 32-bit...
	// Multiplying two 16-bit values also truncates the result.
	stageobj_bgs_size = (image_count * sizeof(ptn_t));
	return PE_OK;
}

void stageobj_bgs_put_all(void)
{
	int i;
	for(i = 0; i < cards.count; i++) {
		stageobj_bgs_put_8(cards.left[i], cards.top[i], (i + 0));
	}
	for(i = 0; i < obstacles.count; i++) {
		stageobj_bgs_put_8(
			obstacles.left[i], obstacles.top[i], (i + cards.count)
		);
	}
}

bool16 stageobj_bgs_free(void)
{
	if(stageobj_bgs) {
		farfree(stageobj_bgs);
		stageobj_bgs_size = 0;
		stageobj_bgs = nullptr;
	}
	return 0;
}

#define vram_put_ptn_bg_fg(plane, vo, bg, fg, y, fg_mask, tmp) \
	tmp = (~fg_mask & bg->planes.plane[y]); \
	VRAM_PUT(plane, vo, ((fg->planes.plane[y] & fg_mask) | tmp), PTN_W);

#define stageobj_put_8(cards_or_obstacles, i, cel) { \
	ptn_put_8(cards_or_obstacles.left[i], cards_or_obstacles.top[i], cel); \
}

#define stageobj_sloppy_unput_16(cards_or_obstacles, i) { \
	ptn_sloppy_unput_16(cards_or_obstacles.left[i], cards_or_obstacles.top[i]);\
}

void stageobj_put_bg_and_obj_8(
	screen_x_t left, vram_y_t top, int ptn_id, int bg_slot
)
{
	upixel_t y;
	dots_t(PTN_W) fg_mask = 0;
	dots_t(PTN_W) bg_dots_masked;
	vram_offset_t vo = vram_offset_muldiv(left, top);

	ptn_t *fg;
	if(ptn_id != PTN_STAGEOBJ_NONE) {
		fg = ptn_with_id(ptn_id);
	}
	ptn_t *bg = &stageobj_bgs[bg_slot];

	if(ptn_id != PTN_STAGEOBJ_NONE) {
		for(y = 0; y < PTN_H; y++) {
			fg_mask = fg->alpha[y];
			vram_put_ptn_bg_fg(B, vo, bg, fg, y, fg_mask, bg_dots_masked);
			vram_put_ptn_bg_fg(R, vo, bg, fg, y, fg_mask, bg_dots_masked);
			vram_put_ptn_bg_fg(G, vo, bg, fg, y, fg_mask, bg_dots_masked);
			vram_put_ptn_bg_fg(E, vo, bg, fg, y, fg_mask, bg_dots_masked);
			vo += ROW_SIZE;
		}
	} else {
		for(y = 0; y < PTN_H; y++) {
			vram_put_ptn_planar(vo, bg, y);
			vo += ROW_SIZE;
		}
	}
}

// Overwrites the stage object background in the given [slot] with the current
// VRAM pixels at (⌊left/8⌋*8, top) on page 1.
void stageobj_bgs_snap_from_1_8(screen_x_t left, vram_y_t top, int slot)
{
	vram_offset_t vo = vram_offset_muldiv(left, top);
	ptn_t *bg = &stageobj_bgs[slot];

	graph_accesspage_func(1);
	for(pixel_t y = 0; y < PTN_H; y++) {
		vram_snap_ptn_planar(bg, y, vo);
		vo += ROW_SIZE;
	}
	graph_accesspage_func(0);
}

void scene_init_and_load(unsigned char id)
{
	stagedat_header_t header;
	char scene_fn[15] = "stage .dat";

	scene_fn[5] = (id + '0');

	arc_file_load(scene_fn);
	arc_file_get_near(header);

	default_grp_fn[2] = (id + '0');
	default_bgm_fn[2] = (id + '0');

	for(int i = 0; i < STAGES_PER_SCENE; i++) {
		arc_file_get_near(scene_stage[i].dat);
	}

	arc_file_free();
}

void obstacles_init_advance_slot(int dat_offset, int ptn_id, int &slot)
{
	obstacles.left[slot] = obstacle_left_from(dat_offset);
	obstacles.top[slot] = obstacle_top_from(dat_offset);
	stageobj_bgs_snap_from_1_8(
		obstacles.left[slot], obstacles.top[slot], (slot + cards.count)
	);
	stageobj_put_8(obstacles, slot, ptn_id);
	slot++;
}

// At least we're going to have "non-exhausive switch statement" warnings on
// modern compilers.
#define if_actual_obstacle(type, body) \
	switch(type) { \
		case OT_BUMPER: \
		case OT_TURRET_SLOW_1_AIMED: \
		case OT_TURRET_SLOW_1_RANDOM_NARROW_AIMED: \
		case OT_TURRET_SLOW_2_SPREAD_WIDE_AIMED: \
		case OT_TURRET_SLOW_3_SPREAD_WIDE_AIMED: \
		case OT_TURRET_SLOW_4_SPREAD_WIDE_AIMED: \
		case OT_TURRET_SLOW_5_SPREAD_WIDE_AIMED: \
		case OT_TURRET_QUICK_1_AIMED: \
		case OT_TURRET_QUICK_1_RANDOM_NARROW_AIMED: \
		case OT_TURRET_QUICK_2_SPREAD_WIDE_AIMED: \
		case OT_TURRET_QUICK_3_SPREAD_WIDE_AIMED: \
		case OT_TURRET_QUICK_4_SPREAD_WIDE_AIMED: \
		case OT_TURRET_QUICK_5_SPREAD_WIDE_AIMED: \
		case OT_PORTAL: \
		case OT_BAR_TOP: \
		case OT_BAR_BOTTOM: \
		case OT_BAR_LEFT: \
		case OT_BAR_RIGHT: \
			body \
			break; \
	}

void stageobjs_copy_0_to_1(int stage_id)
{
	int i;

	int stage_in_scene = stage_id;
	stage_in_scene = (stage_in_scene % STAGES_PER_SCENE);
	if(stage_in_scene == BOSS_STAGE) {
		return;
	}

	for(i = 0; i < obstacles.count; i++) {
		if_actual_obstacle(obstacles.type[i], {
			ptn_copy_8_0_to_1(obstacles.left[i], obstacles.top[i]);
		});
	}
	for(i = 0; i < cards.count; i++) {
		ptn_copy_8_0_to_1(cards.left[i], cards.top[i]);
	}
}

void stageobjs_init_and_render(int stage_id)
{
	register int i;
	int j;
	int card_bit;
	int card_slot = 0;
	int lookup_i;
	screen_x_t lookup_left;
	vram_y_t lookup_top;
	int card_ptn_id;
	int obstacle_slot = 0;
	screen_x_t card_left;
	vram_y_t card_top;

	#define offset j
	#define nth_bit i

	stage_id = (stage_id % STAGES_PER_SCENE);

	obstacles.count = 0;
	cards.count = 0;

	if(stage_id == BOSS_STAGE) {
		return;
	}

	for(offset = cards_begin(); offset < cards_end(); offset++) {
		for(nth_bit = (1 << (CARDS_PER_BYTE - 1)); nth_bit != 0; nth_bit >>= 1) {
			if(scene_stage[stage_id].dat.byte[offset] & nth_bit) {
				cards.count++;
			}
		}
	}
	for(offset = obstacles_begin(); offset < obstacles_end(); offset++) {
		if_actual_obstacle(scene_stage[stage_id].dat.byte[offset], {
			obstacles.count++;
		});
	}

	stageobj_bgs_new(cards.count + obstacles.count);
	cards.new_counted();
	obstacles.new_counted();

	// No, not the ID of the one card that might remain unflipped after a bomb.
	// That's down to a per-frame rand(), see cards_hittest() for the actual
	// algorithm.
	static int a_random_unused_card_id;
	a_random_unused_card_id = (rand() % cards.count);

	for(i = 0; i < obstacles.count; i++) {
		obstacles.frames[i].v = 0;
	}
	for(i = 0; i < cards.count; i++) {
		cards.flip_frames[i] = 0;
	}

	for(offset = cards_begin(); offset < cards_end(); offset++) {
		for(nth_bit = (1 << (CARDS_PER_BYTE - 1)); nth_bit != 0; nth_bit >>= 1) {
			switch(nth_bit) {
			case (1 << 0):	card_bit = 3;	break;
			case (1 << 1):	card_bit = 2;	break;
			case (1 << 2):	card_bit = 1;	break;
			case (1 << 3):	card_bit = 0;	break;
			}
			if(scene_stage[stage_id].dat.byte[offset] & nth_bit) {
				card_left = card_left_from(offset, card_bit);
				card_top = card_top_from(offset);

				stageobj_bgs_snap_from_1_8(card_left, card_top, card_slot);

				cards.left[card_slot] = card_left;
				cards.top[card_slot] = card_top;
				cards.flag[card_slot] = CARD_ALIVE;
				// Remember, the HP is actually stored in the obstacle array
				// if it's ≥1...
				cards.hp[card_slot] = 0;

				card_slot++;
			}
		}
	}

	obstacle_slot = 0; // Again?!
	for(offset = obstacles_begin(); offset < obstacles_end(); offset++) {
		#define obstacle_type scene_stage[stage_id].dat.byte[offset]
		switch(obstacle_type) {
		case OT_BUMPER:
			obstacles_init_advance_slot(offset, PTN_BUMPER, obstacle_slot);
			goto actual_obstacle;

		case OT_TURRET_SLOW_1_AIMED:
		case OT_TURRET_SLOW_1_RANDOM_NARROW_AIMED:
		case OT_TURRET_SLOW_2_SPREAD_WIDE_AIMED:
		case OT_TURRET_SLOW_3_SPREAD_WIDE_AIMED:
		case OT_TURRET_SLOW_4_SPREAD_WIDE_AIMED:
		case OT_TURRET_SLOW_5_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_1_AIMED:
		case OT_TURRET_QUICK_1_RANDOM_NARROW_AIMED:
		case OT_TURRET_QUICK_2_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_3_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_4_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_5_SPREAD_WIDE_AIMED:
			obstacles_init_advance_slot(offset, PTN_TURRET, obstacle_slot);
			goto actual_obstacle;

		case OT_ACTUALLY_A_2FLIP_CARD:
		case OT_ACTUALLY_A_3FLIP_CARD:
		case OT_ACTUALLY_A_4FLIP_CARD:
			lookup_left = obstacle_left_from(offset);
			lookup_top = obstacle_top_from(offset);
			for(lookup_i = 0; lookup_i < cards.count; lookup_i++) {
				if(
					(cards.left[lookup_i] == lookup_left) &&
					(cards.top[lookup_i] == lookup_top)
				) {
					cards.hp[lookup_i] = (
						(obstacle_type - OT_ACTUALLY_A_CARD) + 1
					);
					break;
				}
			}
			break;

		case OT_PORTAL:
			obstacles_init_advance_slot(offset, PTN_PORTAL, obstacle_slot);
			goto actual_obstacle;
		case OT_BAR_TOP:
			obstacles_init_advance_slot(offset, PTN_BAR_TOP, obstacle_slot);
			goto actual_obstacle;
		case OT_BAR_BOTTOM:
			obstacles_init_advance_slot(offset, PTN_BAR_BOTTOM, obstacle_slot);
			goto actual_obstacle;
		case OT_BAR_LEFT:
			obstacles_init_advance_slot(offset, PTN_BAR_LEFT, obstacle_slot);
			goto actual_obstacle;
		case OT_BAR_RIGHT:
			obstacles_init_advance_slot(offset, PTN_BAR_RIGHT, obstacle_slot);
			goto actual_obstacle;

		actual_obstacle:
			obstacles.type[obstacle_slot - 1] = obstacle_type_t(obstacle_type);
			obstacles.frames[obstacle_slot - 1].v = 0; // Again?!
			break;
		}
		#undef obstacle_type
	}

	if(first_stage_in_scene == true) {
		for(i = 0; i < cards.count; i++) {
			card_ptn_id = CARD_ANIM[cards.hp[i]][0];
			stageobj_put_8(cards, i, card_ptn_id);
		}
		return;
	}

	// ZUN bug: Should be STAGEOBJS_COUNT. This effectively limits stages to a
	// maximum of 50 cards rather than the original 200, since...
	int frames_for[50] = { 0 };
	// ... [total_frames] is the next variable on the stack. Therefore, ...
	int total_frames = 0;
	while(1) {
		int cards_animated = 0;
		for(i = 0; i < cards.count; i++) {
			if(frames_for[i] == -1) {
				cards_animated++;
			}
			if(frames_for[i] < card_first_frame_of(CARD_CEL_EDGE)) {
				continue;
			}
			if((frames_for[i] % CARD_FRAMES_PER_CEL) == 0) {
				card_ptn_id = (
					CARD_ANIM[cards.hp[i] + 1][card_cel_at(frames_for[i])]
				);
				stageobj_put_8(cards, i, card_ptn_id);
			}
			frames_for[i]++;
			// ... trying to access the 51st card here actually accesses
			// [total_frames], periodically resetting it to -1. Which in turn
			// means that...
			if(frames_for[i] > card_first_frame_of(CARD_CEL_FLIPPED)) {
				frames_for[i] = -1;
			}
		}
		if(cards_animated >= cards.count) {
			break;
		}
		// ... the first 24 cards are animated over and over in an infinite
		// loop, as the termination condition above can never become true.
		if(total_frames < cards.count) {
			frames_for[total_frames] = card_first_frame_of(CARD_CEL_EDGE);
		}
		total_frames++;
		frame_delay(1);
	}

	#undef nth_bit
	#undef offset
}

#define turret_update(obstacle_i, firing_interval, reset) \
	if(rank != RANK_EASY) { \
		obstacles.frames[obstacle_i].fire_cycle++; \
	} \
	if(obstacles.frames[obstacle_i].fire_cycle >= firing_interval) { \
		turret_fire_update_and_render(obstacle_i); \
	} \
	if(reset == true) { \
		obstacles.frames[obstacle_i].fire_cycle = 0; \
		turrets_reset(); \
	}

// The collision detection macros below are forced to be used inside an `if`
// statement, returning a non-zero value if a collision took place.

#define bar_hittest_horizontal( \
	i, condition_x, condition_above_top, condition_below_top \
) \
	condition_x && condition_above_top && condition_below_top) { \
		if(obstacles.frames[i].since_collision == 0) { \
			obstacles.frames[i].since_collision++; \
			/* \
			 * That's a very naive response to a collision, as it implies that \
			 * the Orb is always coming in perpendicular to the bar. The size \
			 * of a bar's hitbox makes it easily possible to hit it from a \
			 * close-to-parallel angle though. A more "correct" response would \
			 * branch depending on that angle between the Orb and the bar. \
			 */ \
			orb_velocity_reflect_y(); \
		} \
	} \
	/* (redundant, checked after the loop) */ \
	if(obstacles.frames[i].since_collision != 0

#define bar_hittest_vertical( \
	i, condition_y, condition_left_of_left, condition_right_of_left, blocked \
) \
	condition_y && condition_left_of_left && condition_right_of_left) { \
		if((obstacles.frames[i].since_collision == 0) && !blocked) { \
			obstacles.frames[i].since_collision++; \
			blocked = true; \
			\
			/* \
			 * Same here. This one does attempt to cover the parallel case,\
			 * but only for OVX_0. This ignores all other close-to-parallel \
			 * angles between the bar and the Orb that should be handled in an \
			 * identical way, and that the Orb can end up in such an angle at \
			 * any velocity. Any "correct" response would not even look at the \
			 * Orb's velocity in its branch conditions. \
			 */ \
			if(orb_velocity_x == OVX_0) { \
				orb_velocity_reflect_y(); \
			} else { \
				orb_velocity_reflect_x(); \
			} \
		} \
	} \
	/* (redundant, checked after the loop) */ \
	if(obstacles.frames[i].since_collision != 0

void obstacles_update_and_render(bool16 reset)
{
	enum {
		// Actually 7, as [since_collision] is already set from 0 to 2 on the
		// first frame of a collision. Since a new player shot can be fired
		// every 4 frames when standing still, this number is exactly what
		// allows the Orb to be button-mashed through a bumper bar.
		BLOCK_FRAMES = 8,
	};

	// This function tests Orb collisions independently for every obstacle. If
	// two bumper bars are placed right next to each other in any dimension,
	// Orb collisions are therefore detected and handled for both bars within
	// the same frame. For horizontal bars, this isn't a problem, as the Orb's
	// Y velocity can only be changed from outside by replacing the single
	// force acting on the Orb. In this function, the reflected force is
	// exclusively derived from the (otherwise unmodified) Y velocity, which
	// means that this can be done multiple times within the same frame without
	// changing the result.
	// Vertical bars, however, have to directly invert the Orb's X velocity. If
	// they are arranged in a column, colliding with two of them simultaneously
	// is very common due to their hitbox stretching over almost three tile
	// columns. With their collision response only consisting of that velocity
	// change though, the resulting double negation would completely cancel out
	// their effect.
	//
	// This flag works around the issue by simply blocking collision with *any*
	// vertical bumper bar for the next [BLOCK_FRAMES] after the first one.
	// While it doesn't address the general inadequacy of the collision
	// handling code for bumper bars at all, it's at least somewhat decent in
	// how it avoids the need for involving the X velocity in the physics
	// system. Any glitches that are still present with this hack either remain
	// unchanged or are made more interesting.
	// (Try shooting the Orb into the two adjacent bumper bar columns in Makai
	// Stage 17, and watch how this flag contributes to the Orb gradually
	// rising up to the top of the playfield. Without it, the Orb would simply
	// oscillate between a fixed set of bumper bars.)
	static bool vertical_bars_blocked;

	if(reset == true) {
		vertical_bars_blocked = false;
	}

	for(unsigned int i = 0; i < obstacles.count; i++) {
		upixel_t delta_abs_x;
		upixel_t delta_abs_y;
		pixel_t delta_x;
		pixel_t delta_y;

		delta_abs_x = abs(obstacles.left[i] - orb_cur_left);
		delta_abs_y = abs(obstacles.top[i] - orb_cur_top);
		delta_x = (orb_cur_left - obstacles.left[i]);
		delta_y = (orb_cur_top - obstacles.top[i]);

		switch(obstacles.type[i]) {
		case OT_BUMPER:
			if(
				(delta_abs_x < STAGEOBJ_ORB_DISTANCE_X) &&
				(delta_abs_y < STAGEOBJ_ORB_DISTANCE_Y) &&
				(obstacles.frames[i].since_collision == 0)
			) {
				obstacles.frames[i].since_collision++;

				// Yup, an immediate teleport to above or below the bumper, as
				// if it couldn't ever be hit from the left or right side,
				// completely bypassing the regular physics system. This
				// assignment is what causes infinite loops between bumpers in
				// the first place: If two bumpers are close enough and the
				// Orb's Y velocity is small enough before the first collision,
				// this assignment makes sure that the Orb can never escape the
				// hitbox of either bumper.
				// Nothing about this is necessary. Repeated collisions are
				// already prevented by the [since_collision] frame counter,
				// and the physics system could have never produced these
				// loops. So we might as well conclude that ZUN deliberately
				// wrote this code to make infinite bumper loops possible, or
				// at least didn't remove it upon discovering what it did.
				orb_cur_top = ((delta_y <= 0)
					? (obstacles.top[i] - STAGEOBJ_ORB_DISTANCE_Y)
					: (obstacles.top[i] + STAGEOBJ_ORB_DISTANCE_Y)
				);

				// Then again, with OVX_8_* not being handled here and those
				// velocities therefore left unchanged, the above assignment is
				// the only thing that prevents the Orb from flying into the
				// bumper at such a speed.
				// The delta comparisons at least ensure that an Orb moving at
				// OVX_4_* isn't smashed *into* the bumper, only *away* from it.
				if((orb_velocity_x == OVX_4_RIGHT) && (delta_x < 0)) {
					orb_velocity_x = OVX_4_LEFT;
				} else if((orb_velocity_x == OVX_4_LEFT) && (delta_x > 0)) {
					orb_velocity_x = OVX_4_RIGHT;
				}
				orb_force_new(1.5, OF_BOUNCE_FROM_SURFACE);
			}

			if(obstacles.frames[i].since_collision != 0) {
				obstacles.frames[i].since_collision++;
				if(obstacles.frames[i].since_collision >= BLOCK_FRAMES) {
					obstacles.frames[i].since_collision = 0;
				}
			}

			// (redundant, done after the switch)
			if(reset == true) {
				obstacles.frames[i].since_collision = 0;
			}
			continue;

		case OT_TURRET_SLOW_1_AIMED:
		case OT_TURRET_SLOW_1_RANDOM_NARROW_AIMED:
		case OT_TURRET_SLOW_2_SPREAD_WIDE_AIMED:
		case OT_TURRET_SLOW_3_SPREAD_WIDE_AIMED:
		case OT_TURRET_SLOW_4_SPREAD_WIDE_AIMED:
		case OT_TURRET_SLOW_5_SPREAD_WIDE_AIMED:
			turret_update(i, 200, reset);
			continue;

		case OT_TURRET_QUICK_1_AIMED:
		case OT_TURRET_QUICK_1_RANDOM_NARROW_AIMED:
		case OT_TURRET_QUICK_2_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_3_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_4_SPREAD_WIDE_AIMED:
		case OT_TURRET_QUICK_5_SPREAD_WIDE_AIMED:
			turret_update(i, 100, reset);
			continue;

		case OT_PORTAL:
			if((
				(delta_abs_x < STAGEOBJ_ORB_DISTANCE_X) &&
				(delta_abs_y < STAGEOBJ_ORB_DISTANCE_Y)
			) || (
				obstacles.frames[i].since_collision != 0
			)) {
				portal_enter_update_and_render(i);
			}
			if(reset == true) {
				// (redundant, done after the switch)
				obstacles.frames[i].since_collision = 0;

				portals_reset();
			}
			continue;

		// The fact that the top and bottom bars use swapped extra heights, but
		// differ in which boundary pixel they still include, means that bottom
		// and top bars placed in adjacent stage object tiles would almost
		// share a hitbox, since it only differs in that one boundary pixel.
		case OT_BAR_BOTTOM:
			if(bar_hittest_horizontal(
				i,
				(delta_abs_x < STAGEOBJ_W),
				((orb_cur_top - obstacles.top[i]) <= STAGEOBJ_H),
				((orb_cur_top - obstacles.top[i]) > 0)
			)) {
				break;
			}
			continue;

		case OT_BAR_TOP:
			if(bar_hittest_horizontal(
				i,
				(delta_abs_x < STAGEOBJ_W),
				((orb_cur_top - obstacles.top[i]) <  0),
				((orb_cur_top - obstacles.top[i]) >= -STAGEOBJ_H)
			)) {
				break;
			}
			continue;

		// And since these share that boundary pixel, adjacent right and left
		// bars do share the exact same hitbox. See Makai Stage 17 for an
		// example.
		case OT_BAR_LEFT:
			if(bar_hittest_vertical(
				i,
				(delta_abs_y < STAGEOBJ_H),
				((obstacles.left[i] - orb_cur_left) <= STAGEOBJ_W),
				((obstacles.left[i] - orb_cur_left) >= 0),
				vertical_bars_blocked
			)) {
				break;
			}
			continue;

		case OT_BAR_RIGHT:
			if(bar_hittest_vertical(
				i,
				(delta_abs_y < STAGEOBJ_H),
				((obstacles.left[i] - orb_cur_left) <= 0),
				((obstacles.left[i] - orb_cur_left) >= -STAGEOBJ_W),
				vertical_bars_blocked
			)) {
				break;
			}
			continue;

		default:
			continue;
		}
		// Common to all bumper bars
		if(obstacles.frames[i].since_collision != 0) {
			obstacles.frames[i].since_collision++;
			if(obstacles.frames[i].since_collision >= BLOCK_FRAMES) {
				obstacles.frames[i].since_collision = 0;
				vertical_bars_blocked = false;
			}
		}
		if(reset == true) {
			obstacles.frames[i].since_collision = 0;
		}
	}
}

static const int TURRET_COOLDOWN_FRAMES = 7;

enum turret_state_t {
	TS_READY = 0,
	TS_WARMUP = 1,
	TS_FIRE = 2,
	TS_COOLDOWN = 3,
	TS_DONE = (TS_COOLDOWN + TURRET_COOLDOWN_FRAMES),

	_turret_state_t_FORCE_INT16 = 0x7FFF
};

void turret_fire_update_and_render_or_reset(int obstacle_slot, bool16 reset)
{
	static turret_state_t *turret_state;

	if(reset == true) {
		if(turret_state) {
			delete[] turret_state;
			turret_state = nullptr;
		}
		if(obstacles.count != 0) {
			turret_state = new turret_state_t[obstacles.count];
		}
		for(
			obstacle_slot = 0;
			obstacle_slot < obstacles.count;
			obstacle_slot++
		) {
			turret_state[obstacle_slot] = TS_READY;
		}
		return;
	}
	if(turret_state[obstacle_slot] == TS_READY) {
		// MODDERS: This assumes that PTN_TURRET_FIRING only adds or changes
		// pixels compared to PTN_TURRET, and doesn't remove any. Unblit the
		// previous portal sprite to ensure this.

		graph_accesspage_func(1);
		stageobj_put_8(obstacles, obstacle_slot, PTN_TURRET_FIRING);
		graph_accesspage_func(0);
		stageobj_put_8(obstacles, obstacle_slot, PTN_TURRET_FIRING);

		turret_state[obstacle_slot] = TS_WARMUP;
	} else if(turret_state[obstacle_slot] == TS_WARMUP) {
		if((obstacles.frames[obstacle_slot].fire_cycle % 10) == 9) {
			turret_state[obstacle_slot] = TS_FIRE;
		}
	} else if(turret_state[obstacle_slot] == TS_FIRE) {
		uint8_t group; // ACTUAL TYPE: pellet_group_t
		switch(obstacles.type[obstacle_slot]) {
			case OT_TURRET_SLOW_1_AIMED:
			case OT_TURRET_QUICK_1_AIMED:
				group = PG_1_AIMED;
				break;

			case OT_TURRET_SLOW_1_RANDOM_NARROW_AIMED:
			case OT_TURRET_QUICK_1_RANDOM_NARROW_AIMED:
				group = PG_1_RANDOM_NARROW_AIMED;
				break;

			case OT_TURRET_SLOW_2_SPREAD_WIDE_AIMED:
			case OT_TURRET_QUICK_2_SPREAD_WIDE_AIMED:
				group = PG_2_SPREAD_WIDE_AIMED;
				break;

			case OT_TURRET_SLOW_3_SPREAD_WIDE_AIMED:
			case OT_TURRET_QUICK_3_SPREAD_WIDE_AIMED:
				group = PG_3_SPREAD_WIDE_AIMED;
				break;

			case OT_TURRET_SLOW_4_SPREAD_WIDE_AIMED:
			case OT_TURRET_QUICK_4_SPREAD_WIDE_AIMED:
				group = PG_4_SPREAD_WIDE_AIMED;
				break;

			case OT_TURRET_SLOW_5_SPREAD_WIDE_AIMED:
			case OT_TURRET_QUICK_5_SPREAD_WIDE_AIMED:
				group = PG_5_SPREAD_WIDE_AIMED;
				break;
		}
		Pellets.add_group(
			(obstacles.left[obstacle_slot] + (STAGEOBJ_W / 2) - (PELLET_W / 2)),
			(obstacles.top[obstacle_slot]  + (STAGEOBJ_H / 2) - (PELLET_H / 2)),
			static_cast<pellet_group_t>(group),
			to_sp(3.5f)
		);

		// Redundant. Looks like a workaround for the possibility of the sprite
		// having been unblitted with PTN_TURRET between TS_READY and now, but
		// we've also blitted PTN_TURRET_FIRING to VRAM page 1 before.
		// (Also, same lazy blitting issue as we've had the first time.)
		stageobj_put_8(obstacles, obstacle_slot, PTN_TURRET_FIRING);

		turret_state[obstacle_slot] = TS_COOLDOWN;
	} else {
		reinterpret_cast<int &>(turret_state[obstacle_slot])++;
		if(turret_state[obstacle_slot] >= TS_DONE) {
			graph_accesspage_func(1);
			stageobj_put_8(obstacles, obstacle_slot, PTN_TURRET);
			graph_accesspage_func(0);
			stageobj_put_8(obstacles, obstacle_slot, PTN_TURRET);

			turret_state[obstacle_slot] = TS_READY;
			obstacles.frames[obstacle_slot].fire_cycle = 0;
		}
	}
}

void portal_enter_update_and_render_or_reset(int obstacle_slot, bool16 reset)
{
	// Necessary to continue executing this function for the entered portal
	// while all others are blocked.
	static int obstacle_slot_of_entered_portal;

	static screen_x_t dst_left;
	static screen_y_t dst_top;

	// Additional flag on top of [orb_in_portal]. Left `true` for a few more
	// frames after the orb has exited the destination portal, to prevent it
	// from immediately re-entering into the same one.
	static bool16 portals_blocked;

	int dst_slot;
	int completed_loops_over_all_obstacles;

	if(reset == true) {
		obstacle_slot_of_entered_portal = 0; // (redundant)
		portals_blocked = false;
		if(orb_in_portal) {
			// ZUN bug: Missing an unblitting call. This just blits the regular
			// portal sprite on top of an animated one.
			ptn_put_8(dst_left, dst_top, PTN_PORTAL);

			orb_in_portal = false;
		}
		return;
	}

	if(
		(portals_blocked == true) &&
		(obstacle_slot_of_entered_portal != obstacle_slot)
	) {
		return;
	}

	if(obstacles.frames[obstacle_slot].since_collision != 0) {
		obstacles.frames[obstacle_slot].since_collision++;
	}
	if(obstacles.frames[obstacle_slot].since_collision == 0) {
		orb_in_portal = true;
		obstacles.frames[obstacle_slot].since_collision = 1;
		obstacle_slot_of_entered_portal = obstacle_slot;
		portals_blocked = true;

		ptn_sloppy_unput_16(orb_prev_left, orb_prev_top);

		// MODDERS: This assumes that (PTN_PORTAL_ANIM + 0) only adds or changes
		// pixels compared to PTN_PORTAL, and doesn't remove any. Unblit the
		// previous portal sprite to ensure this.
		stageobj_put_8(obstacles, obstacle_slot, (PTN_PORTAL_ANIM + 0));
	} else if(obstacles.frames[obstacle_slot].since_collision == 10) {
		stageobj_sloppy_unput_16(obstacles, obstacle_slot);
		stageobj_put_8(obstacles, obstacle_slot, (PTN_PORTAL_ANIM + 1));
	} else if(obstacles.frames[obstacle_slot].since_collision == 20) {
		stageobj_sloppy_unput_16(obstacles, obstacle_slot);
		stageobj_put_8(obstacles, obstacle_slot, PTN_PORTAL);

		// So, rather than just remembering all obstacle IDs that belong to
		// portals and pulling a new one directly from that pool, ZUN just
		// repeatedly loops over all obstacles, rolls a die, and gives up if
		// that roll didn't succeed for any non-entered portal after 16 loops.
		// That's cute… but does result in a decent failure chance of
		// 	(0.75 ^ (portal_count - 1)) ^ 16)
		// which is 1% for two portals, and 0.01% for three.
		dst_slot = 0;
		completed_loops_over_all_obstacles = 0;
		while(1) {
			if(
				(static_cast<int>(obstacles.type[dst_slot]) == OT_PORTAL) &&
				((rand() % 4) == 0) &&
				(dst_slot != obstacle_slot)
			 ) {
				break;
			}
			dst_slot++;
			if(completed_loops_over_all_obstacles > 15) {
				dst_slot = obstacle_slot;
				break;
			} else if(dst_slot >= obstacles.count) {
				dst_slot = 0;
				completed_loops_over_all_obstacles++;
			}
		}

		dst_left = obstacles.left[dst_slot];
		dst_top = obstacles.top[dst_slot];
		ptn_sloppy_unput_16(dst_left, dst_top);
		ptn_put_8(dst_left, dst_top, (PTN_PORTAL_ANIM + 1));
	} else if(obstacles.frames[obstacle_slot].since_collision == 30) {
		ptn_sloppy_unput_16(dst_left, dst_top);
		ptn_put_8(dst_left, dst_top, (PTN_PORTAL_ANIM + 0));
	} else if(obstacles.frames[obstacle_slot].since_collision == 40) {
		ptn_sloppy_unput_16(dst_left, dst_top);
		ptn_put_8(dst_left, dst_top, PTN_PORTAL);

		orb_velocity_x = static_cast<orb_velocity_x_t>(rand() % OVX_COUNT);
		orb_force_new(((rand() % 19) - 9), OF_IMMEDIATE);
		orb_cur_left = dst_left;
		orb_cur_top = dst_top;
		orb_in_portal = false;
	} else if(obstacles.frames[obstacle_slot].since_collision == 60) {
		obstacles.frames[obstacle_slot].since_collision = 0;
		portals_blocked = false;
	}
}

static int8_t unused[4];
