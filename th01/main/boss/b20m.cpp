/// Makai Stage 20 Boss - Sariel
/// ----------------------------

extern "C" {
#include <stddef.h>
#include <dos.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/math/area.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/ptrans.hpp"
#include "th01/hardware/scrollup.hpp"
#include "th01/hardware/input.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"
#include "th01/formats/grp.h"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/spawnray.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/player/player.hpp"
}
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"

// Coordinates
// -----------

static const screen_x_t SHIELD_LEFT = 304;
static const screen_y_t SHIELD_TOP = 144;
static const screen_x_t DRESS_LEFT = 280;
static const screen_x_t DRESS_TOP = 192;
static const screen_x_t WAND_LEFT = 296;
static const screen_y_t WAND_TOP = 48;

// MODDERS: That's 32 more than BOSS6_2.BOS is wide? Reducing it to 96 works
// fine as well.
static const pixel_t WAND_W = 128;

static const pixel_t WAND_H = 96;
// -----------

enum sariel_colors_t {
	COL_BIRD = 15, // Yes, just a single one, changed by the background image.
};

#define pattern_state	sariel_pattern_state
#define flash_colors	sariel_flash_colors
#define invincible	sariel_invincible
#define invincibility_frame	sariel_invincibility_frame
#define initial_hp_rendered	sariel_initial_hp_rendered
extern union {
	int unknown;
} pattern_state;
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// File names
// ----------

#include "th01/shiftjis/fns.hpp"

extern const char* BG_IMAGES[4];
// ----------

// Entities (and animations)
// --------

#define ent_shield	boss_entities[0]
#define anm_dress 	boss_anims[0]
#define anm_wand  	boss_anims[1]

inline void sariel_ent_load(void) {
	ent_shield.load("boss6_1.bos", 0);
	anm_wand.load("boss6_2.bos", 0);
	anm_dress.load("boss6_3.bos", 1);
}

inline void sariel_ent_free(void) {
	bos_entity_free(0);
	bos_anim_free(0);
	bos_anim_free(1);
}
// --------

/// .GRC entities
/// -------------

static const main_grc_slot_t GRC_SLOT_VORTEX_DEBRIS = GRC_SLOT_BOSS_1;
static const main_grc_slot_t GRC_SLOT_BIRD = GRC_SLOT_BOSS_2;
static const main_grc_slot_t GRC_SLOT_SPAWNCROSS = GRC_SLOT_BOSS_3;
static const main_grc_slot_t GRC_SLOT_LEAFSPLASH = GRC_SLOT_BOSS_4;

inline void sariel_grc_load(void) {
	grc_load(GRC_SLOT_VORTEX_DEBRIS, "boss6gr1.grc");
	grc_load(GRC_SLOT_BIRD, "boss6gr2.grc");
	grc_load(GRC_SLOT_SPAWNCROSS, "boss6gr3.grc");
	grc_load(GRC_SLOT_LEAFSPLASH, "boss6gr4.grc");
}

inline void sariel_grc_free(void) {
	grc_free(GRC_SLOT_VORTEX_DEBRIS);
	grc_free(GRC_SLOT_BIRD);
	grc_free(GRC_SLOT_SPAWNCROSS);
	grc_free(GRC_SLOT_LEAFSPLASH);
}

// For some reason, all of this code assumes .GRC entities to be 48×32, rather
// than 32×32. Why?!
#define sloppy_unput_32x32(left, top) \
	egc_copy_rect_1_to_0_16(left, top, 48, 32);

// Birds (BOSS6GR2.GRC)
// --------------------

static const pixel_t BIRD_W = 32;
static const pixel_t BIRD_H = 32;

static const int BIRD_COUNT = 30;
static const int BIRD_HATCH_CELS = 5;
static const int BIRD_FLY_CELS = 2;

enum bird_cel_t {
	C_HATCH = 1,
	C_HATCH_last = (C_HATCH + BIRD_HATCH_CELS - 1),
	C_FLY,
	C_FLY_last = (C_FLY + BIRD_FLY_CELS - 1),
};

