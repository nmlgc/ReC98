#ifndef TH04_PLAYCHAR_H
#define TH04_PLAYCHAR_H

typedef enum {
	PLAYCHAR_REIMU = 0,
	PLAYCHAR_MARISA = 1,
	PLAYCHAR_COUNT = 2
} playchar_t;

typedef enum {
	SHOTTYPE_A = 0,
	SHOTTYPE_B = 1,
	SHOTTYPE_COUNT,
} shottype_t;

// Used way too often...
inline playchar_t playchar_other(playchar_t playchar) {
	return static_cast<playchar_t>(PLAYCHAR_MARISA - playchar);
}

extern playchar_t playchar;

#endif /* TH04_PLAYCHAR_H */
