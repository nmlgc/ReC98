#include "th02/main/entity.hpp"

enum item_type_t {
#if GAME == 5
	IT_NONE = -2,
#endif
	IT_ENEMY_DROP_NEXT = -1,
	IT_POWER = 0,
	IT_POINT = 1,
	IT_DREAM = 2,
	IT_BIGPOWER = 3,
	IT_BOMB = 4,
	IT_1UP = 5,
	IT_FULLPOWER = 6,
	IT_COUNT,
};

struct item_t {
	entity_flag_t flag;
	char unused; // ZUN bloat
	PlayfieldMotion pos;
	unsigned char type;
	char unknown;
	int patnum;	// Assumed to be a 16×16 sprite.
	bool16 pulled_to_player;
};

#define ITEM_W 16
#define ITEM_H 16
#define ITEM_PULL_SPEED 10

#if GAME == 5
	#define ITEM_COUNT 40
#else
	#define ITEM_COUNT 32
#endif

extern item_t items[ITEM_COUNT];

extern const int ITEM_PATNUM[IT_COUNT];

void pascal near items_add(subpixel_t x, subpixel_t y, item_type_t type);

// Increments or decrements [playperf] when reaching certain values.
extern unsigned char item_playperf_raise;
extern unsigned char item_playperf_lower;

#if GAME == 5
	extern unsigned int item_point_score_at_full_dream;
#endif

// Items dropped when losing a life
// --------------------------------
#define ITEM_MISS_COUNT 5
typedef enum {
	MISS_FIELD_LEFT = 0,
	MISS_FIELD_CENTER = 1,
	MISS_FIELD_RIGHT = 2,
	MISS_FIELD_COUNT,
};
// Yes, these have Y first and X second.
extern const Subpixel ITEM_MISS_VELOCITIES[MISS_FIELD_COUNT][2][ITEM_MISS_COUNT];

void pascal near items_miss_add(void);
// --------------------------------

// Collection counters
// -------------------

// Reset to 0 when moving to a new stage.
extern unsigned int stage_point_items_collected;

extern unsigned int items_spawned;
extern unsigned int items_collected;

#if GAME == 5
	// Same value as [total_point_items_collected].
	// Used for extends and end-of-game score bonus calculation.
	extern unsigned int extend_point_items_collected;
#endif

extern unsigned int total_point_items_collected;

// TH04 includes items collected above the PoC during a bomb, TH05 doesn't.
extern unsigned int total_max_valued_point_items_collected;
// -------------------

extern bool items_pull_to_player;
