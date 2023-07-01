/// Makai Stage 15 Boss - Elis
/// --------------------------

#include <dos.h>
#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "platform/x86real/pc98/page.hpp"
#include "master.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/formats/grc.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/entity.hpp"
#include "th01/main/playfld.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/shape.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/defeat.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/bullet/pellet.hpp"

// Coordinates
// -----------

static const pixel_t GIRL_W = 128;
static const pixel_t GIRL_H = 96;
static const pixel_t BAT_W = 48;
static const pixel_t BAT_H = 32;

static const screen_x_t BASE_CENTER_X = PLAYFIELD_CENTER_X;
static const screen_y_t BASE_CENTER_Y = (
	PLAYFIELD_TOP + ((PLAYFIELD_H / 21) * 5)
);

static const screen_x_t BASE_LEFT = (BASE_CENTER_X - (GIRL_W / 2));
static const screen_y_t BASE_TOP = (BASE_CENTER_Y - (GIRL_H / 2));
// -----------

enum elis_colors_t {
	COL_FX = 4,
	COL_ENTRANCE_SPHERE = 8,
};

// Always denotes the last phase that ends with that amount of HP.
enum elis_hp_t {
	HP_TOTAL = 14,
	HP_PHASE_1_END = 10,
	HP_PHASE_3_END = 6,
	HP_PHASE_5_END = 0,
};

// Entities
// --------

enum elis_form_t {
	F_GIRL = 0,
	F_BAT = 1,

	_elis_form_t_FORCE_INT16 = 0x7FFF,
};

static const int BAT_CELS = 3;
static const int BAT_FRAMES_PER_CEL = 3;
static const int BAT_CYCLE_FRAMES = (BAT_CELS * BAT_FRAMES_PER_CEL);
static const int BAT_SPEED_DIVISOR = 3;

enum elis_entity_cel_t {
	// ENT_STILL_OR_WAVE
	C_STILL = 0,
	C_HAND = 1,
	C_WAVE_1 = 2,
	C_WAVE_2 = 3,
	C_WAVE_3 = 4,
	C_WAVE_4 = 5, // (unused)

	// ENT_ATTACK
	C_PREPARE = 0,
	C_ATTACK_1 = 1,
	C_ATTACK_2 = 2,

	// ENT_BAT
	C_BAT = 0,
	C_BAT_last = (C_BAT + BAT_CELS - 1),
};

struct CGirlEntity : public CBossEntitySized<GIRL_W, GIRL_H> {
	pixel_t surround_area_offset_y(pixel_t area_h) const {
		return -(area_h - h_static()); // not centered
	}

	void pos_cur_set_to(CBossEntity& other) {
		pos_cur_set(other.cur_left, other.cur_top);
	}
};

struct CBatEntity : public CBossEntitySized<BAT_W, BAT_H> {
	pixel_t surround_area_offset_y(pixel_t area_h) const {
		return -((area_h - h_static()) / 2); // centered
	}

	void pos_cur_set_to(CGirlEntity& girl) {
		pos_cur_set(
			(girl.cur_left + ((girl.w_static() - w_static()) / 2)),
			(girl.cur_top  + ((girl.h_static() - h_static()) / 2))
		);
	}
};

#define ent_still_or_wave \
	reinterpret_cast<CGirlEntity &>(boss_entity_0)

#define ent_attack \
	reinterpret_cast<CGirlEntity &>(boss_entity_1)

#define ent_bat \
	reinterpret_cast<CBatEntity &>(boss_entity_2)

// 1 for [ent_still_or_wave], 2 for [ent_attack]. Not actually needed anywhere
// it's used, so it doesn't warrant subclassing those two just to solve that
// distinction via pseudo-polymorphism.
typedef int unnecessary_1_or_2_t;

inline void elis_ent_load(void) {
	ent_still_or_wave.load("boss5.bos", 0);
	ent_attack.load("boss5_2.bos", 1);
	ent_bat.load("boss5_3.bos", 2);
}

inline void elis_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
}

// It's needed in the functions below...
void girl_bg_put(unnecessary_1_or_2_t unnecessary);

// [unput_0] should theoretically always be `true`. Making sure that both VRAM
// pages are identical avoids visual glitches from blitting cels with different
// transparent areas on top of each other (see: Mima's third arm)… but you can
// always just *assume* rather than ensure, right? :zunpet:
inline void ent_unput_and_put_both(
	CBossEntity& ent,
	unnecessary_1_or_2_t unnecessary,
	elis_entity_cel_t cel,
	bool unput_0 = true
) {
	page_access(1);
	girl_bg_put(unnecessary);
	ent.unlock_put_image_lock_8(cel);
	page_access(0);
	if(unput_0) {
		girl_bg_put(unnecessary);
	}
	ent.unlock_put_image_lock_8(cel);
}

inline void ent_put_both(CBossEntity& ent, elis_entity_cel_t cel) {
	page_access(1); ent.unlock_put_image_lock_8(cel);
	page_access(0); ent.unlock_put_image_lock_8(cel);
}

#define ent_attack_render() { \
	if((boss_phase_frame % 8) == 0) { \
		ent_unput_and_put_both(ent_attack, 2, C_ATTACK_1); \
	} else if((boss_phase_frame % 8) == 4) { \
		ent_put_both(ent_attack, C_ATTACK_2); \
	} \
}
// --------

// Form-relative coordinates
// -------------------------

// Since we can't use shot_hitbox_t() in the main function due to [form] being
// both a compile-time constant and a variable at runtime, we have to manually
// replicate it here. This is also the only reason why the shot_hitbox_(w|h)()
// macros have to exist.
#include "th01/main/player/shot.hpp"
#define form_shot_hitbox_w(form) ( \
	(form == F_GIRL) \
		? shot_hitbox_w((GIRL_W / 8) * 5) \
		: shot_hitbox_w(BAT_W) \
)
#define form_shot_hitbox_h(form) ( \
	(form == F_GIRL) \
		? shot_hitbox_h((GIRL_H / 3) * 2) \
		: shot_hitbox_h(( BAT_H * 3) / 2) \
)

inline screen_x_t form_center_x(elis_form_t form) {
	return (form == F_GIRL)
		? ent_still_or_wave.cur_center_x()
		: ent_bat.cur_center_x();
}

inline screen_y_t form_center_y(elis_form_t form) {
	return (form == F_GIRL)
		? ent_still_or_wave.cur_center_y()
		: ent_bat.cur_center_y();
}

inline screen_x_t form_shot_hitbox_left(elis_form_t form) {
	return (form == F_GIRL)
		? (ent_still_or_wave.cur_left + (GIRL_W / 4))
		: ent_bat.cur_left;
}

inline screen_y_t form_shot_hitbox_top(elis_form_t form) {
	return (form == F_GIRL)
		? (ent_still_or_wave.cur_top + (GIRL_H / 3))
		: ent_bat.cur_left; // ZUN quirk: Should be cur_top
}

inline screen_x_t girl_lefteye_x(void) {
	return (ent_still_or_wave.cur_left + 60);
}

inline screen_y_t girl_lefteye_y(void) {
	return (ent_still_or_wave.cur_top + 28);
}

inline screen_x_t girl_wing_left_center_x(void) {
	return (form_center_x(F_GIRL) - 38);
}

inline screen_x_t girl_wing_right_center_x(void) {
	return (form_center_x(F_GIRL) + 40);
}

inline screen_y_t girl_wing_center_y(void) {
	return (form_center_y(F_GIRL) - 4);
}

#define form_fire_group(form, group, speed) { \
	Pellets.add_group( \
		(form_center_x(form) - (PELLET_W / 2)), \
		(form_center_y(form) - (PELLET_H / 2)), \
		group, \
		to_sp(speed) \
	); \
}
// -------------------------

// Surround area
// -------------
// Common bullet spawn area around Elis.

static const pixel_t SURROUND_AREA_W = ((PLAYFIELD_W * 3) / 10);
static const pixel_t SURROUND_AREA_H = ((PLAYFIELD_H * 8) / 21);

#define surround_random_left(relative_to) ( \
	(relative_to.cur_left + (rand() % SURROUND_AREA_W)) - \
	((SURROUND_AREA_W - relative_to.w_static()) / 2) \
)

#define surround_random_top(relative_to) ( \
	(relative_to.cur_top + (rand() % SURROUND_AREA_H)) + \
	relative_to.surround_area_offset_y(SURROUND_AREA_H) \
)
// -------------

// Random teleport and bat movement coordinates
// --------------------------------------------

inline screen_x_t elis_playfield_random_left(void) {
	return (PLAYFIELD_LEFT + (rand() % (PLAYFIELD_W - GIRL_W)));
}

inline screen_y_t elis_playfield_random_top(void) {
	return playfield_rand_y(0.0f, (17 / 42.0f));
}
// --------------------------------------------

// .GRC entities
// -------------

static const pixel_t SPHERE_W = 32;
static const pixel_t SPHERE_H = 32;

enum elis_grc_cel_t {
	RIFT_CELS = 2,

	C_EMPTY = 0,
	C_SPHERE_SMALL,
	C_SPHERE_MEDIUM,
	C_SPHERE_LARGE,
	C_RIFT,
	C_RIFT_last = (C_RIFT + RIFT_CELS - 1),
};

