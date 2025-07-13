#if (GAME == 5)
#include "th05/playchar.h"
#else
#include "th04/playchar.h"
#endif
#include "th04/score.h"
#include "th01/rank.h"

#define SCOREDAT_FN "GENSOU.SCR"

#if GAME == 5
#define SCOREDAT_PLACES 5
#define SCOREDAT_NOT_CLEARED 18
#define SCOREDAT_CLEARED 0x80
#else
#define SCOREDAT_PLACES 10
#define SCOREDAT_NOT_CLEARED 25
#define SCOREDAT_CLEARED_A 1
#define SCOREDAT_CLEARED_B 2
#define SCOREDAT_CLEARED_BOTH (SCOREDAT_CLEARED_A | SCOREDAT_CLEARED_B)
#endif

#define SCOREDAT_NAME_LEN 8

struct scoredat_t {
	unsigned char g_name[SCOREDAT_PLACES][SCOREDAT_NAME_LEN + 1];
	score_lebcd_t g_score[SCOREDAT_PLACES];

#if GAME == 5
	unsigned char g_stage[SCOREDAT_PLACES];
	unsigned char cleared;
	unsigned char unused_1;
#else
	unsigned char cleared;
	unsigned char unused_1;
	unsigned char g_stage[SCOREDAT_PLACES];
	unsigned char unused_2[SCOREDAT_PLACES];
#endif
};

struct scoredat_section_t {
	int8_t key1;
	int8_t key2;
	int16_t score_sum; // Sum of all bytes in [score], pre-encraption
	scoredat_t score;
};

extern scoredat_section_t hi;

/// Functions
/// ---------
/// All of those write to and read from [hi], except where mentioned otherwise.

// Decoding and encoding. scoredat_decode() returns 0 if the contents of [hi]
// match its checksum.

#if ((GAME == 5) && (BINARY == 'M'))
uint8_t pascal near scoredat_decode(void);
void pascal near scoredat_encode(void);
#else
uint8_t pascal near scoredat_decode(scoredat_section_t& section);
void pascal near scoredat_encode(scoredat_section_t& section);

// Loads the score data for the given [playchar] at the given [rank] into [hi].
// Returns `false` if the data was loaded and decoded correctly, or `true` if
// the defaults were recreated.
bool pascal near scoredat_load(playchar_t playchar, rank_t rank);

// Saves [hi] to the score file, replacing the section for the given [playchar]
// at the given [rank]. Leaves [hi] in encoded state.
void pascal near scoredat_save(playchar_t playchar, rank_t rank);
#endif

// Recreation
void near scoredat_recreate(void);
/// ---------
