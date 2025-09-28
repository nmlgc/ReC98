// Growing or shrinking circles
// ----------------------------
// Due to the lack of a tile invalidation function, these are only supported on
// top of backgrounds that are fully redrawn each frame (read: during bosses).

#include "th01/math/subpixel.hpp"

// Color used to render all currently active circles.
extern vc_t circles_color;

// [center_x] and [center_y] are *passed* as subpixels, but stored at pixel
// precision, as master.lib's grcg_circle() function doesn't support more than
// that anyway.
void pascal circles_add_growing(subpixel_t center_x, subpixel_t center_y);
void pascal circles_add_shrinking(subpixel_t center_x, subpixel_t center_y);

void near circles_update(void);
void near circles_render(void);
// ----------------------------
