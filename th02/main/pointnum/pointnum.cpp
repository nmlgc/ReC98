#pragma option -zPmain_01

#include "platform.h"
#include "pc98.h"
#include "th01/rank.h"
#include "th02/v_colors.hpp"
#include "th02/core/globals.hpp"
#include "th02/main/entity.hpp"
#include "th02/main/pointnum/pointnum.hpp"
#include "th02/sprites/pointnum.h"

#pragma option -a2

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

void near pointnums_init_for_rank_and_reset(void)
{
	for(int i = 0; i < POINTNUM_COUNT; i++) {
		pointnums.flag[i] = F_FREE;
	}
	pointnums.col = V_WHITE;

	switch(rank) {
	case RANK_EASY:
	case RANK_NORMAL:
		pointnums.op = POINTNUM_EMPTY;
		pointnums.operand = POINTNUM_EMPTY;
		break;

	case RANK_HARD:
		pointnums.op = POINTNUM_MUL;
		pointnums.operand = POINTNUM_2;
		break;

	case RANK_LUNATIC:
		pointnums.op = POINTNUM_MUL;
		pointnums.operand = POINTNUM_4;
		break;

	case RANK_EXTRA:
		pointnums.op = POINTNUM_MUL;
		pointnums.operand = POINTNUM_8;
		break;
	}
}

void pascal near pointnums_add(
	screen_x_t left_, screen_y_t top_, uint16_t points_
)
{
	register screen_x_t left = left_;
	register screen_y_t top = top_;
	register uint16_t points = points_;
	for(register int i = 0; i < POINTNUM_COUNT; i++) {
		if(pointnums.flag[i] == F_FREE) {
			pointnums.flag[i] = F_ALIVE;
			pointnums.age[i] = 0;
			pointnums.points[i] = points;
			pointnums.left[i] = left;
			pointnums.top[i][0] = top;
			pointnums.top[i][1] = top;
			break;
		}
	}
}
