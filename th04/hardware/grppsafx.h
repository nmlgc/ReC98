// TH04 adds 4 dissolve masks with patterns of increasing strength, and splits
// the [fx] parameter into two separate global variables.
extern int graph_putsa_fx_func;
extern int graph_putsa_fx_spacing;

void pascal graph_putsa_fx(int x, int y, int color, const unsigned char *str);
