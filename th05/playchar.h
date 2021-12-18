typedef enum {
	PLAYCHAR_REIMU = 0,
	PLAYCHAR_MARISA = 1,
	PLAYCHAR_MIMA = 2,
	PLAYCHAR_YUUKA = 3,
	PLAYCHAR_COUNT = 4,

	_playchar_t_FORCE_UINT8 = 0xFF
} playchar_t;

extern playchar_t playchar;
