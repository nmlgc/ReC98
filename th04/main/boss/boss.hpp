// Bosses
// ------
static const pixel_t BOSS_W = 64;
static const pixel_t BOSS_H = 64;

typedef struct {
	PlayfieldMotion pos;
	int hp;
	unsigned char sprite;
	unsigned char phase;
	int phase_frame;
	unsigned char damage_this_frame;
	unsigned char mode;
	// Used for both movement and bullet angles.
	unsigned char angle;
	unsigned char mode_change;
	int phase_end_hp;
} boss_stuff_t;

extern boss_stuff_t boss;
extern SPPoint boss_hitbox_radius;

// Callbacks
extern  farfunc_t_near boss_update;
extern nearfunc_t_near boss_fg_render;

// Also responsible to set [bg_render_bombing_func] to the
// [boss_bg_render_func]!
extern  farfunc_t_near boss_update_func;

extern nearfunc_t_near boss_backdrop_colorfill;
extern nearfunc_t_near boss_bg_render_func;
extern nearfunc_t_near boss_fg_render_func;

#define BOSS_DEC(name) \
	void pascal  far name##_update(void); \
	void pascal near name##_bg_render(void); \
	void pascal near name##_fg_render(void);

// Renders the boss battle background image at the given screen position,
// surrounded by the given background [col].
void pascal near boss_backdrop_render(
	screen_x_t left, vram_y_t top, uint4_t col
);
// ------

/// Explosions
/// ----------
#define EXPLOSION_SMALL_COUNT 2

struct explosion_t {
	char flag;
	unsigned char age;
	SPPoint center;
	SPPoint radius_cur;
	SPPoint radius_delta;
	int8_t unused;
	// Offset to add to the angle for the Y coordinate, turning the circle
	// into a slanted ellipse. See https://www.desmos.com/calculator/faeefi6w1u
	// for a plot of the effect.
	unsigned char angle_offset;
};

enum explosion_type_t {
	ET_NONE = -1,
	ET_CIRCLE = 0,
	ET_NW_SE = 1,
	ET_SW_NE = 2,
	ET_HORIZONTAL = 3,
	ET_VERTICAL = 4,

	_explosion_type_t_FORCE_INT16 = 0x7FFF
};

extern explosion_t explosions_small[EXPLOSION_SMALL_COUNT];
extern explosion_t explosions_big;

void pascal near boss_explode_small(explosion_type_t type);
#if (GAME == 5)
	void near boss_explode_big_circle(void);

	// Wrapper for easy compatibility with TH04 code.
	inline void boss_explode_big(explosion_type_t type) {
		boss_explode_big_circle();
	}
#else
	void pascal near boss_explode_big(explosion_type_t type);
#endif

void near explosions_small_update_and_render(void);
void near explosions_big_update_and_render(void);

void explosions_small_reset(void);
/// ----------

void near boss_items_drop();
void pascal near boss_phase_end(
	explosion_type_t explosion_type, int next_phase_end_hp
);
