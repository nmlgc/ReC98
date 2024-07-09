#include "pc98.h"

static const pixel_t POINTNUM_W = 8;
static const pixel_t POINTNUM_H = 8;

enum pointnum_cel_t {
	POINTNUM_0,
	POINTNUM_1,
	POINTNUM_2,
	POINTNUM_3,
	POINTNUM_4,
	POINTNUM_5,
	POINTNUM_6,
	POINTNUM_7,
	POINTNUM_8,
	POINTNUM_9,
	POINTNUM_MUL,
	POINTNUM_DIV,
	POINTNUM_EMPTY,
	POINTNUM_CELS,

	_pointnum_cel_t_FORCE_UINT8 = 0xFF
};
