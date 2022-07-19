// "Line" bullets
// --------------
// Lines at arbitrary angles and with arbitrary 1- to 16-pixel dot patterns
// that kill the player on contact with their right/bottom end.

void linebullet_unput(
	screen_x_t left, screen_y_t top, screen_x_t right, screen_y_t bottom
);

void linebullet_put_and_hittest(
	screen_x_t left,
	screen_y_t top,
	screen_x_t right,
	screen_y_t bottom,
	int col
);

// Will only collision-detect for the [right]most pixel itself.
void linebullet_put_patterned_and_hittest(
	screen_x_t left,
	screen_y_t top,
	screen_x_t right,
	screen_y_t bottom,
	int col,
	dots16_t pattern
);
// --------------
