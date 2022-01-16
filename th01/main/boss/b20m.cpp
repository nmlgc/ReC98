/// Makai Stage 20 Boss - Sariel
/// ----------------------------

extern "C" {
#include <stddef.h>
#include <stdlib.h>
#include <dos.h>
#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/polar.hpp"
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
#include "th01/sprites/shape8x8.hpp"
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

static const screen_x_t SEAL_CENTER_X = 320;
static const screen_x_t SEAL_CENTER_Y = 185;
static const pixel_t SEAL_RADIUS = 140;

// That's… not quite where the sphere is?
static const screen_x_t WAND_EMIT_LEFT = 340;
static const screen_y_t WAND_EMIT_TOP = 64;

// That's… not quite where the face is?
static const screen_x_t FACE_LEFT = 314;
static const screen_y_t FACE_TOP = 104;
static const pixel_t FACE_W = 32;
static const pixel_t FACE_H = 32;
static const screen_y_t FACE_CENTER_Y = (FACE_TOP + (FACE_H / 2));

// MODDERS: That's 32 more than BOSS6_2.BOS is wide? Reducing it to 96 works
// fine as well.
static const pixel_t WAND_W = 128;

static const pixel_t WAND_H = 96;

// BOSS6_A2.GRP
static const screen_x_t A2_ORBS_L_CENTER_X = 64;
static const screen_x_t A2_ORBS_R_CENTER_X = 568;
static const screen_y_t A2_ORBS_CENTER_Y = 160;
// -----------

enum sariel_colors_t {
	COL_LASER = 4,
	COL_PARTICLE2X2 = 4,
	COL_DETONATION = 5,
	COL_DETONATION_START = 6,
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
	int start_frame;
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
static const pixel_t DEBRIS_W = 32;
static const pixel_t DEBRIS_H = 32;

static const int VORTEX_COUNT = 2;

enum vortex_or_debris_cel_t {
	VORTEX_CELS = 3,
	DEBRIS_CELS = 3,

	C_VORTEX = 0,
	C_VORTEX_last = (C_VORTEX + VORTEX_CELS - 1),
	C_DEBRIS,
	C_DEBRIS_last = (C_DEBRIS + DEBRIS_CELS - 1),

	_vortex_or_debris_cel_t_FORCE_INT16 = 0x7FFF
};

inline vortex_or_debris_cel_t debris_cel_next(vortex_or_debris_cel_t &cur) {
	return (cur < C_DEBRIS_last)
		? static_cast<vortex_or_debris_cel_t>(cur + 1)
		: C_DEBRIS;
}

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

// 2×2 particles (just "particles" was taken)
// -------------

static const pixel_t PARTICLE2X2_W = 2;
static const pixel_t PARTICLE2X2_H = 2;
static const int PARTICLE2X2_COUNT = 30;
static const dots8_t sPARTICLE2X2 = 0xC0; // (**      )

#define particle2x2_linear_vram_offset(vo, first_bit, left, top) { \
	vo = vram_offset_divmul_double(left, top); \
	first_bit = (static_cast<screen_x_t>(left) % BYTE_DOTS); \
}

// Better.
#define particle2x2_snap(dots, vo, first_bit) { \
	dots[0] = grcg_chunk_8(vo); \
	dots[1] = grcg_chunk_8(vo + ROW_SIZE); \
	dots[0] &= (sPARTICLE2X2 >> first_bit); \
	dots[1] &= (sPARTICLE2X2 >> first_bit); \
}

// Worse.
#define particle2x2_snap_2(dots, vo, first_bit) { \
	dots[0] = grcg_chunk(vo, 8); \
	/* Parentheses omitted for code generation reasons */ \
	dots[1] = grcg_chunk(vo + ROW_SIZE, 8); \
	dots[0] &= (sPARTICLE2X2 >> first_bit); \
	dots[1] &= (sPARTICLE2X2 >> first_bit); \
}

#define particle2x2_snap_left_right(dots_left, dots_right, vo, first_bit) { \
	particle2x2_snap_2(dots_left, vo, first_bit); \
	if(first_bit == ((BYTE_DOTS - PARTICLE2X2_W) + 1)) { \
		/* Parentheses omitted for code generation reasons */ \
		dots_right[0] = grcg_chunk(vo + 1, 8); \
		dots_right[1] = grcg_chunk(vo + 1 + ROW_SIZE, 8); \
		/* We only care about the leftmost dot, if anything */ \
		dots_right[0] &= 0x80; \
		dots_right[1] &= 0x80; \
	} \
}

#define particle2x2_put(vo, first_bit, dots) { \
	grcg_put_emptyopt(vo, dots[0], 8); \
	/* Parentheses omitted for code generation reasons */ \
	grcg_put_emptyopt(vo + ROW_SIZE, dots[1], 8); \
}

#define particle2x2_put_left_right(vo, first_bit, dots_left, dots_right) { \
	particle2x2_put(vo, first_bit, dots_left); \
	if(first_bit == ((BYTE_DOTS - PARTICLE2X2_W) + 1)) { \
		particle2x2_put(vo + 1, first_bit, dots_right); \
	} \
}
// -------------

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

inline void spawnray_reset(void) {
	spawnray_unput_and_put(0, 0, 0, 0, SPAWNRAY_RESET);
}

// Two symmetric spawn rays with debris
// ------------------------------------

template <
	screen_x_t OriginX, screen_y_t OriginY, pixel_t DebrisOffsetX
