#pragma option -G

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/rank.h"
#include "th02/score.h"
#include "th02/resident.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/hardware/frmdelay.h"
#include "th02/core/globals.hpp"
extern "C" {
#include "th02/snd/snd.h"
}
#include "th02/main/playfld.hpp"
#include "th02/main/player/player.hpp"
#include "th02/main/hud/hud.hpp"
#include "th02/main/hud/overlay.hpp"

// Gaiji strings
// -------------
// ZUN bloat: Needlessly using a consistent length ruins any chance of
// calculating lengths at compile time. (At least in ancient C++.)

extern const gaiji_th02_t gsSCORE[5];
extern const gaiji_th02_t gsHISCORE[5];
extern const gaiji_th02_t gsREIMU[5];
extern const gaiji_th02_t gsREIGEKI[5];
extern const gaiji_th02_t gsREIRYOKU[5];

static const tram_cell_amount_t gsSCORE_W = (3 * GAIJI_TRAM_W);
static const tram_cell_amount_t gsHISCORE_W = (4 * GAIJI_TRAM_W);

extern const gaiji_th02_t gRANKS[RANK_COUNT][8];
// -------------

#include "th02/gaiji/loadfree.cpp"

// Coordinates
// -----------

static const tram_x_t HUD_CONTINUES_LEFT = (
	HUD_LEFT + ((SCORE_DIGITS - 1) * GAIJI_TRAM_W)
);
static const tram_x_t HUD_LABELED_LABEL_LEFT = (HUD_LEFT + HUD_LABEL_PADDING);

static const tram_x_t HUD_CENTER_X = (HUD_LEFT + (HUD_TRAM_W / 2));

static const shiftjis_kanji_amount_t HUD_LABELED_GAIJI_W = (
	HUD_LABELED_W / GAIJI_TRAM_W
);
// -----------

static const uint8_t SHOT_LEVEL_INTERVAL_BITS = 2;

extern uint8_t POWER_TO_SHOT_LEVEL[POWER_MAX >> SHOT_LEVEL_INTERVAL_BITS];

// Only prints the seven score digits, in contrast to the TH04/TH05 version!
void pascal near hud_score_put(utram_y_t y, int32_t value)
{
	extern int32_t SEVEN_DIGIT_POWERS_OF_10[SCORE_DIGITS - 1];

	int32_t near* po10_p = SEVEN_DIGIT_POWERS_OF_10;
	int c;
	for(tram_x_t x = HUD_LEFT; x < HUD_CONTINUES_LEFT; x += GAIJI_TRAM_W) {
		int numeral = (value / *po10_p);
		value -= (numeral * (*po10_p));
		po10_p++;
		c = (gb_0_ + numeral);
		gaiji_putca(x, y, c, TX_WHITE);
	}
}

void pascal near hud_continues_put(utram_y_t y, int continues_used)
{
	if(continues_used >= 10) {
		continues_used = 9;
	}
	int c = (gb_0_ + continues_used);
	gaiji_putca(HUD_CONTINUES_LEFT, y, c, TX_WHITE);
}

#include "th02/main/score.cpp"

void near player_shot_level_update_and_hud_power_put(void)
{
	struct hack_bar {
		char x[(POWER_MAX / BAR_GAIJI_MAX) + 1]; // ACTUAL TYPE: gaiji_th02_t
	};
	struct hack_colors {
		uint8_t x[SHOT_LEVEL_MAX];
	};
	extern struct hack_bar gHUD_BAR_MAX;
	extern struct hack_colors HUD_POWER_COLORS;
	extern struct hack_bar gHUD_BAR_BLANK;

	int i = 0;
	int value_rem;
	const struct hack_bar G_MAX = gHUD_BAR_MAX;
	const struct hack_colors COLORS = HUD_POWER_COLORS;
	struct hack_bar g_buf = gHUD_BAR_BLANK;

	shot_level = POWER_TO_SHOT_LEVEL[power >> SHOT_LEVEL_INTERVAL_BITS];
	if(shot_level == SHOT_LEVEL_MAX) {
		gaiji_putsa(HUD_LABELED_LEFT, HUD_POWER_Y, G_MAX.x, TX_WHITE);
		return;
	}

	value_rem = power;
	value_rem -= BAR_GAIJI_MAX;
	while(value_rem > 0) {
		g_buf.x[i] = g_BAR_16W;
		value_rem -= BAR_GAIJI_MAX;
		i++;
	}

	// ZUN landmine: This causes a [power] of 0 to be rendered as 16 power
	// instead. Probably the reason why TH02, TH04, and TH05 treat 1 as the
	// lowest possible [power].
	value_rem = ((power - 1) & (BAR_GAIJI_MAX - 1));
	g_buf.x[i] = (g_BAR_01W + value_rem);

	gaiji_putsa(HUD_LABELED_LEFT, HUD_POWER_Y, g_buf.x, COLORS.x[shot_level]);
}

