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

typedef struct {
	SPPoint8 aligned;
	SPPoint8 diagonal;
} speed_t;

typedef struct {
	speed_t motion;
	unsigned char gauge_charge;
} playchar_speeds_t;

extern playchar_speeds_t PLAYCHAR_SPEEDS[PLAYCHAR_COUNT + 1];
