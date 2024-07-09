#ifndef TH01_RANK_H
#define TH01_RANK_H

// Rank definitions
typedef enum {
	RANK_EASY,
	RANK_NORMAL,
	RANK_HARD,
	RANK_LUNATIC,

	// Hi Asprey, there is no unused Extra rank in TH01.
	// (https://www.youtube.com/watch?v=RcjhM4tfPq4&t=169s)
	#if ((GAME != 1) && (GAME != 3))
		RANK_EXTRA,
	#endif

	RANK_COUNT,

	#if (GAME >= 4)
		// Triggering the first-launch setup menu via a special rank value...
		// Definitely unique.
		RANK_SHOW_SETUP_MENU = 0xFF,
	#endif

	_rank_t_FORCE_INT16 = 0x7FFF
} rank_t;

#define RANKS_CAPS { \
	"EASY", "NORMAL", "HARD", "LUNATIC" \
}

#define RANKS_CAPS_CENTERED { \
	" EASY ", \
	"NORMAL", \
	" HARD ", \
	"LUNATIC" \
}

#endif /* TH01_RANK_H */