#define elis_grc_sloppy_unput(entities, i) { \
	grc_sloppy_unput(entities.left[i], entities.top[i]); \
}

#define elis_grc_put(entities, i, cel, col) { \
	grc_put_8(entities.left[i], entities.top[i], GRC_SLOT_BOSS_1, cel, col); \
}

#define sphere_put(left, top, cel) { \
	grc_put_8(left, top, GRC_SLOT_BOSS_1, cel, COL_ENTRANCE_SPHERE); \
}

#define sphere_unput(left, top) { \
	grc_sloppy_unput(left, top) \
}

#define rifts_update_and_render( \
	rifts, ent, start_frame, end_frame, col, tmp_cel \
) { \
	if( \
		(boss_phase_frame >= start_frame) && \
		(boss_phase_frame <= end_frame) && \
		((boss_phase_frame % 4) == 0) \
	) { \
		for(int i = 0; i < rifts.count(); i++) { \
			/* Unblit */ \
			if(boss_phase_frame > start_frame) { \
				elis_grc_sloppy_unput(rifts, i); \
			} \
			\
			/* Initialize */ \
			if( \
				((boss_phase_frame % 16) == ((i * 4) % 16)) || \
				(boss_phase_frame == start_frame) \
			) { \
				rifts.left[i] = surround_random_left(ent); \
				rifts.top[i] = surround_random_top(ent); \
			} \
			\
			/* Render */ \
			if(boss_phase_frame < end_frame) { \
				tmp_cel = (rand() % RIFT_CELS); \
				elis_grc_put(rifts, i, (C_RIFT + cel), col); \
			} \
		} \
		mdrv2_se_play(7); \
	} \
}
// -------------

// Shared big circle
// -----------------
// Concrete circle structures must look like this: {
// 	unsigned char angle;
// 	int frame;
//
// 	screen_x_t center_x(void) { return …; };
// 	screen_y_t center_y(void) { return …; };
// };

static const pixel_t BIGCIRCLE_RADIUS = ((GIRL_W * 2) / 2);

#define bigcircle_sloppy_unput(bigcircle) { \
	shape_circle_sloppy_unput( \
		bigcircle.center_x(), bigcircle.center_y(), BIGCIRCLE_RADIUS, 0x01 \
	); \
}

#define bigcircle_put_arc(bigcircle, angle_start, angle_end, col) { \
	shape_ellipse_arc_put( \
		bigcircle.center_x(), \
		bigcircle.center_y(), \
		BIGCIRCLE_RADIUS, \
		BIGCIRCLE_RADIUS, \
		col, \
		0x01, \
		angle_start, \
		angle_end \
	); \
}

#define bigcircle_put(bigcircle, col) { \
	bigcircle_put_arc(bigcircle, 0x00, 0xFF, col); \
}

#define bigcircle_put_dot(bigcircle, offset_start, offset_end, col) { \
	bigcircle_put_arc( \
		bigcircle, \
		(bigcircle.angle + offset_start), \
		(bigcircle.angle + offset_end), \
		col \
	); \
}

#define bigcircle_is_summon_frame(start_frame) ( \
	(boss_phase_frame >= start_frame) && ((boss_phase_frame % 2) == 0) \
)

#define bigcircle_summon_done(bigcircle) \
	(bigcircle.angle >= (0x100 / 4))

#define bigcircle_summon_update_and_render(bigcircle, q4_offset_end) { \
	bigcircle_put_dot(bigcircle, 0x00, q4_offset_end, V_WHITE); \
	bigcircle_put_dot(bigcircle, 0x40, 0x42, V_WHITE); \
	bigcircle_put_dot(bigcircle, 0x80, 0x82, V_WHITE); \
	bigcircle_put_dot(bigcircle, 0xC0, 0xC2, V_WHITE); \
	\
	bigcircle.angle += 0x02; \
}

// All of the summon animation macros below are forced to be used inside an
// `if` statement, returning a non-zero value when the flash animation is done.
// MODDERS: Just turn them into regular functions.

// Renders a frame of the summon animation.
#define bigcircle_summon(bigcircle, start_frame, q4_offset_end) \
	boss_phase_frame == start_frame) { \
		mdrv2_se_play(8); \
	} \
	bigcircle_summon_update_and_render(bigcircle, q4_offset_end); \
	if(bigcircle_summon_done(bigcircle) /* return value */

// Renders a frame of the summon and flash animation.
#define bigcircle_summon_and_flash(bigcircle, start_frame, q4_offset_end) \
	bigcircle_is_summon_frame(start_frame) && (bigcircle.frames == 0)) { \
		if(bigcircle_summon(bigcircle, start_frame, q4_offset_end)) { \
			bigcircle_sloppy_unput(bigcircle);	/* ZUN bloat */ \
			\
			/* Also looks redundant, but we might have unblitted parts of */ \
			/* the circle during the summon animation… */ \
			bigcircle_put(bigcircle, V_WHITE); \
			\
			bigcircle.frames = 1; \
			ent_unput_and_put_both(ent_still_or_wave, 1, C_STILL); \
		} \
	} else if((bigcircle.frames != 0) && (bigcircle.frames < 40)) { \
		bigcircle.frames++; \
		if((bigcircle.frames % 8) == 0) { \
			bigcircle_sloppy_unput(bigcircle);	/* ZUN bloat */ \
			bigcircle_put(bigcircle, COL_FX); \
		} else if((bigcircle.frames % 8) == 4) { \
			bigcircle_sloppy_unput(bigcircle);	/* ZUN bloat */ \
			bigcircle_put(bigcircle, V_WHITE); \
		} \
	} else if(bigcircle.frames != 0 /* return value */

// Circle around the Star of David
struct StarCircle {
	unsigned char angle;
	int frames;

	screen_x_t center_x(void) { return form_center_x(F_GIRL); }
	screen_y_t center_y(void) { return form_center_y(F_GIRL); }
};
// -----------------

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;
// ----

#define bg_func_init(left, top, unnecessary) { \
	ent_attack.pos_cur_set_to(ent_still_or_wave); \
	if(unnecessary == 1) { \
		left = ent_still_or_wave.cur_left; \
		top = ent_still_or_wave.cur_top; \
	} else if(unnecessary == 2) { \
		left = ent_attack.cur_left; \
		top = ent_attack.cur_top; \
	} \
}

void girl_bg_snap(unnecessary_1_or_2_t unnecessary)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left;
	screen_y_t top;
	int image;

	bg_func_init(left, top, unnecessary);

	image = 0;
	ptn_snap_rect_from_1_8(
		left, top, GIRL_W, GIRL_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
	);
}

void girl_bg_put(unnecessary_1_or_2_t unnecessary)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left;
	screen_y_t top;
	int image = 0;

	bg_func_init(left, top, unnecessary);
	ptn_put_rect_noalpha_8(
		left, top, GIRL_W, GIRL_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
	);
}

// Patterns
// --------
static const int CHOOSE_NEW = 0;

enum elis_starpattern_ret_t {
	SP_STAR_OF_DAVID = false,
	SP_PATTERN = true,

	_elis_starpattern_ret_t_FORCE_INT16 = 0x7FFF,
};

enum elis_phase_5_subphase_t {
	P5_PATTERN = false,
	P5_TRANSFORM = true,

	_elis_phase_5_subphase_t_FORCE_INT16 = 0x7FFF,
};

typedef int (*elis_phase_func_t)(int id);

// Returns `CHOOSE_NEW` if done, or the pattern ID within the phase if still
// ongoing.
typedef int (*elis_phase_1_3_pattern_func_t)(void);

// Returns `SP_STAR_OF_DAVID` if done, or `SP_PATTERN` if still ongoing.
typedef elis_starpattern_ret_t (*elis_starpattern_func_t)(void);

static union {
	int angle_range; // ACTUAL TYPE: unsigned char
	int count;
	pellet_group_t group;
	int interval;
	int ring;
	int speed_multiplied_by_8;
	pixel_t speed;
} pattern_state;
// --------

void elis_load(void)
{
	pellet_interlace = true;
	elis_ent_load();
	grc_load(GRC_SLOT_BOSS_1, "boss5_gr.grc");
	ptn_new(PTN_SLOT_BG_ENT, ((GIRL_W / PTN_W) * (GIRL_H / PTN_H)));
	Missiles.load(PTN_SLOT_MISSILE);
	boss_palette_snap();
	void elis_setup(void);
	elis_setup();
}

void elis_setup(void)
{
	svc2 col;
	int comp;

	ent_still_or_wave.pos_set(BASE_LEFT, BASE_TOP);

	// ZUN bloat: These two are redundant, as they're synced with
	// [ent_still_or_wave] before first use anyway.
	ent_attack.pos_set(BASE_LEFT, BASE_TOP);
	ent_bat.pos_set(BASE_LEFT, BASE_TOP);

	ent_still_or_wave.hitbox_orb_set(
		((GIRL_W / 8) * 1), -4,
		((GIRL_W / 8) * 7), ((GIRL_H / 6) * 5)
	);
	// Note that [ent_attack] doesn't receive a hitbox!
	ent_bat.hitbox_orb_set(-8, -8, (BAT_W + 8), (BAT_H + 8));

	boss_phase = 0;
	boss_phase_frame = 0;

	// Same HP and phase settings as Kikuri.
	boss_hp = HP_TOTAL;
	hud_hp_first_white = HP_PHASE_1_END;
	hud_hp_first_redwhite = HP_PHASE_3_END;

	random_seed = frame_rand;
	palette_set_grayscale(boss_post_defeat_palette, 0x0, col, comp);
}

