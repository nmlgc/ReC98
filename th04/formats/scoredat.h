#include "th02/score.h"

#if GAME == 5
# define SCOREDAT_PLACES 5
#else
# define SCOREDAT_PLACES 10
#endif

#define SCOREDAT_NAME_LEN 8

typedef struct {
	unsigned char g_name[SCOREDAT_PLACES][SCOREDAT_NAME_LEN + 1];
	unsigned char g_points[SCOREDAT_PLACES][SCORE_DIGITS];

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
} scoredat_t;

typedef struct {
	int8_t key1;
	int8_t key2;
	int16_t score_sum; // Sum of all bytes in [score], pre-encraption
	scoredat_t score;
} scoredat_section_t;

extern scoredat_section_t hi;
// Used to simultaneously store scores for Marisa in TH04's OP.EXE. Still
// present in TH05, but unused.
extern scoredat_section_t hi2;

/// Functions
/// ---------
// All of those write to and read from [hi], except where mentioned otherwise.

// Decoding and encoding
#if (BINARY == 'O')
	// scoredat_decode() variant that decodes both [hi] and [hi2] -
	// even in TH05 where [hi2] is not referenced anywhere else.
	void pascal near scoredat_decode_both(void);
	void pascal near scoredat_encode(void);

#	define scoredat_decode_func scoredat_decode_both
#elif (BINARY == 'M') && (GAME == 4)
	void pascal near scoredat_decode(scoredat_section_t near *hi);
	void pascal near scoredat_encode(scoredat_section_t near *hi);

#	define scoredat_decode_func() scoredat_decode(&hi)
#	define scoredat_encode_func() scoredat_encode(&hi)
#else
	void pascal near scoredat_decode(void);
	void pascal near scoredat_encode(void);

#	define scoredat_decode_func scoredat_decode
#	define scoredat_encode_func scoredat_encode
#endif

// Recreation
#if (GAME == 4)
	void pascal near scoredat_recreate(void);
#elif (GAME == 5) && (BINARY == 'O')
	void pascal near scoredat_recreate_op(void);
#elif (GAME == 5) && (BINARY == 'E')
	void pascal near scoredat_recreate_maine(void);
#endif
/// ---------
