/* ReC98
 * -----
 * Code segment #19 of TH01's REIIDEN.EXE
 */

#include <string.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/formats/grp.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/shiftjis/fns.hpp"
#include "th01/shiftjis/regist.hpp"
#include "th01/formats/scoredat.hpp"

void near str_from_swapped_kanji(
	shiftjis_t str[3], shiftjis_kanji_swapped_t kanji
)
{
	uint8_t tmp;
	(reinterpret_cast<shiftjis_kanji_t *>(str))[0] = kanji;
	tmp = str[1];
	str[1] = str[0];
	str[0] = tmp;
	str[2] = '\0';
}

#define graph_putkanji_fx_declare() shiftjis_t kanji_str[3];
#define graph_putkanji_fx(left, top, col_and_fx, kanji) { \
	str_from_swapped_kanji(kanji_str, kanji); \
	graph_putsa_fx(left, top, col_and_fx, kanji_str); \
}

#define graph_printf_fx graph_putsa_fx
#define graph_printf_s_fx graph_putsa_fx

// A completely hidden timeout that force-enters a high score name after
// 1000... *keyboard inputs*? Not frames? Why. Like, how do even you
// realistically get to such a number.
// (Best guess: It's a hidden easter egg to amuse players who place drinking
// glasses on cursor keys. Or beer bottles.)
#define regist_input_timeout_declare() unsigned int timeout;
#define regist_input_timeout_reset() timeout = 0;
#define regist_input_timeout_inc() timeout++;
#define regist_input_timeout_if_reached(then) if(timeout > 1000) then

#define regist_bg_put(stage_num_or_scoredat_constant) { \
	z_graph_clear_0(); \
	z_palette_black(); \
	graph_accesspage_func(1); \
	\
	if(stage_num_or_scoredat_constant < SCOREDAT_NOT_CLEARED) { \
		grp_put("game_o.grp", GPF_PALETTE_SHOW); \
	} else { \
		grp_put(REGIST_BG_CLEARED, GPF_PALETTE_KEEP); \
	} \
	graph_copy_accessed_page_to_other(); \
	z_palette_black_in(); \
}

#define regist_title_put( \
	left, stage_num_or_scoredat_constant, ranks, col_and_fx \
) { \
	if(stage_num_or_scoredat_constant < SCOREDAT_NOT_CLEARED) { \
		graph_putsa_fx( \
			left, TITLE_BACK_TOP, col_and_fx, REGIST_TITLE_WITH_SPACE \
		); \
		graph_putsa_fx( \
			(left + REGIST_TITLE_W), TITLE_BACK_TOP, col_and_fx, ranks[rank] \
		); \
	} else { \
		graph_putsa_fx(left, TITLE_TOP, col_and_fx, REGIST_TITLE); \
		graph_putsa_fx( \
			(left + REGIST_TITLE_W), TITLE_TOP, col_and_fx, ranks[rank] \
		); \
	} \
}

#include "th01/hiscore/regist.cpp"