void elis_free(void)
{
	elis_ent_free();
	grc_free(GRC_SLOT_BOSS_1);
	ptn_free(PTN_SLOT_BG_ENT);
	ptn_free(PTN_SLOT_MISSILE);
}

bool16 wave_teleport(screen_x_t target_left, screen_y_t target_top)
{
	ent_attack.pos_cur_set_to(ent_still_or_wave);

	// Wave sprite
	if(boss_phase_frame == 20) {
		page_access(1);
		girl_bg_put(1);
		page_access(0);
		ent_still_or_wave.unlock_put_image_lock_8(C_WAVE_1);
		ent_still_or_wave.hitbox_orb_inactive = true;
	} else if(boss_phase_frame == 28) {
		girl_bg_put(1);
		ent_still_or_wave.unlock_put_image_lock_8(C_WAVE_2);
		ent_still_or_wave.hitbox_orb_inactive = true;
	} else if(boss_phase_frame == 36) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		girl_bg_put(1);
		ent_still_or_wave.unlock_put_image_lock_8(C_WAVE_3);
	} else if(boss_phase_frame == 44) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		egc_copy_rect_1_to_0_16(
			ent_still_or_wave.cur_left,
			ent_still_or_wave.cur_top,
			GIRL_W,
			GIRL_H
		);
	} else if(boss_phase_frame == 52) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		ent_still_or_wave.pos_cur_set(target_left, target_top);
		girl_bg_snap(1);
		girl_bg_put(1); // unnecessary
		ent_still_or_wave.unlock_put_image_lock_8(C_WAVE_3);
	} else if(boss_phase_frame == 60) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		girl_bg_put(1);
		ent_still_or_wave.unlock_put_image_lock_8(C_WAVE_2);
	} else if(boss_phase_frame == 68) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		girl_bg_put(1);
		ent_still_or_wave.unlock_put_image_lock_8(C_WAVE_1);
	} else if(boss_phase_frame == 76) {
		ent_still_or_wave.hitbox_orb_inactive = false;
		page_access(1);
		ent_still_or_wave.unlock_put_image_lock_8(C_STILL);
		page_access(0);
		ent_still_or_wave.unlock_put_image_lock_8(C_STILL);
	} else if(boss_phase_frame > 80) {
		boss_phase_frame = 0;
		return true;
	}

	// Stars
	if((boss_phase_frame % 4) != 0) {
		return false;
	}

	static EntitiesTopleft<5> stars;

	for(int i = 0; i < stars.count(); i++) {
		if(boss_phase_frame > 4) {
			egc_copy_rect_1_to_0_16_word_w(stars.left[i], stars.top[i], 8, 8);
		}
		if((boss_phase_frame < 40) || (boss_phase_frame > 52)) {
			stars.left[i] = surround_random_left(ent_still_or_wave);
			stars.top[i] = surround_random_top(ent_still_or_wave);
		} else {
			stars.left[i] = (stars.left[i] + (
				(surround_random_left(ent_still_or_wave) - stars.left[i]) / 3
			));
			stars.top[i] = (stars.top[i] + (
				(surround_random_top(ent_still_or_wave) - stars.top[i]) / 3
			));
		}
		if(boss_phase_frame < 68) {
			shape8x8_star_put(stars.left[i], stars.top[i], 2);
		}
	}
	return false;
}

#include "th01/main/select_r.cpp"

int pattern_11_lasers_across(void)
{
	enum {
		INTERVAL = 10,
	};

	#define circle_center_x	form_center_x(F_GIRL)
	#define circle_center_y	(ent_still_or_wave.cur_top + (GIRL_H / 3))

	static pixel_t circle_radius;
	static bool16 direction; // ACTUAL TYPE: x_direction_t
	double target_left;
	double target_y;

	if(boss_phase_frame == 50) {
		direction = (rand() % 2);
		ent_unput_and_put_both(ent_still_or_wave, 1, C_HAND, false);
		select_laser_speed_for_rank(pattern_state.speed_multiplied_by_8,
			6.25f, 6.875f, 7.5f, 8.125f
		);
	} else if(boss_phase_frame == 60) {
		shape_circle_put(
			circle_center_x, circle_center_y, (GIRL_W / 4), COL_FX, 0x02
		);
		circle_radius = (GIRL_W / 4);
	} else if(
		(boss_phase_frame < 120) &&
		(boss_phase_frame > 60) &&
		((boss_phase_frame % 2) == 0)
	) {
		shape_circle_sloppy_unput(
			circle_center_x, circle_center_y, circle_radius, 0x02
		);
		circle_radius += 8;
		shape_circle_put(
			circle_center_x, circle_center_y, circle_radius, COL_FX, (
				(boss_phase_frame < 100) ? 0x02 :
				(boss_phase_frame < 110) ? 0x08 :
				0x20
			)
		);
	} else if(boss_phase_frame == 120) {
		shape_circle_sloppy_unput(
			circle_center_x, circle_center_y, circle_radius, 0x20
		);
	} else if(boss_phase_frame == 150) {
		ent_unput_and_put_both(ent_still_or_wave, 1, C_STILL, false);
	}

	if((boss_phase_frame >= 70) && ((boss_phase_frame % INTERVAL) == 0)) {
		if(direction == X_RIGHT) {
			target_left = (PLAYFIELD_LEFT +
				(((boss_phase_frame - 70) / INTERVAL) * (PLAYFIELD_W / 10))
			);
		} else {
			target_left = (PLAYFIELD_RIGHT -
				(((boss_phase_frame - 70) / INTERVAL) * (PLAYFIELD_W / 10))
			);
		}
		target_y = PLAYFIELD_BOTTOM;
		shootout_laser_safe(boss_phase_frame / INTERVAL).spawn(
			girl_lefteye_x(),
			girl_lefteye_y(),
			target_left,
			target_y,
			pattern_state.speed_multiplied_by_8,
			V_WHITE,
			25,
			4
		);
		mdrv2_se_play(6);

		// <= instead of < is why this pattern actually fires 11 lasers rather
		// than the 10 you might guess from looking at the target calculation
		// above.
		if(
			((direction == X_RIGHT) && (target_left >= PLAYFIELD_RIGHT)) ||
			((direction == X_LEFT) && (target_left <= PLAYFIELD_LEFT))
		) {
			boss_phase_frame = 0;
			return CHOOSE_NEW;
		}
	}
	return 1;

	#undef circle_center_y
	#undef circle_center_x
}

int pattern_random_downwards_missiles(void)
{
	static EntitiesTopleft<5> rifts;
	int cel; // ACTUAL TYPE: elis_grc_cel_t
	pixel_t velocity_x;
	pixel_t velocity_y;
	unsigned char angle;

	if(boss_phase_frame == 50) {
		ent_unput_and_put_both(ent_still_or_wave, 1, C_HAND, false);
		select_for_rank(pattern_state.angle_range, 0x0F, 0x15, 0x19, 0x1D);
	}

	// That's quite the brave placement for this branch...
	if((boss_phase_frame > 60) && ((boss_phase_frame % 3) == 0)) {
		int i = (rand() % rifts.count());
		angle = (
			(rand() % pattern_state.angle_range) -
			((pattern_state.angle_range - 0x01) / 2) +
			0x40
		);
		vector2(velocity_x, velocity_y, 7, angle);
		Missiles.add(rifts.left[i], rifts.top[i], velocity_x, velocity_y);
	}

	rifts_update_and_render(rifts, ent_still_or_wave, 60, 160, COL_FX, cel);

	if(boss_phase_frame > 170) {
		boss_phase_frame = 0;
		return CHOOSE_NEW;
	}
	return 2;
}

int pattern_pellets_along_circle(void)
{
	static StarCircle circle;
	screen_x_t left;
	screen_y_t top;

	if(boss_phase_frame < 10) {
		circle.frames = 0;
	}
	if(boss_phase_frame == 50) {
		ent_unput_and_put_both(ent_still_or_wave, 1, C_HAND, false);
		circle.angle = 0x00;
		select_for_rank(reinterpret_cast<int &>(pattern_state.group),
			PG_1_AIMED,
			PG_1_RANDOM_NARROW_AIMED,
			PG_3_SPREAD_WIDE_AIMED,
			// This will spawn (32 * 5) = 160 pellets, which is 60 more than
			// the original PELLET_COUNT. As a result, Elis will only ever fire
			// up to 20 of these spreads on Lunatic, rather than the coded 32.
			PG_5_SPREAD_NARROW_AIMED
		);
	}

	// ZUN quirk: Adding a `double` value < 1.0 to an integer is still a no-op.
	// That leads to the start and end angle for quadrant IV being identical,
	// and nothing being drawn there as a result. Hard to call it a bug though,
	// since this is the only function where this happens. But if it this was
	// intended after all, why not just remove the call for quadrant IV?!
	if(bigcircle_summon_and_flash(circle, 60, 0.05)) {
		bigcircle_sloppy_unput(circle);
		circle.angle = 0x00;
		for(int i = 0; i < 32; i++) {
			// lefteye?!
			left = polar_x(girl_lefteye_x(), BIGCIRCLE_RADIUS, circle.angle);

			top = polar_y(
				form_center_y(F_GIRL), BIGCIRCLE_RADIUS, circle.angle
			);
			Pellets.add_group(left, top, pattern_state.group, to_sp(0.25f));
			circle.angle += (0x100 / 32);
		}
		boss_phase_frame = 0;
		circle.frames = 0;
		return CHOOSE_NEW;
	}
	return 3;
}

