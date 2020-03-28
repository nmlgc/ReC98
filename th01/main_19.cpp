/* ReC98
 * -----
 * Code segment #19 of TH01's REIIDEN.EXE
 */

#pragma option -3 -Z -d

extern "C" {
#include "ReC98.h"
#include "th01/ranks.h"
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

#define graph_putkanji_fx(left, top, fx, fmt_instance, kanji) \
	str_from_kanji(kanji_str, kanji); \
	graph_putsa_fx(left, top, fx, kanji_str);
#define graph_printf_fx graph_putsa_fx

#include "th01/hiscore/alph_p_i.cpp"

}
