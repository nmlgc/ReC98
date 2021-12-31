/// Makai Stage 20 Boss - Sariel
/// ----------------------------

extern "C" {
#include <stddef.h>
#include <stdlib.h>
#include <dos.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/palette.h"
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
#include "th01/main/stage/palette.hpp"
}
#include "th01/main/shape.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/hud/hud.hpp"

// Coordinates
// -----------

static const screen_x_t SHIELD_LEFT = 304;
static const screen_y_t SHIELD_TOP = 144;
static const screen_x_t DRESS_LEFT = 280;
static const screen_y_t DRESS_TOP = 192;
static const screen_x_t WAND_LEFT = 296;
static const screen_y_t WAND_TOP = 48;

static const screen_y_t SHIELD_CENTER_X = 320;
static const screen_y_t SHIELD_CENTER_Y = 164;

// That's… not quite where the sphere is?
static const screen_x_t WAND_EMIT_LEFT = 340;
static const screen_y_t WAND_EMIT_TOP = 64;

// MODDERS: That's 32 more than BOSS6_2.BOS is wide? Reducing it to 96 works
// fine as well.
static const pixel_t WAND_W = 128;

static const pixel_t WAND_H = 96;
// -----------

enum sariel_colors_t {
	COL_LASER = 4,
	COL_AIR = 12,
	COL_BIRD = 15, // Yes, just a single one, changed by the background image.
};

