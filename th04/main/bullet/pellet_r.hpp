union pellet_render_t {
	struct {
		screen_x_t left;
		vram_y_t top;
	} top;
	struct {
		vram_offset_t vram_offset;
		uint16_t sprite_offset;
	} bottom;
};

#if (GAME == 5)
	// Separate render list for pellets during their delay cloud stage.
	extern int pellet_clouds_render_count;
	extern bullet_t near *pellet_clouds_render[PELLET_COUNT];
#endif

extern int pellets_render_count;
extern pellet_render_t pellets_render[PELLET_COUNT];

// Renders the top and bottom part of all pellets, as per [pellets_render] and
// [pellets_render_count]. Assumptions:
// • ES is already set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// • pellets_render_top() is called before pellets_render_bottom()
void near pellets_render_top();
void near pellets_render_bottom();
