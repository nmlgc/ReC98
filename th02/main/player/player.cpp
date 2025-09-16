#pragma option -G

#include "th02/main/player/player.hpp"
#include "th02/main/player/shot.hpp"
#include "th02/main/hud/hud.hpp"
#include "th02/main/item/item.hpp"
#include "th02/main/main.hpp"
#include "th02/main/playperf.hpp"
#include "th02/main/score.hpp"
#include "th02/main/scroll.hpp"
#include "th02/main/spark.hpp"
#include "th02/snd/snd.h"
#include "th02/resident.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

// Coordinates
// -----------

static const screen_x_t PLAYER_LEFT_MIN = (PLAYFIELD_LEFT - 4);
static const screen_x_t PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - (PLAYER_W - 6));
static const screen_y_t PLAYER_TOP_MIN = PLAYFIELD_TOP;
static const screen_y_t PLAYER_TOP_MAX = (PLAYFIELD_BOTTOM - (PLAYER_H - 8));
// -----------

extern int player_patnum; // ACTUAL TYPE: main_patnum_t

// Function ordering fails
// -----------------------

void near player_miss_update_and_render(void);
// -----------------------

#define negate_hits_if_invincible() { \
	if(player_invincible_via_bomb || ( \
		player_invincibility_time && !miss_active \
	)) { \
		player_is_hit = PLAYER_NOT_HIT; \
	} \
}

void pascal near player_move(pixel_t delta_x, pixel_t delta_y)
{
	player_topleft.y = *player_top_on_back_page;
	player_topleft.y += delta_y;
	if(player_topleft.y < PLAYER_TOP_MIN) {
		player_topleft.y = PLAYER_TOP_MIN;
	} else if(player_topleft.y > PLAYER_TOP_MAX) {
		player_topleft.y = PLAYER_TOP_MAX;
	}
	*player_top_on_back_page = player_topleft.y;

	// ZUN bloat: Could have been abstracted away if the comparison order and
	// operator were consistent...
	player_topleft.x = *player_left_on_back_page;
	player_topleft.x += delta_x;
	if(player_topleft.x >= PLAYER_LEFT_MAX) {
		player_topleft.x = PLAYER_LEFT_MAX;
	} else if(player_topleft.x <= PLAYER_LEFT_MIN) {
		player_topleft.x = PLAYER_LEFT_MIN;
	}
	*player_left_on_back_page = player_topleft.x;
}

void near player_update_and_render(void)
{
	// Update
	// ------

	negate_hits_if_invincible();
	if(player_invincibility_time > 0) {
		player_invincibility_time--;
	}

	shots_update_and_render();

	if(player_is_hit) {
		player_miss_update_and_render();
		if(player_is_hit == PLAYER_HIT_GAMEOVER) {
			quit = true;
			player_is_hit = PLAYER_NOT_HIT;
		}
		return;
	}
	// ------

	// Render
	// ------

	vram_y_t vram_top;
	if((player_invincibility_time & 3) < 3) {
		vram_top = scroll_screen_y_to_vram(vram_top, player_topleft.y);
		super_roll_put(player_topleft.x, vram_top, player_patnum);
	}
	if(power >= 8) {
		// ZUN bloat: Repeats the dereferencing every time it's used. (Yes, not
		// just the wordy name I chose for this variable!)
		#define option_left_left *player_option_left_left_on_back_page

		vram_top = scroll_screen_y_to_vram(
			vram_top, *player_option_left_top_on_back_page
		);
		super_roll_put_tiny(option_left_left, vram_top, player_option_patnum);
		super_roll_put_tiny(
			(option_left_left + PLAYER_OPTION_TO_OPTION_DISTANCE),
			vram_top,
			player_option_patnum
		);

		#undef option_left_left
	}
	// ------
}

inline void player_miss_sparks_add(int count) {
	// ZUN bug: Should subtract half the spark size to actually center them.
	sparks_add(
		(*player_left_on_back_page + (PLAYER_W / 2)),
		(*player_top_on_back_page  + (PLAYER_H / 2)),
		to_sp(8.0f),
		count,
		true
	);
}