// Draws a line from [angle_1] to [angle_2] on the star circle around Elis.
void near starcircle_line_put(
	unsigned char angle_1, unsigned char angle_2, vc_t col
)
{
	screen_x_t p1_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_y_t p1_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_x_t p2_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	screen_y_t p2_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	graph_r_line(p1_x, p1_y, p2_x, p2_y, col);
}

void near starcircle_line_unput(
	unsigned char angle_1, unsigned char angle_2
)
{
	screen_x_t p1_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_y_t p1_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_x_t p2_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	screen_y_t p2_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	graph_r_line_unput(p1_x, p1_y, p2_x, p2_y);
}

int phase_1(int id)
{
	switch(id) {
	case CHOOSE_NEW:
		// Note that this includes `CHOOSE_NEW`. Due to how phase_frame_common()
		// switches between patterns and teleporting, this adds a 25% chance of
		// Elis skipping an attack cycle and teleporting again.
		return (rand() % 4);
	case 1: return pattern_11_lasers_across();
	case 2: return pattern_random_downwards_missiles();
	case 3: return pattern_pellets_along_circle();
	}
	return CHOOSE_NEW;
}

void near star_of_david_put(vc_t col)
{
	starcircle_line_put(-0x40, +0x16, col);
	starcircle_line_put(-0x40, +0x6A, col);
	starcircle_line_put(+0x16, +0x6A, col);
	starcircle_line_put(+0x40, -0x6A, col);
	starcircle_line_put(+0x40, -0x16, col);
	starcircle_line_put(-0x6A, -0x16, col);
}

inline void star_of_david_unput(void) {
	starcircle_line_unput(-0x40, +0x16);
	starcircle_line_unput(-0x40, +0x6A);
	starcircle_line_unput(+0x16, +0x6A);
	starcircle_line_unput(+0x40, -0x6A);
	starcircle_line_unput(+0x40, -0x16);
	starcircle_line_unput(-0x6A, -0x16);
}

// Renders a frame of the Star of David summon/flash animation in front of a
// danmaku pattern.
elis_starpattern_ret_t near star_of_david(void)
{
	static StarCircle circle;

	if(boss_phase_frame < 5) {
		circle.frames = 0;
		circle.angle = 0x00;
	}

	if(boss_phase_frame < 10) {
		return SP_STAR_OF_DAVID;
	}
	if(boss_phase_frame == 10) {
		ent_unput_and_put_both(ent_attack, 2, C_PREPARE);
		circle.angle = 0x00;
		circle.frames = 0;
	}
	if(bigcircle_is_summon_frame(10) && (circle.frames == 0)) {
		if(bigcircle_summon(circle, 10, 0x02)) {
			circle.frames = 1;
			bigcircle_sloppy_unput(circle);	// ZUN bloat: Position unchanged
			bigcircle_put(circle, V_WHITE);
		}
	} else if(bigcircle_summon_done(circle)) {
		circle.frames++;
		if(circle.frames == 10) {
			star_of_david_put(V_WHITE);
		}
		if((circle.frames > 20) && ((circle.frames % 4) == 0)) {
			star_of_david_put(COL_FX);
			bigcircle_put(circle, COL_FX);
		} else if((circle.frames > 20) && ((circle.frames % 4) == 2)) {
			star_of_david_put(V_WHITE);
			bigcircle_put(circle, V_WHITE);
		}
		if(circle.frames > 60) {
			star_of_david_unput();
			bigcircle_sloppy_unput(circle);
			boss_phase_frame = 0;
			circle.angle = 0x00;
			circle.frames = 0;
			return SP_PATTERN;
		}
	}
	return SP_STAR_OF_DAVID;
}

int pattern_curved_5_stack_rings(void)
{
	#define fire_ring(i, angle_offset, speed) { \
		for(int i = 0; i < pattern_state.ring; i++) { \
			Pellets.add_single( \
				(form_center_x(F_GIRL) - (PELLET_W / 2)), \
				(form_center_y(F_GIRL) - (PELLET_H / 2)), \
				(((0x100 / pattern_state.ring) * i) + angle_offset), \
				to_sp(speed) \
			); \
		} \
	}

	ent_attack_render();
	if(boss_phase_frame == 10) {
		select_for_rank(pattern_state.ring, 14, 16, 18, 20);
		fire_ring(i, 0x00, 3.0f);
	} else if(boss_phase_frame == 16) {
		fire_ring(i, 0x02, 3.375f);
	} else if(boss_phase_frame == 24) {
		fire_ring(i, 0x04, 4.0f);
	} else if(boss_phase_frame == 32) {
		fire_ring(i, 0x06, 4.5f);
	} else if(boss_phase_frame == 40) {
		fire_ring(i, 0x08, 5.0f);
	} else if(boss_phase_frame > 60) {
		boss_phase_frame = 0;

		// ZUN bug: A completely unnecessary unblitting call that doesn't even
		// switch back to VRAM page 0. At first, this might look like it has no
		// effect since Elis runs a wave_teleport() animation afterwards. But
		// if any player shot, bomb, or Orb sprites overlap Elis between the
		// end of this pattern and the start of the teleport animation, their
		// corresponding unblitting calls will rip holes into the Elis sprite.
		page_access(1);
		girl_bg_put(2);

		return CHOOSE_NEW;
	}
	return 1;

	#undef fire_ring
}

int pattern_clusters_from_spheres(void)
{
	enum {
		INTERVAL = 10,
		SPHERE_COUNT = 10,
		SPHERE_DURATION = (SPHERE_COUNT * INTERVAL),

		// Spheres spawned, start firing
		KEYFRAME_FIRE = SPHERE_DURATION,

		// Spheres start being removed
		KEYFRAME_REMOVE = (KEYFRAME_FIRE + 30),

		// All spheres fired
		KEYFRAME_FIRE_DONE = (KEYFRAME_FIRE + SPHERE_DURATION),

		// All spheres removed
		KEYFRAME_REMOVE_DONE = (KEYFRAME_REMOVE + SPHERE_DURATION),

		KEYFRAME_DONE = (KEYFRAME_REMOVE_DONE + 20),
	};

	struct Spheres : public EntitiesTopleft<SPHERE_COUNT> {
		static pixel_t column_w(screen_x_t edge) {
			return ((edge - ent_still_or_wave.cur_left) / count());
		}

		static pixel_t row_h(screen_y_t edge) {
			return (
				(((rand() % edge) + edge) - ent_still_or_wave.cur_top) / count()
			);
		}
	};

	static Spheres spheres;
	int i;

	ent_attack_render();
	if(
		(boss_phase_frame <= KEYFRAME_FIRE) &&
		((boss_phase_frame % INTERVAL) == 0)
	) {
		#define sphere_i (boss_phase_frame / INTERVAL)

		if(ent_still_or_wave.cur_left < BASE_LEFT) {
			spheres.left[sphere_i - 1] = (
				(sphere_i * spheres.column_w(PLAYFIELD_RIGHT - SPHERE_W)) +
				(form_center_x(F_GIRL) - (SPHERE_W / 2))
			);
		} else {
			spheres.left[sphere_i - 1] = (
				(sphere_i * spheres.column_w(PLAYFIELD_LEFT)) +
				(form_center_x(F_GIRL) - (SPHERE_W / 2))
			);
		}
		spheres.top[sphere_i - 1] = (
			(sphere_i * spheres.row_h(playfield_fraction_y(25 / 42.0f))) +
			(form_center_y(F_GIRL) - (SPHERE_H / 2))
		);

		// We might have unblitted some of the earlier sprites during the
		// previous interval...
		for(i = 0; i < sphere_i; i++) {
			elis_grc_put(spheres, i, C_SPHERE_LARGE, COL_FX);
		}

		#undef sphere_i
	} else if(
		(boss_phase_frame > KEYFRAME_FIRE) &&
		(boss_phase_frame <= KEYFRAME_REMOVE_DONE) &&
		((boss_phase_frame % INTERVAL) == 0)
	) {
		if(boss_phase_frame <= KEYFRAME_FIRE_DONE) {
			#define sphere_i ((boss_phase_frame - KEYFRAME_FIRE) / INTERVAL)

			mdrv2_se_play(7);

			// ZUN bug: This will only really be visible in the bad case where
			// the sphere has been accidentally unblitted before. In the usual
			// case, the rift sprite will be blitted *on top* of the circle
			// sprite at the same position, which only adds a total of 5 new
			// blue pixels outside of the circle.
			elis_grc_put(spheres, (sphere_i - 1), C_RIFT, COL_FX);

			for(i = sphere_i; i < SPHERE_COUNT; i++) {
				elis_grc_put(spheres, i, C_SPHERE_LARGE, COL_FX);
			}

			select_for_rank(pattern_state.count, 5, 7, 9, 13);
			for(i = 0; i < pattern_state.count; i++) {
				subpixel_t speed;
				unsigned char angle;

				angle = (rand() & 0x7F);
				speed = ((rand() + to_sp(1.5f)) & (to_sp(4.0f) - 1));
				Pellets.add_single(
					spheres.left[sphere_i - 1],
					spheres.top[sphere_i - 1],
					angle,
					speed
				);
			}

			#undef sphere_i
		}
		if(boss_phase_frame > KEYFRAME_REMOVE) {
			#define sphere_i ((boss_phase_frame - KEYFRAME_REMOVE) / INTERVAL)
			elis_grc_sloppy_unput(spheres, (sphere_i - 1));
			#undef sphere_i
		}
	} else if(boss_phase_frame > KEYFRAME_DONE) {
		boss_phase_frame = 0;
		return CHOOSE_NEW;
	}
	return 2;
}

