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
} playchar_t;

// Encodes a playchar_t together with its alternate palette flag.
struct PlaycharPaletted {
	unsigned char v;

	int filename_id() const {
		return (v - 1);
	}

	playchar_t char_id() const {
		return static_cast<playchar_t>(filename_id() / 2);
	}
};

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

#define TO_PALETTED(playchar) ((playchar << 1) + 1)
