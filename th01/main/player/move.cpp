#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"

void player_move_and_clamp(int delta)
{
	player_left += delta;
	if(player_left < PLAYER_LEFT_MIN) {
		player_left = PLAYER_LEFT_MIN;
	} else if(player_left >= PLAYER_LEFT_MAX) {
		player_left = PLAYER_LEFT_MAX;
	}
}