#define pattern_state	sariel_pattern_state
#define flash_colors	sariel_flash_colors
#define invincible	sariel_invincible
#define invincibility_frame	sariel_invincibility_frame
#define initial_hp_rendered	sariel_initial_hp_rendered
extern union {
	int frame;
	int speed_multiplied_by_8;
	int interval;
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

// Vortex and debris sprites (BOSS6GR1.GRC)
// ----------------------------------------

static const pixel_t VORTEX_W = 32;
static const pixel_t VORTEX_H = 32;

static const int VORTEX_COUNT = 2;

enum vortex_or_debris_cel_t {
	VORTEX_CELS = 3,

	C_VORTEX = 0,
	C_VORTEX_last = (C_VORTEX + VORTEX_CELS - 1),
};

#define vortex_or_debris_put_8(left, top, cel) \
	grc_put_8(left, top, GRC_SLOT_VORTEX_DEBRIS, cel, V_WHITE);
// ----------------------------------------

// Birds (BOSS6GR2.GRC)
// --------------------

static const pixel_t BIRD_W = 32;
static const pixel_t BIRD_H = 32;

static const int BIRD_COUNT = 30;
static const int BIRD_HATCH_CELS = 5;
static const int BIRD_FLY_CELS = 2;

enum bird_cel_t {
	C_EGG = 0,
	C_HATCH,
	C_HATCH_last = (C_HATCH + BIRD_HATCH_CELS - 1),
	C_FLY,
	C_FLY_last = (C_FLY + BIRD_FLY_CELS - 1),
};

#define bird_put_8(left, top, cel) \
	grc_put_8(left, top, GRC_SLOT_BIRD, cel, COL_BIRD);
// --------------------

// Spawn cross (BOSS6GR3.GRC)
// --------------------------

static const pixel_t SPAWNCROSS_W = 32;
static const pixel_t SPAWNCROSS_H = 32;
static const int SPAWNCROSS_CELS = 2;
// --------------------------
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

#define birds_spawn(left, top, velocity_x, velocity_y) \
	birds_reset_fire_spawn_unput_update_render( \
		left, top, velocity_x, velocity_y, 1 \
	);

#define birds_fire(pellet_group) \
	birds_reset_fire_spawn_unput_update_render(BF_FIRE + pellet_group);

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

void near dress_render_both(void)
{
	enum {
		CELS = 4,
		FRAMES_PER_CEL = 15,
	};
	if((boss_phase_frame % FRAMES_PER_CEL) != 0) {
		return;
	}
	int cel = ((boss_phase_frame % (FRAMES_PER_CEL * CELS)) / FRAMES_PER_CEL);
	anm_dress.bos_image = cel;
	graph_accesspage_func(1);	anm_dress.put_8();
	graph_accesspage_func(0);	anm_dress.put_8();
}

static const subpixel_t VORTEX_PELLET_SPEED = TO_SP(7);

#define vortex_pellet_left(vortex_left) \
	((vortex_left) + ((VORTEX_W / 2) - (PELLET_W / 2)))

#define vortex_pellet_top(vortex_top) \
	((vortex_top) + ((VORTEX_H / 2) - (PELLET_H / 2)))

inline screen_y_t vortex_pellet_bottom(screen_y_t vortex_bottom) {
	return (vortex_bottom - ((VORTEX_H / 2) - (PELLET_H / 2)));
}

// Shouldn't really take [angle] as a parameter...
void pascal near vortex_fire_3_spread(
	const screen_x_t left[VORTEX_COUNT],
	const vram_y_t top[VORTEX_COUNT],
	int i,
	unsigned char angle
)
{
	Pellets.add_single(
		vortex_pellet_left(left[i]),
		vortex_pellet_top(top[i]),
		0x40,
		VORTEX_PELLET_SPEED
	);
	angle = iatan2(
		(vortex_pellet_bottom(PLAYFIELD_BOTTOM) - top[i]),
		(left[1 - i] - left[i])
	);
	Pellets.add_single(
		vortex_pellet_left(left[i]),
		vortex_pellet_top(top[i]),
		angle,
		VORTEX_PELLET_SPEED
	);
	Pellets.add_single(
		vortex_pellet_left(left[i]),
		vortex_pellet_top(top[i]),
		(0x80 - angle),
		VORTEX_PELLET_SPEED
	);
}

void near pattern_vortices(void)
{
	#define wand_raise_animation_done	pattern1_wand_raise_animation_done
	#define cur_left                 	pattern1_cur_left
	#define cur_top                  	pattern1_cur_top
	#define prev_left                	pattern1_prev_left
	#define prev_top                 	pattern1_prev_top
	#define dir_first                	pattern1_dir_first
	#define dir_second               	pattern1_dir_second

	extern bool16 wand_raise_animation_done;
	extern screen_x_t cur_left[VORTEX_COUNT];
	extern vram_y_t cur_top[VORTEX_COUNT];
	extern screen_x_t prev_left[VORTEX_COUNT];
	extern vram_y_t prev_top[VORTEX_COUNT];
	extern bool16 dir_first; // x_direction_t
	extern bool16 dir_second; // x_direction_t

	#define vortex_unput_and_put_8(i) { \
		sloppy_unput_32x32(prev_left[i], prev_top[i]); \
		vortex_or_debris_put_8( \
			cur_left[i], \
			cur_top[i], \
			(C_VORTEX + (boss_phase_frame % VORTEX_CELS)) \
		); \
	}

	#define vortex_fire_down(i) { \
		Pellets.add_group( \
			vortex_pellet_left(cur_left[i]), \
			vortex_pellet_top(cur_top[i]), \
			PG_1, \
			VORTEX_PELLET_SPEED \
		); \
	}

	#define vortex_unput_put_3_spread(i) { \
		vortex_unput_and_put_8(i); \
		if((boss_phase_frame % 4) == 0) { \
			vortex_fire_3_spread(cur_left, cur_top, i, angle); \
		} \
	}

	unsigned char angle;

	if(wand_raise_animation_done == false) {
		wand_raise_animation_done = wand_render_raise_both();
	}

	if(boss_phase_frame < 50) {
		return;
	} else if(boss_phase_frame == 50) {
		select_for_rank(pattern_state.frame, 140, 145, 150, 155);
	}
	if(boss_phase_frame < 100) {
		for(int i = 0; i < VORTEX_COUNT; i++) {
			cur_left[i] = (i * (PLAYFIELD_RIGHT - VORTEX_W));
			cur_top[i] = (PLAYFIELD_TOP + playfield_fraction_y(17 / 42.0f));

			vortex_unput_and_put_8(i);
			if((boss_phase_frame % 4) == 0) {
				vortex_fire_down(i);
			}
			prev_left[i] = cur_left[i];
			prev_top[i] = cur_top[i];
		}
	} else if(boss_phase_frame < pattern_state.frame) {
		for(int i = 0; i < VORTEX_COUNT; i++) {
			cur_left[i] += (i == 0) ? 5 : -5;
			cur_top[i] -= 2;

			vortex_unput_and_put_8(i);
			if((boss_phase_frame % 4) == 0) {
				vortex_fire_down(i);
				angle = iatan2(
					vortex_pellet_top(PLAYFIELD_BOTTOM - cur_top[i]),
					vortex_pellet_left(cur_left[i] +
						(i * ((PLAYFIELD_W / 8) * 2)) - (PLAYFIELD_W / 8) -
					cur_left[i])
				);
				Pellets.add_single(
					vortex_pellet_left(cur_left[i]),
					vortex_pellet_top(cur_top[i]),
					angle,
					VORTEX_PELLET_SPEED
				);
			}
			prev_left[i] = cur_left[i];
			prev_top[i] = cur_top[i];
		}
	} else if(boss_phase_frame < 200) {
		for(int i = 0; i < VORTEX_COUNT; i++) {
			vortex_unput_put_3_spread(i);
		}
	} else if(boss_phase_frame < 240) {
		if(boss_phase_frame == 200) {
			static_cast<int>(dir_first) = (rand() % 2);
			if(dir_first == X_LEFT) {
				wand_lower_both();
			}
		}
		for(int i = 0; i < VORTEX_COUNT; i++) {
			cur_left[i] += (2 - (dir_first * 4));
			vortex_unput_put_3_spread(i);
			prev_left[i] = cur_left[i];
		}
	} else if(boss_phase_frame < 320) {
		if(boss_phase_frame == 240) {
			static_cast<int>(dir_second) = (rand() % 2);
			if((dir_second == X_RIGHT) && (dir_second == dir_first)) {
				wand_lower_both();
			} else if((dir_second == X_LEFT) && (dir_second == dir_first)) {
				wand_raise_animation_done = false;
			}
		}
		for(int i = 0; i < VORTEX_COUNT; i++) {
			if(dir_second != dir_first) {
				cur_left[i] -= (2 - (dir_second * 4));
			} else {
				cur_left[i] -= (4 - (dir_second * 8));
			}
			vortex_unput_put_3_spread(i);
			prev_left[i] = cur_left[i];
		}
	} else if(boss_phase_frame > 300) {
		for(int i = 0; i < VORTEX_COUNT; i++) {
			sloppy_unput_32x32(cur_left[i], cur_top[i]);
		}
		wand_lower_both();
		boss_phase_frame = 0;
		wand_raise_animation_done = false;
	}

	#undef vortex_unput_put_3_spread
	#undef vortex_fire_down
	#undef vortex_unput_and_put_8

	#undef dir_second
	#undef dir_first
	#undef prev_top
	#undef prev_left
	#undef cur_top
	#undef cur_left
	#undef wand_raise_animation_done
}

