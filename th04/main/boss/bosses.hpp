// TH04-specific boss declarations.

/// Backdrops
/// ---------

// Boss-specific [boss_backdrop_colorfill] functions, called with the GRCG in
// TDW mode and the tile register set to the intended color.
void pascal near orange_backdrop_colorfill(void);
void pascal near kurumi_backdrop_colorfill(void);
void pascal near elly_backdrop_colorfill(void);
void pascal near reimu_marisa_backdrop_colorfill(void);
void pascal near yuuka5_backdrop_colorfill(void);
void pascal near mugetsu_gengetsu_backdrop_colorfill(void);
/// ---------

void pascal near mugetsu_gengetsu_bg_render(void);
void pascal near mugetsu_fg_render(void);
void pascal  far mugetsu_update(void);

static const pixel_t GENGETSU_W = 96;
static const pixel_t GENGETSU_H = 96;

void pascal near gengetsu_fg_render(void);
void pascal  far gengetsu_update(void);
