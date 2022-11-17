// ReC98
// -----
// Gaiji available to TH04 and TH05

#include "th02/gaiji/from_2.h"
#include "th04/gaiji/bar.h"

#define OVERLAY_FADE_CELS 8
#define RETURN_KEY_CELS 4

typedef enum {
	g_NULL = '\0',
	g_EMPTY = 0x02,
	gs_NOTES, // ♫

	gs_HEART_2 = 0x06, // 🎔 (duplicated)
	gs_EXCLAMATION, // !
	gs_QUESTION, // ?
	gs_SWEAT, // 💦
	gs_DOUBLE_EXCLAMATION, // ‼
	gs_EXCLAMATION_QUESTION, // ⁉

	#if (GAME == 5)
		ga_RETURN_KEY = 0x1C,
		ga_RETURN_KEY_last = (ga_RETURN_KEY + RETURN_KEY_CELS - 1),
	#endif

	gaiji_bar(0x20),
	gaiji_bar_max(0x30),
	g_OVERLAY_FADE,
	g_OVERLAY_FADE_last = (g_OVERLAY_FADE + OVERLAY_FADE_CELS - 1),
	gaiji_boldfont(0xA0),
	gs_DOT = 0xC4,
	gaiji_symbols_th02(0xC9),
	gs_BOMB = 0xD3, // ◉? ⦿? 🎯? 🖸? Or simply 💣?
	gs_YINYANG, // ☯
	gs_END, // "End"
	gs_TEN = 0xE6, // 点
	gs_YUME, // 夢
	gs_TAMA, // 弾
	gs_ALL, // "All"
	g_HISCORE_STAGE_EMPTY = 0xEF,
	g_NONE = 0xFF,
} gaiji_th04_t;