int pattern_random_from_rifts(void)
{
	enum {
		KEYFRAME_0 = 60, 	// Firing down
		KEYFRAME_1 = 120,	// Firing in all directions
		KEYFRAME_2 = 200,	// No more firing
		KEYFRAME_3 = 220,	// Pattern done
	};

	static EntitiesTopleft<5> rifts;
	int cel; // ACTUAL TYPE: elis_grc_cel_t
	unsigned char angle;

	ent_attack_render();
	if(boss_phase_frame == (KEYFRAME_0 / 2)) {
		select_for_rank(pattern_state.interval, 6, 3, 2, 2);
	}

	// That's quite the brave placement for this branch...
	if(
		(boss_phase_frame > KEYFRAME_0) &&
		((boss_phase_frame % pattern_state.interval) == 0) &&
		(boss_phase_frame < KEYFRAME_1)
	) {
		int i = (rand() % rifts.count());
		angle = ((rand() % 0x15) + 0x36);
		Pellets.add_single(rifts.left[i], rifts.top[i], angle, to_sp(6.0f));
	} else if(
		(boss_phase_frame >= KEYFRAME_1) && (boss_phase_frame < KEYFRAME_2)
	) {
		int i = (rand() % rifts.count());
		angle = ((rand() % 0x15) + 0x36);
		unsigned char angle_offset = ((rand() & 1)
			? +(boss_phase_frame - KEYFRAME_1)
			: -(boss_phase_frame - KEYFRAME_1)
		);
		angle *= (angle_offset / 2);
		Pellets.add_single(rifts.left[i], rifts.top[i], angle, to_sp(6.0f));
	}

	rifts_update_and_render(
		rifts, ent_still_or_wave, KEYFRAME_0, KEYFRAME_2, COL_FX, cel
	);

	if(boss_phase_frame > KEYFRAME_3) {
		boss_phase_frame = 0;
		return CHOOSE_NEW;
	}
	return 3;
}

int phase_3(int id)
{
	#define star_of_david_then(pattern_cur, id, func) { \
		if(pattern_cur == 0) { \
			pattern_cur = star_of_david() /* != SP_STAR_OF_DAVID */; \
			return id; \
		} \
		return (pattern_cur = func()); \
	}

	static int pattern_cur = CHOOSE_NEW;

	if(id == 99) {
		pattern_cur = CHOOSE_NEW;
		return CHOOSE_NEW;
	}

	switch(id) {
	case CHOOSE_NEW:
		// Note that this includes `CHOOSE_NEW`. Due to how phase_frame_common()
		// switches between patterns and teleporting, this adds a 25% chance of
		// Elis skipping an attack cycle and teleporting again.
		return (rand() % 4);
	case 1: /* return */ star_of_david_then(pattern_cur, 1,
		pattern_curved_5_stack_rings
	);
	case 2: /* return */ star_of_david_then(pattern_cur, 2,
		pattern_clusters_from_spheres
	);
	case 3: /* return */ star_of_david_then(pattern_cur, 3,
		pattern_random_from_rifts
	);
	}
	return CHOOSE_NEW;

	#undef star_of_david_then
}

enum {
	TRANSFORM_START_FRAME = 20,
	TRANSFORM_END_FRAME = 100,
};

#define transform_shake(start_frame) { \
	if((boss_phase_frame >= start_frame) && ((boss_phase_frame % 2) == 0) ) { \
		z_vsync_wait_and_scrollup(RES_Y - ((boss_phase_frame % 4) * 2)); \
	} \
}

elis_form_t transform_girl_to_bat(void)
{
	static EntitiesTopleft<5> rifts;
	int cel;  // ACTUAL TYPE: elis_grc_cel_t

	if(boss_phase_frame == TRANSFORM_START_FRAME) {
		ent_unput_and_put_both(ent_attack, 2, C_PREPARE);
	}

	rifts_update_and_render(
		rifts,
		ent_still_or_wave,
		TRANSFORM_START_FRAME,
		TRANSFORM_END_FRAME,
		(rand() % COLOR_COUNT),
		cel
	);
	transform_shake(TRANSFORM_START_FRAME);

	if(boss_phase_frame > TRANSFORM_END_FRAME) {
		ent_bat.pos_cur_set_to(ent_still_or_wave);

		// ZUN bug: No bat sprite rendered this frame? Wouldn't have happened
		// if the original code consistently used the ent_unput_and_put_both()
		// helper function we've added. :P
		ent_bat.set_image(C_BAT);
		page_access(1);	girl_bg_put(2);
		page_access(0);	girl_bg_put(2);

		z_vsync_wait_and_scrollup(RES_Y);
		boss_phase_frame = 0;
		return F_BAT;
	}
	return F_GIRL;
}

elis_form_t transform_bat_to_girl(void)
{
	static EntitiesTopleft<5> rifts;
	int cel;  // ACTUAL TYPE: elis_grc_cel_t
	screen_x_t left;
	screen_y_t top;

	rifts_update_and_render(
		rifts,
		ent_bat,
		TRANSFORM_START_FRAME,
		TRANSFORM_END_FRAME,
		(rand() % COLOR_COUNT),
		cel
	);
	transform_shake(TRANSFORM_START_FRAME);

	if(boss_phase_frame > TRANSFORM_END_FRAME) {
		// Doubly sloppy! CBossEntity has a function for that!
		egc_copy_rect_1_to_0_16(
			ent_bat.cur_left, ent_bat.cur_top, BAT_W, BAT_H
		);

		// Should ideally be a branch in ent_sync(), but that would make the
		// function too complex to perfectly inline. It's only used here,
		// anyway.
		left = (ent_bat.cur_center_x() - (GIRL_W / 2));
		top  = (ent_bat.cur_center_y() - (GIRL_H / 2));
		if(left < PLAYFIELD_LEFT) {
			left = PLAYFIELD_LEFT;
		} else if(left > (PLAYFIELD_RIGHT - GIRL_W)) {
			left = (PLAYFIELD_RIGHT - GIRL_W);
		}
		if(top < PLAYFIELD_TOP) {
			top = PLAYFIELD_TOP;
		}
		ent_still_or_wave.pos_cur_set(left, top);

		girl_bg_snap(1);
		ent_unput_and_put_both(ent_attack, 2, C_ATTACK_1);
		z_vsync_wait_and_scrollup(RES_Y);
		boss_phase_frame = 0;
		return F_GIRL;
	}
	return F_BAT;
}

// Like the flystep functions in later games, just without the "step" part, and
// with explicit pattern/transformation semantics.
elis_phase_5_subphase_t bat_fly_random(pixel_t &velocity_x, pixel_t &velocity_y)
{
	enum {
		SPEED = 2,
	};

	static screen_x_t target_left; // should be local
	static screen_y_t target_top; // should be local
	static int frames_until_target;

	if(boss_phase_frame < BAT_SPEED_DIVISOR) {
		velocity_x = 0;
		velocity_y = 0;
		return P5_PATTERN;
	}
	if(boss_phase_frame == BAT_SPEED_DIVISOR) {
		do {
			target_left = elis_playfield_random_left();
			target_top = (elis_playfield_random_top() + ((GIRL_H - BAT_H) / 2));
		} while(
			(abs(ent_bat.cur_left - target_left) < (PLAYFIELD_W / 5)) &&
			(abs(ent_bat.cur_top - target_top) < ((PLAYFIELD_H * 4) / 21))
		);
		vector2_between(
			ent_bat.cur_left,
			ent_bat.cur_top,
			target_left,
			target_top,
			velocity_x,
			velocity_y,
			SPEED
		);
		frames_until_target = (abs(target_left - ent_bat.cur_left) / SPEED);
	}

	// What is something like "gravity" doing in a bat movement function?
	// Quite the interesting interpretation as well, even if it wasn't always
	// zero. MODDERS: Remove.
	velocity_y += (((rand() % 5) - 2) / 10);

	if((boss_phase_frame / BAT_SPEED_DIVISOR) >= frames_until_target) {
		velocity_x = 0;
		velocity_y = 0;
		boss_phase_frame = 0;
		return P5_TRANSFORM;
	}
	return P5_PATTERN;
}

