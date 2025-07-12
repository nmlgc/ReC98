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

	// ZUN bloat: Classic TOCTOU issue; file_ropen() also fails if the file
	// doesn't exist. Doesn't have any consequences in this case though: In the
	// very unlikely event that the file stops existing between file_exist()
	// and file_ropen(), the following will happen:
	// • All file-related calls will fail and leave old score data in [hi] and
	//   [hi2].
	// • scoredat_decode() re-decodes already decoded data and fails.
	// • The code then recreates score data just as it would have if the file
	//   hadn't existed in this initial check.
	// Hence, this is not a landmine, just bloat.
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
		// • If Reimu/[hi] is corrupt, scoredat_decode() exits early and
		//   doesn't decode [hi2]. The call site assumes that it got decoded,
		//   though, and consequently renders garbage. The fact that [hi]
		//   receives the default data from scoredat_recreate() doesn't even
		//   matter because the corruption from [hi2] will most likely mess up
		//   the entire screen.
		//
		// • If Marisa/[hi2] is corrupt, [hi2] did get decoded, but still
		//   carries the same garbage data that failed decoding.
		//
		// Both sections then only get loaded correctly on the next call to
		// this function.
		if(scoredat_decode() != 0) {
			scoredat_recreate();
			return true;
		}
	} else {
		// Same TH04 landmine as above.
		scoredat_recreate();
		return true;
	}
	return false;
}
