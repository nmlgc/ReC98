#include "th01/hardware/frmdelay.h"
#include "th01/hardware/tram_x16.hpp"
#include "th01/snd/mdrv2.h"
#include "shiftjis.hpp"

inline void touhou_reiiden_animate_char(shiftjis_kanji_t shiftjis) {
	mdrv2_se_play(14);
	tram_x16_kanji_center_reverse(shiftjis_to_jis(shiftjis));
	frame_delay(8);
}

inline void touhou_reiiden_animate(void) {
	touhou_reiiden_animate_char('“Œ');
	touhou_reiiden_animate_char('•û');
	touhou_reiiden_animate_char('š');
	touhou_reiiden_animate_char('èË');
	touhou_reiiden_animate_char('ˆÙ');
	touhou_reiiden_animate_char('“`');
}
