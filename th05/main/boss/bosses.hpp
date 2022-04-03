// TH05-specific boss declarations.

/// Backdrops
/// ---------

// Image coordinates
// -----------------

static const screen_y_t SHINKI_STAGE_BACKDROP_TOP = (
	PLAYFIELD_TOP + (PLAYFIELD_H / 2) - 80
);
static const pixel_t SHINKI_TYPE_D_BACKDROP_H = 128;
static const pixel_t SHINKI_TYPE_D_BACKDROP_TOP = (
	PLAYFIELD_H - SHINKI_TYPE_D_BACKDROP_H
);
// -----------------

// Boss-specific [boss_backdrop_colorfill] functions, called with the GRCG in
// TDW mode and the tile register set to the intended color.
void pascal near sara_backdrop_colorfill(void);
void pascal near louise_backdrop_colorfill(void);
void pascal near alice_backdrop_colorfill(void);
void pascal near mai_yuki_backdrop_colorfill(void);
void pascal near yumeko_backdrop_colorfill(void);
void pascal near shinki_stage_backdrop_colorfill(void);

// These enable and disable the GRCG themselves.
void near boss_bg_fill_col_0(void);
void near shinki_bg_type_d_colorfill(void);
/// ---------

BOSS_DEC(sara);
BOSS_DEC(louise);
BOSS_DEC(alice);

BOSS_DEC(mai_yuki);
// Pointing to the same address as [boss2]! Might not be possible anymore once
// that variable has to be moved to a C++ translation unit...
extern boss_stuff_t yuki;

BOSS_DEC(yumeko);
extern unsigned char yumeko_interval_phase4;
extern unsigned char yumeko_interval_phase7;

BOSS_DEC(shinki);
BOSS_DEC(exalice);
