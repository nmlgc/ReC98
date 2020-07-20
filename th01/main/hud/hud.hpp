// Updates [hiscore] and re-renders it if the current [score] is higher.
void hiscore_update_and_render(void);

void hud_score_and_cardcombo_render(void);

/// Background
/// ----------
// Loads the first plane from the .GRF file with the given [fn] into [hud_bg],
// and sets [hud_bg_size] to its size in bytes. Always returns 0.
// (The "caller" is "supposed" to delete[] [hud_bg]… which the original game
// never does, resulting in a memory leak.)
int hud_bg_load(const char *fn);

extern uint8_t *hud_bg;
extern size_t hud_bg_size;
/// ----------
