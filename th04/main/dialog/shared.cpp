#include "th04/main/dialog/shared.hpp"

#define BOX_TILE_W 16
#define BOX_TILE_H 4
#define BOX_TILE_COUNT 3

#define BOX_TILE_VRAM_W (BOX_TILE_W / BYTE_DOTS)
#define BOX_VRAM_W (BOX_W / BYTE_DOTS)

extern const dot_rect_t(BOX_TILE_W, BOX_TILE_H) BOX_TILES[BOX_TILE_COUNT];

bool near std_update_done(void)
{
	return false;
}

bool near std_update_frames_then_animate_dialog_and_activate_boss_if_done(void)
{
	if((scroll_speed == 0) && (page_back == 1)) {
		#if (GAME == 4)
			if((stage_id == 5) || (stage_id == STAGE_EXTRA)) {
				cdg_free(CDG_EYECATCH);
				std_free();
				map_free();
			}
		#endif

		/* TODO: Replace with the decompiled call
		 * dialog_animate();
		 * once that function is part of this translation unit */
		_asm {
			nop;
			push cs;
			call near ptr dialog_animate;
		}

		std_update = std_update_done;
		bg_render_not_bombing = boss_bg_render_func;
		boss_update = boss_update_func;
		boss_fg_render = boss_fg_render_func;
		#if (GAME == 4)
			bgm_title_id = (1 + (stage_id * 2) + 1);
			if((stage_id == 3) && (playchar != PLAYCHAR_REIMU)) {
				// TODO: Calculate as (sizeof(BGM_TITLES) - 1)
				bgm_title_id = 16;
			}
		#endif
		overlay1 = overlay_boss_bgm_update_and_render;
		return true;
	}
	total_std_frames++;
	return false;
}

void pascal near dialog_box_put(uscreen_x_t left, uvram_y_t top, int tile)
;
