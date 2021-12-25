#define RANK_H

// Rank definitions
typedef enum {
	RANK_EASY,
	RANK_NORMAL,
	RANK_HARD,
	RANK_LUNATIC,
	RANK_EXTRA,
	RANK_COUNT,
	RANK_DEFAULT = -1,

	_rank_t_FORCE_INT16 = 0x7FFF
} rank_t;
