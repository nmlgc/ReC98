#include "platform/x86real/flags.hpp"
#include "th04/main/dialog/shared.hpp"

#define BOX_TILE_W 16
#define BOX_TILE_H 4
#define BOX_TILE_COUNT 3

#define BOX_TILE_VRAM_W (BOX_TILE_W / BYTE_DOTS)
#define BOX_VRAM_W (BOX_W / BYTE_DOTS)
static const size_t BOX_TILE_SIZE = (BOX_TILE_VRAM_W * BOX_TILE_H);

extern const dot_rect_t(BOX_TILE_W, BOX_TILE_H) near BOX_TILES[BOX_TILE_COUNT];

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
{
	#define rows_left	static_cast<pixel_t>(_DX)

	// ZUN bloat: A near pointer would have been much simpler...
	#define offset	static_cast<uint16_t>(_BX)

	grcg_setcolor(GC_RMW, 1);
	_ES = SEG_PLANE_B;
	_AX = left;
	_DX = top;
	_DI = vram_offset_shift_fast(_AX, _DX);

	static_assert(BOX_TILE_SIZE == 8);
	offset = tile;
	offset <<= 3;

	rows_left = BOX_H;

	do {
		static_assert(BOX_TILE_VRAM_W == 2);
		static_assert((BOX_VRAM_W & 1) == 0);
		_CX = (BOX_VRAM_W / 2);
		_AX = *reinterpret_cast<const dots_t(BOX_TILE_W) __ds *>(
			(reinterpret_cast<const uint8_t __ds *>(BOX_TILES) + offset)
		);
		asm { rep stosw };

		// A needlessly clever wraparound check that expects the box tile size
		// to be a power of two.
		static_assert((BOX_TILE_SIZE & (BOX_TILE_SIZE - 1)) == 0);
		offset += BOX_TILE_VRAM_W;

		// Turbo C++ is too smart to emit this instruction with
		// pseudo-registers, turning it into `TEST BL, 7`.
		asm { test bx, (BOX_TILE_SIZE - 1); }
		if(FLAGS_ZERO) {
			offset -= BOX_TILE_SIZE;
		}

		_DI += (ROW_SIZE - BOX_VRAM_W);
	} while(--rows_left);

	grcg_off();

	#undef offset
	#undef rows_left
}
