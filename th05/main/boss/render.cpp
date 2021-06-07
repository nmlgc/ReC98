/* ReC98 / TH05
 * ------------
 * Rendering code for all bosses
 */

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "decomp.hpp"
#include "master.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/hardware/grcg.h"
#include "th04/math/vector.hpp"
#include "th04/math/motion.hpp"
#include "th04/math/randring.h"
#include "th04/main/drawp.hpp"
#include "th04/main/playfld.hpp"
#include "th05/sprites/main_pat.h"
#include "th05/formats/super.h"
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

// Maps one of Shinki's four visible lines to its index in a line set.
static const int SHINKI_LINE_MAIN = (0 * 6);
static const int SHINKI_LINE_2 = (1 * 6);
static const int SHINKI_LINE_3 = (2 * 6);
static const int SHINKI_LINE_4 = (3 * 6);

extern unsigned char shinki_bg_linesets_zoomed_out;
extern int shinki_bg_type_a_particles_alive;

void near shinki_bg_particles_render(void)
{
	_ES = SEG_PLANE_B;
	boss_particle_t near *particle = boss_particles;
	int patnum;
	screen_x_t left_;
	int i = 0;
	while(i < BOSS_PARTICLE_COUNT) {
		if(particle->pos.x.v != Subpixel::None()) {
			particle->pos.x.v += particle->velocity.x.v;
			particle->pos.y.v += particle->velocity.y.v;
			if(particle->patnum == 0) {
				patnum = (particle->age / 8);
				if(patnum >= PARTICLE_CELS) {
					patnum = (PARTICLE_CELS - 1);
				}
				patnum += PAT_PARTICLE;
			} else {
				patnum = particle->patnum;
			}

			#define left	static_cast<pixel_t>(_CX)
			#define top 	static_cast<pixel_t>(_AX)

			// Lol, is this only not directly assigned to _CX because ZUN was
			// scared that the _AX assignment might overwrite _CX?
			left_ = (
				particle->pos.x.to_pixel() + PLAYFIELD_LEFT - (PARTICLE_W / 2)
			);
			top = (
				particle->pos.y.to_pixel() + PLAYFIELD_TOP - (PARTICLE_H / 2)
			);
			left = left_;
			if(!(
				(left > (PLAYFIELD_LEFT - PARTICLE_W)) &&
				(left < PLAYFIELD_RIGHT) &&
				(top > keep_0(PLAYFIELD_TOP - PARTICLE_H)) &&
				(top < PLAYFIELD_BOTTOM)
			)) {
				particle->pos = particle->origin;
				particle->age = 0;
			} else {
				z_super_roll_put_16x16_mono(left, top, patnum);
				particle->age++;
			}

			#undef top
			#undef left
		}
		i++;
		particle++;
	}
}

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

inline void shinki_bg_render_blue_particles_and_lines(void)
{
	grcg_setmode_rmw_seg1();

	grcg_setcolor_direct_seg1(8);
	shinki_bg_particles_render();
	grcg_lineset_line_put(linesets[0], SHINKI_LINE_4);
	grcg_lineset_line_put(linesets[0], SHINKI_LINE_3);
	grcg_lineset_line_put(linesets[1], SHINKI_LINE_4);
	grcg_lineset_line_put(linesets[1], SHINKI_LINE_3);

	grcg_setcolor_direct_seg1(9);
	grcg_lineset_line_put(linesets[0], SHINKI_LINE_2);
	grcg_lineset_line_put(linesets[1], SHINKI_LINE_2);

	grcg_setcolor_direct_seg1(15);
	grcg_lineset_line_put(linesets[0], SHINKI_LINE_MAIN);
	grcg_lineset_line_put(linesets[1], SHINKI_LINE_MAIN);

	grcg_off();
}

// Particles: Blue, shooting out from the center in random directions and at
//            random speeds
// Lines: Two parallel, repeatedly zooming lines that give the impression of
//        flying into a corridor, with random blue particles
void near shinki_bg_type_a_update_and_render(void)
{
	// MODDERS: Just fuse into this function.
	shinki_bg_type_a_update_part1();

	lineset_t near *set = linesets;
	int i = 0;
	while(i < SHINKI_LINESET_COUNT) {
		lineset_forward_copy(*set);
		set->radius[SHINKI_LINE_MAIN] += 4.0f;
		vector2_at(
			set->center[SHINKI_LINE_MAIN],
			to_sp(PLAYFIELD_W / 2),
			to_sp(PLAYFIELD_H / 2),
			((set->radius[SHINKI_LINE_MAIN].v * 3) / 4),
			(set->angle[SHINKI_LINE_MAIN] - 0x40)
		);
		if(set->radius[SHINKI_LINE_MAIN] >= to_sp(224.0f)) {
			shinki_bg_linesets_zoomed_out++;
			set->radius[SHINKI_LINE_MAIN].set(0.0f);
		}
		i++;
		set++;
	}
	shinki_bg_render_blue_particles_and_lines();
}
/// ----------------
