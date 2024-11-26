#include "th04/score.h"

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
// Used to simultaneously store scores for Marisa in TH04's OP.EXE. Still
// present in TH05, but unused.
extern scoredat_section_t hi2;

/// Functions
/// ---------
// All of those write to and read from [hi], except where mentioned otherwise.

// Decoding and encoding
#if (BINARY == 'M') && (GAME == 4)
	void pascal near scoredat_decode(scoredat_section_t near *hi);
	void pascal near scoredat_encode(scoredat_section_t near *hi);

	#define scoredat_decode_func() scoredat_decode(&hi)
	#define scoredat_encode_func() scoredat_encode(&hi)
#else
	// Returns 0 if the contents of [hi] match its checksum.
	// ZUN bloat: The OP.EXE implementation decodes both [hi] and [hi2], even
	// in TH05 where [hi2] is not referenced anywhere else. Using the MAIN.EXE
	// variant throughout the game would be much saner.
	uint8_t near scoredat_decode(void);

	void near scoredat_encode(void);

	#define scoredat_decode_func scoredat_decode
	#define scoredat_encode_func scoredat_encode
#endif

// Recreation
void near scoredat_recreate(void);

// Loading
// -------
// MODDERS: Take [rank] as a parameter instead.

#if (BINARY == 'M')
	// Loads the score data for the current global playchar at the global
	// [rank] into [hi]. TH04 recreates the default file on a loading or
	// decoding failure, TH05 doesn't.
	void near scoredat_load_for_cur(void);
#endif
// -------
/// ---------
