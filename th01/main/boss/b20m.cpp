/// Makai Stage 20 Boss - Sariel
/// ----------------------------

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/ptrans.hpp"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/vars.hpp"
#include "th01/formats/grp.h"
}
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/bullet/pellet.hpp"

#define flash_colors	sariel_flash_colors
#define invincible	sariel_invincible
#define invincibility_frame	sariel_invincibility_frame
#define initial_hp_rendered	sariel_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// File names
// ----------

// TODO: Inline (if used 1×), or #define (if used >1×), once Sariel is done
extern const char boss6_l_grp[];
extern const char boss6_h_grp[];
extern const char TENSI_MDT[];
extern const char SE_FN[];
extern const char* BG_IMAGES[4];
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
