#include "libs/master.lib/master.hpp"
#include "th05/main/player/player.hpp"

unsigned char pascal near player_angle_from(
	Subpixel x, Subpixel y, unsigned char plus_angle
)
{
	return (
		iatan2((player_pos.cur.y - y), (player_pos.cur.x - x)) + plus_angle
	);
}
