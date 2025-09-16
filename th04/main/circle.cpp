#include "th04/main/circle.hpp"
#include "th04/hardware/grcg.hpp"
#include "th04/main/playfld.hpp"
#include "th02/main/entity.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

// More like 17 though, due to the quirks documented below.
static const int CIRCLE_FRAMES = 16;

// Note the slight semantic differences to the item_splash_t structure.
struct circle_t {
	entity_flag_t flag;
	unsigned char age;
	screen_point_t center;
	pixel_t radius_cur;
	pixel_t radius_delta;
};

static const int CIRCLE_COUNT = ((GAME == 5) ? 8 : 16);

extern circle_t circles[CIRCLE_COUNT];

#define circle_init(p, center_x, center_y, radius_delta_) { \
	p->flag = F_ALIVE; \
	p->age = 0; \
	p->center.x = (PLAYFIELD_LEFT + (center_x / SUBPIXEL_FACTOR)); \
	p->center.y = (PLAYFIELD_TOP  + (center_y / SUBPIXEL_FACTOR)); \
	p->radius_cur = ( \
		4 + ((radius_delta_ > 0) ? 0 : (CIRCLE_FRAMES * -(radius_delta_))) \
	); \
	p->radius_delta = radius_delta_; \
}

void pascal circles_add_growing(subpixel_t center_x, subpixel_t center_y)
{
	circle_t near *p;
	int i;
	for((p = circles, i = 0); i < CIRCLE_COUNT; (i++, p++)) {
		if(p->flag != F_FREE) {
			continue;
		}
		circle_init(p, center_x, center_y, 8);
		break;
	}
}

void pascal circles_add_shrinking(subpixel_t center_x, subpixel_t center_y)
{
	circle_t near *p;
	int i;
	for((p = circles, i = 0); i < CIRCLE_COUNT; (i++, p++)) {
		if(p->flag != F_FREE) {
			continue;
		}
		circle_init(p, center_x, center_y, -8);
		break;
	}
}

void near circles_update(void)
{
	circle_t near *p;
	int i;
	for((p = circles, i = 0); i < CIRCLE_COUNT; (i++, p++)) {
		if(p->flag == F_REMOVE) {
			p->flag = F_FREE;
		}
		if(p->flag != F_ALIVE) {
			continue;
		}

		// ZUN quirk: This runs before [boss_update] or the bomb update/render
		// function. Any circles spawned there will therefore bypass this
		// update on their first frame and render at their initial radius.
		p->radius_cur += p->radius_delta;
		p->age++;
		if(p->age > CIRCLE_FRAMES) {
			// ZUN quirk: Deferring the removal until the next update means
			// that this circle will still be rendered on this frame.
			p->flag = F_REMOVE;
		}
	}
}

void near circles_render(void)
{
	grcg_setcolor_direct(circles_color);
	circle_t near *p;
	int i;
	for((p = circles, i = 0); i < CIRCLE_COUNT; (i++, p++)) {
		if(p->flag != F_ALIVE) {
			continue;
		}
		grcg_circle(p->center.x, p->center.y, p->radius_cur);
	}
}
