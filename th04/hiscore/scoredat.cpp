#if (GAME == 5)
	#include "th05/playchar.h"
	typedef int playchar2;
#else
	#include "th04/playchar.h"
	typedef playchar_t playchar2;
#endif

// ZUN bloat: Take [rank] as a parameter instead.
extern unsigned char rank;

#if (GAME == 4) && (BINARY == 'O')
// Loads the score data for both characters at the global [rank] into [hi] and
// [hi2]. Returns `false` if the data was loaded and decoded correctly, or
// `true` if the defaults were recreated.
// ZUN bloat: Shouldn't exist. Give the regular version a `scoredat_section_t&`
// parameter and call it twice.
bool near hiscore_scoredat_load_both(void)
#else
// Loads the score data for the given [playchar] at the global [rank] into
// [hi]. Returns `false` if the data was loaded and decoded correctly, or
// `true` if the defaults were recreated.
// ZUN bloat: Use the regular `playchar_t` type.
bool pascal near hiscore_scoredat_load_for(playchar2 playchar)
#endif
{
	#if (BINARY != 'E')
		#define SCOREDAT_FN_0 SCOREDAT_FN
		#define SCOREDAT_FN_1 SCOREDAT_FN
	#else
		extern const char SCOREDAT_FN_0[];
		extern const char SCOREDAT_FN_1[];
	#endif

	// ZUN bloat: Classic TOCTOU issue; file_ropen() does fail if the file
	// doesn't exist. Doesn't have any consequences in this case though: In the
	// very unlikely event that the file stops existing between file_exist()
	// and file_ropen(), old score data will remain in [hi] and [hi2], the game
	// will re-decode this already decoded data, and always recreate the file.
	if(file_exist(SCOREDAT_FN_0)) {
		file_ropen(SCOREDAT_FN_1);

		// ZUN bloat: The TH05 version is correct for both games.
		#if (GAME == 5)
			file_seek(
				(((playchar * RANK_COUNT) + rank) * sizeof(scoredat_section_t)),
				SEEK_SET
			);
		#else
			file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
			if((BINARY != 'O') && (playchar != PLAYCHAR_REIMU)) {
				file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
			}
		#endif
		file_read(&hi, sizeof(scoredat_section_t));

		#if (GAME == 4) && (BINARY == 'O')
			file_seek(
				((RANK_COUNT - 1) * sizeof(scoredat_section_t)), SEEK_CUR
			);
			file_read(&hi2, sizeof(scoredat_section_t));
		#endif

		file_close();
		if(scoredat_decode() != 0) {
			scoredat_recreate();
			return true;
		}
	} else {
		scoredat_recreate();
		return true;
	}
	return false;
}
