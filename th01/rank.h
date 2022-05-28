#define RANK_H

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
	RANK_DEFAULT = -1,

	_rank_t_FORCE_INT16 = 0x7FFF
} rank_t;
