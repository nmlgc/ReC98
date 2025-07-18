#include "th02/score.h"
#include <dos.h>

#define SCOREDAT_FN "huuhi.dat"

#define SCOREDAT_PLACES 10
#define SCOREDAT_NAME_LEN 6 /* excluding the terminating 0 */
#define EXTRA_CLEAR_FLAGS {1, 2, 4}
#define GAME_CLEAR_CONSTANTS {318, 118, 218}
#define STAGE_ALL 127

struct scoredat_t {
	/* For ranks (and therefore, structure instances) #0, #1 and #2 (Easy,
	 * Normal and Hard), this is either GAME_CLEAR_CONSTANTS[rank] or 0,
	 * and indicates whether the main 5 stages have been cleared with the
	 * *shot type* associated with the rank's index, in any difficulty.
	 * Yes, ZUN uses a field in a rank-specific structure to store a
	 * shot type-specific value.
	 *
	 * For rank #3, this is instead interpreted as a bit field using the
	 * EXTRA_CLEAR_FLAGS to indicate whether the Extra Stage has been
	 * cleared with the respective shot type.
	 * Yes, ZUN stores what is technically information about the Extra
	 * rank in the structure of the Lunatic rank.
	 *
	 * For rank #4, this field is unused.
	 */
	int16_t cleared;

	score_t score[SCOREDAT_PLACES];
	int32_t score_sum;
	unsigned char g_name[SCOREDAT_PLACES][SCOREDAT_NAME_LEN + 1];
	unsigned char g_name_first_sum;
	unsigned char stage[SCOREDAT_PLACES];
	unsigned char stage_sum;
	struct date date[SCOREDAT_PLACES];
	unsigned char shottype[SCOREDAT_PLACES];
};

struct scoredat_section_t {
	scoredat_t score;
	int32_t section_sum; // Sum of all bytes in [score], pre-encraption
};