void pattern_bat_slow_spreads(void)
{
	if((boss_phase_frame % 16) == 0) {
		pellet_group_t group;
		select_for_rank(reinterpret_cast<int &>(group),
			PG_3_SPREAD_WIDE_AIMED,
			PG_5_SPREAD_WIDE_AIMED,
			PG_5_SPREAD_NARROW_AIMED,

			// Not aimed on Lunatic? Probably the easiest version then, since
			// pellets are always fired down in this case.
			// (Compare pattern_souls_spreads() in the Kikuri fight.)
			PG_5_SPREAD_NARROW
		);
		form_fire_group(F_BAT, group, 3.5f);
	}
}

void pattern_bat_alternating_narrow_and_wide_2_spreads(void)
{
	if((boss_phase_frame % 4) == 0) {
		if(rand() & 1) {
			form_fire_group(F_BAT, PG_2_SPREAD_NARROW_AIMED, 5.5f);
		} else {
			form_fire_group(F_BAT, PG_2_SPREAD_WIDE_AIMED, 5.5f);
		}
	}
}

void pattern_bat_alternating_2_and_3_spreads(void)
{
	if(((boss_phase_frame % 50) < 10) && ((boss_phase_frame % 4) == 0)) {
		form_fire_group(F_BAT, PG_2_SPREAD_NARROW_AIMED, 5.3125f);
	}
	if(
		((boss_phase_frame % 50) >= 25) &&
		((boss_phase_frame % 50) < 35) &&
		((boss_phase_frame % 4) == 0)
	) {
		form_fire_group(F_BAT, PG_3_SPREAD_NARROW_AIMED, 5.3125f);
	}
}

void pattern_bat_random_rain(void)
{
	if((boss_phase_frame % 4) == 0) {
		pellets_add_single_rain(
			(form_center_x(F_BAT) - (PELLET_W / 2)),
			(form_center_y(F_BAT) - (PELLET_H / 2)),
			rand(),
			0.125f
		);
	}
}

elis_starpattern_ret_t pattern_three_symmetric_4_stacks_then_symmetric_arc(void)
{
	#define fire_symmetric(angle_right, speed) { \
		Pellets.add_single( \
			(form_center_x(F_GIRL) - (PELLET_W / 2) - 4), \
			(form_center_y(F_GIRL) - (PELLET_H / 2) - 4), \
			(0x80 - angle_right), \
			TO_SP(speed) \
		); \
		Pellets.add_single( \
			(form_center_x(F_GIRL) - (PELLET_W / 2) + 4), \
			(form_center_y(F_GIRL) - (PELLET_H / 2) - 4), \
			angle_right, \
			TO_SP(speed) \
		); \
	}

	ent_attack_render();
	if(boss_phase_frame == 50) {
		select_for_rank(pattern_state.speed, 2, 3, 3, 4);
		for(int i = 0; i < 4; i++) {
			fire_symmetric(0x40, (i + pattern_state.speed));
		}
	} else if(boss_phase_frame == 60) {
		for(int i = 0; i < 4; i++) {
			fire_symmetric(0x30, (i + pattern_state.speed));
		}
		mdrv2_se_play(7);
	} else if(boss_phase_frame == 70) {
		for(int i = 0; i < 4; i++) {
			fire_symmetric(0x18, (i + pattern_state.speed));
		}
		mdrv2_se_play(7);
	} else if(boss_phase_frame == 80) {
		unsigned char angle = 0x00;
		for(int i = 0; i < 10; i++) {
			fire_symmetric(angle, (2 + pattern_state.speed));
			angle += 0x06;
		}
		mdrv2_se_play(7);
	} else if(boss_phase_frame >= 120) {
		boss_phase_frame = 0;
		return SP_STAR_OF_DAVID;
	}
	return SP_PATTERN;

	#undef fire_symmetric
}

elis_starpattern_ret_t pattern_safety_circle_and_rain_from_top(void)
{
	enum {
		CIRCLE_DURATION = 200,

		// A bit unfair, since the kill zone already starts in the transparent
		// parts of the non-moving player sprite.
		SAFETY_OFFSET_LEFT = BIGCIRCLE_RADIUS,

		// Slightly less unfair.
		SAFETY_OFFSET_RIGHT = (
			BIGCIRCLE_RADIUS - (PLAYER_W / 2) - (PLAYER_W / 4)
		),
	};

	static struct {
		int frames;
		screen_x_t target_left;
		unsigned char angle;

		screen_x_t center_x(void) { return (target_left + (PLAYER_W / 2)); };
		screen_y_t center_y(void) { return player_center_y(); };
	} circle;

	if(boss_phase_frame < 10) {
		circle.frames = 0;
	}

	ent_attack_render();

	if(boss_phase_frame < 60) {
		return SP_PATTERN;
	}
	if(boss_phase_frame == 60) {
		select_for_rank(pattern_state.interval, 4, 2, 2, 2);
		circle.angle = 0x00;
	}
	if(bigcircle_is_summon_frame(60) && (circle.frames == 0)) {
		if(boss_phase_frame == 60) {
			mdrv2_se_play(8);
			circle.target_left = player_left;
		}
		bigcircle_summon_update_and_render(circle, 0x02);
		if(bigcircle_summon_done(circle)) {
			bigcircle_sloppy_unput(circle);	// ZUN bloat: Position unchanged
			bigcircle_put(circle, V_WHITE);

			circle.frames = 1;
			ent_unput_and_put_both(ent_still_or_wave, 1, C_STILL);
		}
	} else if((circle.frames != 0) && (circle.frames < CIRCLE_DURATION)) {
		circle.frames++;

		// We only blit the circle to VRAM page 0, so any unblitting call for
		// any overlapping sprite will "cut a hole" into the circle. So, um...
		// let's just re-blit it every 4 frames? :zunpet:
		if((circle.frames % 4) == 0) {
			bigcircle_sloppy_unput(circle); // ZUN bloat: Position unchanged
			bigcircle_put(circle, V_WHITE);
		}
		if(!player_invincible) {
			if(
				((circle.target_left + SAFETY_OFFSET_RIGHT) <= player_left) ||
				((circle.target_left - SAFETY_OFFSET_LEFT) >= player_left)
			) {
				delay(100);
				player_is_hit = true;
			}
		}
		if(player_is_hit == true) {
			circle.frames = CIRCLE_DURATION;
		}
		if((boss_phase_frame % pattern_state.interval) == 0) {
			Pellets.add_group(
				(PLAYFIELD_LEFT + (rand() % (PLAYFIELD_W - PELLET_W))),
				(PLAYFIELD_TOP),
				(rank == RANK_LUNATIC) ? PG_1_RANDOM_WIDE : PG_1,
				to_sp(4.5f)
			);
		}
		if(
			(circle.frames > (CIRCLE_DURATION - 20)) &&
			((circle.frames % 4) == 0)
		) {
			form_fire_group(F_GIRL, PG_1_AIMED, 4.5f);
		}
	} else if(circle.frames < CIRCLE_DURATION) {
		return SP_PATTERN;
	} else {
		if(circle.frames == CIRCLE_DURATION) {
			bigcircle_sloppy_unput(circle);
		}
		circle.frames++;
		if((circle.frames % 8) == 0) {
			// ZUN quirk: Spawning pellets relative to the top-left corner of
			// the bat sprite rather than the girl one. Since this pattern only
			// ever runs after a bat transformation, the position isn't
			// *completely* random at least, just calculated a lot lower than
			// you would expect.
			Pellets.add_group(
				(ent_bat.cur_left + (GIRL_W / 2) - (PELLET_W / 2)),
				(ent_bat.cur_top  + (GIRL_H / 2) - (PELLET_H / 2)),
				PG_1_AIMED,
				to_sp(4.5f)
			);
		}
		if(circle.frames > (CIRCLE_DURATION + 60)) {
			boss_phase_frame = 0;
			circle.frames = 0; // ZUN bloat: Gets reset at the beginning.
			circle.angle = 0x00; // ZUN bloat: Gets reset at the beginning.
			return SP_STAR_OF_DAVID;
		}
	}
	return SP_PATTERN;
}

