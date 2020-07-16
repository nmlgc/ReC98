#include "th01/main/vars.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"
#include "th01/sprites/main_ptn.h"
#include "th01/main/hud/hud.hpp"

/// Constants
/// ---------
static const int SCORE_LEFT = 256;
static const int CARDCOMBO_LEFT = 400;
static const int MAX_TOP = 0;

static const int MAX_FX = FX(7, 2, 0);

#if (PTN_QUARTER_W < GLYPH_FULL_W)
	#error Original code assumes PTN_QUARTER_W >= GLYPH_FULL_W
#endif
static const int COL_W = PTN_QUARTER_W;
/// ---------

/// Globals
/// -------
// Forces re-rendering of all full-width numbers on the HUD, even if they
// haven't changed since the last render call.
extern unsigned char fwnum_force_rerender;
/// -------

/// Functions
/// ---------
inline int col_left(int first_left, int col) {
	return (first_left + (col * COL_W));
}

#define bg_put(first_left, col, top, ptn_id, quarter) \
	ptn_put_quarter_noalpha_8(col_left(first_left, col), top, ptn_id, quarter)

#define ptn_id_and_quarter_from_i(func, first_left, col, top, ptn_id_base, i) \
	func(first_left, col, top, (ptn_id_base + (i / 4)), (i % 4))

#define digit_changed(var, var_prev, divisor) \
	((var_prev / divisor) % 10) != ((var / divisor) % 10) || \
	(fwnum_force_rerender == 1)
/// ---------
}

template <class T1, class T2> inline void fwnum_put(
	int left, int top, int fx, int digits, const T1 &val, const T2 &val_prev
) {
	graph_putfwnum_fx(
		left, top, fx, digits, val,
		(fwnum_force_rerender == true) ? 0 : val_prev, true
	);
}

#define score_bg(func, digit, top, ptn_id_base) \
	ptn_id_and_quarter_from_i(func, SCORE_LEFT, digit, top, ptn_id_base, digit)

#define score_max_bg(func, digit) \
	score_bg(func, digit, MAX_TOP, PTN_BG_MAX_SCORE)

inline void score_put(int top, int fx, const long &prev) {
	fwnum_put(SCORE_LEFT, top, fx, SCORE_DIGITS, score, prev);
}

#define cardcombo_bg(func, digit, top, ptn_id) \
	func(CARDCOMBO_LEFT, digit, top, ptn_id, digit)

#define cardcombo_max_bg(func, digit) \
	cardcombo_bg(func, digit, MAX_TOP, PTN_BG_MAX_CARDCOMBO)

inline void cardcombo_put(int top, int fx, const int &prev) {
	fwnum_put(CARDCOMBO_LEFT, top, fx, CARDCOMBO_DIGITS, cardcombo_cur, prev);
}

extern "C" {

void hiscore_update_and_render(void)
{
	// TODO: Should just be `static` once the variable can be declared here
	#define prev score_prev
	extern long prev;
	long divisor = 1000000; // Must match SCORE_DIGITS!
	unsigned long hiscore = resident->hiscore;

	if(hiscore >= score) {
		return;
	}
	for(int i = 0; i < SCORE_DIGITS; i++) {
		if(digit_changed(score, prev, divisor)) {
			graph_accesspage_func(1);	score_max_bg(bg_put, i);
			graph_accesspage_func(0);	score_max_bg(bg_put, i);
		}
		divisor /= 10;
	}
	graph_accesspage_func(1);	score_put(MAX_TOP, MAX_FX, prev);
	graph_accesspage_func(0);	score_put(MAX_TOP, MAX_FX, prev);

	prev = score;
	resident->hiscore = score;
	#undef prev
}

void cardcombo_max_render(void)
{
	// TODO: Should just be `static` once the variable can be declared here
	#define prev cardcombo_max_prev
	extern int prev;
	int divisor = 10; // Must match CARDCOMBO_DIGITS!

	for(int i = 0; i < CARDCOMBO_DIGITS; i++) {
		if(digit_changed(cardcombo_cur, prev, divisor)) {
			graph_accesspage_func(1);	cardcombo_max_bg(bg_put, i);
			graph_accesspage_func(0);	cardcombo_max_bg(bg_put, i);
		}
		divisor /= 10;
	}
	graph_accesspage_func(1);	cardcombo_put(MAX_TOP, MAX_FX, prev);
	graph_accesspage_func(0);	cardcombo_put(MAX_TOP, MAX_FX, prev);

	prev = cardcombo_cur;
	#undef prev
}