#define bird_put_8(left, top, cel) \
	grc_put_8(left, top, GRC_SLOT_BIRD, cel, COL_BIRD);
// --------------------
/// -------------

// .PTN
// ----

// The original wand sprite together with its background, as it appears in the
// .GRP images, snapped from VRAM.
static const main_ptn_slot_t PTN_SLOT_WAND_LOWERED = PTN_SLOT_BOSS_1;
// ----

// Temporary storage for compiler-generated string literals
// --------------------------------------------------------

char ANGEL[] = "ANGEL";
char OF[] = "OF";
char DEATH[] = "DEATH";
char boss6_a1_grp[] = "BOSS6_A1.GRP";
char boss6_a2_grp[] = "BOSS6_A2.GRP";
char boss6_a3_grp[] = "BOSS6_A3.GRP";
char boss6_a4_grp[] = "BOSS6_A4.GRP";
// --------------------------------------------------------

#define select_for_rank sariel_select_for_rank
#include "th01/main/select_r.cpp"

void sariel_entrance(int8_t)
{
	pellet_interlace = true;

	text_fillca(' ', (TX_BLACK | TX_REVERSE));

	/*  graph_accesspage_func(0);  */	grp_put_palette_show("boss6_l.grp");
	/**/graph_accesspage_func(1)/**/;	grp_put_palette_show("boss6_h.grp");

	graph_accesspage_func(0);
	stageobjs_init_and_render(BOSS_STAGE);
	mdrv2_bgm_load("TENSI.MDT");
	mdrv2_se_load(SE_FN);
	mdrv2_bgm_play();

	text_fillca(' ', TX_WHITE);

	// Scroll
	// ------

	for(pixel_t line_on_top = (RES_Y - 1); line_on_top >= 0; line_on_top--) {
		z_vsync_wait_and_scrollup(line_on_top);
		egc_copy_rows_1_to_0(line_on_top, 1);
		frame_delay(1);
	}
	z_vsync_wait_and_scrollup(0);
	// ------

	graph_accesspage_func(1);
	grp_put_palette_show(BG_IMAGES[0]);
	graph_accesspage_func(0);
	pagetrans_diagonal_8x8(40);

	random_seed = frame_rand;
}

void sariel_load_and_init(void)
{
	sariel_ent_load();
	sariel_grc_load();
	boss_palette_snap();
	void sariel_setup(void);
	sariel_setup();
	ptn_new(
		PTN_SLOT_WAND_LOWERED, (((WAND_W / PTN_W) * (WAND_H / PTN_H)) + 4)
	); // ?
}

void sariel_setup(void)
{
	ent_shield.pos_set(SHIELD_LEFT, SHIELD_TOP, 48, 0, RES_X, 0, RES_Y);
	ent_shield.hitbox_set(0, 0, 48, 48);
	boss_hp = 18;
	hud_hp_first_white = 8;
	hud_hp_first_redwhite = 2;
	boss_phase = 0;
	boss_phase_frame = 0;
	ent_shield.hitbox_orb_inactive = false;
	anm_dress.left = DRESS_LEFT;
	anm_dress.top = DRESS_TOP;
	anm_wand.left = WAND_LEFT;
	anm_wand.top = WAND_TOP;
}

void near wand_lowered_snap(void)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left = anm_wand.left;
	screen_y_t top = anm_wand.top;
	int image = 0;

	ptn_snap_rect_from_1_8(
		left, top, WAND_W, WAND_H, PTN_SLOT_WAND_LOWERED, image, ptn_x, ptn_y
	);
}

void near wand_lowered_put(void)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left;
	screen_y_t top;
	int image;

	image = 0;
	left = anm_wand.left;
	top = anm_wand.top;

	ptn_put_rect_noalpha_8(
		left, top, WAND_W, WAND_H, PTN_SLOT_WAND_LOWERED, image, ptn_x, ptn_y
	)
}

void sariel_free(void)
{
	sariel_ent_free();
	sariel_grc_free();
	ptn_free(PTN_SLOT_WAND_LOWERED);
}