> struct SymmetricSpawnraysWithDebris {
	screen_x_t target_l_x;	// Left ray target, used to calculate the right one.
	screen_y_t target_y;

	screen_x_t target_x(x_direction_t ray_id) const {
		return (ray_id == X_LEFT)
			? target_l_x
			: ((PLAYFIELD_RIGHT - 1) - target_l_x);
	}

	screen_x_t debris_left(x_direction_t ray_id, pixel_t offset = 0) const {
		return (ray_id == X_LEFT)
			? ((target_l_x - (DEBRIS_W - DebrisOffsetX)) - offset)
			: (((PLAYFIELD_RIGHT - DebrisOffsetX) - target_l_x) + offset);
	}

	void unput_and_put(
		x_direction_t ray_id,
		const vortex_or_debris_cel_t &debris_cel,
		pixel_t velocity_x
	) const {
		// ZUN bug: Due to egc_copy_rect_1_to_0_16()'s lack of horizontal
		// clamping, an initially negative X coordinate for the left debris
		// sprite, and an extra sloppy 48-pixel width, this unblitting call
		// will wrap around to the other side of the screen for *both* the left
		// and right sprites, unblitting most of the other sprite as well.
		// It will take until
		//
		// 	(target_l_x - (DEBRIS_W / 4) - (velocity_x * 2)) >= 32
		//
		// for both the left and right sprite coordinates to have diverged
		// enough for these wraparounds to stop.
		sloppy_unput_32x32(
			debris_left(ray_id, (velocity_x * 2)), (target_y - DEBRIS_H)
		);

		// Also, why only the top half?
		vortex_or_debris_put_8(
			debris_left(ray_id), (target_y - (DEBRIS_H / 2)), debris_cel
		);
		spawnray_unput_and_put(
			OriginX, OriginY, target_x(ray_id), target_y, V_WHITE
		);
	}

	void ray_unput_right(pixel_t velocity_x) const {
		// spawnray_unput_and_put() could have done this as well, no need to
		// change APIs...
		// Also, [target_l_x] was updated after the last time the right ray was
		// rendered, so we have to undo this movement here.
		graph_r_line_unput(
			OriginX, OriginY, (target_x(X_RIGHT) + velocity_x), target_y
		);
	}

	void fire_random_to_bottom(
		unsigned char &angle, x_direction_t from_dir, subpixel_t speed
	) const {
		angle = iatan2(
			(PLAYFIELD_BOTTOM - target_y),
			((PLAYFIELD_LEFT + playfield_rand_x()) - target_l_x)
		);
		if(from_dir == X_LEFT) {
			Pellets.add_single(
				inhibit_Z3(screen_x_t, target_l_x), target_y, angle, speed
			);
		} else {
			Pellets.add_single(target_x(from_dir), target_y, angle, speed);
		}
	}
};
// ------------------------------------

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

void pascal near particles2x2_vertical_unput_update_render(bool16 from_bottom)
{
	#define col       	particles2x2_vertical_col
	#define left      	particles2x2_vertical_left
	#define top       	particles2x2_vertical_top
	#define velocity_y	particles2x2_vertical_velocity_y

	// Also indicates whether a particle is alive.
	extern uint4_t col[PARTICLE2X2_COUNT];

	extern double left[PARTICLE2X2_COUNT];
	extern double top[PARTICLE2X2_COUNT];
	extern double velocity_y[PARTICLE2X2_COUNT];

	int i;
	vram_offset_t vo;
	int first_bit;
	DotRect<dots8_t, PARTICLE2X2_H> dots;

	if((boss_phase_frame % 7) == 0) {
		for(i = 0; i < PARTICLE2X2_COUNT; i++) {
			if(col[i] != 0) {
				continue;
			}
			left[i] = (rand() % RES_X);
			top[i] = ((from_bottom == false) ? 0 : (RES_Y - 1 - PARTICLE2X2_H));
			velocity_y[i] = ((from_bottom == false)
				? (( rand() % 15) + 2)
				: ((-rand() % 15) - 8)
			);
			col[i] = COL_PARTICLE2X2;
			break;
		}
	}
	if((boss_phase_frame % 2) != 0) {
		return;
	}
	for(i = 0; i < PARTICLE2X2_COUNT; i++) {
		if(col[i] == 0) {
			continue;
		}

		grcg_setcolor_tcr(COL_AIR);

		particle2x2_linear_vram_offset(vo, first_bit, left[i], top[i]);

		// Lazy trick to avoid having to touch two adjacent VRAM bytes? Why
		// though, you've got a 16-bit CPU. And why not just shift it to the
		// next VRAM byte (= 1 pixel to the right) rather than 7 pixels to the
		// left? And why is this done every frame?
		if(first_bit == ((BYTE_DOTS - PARTICLE2X2_W) + 1)) {
			first_bit = 0;
		}

		// Unblit
		graph_accesspage_func(1);	particle2x2_snap_2(dots, vo, first_bit);
		grcg_setcolor_rmw(COL_AIR);
		graph_accesspage_func(0);	particle2x2_put(vo, first_bit, dots);

		// Update
		top[i] += velocity_y[i];

		// Recalculate VRAM offset and clip
		vo = vram_offset_divmul_double(left[i], top[i]);
		if((vo >= (((RES_Y - PARTICLE2X2_H) + 1) * ROW_SIZE) || (vo < 0))) {
			col[i] = 0;
			continue;
		}

		// Render
		grcg_setcolor_tcr(COL_AIR);
		graph_accesspage_func(1);	particle2x2_snap_2(dots, vo, first_bit);
		grcg_setcolor_rmw(col[i]);
		graph_accesspage_func(0);	particle2x2_put(vo, first_bit, dots);
	}
	grcg_off();

	#undef velocity_y
	#undef top
	#undef left
	#undef col
}

