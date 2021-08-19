/// Makai Stage 20 Boss - Sariel
/// ----------------------------

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/ptrans.hpp"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"
#include "th01/formats/grp.h"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/main_ptn.h"
#include "th01/sprites/pellet.h"
#include "th01/main/vars.hpp"
#include "th01/main/boss/entity_a.hpp"
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

static const pixel_t WAND_W = 128; // That's 32 more than BOSS6_2.BOS is wide?
static const pixel_t WAND_H = 96;

static const int WAND_PTN_W = (WAND_W / PTN_W);
static const int WAND_PTN_H = (WAND_H / PTN_H);
// -----------

#define flash_colors	sariel_flash_colors
#define invincible	sariel_invincible
#define invincibility_frame	sariel_invincibility_frame
#define initial_hp_rendered	sariel_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// Entities (and animations)
// --------

#define ent_shield	boss_entities[0]
#define anm_dress 	boss_anims[0]
#define anm_wand  	boss_anims[1]
// --------

// File names
// ----------

// TODO: Inline (if used 1×), or #define (if used >1×), once Sariel is done
extern const char boss6_l_grp[];
extern const char boss6_h_grp[];
extern const char TENSI_MDT[];
extern const char SE_FN[];
extern const char* BG_IMAGES[4];
extern const char boss6_1_bos[];
extern const char boss6_2_bos[];
extern const char boss6_3_bos[];
extern const char boss6gr1_grc[];
extern const char boss6gr2_grc[];
extern const char boss6gr3_grc[];
extern const char boss6gr4_grc[];
// ----------


#define select_for_rank sariel_select_for_rank
#include "th01/main/select_r.cpp"

void sariel_entrance(int8_t)
{
	pellet_interlace = true;

	text_fillca(' ', (TX_BLACK | TX_REVERSE));

	/*  graph_accesspage_func(0);  */	grp_put_palette_show(boss6_l_grp);
	/**/graph_accesspage_func(1)/**/;	grp_put_palette_show(boss6_h_grp);

	graph_accesspage_func(0);
	stageobjs_init_and_render(BOSS_STAGE);
	mdrv2_bgm_load(TENSI_MDT);
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
	ent_shield.load(boss6_1_bos, 0);
	anm_wand.load(boss6_2_bos, 0);
	anm_dress.load(boss6_3_bos, 1);
	grc_load(0, boss6gr1_grc);
	grc_load(1, boss6gr2_grc);
	grc_load(2, boss6gr3_grc);
	grc_load(3, boss6gr4_grc);
	boss_palette_snap();
	void sariel_setup(void);
	sariel_setup();
	ptn_new(PTN_SLOT_BG_BOSS, ((WAND_PTN_W * WAND_PTN_H) + 4)); // ???
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
