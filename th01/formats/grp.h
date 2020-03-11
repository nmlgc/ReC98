extern Palette4 grp_palette;
#if (BINARY == 'E')
	extern int grp_palette_tone;

	// Sets colors 1 - 15 (excluding color 0!) of z_Palettes and the hardware
	// palette to [grp_palette] at the given [tone].
	// The toning algorithm is equivalent to master.lib's palette_settone().
	void pascal grp_palette_settone(int tone);

	// Equivalent to the master.lib functions, but based on the [grp_palette].
	void pascal grp_palette_black_out(unsigned int frames);
	void pascal grp_palette_black_in(unsigned int frames);
	void pascal grp_palette_white_out(unsigned int frames);
	void pascal grp_palette_white_in(unsigned int frames);
#endif
