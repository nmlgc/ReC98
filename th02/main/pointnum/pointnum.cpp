#pragma option -zPmain_01 -G

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th02/v_colors.hpp"
#include "th02/core/globals.hpp"
#include "th02/hardware/pages.hpp"
#include "th02/formats/tile.hpp"
#include "th02/main/entity.hpp"
#include "th02/main/scroll.hpp"
#include "th02/main/pointnum/pointnum.hpp"
#include "th02/main/tile/tile.hpp"
#include "th02/sprites/pointnum.h"

#pragma option -a2

static const int POINTNUM_COUNT = 20;

struct CPointnums {
	vc_t col;
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

// Function ordering fails
// -----------------------

// Blits the given [numeral] to the given position. Assumptions:
// • ES is already set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
void pascal near pointnum_put(screen_x_t left, vram_y_t top, int numeral);
// -----------------------

void near pointnums_init_for_rank_and_reset(void)
{
	for(int i = 0; i < POINTNUM_COUNT; i++) {
		pointnums.flag[i] = F_FREE;
	}
	pointnums.col = V_WHITE;

	// Matches the score multiplier at the end of items_update_and_render().
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

void near pointnums_invalidate(void)
{
	for(int i = 0; i < POINTNUM_COUNT; i++) {
		if(pointnums.flag[i] == F_FREE) {
			continue;
		}

		tiles_invalidate_rect(
			pointnums.left[i],
			pointnums.top[i][page_back],

			// Adding the trailing 0, operator, and operand.
			// ZUN bloat: And one unnecessary glyph?
			(POINTNUM_W * (POINTNUM_DIGITS + 3 + 1)),

			POINTNUM_H
		);

		if(pointnums.flag[i] == F_REMOVE) {
			pointnums.flag[i] = F_FREE;
		} else {
			pointnums.top[i][page_back] = pointnums.top[i][page_front];
		}
	}
}

void pascal near pointnum_render(screen_x_t left, vram_y_t top, uint16_t points)
{
	extern uint16_t FOUR_DIGIT_POWERS_OF_10[POINTNUM_DIGITS];

	int i;
	bool past_leading_zeroes = false;
	for(i = 0; i < POINTNUM_DIGITS; (i++, left += POINTNUM_W)) {
		// ZUN landmine: Since [FOUR_DIGIT_POWERS_OF_10] doesn't cover the
		// full value range of an uint16_t, [numeral] should be limited to the
		// 0-9 range.
		int8_t numeral = (POINTNUM_0 + (points / FOUR_DIGIT_POWERS_OF_10[i]));
		points %= FOUR_DIGIT_POWERS_OF_10[i];
		if((numeral != POINTNUM_0) || past_leading_zeroes) {
			past_leading_zeroes = true;
			pointnum_put(left, top, numeral);
		}
	}
	pointnum_put((left + (POINTNUM_W * 0)), top, POINTNUM_0);
	pointnum_put((left + (POINTNUM_W * 1)), top, pointnums.op);
	pointnum_put((left + (POINTNUM_W * 2)), top, pointnums.operand);
}

void near pointnums_update_and_render(void)
{
	grcg_setcolor(GC_RMW, pointnums.col);
	_ES = SEG_PLANE_B;
	for(int i = 0; i < POINTNUM_COUNT; i++) {
		if(pointnums.flag[i] != F_ALIVE) {
			continue;
		}

		// Update
		if(pointnums.age[i] > 6) {
			pointnums.top[i][page_back] -= 1;
			if(pointnums.age[i] > 24) {
				pointnums.flag[i] = F_REMOVE;
				continue;
			}
		}
		pointnums.age[i]++;

		// Render
		vram_y_t top = scroll_screen_y_to_vram(
			top, pointnums.top[i][page_back]
		);
		pointnum_render(pointnums.left[i], top, pointnums.points[i]);
	}
	grcg_off();
}
