typedef enum {
	PLAYCHAR_REIMU = 0,
	PLAYCHAR_MARISA = 1,
	PLAYCHAR_MIMA = 2,
	PLAYCHAR_YUUKA = 3,
	PLAYCHAR_COUNT = 4,

	_playchar_t_FORCE_UINT8 = 0xFF
} playchar_t;

extern playchar_t playchar;

// Returns the parameter for the current player character.
int pascal select_for_playchar(
	int for_reimu, int for_marisa,
	int for_mima, int for_yuuka
);
