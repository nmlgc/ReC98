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
