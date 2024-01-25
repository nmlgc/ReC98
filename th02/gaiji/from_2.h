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
	#define gb_MN_BUG gb_N_, gb_M_
#else
	#define gb_MN_BUG gb_M_, gb_N_
#endif

#define gaiji_boldfont(start) \
	gb_0_ = start, \
	gb_1_, \
	gb_2_, \
	gb_3_, \
	gb_4_, \
	gb_5_, \
	gb_6_, \
	gb_7_, \
	gb_8_, \
	gb_9_, \
	gb_A_, \
	gb_B_, \
	gb_C_, \
	gb_D_, \
	gb_E_, \
	gb_F_, \
	gb_G_, \
	gb_H_, \
	gb_I_, \
	gb_J_, \
	gb_K_, \
	gb_L_, \
	gb_MN_BUG, \
	gb_O_, \
	gb_P_, \
	gb_Q_, \
	gb_R_, \
	gb_S_, \
	gb_T_, \
	gb_U_, \
	gb_V_, \
	gb_W_, \
	gb_X_, \
	gb_Y_, \
	gb_Z_

#define gaiji_symbols_th02(start) \
	gs_HEART = start, /* 🎔 */ \
	gs_SKULL, /* 💀 */ \
	gs_GHOST, /* 👻 */ \
	gs_SIDDHAM_HAM, /* Siddhaṃ seed syllable HĀṂ (I don't even) */ \
	gs_SPACE, /* ␠ */ \
	gs_ARROW_LEFT, /* ← */ \
	gs_ARROW_RIGHT /* → */
/// -----------------------------------------------------
