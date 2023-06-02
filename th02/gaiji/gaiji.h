// ReC98
// -----
// Gaiji available to TH02

#include "th02/gaiji/from_2.h"

typedef enum {
	gs_YINYANG = 0x02, // ☯
	gs_BOMB, // ◉? ⦿? 🎯? 🖸? Or simply 💣?

	gaiji_bar(0x30),

	// A completely filled, 80-pixel bar with MAX drawn on top, stored in 5
	// consecutive gaiji characters.
	g_BAR_MAX_0,
	g_BAR_MAX_1,
	g_BAR_MAX_2,
	g_BAR_MAX_3,
	g_BAR_MAX_4,

	gaiji_boldfont(0xA0),

	gs_Sc,
	gs_cor,
	gs_e,
	gs_REIRYOKU_REI,
	gs_REIRYOKU_RYOKU,
	gs_REIMU_REI,
	gs_REIMU_MU,
	gs_BLANK,
	gs_REIGEKI_REI,
	gs_REIGEKI_GEKI,
	gs_Hi,
	gb_SP,
	gs_NOTES = 0xD8, // ♫
	gs_BULLET = 0xDA, // •
	gs_PERIOD, // .
	gs_EXCLAMATION, // !
	gs_QUESTION, // ?
	gs_ELLIPSIS, // …
	gs_COPYRIGHT, // ©

	gaiji_symbols_th02(0xE0),

	gs_END, // "End"

	// Unused 32x16 rank sprites
	gs_EA, gs_SY, // "Ea", "sy"
	gs_NOR, gs_MAL, // "Nor, "mal"
	gs_HA, gs_RD, // "Ha, "rd"
	gs_LUN, gs_ATIC, // "Lun", "atic"

	gs_ALL, // "All"
} gaiji_th02_t;
