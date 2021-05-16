// The intended palette for a boss, with no effects applied.
extern Palette4 boss_palette;

#define boss_palette_snap_inlined() \
	for(int col = 0; col < COLOR_COUNT; col++) { \
		for(int comp = 0; comp < COMPONENT_COUNT; comp++) { \
			boss_palette[col].v[comp] = z_Palettes[col].v[comp]; \
		} \
	}

// Overwrites [boss_palette] with [z_Palettes].
void boss_palette_snap(void);

// Sets both [z_Palettes] and the hardware palette to [boss_palette].
void boss_palette_show(void);
