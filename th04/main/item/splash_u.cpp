#include <mem.h>
#include "th04/main/item/splash.hpp"

#define ITEM_SPLASH_RADIUS_START 2.0f
#define ITEM_SPLASH_RADIUS_DELTA 2.0f
#define ITEM_SPLASH_RADIUS_END 32.0f

extern unsigned char item_splash_last_id;

void near item_splashes_init(void)
{
	// memset(item_splashes, 0x00, sizeof(item_splashes));
	_CX = (sizeof(item_splashes) / sizeof(uint16_t));
	_ES = _DS;
	_AX = 0x00;
	reinterpret_cast<item_splash_t near *>(_DI) = item_splashes;
	asm { rep stosw; }

	item_splash_last_id = 0;
}

void pascal near item_splashes_add(Subpixel center_x, Subpixel center_y)
{
	item_splash_t near &splash = item_splashes[item_splash_last_id];

	item_splash_last_id++;
	if(item_splash_last_id >= ITEM_SPLASH_COUNT) {
		item_splash_last_id = 0;
	}

	if(splash.flag != F_FREE) {
		return;
	}
	splash.flag = F_ALIVE;
	splash.center.x = center_x;
	splash.center.y = center_y;
	splash.radius_cur.set(ITEM_SPLASH_RADIUS_START);
	splash.time = (ITEM_SPLASH_RADIUS_END / ITEM_SPLASH_RADIUS_DELTA);
	splash.radius_prev.set(ITEM_SPLASH_RADIUS_START);
}

void near item_splashes_update(void)
{
	item_splash_t near *p;
	int i;

	for((p = item_splashes, i = 0); i < ITEM_SPLASH_COUNT; (i++, p++)) {
		if(p->flag == F_FREE) {
			continue;
		} else if(p->flag == F_REMOVE) {
			p->flag = F_FREE;
		} else {
			p->radius_prev = p->radius_cur;
			p->radius_cur += ITEM_SPLASH_RADIUS_DELTA;
			if(p->radius_cur.v >= to_sp(ITEM_SPLASH_RADIUS_END)) {
				p->flag = F_REMOVE;
			}
		}
	}
}
