// This file is probably the prime reason why you'd rather want to work on the
// `debloated` or `anniversary` branches instead.

#if (GAME == 5)
#include "th05/playchar.h"
#else
#if ((GAME == 4) && (BINARY == 'M'))
#include "th04/resident.hpp"
#endif
#include "th04/playchar.h"
#endif

#if ((GAME == 4) && (BINARY == 'M'))
#define recreated
#define loaded
// Loads the score data for the current resident player character at the given
// [rank] into [hi], recreating the defaults if necessary.
// ZUN bloat: Completely redundant.
void pascal near hiscore_scoredat_load_for_cur(rank_t rank)
#else
#define recreated true
#define loaded false
// Loads the score data for the given [playchar] at the given [rank] into [hi].
// Returns `false` if the data was loaded and decoded correctly, or `true` if
// the defaults were recreated.
bool pascal near hiscore_scoredat_load_for(playchar_t playchar, rank_t rank)
#endif
{
	if(file_ropen(SCOREDAT_FN)) {
		// ZUN bloat: The TH05 version is correct for both games and all
		// binaries.
#if (GAME == 5)
		file_seek(
			(((playchar * RANK_COUNT) + rank) * sizeof(scoredat_section_t)),
			SEEK_SET
		);
#else
		file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
#if (BINARY == 'M')
		if(resident->playchar_ascii == ('0' + PLAYCHAR_MARISA)) {
			file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
		}
#else
		if(playchar != PLAYCHAR_REIMU) {
			file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
		}
#endif
#endif
		file_read(&hi, sizeof(scoredat_section_t));
		file_close();

		if(scoredat_decode(hi) != 0) {
			scoredat_recreate();
			return recreated;
		}
	} else {
		scoredat_recreate();
		return recreated;
	}
	return loaded;
}
