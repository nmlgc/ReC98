// Blits the hardcoded diamond, star, or snowflake sprites in the given [col]
// to the given position.
void shape8x8_diamond_put(screen_x_t left, vram_y_t top, int col);
void shape8x8_star_put(screen_x_t left, vram_y_t top, int col);
void shape8x8_flake_put(screen_x_t left, vram_y_t top, int col);

void shape_ellipse_arc_put(
	screen_x_t center_x,
	vram_y_t center_y,
	pixel_t radius_x,
	pixel_t radius_y,
	int col,
	unsigned char angle_step,
	unsigned char angle_start,
	unsigned char angle_end
);

// Makes a sloppy attempt at restoring the pixels along the given ellipse arc
// from VRAM page 1, but ends up restoring horizontal 16×1 lines along that
// arc.
void shape_ellipse_arc_sloppy_unput(
	screen_x_t center_x,
	vram_y_t center_y,
	pixel_t radius_x,
	pixel_t radius_y,
	unsigned char angle_step,
	unsigned char angle_start,
	unsigned char angle_end
);
