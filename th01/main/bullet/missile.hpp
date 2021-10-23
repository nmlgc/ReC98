/// Constants
/// ---------

static const int MISSILE_COUNT = 50;

static const pixel_t MISSILE_W = PTN_QUARTER_W;
static const pixel_t MISSILE_H = PTN_QUARTER_H;

// Missiles explode when reaching these coordinates.
static const screen_x_t MISSILE_LEFT_MIN = PLAYFIELD_LEFT;
static const screen_y_t MISSILE_TOP_MIN = PLAYFIELD_TOP;
static const screen_x_t MISSILE_LEFT_MAX = (PLAYFIELD_RIGHT - MISSILE_W);
static const screen_y_t MISSILE_TOP_MAX = (PLAYFIELD_BOTTOM - 1);

// Indicates that this missile hasn't been rendered before. Should not exist,
// because there's already Subpixel::None() for that.
static const subpixel_t MISSILE_NEW = -1;

static const int MISSILE_HIT_CELS = 2;
static const int MISSILE_HIT_IMAGE = 4;
/// ---------

enum missile_flag_t {
	MF_FREE = 0,
	MF_MOVING = 1,
	MF_HIT = 2,
	MF_HIT_last = (MF_HIT + MISSILE_HIT_CELS - 1),

	_missile_flag_t_FORCE_UINT8 = 0xFF
};

class CMissiles {
	Subpixel cur_left[MISSILE_COUNT];
	Subpixel cur_top[MISSILE_COUNT];
	Subpixel prev_left[MISSILE_COUNT];
	Subpixel prev_top[MISSILE_COUNT];
	Subpixel velocity_x[MISSILE_COUNT];
	Subpixel velocity_y[MISSILE_COUNT];
	int16_t unused[MISSILE_COUNT];
	int8_t unknown[MISSILE_COUNT];
	uint8_t ptn_id_base; // main_ptn_id_t. Very bold to limit this to 8 bits!
	missile_flag_t flag[MISSILE_COUNT];
};

extern CMissiles Missiles;