void near pattern_detonating_snowflake(void)
{
	enum {
		HITBOX_W = 96,
		RADIUS_MAX = (HITBOX_W / 2),
		STEP_OUTER = 0x08,
		STEP_INNER = 0x06,
	};

	enum phase_t {
		P_RESET = -1,
		P_WAND_RAISE = 0,
		P_FLAKE_SPAWN = 1,
		P_FLAKE_MOVING = 2,
		P_DETONATION_START = 3,
		P_DETONATION_ACTIVE = 5,

		_phase_t_FORCE_INT16 = 0x7FFF
	};

	#define state         	pattern3_state
	#define left          	pattern3_left
	#define star_left     	pattern3_star_left
	#define top           	pattern3_top
	#define star_top      	pattern3_star_top
	#define velocity_y    	pattern3_velocity_y
	#define velocity_x    	pattern3_velocity_x
	#define radius_outer_1	pattern3_radius_outer_1
	#define radius_outer_2	pattern3_radius_outer_2
	#define radius_inner  	pattern3_radius_inner

	extern union {
		phase_t phase;
		int detonation_frame;
	} state;
	extern Subpixel left;
	extern screen_x_t star_left;
	extern Subpixel top;
	extern vram_y_t star_top;
	extern Subpixel velocity_y;
	extern Subpixel velocity_x;
	extern pixel_t radius_outer_1;
	extern pixel_t radius_outer_2;
	extern pixel_t radius_inner;

	#define ellipse_put(radius_x, radius_y, col, angle_step) { \
		shape_ellipse_arc_put( \
			left.to_pixel(), player_center_y(), radius_x, radius_y, \
			col, angle_step, 0x00, 0xFF \
		); \
	}

	#define ellipse_sloppy_unput(radius_x, radius_y, angle_step) { \
		shape_ellipse_arc_sloppy_unput( \
			left.to_pixel(), player_center_y(), radius_x, radius_y, \
			angle_step, 0x00, 0xFF \
		); \
	}

	if(boss_phase_frame < 10) {
		state.phase = P_RESET;
		select_for_rank(pattern_state.start_frame, 160, 160, 160, 160);
	}

	if((boss_phase_frame % pattern_state.start_frame) == 0) {
		state.phase = P_WAND_RAISE;
	}

	if(state.phase == P_WAND_RAISE) {
		state.phase = static_cast<phase_t>(wand_render_raise_both());
	}
	if(state.phase == P_FLAKE_SPAWN) {
		mdrv2_se_play(6);
		left.v = to_sp(WAND_EMIT_LEFT);
		top.v = to_sp(WAND_EMIT_TOP);
		vector2_between(
			WAND_EMIT_LEFT,
			WAND_EMIT_TOP,
			(player_left + (PLAYER_W / 2) - (FLAKE_W / 2)),
			(player_top + (PLAYER_H / 2) - (FLAKE_H / 2)),
			velocity_x.v,
			velocity_y.v,
			to_sp(7.0f)
		);
		state.phase = P_FLAKE_MOVING;
	}
	if(state.phase == P_FLAKE_MOVING) {
		shape8x8_sloppy_unput(left.to_pixel(), top.to_pixel());

		top.v += velocity_y.v;
		if(top.v >= to_sp(PLAYFIELD_BOTTOM - (FLAKE_H / 2))) {
			state.phase = P_DETONATION_START;
			wand_lower_both();
			return;
		}
		left.v += velocity_x.v;
		shape8x8_flake_put(left.to_pixel(), top.to_pixel(), V_WHITE);
	}
	if(state.phase == P_DETONATION_START) {
		ellipse_put(RADIUS_MAX, 16, COL_DETONATION_START, STEP_OUTER);
		ellipse_put(16, RADIUS_MAX, COL_DETONATION_START, STEP_OUTER);
		ellipse_put(24, 24, V_WHITE, STEP_INNER);
		radius_outer_1 = RADIUS_MAX;
		radius_outer_2 = 16;
		radius_inner = 24;
		// ZUN bug: Assigning a subpixel to a regular pixel. Will affect a
		// single frame, until the X position is randomized again.
		star_left = left.v;
		star_top = (PLAYFIELD_BOTTOM - (rand() % RADIUS_MAX));
		mdrv2_se_play(10);
	}
	if(state.phase >= P_DETONATION_START) {
		state.detonation_frame++;
	}
	if(
		(state.phase >= P_DETONATION_ACTIVE) &&
		((state.detonation_frame % 8) == 0)
	) {
		shape8x8_sloppy_unput(star_left, star_top);
		ellipse_sloppy_unput(radius_outer_1, radius_outer_2, STEP_OUTER);
		ellipse_sloppy_unput(radius_outer_2, radius_outer_1, STEP_OUTER);
		ellipse_sloppy_unput(radius_inner, radius_inner, STEP_INNER);

		radius_outer_1 -= 6;
		radius_outer_2 += 6;
		radius_inner += 4;
		star_left = ((rand() % ((HITBOX_W * 2) / 3)) + left.to_pixel() - (
			 ((HITBOX_W * 2) / 6) - (FLAKE_W / 2)
		));
		star_top = (PLAYFIELD_BOTTOM - (rand() % RADIUS_MAX));
		if(radius_outer_1 <= 8) {
			state.phase = P_RESET;
			return;
		}

		ellipse_put(radius_outer_1, radius_outer_2, COL_DETONATION, STEP_OUTER);
		ellipse_put(radius_outer_2, radius_outer_1, COL_DETONATION, STEP_OUTER);
		ellipse_put(radius_inner, radius_inner, V_WHITE, STEP_INNER);
		shape8x8_star_put(star_left, star_top, V_WHITE);
	}

	if(
		!player_invincible &&
		((left.to_pixel() + ((HITBOX_W / 2) - (PLAYER_W / 2))) > player_left) &&
		((left.to_pixel() - ((HITBOX_W / 2) + (PLAYER_W / 2))) < player_left) &&
		(state.phase >= P_DETONATION_START)
	) {
		done = true;
	}

	#undef ellipse_put
	#undef ellipse_sloppy_unput

	#undef radius_inner
	#undef radius_outer_2
	#undef radius_outer_1
	#undef velocity_x
	#undef velocity_y
	#undef star_top
	#undef top
	#undef star_left
	#undef left
	#undef state
}

