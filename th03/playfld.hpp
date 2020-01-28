#include "th03/math/subpixel.hpp"

#define PLAYFIELD_COUNT 2
#define PLAYFIELD_W 288
#define PLAYFIELD_H 368
// For both playfields, in every direction. (CSS style!)
// The clipped SPRITE16 display functions rely on this being at least 16!
#define PLAYFIELD_BORDER 16
#define PLAYFIELD_X PLAYFIELD_BORDER
#define PLAYFIELD_Y PLAYFIELD_BORDER

#define PLAYFIELD_VRAM_H (PLAYFIELD_H / 2)

#define PLAYFIELD_W_BORDERED (PLAYFIELD_BORDER + PLAYFIELD_W + PLAYFIELD_BORDER)
#define PLAYFIELD1_CLIP_LEFT 0
#define PLAYFIELD1_CLIP_RIGHT (PLAYFIELD1_CLIP_LEFT + PLAYFIELD_W_BORDERED - 1)
#define PLAYFIELD2_CLIP_LEFT  (PLAYFIELD1_CLIP_RIGHT + 1)
#define PLAYFIELD2_CLIP_RIGHT (PLAYFIELD2_CLIP_LEFT + PLAYFIELD_W_BORDERED - 1)

#define PLAYFIELD_VRAM_W_BORDERED (PLAYFIELD_W_BORDERED / 8)

extern int playfield_fg_shift_x[PLAYFIELD_COUNT];

int pascal playfield_fg_x_to_screen(Subpixel x, unsigned int pid);
