// TH04 adds 4 dissolve masks with patterns of increasing strength, and splits
// the [fx] parameter into two separate global variables.
extern int graph_putsa_fx_func;
extern int graph_putsa_fx_spacing;

void pascal graph_putsa_fx(
	screen_x_t left, vram_y_t top, int color, const unsigned char *str
);
