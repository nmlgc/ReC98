#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/overlap.hpp"
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

void CParticles::unput(EGCCopy& egc)
{
	for(int i = 0; i < PARTICLE_COUNT; i++) {
		if(alive[i]) {
			egc.rect_interpage(x[i].to_pixel(), y[i].to_pixel(), 1, 1, 1);
		}
	}
}

void CParticles::update_and_render(particle_origin_t origin, vc_t col)
{
	unsigned char i;

	// Spawn

	// This should have maybe been done after spawning, and the fact that it's
	// done here was partly responsible for an off-by-one bug in the original
	// game. Keeping it here to at least preserve the single frame of delay
	// before the first spawn.
	spawn_cycle++;
	if(spawn_cycle >= (spawn_interval * PARTICLE_COUNT)) {
		spawn_cycle = 0;
	}
	if((spawn_cycle % spawn_interval) == 0) {
		i = (spawn_cycle / spawn_interval);
		if(alive[i] == false) {
			alive[i] = true;
			const pixel_t velocity_base = ((irand() % velocity_base_max) + 1);
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

			switch(origin) {
			case PO_TOP:
				velocity_y[i].v = TO_SP(velocity_base);
				velocity_x[i].set(0.0f);
				break;
			case PO_TOP_RIGHT:
				velocity_x[i].v = (-(velocity_base * to_sp(0.8125f)));
				velocity_y[i].v = (  velocity_base * to_sp(0.5f));
				break;
			case PO_RIGHT:
				velocity_x[i].v = TO_SP(-velocity_base);
				velocity_y[i].set(0.0f);
				break;
			case PO_BOTTOM_RIGHT:
				velocity_x[i].v = (-(velocity_base  * to_sp(0.8125f)));
				velocity_y[i].v = ((-velocity_base) * to_sp(0.5f));
				break;
			case PO_BOTTOM:
				velocity_y[i].v = TO_SP(-velocity_base);
				velocity_x[i].set(0.0f);
				break;
			case PO_BOTTOM_LEFT:
				velocity_x[i].v = (  velocity_base  * to_sp(0.8125f));
				velocity_y[i].v = ((-velocity_base) * to_sp(0.5f));
				break;
			case PO_LEFT:
				velocity_x[i].v = TO_SP(velocity_base);
				velocity_y[i].set(0.0f);
				break;
			case PO_TOP_LEFT:
				velocity_x[i].v = (velocity_base * to_sp(0.8125f));
				velocity_y[i].v = (velocity_base * to_sp(0.5f));
				break;
			}
		}
	}

	// Update
	for(i = 0; i < PARTICLE_COUNT; i++) {
		if(!alive[i]) {
			continue;
		}
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
