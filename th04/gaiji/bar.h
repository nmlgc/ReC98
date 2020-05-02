#include "th03/gaiji/bar.h"

// A completely filled, 128-pixel bar, stored in 8 consecutive gaiji
// characters. TH05 has *MAX♡ drawn on the last three.
#define G_BAR_MAX(sprite)
#define gaiji_bar_max(start) \
	g_BAR_MAX_0 = start, \
	g_BAR_MAX_1, \
	g_BAR_MAX_2, \
	g_BAR_MAX_3, \
	g_BAR_MAX_4, \
	g_BAR_MAX_5, \
	g_BAR_MAX_6, \
	g_BAR_MAX_7