void near pattern_2_rings_from_a2_orbs(void)
{
	#define angle   	pattern4_angle
	#define interval	pattern4_interval

	extern unsigned char angle;
	extern int interval;

	if(boss_phase_frame < 5) {
		angle = 0x00;
		select_for_rank(interval, 18, 12, 10, 8);
	}
	if((boss_phase_frame % interval) == 0) {
		Pellets.spawn_with_cloud = true;
		Pellets.add_single(
			A2_ORBS_R_CENTER_X, A2_ORBS_CENTER_Y, (0x00 - angle), to_sp(3.5f)
		);
		Pellets.add_single(
			A2_ORBS_R_CENTER_X, A2_ORBS_CENTER_Y, (0x80 - angle), to_sp(3.5f)
		);
		Pellets.add_single(
			A2_ORBS_L_CENTER_X, A2_ORBS_CENTER_Y, (0x00 + angle), to_sp(3.5f)
		);
		Pellets.add_single(
			A2_ORBS_L_CENTER_X, A2_ORBS_CENTER_Y, (0x80 + angle), to_sp(3.5f)
		);
		angle += interval;
	}
	if(boss_phase_frame > 479) {
		boss_phase_frame = 0;
	}

	#undef interval
	#undef angle
}

void near pattern_aimed_sling_clusters(void)
{
	if(boss_phase_frame == 10) {
		select_for_rank(pattern_state.interval, 4, 3, 2, 2);
	}
	if(
		((boss_phase_frame % 200) >= 150) &&
		((boss_phase_frame % pattern_state.interval) == 0)
	) {
		screen_x_t left;
		vram_y_t top;
		unsigned char angle = rand();

		left = polar_y(PLAYFIELD_CENTER_X, (PLAYFIELD_W / 16), angle);
		top = polar_x(
			(SEAL_CENTER_Y - (PELLET_H / 2) - 1),
			playfield_fraction_y(5 / 42.0f),
			angle
		);
		Pellets.add_single(left, top, 0x00, 0x00, PM_SLING_AIMED, to_sp(4.5f));
	}
	if(boss_phase_frame >= 299) {
		boss_phase_frame = 0;
	}
}

void near particles2x2_wavy_unput_update_render()
{
	#define col       	particles2x2_wavy_col
	#define left      	particles2x2_wavy_left
	#define top       	particles2x2_wavy_top
	#define velocity_y	particles2x2_wavy_velocity_y
	#define age       	particles2x2_wavy_age

	// Also indicates whether a particle is alive.
	extern uint4_t col[PARTICLE2X2_COUNT];

	extern screen_x_t left[PARTICLE2X2_COUNT];
	extern vram_y_t top[PARTICLE2X2_COUNT];
	extern pixel_t velocity_y[PARTICLE2X2_COUNT];
	extern int age[PARTICLE2X2_COUNT];

	int i;
	int first_bit;
	vram_offset_t vo;
	screen_x_t wave_left;
	DotRect<dots8_t, PARTICLE2X2_H> dots;

	if((boss_phase_frame % 7) == 0) {
		for(i = 0; i < PARTICLE2X2_COUNT; i++) {
			if(col[i] != 0) {
				continue;
			}
			left[i] = (rand() % RES_X);
			top[i] = RES_Y;
			velocity_y[i] = -1;
			age[i] = 0;
			col[i] = COL_PARTICLE2X2;
			break;
		}
	}
	if((boss_phase_frame % 2) != 0) {
		return;
	}
	for(i = 0; i < PARTICLE2X2_COUNT; i++) {
		if(col[i] == 0) {
			continue;
		}

		grcg_setcolor_tcr(COL_AIR);

		wave_left = polar_y(left[i], 16, age[i]);
		vo = vram_offset_shift(wave_left, top[i]);
		first_bit = (wave_left & (BYTE_DOTS - 1));

		// Unblit
		graph_accesspage_func(1);	particle2x2_snap(dots, vo, first_bit);
		grcg_setcolor_rmw(COL_AIR);
		graph_accesspage_func(0);	particle2x2_put(vo, first_bit, dots);

		// Update
		top[i] += velocity_y[i];
		age[i]++;

		// Recalculate VRAM offset and clip
		wave_left = polar_y(left[i], 16, age[i]);
		vo = vram_offset_shift(wave_left, top[i]);
		first_bit = (wave_left & (BYTE_DOTS - 1));
		if(age[i] >= 100) {
			col[i] = 0;
			continue;
		}

		// Render
		grcg_setcolor_tcr(COL_AIR);
		graph_accesspage_func(1);	particle2x2_snap(dots, vo, first_bit);
		grcg_setcolor_rmw(col[i]);
		graph_accesspage_func(0);	particle2x2_put(vo, first_bit, dots);
	}
	grcg_off();

	#undef age
	#undef velocity_y
	#undef top
	#undef left
	#undef col
}

