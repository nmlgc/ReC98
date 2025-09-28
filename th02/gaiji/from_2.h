/// Gaiji introduced in TH02, and shared with later games
/// -----------------------------------------------------

// Enemy health / dream / power bars, with the given width in pixels.
#define gaiji_bar(start) \
	g_BAR_01W = start, \
	g_BAR_02W, \
	g_BAR_03W, \
	g_BAR_04W, \
	g_BAR_05W, \
	g_BAR_06W, \
	g_BAR_07W, \
	g_BAR_08W, \
	g_BAR_09W, \
	g_BAR_10W, \
	g_BAR_11W, \
	g_BAR_12W, \
	g_BAR_13W, \
	g_BAR_14W, \
	g_BAR_15W, \
	g_BAR_16W

#define BAR_GAIJI_MAX 16

// In TH02, ZUN messed up and swapped M and N in MIKOFT.BFT for both regular
// and bold fonts. Therefore, other code shouldn't really use the
// straightforward solution of just adding char literals to a defined start
// offset, as it may suggest that this also works for M and N (which it
// doesn't). This was fixed in later games.
#if (GAME == 2)
#define gb_MN_BUG gb_N, gb_M
#else
#define gb_MN_BUG gb_M, gb_N
#endif

#define gaiji_boldfont(start) \
	gb_0 = start, \
	gb_1, \
	gb_2, \
	gb_3, \
	gb_4, \
	gb_5, \
	gb_6, \
	gb_7, \
	gb_8, \
	gb_9, \
	gb_A, \
	gb_B, \
	gb_C, \
	gb_D, \
	gb_E, \
	gb_F, \
	gb_G, \
	gb_H, \
	gb_I, \
	gb_J, \
	gb_K, \
	gb_L, \
	gb_MN_BUG, \
	gb_O, \
	gb_P, \
	gb_Q, \
	gb_R, \
	gb_S, \
	gb_T, \
	gb_U, \
	gb_V, \
	gb_W, \
	gb_X, \
	gb_Y, \
	gb_Z

#define gaiji_symbols_th02(start) \
	gs_HEART = start, /* 🎔 */ \
	gs_SKULL, /* 💀 */ \
	gs_GHOST, /* 👻 */ \
	gs_SIDDHAM_HAM, /* Siddhaṃ seed syllable HĀṂ (I don't even) */ \
	gs_SPACE, /* ␠ */ \
	gs_ARROW_LEFT, /* ← */ \
	gs_ARROW_RIGHT /* → */
/// -----------------------------------------------------