void near pattern_random_purple_lasers(void)
{
	enum {
		LASER_COUNT = 10,
		INTERVAL = 10,

		KEYFRAME_0 = 50,
		KEYFRAME_1 = (KEYFRAME_0 + (LASER_COUNT * INTERVAL)),
		KEYFRAME_2 = (KEYFRAME_1 + 50),
	};

	#define spawner_x	pattern0_spawner_x
	#define spawner_y	pattern0_spawner_y

	extern screen_x_t spawner_x[LASER_COUNT];
	extern vram_y_t spawner_y[LASER_COUNT];

	if(boss_phase_frame < KEYFRAME_0) {
		return;
	}
	if(boss_phase_frame == KEYFRAME_0) {
		select_for_rank(pattern_state.speed_multiplied_by_8,
			(to_sp( 8.5f) / 2),
			(to_sp( 9.0f) / 2),
			(to_sp( 9.5f) / 2),
			(to_sp(10.0f) / 2)
		);
		for(int i = 0; i < LASER_COUNT; i++) {
			spawner_x[i] = (PLAYFIELD_LEFT +
				playfield_fraction_x(3 / 16.0f) + playfield_rand_x(10 / 16.0f)
			);
			spawner_y[i] = (PLAYFIELD_TOP +
				playfield_fraction_y(9 / 84.0f) + playfield_rand_y(25 / 84.0f)
			);
		}
	}
	if(boss_phase_frame < KEYFRAME_1) {
		int i = ((boss_phase_frame - KEYFRAME_0) / INTERVAL);
		if((boss_phase_frame % INTERVAL) != (INTERVAL - 1)) {
			int radius_cur  = (64 - (( boss_phase_frame      % INTERVAL) * 8));
			int radius_prev = (64 - (((boss_phase_frame - 1) % INTERVAL) * 8));
			if((boss_phase_frame % INTERVAL) != 0) {
				shape_circle_sloppy_unput(
					spawner_x[i], spawner_y[i], radius_prev, 1
				);
			}
			if((boss_phase_frame % INTERVAL) != (INTERVAL - 2)) {
				shape_circle_put(
					spawner_x[i], spawner_y[i], radius_cur, COL_LASER, 1
				);
			}
		} else {
			mdrv2_se_play(6);
			shootout_lasers[i].spawn(
				spawner_x[i],
				spawner_y[i],
				playfield_rand_x(),
				PLAYFIELD_BOTTOM,
				pattern_state.speed_multiplied_by_8,
				COL_LASER,
				25,
				5
			);
		}
	} else if(boss_phase_frame > KEYFRAME_2) {
		boss_phase_frame = 0;
	}

	#undef spawner_y
	#undef spawner_x
}

