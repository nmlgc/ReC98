extern enum {
	// Round is still being played.
	DF_NONE = 0,

	// Losing player explodes, winning player can still move.
	DF_EXPLODE = 1,

	// Shows the "Win" and "Lose" banners and disables movement and collision
	// detection for both players.
	DF_BANNER = 2,
} defeat_flag;
