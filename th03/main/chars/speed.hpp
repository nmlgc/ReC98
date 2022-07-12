typedef struct {
	SPPoint8 aligned;
	SPPoint8 diagonal;
} speed_t;

typedef struct {
	speed_t motion;
	unsigned char gauge_charge;
} playchar_speed_t;

extern playchar_speed_t PLAYCHAR_SPEEDS[PLAYCHAR_COUNT + 1];
