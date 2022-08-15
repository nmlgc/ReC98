/// Makai Stage 20 Boss - Sariel
/// ----------------------------

#include <stdlib.h>
#include <dos.h>
#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grcg8x8m.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/egcrows.hpp"
#include "th01/hardware/grpinv32.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/pgtrans.hpp"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"
#include "th01/formats/grp.h"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/leaf.hpp"
#include "th01/sprites/pellet.h"
#include "th01/sprites/shape8x8.hpp"
#include "th01/main/entity.hpp"
#include "th01/main/spawnray.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/stage/palette.hpp"
#include "th01/main/shape.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/player/bomb.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/shot.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/hud/hud.hpp"

static const char* unused_entrance_letters_maybe[] = { "ANGEL", "OF", "DEATH" };
int8_t game_cleared = false; // ACTUAL TYPE: bool

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
static const pixel_t FACE_W = 64;
static const pixel_t FACE_H = 64;
static const screen_y_t FACE_CENTER_Y = (FACE_TOP + (FACE_H / 4));

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
	COL_FORM2_PULSE = 6,
	COL_AIR = 12,
	COL_BIRD = 15, // Yes, just a single one, changed by the background image.
};

static union {
	int frame;
	int speed_multiplied_by_8;
	int interval;
	int start_frame;
	pixel_t velocity_x;
	int pellet_count;
	int unknown;
} pattern_state;

// File names
// ----------

#include "th01/shiftjis/fns.hpp"

const char* BG_IMAGES[4] = {
	"BOSS6_A1.GRP", "BOSS6_A2.GRP", "BOSS6_A3.GRP", "BOSS6_A4.GRP"
};
// ----------

// Entities (and animations)
// --------

#define ent_shield	boss_entity_0
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

// Leaf splash animation (BOSS6GR4.GRC)
// ------------------------------------
// Never seen in the original game, due to a ZUN bug in the only pattern that
// uses it.

