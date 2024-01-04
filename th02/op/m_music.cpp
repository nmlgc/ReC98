#include "platform.h"
#include "shiftjis.hpp"
#if (GAME == 5)
	#include "th05/shiftjis/music.hpp"

	int game_sel = (GAME_COUNT - 1);
	extern const int TRACK_COUNT[GAME_COUNT] = { 14, 18, 24, 28, 23 };
#else
	#if (GAME == 4)
		#include "th04/shiftjis/music.hpp"
	#elif (GAME == 3)
		#include "th03/shiftjis/music.hpp"
	#elif (GAME == 2)
		#include "th02/shiftjis/music.hpp"
	#endif
#endif

// Polygon state
// -------------

bool polygons_initialized = false;
// -------------

// Selection state
// ---------------

#if (GAME <= 4)
	uint8_t track_playing = 0;
#endif
// ---------------
