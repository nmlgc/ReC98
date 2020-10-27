typedef enum {
	PLAYCHAR_REIMU = 0,
	PLAYCHAR_MARISA = 1,
	PLAYCHAR_COUNT = 2
} playchars_t;

typedef enum {
	SHOTTYPE_A = 0,
	SHOTTYPE_B = 1,
	SHOTTYPE_COUNT,
} shottype_t;

// Used way too often...
inline playchars_t playchar_other(playchars_t playchar) {
	return static_cast<playchars_t>(PLAYCHAR_MARISA - playchar);
}

extern playchars_t playchar;