// Almost identical to Konngara's version. This one is worse.
void pascal near spawnray_unput_and_put(
	screen_x_t origin_x, vram_y_t origin_y,
	screen_x_t target_x, vram_y_t target_y,
	int col
)
{
	#define target_prev_x	spawnray_target_prev_x
	#define target_prev_y	spawnray_target_prev_y

	extern screen_x_t target_prev_x;
	extern vram_y_t target_prev_y;
	spawnray_unput_and_put_func(
		target_prev_x, target_prev_y,
		origin_x, origin_y, target_x, target_y, col, true
	);

	#undef target_prev_x
	#undef target_prev_y
}

enum bird_pellet_group_t {
	BPG_AIMED = 0,
	BPG_6_RING = 1,
	BPG_RANDOM_RAIN = 2,
};

static const int BF_UNPUT_UPDATE_RENDER = 0;
static const int BF_RESET = 1000;
static const int BF_FIRE = 1001;

void pascal near birds_reset_fire_spawn_unput_update_render(
	double func_or_left,
	double top = 0.0f,
	double velocity_x = 0.0f,
	double velocity_y = 0.0f,
	int8_t unknown = 0
)
{
	extern char birds_alive[BIRD_COUNT]; // Should be bool.
	extern struct {
		double left[BIRD_COUNT];
		double top[BIRD_COUNT];
		double velocity_x[BIRD_COUNT];
		double velocity_y[BIRD_COUNT];
		int8_t unknown[BIRD_COUNT];
		char hatch_time[BIRD_COUNT];
		char hatch_duration[BIRD_COUNT];

		double pellet_left(int i) {
			return (left[i] + ((BIRD_W / 2) - (PELLET_W / 2)));
		}

		double pellet_top(int i) {
			return (top[i] + ((BIRD_H / 2) - (PELLET_H / 2)));
		}

		// Yes, this is a genuine ZUN abstraction, nothing I refactored.
		// Why would you not just have a per-instance spawn() method?!
		void set_velocity_and_hatch_time(
			const double velocity_x, const double velocity_y,
			double& out_velocity_x, double& out_velocity_y, char& hatch_time
		) {
			out_velocity_x = velocity_x;
			out_velocity_y = velocity_y;
			hatch_time = 25;
		}
	} birds;

	if(func_or_left == BF_RESET) {
		for(int i = 0; i < BIRD_COUNT; i++) {
			birds_alive[i] = false;
		}
	} else if(func_or_left == (BF_FIRE + BPG_AIMED)) {
		for(int i = 0; i < BIRD_COUNT; i++) {
			if(!birds_alive[i] || birds.hatch_time[i]) {
				continue;
			}
			Pellets.add_group(
				birds.pellet_left(i),
				birds.pellet_top(i),
				PG_1_AIMED,
				to_sp(3.0f)
			);
		}
	} else if(func_or_left == (BF_FIRE + BPG_6_RING)) {
		for(int i = 0; i < BIRD_COUNT; i++) {
			if(!birds_alive[i] || birds.hatch_time[i]) {
				continue;
			}
			for(int j = 0; j < 6; j++) {
				Pellets.add_single(
					birds.pellet_left(i),
					birds.pellet_top(i),
					(j * (0x100 / 6)),
					to_sp(4.0f)
				);
			}
		}
	} else if(func_or_left == (BF_FIRE + BPG_RANDOM_RAIN)) {
		for(int i = 0; i < BIRD_COUNT; i++) {
			if(!birds_alive[i] || birds.hatch_time[i]) {
				continue;
			}
			Pellets.add_single(
				birds.pellet_left(i),
				birds.pellet_top(i),
				((rand() & 0x7F) + 0x80),
				to_sp(4.0f),
				PM_GRAVITY,
				to_sp(0.1f)
			);
		}
	} else if(func_or_left != BF_UNPUT_UPDATE_RENDER) {
		// (Yes, this prevents birds from being spawned at [left] == 0.)
		for(int i = 0; i < BIRD_COUNT; i++) {
			if(birds_alive[i] != true) {
				birds_alive[i] = true;
				birds.set_velocity_and_hatch_time(
					velocity_x,
					velocity_y,
					birds.velocity_x[i],
					birds.velocity_y[i],
					birds.hatch_time[i]
				);
				birds.left[i] = func_or_left;
				birds.top[i] = top;
				birds.unknown[i] = unknown;
				birds.hatch_duration[i] = birds.hatch_time[i];
				return;
			}
		}
	} else {
		int i;
		for(i = 0; i < BIRD_COUNT; i++) {
			if(!birds_alive[i]) {
				continue;
			}
			if(birds.hatch_time[i] > 0) {
				bird_put_8(birds.left[i], birds.top[i], ((
					(birds.hatch_duration[i] - birds.hatch_time[i]) /
					(birds.hatch_duration[i] / BIRD_HATCH_CELS)
				) + C_HATCH));
				birds.hatch_time[i]--;
			} else {
				// ZUN bug: Shouldn't these be unblitted unconditionally?
				// Because they aren't, each cel of the hatch animation is
				// blitted on top of the previous one...
				sloppy_unput_32x32(birds.left[i], birds.top[i]);
			}
		}
		for(i = 0; i < BIRD_COUNT; i++) {
			if(!birds_alive[i] || birds.hatch_time[i]) {
				continue;
			}
			birds.left[i] += birds.velocity_x[i];
			birds.top[i] += birds.velocity_y[i];
			if(!overlap_xy_lrtb_le_ge(
				birds.left[i], birds.top[i], 0, 0, (RES_X - 1), (RES_Y - 1)
			)) {
				sloppy_unput_32x32(birds.left[i], birds.top[i]);
				birds_alive[i] = false;
				continue;
			}
			bird_put_8(birds.left[i], birds.top[i], (
				C_FLY + ((boss_phase_frame / 5) % BIRD_FLY_CELS)
			));
			// 14×38 pixels… still unfair given the shape of such a bird.
			if(
				!player_invincible &&
				(birds.left[i] > (player_left - (PLAYER_W / 4))) &&
				(birds.left[i] < (player_left + (PLAYER_W / 4))) &&
				(birds.top[i] > (player_top - (PLAYER_H / 2) - (BIRD_H / 4))) &&
				(birds.top[i] < (player_top + (PLAYER_H / 2)))
			) {
				done = true;
				delay(100); // ???
				return;
			}
		}
	}
}

