#ifndef TH03_PLAYCHAR_HPP
#define TH03_PLAYCHAR_HPP

#include "platform.h"

typedef enum {
	PLAYCHAR_REIMU = 0,
	PLAYCHAR_MIMA = 1,
	PLAYCHAR_MARISA = 2,
	PLAYCHAR_ELLEN = 3,
	PLAYCHAR_KOTOHIME = 4,
	PLAYCHAR_KANA = 5,
	PLAYCHAR_RIKAKO = 6,
	PLAYCHAR_CHIYURI = 7,
	PLAYCHAR_YUMEMI = 8,
	PLAYCHAR_COUNT = 9,

	PLAYCHAR_COUNT_LOCKED = (PLAYCHAR_COUNT - 2),
} playchar_t;

typedef unsigned char playchar_paletted_t;

// Uses 0 to indicate "no character" and shifts all IDs up by 1.
struct PlaycharOptional {
	unsigned char v;

	playchar_t char_id() const {
		return static_cast<playchar_t>(v - 1);
	}

	void set_none() {
		v = 0;
	}
};

// Encodes a playchar_t together with its alternate palette flag in the lowest
// bit.
struct PlaycharPaletted {
	playchar_paletted_t v;

	playchar_t char_id() const {
		return static_cast<playchar_t>(v / 2);
	}

	// ZUN bloat
	int char_id_16() const {
		return (v / 2);
	}

	bool16 palette_id() const {
		return (v & 1);
	}
};

#define TO_OPTIONAL_PALETTED(playchar) ((playchar << 1) + 1)

// Like PlaycharPaletted, but with all IDs shifted up by 1 to reserve 0 for "no
// character".
struct PlaycharPalettedOptional {
	unsigned char v;

	int filename_id() const {
		return (v - 1);
	}

	playchar_t char_id() const {
		return static_cast<playchar_t>(filename_id() / 2);
	}

	// ZUN bloat
	int char_id_16() const {
		return (filename_id() / 2);
	}

	void set(playchar_t playchar) {
		v = TO_OPTIONAL_PALETTED(playchar);
	}
};

#endif /* TH03_PLAYCHAR_HPP */
