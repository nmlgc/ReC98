#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/overlap.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/grcg.hpp"
#include "th01/main/particle.hpp"

CParticles Particles;

void CParticles::init()
{
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		alive[i] = false;
	}
	spawn_interval = 2;
	velocity_base_max = 10;
}

void CParticles::unput_update_render(particle_origin_t origin, vc_t col)
{
	unsigned char i;

	// Spawn

	// ZUN bug: Should rather be done after spawning? Doing it here results in
	// the particle at slot 0 not being written on the first cycle. It also...
	spawn_cycle++;

	// ... turns the usage of > instead of >= into an off-by-one error...
	if(spawn_cycle > (spawn_interval * PARTICLE_COUNT)) {
		spawn_cycle = 0;
	}
	// ... which leads to this code still being run if [spawn_cycle] is
	// ([spawn_interval] * PARTICLE_COUNT), ...
	if((spawn_cycle % spawn_interval) == 0) {
		// ...and to [i] == PARTICLE_COUNT setting the stage for out-of-bounds
		// structure accesses.
		i = (spawn_cycle / spawn_interval);

		// Luckily, [alive[PARTICLE_COUNT]] corresponds to
		// [velocity_base[0]]. Due to the first ZUN bug in this function, this
		// value is 0 only during the first cycle, which causes actual
		// out-of-bounds accesses to only happen on one single frame.
		if(alive[i] == false) {
			alive[i] = true;
			velocity_base[i] = ((irand() % velocity_base_max) + 1);
			if((i % 2) == 0) {
				switch(origin) {
				case PO_TOP:
				case PO_TOP_RIGHT:
				case PO_TOP_LEFT:
					x[i].v = TO_SP(irand() % RES_X);
					y[i].set(0.0f);
					break;
				case PO_BOTTOM_RIGHT:
				case PO_BOTTOM:
				case PO_BOTTOM_LEFT:
					x[i].v = TO_SP(irand() % RES_X);
					y[i].set(RES_Y - 1.0f);
					break;
				case PO_RIGHT:
				case PO_LEFT:
					x[i].v = (origin == PO_RIGHT) ? to_sp(RES_X - 1.0f) : 0;
					y[i].v = TO_SP(irand() % RES_Y);
					break;
				}
			} else {
				switch(origin) {
				case PO_TOP_RIGHT:
				case PO_RIGHT:
				case PO_BOTTOM_RIGHT:
					x[i].set(RES_X - 1.0f);
					y[i].v = TO_SP(irand() % RES_Y);
					break;
				case PO_BOTTOM_LEFT:
				case PO_LEFT:
				case PO_TOP_LEFT:
					x[i].set(0.0f);
					y[i].v = TO_SP(irand() % RES_Y);
					break;
				case PO_TOP:
				case PO_BOTTOM:
					x[i].v = TO_SP(irand() % RES_X);
					y[i].v = (origin == PO_TOP) ? 0 : to_sp(RES_Y - 1.0f);
					break;
				}
			}
			// Due to the SoA layout, setting [velocity_y[PARTICLE_COUNT]] will
			// overwrite [alive[0]] and [alive[1]].
			// Since [velocity_y[PARTICLE_COUNT]] is always smaller than
			// to_sp(16.0f) or 0x100, [alive[1]] will be set to `false`. And
			// if that particle was still alive before...
			switch(origin) {
			case PO_TOP:
				velocity_y[i].v = TO_SP(velocity_base[i]);
				velocity_x[i].set(0.0f);
				break;
			case PO_TOP_RIGHT:
				velocity_x[i].v = (-(velocity_base[i] * to_sp(0.8125f)));
				velocity_y[i].v = (  velocity_base[i] * to_sp(0.5f));
				break;
			case PO_RIGHT:
				velocity_x[i].v = TO_SP(-velocity_base[i]);
				velocity_y[i].set(0.0f);
				break;
			case PO_BOTTOM_RIGHT:
				velocity_x[i].v = (-(velocity_base[i]  * to_sp(0.8125f)));
				velocity_y[i].v = ((-velocity_base[i]) * to_sp(0.5f));
				break;
			case PO_BOTTOM:
				velocity_y[i].v = TO_SP(-velocity_base[i]);
				velocity_x[i].set(0.0f);
				break;
			case PO_BOTTOM_LEFT:
				velocity_x[i].v = (  velocity_base[i]  * to_sp(0.8125f));
				velocity_y[i].v = ((-velocity_base[i]) * to_sp(0.5f));
				break;
			case PO_LEFT:
				velocity_x[i].v = TO_SP(velocity_base[i]);
				velocity_y[i].set(0.0f);
				break;
			case PO_TOP_LEFT:
				velocity_x[i].v = (velocity_base[i] * to_sp(0.8125f));
				velocity_y[i].v = (velocity_base[i] * to_sp(0.5f));
				break;
			}
		}
	}

	// Unput/Update
	for(i = 0; i < PARTICLE_COUNT; i++) {
		// ... its unblitting call will never run, leaving its pixel on the
		// screen until it's overlapped by a different entity and unblitted
		// via that one.
		if(!alive[i]) {
			continue;
		}
		egc_copy_rect_1_to_0_16(x[i].to_pixel(), y[i].to_pixel(), 8, 1);
		x[i].v += velocity_x[i].v;
		y[i].v += velocity_y[i].v;

		if(!overlap_xyxy_lrtb_le_ge(
			x[i].v, y[i].v, 0, 0, to_sp(RES_X - 1), to_sp(RES_Y - 1)
		)) {
			alive[i] = false;
		}
	}

	// Render
	grcg_setcolor(GC_RMW, col);
	for(i = 0; i < PARTICLE_COUNT; i++) {
		if(!alive[i]) {
			continue;
		}
		grcg_pset(x[i].to_pixel(), y[i].to_pixel());
	}
	grcg_off();
}
