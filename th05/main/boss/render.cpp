/* ReC98 / TH05
 * ------------
 * Rendering code for all bosses
 */

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/vector.hpp"
#include "th04/math/motion.hpp"
#include "th04/math/randring.h"
#include "th04/main/drawp.hpp"
#include "th04/main/playfld.hpp"
#include "th05/main/boss/boss.hpp"

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

/// Stage 6 - Shinki
/// ----------------

static const int SHINKI_LINESET_COUNT = 2;
static const int PARTICLES_UNINITIALIZED = (-1 & 0xFF);

extern unsigned char shinki_bg_linesets_zoomed_out;
extern int shinki_bg_type_a_particles_alive;

void near shinki_bg_type_a_update_part1(void)
{
	boss_particle_t near *particle;
	int i;
	unsigned int angle;
	int line_i;
	lineset_t near *set;

	if(shinki_bg_type_a_particles_alive == PARTICLES_UNINITIALIZED) {
		set = linesets;
		i = 0;
		angle = 0x40;
		while(i < SHINKI_LINESET_COUNT) {
			for(line_i = 0; line_i < LINESET_LINE_COUNT; line_i++) {
				set->center[line_i].x.v = to_sp(PLAYFIELD_W / 2);
				set->center[line_i].y.v = to_sp(PLAYFIELD_H / 2);
				set->radius[line_i].set(1.0f);
				set->angle[line_i] = angle;
			}
			i++;
			set++;
			angle -= 0x80;
		}

		particle = boss_particles;
		i = 0;
		while(i < BOSS_PARTICLE_COUNT) {
			particle->pos.x.v = Subpixel::None();
			particle->patnum = 0;
			i++;
			particle++;
		}
		shinki_bg_type_a_particles_alive = 0;
	}
	if(shinki_bg_type_a_particles_alive < BOSS_PARTICLE_COUNT) {
		if(((boss.phase_frame % 4) == 0) == true) {
			particle = &boss_particles[shinki_bg_type_a_particles_alive];
			particle->pos.set((PLAYFIELD_W / 2), (PLAYFIELD_H / 2));
			particle->origin.set((PLAYFIELD_W / 2), (PLAYFIELD_H / 2));
			particle->angle = randring1_next16();
			particle->age = 0;
			vector2_at(
				particle->velocity,
				0.0f, 0.0f,
				(randring1_next16_and(to_sp(4.0f) - 1) + to_sp(2.0f)),
				particle->angle
			);
			shinki_bg_type_a_particles_alive++;
		}
	}
	if(boss.phase == 3) {
		if((shinki_bg_linesets_zoomed_out % (SHINKI_LINESET_COUNT * 2)) < 2) {
			linesets[0].angle[0] += 0x02;
			linesets[1].angle[0] += 0x02;
		} else {
			linesets[0].angle[0] -= 0x02;
			linesets[1].angle[0] -= 0x02;
		}
	}
	#undef PARTICLES_UNINITIALIZED
}

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
/// ----------------