void near pattern_four_aimed_lasers(void)
{
	#define ORIGIN_DISTANCE_X_1 (SEAL_CENTER_X - SEAL_RADIUS)
	#define ORIGIN_Y_1 FACE_CENTER_Y
	#define ORIGIN_Y_2 SHIELD_CENTER_Y

	#define origin_x    	pattern6_origin_x
	#define origin_y    	pattern6_origin_y
	#define spawnray    	pattern6_spawnray
	#define target_first	pattern6_target_first

	extern screen_x_t origin_x;
	extern screen_y_t origin_y;
	extern struct {
		pixel_t velocity_y;
		pixel_t velocity_x;

		void unput_update_render(void) {
			spawnray_unput_and_put(
				PLAYFIELD_CENTER_X, ORIGIN_Y_1, origin_x, origin_y, V_WHITE
			);
			origin_x += velocity_x;
			origin_y += velocity_y;
		}
	} spawnray;
	extern screen_x_t target_first;

	#define spawnray_init(origin_x_, origin_y_, target_left) { \
		origin_x = origin_x_; \
		origin_y = origin_y_; \
		vector2_between( \
			origin_x, \
			origin_y, \
			target_left, \
			PLAYFIELD_BOTTOM, \
			spawnray.velocity_x, \
			spawnray.velocity_y, \
			16 \
		); \
	}

	#define fire(laser_id, origin_left, origin_top, target_left) { \
		shootout_lasers[laser_id].spawn( \
			origin_left, origin_top, target_left, PLAYFIELD_BOTTOM, \
			pattern_state.speed_multiplied_by_8, V_WHITE, 50, 8 \
		); \
		mdrv2_se_play(6); \
	}

	if(boss_phase_frame < 5) {
		spawnray_reset();
	}

	if(boss_phase_frame < 50) {
		return;
	} else if(boss_phase_frame == 50) {
		spawnray_init(
			(PLAYFIELD_RIGHT - ORIGIN_DISTANCE_X_1), ORIGIN_Y_1, player_left
		);

		target_first = player_left;
		select_for_rank(pattern_state.speed_multiplied_by_8,
			(to_sp(7.5f) / 2),
			(to_sp(8.0f) / 2),
			(to_sp(8.5f) / 2),
			(to_sp(9.0f) / 2)
		);

		fire(0,
			(PLAYFIELD_RIGHT - ORIGIN_DISTANCE_X_1), ORIGIN_Y_1, player_left
		);
	} else if(boss_phase_frame < 100) {
		spawnray.unput_update_render();
	} else if(boss_phase_frame == 100) {
		spawnray_init(
			(PLAYFIELD_LEFT + ORIGIN_DISTANCE_X_1),
			ORIGIN_Y_1,
			((PLAYFIELD_RIGHT - 1) - target_first)
		);
		fire(1, origin_x, origin_y, ((PLAYFIELD_RIGHT - 1) - target_first));
	} else if(boss_phase_frame < 150) {
		spawnray.unput_update_render();
	} else if(boss_phase_frame == 150) {
		spawnray_init(
			(PLAYFIELD_RIGHT - playfield_fraction_x(4 / 80.0f)),
			ORIGIN_Y_2,
			player_left
		);
		fire(2, origin_x, origin_y, player_left);
	} else if(boss_phase_frame < 200) {
		spawnray.unput_update_render();
	} else if(boss_phase_frame == 200) {
		spawnray_init(
			(PLAYFIELD_LEFT + playfield_fraction_x(3 / 80.0f)),
			ORIGIN_Y_2,
			player_left
		);
		fire(3, origin_x, origin_y, player_left);
	} else if(boss_phase_frame < 250) {
		spawnray.unput_update_render();
	} else if(boss_phase_frame > 300) {
		boss_phase_frame = 0;
	}

	#undef fire
	#undef spawnray_init

	#undef target_first
	#undef spawnray
	#undef origin_y
	#undef origin_x

	#undef ORIGIN_Y_2
	#undef ORIGIN_Y_1
	#undef ORIGIN_DISTANCE_X_1
}

void near shake_for_50_frames(void)
{
	if(boss_phase_frame < 50) {
		if((boss_phase_frame % 8) == 0) {
			z_vsync_wait_and_scrollup(RES_Y - 4);
		} else if((boss_phase_frame % 8) == 4) {
			z_vsync_wait_and_scrollup(RES_Y + 4);
		}
		if((boss_phase_frame % 4) == 0) {
			mdrv2_se_play(7);
		}
	} else if(boss_phase_frame == 50) {
		z_vsync_wait_and_scrollup(0);
		boss_phase_frame = 0;
	}
}

