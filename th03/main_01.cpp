/* ReC98
 * -----
 * Code segment #1 of TH03's MAIN.EXE
 */

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "th03/sprite16.hpp"
#include "th03/main/playfld.hpp"
#include "th03/main/player/shots.hpp"

void pascal near shots_update(void)
{
	shotpair_t near *shotpair = shotpairs;
	for(int i = 0; i < SHOTPAIR_COUNT; i++, shotpair++) {
		if(shotpair->flag) {
			shotpair->topleft.y.v += shotpair->velocity_y.v;
			if(shotpair->topleft.y.v <= to_sp(-1.0f)) {
				shotpair->flag = 0;
			}
		}
	}
}

void pascal near shots_render(void)
{
	shotpair_t near *shotpair = shotpairs;

	sprite16_put_w = SHOT_W;
	sprite16_put_h = SHOT_H;
	sprite16_clip_left = 0;
	sprite16_clip_right = RES_X - 1;

	for(int i = 0; i < SHOTPAIR_COUNT; i++, shotpair++) {
		if(shotpair->flag) {
			int so = shotpair->so_anim + shotpair->so_pid;
			screen_x_t left = playfield_fg_x_to_screen(
				shotpair->topleft.x, shotpair->pid
			);
			screen_y_t top = shotpair->topleft.y.to_pixel() + PLAYFIELD_TOP;

			sprite16_put(left + 0,                 top, so);
			sprite16_put(left + SHOTPAIR_DISTANCE, top, so);

			shotpair->so_anim += SHOT_VRAM_W;
			if(shotpair->so_anim >= (SHOT_VRAM_W * SHOT_SPRITE_COUNT)) {
				shotpair->so_anim = 0;
			}
		}
	}
}

}