void near pattern_birds_on_ellipse_arc(void)
{
	#define wand_raise_animation_done	pattern2_wand_raise_animation_done
	#define pellet_group             	pattern2_pellet_group
	#define eggs_alive               	pattern2_eggs_alive
	#define spawner_left             	pattern2_spawner_left
	#define spawner_top              	pattern2_spawner_top
	#define spawner_velocity_x       	pattern2_spawner_velocity_x
	#define spawner_velocity_y       	pattern2_spawner_velocity_y
	#define egg_left                 	pattern2_egg_left
	#define egg_top                  	pattern2_egg_top

	extern bool wand_raise_animation_done;
	extern bird_pellet_group_t pellet_group;
	extern int eggs_alive;
	extern screen_x_t egg_left[BIRD_COUNT];
	extern vram_y_t egg_top[BIRD_COUNT];
	extern Subpixel spawner_left;
	extern Subpixel spawner_top;
	extern Subpixel spawner_velocity_y;
	extern Subpixel spawner_velocity_x;

	point_t velocity;

	if(boss_phase_frame < 40) {
		return;
	}

	if(wand_raise_animation_done == false) {
		wand_raise_animation_done = wand_render_raise_both();
	}
	if(boss_phase_frame < 50) {
		return;
	} else if(boss_phase_frame == 50) {
		eggs_alive = 0;
		spawner_left.v = to_sp(WAND_EMIT_LEFT);
		spawner_top.v = to_sp(WAND_EMIT_TOP);
		spawner_velocity_x.v = TO_SP(4 - ((rand() % 2) * 8));
		spawner_velocity_y.v = TO_SP(2 - ((rand() % 2) * 4));
		select_for_rank(pattern_state.interval, 20, 15, 10, 8);
		mdrv2_se_play(8);
	} else if(boss_phase_frame < 200) {
		if(spawner_left.v < to_sp(SHIELD_CENTER_X)) {
			spawner_velocity_x.v += to_sp(0.0625f);
		} else {
			spawner_velocity_x.v -= to_sp(0.0625f);
		}
		if(spawner_top.v < to_sp(SHIELD_CENTER_Y)) {
			spawner_velocity_y.v += to_sp(0.0625f);
		} else {
			spawner_velocity_y.v -= to_sp(0.0625f);
		}
		sloppy_unput_32x32(spawner_left.to_pixel(), spawner_top.to_pixel());
		for(int i = (eggs_alive - 1); i >= 0; i--) {
			bird_put_8(egg_left[i], egg_top[i], C_EGG);
		}
		spawner_left.v += spawner_velocity_x.v;
		spawner_top.v += spawner_velocity_y.v;
		if((boss_phase_frame % pattern_state.interval) == 0) {
			if(overlap_xy_lrtb_le_ge(
				spawner_left.v, spawner_top.v,
				to_sp(0.0), to_sp(0.0f),
				to_sp(RES_X - SPAWNCROSS_W), to_sp(RES_Y - SPAWNCROSS_H)
			)) {
				egg_left[eggs_alive] = spawner_left.to_pixel();
				egg_top[eggs_alive] = spawner_top.to_pixel();
				bird_put_8(
					spawner_left.to_pixel(), spawner_top.to_pixel(), C_EGG
				);
				eggs_alive++;
			}
		}
		grc_put_8(
			spawner_left.to_pixel(),
			spawner_top.to_pixel(),
			GRC_SLOT_SPAWNCROSS,
			(boss_phase_frame % SPAWNCROSS_CELS),
			((boss_phase_frame % 4) + 2)
		);
	} else if(boss_phase_frame < 400) {
		if(boss_phase_frame == 200) {
			if(abs(spawner_velocity_y.v) < to_sp(0.25f)) {
				spawner_velocity_y.v = (spawner_velocity_y.v < 0)
					? to_sp(-0.25f)
					: to_sp( 0.25f);
			}
			if(abs(spawner_velocity_x.v) < to_sp(0.25f)) {
				spawner_velocity_x.v = (spawner_velocity_x.v < 0)
					? to_sp(-0.25f)
					: to_sp( 0.25f);
			}
			for(int i = (eggs_alive - 1); i >= 0; i--) {
				vector2(velocity.x, velocity.y, 3, ((rand() & 0x7F) + 0x80));
				birds_spawn(egg_left[i], egg_top[i], velocity.x, velocity.y);
			}
			wand_lower_both();
			pellet_group = static_cast<bird_pellet_group_t>(
				rand() % (BPG_6_RING + 1) // excluding random rain here
			);
		}

		if(overlap_xy_lrtb_le_ge(
			spawner_left, spawner_top,
			to_sp(-SPAWNCROSS_W), to_sp(-SPAWNCROSS_H),
			to_sp(RES_X), to_sp(RES_Y)
		)) {
			sloppy_unput_32x32(spawner_left.to_pixel(), spawner_top.to_pixel());
			spawner_left.v += spawner_velocity_x.v;
			spawner_top.v += spawner_velocity_y.v;

			// ZUN bug: ZUN suddenly forgot that [spawner] uses subpixels, not
			// pixels. Comparing its position to the pixel equivalent of
			// 	((RES_X - SPAWNCROSS_W), (RES_Y - SPAWNCROSS_H))
			// effectively clips the top-left coordinate of the spawner to a
			// screen-space rectangle from (0, 0) to (38, 23). Since that's
			// quite far from its actual position, the code below never gets
			// executed.
			if(overlap_xy_lrtb_le_ge(
				spawner_left, spawner_top,
				0, 0,
				(RES_X - SPAWNCROSS_W), // should be subpixels
				(RES_Y - SPAWNCROSS_H) // should be subpixels
			)) {
				// ZUN bug: Also, here. Quite ironic given that there's a
				// correct version of this blitting call above… Copy-pasta
				// confirmed.
				grc_put_8(
					spawner_left, // should be pixels
					spawner_top, // should be pixels
					GRC_SLOT_SPAWNCROSS,
					(boss_phase_frame % SPAWNCROSS_CELS),
					((boss_phase_frame % 4) + 2)
				);
			}
		}
		if(((boss_phase_frame % 16) == 0) || ((boss_phase_frame % 16) == 2)) {
			birds_fire(pellet_group);
		}
	} else if(boss_phase_frame == 400) {
		boss_phase_frame = 0;
		wand_raise_animation_done = false;
	}

	#undef egg_top
	#undef egg_left
	#undef spawner_velocity_y
	#undef spawner_velocity_x
	#undef spawner_top
	#undef spawner_left
	#undef eggs_alive
	#undef pellet_group
	#undef wand_raise_animation_done
}

