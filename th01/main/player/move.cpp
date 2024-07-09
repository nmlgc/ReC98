#include "th01/main/player/player.hpp"

// Global state that is defined here for some reason
// -------------------------------------------------

bool player_invincible_against_orb = false;
// -------------------------------------------------

void player_move_and_clamp(pixel_t delta)
{
	player_left += delta;
	if(player_left < PLAYER_LEFT_MIN) {
		player_left = PLAYER_LEFT_MIN;
	} else if(player_left >= PLAYER_LEFT_MAX) {
		player_left = PLAYER_LEFT_MAX;
	}
}
