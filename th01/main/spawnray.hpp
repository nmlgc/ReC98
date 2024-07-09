#include "th01/hardware/graph.h"

static const int SPAWNRAY_RESET = 99;

#define spawnray_unput_and_put_func( \
	target_prev_x, target_prev_y, \
	origin_x, origin_y, target_x, target_y, col, unblit_always \
) { \
	if(col == SPAWNRAY_RESET) { \
		target_prev_x = -PIXEL_NONE; \
		target_prev_y = -PIXEL_NONE; \
		/* Umm, shouldn't we unblit in this case? */ \
		goto spawnray_ret; \
	} \
	if( \
		(unblit_always || \
			(target_prev_x != -PIXEL_NONE) && (target_prev_y != -PIXEL_NONE) \
		) && \
		(target_prev_x >= 0) && (target_prev_x < RES_X) && \
		(target_prev_y >= 0) && (target_prev_y < RES_Y) \
	) { \
		graph_r_line_unput(origin_x, origin_y, target_prev_x, target_prev_y); \
	} \
	if( \
		(target_x >= 0) && (target_x < RES_X) && \
		(target_y >= 0) && (target_y < RES_Y) \
	) { \
		graph_r_line(origin_x, origin_y, target_x, target_y, col); \
	} \
	target_prev_x = target_x; \
	target_prev_y = target_y; \
spawnray_ret: \
}
