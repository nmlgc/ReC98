#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "shiftjis.hpp"
#include "master.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#if (GAME == 5)
	#include "th02/v_colors.hpp"
	#include "th04/hardware/bgimage.hpp"
	#include "th04/gaiji/gaiji.h"
#endif
}
#include "th03/cutscene/cutscene.hpp"

typedef enum {
	BOX_MASK_0,
	BOX_MASK_1,
	BOX_MASK_2,
	BOX_MASK_3,
	BOX_MASK_COPY,
	BOX_MASK_COUNT,

	_box_mask_t_FORCE_UINT16 = 0xFFFF
} box_mask_t;

#define egc_start_copy egc_start_copy_1
void near egc_start_copy(void);

// Copies the text box area from VRAM page 1 to VRAM page 0, applying the
// given [mask]. Assumes that the EGC is active, and initialized for a copy.
void pascal near box_1_to_0_masked(box_mask_t mask)
{
	extern const dot_rect_t(16, 4) BOX_MASKS[BOX_MASK_COUNT];
	egc_temp_t tmp;

	for(screen_y_t y = BOX_TOP; y < BOX_BOTTOM; y++) {
		outport2(EGC_READPLANEREG, 0x00ff);
		// EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD
		outport2(EGC_MODE_ROP_REG, 0x3100);
		outport2(EGC_BITLENGTHREG, 0xF);
		outport(EGC_MASKREG, BOX_MASKS[mask][y & 3]);

		vram_offset_t vram_offset = vram_offset_shift(BOX_LEFT, y);
		pixel_t x = 0;
		while(x < BOX_W) {
			graph_accesspage(1);	tmp = egc_chunk(vram_offset);
			graph_accesspage(0);	egc_chunk(vram_offset) = tmp;
			x += EGC_REGISTER_DOTS;
			vram_offset += EGC_REGISTER_SIZE;
		}
	}
}

void near box_1_to_0_animate(void)
{
	// ZUN bloat: box_1_to_0_masked() switches the accessed page anyway.
	#if (GAME == 5)
		graph_accesspage(0);
	#endif

	egc_start_copy();
	if(!fast_forward) {
		for(int i = BOX_MASK_0; i < BOX_MASK_COPY; i++) {
			box_1_to_0_masked(static_cast<box_mask_t>(i));
			frame_delay(text_interval);
		}
	}
	box_1_to_0_masked(BOX_MASK_COPY);
	egc_off();

	#if (GAME == 5)
		frame_delay(1); // ZUN quirk
	#endif
}

#if (GAME == 5)
	void pascal near box_wait_animate(int frames_to_wait)
	{
		enum {
			LEFT = (BOX_RIGHT + GLYPH_FULL_W),
		};

		unsigned int frames_waited = 0;
		bool16 ignore_frames = false;

		while(1) {
			cutscene_input_sense();
			if(key_det == INPUT_NONE) {
				break;
			}
			frame_delay(1);
		}

		if(frames_to_wait == 0) {
			frames_to_wait = 999;
			ignore_frames = true;
		}

		graph_accesspage(0);
		while(1) {
			cutscene_input_sense();

			// ZUN bloat: A white glyph aligned to the 8×16 cell grid, without
			// applying boldface… why not just show it on TRAM?
			bgimage_put_rect(LEFT, cursor.y, GLYPH_FULL_W, GLYPH_H);

			if(
				(frames_to_wait <= 0) ||
				(key_det & INPUT_OK) ||
				(key_det & INPUT_SHOT) ||
				(key_det & INPUT_CANCEL)
			) {
				return;
			}
			graph_gaiji_putc(
				LEFT,
				cursor.y,
				(ga_RETURN_KEY + ((frames_waited / 8) & (RETURN_KEY_CELS - 1))),
				V_WHITE
			);
			frames_waited++;
			if(!ignore_frames) {
				frames_to_wait--;
			}
			frame_delay(1);
		}
	}
#endif
