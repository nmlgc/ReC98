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
#if (GAME == 4) && (BINARY == 'O')
// Loads the score data for both characters at the given [rank] into [hi] and
// [hi2]. Returns `false` if the data was loaded and decoded correctly, or
// `true` if the defaults were recreated.
// ZUN bloat: Shouldn't exist. Give the regular version a `scoredat_section_t&`
// parameter and call it twice.
bool pascal near hiscore_scoredat_load_both(rank_t rank)
#else
// Loads the score data for the given [playchar] at the given [rank] into [hi].
// Returns `false` if the data was loaded and decoded correctly, or `true` if
// the defaults were recreated.
bool pascal near hiscore_scoredat_load_for(playchar_t playchar, rank_t rank)
#endif
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
#elif (BINARY == 'E')
		if(playchar != PLAYCHAR_REIMU) {
			file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
		}
#endif
#endif
		file_read(&hi, sizeof(scoredat_section_t));
#if (GAME == 4) && (BINARY == 'O')
		file_seek(((RANK_COUNT - 1) * sizeof(scoredat_section_t)), SEEK_CUR);
		file_read(&hi2, sizeof(scoredat_section_t));
#endif
		file_close();

		// ZUN landmine: In TH04, scoredat_recreate() only writes to [hi] and
		// leaves [hi2] as it is. TH04's High Score viewer in OP.EXE uses both
		// sections and doesn't double-check whether it contains valid data,
		// because why should it, this is our job. But this means that it will
		// render garbage data in both cases:
		//
		// • If Reimu/[hi] is corrupt, we return and don't decode [hi2]. The
		//   call site assumes that it got decoded, though, and consequently
		//   renders garbage. The fact that [hi] receives the default data from
		//   scoredat_recreate() doesn't even matter because the corruption
		//   from [hi2] will most likely mess up the entire screen.
		//
		// • If Marisa/[hi2] is corrupt, [hi2] did get decoded, but still
		//   carries the same garbage data that failed decoding.
		//
		// Both sections then only get loaded correctly on the next call to
		// this function.
		if(scoredat_decode(hi) != 0) {
			scoredat_recreate();
			return recreated;
		}
#if (GAME == 4) && (BINARY == 'O')
		if(scoredat_decode(hi2) != 0) {
			scoredat_recreate();
			return recreated;
		}
#endif
	} else {
		// Same TH04 landmine as above.
		scoredat_recreate();
		return recreated;
	}
	return loaded;
}
