#include "platform.h"
#include "pc98.h"
#include "libs/master.lib/master.hpp"
#include "th04/main/frames.h"
#include "th04/main/playfld.hpp"
#include "th04/main/tile/tile.hpp"
#if (GAME == 5)
	#include "th02/main/scroll.hpp"
#endif

extern int8_t playfield_shake_redraw_time;

inline void shift(
	egc_shift_func_t *func,
	vram_y_t top,
	vram_y_t bottom,
	bool negate,
	const pixel_t &dots
) {
	func(
		PLAYFIELD_LEFT,
		top,
		(PLAYFIELD_RIGHT - 1),
		bottom,
		(negate) ? -dots : dots
	);

	// Since these games use page flipping and we only ever shift the active
	// VRAM page, we need to force a redraw *on* the next frame after this one
	// (*for* the one two frames after this one) to undo the shift we just did.
	//
	// Forcing a redraw *on this* frame (*for* the next one) is technically
	// only necessary during the animation, where the other VRAM page will
	// still display its previous shifted state. It's just easier to always
	// unconditionally redraw the next two frames, though.
	playfield_shake_redraw_time = 2;
}

inline void shift_x(egc_shift_func_t *func, bool negate) {
	shift(func, 0, (RES_Y - 1), negate, playfield_shake_x);
}

inline void shift_y(egc_shift_func_t *func, bool negate) {
	#if (GAME == 5)
		// Micro-optimization to limit the amount of moved pixels during
		// bosses.
		if(scroll_line == 0) {
			shift(
				func,
				PLAYFIELD_TOP,
				(PLAYFIELD_BOTTOM - 1),
				negate,
				playfield_shake_y
			);
			return;
		}
	#endif
	shift(func, 0, (RES_Y - 1), negate, playfield_shake_y);
}

void near playfield_shake_update_and_render(void)
{
	if(playfield_shake_anim_time) {
		playfield_shake_x = (stage_frame_mod2 == 0) ? -2 : 2;
		playfield_shake_y = (stage_frame_mod4 <= 1) ? -2 : 2;
		playfield_shake_anim_time--;
	}

	if(playfield_shake_x < 0) {
		#if (GAME == 5)
			// Doubly strong left shaking?
			egc_shift_left(
				PLAYFIELD_LEFT,
				0,
				(PLAYFIELD_RIGHT - 1),
				(RES_Y - 1),
				-playfield_shake_x
			);
		#endif
		shift_x(egc_shift_left, true);
	} else if(playfield_shake_x > 0) {
		shift_x(egc_shift_right, false);
	}
	if(playfield_shake_y < 0) {
		shift_y(egc_shift_up, true);
	} else if(playfield_shake_y > 0) {
		shift_y(egc_shift_down, false);
	}

	if(playfield_shake_redraw_time) {
		playfield_shake_redraw_time--;
		tiles_invalidate_all();
		playfield_shake_x = 0;
		playfield_shake_y = 0;
	}

}
