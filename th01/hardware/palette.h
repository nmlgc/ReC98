/// Current palette
/// ---------------
#if defined(COLOR_COUNT) && defined(__cplusplus)
	extern Palette4 z_Palettes;

	// Calls z_palette_set_show() for all colors in [pal].
	void z_palette_set_all_show(const Palette4& pal);

	// Fades each hardware palette color from the given RGB value to its
	// respective value in z_Palettes, blocking [step_ms] milliseconds at each
	// of the 16 fade steps. If [keep] is nonzero for a specific color number,
	// that color is excluded from the fade calculation and will stay at its
	// z_Palettes value throughout the function.
	void z_palette_fade_from(
		uint4_t from_r, uint4_t from_g, uint4_t from_b,
		int keep[COLOR_COUNT],
		unsigned int step_ms
	);
#endif

// Sets the given hardware [col] to the given RGB value.
#define UINT4 int
void z_palette_show_single(UINT4 col, UINT4 r, UINT4 g, UINT4 b);
#define z_palette_show_single_col(col, rgb) \
	z_palette_show_single(col, rgb.c.r, rgb.c.g, rgb.c.b);
#undef UINT4

// Clamps #[r][g][b] to the 4-bit 0-15 range, then sets the given [col] in
// both z_Palettes and the hardware palette to that value.
void z_palette_set_show(int col, int r, int g, int b);

// Sets all hardware colors to #000, without touching z_Palettes.
void z_palette_black(void);

// Sets all hardware colors to #FFF, without touching z_Palettes.
void z_palette_white(void);

// Fades all hardware colors from #000 or #FFF to their value in z_Palettes.
void z_palette_black_in(void);
void z_palette_white_in(void);

// Fades all hardware colors from their value in z_Palettes to #000 or #FFF,
// without modifying z_Palettes.
void z_palette_black_out(void);
void z_palette_white_out(void);

#define z_Palettes_set_func_and_show(tmp_col, tmp_comp, func) { \
	palette_foreach(tmp_col, tmp_comp, func); \
	z_palette_set_all_show(z_Palettes); \
}

// Sets all colors in both the hardware palette and z_Palettes to #000.
#define z_palette_set_black(tmp_col, tmp_comp) { \
	palette_set_grayscale(z_Palettes, 0, tmp_col, tmp_comp); \
	z_palette_set_all_show(z_Palettes); \
}

// Sets all colors in both the hardware palette and z_Palettes to #FFF.
#define z_palette_set_white(tmp_col, tmp_comp) { \
	palette_set_grayscale(z_Palettes, RGB4::max(), tmp_col, tmp_comp); \
	z_palette_set_all_show(z_Palettes); \
}

// Performs a single black-out step.
#define z_palette_black_out_step(tmp_col, tmp_comp) \
	z_Palettes_set_func_and_show(tmp_col, tmp_comp, { \
		z_Palettes.colors[tmp_col].v[tmp_comp] -= \
			(z_Palettes.colors[tmp_col].v[tmp_comp] > 0) ? 1 : 0; \
	})

#define z_palette_black_out_step_2(tmp_col, tmp_comp) \
	z_Palettes_set_func_and_show(tmp_col, tmp_comp, { \
		z_Palettes.colors[tmp_col].v[tmp_comp] += \
			(z_Palettes.colors[tmp_col].v[tmp_comp] > 0) ? -1 : 0; \
	})

// That's… not how you "quickly dereference the first element"?
#define z_palette_black_out_step_bugged(tmp_col, tmp_comp) \
	z_Palettes_set_func_and_show(tmp_col, tmp_comp, { \
		z_Palettes.colors[tmp_col].v[tmp_comp] -= (&z_Palettes > 0) ? 1 : 0; \
	})

// Performs a single white-out step.
#define z_palette_white_out_step(tmp_col, tmp_comp) \
	z_Palettes_set_func_and_show(tmp_col, tmp_comp, { \
		if(z_Palettes.colors[tmp_col].v[tmp_comp] < 0xF) { \
			z_Palettes.colors[tmp_col].v[tmp_comp]++; \
		} \
	})

// Performs a single ramping step from z_Palettes to [target_pal]. Every color
// in z_Palettes is assumed to not be brighter than the corresponding color in
// [target_pal].
#define z_palette_black_in_step_to(tmp_col, tmp_comp, target_pal) \
	z_Palettes_set_func_and_show(tmp_col, tmp_comp, { \
		z_Palettes.colors[tmp_col].v[tmp_comp] += ( \
			target_pal[tmp_col].v[tmp_comp] > z_Palettes[tmp_col].v[tmp_comp] \
				? 1 \
				: 0 \
		); \
	})


// Performs a single ramping step from z_Palettes to [target_pal].
#define z_palette_step_to(tmp_col, tmp_comp, target_pal) { \
	z_Palettes_set_func_and_show(tmp_col, tmp_comp, { \
		if( \
			z_Palettes[tmp_col].v[tmp_comp] != \
			target_pal[tmp_col].v[tmp_comp] \
		) { \
			z_Palettes.colors[tmp_col].v[tmp_comp] += ( \
				z_Palettes[tmp_col].v[tmp_comp] < \
				target_pal[tmp_col].v[tmp_comp] \
			) ? 1 : -1; \
		} \
	}) \
}

// Sets the given specific hardware [colors] to #FFF.
#define z_palette_flash_colors(colors, colors_count, i) \
	for(i = 0; colors_count > i; i++) { \
		z_palette_set_show(colors[i], RGB4::max(), RGB4::max(), RGB4::max()); \
	}
/// ----------------