void near pattern_rain_from_top(void)
{
	if((boss_phase_frame % 8) != 0) {
		return;
	}
	screen_x_t left = (PLAYFIELD_LEFT + playfield_rand_x());
	vram_y_t top = PLAYFIELD_TOP;
	pellet_group_t group;

	select_for_rank(
		reinterpret_cast<int &>(group), PG_1, PG_1, PG_1, PG_1_RANDOM_WIDE
	);
	Pellets.add_group(left, top, group, to_sp(2.75f));
}

void near pattern_radial_stacks_and_lasers(void)
{
	#define CENTER_X	PLAYFIELD_CENTER_X
	// Technically wrong as the ray's origin point, but who cares.
	#define CENTER_Y	(SHIELD_CENTER_Y - (PELLET_H / 2))

	#define angle         	pattern8_angle
	#define angle_velocity	pattern8_angle_velocity

	extern unsigned char angle;
	extern unsigned char angle_velocity;

	screen_x_t target_x;
	screen_y_t target_y;

	if(boss_phase_frame < 5) {
		spawnray_reset();
	}
	if(boss_phase_frame < 150) {
		return;
	} else if(boss_phase_frame == 150) {
		angle = 0x00;
		angle_velocity = 0x01;
		select_for_rank(pattern_state.speed_multiplied_by_8,
			(to_sp(7.5f  ) / 2),
			(to_sp(8.125f) / 2),
			(to_sp(8.75f ) / 2),
			(to_sp(9.375f) / 2)
		);
		mdrv2_se_play(6);
	} else if(boss_phase_frame < 200) {
		target_x = polar_x(CENTER_X, SEAL_RADIUS, angle);
		target_y = polar_y(CENTER_Y, SEAL_RADIUS, angle);
		spawnray_unput_and_put(CENTER_X, CENTER_Y, target_x, target_y, V_WHITE);
		angle += angle_velocity;
		angle_velocity++;
		if((boss_phase_frame % 10) == 0) {
			mdrv2_se_play(6);
		}
	} else if(boss_phase_frame == 200) {
		target_x = -PIXEL_NONE;
		target_y = -PIXEL_NONE;
		spawnray_unput_and_put(CENTER_X, CENTER_Y, target_x, target_y, V_WHITE);
		angle = 0x00;
	} else if(boss_phase_frame <= 400) {
		if((boss_phase_frame % 5) == 0) {
			target_x = polar_x(CENTER_X, 600, angle);
			target_y = polar_y(CENTER_Y, 600, angle);
			mdrv2_se_play(7);
			if((boss_phase_frame % 15) == 0) {
				shootout_lasers[
					((boss_phase_frame - 215) / 15) % SHOOTOUT_LASER_COUNT
				].spawn(
					CENTER_X, CENTER_Y, target_x, target_y,
					pattern_state.speed_multiplied_by_8, V_WHITE, 20, 4
				);
			} else {
				Pellets.add_single(CENTER_X, CENTER_Y, angle, to_sp(6.25f));
			}
			Pellets.add_single(CENTER_X, CENTER_Y, (angle - 0x04), to_sp(6.0f));
			Pellets.add_single(CENTER_X, CENTER_Y, (angle + 0x04), to_sp(6.0f));
			if(rank >= RANK_HARD) {
				Pellets.add_single(
					CENTER_X, CENTER_Y, (angle - 0x04), to_sp(4.0f)
				);
				Pellets.add_single(
					CENTER_X, CENTER_Y, (angle + 0x04), to_sp(4.0f)
				);
				if(rank == RANK_LUNATIC) {
					Pellets.add_single(CENTER_X, CENTER_Y, angle, to_sp(4.0f));
					Pellets.add_single(CENTER_X, CENTER_Y, angle, to_sp(3.0f));
				}
			}
			angle += 0x0C;
		}
	} else if(boss_phase_frame == 450) {
		boss_phase_frame = 0;
	}

	#undef angle_velocity
	#undef angle

	#undef CENTER_Y
	#undef CENTER_X
}

void near pattern_symmetric_birds_from_bottom(void)
{
	enum {
		VELOCITY_X = 2,
	};

	#define rays      	pattern9_rays
	#define velocity  	pattern9_velocity
	#define debris_cel	pattern9_debris_cel

	extern SymmetricSpawnraysWithDebris<
		PLAYFIELD_CENTER_X, FACE_CENTER_Y, (DEBRIS_W / 4)
	> rays;
	extern point_t velocity;
	extern vortex_or_debris_cel_t debris_cel;

	double target_x; // double?!

	if(boss_phase_frame < 50) {
		return;
	}
	if(boss_phase_frame == 50) {
		select_for_rank(pattern_state.unknown, 6, 7, 8, 9);
		rays.target_l_x = VELOCITY_X;
		rays.target_y = (PLAYFIELD_BOTTOM - 1);
		velocity.x = VELOCITY_X;
		velocity.y = -2; // could have been a constant
		debris_cel = C_DEBRIS;
		return;
	} else if(boss_phase_frame < 100) {
		if((boss_phase_frame % 2) == 0) {
			rays.unput_and_put(X_LEFT, debris_cel, VELOCITY_X);
		}
		if((boss_phase_frame % 2) == 1) {
			rays.unput_and_put(X_RIGHT, debris_cel, VELOCITY_X);
			debris_cel = debris_cel_next(debris_cel);
		}
		rays.target_l_x += VELOCITY_X;
		if((boss_phase_frame % 10) == 0) {
			mdrv2_se_play(6);

			target_x = (((boss_phase_frame - 60) * 10) + rays.target_l_x);
			vector2_between(
				rays.target_x(X_LEFT), (rays.target_y - BIRD_H),
				target_x, 0,
				velocity.x, velocity.y,
				4
			);
			birds_spawn(
				rays.target_x(X_LEFT),
				(rays.target_y - BIRD_H),
				velocity.x,
				velocity.y
			);
			birds_spawn(
				rays.target_x(X_RIGHT),
				(rays.target_y - BIRD_H),
				-velocity.x,
				velocity.y
			);
		}
		if((boss_phase_frame % 6) == 0) {
			birds_fire(BPG_RANDOM_RAIN);
		}
		return;
	} else if(boss_phase_frame == 100) {
		rays.ray_unput_right(VELOCITY_X);
		return;
	} else if((boss_phase_frame % 10) == 0) {
		birds_fire(BPG_RANDOM_RAIN);
	}
	if(boss_phase_frame >= 300) {
		boss_phase_frame = 0;
	}

	#undef debris_cel
	#undef velocity
	#undef rays
}

