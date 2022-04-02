/* ReC98 / TH05
 * ------------
 * Rendering code for all bosses
 */

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "master.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th04/hardware/grcg.h"
#include "th04/math/vector.hpp"
#include "th04/math/motion.hpp"
#include "th04/math/randring.h"
#include "th04/formats/bb.h"
#include "th04/formats/cdg.h"
#include "th04/main/frames.h"
#include "th04/main/playfld.hpp"
#include "th04/main/phase.hpp"
#include "th04/main/drawp.hpp"
#include "th04/main/tile/bb.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/sprites/main_cdg.h"
#include "th05/sprites/main_pat.h"
#include "th05/formats/super.h"
}
#include "th05/main/boss/boss.hpp"
#include "th05/main/boss/bosses.hpp"

/// Structures
/// ----------
#define BOSS_PARTICLE_COUNT 64
#define LINESET_LINE_COUNT 20
#define LINESET_COUNT 4

// `boss_` to differentiate this structure from `s2particle_t`, which uses the
// same sprites.
struct boss_particle_t {
	PlayfieldPoint pos; // [x] == Subpixel::None() indicates a dead particle

	// [pos] is reset to this value once it has left the playfield, restarting
	// the particle movement.
	PlayfieldPoint origin;

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

#define SHINKI_SPINLINE_MOVE_W (PLAYFIELD_W / 6) /* pixel_t! */
#define SHINKI_SPINLINE_MOVE_SPEED to_sp(0.25f)
#define SHINKI_SPINLINE_TOP to_sp(80.0f)
#define SHINKI_SPINLINE_BOTTOM to_sp(PLAYFIELD_H - 64)
#define SHINKI_SPINLINE_MOVE_DURATION \
	(SHINKI_SPINLINE_MOVE_W * SHINKI_SPINLINE_MOVE_SPEED)

static const int SHINKI_LINESET_COUNT = 2;
static const int PARTICLES_UNINITIALIZED = (-1 & 0xFF);

// Maps one of Shinki's four visible lines to its index in a line set.
static const int SHINKI_LINE_MAIN = (0 * 6);
static const int SHINKI_LINE_2 = (1 * 6);
static const int SHINKI_LINE_3 = (2 * 6);
static const int SHINKI_LINE_4 = (3 * 6);

extern unsigned char shinki_bg_linesets_zoomed_out;
extern int shinki_bg_type_a_particles_alive;
extern bool shinki_bg_type_b_initialized;
extern unsigned int shinki_bg_spinline_frames;
extern bool shinki_bg_type_c_initialized;
extern bool shinki_bg_type_d_initialized;

#define shinki_spinline_x_and_angle(set, delta) \
	if(set->radius[SHINKI_LINE_MAIN] > to_sp(96.0f)) { \
		set->radius[SHINKI_LINE_MAIN] -= 0.125f; \
	} \
	if( \
		(shinki_bg_spinline_frames & ( \
			(SHINKI_SPINLINE_MOVE_DURATION * 2) - 1) \
		) < SHINKI_SPINLINE_MOVE_DURATION \
	) { \
		set->center[SHINKI_LINE_MAIN].x.v += delta; \
	} else { \
		set->center[SHINKI_LINE_MAIN].x.v -= delta; \
	} \
	set->angle[SHINKI_LINE_MAIN] += (delta / 2);

#define shinki_spinline_y_formation_top(set, delta, set_i, line_i) \
	delta = (SHINKI_SPINLINE_TOP - set->center[SHINKI_LINE_MAIN].y); \
	set_i = 0; \
	while(set_i < SHINKI_LINESET_COUNT) { \
		for(line_i = SHINKI_LINE_4; line_i >= 0; line_i--) { \
			set->center[line_i].y.v += delta; \
		} \
		set_i++; \
		set++; \
	}

#define shinki_spinline_y_formation_bottom(set, delta, set_i, line_i) \
	delta = (set->center[SHINKI_LINE_MAIN].y - SHINKI_SPINLINE_BOTTOM); \
	set_i = 0; \
	while(set_i < SHINKI_LINESET_COUNT) { \
		for(line_i = SHINKI_LINE_4; line_i >= 0; line_i--) { \
			set->center[line_i].y.v -= delta; \
		} \
		set_i++; \
		set++; \
	}

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
			left_ = particle->pos.to_screen_left(PARTICLE_W);
			top = particle->pos.to_screen_top(PARTICLE_H);
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
}

