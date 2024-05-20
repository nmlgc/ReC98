#include "th01/rank.h"

#define SCOREDAT_FN "YUME.NEM"

#undef SCOREDAT_FN
extern const char near* SCOREDAT_FN;

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
	// sprites, analogous to this game's score_lebcd_t type. One of those
	// additional digits corresponds to the amount of continues used, the
	// other one is stored for no reason. (It's rendered, but never set to
	// anything but a leading REGI_0 because there's nowhere it could come
	// from.)
	regi_patnum_t score[SCOREDAT_PLACES][SCORE_DIGITS + 2];

	PlaycharOptional playchar[SCOREDAT_PLACES];
	regi_patnum_t stage[SCOREDAT_PLACES];
	uint8_t key1;
	uint8_t key2;
};

struct scoredat_section_t {
	uint16_t sum; // Sum of all bytes in [score], pre-encraption
	scoredat_t score;
};

extern scoredat_section_t hi;

/// Functions
/// ---------
// All of those write to and read from [hi], except where mentioned otherwise.

#define scoredat_sum(sum, p, i) \
	p = reinterpret_cast<uint8_t near *>(&hi.score); \
	i = 0; \
	while(i < sizeof(hi.score)) { \
		sum += *p; \
		i++; \
		p++; \
	}

void near scoredat_decode(void);

// Loads the score data for the given [rank] into [hi]. The OP.EXE version
// returns `true` if that data was recreated due to corruption or a nonexistent
// file.
#if (BINARY == 'O')
	bool16 pascal near scoredat_load_and_decode(rank_t rank);
#elif (BINARY == 'L')
	void pascal near scoredat_load_and_decode(rank_t rank);
#endif

// Calculates the checksum and encrypts [hi] in-place, then saves it to the
// score file under the given [rank]. The MAINL version also sets [cleared]
// based on resident data.
void pascal near scoredat_encode_and_save(rank_t rank);

// Fills [hi] with default (decrypted) score data, and writes it to the score
// file under all ranks.
void near scoredat_recreate(void);

// Returns `false` if the contents of [hi] match its checksum.
bool near scoredat_sum_invalid(void);
/// ---------
