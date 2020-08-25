// Growing or shrinking circles
// ----------------------------
// [center_x] and [center_y] are *passed* as subpixels, but stored at pixel
// precision, as master.lib's grcg_circle() function doesn't support more than
// that anyway.
void pascal circles_add_growing(subpixel_t center_x, subpixel_t center_y);
void pascal circles_add_shrinking(subpixel_t center_x, subpixel_t center_y);

void pascal near circles_update(void);
void pascal near circles_render(void);
// ----------------------------
