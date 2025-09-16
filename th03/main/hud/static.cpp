#include "th03/main/hud/static.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/gaiji/gaiji.h"
#include "th03/resident.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

void hud_wipe(void)
{
	text_fillca(' ', (TX_BLACK | TX_REVERSE));

	// Include the bottom row of TRAM, which contains the gauge.
	text_boxfilla(
		playfield_tram_x(0, 0),
		PLAYFIELD_TRAM_TOP,
		(playfield_tram_x(0, PLAYFIELD_W) - 1),
		((RES_Y / GLYPH_H) - 1),
		TX_WHITE
	);
	text_boxfilla(
		playfield_tram_x(1, 0),
		PLAYFIELD_TRAM_TOP,
		(playfield_tram_x(1, PLAYFIELD_W) - 1),
		((RES_Y / GLYPH_H) - 1),
		TX_WHITE
	);
}

void pascal hud_static_halfhearts_put(pid_t pid)
{
	enum {
		HALFHEARTS_W = ((HALFHEARTS_MAX / 2) * GAIJI_W),
	};

	tram_x_t x;
	int halfheart_i = 0;
	if(pid == 0) {
		x = (playfield_tram_x(0, ((PLAYFIELD_W / 2) - (HALFHEARTS_W / 2))));
	} else {
		x = (playfield_tram_x(1, ((PLAYFIELD_W / 2) - (HALFHEARTS_W / 2))));
	}
	int halfhearts;
	tram_y_t y = PLAYFIELD_TRAM_TOP;

	halfhearts = players[pid].halfhearts;
	while(halfheart_i < halfhearts) {
		if((halfhearts - halfheart_i) >= 2) {
			gaiji_putca(x, y, gs_HEART_FULL, TX_WHITE);
		} else {
			gaiji_putca(x, y, gs_HEART_HALF, TX_WHITE);
		}
		x += GAIJI_TRAM_W;
		halfheart_i += 2;
	}

	while(halfheart_i < HALFHEARTS_MAX) {
		gaiji_putca(x, y, gs_HEART_EMPTY, TX_WHITE);
		x += GAIJI_TRAM_W;
		halfheart_i += 2;
	}
}

// ZUN bloat: The simple horizontal gaiji_putca() loop in all of the functions
// below could have been moved out into a separate function.

void pascal hud_static_bombs_put(pid_t pid)
{
	tram_x_t x;
	int i = 0;
	int bombs;
	tram_y_t y;
	tram_cell_amount_t step;
	if(pid == 0) {
		x = playfield_tram_x(0, (PLAYFIELD_W - GAIJI_W));
		step = -GAIJI_TRAM_W;
	} else {
		x = playfield_tram_x(1, 0);
		step = +GAIJI_TRAM_W;
	}
	y = ((PLAYFIELD_BOTTOM - GLYPH_H) / GLYPH_H);

	bombs = players[pid].bombs;
	while(i < bombs) {
		gaiji_putca(x, y, gs_BOMB, TX_WHITE);
		x += step;
		i++;
	}

	// In case we lost a single bomb on this frame… Very clever!
	gaiji_putca(x, y, g_SP, TX_WHITE);
}

void pascal near hud_static_rounds_won_put(pid_t pid)
{
	tram_x_t x;
	int i = 0;
	if(pid == 0) {
		x = playfield_tram_x(0, 0);
	} else {
		x = playfield_tram_x(1, 0);
	}

	int rounds_won = players[pid].rounds_won;
	while(i < rounds_won) {
		gaiji_putca(x, PLAYFIELD_TRAM_TOP, gs_THALIA, TX_WHITE);
		x += GAIJI_TRAM_W;
		i++;
	}
}

void near hud_static_story_lives_put(void)
{
	int i = 0;
	tram_x_t x = playfield_tram_x(0, (PLAYFIELD_W - GAIJI_W));
	int lives = resident->story_lives;
	while(i < lives) {
		gaiji_putca(x, (PLAYFIELD_TRAM_TOP + 1), gs_YINYANG, TX_WHITE);
		x -= GAIJI_TRAM_W;
		i++;
	}
}

void pascal hud_static_gauge_levels_put(pid2 pid)
{
	int level;
	tram_x_t x = playfield_tram_x(0, 0);
	if(pid != 0) {
		x += (PLAYFIELD_W_BORDERED / GLYPH_HALF_W);
	}

	level = gauge_attack_level[pid];
	gaiji_putca(x, (PLAYFIELD_BOTTOM / GLYPH_H), (gpd_1 - 1 + level), TX_GREEN);
	x += ((PLAYFIELD_W / GLYPH_HALF_W) - GAIJI_TRAM_W);

	// This branch seems to confirm the interpretation that these digits
	// display the *next* Boss Attack level, not the current one. If the level
	// is already at the maximum, additional attacks won't increase it further.
	level = boss_attack_level;
	if(level >= BOSS_ATTACK_LEVEL_MAX) {
		// A bit brave to assume that [level] will never be greater than
		// [BOSS_ATTACK_LEVEL_MAX]. On the other hand, it's great for debugging
		// as any invalid state would render as a non-proportional-digit gaiji.
		level--;
	}
	gaiji_putca(x, (PLAYFIELD_BOTTOM / GLYPH_H), (gpd_1 + level), TX_RED);
}

void hud_static_put(void)
{
	for(int i = 0; i < PLAYER_COUNT; i++) {
		hud_static_halfhearts_put(i);
		hud_static_bombs_put(i);
		hud_static_rounds_won_put(i);
		hud_static_gauge_levels_put(i);
	}
	if(resident->game_mode == GM_STORY) {
		hud_static_story_lives_put();
	}
}
