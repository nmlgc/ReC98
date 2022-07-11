/// Jigoku Stage 10 Boss - Mima
/// ---------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/egc.h"
extern "C" {
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"
}
#include "th01/formats/grp.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/shiftjis/fns.hpp"
#undef MISSILE_FN
#define MISSILE_FN boss3_m_ptn_0
extern const char MISSILE_FN[];
#include "th01/main/particle.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/hud/hp.hpp"

// Coordinates
// -----------

static const pixel_t MIMA_W = 128;
static const pixel_t MIMA_H = 160;

static const pixel_t MIMA_ANIM_TOP = 48; // relative to the sprite's top edge
static const pixel_t MIMA_ANIM_H = 64;
// -----------

#define meteor_active	mima_meteor_active
#define spreadin_interval	mima_spreadin_interval
#define spreadin_speed	mima_spreadin_speed
#define flash_colors	mima_flash_colors
#define invincibility_frame	mima_invincibility_frame
#define invincible	mima_invincible
#define initial_hp_rendered	mima_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

extern bool meteor_active;

// Amount of frames between the individual steps of the spread-in transition
extern uint8_t spreadin_interval;
// Sprite pixels to spread in per frame, in one half of Mima's sprite
extern uint8_t spreadin_speed;

// File names
// ----------

extern const char boss3_1_bos[];
extern const char boss3_2_bos[];
extern const char boss3_grp_0[];
extern const char boss5_gr_grc[];
// ----------

// Entities
// --------

static const int METEOR_CELS = 4;

enum anim_cel_t {
	C_CAST = 0,
	C_METEOR = 1,
	C_METEOR_last = (C_METEOR + METEOR_CELS - 1),
};

#define ent_still	boss_entities[0]
#define ent_anim 	boss_entities[1]

inline void mima_ent_load(void) {
	ent_still.load(boss3_1_bos, 0);
	ent_anim.load(boss3_2_bos, 1);
}

inline void mima_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
}
// --------

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;

// Three unused background .PTN IDs, for three unused 32×32 animations?
static const int BG_ENT_OFFSET = 3;
// ----

// Patterns
// --------

#define pattern_state mima_pattern_state
extern union {
} pattern_state;
// --------

void mima_load(void)
{
	int col;
	int comp;

	mima_ent_load();
	grp_palette_load_show(boss3_grp_0);
	palette_copy(boss_post_defeat_palette, z_Palettes, col, comp);
	void mima_setup(void);
	mima_setup();
	ptn_new(
		PTN_SLOT_BG_ENT,
		(((MIMA_W / PTN_W) * (MIMA_H / PTN_H)) + BG_ENT_OFFSET + 1)
	);
	Missiles.load(PTN_SLOT_MISSILE);
	Missiles.reset();
}

inline void ent_anim_sync_with_still(void) {
	ent_anim.pos_cur_set(
		ent_still.cur_left, (ent_still.cur_top + MIMA_ANIM_TOP)
	);
}

inline void ent_anim_sync_with_still_and_put_both(int cel) {
	ent_anim_sync_with_still();
	ent_anim.set_image(cel);
	graph_accesspage_func(1);	ent_anim.put_8(cel);
	graph_accesspage_func(0);	ent_anim.put_8(cel);
}

void meteor_put(void)
{
	if(meteor_active && ((boss_phase_frame % 8) == 0)) {
		ent_anim_sync_with_still();
		ent_anim.set_image_unput_and_put_8(
			(C_METEOR + ((boss_phase_frame / 8) % METEOR_CELS))
		);
	}
}

void mima_put_cast_both(void)
{
	meteor_active = false;
	ent_anim_sync_with_still_and_put_both(C_CAST);
}

void meteor_activate(void)
{
	if(!meteor_active) {
		meteor_active = true;
		ent_anim_sync_with_still_and_put_both(C_METEOR);
	}
}

void mima_put_still_both(void)
{
	graph_accesspage_func(1);	ent_still.put_8();
	graph_accesspage_func(0);	ent_still.put_8();
}

void mima_bg_snap(void)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left = ent_still.cur_left;
	screen_y_t top = ent_still.cur_top;
	int image = BG_ENT_OFFSET;

	ptn_snap_rect_from_1_8(
		left, top, MIMA_W, MIMA_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
	);
}

