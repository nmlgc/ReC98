#define PLAYER_W 32
#define PLAYER_H 48

extern screen_point_t player_topleft;

extern bool player_is_hit;

// Grants invincibility when >0. Decrements by 1 each frame in that case.
// In TH02, this works independently from [player_invincible_via_bomb].
extern unsigned char player_invincibility_time;

static const uint8_t POWER_MIN = 1;
#if (GAME == 2)
	static const uint8_t POWER_MAX = 80;

	// Grants invincibility as long as it's true. Works independently from
	// [player_invincibility_time].
	extern bool player_invincible_via_bomb;
#endif

static const int POWER_OVERFLOW_MAX = 42;
static const int SHOT_LEVEL_MAX = 9;

extern uint8_t power;

// Amount of power past POWER_MAX, capped to POWER_OVERFLOW_MAX. Determines the
// point value of any further power items collected.
extern int power_overflow;

extern uint8_t shot_level;
