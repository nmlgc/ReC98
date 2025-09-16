// Platform-specific VRAM clipping region
// --------------------------------------
// Defaults to the visible edges of VRAM.

#include "game/coords.hpp"

static const screen_x_t CLIP_NO_LEFT = -32768;
static const screen_y_t CLIP_NO_TOP = -32768;
static const screen_x_t CLIP_NO_RIGHT = 32767;
static const screen_y_t CLIP_NO_BOTTOM = 32767;

// Sets the clipping region. Set any of the coordinates to the respective
// [CLIP_NO_*] constant to effectively disable clipping in that direction, or
// pass a `nullptr` to set the clipping region to the visible edges of VRAM.
void Grp_SetClip(const LTRB<screen_x_t, screen_y_t> *region);
