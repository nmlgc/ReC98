/* ReC98 / TH05
 * ------------
 * Rendering code for all bosses
 */

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/vector.hpp"
#include "th04/main/drawp.hpp"
#include "th04/main/playfld.h"

/// Structures
/// ----------
#define BOSS_PARTICLE_COUNT 64
#define LINESET_LINE_COUNT 20
#define LINESET_COUNT 4

// `boss_` to differentiate this structure from `s2particle_t`, which uses the
// same sprites.
struct boss_particle_t {
	SPPoint pos; // [x] == Subpixel::None() indicates a dead particle

	// [pos] is reset to this value once it has left the playfield, restarting
	// the particle movement.
	SPPoint origin;

	SPPoint velocity;
	int age;
	unsigned char angle;
	unsigned char patnum;	// if 0, calculated from [age] during rendering
};

// Each final rendered line effectively corresponds to the diameter of the
// described circle, with the two line points at +[angle] and -[angle].
struct lineset_t {
	SPPoint center[LINESET_LINE_COUNT];
	Subpixel velocity_y;
	Subpixel radius[LINESET_LINE_COUNT];
	unsigned char angle[LINESET_LINE_COUNT];
};

extern boss_particle_t boss_particles[BOSS_PARTICLE_COUNT];
extern lineset_t linesets[LINESET_COUNT];
/// ----------

// Draws the given line out of [set] with the current GRCG tile and color.
void pascal near grcg_lineset_line_put(lineset_t near &set, int i)
{
	vector2_at(drawpoint,
		set.center[i].x, set.center[i].y, set.radius[i], set.angle[i]
	);
	screen_x_t x1 = (PLAYFIELD_LEFT + drawpoint.x.to_pixel());
	screen_y_t y1 = (PLAYFIELD_TOP  + drawpoint.y.to_pixel());

	vector2_at(drawpoint,
		set.center[i].x, set.center[i].y, set.radius[i], (set.angle[i] + 0x80)
	);
	screen_x_t x2 = (PLAYFIELD_LEFT + drawpoint.x.to_pixel());
	screen_y_t y2 = (PLAYFIELD_TOP  + drawpoint.y.to_pixel());

	grcg_line(x1, y1, x2, y2);
}

// Copies lines [0; 17] to lines [1..18].
void pascal near lineset_forward_copy(lineset_t near &set)
{
	for(int i = (LINESET_LINE_COUNT - 2); i > 0; i--) {
		set.center[i] = set.center[i - 1];
		set.angle[i] = set.angle[i - 1];
		set.radius[i].v = set.radius[i - 1].v;
	}
}