void near pattern_four_semicircle_spreads(void)
{
	enum {
		ORIGIN_X = SHIELD_CENTER_X,
		ORIGIN_Y = (SHIELD_CENTER_Y - (PELLET_H / 2)),
	};

	int i;
	unsigned char angle;

	if(boss_phase_frame < 50) {
		return;
	} else if(boss_phase_frame == 50) {
		for((angle = 0x00, i = 0); i < 20; (angle += 0x07, i++)) {
			Pellets.add_single(ORIGIN_X, ORIGIN_Y, angle, to_sp(2.0f));
		}
	} else if(boss_phase_frame == 60) {
		for((angle = 0x04, i = 0); i < 10; (angle += 0x0C, i++)) {
			Pellets.add_single(ORIGIN_X, ORIGIN_Y, angle, to_sp(3.0f));
		}
	} else if(boss_phase_frame == 70) {
		for((angle = 0x04, i = 0); i < 8; (angle += 0x0E, i++)) {
			Pellets.add_single(ORIGIN_X, ORIGIN_Y, angle, to_sp(4.0f));
		}
	} else if(boss_phase_frame == 80) {
		for((angle = 0x0E, i = 0); i < 10; (angle += 0x0A, i++)) {
			Pellets.add_single(ORIGIN_X, ORIGIN_Y, angle, to_sp(3.0f));
		}
	} else if(boss_phase_frame > 150) {
		boss_phase_frame = 0;
	}
}

void near pattern_vertical_stacks_from_bottom_then_random_rain_from_top(void)
{
	enum {
		COLUMN_INTERVAL = 10,
		COLUMN_COUNT = 20,
		SPAWNRAY_VELOCITY_X = (PLAYFIELD_W / 80),
		COLUMN_DISTANCE_X = (PLAYFIELD_W / COLUMN_COUNT),

		KEYFRAME_0 = 50,
		KEYFRAME_1 = (KEYFRAME_0 + (PLAYFIELD_W / SPAWNRAY_VELOCITY_X)),
		KEYFRAME_2 = (KEYFRAME_1 + 20),
		KEYFRAME_3 = (KEYFRAME_2 + (COLUMN_COUNT * COLUMN_INTERVAL)),
		KEYFRAME_4 = (KEYFRAME_3 + (COLUMN_COUNT * COLUMN_INTERVAL)),
		KEYFRAME_5 = (KEYFRAME_4 + 50),
	};

	#define rays      	pattern11_rays
	#define debris_cel	pattern11_debris_cel

	extern SymmetricSpawnraysWithDebris<
		PLAYFIELD_CENTER_X, FACE_CENTER_Y, (DEBRIS_W / 4)
	> rays;

	// ZUN bug: Leaving this uninitalized indeed implies vortex sprites for the
	// first 5 frames, until this actually reaches C_DEBRIS...
	extern vortex_or_debris_cel_t debris_cel;

	unsigned char angle;

	if(boss_phase_frame < KEYFRAME_0) {
		return;
	}
	if(boss_phase_frame == KEYFRAME_0) {
		// Note that the value for Lunatic is less than the COLUMN_INTERVAL.
		// This will move the spawners into another VRAM row before the pattern
		// ends.
		select_for_rank(pattern_state.interval, 16, 13, 10, 8);

		rays.target_l_x = 2;
		rays.target_y = (PLAYFIELD_BOTTOM - 1);
	} else if(boss_phase_frame < KEYFRAME_1) {
		if((boss_phase_frame % 2) == 0) {
			rays.unput_and_put(X_LEFT, debris_cel, SPAWNRAY_VELOCITY_X);
		}
		if((boss_phase_frame % 2) == 1) {
			rays.unput_and_put(X_RIGHT, debris_cel, SPAWNRAY_VELOCITY_X);
			debris_cel = debris_cel_next(debris_cel);
		}
		rays.target_l_x += SPAWNRAY_VELOCITY_X;
	} else if(boss_phase_frame == KEYFRAME_1) {
		rays.ray_unput_right(SPAWNRAY_VELOCITY_X);
		rays.target_l_x = PLAYFIELD_LEFT;
	} else if(
		(boss_phase_frame > KEYFRAME_2) &&
		(boss_phase_frame < KEYFRAME_3)
	) {
		if((boss_phase_frame % COLUMN_INTERVAL) == 0) {
			for(subpixel_t i = to_sp(0.0f); i < to_sp(4.0f); i += to_sp(1.0f)) {
				// How nice!
				if(abs(player_center_x() - rays.target_x(X_LEFT)) > PLAYER_W) {
					Pellets.add_single(
						rays.target_x(X_LEFT),
						(rays.target_y - PELLET_H),
						-0x40,
						(i + to_sp(3.0f))
					);
				}
				if(abs(player_center_x() - rays.target_x(X_RIGHT)) > PLAYER_W) {
					Pellets.add_single(
						rays.target_x(X_RIGHT),
						(rays.target_y - PELLET_H),
						-0x40,
						(i + to_sp(3.0f))
					);
				}
			}
			rays.target_l_x += COLUMN_DISTANCE_X;
			mdrv2_se_play(7);
		}
	} else if(boss_phase_frame == KEYFRAME_3) {
		rays.target_l_x = PLAYFIELD_LEFT;
		rays.target_y = PLAYFIELD_TOP;
	} else if(boss_phase_frame < KEYFRAME_4) {
		if((boss_phase_frame % pattern_state.interval) == 0) {
			for(int i = 0; i < 2; i++) {
				rays.fire_random_to_bottom(angle, X_LEFT, to_sp(3.0f));
				rays.fire_random_to_bottom(angle, X_RIGHT, to_sp(3.0f));
			}
			rays.target_l_x += COLUMN_DISTANCE_X;
		}
	} else if(boss_phase_frame > KEYFRAME_5) {
		boss_phase_frame = 0;
	}

	#undef debris_cel
	#undef rays
}

