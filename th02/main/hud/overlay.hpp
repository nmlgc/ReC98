#if (GAME == 2)
	// Prints the rightmost [digits] of [val] using the bold gaiji font onto
	// TRAM, right-aligned at
	//
	// 	(([left] + ([digits] * GAIJI_W)), [y])
	//
	// Leading zeroes are skipped. [digits] is expected to be ≤8.
	void pascal near overlay_uint_put(
		tram_x_t left, tram_y_t y, int digits, long val
	);

	// Fills the playfield's area on the text RAM with transparency.
	// (Future games use a near function.)
	void far overlay_wipe(void);
#endif
