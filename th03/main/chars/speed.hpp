struct speed_t {
	SPPoint8 aligned;
	SPPoint8 diagonal;
};

struct playchar_speed_t {
	speed_t motion;
	unsigned char gauge_charge;
};

extern playchar_speed_t PLAYCHAR_SPEEDS[PLAYCHAR_COUNT + 1];
