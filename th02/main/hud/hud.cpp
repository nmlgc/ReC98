#pragma option -G

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/main/player/player.hpp"
#include "th02/main/hud/hud.hpp"

static const uint8_t SHOT_LEVEL_INTERVAL_BITS = 2;

extern uint8_t POWER_TO_SHOT_LEVEL[POWER_MAX >> SHOT_LEVEL_INTERVAL_BITS];

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