// Draws the given line out of [set] with the current GRCG tile and color.
void pascal near grcg_lineset_line_put(lineset_t near &set, int i)
{
	vector2_at(drawpoint,
		set.center[i].x, set.center[i].y, set.radius[i], set.angle[i]
	);
	screen_x_t x1 = drawpoint.to_screen_left();
	screen_y_t y1 = drawpoint.to_screen_top();

	vector2_at(drawpoint,
		set.center[i].x, set.center[i].y, set.radius[i], (set.angle[i] + 0x80)
	);
	screen_x_t x2 = drawpoint.to_screen_left();
	screen_y_t y2 = drawpoint.to_screen_top();

	grcg_line(x1, y1, x2, y2);
}

// Copies lines [0..17] to lines [1..18].
void pascal near shinki_lineset_forward_copy(lineset_t near &set)
{
	for(int i = SHINKI_LINE_4; i > 0; i--) {
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
		shinki_lineset_forward_copy(*set);
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

void near shinki_bg_type_b_update_part1(void)
{
	boss_particle_t near *particle;
	int i;
	subpixel_t center_x;
	int line_i;
	lineset_t near *set;

	if(!shinki_bg_type_b_initialized) {
		center_x = to_sp(playfield_fraction_x(1 / 6.0f));
		set = linesets;
		i = 0;
		while(i < SHINKI_LINESET_COUNT) {
			for(line_i = SHINKI_LINE_4; line_i >= 0; line_i--) {
				set->center[line_i].x.v = center_x;
				set->center[line_i].y.v = to_sp((PLAYFIELD_H / 2) + 32);
				set->radius[line_i].set(256.0f);
				set->angle[line_i] = 0x40;
			}
			set->velocity_y.set(0.0f);
			i++;
			set++;
			center_x += to_sp(playfield_fraction_x(4 / 6.0f));
		}
		particle = boss_particles;
		i = 0;
		while(i < BOSS_PARTICLE_COUNT) {
			particle->pos.x.v = randring1_next16_mod(to_sp(PLAYFIELD_W));
			// Huh? Not PLAYFIELD_H?
			particle->pos.y.v = randring1_next16_mod(to_sp(PLAYFIELD_W));
			particle->origin.x = particle->pos.x;
			particle->origin.y.set(-1.0f);
			particle->velocity.set(0.0f, 0.0f);
			particle->patnum = (
				PAT_PARTICLE + randring1_next16_and(PARTICLE_CELS - 1)
			);
			i++;
			particle++;
		}
		shinki_bg_type_b_initialized++;
		return;
	}

	particle = boss_particles;
	i = 0;
	while(i < BOSS_PARTICLE_COUNT) {
		if(particle->velocity.y < to_sp(10.0f)) {
			particle->velocity.y.v += stage_frame_mod2;
		}
		i++;
		particle++;
	}
}

// Particles: Blue, at random X positions, falling down
// Lines: Spinning and horizontally shifting at both sides of Shinki's wings,
//        starting near the center of the playfield, moving up to
//        [SHINKI_SPINLINE_TOP], and then pushed *down* into a vertical
//        formation, until the set has reached its target velocity.
void near shinki_bg_type_b_update_and_render(void)
{
	// MODDERS: Just fuse into this function.
	shinki_bg_type_b_update_part1();

	lineset_t near *set;
	int set_i;
	subpixel_t delta;
	int line_i;

	delta = SHINKI_SPINLINE_MOVE_SPEED;
	set = linesets;
	set_i = 0;
	while(set_i < SHINKI_LINESET_COUNT) {
		shinki_lineset_forward_copy(*set);
		set->center[SHINKI_LINE_MAIN].y.v += set->velocity_y.v;
		if(set->velocity_y > to_sp(-14.0f)) {
			set->velocity_y.v -= (
				(stage_frame_mod4 == 0) ? to_sp(0.0625f) : to_sp(0.0f)
			);
		}
		shinki_spinline_x_and_angle(set, delta);

		set_i++;
		set++;
		delta = -delta;
	}

	shinki_bg_spinline_frames++;

	set = linesets;
	if(set->center[SHINKI_LINE_MAIN].y < SHINKI_SPINLINE_TOP) {
		shinki_spinline_y_formation_top(set, delta, set_i, line_i);
	}

	shinki_bg_render_blue_particles_and_lines();
}

void near shinki_bg_type_c_update_part1(void)
{
	boss_particle_t near *particle;
	int i;

	if(!shinki_bg_type_c_initialized) {
		particle = boss_particles;
		if(particle->velocity.y < to_sp(0.0f)) {
			i = 0;
			while(i < BOSS_PARTICLE_COUNT) {
				particle->origin.y.set(PLAYFIELD_H + 1.0f);
				i++;
				particle++;
			}
			shinki_bg_type_c_initialized++;
		}
	}

	particle = boss_particles;
	i = 0;
	while(i < BOSS_PARTICLE_COUNT) {
		if(particle->velocity.y.v > to_sp(-10.0f)) {
			particle->velocity.y.v -= stage_frame_mod2;
		}
		i++;
		particle++;
	}
}

// Particles: Blue, keeping their random X positions from type B, rising
// Lines: Moving back up to [SHINKI_SPINLINE_TOP], starting at the Y velocity
//        they had from the previous background type. Then, moving down to
//        [SHINKI_SPINLINE_BOTTOM], and then pushed *up* into a vertical
//        formation, until the set has reached its target velocity.
void near shinki_bg_type_c_update_and_render(void)
{
	// MODDERS: Just fuse into this function.
	shinki_bg_type_c_update_part1();

	lineset_t near *set;
	int set_i;
	subpixel_t delta;
	int line_i;

	delta = SHINKI_SPINLINE_MOVE_SPEED;
	set = linesets;
	set_i = 0;
	while(set_i < SHINKI_LINESET_COUNT) {
		shinki_lineset_forward_copy(*set);
		set->center[SHINKI_LINE_MAIN].y.v += set->velocity_y.v;
		if(set->velocity_y < to_sp(14.0f)) {
			set->velocity_y.v += stage_frame_mod2;
		}
		shinki_spinline_x_and_angle(set, delta);

		set_i++;
		set++;
		delta = -delta;
	}

	shinki_bg_spinline_frames++;

	set = linesets;
	// [velocity_y] is still negative from type B in the beginning. Continue
	// applying friction until [velocity_y] gets positive again
	if(set->center[SHINKI_LINE_MAIN].y < SHINKI_SPINLINE_TOP) {
		shinki_spinline_y_formation_top(set, delta, set_i, line_i);
	} else if(set->center[SHINKI_LINE_MAIN].y > SHINKI_SPINLINE_BOTTOM) {
		shinki_spinline_y_formation_bottom(set, delta, set_i, line_i);
	}

	shinki_bg_render_blue_particles_and_lines();
}

// Rising "smoke" particles.
void near shinki_bg_type_d_update(void)
{
	boss_particle_t near *particle;
	int i;

	if(!shinki_bg_type_d_initialized) {
		particle = boss_particles;
		i = 0;
		while(i < BOSS_PARTICLE_COUNT) {
			particle->origin.y.v = to_sp(SHINKI_TYPE_D_BACKDROP_TOP);
			particle->velocity.y.set(-1.0f);
			i++;
			particle++;
		}
		shinki_bg_type_d_initialized++;
	}

	particle = boss_particles;
	i = 0;
	while(i < BOSS_PARTICLE_COUNT) {
		int cel = ((PARTICLE_CELS - 1) - (particle->pos.y.v / to_sp(64.0f)));
		if(cel < 0) {
			cel = 0;
		}
		particle->patnum = (PAT_PARTICLE + cel);
		i++;
		particle++;
	}
}

void pascal near shinki_bg_render(void)
{
	if(boss.phase == PHASE_BOSS_HP_FILL) {
		boss_backdrop_render(PLAYFIELD_LEFT, SHINKI_STAGE_BACKDROP_TOP, 1);
	} else if(boss.phase == PHASE_BOSS_ENTRANCE_BB) {
		unsigned char entrance_cel = (boss.phase_frame / 4);
		if(entrance_cel < TILES_BB_CELS) {
			boss_backdrop_render(PLAYFIELD_LEFT, SHINKI_STAGE_BACKDROP_TOP, 1);
		} else {
			boss_bg_fill_col_0();
		}
		tiles_bb_col = 15;
		tiles_bb_put(bb_boss_seg, entrance_cel);
	} else if(boss.phase < 4) {
		boss_bg_fill_col_0();
		shinki_bg_type_a_update_and_render();
	} else if(boss.phase < 8) {
		boss_bg_fill_col_0();
		shinki_bg_type_b_update_and_render();
	} else if(boss.phase < 12) {
		boss_bg_fill_col_0();
		shinki_bg_type_c_update_and_render();
	} else {
		playfield_bg_put(0, SHINKI_TYPE_D_BACKDROP_TOP, CDG_BG_2);
		shinki_bg_type_d_colorfill();
		shinki_bg_type_d_update();

		grcg_setcolor(GC_RMW, 6);
		shinki_bg_particles_render();
		grcg_off();
	}
}
/// ----------------

/// Extra Stage - EX-Alice
/// ----------------------

static const screen_x_t HEXAGRAM_CENTER_X = (
	PLAYFIELD_LEFT + (PLAYFIELD_W / 2)
);
static const vram_y_t HEXAGRAM_CENTER_Y = (PLAYFIELD_TOP + (PLAYFIELD_H / 2));

#define exalice_hexagram_point_set(ret, radius, angle) \
	vector2_at( \
		ret, to_sp(HEXAGRAM_CENTER_X), to_sp(HEXAGRAM_CENTER_Y), radius, angle \
	)

void pascal near exalice_grcg_hexagram_put(subpixel_t radius, int angle)
{
	#define tri_point_0 drawpoint
	extern SPPoint tri_point_1;
	extern SPPoint tri_point_2;

	grcg_circle(HEXAGRAM_CENTER_X, HEXAGRAM_CENTER_Y, TO_PIXEL(radius));
	int i = 0;
	while(i < 2) {
		exalice_hexagram_point_set(tri_point_0, radius, angle);
		exalice_hexagram_point_set(tri_point_1, radius, (angle + (0x100 / 3)));
		exalice_hexagram_point_set(tri_point_2, radius, (angle - (0x100 / 3)));

		TO_PIXEL_INPLACE(tri_point_0.x.v);
		TO_PIXEL_INPLACE(tri_point_0.y.v);
		TO_PIXEL_INPLACE(tri_point_1.x.v);
		TO_PIXEL_INPLACE(tri_point_1.y.v);
		TO_PIXEL_INPLACE(tri_point_2.x.v);
		TO_PIXEL_INPLACE(tri_point_2.y.v);

		grcg_line(
			tri_point_0.x.v, tri_point_0.y.v, tri_point_1.x.v, tri_point_1.y.v
		);
		grcg_line(
			tri_point_1.x.v, tri_point_1.y.v, tri_point_2.x.v, tri_point_2.y.v
		);
		grcg_line(
			tri_point_0.x.v, tri_point_0.y.v, tri_point_2.x.v, tri_point_2.y.v
		);

		i++;
		angle += (0x100 / 6);
	}

	#undef tri_point_0
}

void near exalice_hexagrams_update_and_render(void)
{
	enum exalice_hexagrams_state_t {
		UNINITIALIZED = 0,
		TURN_RIGHT = 1,
		TURN_LEFT = 2,
		STATE_COUNT,
	};
	extern exalice_hexagrams_state_t exalice_hexagrams_state;
	int i;

	lineset_t near &set = linesets[0];
	if(exalice_hexagrams_state == UNINITIALIZED) {
		for(i = 0; i < (LINESET_LINE_COUNT - 1); i++) {
			set.radius[i].set(1.0f);
			set.angle[i] = 0x00;
		}
		exalice_hexagrams_state = TURN_RIGHT;
	}
	for(i = (LINESET_LINE_COUNT - 2); i > 0; i--) {
		set.radius[i] = set.radius[i - 1];
		set.angle[i] = set.angle[i - 1];
	}
	set.radius[0] += 5.0f;
	if(set.radius[0].v >= to_sp(320.0f)) {
		set.radius[0].set(1.0f);
		exalice_hexagrams_state = static_cast<exalice_hexagrams_state_t>(
			STATE_COUNT - exalice_hexagrams_state
		);
	}
	if(exalice_hexagrams_state == TURN_RIGHT) {
		set.angle[0] += 0x01;
	} else {
		set.angle[0] -= 0x01;
	}

	grcg_setcolor(GC_RMW, 8);
	exalice_grcg_hexagram_put(set.radius[18].v, set.angle[18]);
	grcg_setcolor(GC_RMW, 9);
	exalice_grcg_hexagram_put(set.radius[9].v, set.angle[9]);
	if(boss.phase < 9 || boss.phase > 12) {
		grcg_setcolor(GC_RMW, 15);
	}
	exalice_grcg_hexagram_put(set.radius[0].v, set.angle[0]);
	grcg_off();

	#undef state
}

void pascal near exalice_bg_render(void)
{
	if(boss.phase == PHASE_BOSS_HP_FILL) {
		tiles_render_after_custom_bg(boss.phase_frame);
	} else if(boss.phase == PHASE_BOSS_ENTRANCE_BB) {
		unsigned char entrance_cel = (boss.phase_frame / 4);
		boss_bg_fill_col_0();
		tiles_bb_col = 15;
		tiles_bb_put(bb_boss_seg, entrance_cel);
	} else if(boss.phase < PHASE_BOSS_EXPLODE_BIG) {
		boss_bg_fill_col_0();
		exalice_hexagrams_update_and_render();
	} else if(boss.phase == PHASE_BOSS_EXPLODE_BIG) {
		tiles_render_all();
	} else {
		tiles_render_after_custom_bg(boss.phase_frame);
	}
}
/// ----------------------
