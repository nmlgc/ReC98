#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "codegen.hpp"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/main/playfld.hpp"

#pragma option -k-

// Points that change from subpixel screen space to pixel screen space within
// the same variable...
union SpaceChangingPoint {
	SPPoint sp;
	screen_point_t pixel;
};

// Register parameters for vector2_at_opt().
#define v_length_	_BX
#define v_length	static_cast<subpixel_t>(v_length_)
#define v_angle 	_CX
#define v_center_	_BP
#define v_center	reinterpret_cast<SPPoint __ss *>(v_center_)
#define v_ret_  	_DI
#define v_ret   	reinterpret_cast<SpaceChangingPoint __ss *>(v_ret_)

// Register parameters for build_line_in_pixels().
#define p_0_       	_DI
#define p_0        	reinterpret_cast<SpaceChangingPoint __ss *>(p_0_)
#define p_1_       	_BX
#define p_1        	reinterpret_cast<SpaceChangingPoint __ss *>(p_1_)
#define p_distance_	_BP
#define p_distance 	reinterpret_cast<SPPoint __ss *>(p_distance_)

#define p_distance_offset	1

// A regular vector2_at() function with [v_center], [v_angle], and [v_length].
// Returns the Y coordinate of the resulting vector.
subpixel_t near vector2_at_opt()
{
	uint16_t table_offset = v_angle;
	table_offset += table_offset; // *= sizeof(short)
	_AX = polar_by_offset(v_center->x, v_length, CosTable8, table_offset);
	mov_to_mem(_SS, v_ret_, offsetof(point_t, x), _AX);
	_AX = polar_by_offset(v_center->y, v_length, SinTable8, table_offset);
	mov_to_mem(_SS, v_ret_, offsetof(point_t, y), _AX);
	return _AX;
}

// Calculates:
// 	p_0 = p_0.to_pixel();
// 	p_1 = (p_0 + p_distance).to_pixel();
void near build_line_in_pixels()
{
	#define tmp_0	_DX
	#define tmp_1	_AX

	tmp_1 = p_distance[p_distance_offset].x;
	mov_to_reg(tmp_0, _SS, p_0_, offsetof(SPPoint, x));
	tmp_1 += tmp_0;
	static_cast<pixel_t>(tmp_1) >>= SUBPIXEL_BITS;
	static_cast<pixel_t>(tmp_0) >>= SUBPIXEL_BITS;
	p_1->pixel.x = tmp_1;
	mov_to_mem(_SS, p_0_, offsetof(screen_point_t, x), tmp_0);

	tmp_1 = p_distance[p_distance_offset].y;
	mov_to_reg(tmp_0, _SS, p_0_, offsetof(SPPoint, y));
	tmp_1 += tmp_0;
	static_cast<pixel_t>(tmp_1) >>= SUBPIXEL_BITS;
	static_cast<pixel_t>(tmp_0) >>= SUBPIXEL_BITS;
	p_1->pixel.y = tmp_1;
	mov_to_mem(_SS, p_0_, offsetof(screen_point_t, y), tmp_0);

	#undef tmp_1
	#undef tmp_0
}