void mima_unput(bool16 just_the_animated_part = false)
{
	int ptn_x;
	int image = BG_ENT_OFFSET;
	screen_x_t left = ent_still.cur_left;
	screen_y_t top = ent_still.cur_top;

	if(!just_the_animated_part) {
		int ptn_y;
		ptn_put_rect_noalpha_8(
			left, top, MIMA_W, MIMA_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
		);
		return;
	}

	// (The code below is never executed in the original game.)

	// Advance to the .PTN background row that contains the background behind
	// the animating part of Mima's sprite (i.e., the second one)
	image = (BG_ENT_OFFSET + ((MIMA_ANIM_TOP / PTN_H) * (MIMA_W / PTN_W)));

	// And since MIMA_ANIM_TOP is only a multiple of 16 and not 32, we have to
	// first awkwardly unblit a MIMA_W×16 area...
	for(ptn_x = 0; ptn_x < (MIMA_W / PTN_W); ptn_x++) {
		ptn_put_quarter_noalpha_8(
			(left + (0 * PTN_QUARTER_W) + (ptn_x * PTN_W)),
			(top + MIMA_ANIM_TOP),
			PTN_ID(PTN_SLOT_BG_ENT, image),
			(((MIMA_ANIM_TOP % PTN_H) / PTN_QUARTER_H) * 2)
		);
		ptn_put_quarter_noalpha_8(
			(left + (1 * PTN_QUARTER_W) + (ptn_x * PTN_W)),
			(top + MIMA_ANIM_TOP),
			PTN_ID(PTN_SLOT_BG_ENT, image),
			((((MIMA_ANIM_TOP % PTN_H) / PTN_QUARTER_H) * 2) + 1)
		);
		image++;
	}

	// ZUN bug (?): Why is MIMA_ANIM_H assumed to be 48 (16 above + 32 here)?
	// This might have even worked if the bottom 16 pixels of all [ent_anim]
	// cels were identical, but they differ between C_CAST and C_METEOR.
	//
	// Note that this has nothing to do with Mima's infamous "third arm"
	// (remember, the game never executes this code), but wouldn't exactly
	// prevent it from happening either.
	#define bug_top (top + MIMA_ANIM_TOP + PTN_QUARTER_H)
	ptn_put_row_noalpha_8(left, bug_top, MIMA_W, PTN_SLOT_BG_ENT, image, ptn_x);
	#undef bug_top
}

inline pixel_t spreadin_bottom_cur(void) {
	return ((spreadin_speed / spreadin_interval) * (boss_phase_frame - 10));
}

void spreadin_unput_and_put(screen_x_t left, screen_y_t top)
{
	pixel_t row;
	pixel_t line_on_top;

	if(boss_phase_frame < 10) {
		return;
	} else if(boss_phase_frame == 10) {
		ent_still.pos_cur_set(left, top);
		mima_bg_snap();
		line_on_top = (top + (MIMA_H / 2));
		return;
	} else if((boss_phase_frame % spreadin_interval) != 0) {
		return;
	}

	line_on_top = ((MIMA_H / 2) - spreadin_bottom_cur());
	if(line_on_top < 0) {
		boss_phase_frame = 0;
		mima_put_still_both();
		return;
	}
	for(row = 0; spreadin_bottom_cur() > row; row++) {
		ent_still.unput_and_put_1line(
			left, (top + line_on_top + row), ent_still.image(), row
		);
		ent_still.unput_and_put_1line(
			left,
			((top + MIMA_H) - line_on_top - row),
			ent_still.image(),
			((MIMA_H - 1) - row)
		);
	}

}

// Only called while Mima isn't visible anyway. But even apart from that, it
// barely would have any effect anywhere, as the Mima sprite is blitted to both
// VRAM pages. This *might* have been supposed to crossfade between various
// cels? …Nah, why would you do that by blitting whole lines.
void mima_vertical_sprite_transition_broken(void)
{
	if((boss_phase_frame < 10) || ((boss_phase_frame % 4) != 0)) {
		return;
	}
	pixel_t half_h = ((boss_phase_frame - 10) * 2);
	if(half_h >= (MIMA_H / 2)) {
		boss_phase_frame = 0;
		return;
	}
	// And besides, *VRAM width*?! This is completely broken.
	egc_copy_rect_1_to_0_16(
		ent_still.cur_left, (ent_still.cur_top + half_h), ent_still.vram_w, 8
	);
	egc_copy_rect_1_to_0_16(
		ent_still.cur_left,
		(ent_still.cur_top + (MIMA_H - 8) - half_h),
		ent_still.vram_w,
		8
	);
}

void mima_setup(void)
{
	boss_palette_snap();
	ent_still.set_image(0);
	ent_anim.set_image(C_METEOR);
	z_palette_white_in();
	ent_still.pos_set((PLAYFIELD_CENTER_X - (MIMA_W / 2)), PLAYFIELD_TOP);
	ent_still.hitbox_orb_set(
		((MIMA_W / 8) * 1), ((MIMA_H / 10) * 1),
		((MIMA_W / 8) * 7), ((MIMA_H / 10) * 9)
	);
	ent_still.hitbox_orb_inactive = false;
	boss_phase_frame = 0;
	boss_phase = 0;
	boss_hp = 12;
	hud_hp_first_white = 6;
	hud_hp_first_redwhite = 2;
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

void mima_free(void)
{
	mima_ent_free();
	ptn_free(PTN_SLOT_BG_ENT);
	ptn_free(PTN_SLOT_MISSILE);
}

#define select_for_rank mima_select_for_rank
#include "th01/main/select_r.cpp"