void near player_miss_update_and_render(void)
{
	enum {
		KEYFRAME_PLAYCHAR_ANIM = 0,
		KEYFRAME_PLAYCHAR_ANIM_DONE = 24,
		KEYFRAME_RESPAWN = 43,
		KEYFRAME_RESPAWN_DONE = 68,

		PLAYCHAR_ANIM_FRAMES = (
			KEYFRAME_PLAYCHAR_ANIM_DONE - KEYFRAME_PLAYCHAR_ANIM
		),
	};

	if(miss_frames == 0) {
		snd_se_play(2);
		miss_active = true;
		stage_miss_count++;

		// ZUN bug: The fact that this function does not re-render the score
		// means that any existing [score_delta] will stop being animated. The
		// score display will therefore only refresh with the correct value
		// after the player gained another point.
		/* TODO: Replace with the decompiled call
		 * 	score_delta_commit();
		 * once that function is part of the same segment */
		_asm { nop; push cs; call near ptr score_delta_commit; }

		total_miss_count++;
		player_miss_sparks_add(16);
	}

	player_topleft.x = *player_left_on_back_page;
	player_topleft.y = *player_top_on_back_page;
	miss_frames++;
	if(miss_frames < KEYFRAME_PLAYCHAR_ANIM_DONE) {
		static_assert(PLAYCHAR_ANIM_FRAMES == (MISS_ANIM_CELS * 4));

		// ACTUAL TYPE: main_patnum_t
		int patnum = (PAT_PLAYCHAR_MISS + (miss_frames >> 2));

		vram_y_t vram_top = scroll_screen_y_to_vram(
			vram_top, *player_top_on_back_page
		);
		super_roll_put(*player_left_on_back_page, vram_top, patnum);
	} else if(miss_frames == KEYFRAME_PLAYCHAR_ANIM_DONE) {
		player_invincibility_time = MISS_INVINCIBILITY_FRAMES;
		if(playperf > 2) {
			playperf = 0;
		} else {
			playperf -= 2;
			if(playperf < playperf_min) {
				playperf = playperf_min;
			}
		}
		player_miss_sparks_add(32);
		if(lives == 0) {
			miss_frames = 0;
			items_miss_add_gameover = true;

			// ZUN quirk: Not centered
			items_miss_add(*player_left_on_back_page, *player_top_on_back_page);

			items_miss_add_gameover = false;
			player_is_hit = PLAYER_HIT_GAMEOVER;
		} else {
			extern const uint8_t POWER_RESET_FOR[SHOT_LEVEL_MAX + 1];
			power = POWER_RESET_FOR[shot_level];
			player_shot_level_update_and_hud_power_put();

			// ZUN quirk: Not centered
			items_miss_add(*player_left_on_back_page, *player_top_on_back_page);
		}
	} else if(miss_frames < KEYFRAME_RESPAWN) {
		// ZUN quirk: The only "death-induced hitbox shifting" that actually
		// exists in the code. (The infamous one during the Extra Stage midboss
		// is just players elevating happy collision detection accidents to a
		// "safespot" while disregarding the much more obvious effect of rank
		// on patterns; see
		//
		// 	https://rec98.nmlgc.net/blog/2025-02-24#myth-2025-02-24
		//
		// for documentation.
		//
		// This does have gameplay impact as the player's position continues to
		// be used for collision detection, and thus, potential entity removal.
		// Also, this can and will move the player past [PLAYER_TOP_MAX] if the
		// death occurred low enough.
		*player_top_on_back_page += 4;
	} else if(miss_frames == KEYFRAME_RESPAWN) {
		lives--;
		hud_lives_put();

		bombs = resident->start_bombs;
		if(lives == 0) {
			bombs += 2;
		}
		hud_bombs_put();

		// ZUN quirk: If the additions between [KEYFRAME_PLAYCHAR_ANIM_DONE]
		// and [KEYFRAME_RESPAWN] moved the player's Y position below [RES_Y],
		// the sparks spawned here will get wrapped back into the VRAM area and
		// seemingly strangely appear near the top of the playfield.
		// See sparks_add()'s implementation for why this actually is a quirk
		// and not a bug.
		player_miss_sparks_add(16);

		player_left_on_page[1] = player_left_on_page[0] = PLAYER_LEFT_START;
		player_top_on_page[1] = player_top_on_page[0] = (
			((PLAYFIELD_BOTTOM + PLAYFIELD_ROLL_MARGIN) - PLAYER_H) - 2
		);
	} else if(miss_frames < KEYFRAME_RESPAWN_DONE) {
		*player_top_on_back_page -= 2;
		vram_y_t vram_top = scroll_screen_y_to_vram(
			vram_top, *player_top_on_back_page
		);
		super_roll_put(*player_left_on_back_page, vram_top, PAT_PLAYCHAR_STILL);
	} else {
		miss_frames = 0;
		miss_active = false;
		player_is_hit = PLAYER_NOT_HIT;
	}
}
