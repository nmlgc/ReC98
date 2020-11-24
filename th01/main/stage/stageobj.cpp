extern "C" {
#include <stddef.h>
#include <malloc.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/common.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/hardware/graph.h"
#include "th01/main/stage/stages.hpp"
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
