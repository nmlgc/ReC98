// Adds [count] new spark sprites with the given [distance] in random
// directions away from ([center_x], [center_y]).
void pascal sparks_add_random(
	Subpixel center_x, Subpixel center_y, subpixel_t distance, int count
);

// Adds [count] new spark sprites along a circle with the given [distance] away
// from ([center_x], [center_y]). Obviously ignores the random angle set in
// sparks_init().
void pascal sparks_add_circle(
	Subpixel center_x, Subpixel center_y, subpixel_t distance, int count
);

// Initializes all sparks with a random angle.
void near sparks_init(void);

void near sparks_update(void);
void near sparks_render(void);
void near sparks_invalidate(void);
