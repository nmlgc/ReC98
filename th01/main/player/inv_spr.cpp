#include "th01/sprites/shape8x8.hpp"
#include "th01/main/shape.hpp"

static const int INVINCIBILITY_SPRITE_COUNT = 8;
static const int INVINCIBILITY_SPRITE_FRAMES = 8;
static const int INVINCIBILITY_SPRITES_DONE = 0xFF;

void invincibility_sprites_update_and_render(bool16 invincible)
{
	int i;
	extern struct {
		int frame[INVINCIBILITY_SPRITE_COUNT];
		screen_x_t left[INVINCIBILITY_SPRITE_COUNT];
		vram_y_t top[INVINCIBILITY_SPRITE_COUNT];
	} invincibility_sprites;
	#define sprites invincibility_sprites

	#define sloppy_unput(i) \
		egc_copy_rect_1_to_0_16( \
			sprites.left[i], sprites.top[i], 16, sSHAPE8X8[0].h() \
		);

	if(!invincible) {
		if(sprites.frame[0] == INVINCIBILITY_SPRITES_DONE) {
			return;
		}
		for(i = 0; i < INVINCIBILITY_SPRITE_COUNT; i++) {
			sloppy_unput(i);
		}
		sprites.frame[0] = INVINCIBILITY_SPRITES_DONE;
		return;
	}

	if(sprites.frame[0] == INVINCIBILITY_SPRITES_DONE) {
		for(i = 0; i < INVINCIBILITY_SPRITE_COUNT; i++) {
			sprites.frame[i] = 0;
		}
	}

	for(i = 0; i < INVINCIBILITY_SPRITE_COUNT; i++) {
		if(
			(sprites.frame[i] == (INVINCIBILITY_SPRITE_FRAMES + 1)) ||
			(sprites.frame[i] == 0)
		) {
			if(sprites.frame[i] == (INVINCIBILITY_SPRITE_FRAMES + 1)) {
				sloppy_unput(i);
			}
			sprites.left[i]  = ((rand() % 48) + (player_left - 8));
			sprites.top[i]   = ((rand() % 48) + (player_top - 16));
			sprites.frame[i] = ((rand() % 7) + 1);
		}
		// ZUN bug: Did you mean: `sprites.left[i]`?
		if(
			(sprites.top[i] >= 0) &&
			(sprites.top[i] < (RES_X - sSHAPE8X8[0].w()))
		) {
			shape8x8_invincibility_put(
				sprites.left[i],
				sprites.top[i],
				(sprites.frame[i] <= SHAPE8X8_INVINCIBILITY_CELS)
					? (sprites.frame[i] - 1)
					: (INVINCIBILITY_SPRITE_FRAMES - sprites.frame[i])
			);
		}
		sprites.frame[i]++;
	}
	#undef sloppy_unput
	#undef sprites
}
