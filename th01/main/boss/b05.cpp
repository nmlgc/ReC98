/// Stage 5 Boss - SinGyoku
/// -----------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/formats/pf.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#define boss_hp	singyoku_hp
#define boss_phase_frame	singyoku_phase_frame
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"

// Entities
// --------

static const int SPHERE_CELS = 8;

#define ent_sphere \
	reinterpret_cast<CBossEntitySized<SINGYOKU_W, SINGYOKU_H> &>( \
		boss_entities[0] \
	)

inline void singyoku_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
}

// And that's how you avoid the entity position synchronization code that
// plagues Elis: By simply only using a single set of coordinates.
#define ent ent_sphere

#define ent_unput_and_put(ent_with_cel, cel) { \
	ent_with_cel.unput_and_put_8(ent.cur_left, ent.cur_top, cel); \
}
// --------

// Patterns
// --------

#define pattern_state	singyoku_pattern_state
extern union {
	int pellet_count;
	pixel_t speed_in_pixels;
	subpixel_t speed_in_subpixels;
	int unknown;
} pattern_state;
// --------

#define flash_colors	singyoku_flash_colors
#define invincible	singyoku_invincible
#define invincibility_frame	singyoku_invincibility_frame
#define initial_hp_rendered	singyoku_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool16 initial_hp_rendered;

void singyoku_free(void)
{
	singyoku_ent_free();
}

// Rotates the sphere by the given [cel_delta]. [interval] could be used to
// restrict this function to certain [boss_phase_frame] intervals, but it's
// always either 1 or -1 in the original game.
void sphere_rotate_and_render(int interval, int cel_delta)
{
	if((boss_phase_frame % interval) != 0) {
		return;
	}

	// Yeah, why is the CBossEntity image variable 16 bits anywhere else to
	// begin with?
	int8_t image_new = (ent_sphere.image() + cel_delta);
	if(image_new > (SPHERE_CELS - 1)) {
		image_new = 0;
	} else if(image_new < 0) {
		image_new = (SPHERE_CELS - 1);
	}

	ent_sphere.set_image(image_new);
	ent_unput_and_put(ent_sphere, image_new);
}

#define select_for_rank singyoku_select_for_rank
#include "th01/main/select_r.cpp"
