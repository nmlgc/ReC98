#include "platform.h"
#include "pc98.h"
#include "th02/main/entity.hpp"
#include "th02/sprites/pointnum.h"

static const int POINTNUM_COUNT = 20;

struct CPointnums {
	uint8_t col;
	int8_t unused;
	screen_x_t left[POINTNUM_COUNT];
	screen_y_t top[POINTNUM_COUNT][2];
	uint16_t points[POINTNUM_COUNT];
	entity_flag_t flag[POINTNUM_COUNT];
	uint8_t age[POINTNUM_COUNT];
	pointnum_cel_t op; // `operator` is a keyword.
	pointnum_cel_t operand;
};

extern CPointnums pointnums;