static const pixel_t LEAFSPLASH_W = 32;
static const pixel_t LEAFSPLASH_H = 32;
static const int LEAFSPLASH_CELS = 3;
// ------------------------------------
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
	mdrv2_se_load(SE_FN); // ZUN bloat: Already done in main()
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
	ent_shield.hitbox_orb_set(-16, -16, 64, 64);
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
	static screen_x_t target_prev_x = -PIXEL_NONE;
	static vram_y_t target_prev_y = -PIXEL_NONE;
	spawnray_unput_and_put_func(
		target_prev_x, target_prev_y,
		origin_x, origin_y, target_x, target_y, col, true
	);
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

	// Almost a correct unblitting call, except for the top coordinate...
	void debris_sloppy_unput(
		x_direction_t ray_id, pixel_t offset = 0, pixel_t additional_h = 0
	) const {
		egc_copy_rect_1_to_0_16(
			debris_left(ray_id),
			((target_y - (DEBRIS_H / 4)) + offset),
			DEBRIS_W,
			(DEBRIS_H + additional_h)
		);
	}

	// Worse.
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
		grc_sloppy_unput(
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

	// Better.
	void unput_and_put(
		x_direction_t ray_id, const vortex_or_debris_cel_t &debris_cel
	) const {
		debris_sloppy_unput(ray_id);
		spawnray_unput_and_put(
			OriginX, OriginY, target_x(ray_id), target_y, V_WHITE
		);
		vortex_or_debris_put_8(
			debris_left(ray_id), (target_y - (DEBRIS_H / 2)), debris_cel
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

	void unput_broken(pixel_t velocity_y) const {
		debris_sloppy_unput(X_RIGHT, -velocity_y, velocity_y);
		debris_sloppy_unput(X_LEFT, -velocity_y, (velocity_y + 10)); // ???

		// ZUN bug: Should of course be [velocity_y] rather than 4. These calls
		// therefore unblit lines at angles that completely differ from the
		// intended spawn rays. It doesn't matter for the left one, which
		// actually isn't visible when this code gets to run, but the right one
		// does indeed stay visible after this function. You only barely notice
		// it because the one pattern that calls this function then spawns
		// pellets on top of both rays, and it's *their* sloppy unblitting code
		// that ends up gradually unblitting the right ray over the next few
		// frames, as a side effect.
		// Again, spawnray_unput_and_put() would have just done the correct
		// thing.
		graph_r_line_unput(OriginX, OriginY, target_x(X_LEFT),  (target_y + 4));
		graph_r_line_unput(OriginX, OriginY, target_x(X_RIGHT), (target_y + 4));
	}

	void fire_random_to_bottom(
		unsigned char &angle, x_direction_t from_dir, subpixel_t speed
	) const {
		angle = iatan2(
			(PLAYFIELD_BOTTOM - target_y), (playfield_rand_x() - target_l_x)
		);
		if(from_dir == X_LEFT) {
			Pellets.add_single(inhibit_Z3(target_l_x), target_y, angle, speed);
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
	static char birds_alive[BIRD_COUNT] = { false }; // Should be bool.
	static struct {
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
			pellets_add_single_rain(
				birds.pellet_left(i),
				birds.pellet_top(i),
				((rand() & 0x7F) + 0x80),
				4.0f
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
				grc_sloppy_unput(birds.left[i], birds.top[i]);
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
				grc_sloppy_unput(birds.left[i], birds.top[i]);
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
				player_is_hit = true;
				delay(100); // ???
				return;
			}
		}
	}
}

inline void birds_reset(void) {
	birds_reset_fire_spawn_unput_update_render(BF_RESET);
}

#define birds_spawn(left, top, velocity_x, velocity_y) \
	birds_reset_fire_spawn_unput_update_render( \
		left, top, velocity_x, velocity_y, 1 \
	);

#define birds_fire(pellet_group) \
	birds_reset_fire_spawn_unput_update_render(BF_FIRE + pellet_group);

inline void birds_unput_update_render(void) {
	birds_reset_fire_spawn_unput_update_render(BF_UNPUT_UPDATE_RENDER);
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
	ent_shield.set_image(
		(boss_phase_frame % (FRAMES_PER_CEL * CELS)) / FRAMES_PER_CEL
	);
	graph_accesspage_func(1);	ent_shield.unlock_put_lock_8();
	graph_accesspage_func(0);	ent_shield.unlock_put_lock_8();
}

// Renders a frame of Sariel's wand raise animation on both VRAM pages, and
// returns `true` once the animation completed.
bool16 pascal near wand_render_raise_both(bool16 restart = false)
{
	static int frames = 0;

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
	static bool16 wand_raise_animation_done = false;
	static CEntities<VORTEX_COUNT> cur;
	static CEntities<VORTEX_COUNT> prev;
	static bool16 dir_first; // x_direction_t
	static bool16 dir_second; // x_direction_t

	#define vortex_unput_and_put_8(i) { \
		grc_sloppy_unput(prev.left[i], prev.top[i]); \
		vortex_or_debris_put_8( \
			cur.left[i], \
			cur.top[i], \
			(C_VORTEX + (boss_phase_frame % VORTEX_CELS)) \
		); \
	}

	#define vortex_fire_down(i) { \
		Pellets.add_group( \
			vortex_pellet_left(cur.left[i]), \
			vortex_pellet_top(cur.top[i]), \
			PG_1, \
			VORTEX_PELLET_SPEED \
		); \
	}

	#define vortex_unput_put_3_spread(i) { \
		vortex_unput_and_put_8(i); \
		if((boss_phase_frame % 4) == 0) { \
			vortex_fire_3_spread(cur.left, cur.top, i, angle); \
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
			cur.left[i] = (i * (PLAYFIELD_RIGHT - VORTEX_W));
			cur.top[i] = (PLAYFIELD_TOP + playfield_fraction_y(17 / 42.0f));

			vortex_unput_and_put_8(i);
			if((boss_phase_frame % 4) == 0) {
				vortex_fire_down(i);
			}
			prev.left[i] = cur.left[i];
			prev.top[i] = cur.top[i];
		}
	} else if(boss_phase_frame < pattern_state.frame) {
		for(int i = 0; i < VORTEX_COUNT; i++) {
			cur.left[i] += (i == 0) ? 5 : -5;
			cur.top[i] -= 2;

			vortex_unput_and_put_8(i);
			if((boss_phase_frame % 4) == 0) {
				vortex_fire_down(i);
				angle = iatan2(
					vortex_pellet_top(PLAYFIELD_BOTTOM - cur.top[i]),
					vortex_pellet_left(cur.left[i] +
						(i * ((PLAYFIELD_W / 8) * 2)) - (PLAYFIELD_W / 8) -
					cur.left[i])
				);
				Pellets.add_single(
					vortex_pellet_left(cur.left[i]),
					vortex_pellet_top(cur.top[i]),
					angle,
					VORTEX_PELLET_SPEED
				);
			}
			prev.left[i] = cur.left[i];
			prev.top[i] = cur.top[i];
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
			cur.left[i] += (2 - (dir_first * 4));
			vortex_unput_put_3_spread(i);
			prev.left[i] = cur.left[i];
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
				cur.left[i] -= (2 - (dir_second * 4));
			} else {
				cur.left[i] -= (4 - (dir_second * 8));
			}
			vortex_unput_put_3_spread(i);
			prev.left[i] = cur.left[i];
		}
	} else if(boss_phase_frame > 300) {
		for(int i = 0; i < VORTEX_COUNT; i++) {
			grc_sloppy_unput(cur.left[i], cur.top[i]);
		}
		wand_lower_both();
		boss_phase_frame = 0;
		wand_raise_animation_done = false;
	}

	#undef vortex_unput_put_3_spread
	#undef vortex_fire_down
	#undef vortex_unput_and_put_8
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

	static screen_x_t spawner_x[LASER_COUNT];
	static vram_y_t spawner_y[LASER_COUNT];

	if(boss_phase_frame < KEYFRAME_0) {
		return;
	}
	if(boss_phase_frame == KEYFRAME_0) {
		select_laser_speed_for_rank(pattern_state.speed_multiplied_by_8,
			8.5f, 9.0f, 9.5f, 10.0f
		);
		for(int i = 0; i < LASER_COUNT; i++) {
			spawner_x[i] = playfield_rand_x(0.1875f, 0.8125f);
			spawner_y[i] = playfield_rand_y((9 / 84.0f), (34 / 84.0f));
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
}

void near pattern_birds_on_ellipse_arc(void)
{
	static bool wand_raise_animation_done = false;
	static bird_pellet_group_t pellet_group = BPG_AIMED;
	static int eggs_alive = 0;
	static CEntities<BIRD_COUNT> egg;
	static Subpixel spawner_left;
	static Subpixel spawner_top;
	static Subpixel spawner_velocity_y;
	static Subpixel spawner_velocity_x;

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
		grc_sloppy_unput(spawner_left.to_pixel(), spawner_top.to_pixel());
		for(int i = (eggs_alive - 1); i >= 0; i--) {
			bird_put_8(egg.left[i], egg.top[i], C_EGG);
		}
		spawner_left.v += spawner_velocity_x.v;
		spawner_top.v += spawner_velocity_y.v;
		if((boss_phase_frame % pattern_state.interval) == 0) {
			if(overlap_xy_lrtb_le_ge(
				spawner_left.v, spawner_top.v,
				to_sp(0.0), to_sp(0.0f),
				to_sp(RES_X - SPAWNCROSS_W), to_sp(RES_Y - SPAWNCROSS_H)
			)) {
				egg.left[eggs_alive] = spawner_left.to_pixel();
				egg.top[eggs_alive] = spawner_top.to_pixel();
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
				birds_spawn(egg.left[i], egg.top[i], velocity.x, velocity.y);
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
			grc_sloppy_unput(spawner_left.to_pixel(), spawner_top.to_pixel());
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

	static screen_x_t cell_x;
	static vram_y_t cell_y;
	static vram_offset_t cell_vo;
	static int stripe_col_base;
	static int gust_id;

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
}

void pascal near particles2x2_vertical_unput_update_render(bool16 from_bottom)
{
	// Also indicates whether a particle is alive.
	static uint4_t col[PARTICLE2X2_COUNT] = { 0 };

	static double left[PARTICLE2X2_COUNT];
	static double top[PARTICLE2X2_COUNT];
	static double velocity_y[PARTICLE2X2_COUNT];

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

	static union {
		phase_t phase;
		int detonation_frame;
	} state = { P_RESET };
	static Subpixel left;
	static screen_x_t star_left;
	static Subpixel top;
	static vram_y_t star_top;
	static Subpixel velocity_y;
	static Subpixel velocity_x;
	static pixel_t radius_outer_1;
	static pixel_t radius_outer_2;
	static pixel_t radius_inner;

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
		// single frame, until we enter P_DETONATION_ACTIVE via the
		// [detonation_frame] in the condition below, where the X position is
		// randomized again.
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
		player_is_hit = true;
	}

	#undef ellipse_put
	#undef ellipse_sloppy_unput
}

void near pattern_2_rings_from_a2_orbs(void)
{
	static unsigned char angle;
	static int interval;

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
		Pellets.add_single(left, top, 0x00, 0, PM_SLING_AIMED, to_sp(4.5f));
	}
	if(boss_phase_frame >= 299) {
		boss_phase_frame = 0;
	}
}

void near particles2x2_wavy_unput_update_render()
{
	// Also indicates whether a particle is alive.
	static uint4_t col[PARTICLE2X2_COUNT] = { 0 };

	static screen_x_t left[PARTICLE2X2_COUNT];
	static vram_y_t top[PARTICLE2X2_COUNT];
	static pixel_t velocity_y[PARTICLE2X2_COUNT];
	static int age[PARTICLE2X2_COUNT];

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
		first_bit = (wave_left & BYTE_MASK);

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
		first_bit = (wave_left & BYTE_MASK);
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
}

void near pattern_four_aimed_lasers(void)
{
	#define ORIGIN_DISTANCE_X_1 (SEAL_CENTER_X - SEAL_RADIUS)
	#define ORIGIN_Y_1 FACE_CENTER_Y
	#define ORIGIN_Y_2 SHIELD_CENTER_Y

	static screen_x_t origin_x;
	static screen_y_t origin_y;
	static struct {
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
	static screen_x_t target_first;

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
		select_laser_speed_for_rank(pattern_state.speed_multiplied_by_8,
			7.5f, 8.0f, 8.5f, 9.0f
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
	screen_x_t left = playfield_rand_x();
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

	static unsigned char angle;
	static unsigned char angle_velocity;

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
		select_laser_speed_for_rank(pattern_state.speed_multiplied_by_8,
			7.5f, 8.125f, 8.75f, 9.375f
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
				shootout_laser_safe((boss_phase_frame - 215) / 15).spawn(
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

	#undef CENTER_Y
	#undef CENTER_X
}

void near pattern_symmetric_birds_from_bottom(void)
{
	enum {
		VELOCITY_X = 2,
	};

	static SymmetricSpawnraysWithDebris<
		PLAYFIELD_CENTER_X, FACE_CENTER_Y, (DEBRIS_W / 4)
	> rays;
	static point_t velocity;
	static vortex_or_debris_cel_t debris_cel;

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

	static SymmetricSpawnraysWithDebris<
		PLAYFIELD_CENTER_X, FACE_CENTER_Y, (DEBRIS_W / 4)
	> rays;

	// ZUN bug: Leaving this uninitialized indeed implies vortex sprites for
	// the first 5 frames, until this actually reaches C_DEBRIS...
	static vortex_or_debris_cel_t debris_cel;

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
	static pixel_t radius_prev;
	static bool16 active;

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
}

void pascal near particles2x2_horizontal_unput_update_render(int frame)
{
	// Also indicates whether a particle is alive.
	static uint4_t col[PARTICLE2X2_COUNT] = { 0 };

	static double left[PARTICLE2X2_COUNT];
	static double top[PARTICLE2X2_COUNT];
	static double velocity_x[PARTICLE2X2_COUNT];

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
}

struct CurvedSpray {
	screen_point_t target;
	Subpixel speed;
	unsigned char angle; // should be local
	int subpattern_id; // controlled by the pattern

	void init(void) {
		target.x = PLAYFIELD_LEFT;
		target.y = PLAYFIELD_BOTTOM;
		speed.set(7.0f);
		subpattern_id = 0;

		// Divisor = number of pellets effectively fired per direction.
		select_for_rank(pattern_state.velocity_x,
			(PLAYFIELD_W / 20),
			(PLAYFIELD_W / 26.66),
			(PLAYFIELD_W / 35.55),
			(PLAYFIELD_W / 40)
		);
	}

	void fire_and_advance(x_direction_t dir) {
		angle = iatan2((target.y - SEAL_CENTER_Y), (target.x - SEAL_CENTER_X));
		Pellets.add_single(SEAL_CENTER_X, SEAL_CENTER_Y, angle, speed);
		speed -= 0.25f;
		if(dir == X_RIGHT) {
			target.x += pattern_state.velocity_x;
		} else {
			target.x -= pattern_state.velocity_x;
		}
	}

	void reset(screen_x_t new_target) {
		speed.set(7.0f);
		target.x = new_target;
	}

	void reset_2(screen_x_t new_target) {
		target.x = new_target;
		speed.set(7.0f);
	}
};

void pascal near pattern_curved_spray_leftright_once(int &frame)
{
	static CurvedSpray spray;

	if(frame < 50) {
		return;
	} else if(frame == 50) {
		dottedcircle_unput_update_render(
			SEAL_CENTER_X, SEAL_CENTER_Y, 1, 4, 16, V_WHITE, 32, 160
		);
	}

	// The duration can be calculated as:
	//
	//	target_radius = √((RES_X - SEAL_CENTER_X)² + (RES_Y - SEAL_CENTER_Y)²)
	//	duration = (((target_radius - radius_initial) / radius_step) * interval)
	//
	// Good luck doing that at compile time, but given the variables defined
	// here, the result does come out as 88.38. So, close enough.
	dottedcircle_unput_update_render(
		SEAL_CENTER_X, SEAL_CENTER_Y, ((frame - 50) + 1), 4, 16, V_WHITE, 32, 90
	);

	if(frame < 100) {
		return;
	} else if(frame == 100) {
		spray.init();
	}

	if(spray.subpattern_id == 0) {
		spray.fire_and_advance(X_RIGHT);
		if(spray.target.x >= PLAYFIELD_RIGHT) {
			spray.subpattern_id = 1;
			spray.reset(PLAYFIELD_RIGHT);
		}
	} else {
		spray.fire_and_advance(X_LEFT);
		if(spray.target.x < PLAYFIELD_LEFT) {
			frame = 0;
		}
	}

	#undef spray
}

void pascal near pattern_rain_from_seal_center(int &frame)
{
	enum {
		VELOCITY_Y = 8,
	};

	static struct SymmetricSpawnraysWithDebris<
		SEAL_CENTER_X, SEAL_CENTER_Y, DEBRIS_W
	> rays;
	static vortex_or_debris_cel_t debris_cel_cur;
	static vortex_or_debris_cel_t debris_cel_prev;

	if(frame < 50) {
		return;
	} else if(frame == 50) {
		rays.target_l_x = PLAYFIELD_LEFT;
		rays.target_y = (PLAYFIELD_BOTTOM - 1);
		debris_cel_cur = C_DEBRIS;
		debris_cel_prev = C_DEBRIS;
		select_for_rank(pattern_state.pellet_count, 30, 35, 40, 45);
	}

	if(rays.target_y > SEAL_CENTER_Y) {
		if((frame % 2) == 0) {
			rays.unput_and_put(X_LEFT, debris_cel_cur);
		} else if((frame % 2) == 1) {
			rays.unput_and_put(X_RIGHT, debris_cel_cur);
			debris_cel_prev = debris_cel_cur;
			debris_cel_cur = debris_cel_next(debris_cel_cur);
			rays.target_y -= VELOCITY_Y;
		}
		if((frame % 10) == 0) {
			mdrv2_se_play(6);
		}
		return;
	}

	mdrv2_se_play(3);
	rays.unput_broken(VELOCITY_Y);

	for(int i = 0; i < pattern_state.pellet_count; i++) {
		pellets_add_single_rain(
			(PLAYFIELD_LEFT + ((PLAYFIELD_W / pattern_state.pellet_count) * i)),
			SEAL_CENTER_Y,
			rand(),
			1.0f
		);
	}
	frame = 0;
}

void pascal near pattern_curved_spray_leftright_twice(int &frame)
{
	static CurvedSpray spray;

	if(frame < 80) {
		return;
	} else if(frame == 80) {
		spray.init();
	}
	if((spray.subpattern_id % 2) == 0) {
		spray.fire_and_advance(X_RIGHT);
		if(spray.target.x >= PLAYFIELD_RIGHT) {
			spray.subpattern_id++;
			spray.reset(PLAYFIELD_RIGHT);
		}
	} else {
		spray.fire_and_advance(X_LEFT);
		if(spray.target.x < PLAYFIELD_LEFT) {
			spray.subpattern_id++;
			spray.reset_2(PLAYFIELD_LEFT);
			if(spray.subpattern_id == 4) {
				frame = 0;
			}
		}
	}
}

void pascal near pattern_swaying_leaves(int &frame, int spawn_interval_or_reset)
{
	enum {
		LEAF_COUNT = 30,
	};

	enum leaf_flag_t {
		LF_FREE = 0,
		LF_SPARK = 1,
		LF_SPLASH = 2,

		// Separate state because it assigns the velocity for the next one.
		LF_SPLASH_DONE = (LF_SPLASH + LEAFSPLASH_CELS),

		LF_LEAF,

		_leaf_flag_t_FORCE_INT16 = 0x7FFF,
	};

	static leaf_flag_t flag[LEAF_COUNT] = { LF_FREE };
	static DecimalSubpixel left[LEAF_COUNT];
	static DecimalSubpixel top[LEAF_COUNT];
	static DecimalSubpixel velocity_x[LEAF_COUNT];
	static DecimalSubpixel velocity_y[LEAF_COUNT];

	#define leaf_on_screen(i) \
		overlap_xy_rltb_lt_ge( \
			left[i].v, \
			top[i].v, \
			to_dsp(0.0f), \
			to_dsp(0.0f), \
			to_dsp(RES_X - LEAF_W), \
			to_dsp(RES_Y - LEAF_H) \
		)

	#define leaf_put(tmp_vo, tmp_first_bit, i, sprite) { \
		if(leaf_on_screen(i)) { \
			tmp_vo = vram_offset_divmul( \
				left[i].to_pixel(), top[i].to_pixel() \
			); \
			tmp_first_bit = (left[i].to_pixel() % BYTE_DOTS); \
			grcg_put_8x8_mono(tmp_vo, tmp_first_bit, sprite[0].row, V_WHITE); \
		} \
	}

	// Code generation needs them to be separate, unfortunately...
	#include "th01/sprites/leaf_s.csp"
	#include "th01/sprites/leaf_l.csp"
	#include "th01/sprites/leaf_r.csp"

	int i;
	vram_offset_t vo;
	int first_bit;

	if(spawn_interval_or_reset == 999) {
		for(i = 0; i < LEAF_COUNT; i++) {
			flag[i] = LF_FREE;
		}
		return;
	}
	if((frame % spawn_interval_or_reset) == 0) {
		for(i = 0; i < LEAF_COUNT; i++) {
			if(flag[i] != LF_FREE) {
				continue;
			}
			left[i].v = (
				to_dsp(PLAYFIELD_LEFT) + (rand() % to_dsp(PLAYFIELD_W))
			);
			top[i].v = (
				to_dsp(FACE_CENTER_Y) +
				(rand() % to_dsp((PLAYFIELD_H * 25) / 84))
			);
			vector2_between(
				left[i].to_pixel(),
				top[i].to_pixel(),
				playfield_rand_x(),
				PLAYFIELD_TOP,
				velocity_x[i].v,
				velocity_y[i].v,
				to_dsp(4.0f)
			);
			flag[i] = LF_SPARK;
			break;
		}
	}

	if((frame % 2) != 0) {
		return;
	}

	// Unblit and update
	for(i = 0; i < LEAF_COUNT; i++) {
		if(flag[i] == LF_FREE) {
			continue;
		}
		if(flag[i] == LF_SPARK) {
			if(leaf_on_screen(i)) {
				egc_copy_rect_1_to_0_16_word_w(
					left[i].to_pixel(), top[i].to_pixel(), LEAF_W, LEAF_H
				);
			}
			left[i].v += velocity_x[i].v;
			top[i].v += velocity_y[i].v;
			if(top[i].v < to_dsp(PLAYFIELD_TOP)) {
				flag[i] = LF_SPLASH;
			}
		} else if(flag[i] <= LF_SPLASH_DONE) {
			if(leaf_on_screen(i)) {
				grc_sloppy_unput(left[i].to_pixel(), top[i].to_pixel());
			}
			if(flag[i] == LF_SPLASH_DONE) {
				flag[i] = LF_LEAF;
				velocity_y[i].v = (to_dsp(0.3f) + (rand() % to_dsp(0.2f)));
				velocity_x[i].v = to_dsp(0.2f);
			}
		} else if(flag[i] == LF_LEAF) {
			if(leaf_on_screen(i)) {
				egc_copy_rect_1_to_0_16_word_w(
					left[i].to_pixel(), top[i].to_pixel(), LEAF_W, LEAF_H
				);
			}
			left[i].v += velocity_x[i].v;
			top[i].v += velocity_y[i].v;
			velocity_y[i].v--;
			if(velocity_y[i].v < to_dsp(-0.1f)) {
				velocity_y[i].v = (to_dsp(3.0f) + (rand() % to_dsp(2.0f)));
				velocity_x[i].v = (velocity_x[i].v < to_dsp(0.0f))
					? to_dsp(+2.0f)
					: to_dsp(-2.0f);
			}
			if(top[i].to_pixel() > PLAYFIELD_BOTTOM) {
				flag[i] = LF_FREE;
			}
		}
	}

	// Render and detect player collisions
	for(i = 0; i < LEAF_COUNT; i++) {
		if(flag[i] == LF_FREE) {
			continue;
		}
		if(flag[i] == LF_SPARK) {
			leaf_put(vo, first_bit, i, sSPARK);
		} else if(flag[i] <= LF_SPLASH_DONE) {
			if(leaf_on_screen(i)) {
				// ZUN bug: Another missing conversion to screen pixels,
				// resulting in the entire leaf splash animation never being
				// actually rendered, and becoming effectively unused.
				grc_put_8(
					left[i].v, // should be pixels
					top[i].v, // should be pixels
					GRC_SLOT_LEAFSPLASH,
					(flag[i] - LF_SPLASH),
					V_WHITE
				);
			}
			if((frame % 4) == 0) {
				static_cast<int>(flag[i])++;
			}
		} else if(flag[i] == LF_LEAF) {
			leaf_put(vo, first_bit, i, ((velocity_x[i].v < to_dsp(0.0f))
				? sLEAF_LEFT
				: sLEAF_RIGHT
			));
			if(
				(top[i].v > to_dsp(player_top)) &&
				(top[i].v < to_dsp(player_bottom() - LEAF_H)) &&
				(left[i].to_pixel() > player_left) &&
				(left[i].to_pixel() < (player_left + PLAYER_W - LEAF_W)) &&
				!player_invincible
			) {
				player_is_hit = true;
			}
		}
	}

	#undef leaf_put
	#undef leaf_on_screen
}

void sariel_main(void)
{
	enum {
		PHASE_FORM1_DEFEATED = 99,
		PHASE_FORM2 = 100,
		PHASE_FORM2_DEFEATED = 101,

		MAGNITUDE = 16,
	};

	static bool16 invincible;
	static int invincibility_frame;
	static pixel_t entrance_ring_radius_base;
	static bool initial_hp_rendered;
	static struct {
		int pattern_cur;
		union {
			int patterns_done;
			int pulse_fade_direction;
		} u1;
		int patterns_until_next;

		void next(int phase) {
			boss_phase = phase;
			boss_phase_frame = 0;
			// Shouldn't this be bg_transition()'s job?
			wand_lowered_snap();
		}

		void frame_common(bool form2) {
			boss_phase_frame++;
			invincibility_frame++;
			if(!form2) {
				shield_render_both();
				dress_render_both();
			}
		}

		void frame_bg_transition(int next_bg_id) {
			boss_phase_frame++;
			bg_transition(next_bg_id);
			dress_render_both();
		}

		void pattern_next(int ring_min, int ring_max) {
			if(ring_max == 1) {
				pattern_cur = (1 - pattern_cur);
			} else {
				pattern_cur = (pattern_cur == ring_max)
					? ring_min
					: (pattern_cur + 1);
			}
			// ZUN quirk: Modifying this variable during the second form also
			// causes the pulse effect to switch its fade direction. Might have
			// even been sort of intended.
			u1.patterns_done++;
		}
	} phase = { 0, 0, 0 };

	#define phase_form1_next_if_done(next_phase) { \
		if(boss_hp <= 0) { \
			boss_phase = PHASE_FORM1_DEFEATED; \
		} \
		if( \
			(phase.u1.patterns_done >= phase.patterns_until_next) && \
			!invincible \
		) { \
			phase.u1.patterns_done = 0; \
			boss_phase = next_phase; \
			phase.pattern_cur = 0; \
			boss_phase_frame = 0; \
		} \
	}

	unsigned int i;
	const unsigned char flash_colors[3] = { 3, 4, 5 };

	struct {
		bool padding;
		bool colliding_with_orb;

		void update_and_render(const unsigned char (&flash_colors)[3]) {
			boss_hit_update_and_render(
				invincibility_frame,
				invincible,
				boss_hp,
				flash_colors,
				sizeof(flash_colors),
				10000,
				boss_nop,
				colliding_with_orb,
				shot_hitbox_t(
					FACE_LEFT, FACE_TOP, ((FACE_W * 5) / 4), ((FACE_H * 3) / 4)
				)
			);
		}
	} hit;

	hit.colliding_with_orb = overlap_xy_xywh_le_ge(
		orb_cur_left, orb_cur_top,
		FACE_LEFT, FACE_TOP, (FACE_W - ORB_W), (FACE_H - ORB_H)
	) || ent_shield.hittest_orb();

	if(boss_phase == 0) {
		boss_phase_frame = -1;
		invincibility_frame = 0;
		invincible = false;
		boss_palette_snap();
		stage_palette_set(z_Palettes);
		random_seed = frame_rand;

		while(1) {
			#define frame_half	boss_phase_frame

			unsigned int tmp;

			frame_half++;
			if(entrance_rings_update_and_render(
				entrance_ring_radius_base, i, tmp, frame_half, 16, 1
			)) {
				boss_phase = 1;
				phase.pattern_cur = 0;
				phase.u1.patterns_done = 0;
				phase.patterns_until_next = ((rand() % 6) + 1);
				boss_phase_frame = 0;
				initial_hp_rendered = 0;
				boss_palette_show(); // Unnecessary.
				ent_shield.pos_cur_set(SHIELD_LEFT, SHIELD_TOP);
				wand_lowered_snap();
				wand_render_raise_both(true);
				birds_reset();
				break;
			}
entrance_rings_still_active:
			if(frame_half % 2) { // That's why we've renamed the variable
				frame_delay(1);
			}
			#undef frame_half
		}
	} else if(boss_phase == 1) {
		hud_hp_increment_render(initial_hp_rendered, boss_hp, boss_phase_frame);
		phase.frame_common(false);
		birds_unput_update_render();

		if(phase.pattern_cur == 0) {
			pattern_random_purple_lasers();
		} else if(phase.pattern_cur == 1) {
			pattern_vortices();
		} else if(phase.pattern_cur == 2) {
			pattern_birds_on_ellipse_arc();
		}

		if(boss_phase_frame == 0) {
			phase.pattern_next(0, 2);
		}
		hit.update_and_render(flash_colors);
		phase_form1_next_if_done(2);
	} else if(boss_phase == 2) {
		phase.frame_bg_transition(1);
		if(boss_phase_frame == 0) {
			phase.next(3);
			// Assume that the palette didn't change between background ID 0
			// and 1...
			// boss_palette_snap();
			phase.patterns_until_next = ((rand() % 5) + 1);
		}
	} else if(boss_phase == 3) {
		phase.frame_common(false);
		particles2x2_vertical_unput_update_render(false);

		if(phase.pattern_cur == 0) {
			pattern_detonating_snowflake();
			pattern_2_rings_from_a2_orbs();
		} else if(phase.pattern_cur == 1) {
			pattern_aimed_sling_clusters();
			pattern_2_rings_from_a2_orbs();
		} else if(boss_phase_frame < 60) {
			boss_phase_frame = 0;
		}

		if(boss_phase_frame == 0) {
			phase.pattern_next(0, 1);
		}
		hit.update_and_render(flash_colors);
		phase_form1_next_if_done(4);
	} else if(boss_phase == 4) {
		phase.frame_bg_transition(2);
		if(boss_phase_frame == 0) {
			phase.next(5);
			boss_palette_snap();
			phase.patterns_until_next = ((rand() % 4) + 3);
		}
	} else if(boss_phase == 5) {
		phase.frame_common(false);
		particles2x2_wavy_unput_update_render();

		if(phase.pattern_cur == 0) {
			pattern_four_aimed_lasers();
		} else if(phase.pattern_cur == 1) {
			shake_for_50_frames();
		} else if(phase.pattern_cur == 2) {
			pattern_four_aimed_lasers();
			pattern_rain_from_top();
		} else if(phase.pattern_cur == 3) {
			pattern_radial_stacks_and_lasers();
		} else if(phase.pattern_cur == 4) {
			shake_for_50_frames();
		} else if(phase.pattern_cur == 5) {
			pattern_four_aimed_lasers();
			pattern_rain_from_top();
		}

		if(boss_phase_frame == 0) {
			phase.pattern_next(10, 5); // ???
		}
		hit.update_and_render(flash_colors);
		phase_form1_next_if_done(6);
	} else if(boss_phase == 6) {
		phase.frame_bg_transition(3);
		if(boss_phase_frame == 0) {
			phase.next(7);
			boss_palette_snap();
			phase.patterns_until_next = ((rand() % 5) + 2);
		}
	} else if(boss_phase == 7) {
		phase.frame_common(false);
		particles2x2_vertical_unput_update_render(true);
		birds_unput_update_render();

		if(phase.pattern_cur == 0) {
			pattern_symmetric_birds_from_bottom();
		} else if(phase.pattern_cur == 1) {
			pattern_four_semicircle_spreads();
		} else if(phase.pattern_cur == 2) {
			pattern_vertical_stacks_from_bottom_then_random_rain_from_top();
		}

		if(boss_phase_frame == 0) {
			phase.pattern_next(0, 2);
		}
		hit.update_and_render(flash_colors);
		phase_form1_next_if_done(8);
	} else if(boss_phase == 8) {
		phase.frame_bg_transition(0);
		if(boss_phase_frame == 0) {
			phase.next(1);
			boss_palette_snap();
			phase.patterns_until_next = ((rand() % 6) + 1);
		}
	} else if(boss_phase == PHASE_FORM1_DEFEATED) {
		boss_phase_frame = 0;

		// Not that this variable is ever read from, before it's set back to 0
		// at the end of the transition animation.
		invincibility_frame = 399;

		Shots.unput_and_reset();
		Pellets.unput_and_reset();
		shootout_lasers_unput_and_reset_broken(i, SHOOTOUT_LASER_COUNT);

		// MODDERS: Move this to a common player reset function.
		orb_cur_left = ORB_LEFT_START;
		orb_cur_top = ORB_TOP_START;
		player_left = PLAYER_LEFT_START;
		orb_force = ORB_FORCE_START;
		orb_force_frame = 0;
		orb_velocity_x = ORB_VELOCITY_X_START;
		player_deflecting = false;
		bomb_damaging = false;
		player_reset();

		invincible = false;
		random_seed = frame_rand;
		mdrv2_bgm_fade_out_nonblock();

		// boss6.grp is not part of the game? Might have been a defeat graphic.
		graph_accesspage_func(1);
		grp_put_palette_show("boss6.grp");
		z_palette_set_show(0xF, 0x0, 0x0, 0x0);
		boss_palette_snap();
		graph_copy_accessed_page_to_other();

		graph_accesspage_func(1);
		grp_put("boss6_a5.grp");
		graph_accesspage_func(0);

		while(1) {
			boss_phase_frame++;
			if(boss_phase_frame < 200) {
				if((boss_phase_frame % 2) == 0) {
					z_palette_set_show(
						0xF, RGB4::max(), RGB4::max(), RGB4::max()
					);
					z_vsync_wait_and_scrollup(RES_Y + MAGNITUDE);
				}
				if((boss_phase_frame % 2) == 1) {
					boss_palette_show();
					z_vsync_wait_and_scrollup(RES_Y - (MAGNITUDE - 2)); // ???
				}
				if((boss_phase_frame % 4) == 0) {
					mdrv2_se_play(9);
				}
			}
			if(boss_phase_frame == 200) {
				boss_palette_show();
				z_vsync_wait_and_scrollup(0);
			}
			if(boss_phase_frame > 200) {
				for(i = 0; i < COMPONENT_COUNT; i++) {
					grp_palette[0xF].v[i] = 0x0;
				}
				// The palette was loaded from boss6_a5.grp earlier.
				pagetrans_diagonal_8x8_with_palette(0, z_Palettes, grp_palette);
				graph_accesspage_func(1);
				mdrv2_bgm_load("syugen.MDT");
				mdrv2_bgm_play();
				grp_put_palette_show("boss6_a6.grp");
				z_palette_set_show(COL_FORM2_PULSE, 0x0, 0x0, 0x0);
				graph_copy_accessed_page_to_other();
				hud_rerender();
				z_vsync_wait_and_scrollup(0);
				boss_phase_frame = 0;
				invincibility_frame = 0;
				phase.pattern_cur = 0;
				phase.u1.pulse_fade_direction = 0;
				boss_phase = PHASE_FORM2;
				player_invincibility_time = 0;
				player_invincible = false;
				boss_palette_snap();
				stage_palette_set(z_Palettes);

				boss_hp = 6;
				hud_hp_first_white = 10;
				hud_hp_first_redwhite = 3;
				initial_hp_rendered = false;
				pattern_swaying_leaves(boss_phase_frame, 999);
				return;
			} else {
				frame_delay(1);
			}
		}
	} else if(boss_phase == PHASE_FORM2) {
		hud_hp_increment_render(initial_hp_rendered, boss_hp, boss_phase_frame);
		phase.frame_common(true);
		particles2x2_horizontal_unput_update_render(boss_phase_frame);

		if(phase.pattern_cur == 0) {
			// Hey, that variable is supposed to be off-limits to the main
			// function! (And also completely pointless, since it could have
			// just been done locally for pattern 4.)
			select_for_rank(pattern_state.interval, 56, 32, 24, 20);

			if(boss_phase_frame > 100) {
				boss_phase_frame = 0;
			}
		} else if(phase.pattern_cur == 1) {
			pattern_curved_spray_leftright_once(boss_phase_frame);
		} else if(phase.pattern_cur == 2) {
			pattern_rain_from_seal_center(boss_phase_frame);
		} else if(phase.pattern_cur == 3) {
			pattern_curved_spray_leftright_twice(boss_phase_frame);
		} else if(phase.pattern_cur == 4) {
			pattern_swaying_leaves(boss_phase_frame, pattern_state.interval);
			if(boss_phase_frame > 300) {
				boss_phase_frame = 0;
			}
		} else if(phase.pattern_cur == 5) {
			pattern_swaying_leaves(boss_phase_frame, 500);
			if(boss_phase_frame > 200) {
				boss_phase_frame = 0;
			}
		} else if(phase.pattern_cur == 6) {
			pattern_swaying_leaves(boss_phase_frame, 500);
			pattern_curved_spray_leftright_once(boss_phase_frame);
		} else if(phase.pattern_cur == 7) {
			pattern_swaying_leaves(boss_phase_frame, 500);
			pattern_rain_from_seal_center(boss_phase_frame);
		} else if(phase.pattern_cur == 8) {
			pattern_swaying_leaves(boss_phase_frame, 32);
			pattern_curved_spray_leftright_twice(boss_phase_frame);
		}

		if(boss_phase_frame == 0) {
			phase.pattern_next(4, 8);
		}
		hit.update_and_render(flash_colors);

		if((boss_phase_frame % 10) == 0) {
			// Setting just the COL_FORM2_PULSE entry in this palette surely
			// doesn't require resetting the hardware palette to the intended
			// boss palette, modifying the one entry, and then capturing the
			// palette again...
			boss_palette_show();
			if(phase.u1.pulse_fade_direction == 0) {
				if(z_Palettes[COL_FORM2_PULSE].c.r < 0xA) {
					z_Palettes[COL_FORM2_PULSE].c.r++;
				} else {
					phase.u1.pulse_fade_direction = 1;
				}
				if(z_Palettes[COL_FORM2_PULSE].c.g < 0xA) {
					z_Palettes[COL_FORM2_PULSE].c.g++;
				}
				if(z_Palettes[COL_FORM2_PULSE].c.b < 0x6) {
					z_Palettes[COL_FORM2_PULSE].c.b++;
				}
			} else {
				if(z_Palettes[COL_FORM2_PULSE].c.r > 0x0) {
					z_Palettes[COL_FORM2_PULSE].c.r--;
				} else {
					phase.u1.pulse_fade_direction = 0;
				}
				if(z_Palettes[COL_FORM2_PULSE].c.g > 0x0) {
					z_Palettes[COL_FORM2_PULSE].c.g--;
				}
				if(z_Palettes[COL_FORM2_PULSE].c.b > 0x0) {
					z_Palettes[COL_FORM2_PULSE].c.b--;
				}
			}
			// Yeah, what a waste.
			z_palette_set_all_show(z_Palettes);
			boss_palette_snap();
		}

		if(boss_hp <= 0) {
			mdrv2_bgm_stop();
			boss_phase = PHASE_FORM2_DEFEATED;
			boss_phase_frame = 0;
			invincibility_frame = 0;
		}
	} else if(boss_phase == PHASE_FORM2_DEFEATED) {
		graph_accesspage_func(1);
		grp_put_palette_show("boss6_a6.grp");

		// Actually a different color inside the .GRP! Would have been nicer to
		// reuse the previous state of the color from above.
		z_palette_set_show(COL_FORM2_PULSE, 0x0, 0x0, 0x0);

		boss_palette_snap(); // No longer necessary.

		graph_copy_accessed_page_to_other();
		graph_accesspage_func(0);

		while(1) {
			boss_phase_frame++;
			if(boss_phase_frame < 230) {
				if((boss_phase_frame % 2) == 0) {
					z_vsync_wait_and_scrollup(RES_Y + MAGNITUDE);
				}
				if((boss_phase_frame % 2) == 1) {
					z_vsync_wait_and_scrollup(RES_Y - (MAGNITUDE - 2)); // ???
				}
				if((boss_phase_frame < 200) && ((boss_phase_frame % 4) == 0)) {
					mdrv2_se_play(9);
				}
			}
			if(boss_phase_frame == 170) {
				mdrv2_bgm_fade_out_nonblock();
			}
			if(boss_phase_frame > 190) {
				if((boss_phase_frame % 2) == 0) {
					unsigned int comp;
					z_palette_black_out_step_bugged(i, comp);
				}
				if(boss_phase_frame > 230) {
					break;
				}
			}
			frame_delay(2);
		}

		z_vsync_wait_and_scrollup(0);
		sariel_free();

		// Makai clear! Grant 50,000 score points in the fanciest way
		for(i = 0; i < 5; i++) {
			score += 10000;
		}
		game_cleared = true;
	}

	#undef phase_form1_next_if_done
}
