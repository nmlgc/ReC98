#include "th04/main/player/player.hpp"

// Calculates the angle from ([x], [y]) to the current player position, and
// optionally adds [plus_angle] to the result.
unsigned char pascal near player_angle_from(
	Subpixel x, Subpixel y, unsigned char plus_angle = 0
);

inline unsigned char near player_angle_from(
	const PlayfieldPoint &point, unsigned char plus_angle = 0
) {
	return player_angle_from(point.x, point.y, plus_angle);
}
