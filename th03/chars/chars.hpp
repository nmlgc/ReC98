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
} playchars_t;

// Encodes a playchars_t together with its alternate palette flag.
#pragma option -a1
struct playchar_paletted_t {
	unsigned char v;

	int filename_id() const {
		return (v - 1);
	}

	playchars_t char_id() const {
		return static_cast<playchars_t>(filename_id() / 2);
	}
};
#pragma option -a.

#define TO_PALETTED(playchar) ((playchar << 1) + 1)

typedef struct {
	SPPoint8 aligned;
	SPPoint8 diagonal;
} speed_t;

typedef struct {
	speed_t motion;
	unsigned char gauge_charge;
} playchar_speeds_t;

extern playchar_speeds_t PLAYCHAR_SPEEDS[PLAYCHAR_COUNT + 1];
