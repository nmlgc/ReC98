#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/hardware/graph.h"
#include "th01/main/playfld.hpp"
#include "th01/main/bullet/line.hpp"
#include "th01/main/player/player.hpp"

// Translation: 62 pixels on the X axis, centered around [right], 16 pixels
// below [bottom], and extending infinitely far up.
#define hittest(left, top, right, bottom) { \
	if( \
		(right > player_left) && \
		(right < player_right()) && \
		(bottom > player_center_y()) && \
		!player_invincible \
	) { \
		player_is_hit = true; \
	} \
}

void linebullet_unput(
	screen_x_t left, screen_y_t top, screen_x_t right, screen_y_t bottom
)
{
	graph_r_line_unput(left, top, right, bottom);
}

void linebullet_put_and_hittest(
	screen_x_t left,
	screen_y_t top,
	screen_x_t right,
	screen_y_t bottom,
	int col
)
{
	graph_r_line(left, top, right, bottom, col);
	hittest(left, top, right, bottom);
}

void linebullet_put_patterned_and_hittest(
	screen_x_t left,
	screen_y_t top,
	screen_x_t right,
	screen_y_t bottom,
	int col,
	dots16_t pattern
)
{
	graph_r_line_patterned(left, top, right, bottom, col, pattern);
	hittest(left, top, right, bottom);
}