void near shield_render_both(void)
{
	enum {
		CELS = 4,
		FRAMES_PER_CEL = 10,
	};
	if((boss_phase_frame % FRAMES_PER_CEL) != 0) {
		return;
	}
	int cel = ((boss_phase_frame % (FRAMES_PER_CEL * CELS)) / FRAMES_PER_CEL);
	ent_shield.bos_image = cel;
	graph_accesspage_func(1);	ent_shield.move_lock_and_put_8();
	graph_accesspage_func(0);	ent_shield.move_lock_and_put_8();
}

// Renders a frame of Sariel's wand raise animation on both VRAM pages, and
// returns `true` once the animation completed.
bool16 pascal near wand_render_raise_both(bool16 restart = false)
{
	#define frames wand_raise_frames

	extern int frames;

	if(restart == true) {
		frames = 0;
	} else if (frames == 0) {
		frames = 1;
	} else {
		frames++;
		if(frames == 2) {
			anm_wand.bos_image = 0;
			graph_accesspage_func(1);	anm_wand.put_8();
			graph_accesspage_func(0);	anm_wand.put_8();
		} else if(frames == 16) {
			anm_wand.bos_image = 1;
			graph_accesspage_func(1);	anm_wand.put_8();
			graph_accesspage_func(0);	anm_wand.put_8();
			frames = 0;
			return true;
		}
	}
	return false;

	#undef frames
}

// Should maybe return `false`, for consistency with wand_render_raise_both().
void near wand_lower_both(void)
{
	graph_accesspage_func(1);	wand_lowered_put();
	graph_accesspage_func(0);	wand_lowered_put();
}