void pascal near bg_transition(int image_id_new)
{
	// Terminology:
	// • Gust: The full animation drawn across the whole width of VRAM
	// • Cell: Area drawn in a single loop iteration, randomly shifted
	// • Stripe: 8×1 pixels drawn in the same color, followed by an 8-pixel gap

	enum {
		VELOCITY_X = 32,
		ROW_SPACING = 4,
		STRIPES_PER_CELL = 5,
		STRIPE_PADDED_VRAM_W = 2,
	};

	#define cell_x         	bg_transition_cell_x
	#define cell_y         	bg_transition_cell_y
	#define cell_vo        	bg_transition_cell_vo
	#define stripe_col_base	bg_transition_stripe_col_base
	#define gust_id        	bg_transition_gust_id

	extern screen_x_t cell_x;
	extern vram_y_t cell_y;
	extern vram_offset_t cell_vo;
	extern int stripe_col_base;
	extern int gust_id;

	int row;
	vram_word_amount_t stripe_id;
	vram_byte_amount_t cell_offset_right;

	struct {
		// Storing 8 dots would have been enough.
		dots16_t put[STRIPES_PER_CELL];
		dots16_t unput[STRIPES_PER_CELL];

		// Yeah, unsafe, but this code is hardware-dependent anyway :P
		dots16_t& operator [](int stripe_id) {
			return put[stripe_id];
		}
	} cell_mask;

	#define stripe_vram_offset(id_static, id_dynamic) \
		/* The parentheses around the whole expression are omitted for */ \
		/* code generation reasons, since this macro is used as an operand */ \
		/* for pointer arithmetic. */ \
		cell_vo + cell_offset_right - (id_static * STRIPE_PADDED_VRAM_W) - ( \
			id_dynamic * STRIPE_PADDED_VRAM_W \
		)

	#define stripe_y(id_static, id_dynamic) \
		((stripe_vram_offset(id_static, id_dynamic)) / ROW_SIZE)

	#define stripe_vram(id_static, id_dynamic) \
		grcg_chunk(stripe_vram_offset(id_static, id_dynamic), 16)

	#define on_same_y_as_cell(id_static, id_dynamic) ( \
		/* Note how (cell_vo / ROW_SIZE) == cell_y */ \
		((cell_vo / ROW_SIZE) == stripe_y(id_static, id_dynamic)) && \
		(stripe_vram_offset(id_static, id_dynamic) >= 0) \
	)

	if(boss_phase_frame == 20) {
		gust_id = 0;
	}
	if(boss_phase_frame < 50) {
		return;
	} else if(boss_phase_frame == 50) {
		cell_x = 0;
		cell_y = 0;
		stripe_col_base = 2;
		cell_vo = vram_offset_shift(0, 0);
		mdrv2_se_play(10);
	}

	for(row = 0; row < (RES_Y / ROW_SPACING); row++) {
		grcg_setcolor_tcr(COL_AIR);
		cell_offset_right = (rand() % 8);

		graph_accesspage(1);
		for(stripe_id = 0; stripe_id < (STRIPES_PER_CELL * 2); stripe_id++) {
			if(stripe_y(0, 0) != stripe_y(0, stripe_id)) {
				break;
			}
			if(on_same_y_as_cell(0, stripe_id)) {
				cell_mask[stripe_id] = stripe_vram(0, stripe_id);
			}
		}

		graph_accesspage(0);
		for(stripe_id = 0; stripe_id < STRIPES_PER_CELL; stripe_id++) {
			if(stripe_y(0, 0) != stripe_y(0, stripe_id)) {
				break;
			}
			if(on_same_y_as_cell(0, stripe_id)) {
				grcg_setcolor_rmw(
					stripe_col_base + ((stripe_id > (STRIPES_PER_CELL / 2))
						? ((STRIPES_PER_CELL - 1) - stripe_id)
						: stripe_id
				));
				stripe_vram(0, stripe_id) = (cell_mask.put[stripe_id] & 0x00FF);
			}
		}

		grcg_setcolor_rmw(COL_AIR);
		for(stripe_id = 0; stripe_id < (gust_id + 2); stripe_id++) {
			if(stripe_y(STRIPES_PER_CELL, stripe_id) != stripe_y(0, 0)) {
				break;
			}
			if(on_same_y_as_cell(STRIPES_PER_CELL, stripe_id)) {
				stripe_vram(STRIPES_PER_CELL, stripe_id) = (
					cell_mask.unput[stripe_id] & 0x00FF
				);
			}
		}

		cell_y += ROW_SPACING;
		cell_vo = vram_offset_shift(cell_x, cell_y);
		// Yeah, this could have just been done unconditionally outside the
		// loop.
		if(cell_vo >= PLANE_SIZE) {
			cell_y = 0;
			cell_x += VELOCITY_X;
			cell_vo = vram_offset_shift(cell_x, cell_y);
		}
		grcg_off_func();
	}

	if(cell_x > (RES_X - VELOCITY_X)) {
		gust_id++;
		boss_phase_frame = 49;
		if(gust_id >= 3) {
			z_vsync_wait_and_scrollup(0);

			graph_accesspage_func(1);
			grp_put_palette_show(BG_IMAGES[image_id_new]);
			graph_copy_accessed_page_to_other();
			stage_palette_set(z_Palettes);

			graph_accesspage_func(0);
			hud_rerender();
			hud_hp_rerender(boss_hp);
			boss_phase_frame = 0;
		}
	}

	#undef on_same_y_as_cell
	#undef stripe_vram
	#undef stripe_y
	#undef stripe_vram_offset

	#undef gust_id
	#undef stripe_col_base
	#undef cell_vo
	#undef cell_y
	#undef cell_x
}
