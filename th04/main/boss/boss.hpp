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

enum explode_type_t {
	ET_NONE = -1,
	ET_NW_SE = 1,
	ET_SW_NE = 2,
	ET_HORIZONTAL = 3,
	ET_VERTICAL = 4,
};

extern explosion_t explosions_small[EXPLOSION_SMALL_COUNT];
extern explosion_t explosions_big;

void pascal near boss_explode_small(unsigned int type);
#if GAME == 4
	void pascal near boss_explode_big(unsigned int type);
#endif

void pascal near explosions_small_update_and_render(void);
void pascal near explosions_big_update_and_render(void);

void pascal explosions_small_reset(void);
/// ----------

void near boss_items_drop();
void pascal near boss_phase_end(
	explode_type_t explode_type, int next_phase_end_hp
);
