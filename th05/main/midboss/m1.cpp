/// Stage 1 midboss
/// ---------------

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/vector.hpp"
#include "th04/main/playfld.hpp"
}
#include "th04/main/midboss/midboss.hpp"

// State
// -----

#define distance_from_center midboss.pos.velocity.x
// -----

void near midboss1_move(void)
{
	midboss.pos.prev.x = midboss.pos.cur.x;
	midboss.pos.prev.y = midboss.pos.cur.y;

	midboss.pos.cur.x.v = vector1_at(
		to_sp(playfield_fraction_x(1 / 2.0f)),
		distance_from_center,
		CosTable8[midboss.angle]
	);
	midboss.pos.cur.y.v = vector1_at(
		to_sp(playfield_fraction_y(6 / 23.0f)),
		distance_from_center,
		SinTable8[midboss.angle]
	);
	midboss.angle -= 0x02;
}