elis_starpattern_ret_t pattern_aimed_5_spreads_and_lasers_followed_by_ring(void)
{
	enum {
		KEYFRAME_INIT = 50,
		KEYFRAME_START = 60,
	};

	static StarCircle circle;
	screen_x_t left;
	screen_x_t top;

	ent_attack_render();

	if(boss_phase_frame < KEYFRAME_INIT) {
		return SP_PATTERN;
	} else if(boss_phase_frame == KEYFRAME_INIT) {
		ent_unput_and_put_both(ent_still_or_wave, 1, C_HAND, false);
		circle.angle = 0x00;
		select_for_rank(pattern_state.interval, 40, 30, 20, 15);
	}
	if(bigcircle_summon_and_flash(circle, KEYFRAME_START, 0x02)) {
		bigcircle_sloppy_unput(circle);
		circle.angle = 0x00;

		// Depending on Elis' position, most of these pellets might be clipped.
		for(int i = 0; i < 32; i++) {
			left = polar_x(
				form_center_x(F_GIRL), BIGCIRCLE_RADIUS, circle.angle
			);

			// lefteye?!
			top = polar_y(girl_lefteye_y(), BIGCIRCLE_RADIUS, circle.angle);

			Pellets.add_group(left, top, PG_1, to_sp(4.0f));
			circle.angle += (0x100 / 32);
		}
		boss_phase_frame = 0;
		circle.frames = 0;
		return SP_STAR_OF_DAVID;
	}
	if((boss_phase_frame % pattern_state.interval) == 0) {
		Pellets.add_group(
			(girl_wing_left_center_x() - (PELLET_W / 2)),
			(girl_wing_center_y() - (PELLET_H / 2)),
			PG_5_SPREAD_WIDE_AIMED,
			to_sp(4.0f)
		);
		Pellets.add_group(
			(girl_wing_right_center_x() - (PELLET_W / 2)),
			(girl_wing_center_y() - (PELLET_H / 2)),
			PG_5_SPREAD_WIDE_AIMED,
			to_sp(4.0f)
		);
	}
	if((boss_phase_frame % (pattern_state.interval * 2)) == 0) {
		shootout_laser_safe(boss_phase_frame / 10).spawn(
			(form_center_x(F_GIRL) - (8 / 2)),
			girl_lefteye_y(),
			player_left,
			player_bottom(),
			(to_sp(6.25f) / 2),
			V_WHITE,
			20,
			8
		);
		mdrv2_se_play(6);
	}
	return SP_PATTERN;
}

elis_phase_5_subphase_t phase_5_girl(bool16 reset = false)
{
	#define star_of_david_then(in, pattern_cur, func) { \
		if(subphase == SP_STAR_OF_DAVID) { \
			subphase = star_of_david(); \
			return P5_PATTERN; \
		} \
		/* subphase == SP_PATTERN */ \
		subphase = func(); \
		if(subphase == SP_STAR_OF_DAVID) { \
			subphase = SP_STAR_OF_DAVID; \
			pattern_cur = CHOOSE_NEW; \
			return P5_TRANSFORM; \
		} \
		return P5_PATTERN; \
	}

	static int pattern_cur = CHOOSE_NEW;
	static elis_starpattern_ret_t subphase = SP_STAR_OF_DAVID;

	if(reset == true) {
		pattern_cur = CHOOSE_NEW;
		subphase = SP_STAR_OF_DAVID;
		return P5_PATTERN;
	}

	switch(pattern_cur) {
	case CHOOSE_NEW:
		// In contrast to phases 1 and 3, no pattern cycle is skipped here.
		pattern_cur = ((rand() % 3) + 1);
		break;
	case 1: /* return */ star_of_david_then(subphase, pattern_cur,
		pattern_three_symmetric_4_stacks_then_symmetric_arc
	);
	case 2: /* return */ star_of_david_then(subphase, pattern_cur,
		pattern_safety_circle_and_rain_from_top
	);
	case 3: /* return */ star_of_david_then(subphase, pattern_cur,
		pattern_aimed_5_spreads_and_lasers_followed_by_ring
	);
	}
	return P5_PATTERN;

	#undef star_of_david_then
}

void phase_5(
	elis_form_t& form,
	pixel_t& bat_velocity_x,
	pixel_t& bat_velocity_y,
	bool16 reset = false
)
{
	static elis_phase_5_subphase_t subphase = P5_PATTERN;
	static int pattern_bat_cur = CHOOSE_NEW;

	if(reset == true) {
		subphase = P5_PATTERN;
		pattern_bat_cur = CHOOSE_NEW;
		phase_5_girl(true);
		return;
	}
	if(form == F_BAT) {
		if(subphase == P5_PATTERN) {
			subphase = bat_fly_random(bat_velocity_x, bat_velocity_y);
			if(pattern_bat_cur == CHOOSE_NEW) {
				// In contrast to phases 1 and 3, no pattern cycle is skipped
				// here.
				pattern_bat_cur = ((rand() % 4) + 1);
			}
			switch(pattern_bat_cur) {
			case 1:
				pattern_bat_slow_spreads();
				break;
			case 2:
				pattern_bat_alternating_narrow_and_wide_2_spreads();
				break;
			case 3:
				pattern_bat_random_rain();
				break;
			case 4:
				pattern_bat_alternating_2_and_3_spreads();
				break;
			}
		} else if(subphase == P5_TRANSFORM) { // Thanks for making it explicit!
			form = transform_bat_to_girl();
			if(form == F_GIRL) {
				pattern_bat_cur = CHOOSE_NEW;
				subphase = P5_PATTERN;
			}
		}
	} else /* if(form == F_GIRL) */ {
		if(subphase == P5_PATTERN) {
			subphase = phase_5_girl();
		} else /* if(subphase == P5_TRANSFORM) */ {
			form = transform_girl_to_bat();
			if(form == F_BAT) {
				subphase = P5_PATTERN;
			}
		}
	}
}

