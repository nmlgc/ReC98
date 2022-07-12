// Blits [h] rows starting at [top] from VRAM page 1 to the same position on
// VRAM page 0. Mainly used after a previous GDC scroll of [h] rows, to
// smoothly scroll between two full background images.
void egc_copy_rows_1_to_0(vram_y_t top, pixel_t h);
