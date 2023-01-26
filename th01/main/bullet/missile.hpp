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
/// ---------

// Sprites
// -------

static const int MISSILE_CELS = 16;
static const int MISSILE_PTNS = (MISSILE_CELS / 4);

static const int MISSILE_HIT_IMAGE = (MISSILE_CELS / 4);
static const int MISSILE_HIT_CELS = 2;
// -------

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
	uint8_t ptn_id_base; // main_ptn_id_t. Very bold to limit this to 8 bits!
	missile_flag_t flag[MISSILE_COUNT];

protected:
	// Calculates the current [ptn_id] and [quarter] for the missile at the
	// given index.
	void ptn_cel_for(int i, main_ptn_id_t& ptn_id, int& quarter) const;

public:
	// Loads the missile sprites into the given .PTN [slot].
	void load(main_ptn_slot_t slot) {
		ptn_load(slot, "boss3_m.ptn");
		ptn_id_base = PTN_ID(slot, 0);
	}

	// Spawns a new missile if there is a free slot left. [velocity_x] and
	// [velocity_y] are limited to Subpixel resolution.
	void add(
		screen_x_t left, screen_x_t top, double velocity_x, double velocity_y
	);

	void reset(void);
	void unput_update_render(void);
};

extern CMissiles Missiles;
