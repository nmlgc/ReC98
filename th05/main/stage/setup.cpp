/* ReC98
 * -----
 * TH05 stage initialization
 */

#include "th04/sprites/main_cdg.h"
extern "C" {
#include "th04/main/midboss/midboss.hpp"
#include "th05/main/stage/stages.hpp"
#include "th05/main/boss/bosses.hpp"

void pascal near stage1_setup(void)
{
	midboss_update_func = midboss1_update;
	midboss_render_func = midboss1_render;
	midboss.frames_until = 2500;
	midboss.pos. cur.set(192, 96);
	midboss.pos.prev.set(192, 96);
	midboss.pos.velocity.set(0, 0);
	midboss.hp = 1000;
	midboss.sprite = 200;

	boss_reset();
	boss.pos.init(192, 64);
	boss_bg_render_func = sara_bg_render;
	boss_update_func = sara_update;
	boss_fg_render_func = sara_fg_render;
	boss.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_sprite_left = 186;
	boss_sprite_right = 184;
	boss_sprite_stay = 180;
	boss_backdrop_colorfill = playfield_fillm_32_0_320_192;

	super_entry_bfnt("st00.bmt");
	cdg_load_all_noalpha(CDG_BG_BOSS, "st00bk.cdg");
	bb_boss_load("st00.bb");

	stage_render = nullfunc_near;
	stage_invalidate = nullfunc_near;
}

void pascal near stage2_setup(void)
{
	midboss_update_func = midboss2_update;
	midboss_render_func = midboss2_render;
	midboss.frames_until = 2750;
	midboss.pos.init(192, -32);
	midboss.pos.velocity.set(0.0f, 0.5f);
	midboss.hp = 1400;
	midboss.sprite = 202;

	boss_reset();
	boss.pos.init(192, 64);
	boss_bg_render_func = louise_bg_render;
	boss_update_func = louise_update;
	boss_fg_render_func = louise_fg_render;
	boss.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_backdrop_colorfill = playfield_fillm_0_0_384_192__1;

	super_entry_bfnt("st01.bmt");
	cdg_load_all_noalpha(CDG_BG_BOSS, "st01bk.cdg");
	bb_boss_load("st01.bb");

	stage_render = stage2_update;
	stage_invalidate = stage2_invalidate;
}

void pascal near stage3_setup(void)
{
	midboss_update_func = midboss3_update;
	midboss_render_func = midboss3_render;
	midboss.frames_until = 5750;
	midboss.pos.init(192, -32);
	midboss.pos.velocity.set(0.0f, 0.5f);
	midboss.hp = 1400;
	midboss.sprite = 208;

	boss_reset();
	boss.pos.init(192, 64);
	boss_bg_render_func = alice_bg_render;
	boss_update_func = alice_update;
	boss_fg_render_func = alice_fg_render;
	boss.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_backdrop_colorfill = playfield_fillm_0_205_384_163;
	boss_sprite_left = 188;
	boss_sprite_right = 186;
	boss_sprite_stay = 180;

	super_entry_bfnt("st02.bmt");
	cdg_load_all_noalpha(CDG_BG_BOSS, "st02bk.cdg");
	bb_boss_load("st02.bb");

	stage_render = nullfunc_near;
	stage_invalidate = nullfunc_near;
}

void pascal near stage4_setup(void)
{
	midboss_update_func = midboss4_update;
	midboss_render_func = midboss4_render;
	midboss.frames_until = 3900;
	midboss.pos.init(192, -32);
	midboss.pos.velocity.set(0.0f, 0.5f);
	midboss.hp = 1100;
	midboss.sprite = 208;

	boss_reset();
	boss.pos.init( 96, 64);
	yuki.pos.init(288, 64);
	boss_bg_render_func = mai_yuki_bg_render;
	boss_update_func = mai_yuki_update;
	boss_fg_render_func = mai_yuki_fg_render;
	boss.sprite = 180;
	yuki.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_backdrop_colorfill = playfield_fillm_64_56_256_256;

	super_entry_bfnt("st03.bmt");
	cdg_load_all_noalpha(CDG_BG_BOSS, "st03bk.cdg");
	bb_boss_load("st03.bb");

	stage_render = nullfunc_near;
	stage_invalidate = nullfunc_near;
}

void pascal near stage5_setup(void)
{
	midboss_update_func = midboss5_update;
	midboss_render_func = midboss5_render;
	midboss.frames_until = 4800;
	midboss.pos.init(192, -32);
	midboss.pos.velocity.set(0.0f, 0.5f);
	midboss.hp = 1550;
	midboss.sprite = 212;

	boss_reset();
	boss.pos.init(96, 64);
	boss2.pos.init(192, 64);
	boss_bg_render_func = yumeko_bg_render;
	boss_update_func = yumeko_update;
	boss_fg_render_func = yumeko_fg_render;
	boss.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_backdrop_colorfill = playfield_fillm_0_0_384_192__2;

	super_entry_bfnt("st04.bmt");
	cdg_load_all_noalpha(CDG_BG_BOSS, "st04bk.cdg");
	bb_boss_load("st04.bb");

	/* TODO: Replace with the decompiled calls
	 * 	yumeko_interval_phase4 = select_for_rank(20, 10,  6,  6);
	 *	yumeko_interval_phase7 = select_for_rank(48, 32, 24, 24);
	 * once that function is part of this translation unit */
	#define SELECT_FOR_RANK(easy, normal, hard, lunatic) _asm { \
		db	0x66, 0x68,  normal, 0x00, easy, 0x00; \
		db	0x66, 0x68, lunatic, 0x00, hard, 0x00; \
		nop; push cs; call near ptr select_for_rank; \
	}
	SELECT_FOR_RANK(20, 10,  6,  6);
	yumeko_interval_phase4 = _AL;
	SELECT_FOR_RANK(48, 32, 24, 24);
	yumeko_interval_phase7 = _AL;

	stage_render = nullfunc_near;
	stage_invalidate = nullfunc_near;
}

void pascal near stage6_setup(void)
{
	midboss_update_func = nullfunc_far;
	midboss_render_func = nullfunc_near;
	midboss.frames_until = 30000;

	boss_reset();
	boss.pos.init(192, 64);
	boss_bg_render_func = shinki_bg_render;
	boss_update_func = shinki_update;
	boss_fg_render_func = shinki_fg_render;
	boss.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_backdrop_colorfill = playfield_fillm_0_104_384_192;

	cdg_load_all_noalpha(CDG_BG_BOSS, "st05bk.cdg");
	cdg_load_all_noalpha(CDG_BG_2, "st05bk2.cdg");
	bb_boss_load("st05.bb");

	stage_render = nullfunc_near;
	stage_invalidate = nullfunc_near;
}

void pascal near stagex_setup(void)
{
	midboss_update_func = midbossx_update;
	midboss_render_func = midbossx_render;
	midboss.frames_until = 5800;
	midboss.pos.init(192, -16);
	midboss.angle = +0x40;
	midboss.hp = 3000;
	midboss.sprite = 220;

	boss_reset();
	boss.pos.init(192, 64);
	boss_bg_render_func = exalice_bg_render;
	boss_update_func = exalice_update;
	boss_fg_render_func = exalice_fg_render;
	boss.sprite = 180;
	boss_hitbox_radius.set(24, 24);
	boss_backdrop_colorfill = playfield_fillm_0_104_384_192;

	super_entry_bfnt("st06.bmt");
	bb_boss_load("st03.bb");

	stage_render = nullfunc_near;
	stage_invalidate = nullfunc_near;
}

}
