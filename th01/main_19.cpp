/* ReC98
 * -----
 * Code segment #19 of TH01's REIIDEN.EXE
 */

#pragma option -d

extern "C" {
#include <io.h>
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "twobyte.h"
#include "master.hpp"
#include "th01/ranks.h"
#include "th01/formats/grp.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/graph.h"
#include "th01/hiscore/scoredat.hpp"

extern char rank;

#define scoredat_cli()
#define scoredat_sti()
#define scoredat_error(str)
#define scoredat_exist(fn) file_exist(fn)
#define scoredat_create(fn) file_create(fn)
#define scoredat_ropen(fn) file_ropen(fn)
#define scoredat_read(buf, size) file_read(buf, size)
#define scoredat_write(buf, size) file_write(buf, size)
#define scoredat_close() file_close()
#include "th01/hiscore/scorelod.cpp"

uint32_t scoredat_hiscore_get()
{
	return scoredat_points[0];
}

#include "th01/hiscore/score_nm.cpp"

void pascal near str_from_kanji(char str[3], uint16_t kanji)
{
	char tmp;
	(reinterpret_cast<uint16_t *>(str))[0] = kanji;
	tmp = str[1];
	str[1] = str[0];
	str[0] = tmp;
	str[2] = '\0';
}

#define graph_putkanji_fx(left, top, col_and_fx, fmt_instance, kanji) \
	str_from_kanji(kanji_str, kanji); \
	graph_putsa_fx(left, top, col_and_fx, kanji_str);
#define graph_printf_fx graph_putsa_fx

#define graph_printf_s_fx(left, top, col_and_fx, fmt_instance, str) \
	graph_putsa_fx(left, top, col_and_fx, str);

#define regist_route_put(left, top, col_and_fx, char_1, char_2) \
	unsigned char route[sizeof(twobyte_t) + 1]; \
	route[2] = '\0'; \
	route[0] = char_1; \
	route[1] = char_2; \
	graph_putsa_fx(left, top, col_and_fx, route); \

#define ALPHABET_SPACE_0 ALPHABET_SPACE
#define ALPHABET_LEFT_0  ALPHABET_LEFT
#define ALPHABET_RIGHT_0 ALPHABET_RIGHT
#define ALPHABET_ENTER_0 ALPHABET_ENTER

// A completely hidden timeout that force-enters a high score name after
// 1000... *keyboard inputs*? Not frames? Why. Like, how do even you
// realistically get to such a number.
// (Best guess: It's a hidden easter egg to amuse players who place drinking
// glasses on cursor keys. Or beer bottles.)
#define regist_input_timeout_declare() unsigned int timeout;
#define regist_input_timeout_reset() timeout = 0;
#define regist_input_timeout_inc() timeout++;
#define regist_input_timeout_if_reached(then) if(timeout > 1000) then

#define regist_bg_put(stage) { \
	extern const char REGIST_BG_NOT_CLEARED[]; \
	extern const char REGIST_BG_CLEARED[]; \
	z_graph_clear_0(); \
	z_palette_black(); \
	graph_accesspage_func(1); \
	\
	if(stage < SCOREDAT_NOT_CLEARED) { \
		grp_put_palette_show(REGIST_BG_NOT_CLEARED); \
	} else { \
		grp_put(REGIST_BG_CLEARED); \
	} \
	graph_copy_page_back_to_front(); \
	z_palette_black_in(); \
}

#define regist_title_put(left, stage, ranks, col_and_fx) { \
	extern const char REGIST_TITLE_1[]; \
	extern const char REGIST_TITLE_2[]; \
	if(stage < SCOREDAT_NOT_CLEARED) { \
		graph_putsa_fx(left +   0, TITLE_BACK_TOP, col_and_fx, REGIST_TITLE_1); \
		graph_putsa_fx(left + 192, TITLE_BACK_TOP, col_and_fx, ranks[rank]); \
	} else { \
		graph_putsa_fx(left +   0, TITLE_TOP, col_and_fx, REGIST_TITLE_2); \
		graph_putsa_fx(left + 192, TITLE_TOP, col_and_fx, ranks[rank]); \
	} \
}

#include "th01/hiscore/regist.cpp"

}