void elis_main(void)
{
	static elis_form_t form = F_GIRL;
	static struct {
		int invincibility_frame;
		bool16 invincible;

		#define hit_update_and_render(form_inlined, flash_colors) { \
			boss_hit_update_and_render( \
				hit.invincibility_frame, \
				hit.invincible, \
				boss_hp, \
				flash_colors, \
				(sizeof(flash_colors) / sizeof(flash_colors[0])), \
				7000, \
				(form == F_GIRL) \
					? ent_still_or_wave.hittest_orb() \
					: ent_bat.hittest_orb(), \
				form_shot_hitbox_left(form_inlined), \
				form_shot_hitbox_top(form_inlined), \
				form_shot_hitbox_w(form_inlined), \
				form_shot_hitbox_h(form_inlined) \
			); \
		}
	} hit;
	static struct {
		union {
			int pattern;

			// ZUN bloat: The static one would have been fine.
			elis_form_t form;
		} cur;
		bool16 teleport_done;

		void frame_common(int8_t phase_id) {
			boss_phase_frame++;
			hit.invincibility_frame++;

			// ZUN bloat: Already done as part of ent_unput_and_put_both(),
			// which is the only function that reads from [ent_attack].
			if(phase_id != 1) {
				ent_attack.pos_cur_set_to(ent_still_or_wave);
			}
		}

		#define phase_frame_common(phase_id, phase_func, flash_colors) { \
			phase.frame_common(phase_id); \
			\
			if(phase.cur.pattern != CHOOSE_NEW) { \
				phase.cur.pattern = phase_func(phase.cur.pattern); \
			} else if(phase.teleport_done == false) { \
				phase.teleport_done = wave_teleport( \
					elis_playfield_random_left(), elis_playfield_random_top() \
				); \
			} else if(phase.teleport_done == true) { \
				phase.cur.pattern = phase_func(phase.cur.pattern); \
				phase.teleport_done = false; \
			} \
			hit_update_and_render(F_GIRL, flash_colors); \
		}

		#define phase_done(end_hp) ( \
			(boss_hp <= end_hp) && (phase.teleport_done == true) \
		)

		void next(int8_t phase_new, int pattern_new) {
			boss_phase = phase_new;
			boss_phase_frame = 0;
			hit.invincibility_frame = 0;
			cur.pattern = pattern_new;
			teleport_done = false;
		}
	} phase;
	static pixel_t bat_velocity_y;
	static pixel_t bat_velocity_x;
	static bool initial_hp_rendered;

	screen_x_t head_left;
	screen_y_t head_top;
	bool16 trails_offscreen;
	const vc_t flash_colors[] = { 3, 6, 8, 2 };
	unsigned char angle;

	Missiles.unput_update_render();

	// Entrance animation
	if(boss_phase == 0) {
		#define entrance_frame hit.invincibility_frame

		enum {
			SPHERE_COUNT = 2,
			TRAIL_COUNT = 3,
		};

		// Trail (i + 1) = position of trail (i) in the previous frame. The
		// head coordinates are stored separately, and trail (TRAIL_COUNT - 1)
		// is never rendered.
		struct {
			screen_y_t top[SPHERE_COUNT][TRAIL_COUNT];
			screen_x_t left[SPHERE_COUNT][TRAIL_COUNT];
		} trails;

		#define sphere_unput_and_put_head(sphere_i, head_left, head_top) { \
			sphere_unput(trails.left[sphere_i][0], trails.top[sphere_i][0]); \
			sphere_put(head_left, head_top, C_SPHERE_LARGE); \
		}

		#define sphere_unput_and_put_trail(sphere_i, trail_i) { \
			sphere_unput( \
				trails.left[sphere_i][trail_i + 1], \
				trails.top[sphere_i][trail_i + 1] \
			); \
			sphere_put( \
				trails.left[sphere_i][trail_i], \
				trails.top[sphere_i][trail_i], \
				(trail_i == 0) ? C_SPHERE_MEDIUM : C_SPHERE_SMALL \
			); \
		}

		#define sphere_trails_forward_copy(sphere_i, head_left, head_top) { \
			trails.left[sphere_i][2] = trails.left[sphere_i][1]; \
			trails.top[sphere_i][2] = trails.top[sphere_i][1]; \
			trails.left[sphere_i][1] = trails.left[sphere_i][0]; \
			trails.top[sphere_i][1] = trails.top[sphere_i][0]; \
			trails.left[sphere_i][0] = head_left; \
			trails.top[sphere_i][0] = head_top; \
		}

		boss_palette_snap();
		girl_bg_snap(1);

		// Trailing rotation
		// -----------------

		angle = 0x00;
		entrance_frame = 0;
		while(1) {
			entrance_frame++;
			for(int i = 0; i < SPHERE_COUNT; i++) {
				head_left = polar_x(
					(BASE_CENTER_X - (SPHERE_W / 2)),
					((GIRL_H * 2) / 2),
					(angle + (i * (0x100 / SPHERE_COUNT))
				));
				head_top = polar_y(
					// Yup, slightly off-center.
					((BASE_CENTER_Y - (SPHERE_H / 2)) - 14),
					((GIRL_H * 2) / 2),
					(angle + (i * (0x100 / SPHERE_COUNT)))
				);

				// ZUN landmine: Reads uninitialized stack memory in frame 0.
				// Thankfully doesn't end up hitting the player or orb sprite
				// in the original binary.
				sphere_unput_and_put_head(i, head_left, head_top);

				// ZUN landmine: Both of these calls read uninitialized stack
				// memory during frames 2 and 3, respectively. Invisible as
				// well.
				if(entrance_frame > 1) {
					sphere_unput_and_put_trail(i, 0);
					if(entrance_frame > 2) {
						sphere_unput_and_put_trail(i, 1);
					}
				}
				sphere_trails_forward_copy(i, head_left, head_top);
			}
			if(entrance_frame >= 120) {
				break;
			}
			angle += (0x300 / 32);

			// [entrance_frame] doesn't directly correspond to frames here,
			// therefore.
			frame_delay(((120 - entrance_frame) / 12) + 1);
		};
		// -----------------

		// Spheres move offscreen / wave-in effect
		// ---------------------------------------

		enum {
			MOVE_INTERVAL = 4,
			MOVE_VELOCITY = (PLAYFIELD_W / 40),

			WAVE_INTERVAL = 4,
			KEYFRAME_WAVE = 20,
			KEYFRAME_WAVE_DONE = 100,
			KEYFRAME_SLIGHT_RIPPLE = 128,
			KEYFRAME_SLIGHT_RIPPLE_DONE = 130,
			KEYFRAME_ENTRANCE_DONE = 140,
		};

		entrance_frame = 0;
		trails_offscreen = false;
		while(1) {
			entrance_frame++;
			if(!trails_offscreen && ((entrance_frame % MOVE_INTERVAL) == 0)) {
				for(int i = 0; i < SPHERE_COUNT; i++) {
					head_left = (
						(trails.left[i][0] + (MOVE_VELOCITY * MOVE_INTERVAL)) -
						(i * (MOVE_VELOCITY * MOVE_INTERVAL * 2))
					);
					head_top = trails.top[i][0];

					sphere_unput_and_put_head(i, head_left, head_top);
					sphere_unput_and_put_trail(i, 0);
					sphere_unput_and_put_trail(i, 1);

					if(
						(trails.left[0][2] > RES_X) &&
						(trails.left[1][2] < (0 - SPHERE_W))
					) {
						trails_offscreen = true;
					}

					sphere_trails_forward_copy(i, head_left, head_top);
				}
			}
			if(
				(entrance_frame > KEYFRAME_WAVE) &&
				(entrance_frame < KEYFRAME_WAVE_DONE)
			) {
				if((entrance_frame % WAVE_INTERVAL) == 0) {
					if(entrance_frame != (KEYFRAME_WAVE + WAVE_INTERVAL)) {
						// Amplitude should technically be
						//
						// 	((KEYFRAME_WAVE_DONE - WAVE_INTERVAL) - frame)
						//
						// here (not +), matching the blitting function below.
						// Good that this function is so sloppy with all its
						// word alignment that it actually makes no difference.
						ent_still_or_wave.wave_sloppy_unput(
							((entrance_frame - WAVE_INTERVAL) + 2),
							(
								(KEYFRAME_WAVE_DONE + WAVE_INTERVAL) -
								entrance_frame
							),
							((entrance_frame - WAVE_INTERVAL) * 6)
						);
					}
					ent_still_or_wave.wave_put(
						C_STILL,
						(entrance_frame + 2),
						(KEYFRAME_WAVE_DONE - entrance_frame),
						(entrance_frame * 6)
					);
				}
			} else if(entrance_frame == KEYFRAME_WAVE_DONE) {
				// Phase should technically be (entrance_frame * 6), but...
				// yeah, see above. No difference here either.
				ent_still_or_wave.wave_sloppy_unput(
					(entrance_frame + 2),
					(KEYFRAME_WAVE_DONE - entrance_frame),
					entrance_frame
				);
				// Unnecessary unblitting...
				ent_still_or_wave.unlock_unput_put_image_lock_8(C_STILL);
			} else if(entrance_frame == KEYFRAME_SLIGHT_RIPPLE) {
				girl_bg_put(1);
				ent_still_or_wave.wave_put(C_STILL, 3, 8, 64);
			} else if(entrance_frame == KEYFRAME_SLIGHT_RIPPLE_DONE) {
				ent_still_or_wave.wave_sloppy_unput(3, 8, 64);
				// Unnecessary unblitting...
				ent_still_or_wave.unlock_unput_put_image_lock_8(C_STILL);
			} else if(entrance_frame > KEYFRAME_ENTRANCE_DONE) {
				break;
			}
			frame_delay(1);
		}

		#undef sphere_trails_forward_copy
		#undef sphere_unput_and_put_trail
		#undef sphere_unput_and_put_head
		#undef entrance_frame
		// ---------------------------------------

		boss_phase_frame = 0;
		hit.invincibility_frame = 0;
		boss_phase = 1;
		ent_still_or_wave.hitbox_orb_inactive = false;

		// Necessary, since the entire entrance animation was only played on
		// VRAM page 0...
		page_access(1); ent_still_or_wave.unlock_put_lock_8();

		// ... which makes this blitting call redundant, though.
		page_access(0); ent_still_or_wave.unlock_put_lock_8();

		phase.teleport_done = false;
		phase.cur.pattern = 1;
		initial_hp_rendered = false;
	} else if(boss_phase == 1) {
		// ZUN bug: Since the fight only ends in Phase 5 at the earliest, HP
		// subtraction in debug mode can lead to this function being called
		// with [boss_phase_frame] being larger than the initial HP value,
		// causing the heap corruption bug mentioned in the comment of this
		// function. Elis starts with an even number of total HP, so this will
		// even happen for the easiest possible case of holding ↵ Return for
		// the first 8 frames of phase 1.
		hud_hp_increment_render(initial_hp_rendered, boss_hp, boss_phase_frame);

		phase_frame_common(1, phase_1, flash_colors);
		if(!hit.invincible && phase_done(HP_PHASE_1_END)) {
			phase.next(2, CHOOSE_NEW);
		}
	} else if(boss_phase == 2) {
		boss_phase_frame++;
		phase.teleport_done = wave_teleport(BASE_LEFT, BASE_TOP);
		if(phase.teleport_done == true) {
			phase_3(99);

			phase.next(3, 1);
		}
	} else if(boss_phase == 3) {
		phase_frame_common(3, phase_3, flash_colors);
		if(!hit.invincible && phase_done(HP_PHASE_3_END)) {
			phase.next(4, CHOOSE_NEW);
			form = F_GIRL;
		}
	} else if(boss_phase == 4) {
		boss_phase_frame++;
		if(!phase.teleport_done) {
			phase.teleport_done = wave_teleport(BASE_LEFT, BASE_TOP);
		} else {
			phase.cur.form = transform_girl_to_bat();
		}
		if(phase.cur.form == F_BAT) {
			phase.next(5, CHOOSE_NEW);
			form = F_BAT;

			phase_5(form, bat_velocity_x, bat_velocity_y, true);
		}
	} else if(boss_phase == 5) {
		phase.frame_common(5);
		if(form != F_GIRL) {
			ent_bat.locked_move_unput_and_put_8(
				bat_velocity_x, bat_velocity_y, (BAT_SPEED_DIVISOR - 1)
			);

			#define bat_cycle_frame (boss_phase_frame % BAT_CYCLE_FRAMES)
			if(bat_cycle_frame == (BAT_FRAMES_PER_CEL * 0)) {
				ent_bat.set_image(C_BAT + 0);
			} else if(bat_cycle_frame == (BAT_FRAMES_PER_CEL * 1)) {
				ent_bat.set_image(C_BAT + 1);
			} else if(bat_cycle_frame == (BAT_FRAMES_PER_CEL * 2)) {
				ent_bat.set_image(C_BAT + 2);
			}
			#undef bat_cycle_frame
		}
		phase_5(form, bat_velocity_x, bat_velocity_y);
		hit_update_and_render(form, flash_colors);
		if(boss_hp <= HP_PHASE_5_END) {
			int i;

			mdrv2_bgm_fade_out_nonblock();
			Pellets.unput_and_reset_nonclouds();
			girl_bg_put(1);
			Missiles.reset();
			shootout_lasers_reset();
			boss_defeat_animate();
		}
	}

	#undef hit_update_and_render
	#undef phase_frame_common
	#undef phase_done
}
