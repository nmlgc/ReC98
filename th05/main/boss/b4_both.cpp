/* ReC98 / TH05
 * ------------
 * Update code for Part 1 of the Stage 4 boss fight, against both Mai and Yuki
 */

#include "th04/math/vector.hpp"
#include "th05/sprites/main_pat.h"

#define mai boss
#define yuki boss2

extern y_direction_t mai_flystep_random_next_y_direction;
extern y_direction_t yuki_flystep_random_next_y_direction;

// See boss_flystep_random().
bool pascal near flystep_random(
	boss_stuff_t near &boss, int frame, y_direction_t near &next_y_direction
)
{
	flystep_random_for(
		boss,
		next_y_direction,
		6.25f,
		48,
		to_sp(BOSS_W / 2),
		to_sp(PLAYFIELD_W - (BOSS_W / 2)),
		to_sp(24.0f),
		to_sp(128.0f),
		PAT_B4_LEFT,
		PAT_B4_RIGHT,
		PAT_B4_STILL,
		frame
	);
}

bool pascal near mai_yuki_flystep_random(int frame)
{
	/*  */ flystep_random(mai,  frame, mai_flystep_random_next_y_direction);
	return flystep_random(yuki, frame, yuki_flystep_random_next_y_direction);
}