void near pascal dottedcircle_unput_update_render(
	screen_x_t center_x,
	screen_y_t center_y,
	int frame_1based,
	int interval,
	pixel_t radius_step,
	int col,
	pixel_t radius_initial,
	int duration
)
{
	#define radius_prev	dottedcircle_radius_prev
	#define active     	dottedcircle_active

	extern pixel_t radius_prev;
	extern bool16 active;

	#define radius_cur \
		(((frame_1based / interval) * radius_step) + radius_initial)

	if(frame_1based == 1) {
		active = true;
		// Yup, no rendering call this frame.
	} else {
		if((active != true) || ((frame_1based % interval) != 0)) {
			return;
		}
		shape_circle_sloppy_unput(center_x, center_y, radius_prev, 0x01);
		if(frame_1based >= duration) {
			active = false;
			return;
		}
		shape_circle_put(center_x, center_y, radius_cur, col, 0x01);
	}
	radius_prev = radius_cur;

	#undef radius_cur

	#undef active
	#undef radius_prev
}

void pascal near particles2x2_horizontal_unput_update_render(int frame)
{
	#define col       	particles2x2_horizontal_col
	#define left      	particles2x2_horizontal_left
	#define top       	particles2x2_horizontal_top
	#define velocity_x	particles2x2_horizontal_velocity_x

	// Also indicates whether a particle is alive.
	extern uint4_t col[PARTICLE2X2_COUNT];

	extern double left[PARTICLE2X2_COUNT];
	extern double top[PARTICLE2X2_COUNT];
	extern double velocity_x[PARTICLE2X2_COUNT];

	int i;
	int first_bit;
	vram_offset_t vo;
	DotRect<dots8_t, PARTICLE2X2_H> dots_right;
	DotRect<dots8_t, PARTICLE2X2_H> dots_left;

	if((frame % 7) == 0) {
		for(i = 0; i < PARTICLE2X2_COUNT; i++) {
			if(col[i] != 0) {
				continue;
			}
			left[i] = (rand() % RES_X);
			top[i] = (rand() % RES_Y);
			velocity_x[i] = ((rand() % 2) == 0) ? -6 : 6;
			col[i] = COL_PARTICLE2X2;
			break;
		}
	}
	if((frame % 2) != 0) {
		return;
	}
	for(i = 0; i < PARTICLE2X2_COUNT; i++) {
		if(col[i] == 0) {
			continue;
		}

		grcg_setcolor_tcr(COL_AIR);

		particle2x2_linear_vram_offset(vo, first_bit, left[i], top[i]);

		// Unblit
		graph_accesspage_func(1);
		particle2x2_snap_left_right(dots_left, dots_right, vo, first_bit);
		grcg_setcolor_rmw(COL_AIR);
		graph_accesspage_func(0);
		particle2x2_put_left_right(vo, first_bit, dots_left, dots_right);

		// Update
		left[i] += velocity_x[i];
		velocity_x[i] += (velocity_x[i] < 0) ? 0.1 : -0.1;

		// Recalculate VRAM offset and clip
		particle2x2_linear_vram_offset(vo, first_bit, left[i], top[i]);
		if((left[i] >= RES_X) || (left[i] < 0) || (abs(velocity_x[i]) < 0.5)) {
			col[i] = 0;
			continue;
		}

		// Render
		grcg_setcolor_tcr(COL_AIR);
		graph_accesspage_func(1);
		particle2x2_snap_left_right(dots_left, dots_right, vo, first_bit);

		grcg_setcolor_rmw(col[i]);
		graph_accesspage_func(0);
		particle2x2_put_left_right(vo, first_bit, dots_left, dots_right);
	}
	grcg_off();

	#undef velocity_x
	#undef top
	#undef left
	#undef col
}
