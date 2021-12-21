#define SCOREDAT_FN "YUME.NEM"
static const int SCOREDAT_PLACES = 10;
static const int SCOREDAT_NAME_LEN = 8;

enum scoredat_cleared_t {
	SCOREDAT_NOT_CLEARED = 18,
	SCOREDAT_CLEARED = 99, // Chiyuri and Yumemi unlocked
};

struct scoredat_t {
	// Stored backwards for no reason.
	regi_patnum_t name[SCOREDAT_PLACES][SCOREDAT_NAME_LEN];

	scoredat_cleared_t cleared;
	int8_t unknown;

	// Stored as little-endian sprite IDs with leading zeroes as REGI_0
	// sprites, analogous to this game's score_lebcd_t type.
	regi_patnum_t score[SCOREDAT_PLACES][SCORE_DIGITS + 2];

	playchar_optional_t playchar[SCOREDAT_PLACES];
	regi_patnum_t stage[SCOREDAT_PLACES];
	uint8_t key1;
	uint8_t key2;
};

struct scoredat_section_t {
	uint16_t sum; // Sum of all bytes in [score], pre-encraption
	scoredat_t score;
};

extern scoredat_section_t hi;