#define hud_gaiji_tally_put(y, value, gaiji) { \
	/** \
	 * ZUN landmine: No check for values > HUD_LABELED_GAIJI_W. These will \
	 * extend the tally into adjacent TRAM cells, and even wrap into the \
	 * next TRAM row and cover the playfield if necessary. \
	 */ \
	{for(int i = 0; value > i; i++) { \
		gaiji_putca( \
			(HUD_LABELED_LEFT + (i * GAIJI_TRAM_W)), y, gaiji, TX_WHITE \
		); \
	}} \
	{for(int i = value; i < HUD_LABELED_GAIJI_W; i++) { \
		gaiji_putca( \
			(HUD_LABELED_LEFT + (i * GAIJI_TRAM_W)), y, gb_SP, TX_WHITE \
		); \
	}} \
}

void near hud_lives_put(void)
{
	static_assert(LIVES_MAX <= HUD_LABELED_GAIJI_W);
	hud_gaiji_tally_put(HUD_LIVES_Y, lives, gs_YINYANG);
}

void near hud_bombs_put(void)
{
	static_assert(BOMBS_MAX <= HUD_LABELED_GAIJI_W);
	hud_gaiji_tally_put(HUD_BOMBS_Y, bombs, gs_BOMB);
}

inline void hud_label_put(utram_x_t left, utram_y_t y, const gaiji_th02_t* s) {
	gaiji_putsa(left, y, reinterpret_cast<const char *>(s), TX_YELLOW);
}

void near hud_put(void)
{
	hud_label_put((HUD_CENTER_X - (gsSCORE_W / 2)), (HUD_SCORE_Y - 1), gsSCORE);
	hud_score_put(HUD_SCORE_Y, score);
	hud_continues_put(HUD_SCORE_Y, resident->continues_used);

	hud_label_put(
		(HUD_CENTER_X - (gsHISCORE_W / 2)), (HUD_HISCORE_Y - 1), gsHISCORE
	);
	hud_score_put(HUD_HISCORE_Y, hiscore);
	hud_continues_put(HUD_HISCORE_Y, hiscore_continues);

	hud_label_put(HUD_LABELED_LABEL_LEFT, HUD_LIVES_Y, gsREIMU);
	hud_lives_put();

	hud_label_put(HUD_LABELED_LABEL_LEFT, HUD_BOMBS_Y, gsREIGEKI);
	hud_bombs_put();

	hud_label_put(HUD_LABELED_LABEL_LEFT, HUD_POWER_Y, gsREIRYOKU);
	player_shot_level_update_and_hud_power_put();

	gaiji_putsa(
		HUD_LABELED_LABEL_LEFT,
		HUD_RANK_Y,
		reinterpret_cast<const char near *>(gRANKS[rank]),
		(
			(rank ==    RANK_EASY) ? TX_GREEN :
			(rank ==  RANK_NORMAL) ? TX_CYAN :
			(rank ==    RANK_HARD) ? TX_MAGENTA :
			/*       RANK_LUNATIC */ TX_RED
		)
	);
}

#pragma option -G-

void pascal near overlay_stage_fade_animate(
	int gaiji_first // ACTUAL TYPE: gaiji_th02_t
)
{
	enum {
		PLAYFIELD_GAIJI_W = (PLAYFIELD_W / GLYPH_FULL_W),
		X_PER_FRAME = 2,
		DURATION = ((PLAYFIELD_GAIJI_W / X_PER_FRAME) + OVERLAY_FADE_CELS),
	};
	shiftjis_kanji_amount_t x;
	tram_y_t y;
	int frame;

	// ACTUAL TYPE: gaiji_th02_t
	int gaiji_last = (gaiji_first + OVERLAY_FADE_CELS - 1);

	for(frame = 0; frame < DURATION; frame++) {
		for(x = 0; x < PLAYFIELD_GAIJI_W; x++) {
			for(y = PLAYFIELD_TRAM_TOP; y <= (PLAYFIELD_TRAM_BOTTOM - 1); y++) {
				int c = ((gaiji_first + frame) - (x >> 1)); // / X_PER_FRAME
				if(c < gaiji_first) {
					c = gaiji_first;
				} else if(c > gaiji_last) {
					c = gaiji_last;
				}
				gaiji_putca(
					(PLAYFIELD_TRAM_LEFT + (x * GAIJI_TRAM_W)), y, c, TX_BLACK
				);
			}
		}
		frame_delay(2);
	}
}

void overlay_stage_leave_animate(void)
{
	overlay_stage_fade_animate(g_OVERLAY_FADE_OUT);
}

void overlay_stage_enter_animate(void)
{
	overlay_stage_fade_animate(g_OVERLAY_FADE_IN);
}
