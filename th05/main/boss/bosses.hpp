// TH05-specific boss declarations.

/// Backdrops
/// ---------

// Image coordinates
// -----------------

static const pixel_t SARA_BACKDROP_W = 320;
static const screen_x_t SARA_BACKDROP_LEFT = (
	PLAYFIELD_LEFT + (PLAYFIELD_W / 2) - (SARA_BACKDROP_W / 2)
);
static const screen_y_t SARA_BACKDROP_TOP = PLAYFIELD_TOP;

static const screen_x_t LOUISE_BACKDROP_LEFT = PLAYFIELD_LEFT;
static const screen_y_t LOUISE_BACKDROP_TOP = PLAYFIELD_TOP;

static const pixel_t ALICE_BACKDROP_H = 163;
static const screen_x_t ALICE_BACKDROP_LEFT = PLAYFIELD_LEFT;
static const screen_y_t ALICE_BACKDROP_TOP = (
	PLAYFIELD_BOTTOM - ALICE_BACKDROP_H
);

static const pixel_t MAI_YUKI_BACKDROP_W = 256;
static const pixel_t MAI_YUKI_BACKDROP_H = 256;
static const screen_x_t MAI_YUKI_BACKDROP_LEFT = (
	PLAYFIELD_LEFT + (PLAYFIELD_W / 2) - (MAI_YUKI_BACKDROP_W / 2)
);
static const screen_y_t MAI_YUKI_BACKDROP_TOP = (
	PLAYFIELD_TOP + (PLAYFIELD_H / 2) - (MAI_YUKI_BACKDROP_H / 2)
);

static const screen_x_t YUMEKO_BACKDROP_LEFT = PLAYFIELD_LEFT;
static const screen_y_t YUMEKO_BACKDROP_TOP = PLAYFIELD_TOP;

static const screen_x_t SHINKI_BACKDROP_LEFT = PLAYFIELD_LEFT;
static const screen_y_t SHINKI_STAGE_BACKDROP_TOP = (
	PLAYFIELD_TOP + (PLAYFIELD_H / 2) - 80
);
static const pixel_t SHINKI_TYPE_D_BACKDROP_H = 128;
static const screen_y_t SHINKI_TYPE_D_BACKDROP_TOP = (
	PLAYFIELD_BOTTOM - SHINKI_TYPE_D_BACKDROP_H
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

// Same for all bosses in this game.
static const int ENTRANCE_BB_FRAMES_PER_CEL = 4;

BOSS_DEC(sara);
BOSS_DEC(louise);
BOSS_DEC(alice);

BOSS_DEC(mai_yuki);
// Pointing to the same address as [boss2]! Might not be possible anymore once
// that variable has to be moved to a C++ translation unit...
extern boss_stuff_t yuki;

BOSS_DEC(yumeko);
// Frame intervals between shooting out swords and lasers.
#define yumeko_interval_phase4 boss_statebyte[0]
#define yumeko_interval_phase7 boss_statebyte[1]

// TODO: Can't be declared here due to the set_nearfunc_ptr_to_farfunc()
// workarounds in shinki_update().
// BOSS_DEC(shinki);
// void pascal near shinki_custombullets_render();

BOSS_DEC(exalice);
