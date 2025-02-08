#include "th02/main/player/player.hpp"
#include "th02/main/player/shot.hpp"
#include "th02/main/main.hpp"
#include "th02/main/scroll.hpp"
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
