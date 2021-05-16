extern "C" {
#include <stddef.h>
#include <malloc.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/main/vars.hpp"
#include "th01/main/stage/stages.hpp"
#include "th01/sprites/main_ptn.h"
}

#include "th01/main/stage/stageobj.hpp"

static const int TURRET_QUICK_INTERVAL = 100;
static const int TURRET_SLOW_INTERVAL = 200;

// Globals
// -------

struct stage_t {
	stagedat_stage_t dat;
	int8_t padding[5];
};
extern stage_t scene_stage[STAGES_PER_SCENE];
// -------

// Byte-wise iterators for STAGE?.DAT arrays
// -----------------------------------------

inline int cards_begin() {
	return offsetof(stagedat_stage_t, type.cards);
}

inline int cards_end() {
	return (cards_begin() + sizeof(((stagedat_stage_t*)0)->type.cards));
}

inline int obstacles_begin() {
	return offsetof(stagedat_stage_t, type.obstacles);
}

inline int obstacles_end() {
	return (obstacles_begin() + sizeof(((stagedat_stage_t*)0)->type.obstacles));
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

// Frees [stageobj_bgs] if non-NULL, then allocates new memory for the given
// number of stage object backgrounds.
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
		stageobj_bgs = NULL;
	}
	return 0;
}

#define vram_put_ptn_bg_fg(plane, vo, bg, fg, y, fg_mask, tmp) \
	tmp = (~fg_mask & bg->planes.plane[y]); \
	VRAM_PUT(plane, vo, ((fg->planes.plane[y] & fg_mask) | tmp), PTN_W);

void stageobj_put_8(screen_x_t left, vram_y_t top, int ptn_id, int bg_slot)
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
			vram_put_ptn_planar(vo, bg);
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
		vram_snap_ptn_planar(bg, vo);
		vo += ROW_SIZE;
	}
	graph_accesspage_func(0);
}

void scene_init_and_load(unsigned char id)
{
	struct hack { char x[15]; }; // XXX
	extern const hack scene_fn_;

	stagedat_header_t header;
	hack scene_fn = scene_fn_;

	scene_fn.x[5] = (id + '0');

	arc_file_load(scene_fn.x);
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
	ptn_put_8(obstacles.left[slot], obstacles.top[slot], ptn_id);
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

void stageobj_copy_all_0_to_1(int stage_id)
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

void stageobjs_init_and_render(int stage)
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

	stage = (stage % STAGES_PER_SCENE);

	obstacles.count = 0;
	cards.count = 0;

	if(stage == BOSS_STAGE) {
		return;
	}

	for(offset = cards_begin(); offset < cards_end(); offset++) {
		for(nth_bit = (1 << (CARDS_PER_BYTE - 1)); nth_bit != 0; nth_bit >>= 1) {
			if(scene_stage[stage].dat.byte[offset] & nth_bit) {
				cards.count++;
			}
		}
	}
	for(offset = obstacles_begin(); offset < obstacles_end(); offset++) {
		if_actual_obstacle(scene_stage[stage].dat.byte[offset], {
			obstacles.count++;
		});
	}

	stageobj_bgs_new(cards.count + obstacles.count);
	cards.new_counted();
	obstacles.new_counted();

	// No, not the ID of the one card that remains unflipped after a bomb.
	extern int a_random_unused_card_id;
	a_random_unused_card_id = (rand() % cards.count);

	for(i = 0; i < obstacles.count; i++) {
		obstacles.type_frames[i] = 0;
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
			if(scene_stage[stage].dat.byte[offset] & nth_bit) {
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
		#define obstacle_type scene_stage[stage].dat.byte[offset]
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
			obstacles.type_frames[obstacle_slot - 1] = 0; // Again?!
			break;
		}
		#undef obstacle_type
	}

	if(first_stage_in_scene == true) {
		for(i = 0; i < cards.count; i++) {
			card_ptn_id = CARD_ANIM[cards.hp[i]][0];
			ptn_put_8(cards.left[i], cards.top[i], card_ptn_id);
		}
		return;
	}

	#define CEL_START 2 // *_EDGE
	#define CEL_END 4 // Regular card with one less HP
	#define FRAMES_PER_CEL 6

	// ZUN bug: Should be STAGEOBJS_COUNT. This effectively limits stages to a
	// maximum of 50 cards rather than the original 200, since...
	struct hack { int x[50]; }; // XXX
	extern hack stageobjs_init_anim_card_frames;

	hack frames_for = stageobjs_init_anim_card_frames;
	// ... [total_frames] is the next variable on the stack. Therefore, ...
	int total_frames = 0;
	while(1) {
		int cards_animated = 0;
		for(i = 0; i < cards.count; i++) {
			if(frames_for.x[i] == -1) {
				cards_animated++;
			}
			if(frames_for.x[i] < (CEL_START * FRAMES_PER_CEL)) {
				continue;
			}
			if((frames_for.x[i] % FRAMES_PER_CEL) == 0) {
				card_ptn_id = (
					CARD_ANIM[cards.hp[i] + 1][frames_for.x[i] / FRAMES_PER_CEL]
				);
				ptn_put_8(cards.left[i], cards.top[i], card_ptn_id);
			}
			frames_for.x[i]++;
			// ... trying to access the 51st card here actually accesses
			// [total_frames], periodically resetting it to -1. Which in turn
			// means that...
			if(frames_for.x[i] > (CEL_END * FRAMES_PER_CEL)) {
				frames_for.x[i] = -1;
			}
		}
		if(cards_animated >= cards.count) {
			break;
		}
		// ... the first 24 cards are animated over and over in an infinite
		// loop, as the termination condition above can never become true.
		if(total_frames < cards.count) {
			frames_for.x[total_frames] = (CEL_START * FRAMES_PER_CEL);
		}
		total_frames++;
		frame_delay(1);
	}

	#undef FRAMES_PER_CEL
	#undef CEL_END
	#undef CEL_START

	#undef nth_bit
	#undef offset
}
