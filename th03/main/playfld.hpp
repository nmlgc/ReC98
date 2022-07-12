#include "th01/math/subpixel.hpp"

#define PLAYFIELD_COUNT 2
#define PLAYFIELD_W 288
#define PLAYFIELD_H 368
// For both playfields, in every direction. (CSS style!)
// The clipped SPRITE16 display functions rely on this being at least 16!
#define PLAYFIELD_BORDER 16
#define PLAYFIELD_LEFT PLAYFIELD_BORDER
#define PLAYFIELD_TOP PLAYFIELD_BORDER

#define PLAYFIELD_VRAM_H (PLAYFIELD_H / 2)

#define PLAYFIELD_W_BORDERED (PLAYFIELD_BORDER + PLAYFIELD_W + PLAYFIELD_BORDER)
#define PLAYFIELD1_CLIP_LEFT 0
#define PLAYFIELD1_CLIP_RIGHT (PLAYFIELD1_CLIP_LEFT + PLAYFIELD_W_BORDERED - 1)
#define PLAYFIELD2_CLIP_LEFT  (PLAYFIELD1_CLIP_RIGHT + 1)
#define PLAYFIELD2_CLIP_RIGHT (PLAYFIELD2_CLIP_LEFT + PLAYFIELD_W_BORDERED - 1)

#define PLAYFIELD_VRAM_W_BORDERED (PLAYFIELD_W_BORDERED / BYTE_DOTS)

// A subpixel point within one of the playfields. No conversion methods to
// screen space here, since the instance doesn't know the playfield it is on.
typedef SPPoint PlayfieldPoint;

extern screen_x_t playfield_fg_shift_x[PLAYFIELD_COUNT];

screen_x_t pascal playfield_fg_x_to_screen(Subpixel x, unsigned int pid);
