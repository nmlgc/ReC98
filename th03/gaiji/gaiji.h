// ReC98
// -----
// Gaiji available to TH03

#include "th02/gaiji/from_2.h"

typedef enum {
	// 1P/2P selection cursor
	#define gc_GAIJI_W 2

	gs_YINYANG = 0x02,
	gs_HEART_EMPTY = 0x04,
	gs_HEART_FULL,
	gs_HEART_HALF,
	gs_BOMB,
	gs_BOMB_UNUSED,

	// https://en.wikipedia.org/wiki/Comedy_and_tragedy_masks
	// Just a ● in MIKOFT.BFT, but that one is unused.
	gs_THALIA,

	gc_P1_TOP_1 = 0x12,
	gc_P1_TOP_2 = 0x13,
	gc_P1_BOTTOM_1 = 0x14,
	gc_P1_BOTTOM_2 = 0x15,
	gc_P2_TOP_1 = 0x16,
	gc_P2_TOP_2 = 0x17,
	gc_P2_BOTTOM_1 = 0x18,
	gc_P2_BOTTOM_2 = 0x19,
	gaiji_bar(0x20),
	gaiji_boldfont(0xA0),

	g_SP = 0xCF,

	gaiji_symbols_th02(0xE0),
} gaiji_th03_t;
