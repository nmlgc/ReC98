// Shared boss implementation macros.

// Common implementation of [boss_bg_render]:
// 1) Stage tiles before and after the fight
// 2) A static backdrop image during the fight
// 3) An opaque .BB tile animation as the transition between 1) and 2),
//    rendered on top of 1) during its first half, and on top of 2) during its
//    second half.
#define boss_bg_render_entrance_bb_opaque_and_backdrop( \
	on_hp_fill, \
	entrance_bb_cel_type, /* MODDERS: Pick one, and remove this parameter */ \
	entrance_bb_frames_per_cel, \
	backdrop_left, \
	backdrop_top, \
	backdrop_col, \
	backdrop_colorfill, /* MODDERS: Remove, and call boss_backdrop_render() */ \
	bb_col \
) { \
	if(boss.phase == PHASE_HP_FILL) { \
		on_hp_fill; \
	} else if(boss.phase == PHASE_BOSS_ENTRANCE_BB) { \
		entrance_bb_cel_type entrance_cel = ( \
			boss.phase_frame / entrance_bb_frames_per_cel \
		); \
		if(entrance_cel < (TILES_BB_CELS / 2)) { \
			tiles_render_all(); \
		} else { \
			/* A copy of boss_backdrop_render()… */ \
			grcg_setmode_tdw(); \
			grcg_setcolor_direct(backdrop_col); \
			/* … that probably predated [boss_backdrop_colorfill]? */ \
			backdrop_colorfill(); \
			grcg_off(); \
			\
			cdg_put_noalpha_8(backdrop_left, backdrop_top, CDG_BG_BOSS); \
		} \
		tiles_bb_col = bb_col; \
		tiles_bb_put(bb_boss_seg, entrance_cel); \
	} else if(boss.phase < PHASE_BOSS_EXPLODE_BIG) { \
		boss_backdrop_render(backdrop_left, backdrop_top, backdrop_col); \
	} else if(boss.phase == PHASE_BOSS_EXPLODE_BIG) { \
		tiles_render_all(); \
	} else /* if(boss.phase == PHASE_NONE) */ { \
		tiles_render_after_custom(boss.phase_frame); \
	}  \
}

// Like boss_bg_render_entrance_bb_opaque_and_backdrop(), but rendering 3) as
// a transition between stage tiles (where the entrance .BB bit is 0) and the
// backdrop image (where the entrance .BB bit is 1).
#define boss_bg_render_entrance_bb_transition_and_backdrop( \
	on_hp_fill, backdrop_left, backdrop_top, backdrop_col \
) { \
	if(boss.phase == PHASE_HP_FILL) { \
		on_hp_fill; \
	} else if(boss.phase == PHASE_BOSS_ENTRANCE_BB) { \
		boss_backdrop_render(backdrop_left, backdrop_top, backdrop_col); \
		tiles_bb_invalidate( \
			bb_boss_seg, \
			(boss.phase_frame / ENTRANCE_BB_TRANSITION_FRAMES_PER_CEL) \
		); \
		tiles_redraw_invalidated(); \
	} else if(boss.phase < PHASE_BOSS_EXPLODE_BIG) { \
		boss_backdrop_render(backdrop_left, backdrop_top, backdrop_col); \
	} else if(boss.phase == PHASE_BOSS_EXPLODE_BIG) { \
		tiles_render_all(); \
	} else /* if(boss.phase == PHASE_NONE) */ { \
		tiles_render_after_custom(boss.phase_frame); \
	} \
}
