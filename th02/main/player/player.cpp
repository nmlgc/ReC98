#include "th02/main/player/player.hpp"

// Coordinates
// -----------

static const screen_x_t PLAYER_LEFT_MIN = (PLAYFIELD_LEFT - 4);
static const screen_x_t PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - (PLAYER_W - 6));
static const screen_y_t PLAYER_TOP_MIN = PLAYFIELD_TOP;
static const screen_y_t PLAYER_TOP_MAX = (PLAYFIELD_BOTTOM - (PLAYER_H - 8));
// -----------

extern int player_patnum; // ACTUAL TYPE: main_patnum_t

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
