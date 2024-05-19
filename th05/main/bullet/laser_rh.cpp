#pragma option -zPmain_01

#include <stddef.h>
#include "platform.h"
#include "codegen.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "game/coords.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/polar.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/player/player.hpp"
#include "th05/main/bullet/laser.hpp"

#pragma option -k-

// Register parameters for vector2_at_opt().
#define v_length_     	_BX
#define v_length     	static_cast<subpixel_t>(v_length_)
#define v_length_high	_BH // ZUN bloat
#define v_length_low 	_BL // ZUN bloat
#define v_angle      	_CX
#define v_angle_low  	_CL
#define v_angle_high 	_CH
#define v_center_    	_BP
#define v_center     	reinterpret_cast<SPPoint __ss *>(v_center_)
#define v_ret_       	_DI
#define v_ret        	reinterpret_cast<space_changing_point_t __ss *>(v_ret_)

// Register parameters for build_line_in_pixels().
#define p_0_       	_DI
#define p_0        	reinterpret_cast<space_changing_point_t __ss *>(p_0_)
#define p_1_       	_BX
#define p_1        	reinterpret_cast<space_changing_point_t __ss *>(p_1_)
#define p_distance_	_BP
#define p_distance 	reinterpret_cast<SPPoint __ss *>(p_distance_)

// ZUN bloat: To work around the need for shifting BP even further once control
// flow reaches build_line_in_pixels(), ZUN hardcoded the offset from the
// current value of BP to [p_distance] within the function itself. This offset
// actually matches [p_distance]'s position if build_line_in_pixels() were a
// regular function… which means that this madness saves a grand total of one
// single PUSH instruction. Wow.
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

bool16 pascal near laser_render_ray(const laser_coords_t near& coords)
{
	// ZUN bloat: Micro-optimized based on the wrong assumption that using more
	// stack space is bad? This assumption had dramatic effects on the
	// complexity of the resulting monstrosity, for three main reasons:
	//
	// 1) Using BP as a parameter to the helper functions above, within a
	//    function that declares local variables which are accessed *relative*
	//    to BP. This shifts the function's view of its own variables, which in
	//    turn forces us to provide these shifted views as additional structs
	//    within the main union just to keep the code comprehensible.
	//
	// 2) The misguided assumption that pointer arithmetic with addresses of
	//    local variables is superior to just fully recalculating the pointers.
	//    On a 486, both `LEA r16, m` and `ADD r16, imm` take 1 cycle. Sure,
	//    thanks to 1), these addresses are constantly shifting, but it's still
	//    better than us having to annotate the exact movement to the target
	//    variable.
	//
	// 3) The necessary conversion from subpixel space to screen space is done
	//    within the same variables, requiring further unions within unions to
	//    describe which type is active at any given time.
	//
	// The /// comments spell out the core algorithm in pseudocode, and are
	// probably easier to follow than the actual compiled mess of code.

	#define _BP        	reinterpret_cast<space_changing_point_t __ss *>(_BP)
	#define point_count	static_cast<int>(_AX)

	union {
		// Subpixel points used for initial construction.
		// Since the meaning of "left" and "right" would be flipped depending
		// on whether the laser points up and down, we use `_ccw` and `cw` to
		// indicate the ray's corner points as a counter-clockwise or clockwise
		// quarter-circle rotation away from the centered origin.
		struct {
			SPPoint start_ccw;
			/* -------------------- */ point_t _unused_1;
			/* -------------------- */ point_t _unused_2;
			SPPoint end_ccw;
			/* -------------------- */ point_t _unused_3;
			SPPoint origin_ccw;
			SPPoint ccw_to_cw_delta;
			SPPoint origin;
		} c;

		// Variant of [c] for correct addressing with BP shifted by one point.
		struct {
			/* -------------------- */ point_t _shift_dummy;
			SPPoint start_ccw;
			/* -------------------- */ point_t _unused_1;
			/* -------------------- */ point_t _unused_2;
			SPPoint end_ccw;
			/* -------------------- */ point_t _unused_3;
			SPPoint origin_ccw;
			SPPoint ccw_to_cw_delta;
		} c_bp_shifted;

		// Screen-space points, converted from [c].
		struct {
			space_changing_point_t start_ccw;
			space_changing_point_t start_cw;
			space_changing_point_t end_cw;
			space_changing_point_t end_ccw;
		} p;

		// Final clipped points
		screen_point_t clipped[8];

		// BP reference points for stack offset calculation
		space_changing_point_t bp[8];
	} ps;

	// Same transformation as in lasers_render(), for LF_SHOOTOUT_DECAY.
	v_length_low = coords.width.nonshrink;
	v_length_high = 0;
	v_length <<= (SUBPIXEL_BITS - 1);

	ps.c.origin.x.v = (to_sp(PLAYFIELD_LEFT) + coords.origin.x);
	ps.c.origin.y.v = (to_sp(PLAYFIELD_TOP) + coords.origin.y);

	v_angle_low = coords.angle;
	v_angle_low += static_cast<uint8_t>(0x40);
	v_angle_high = 0;

	/// ps.c.ccw_to_cw_delta = vector2_at(
	/// 	ps.c.origin, (coords.width / 2), (coords.angle + 0x40)
	/// );
	lea_local_to_reg(v_ret_, &ps.bp[8], &ps.c.ccw_to_cw_delta);
	_BP -= (&ps.bp[8].sp /* current */ - &ps.c.origin /* target */);
	v_center = &_BP->sp;
	vector2_at_opt();

	/// ps.c.origin_ccw = vector2_at(
	/// 	ps.c.origin, (coords.width / 2), (coords.angle - 0x40)
	/// );
	/// ps.c.ccw_to_cw_delta -= ps.c.origin_ccw;
	v_angle_low += static_cast<uint8_t>(0x80);
	v_ret -= (
		&ps.c.ccw_to_cw_delta /* current */ - &ps.c.origin_ccw /* target */
	);
	ps.c_bp_shifted.ccw_to_cw_delta.y.v -= vector2_at_opt();
	ps.c_bp_shifted.ccw_to_cw_delta.x.v -= ps.c_bp_shifted.origin_ccw.x.v;

	/// ps.c.start_ccw = vector2_at(
	/// 	ps.c.origin_ccw, coords.starts_at_distance, coords.angle
	/// );
	v_angle_low = coords.angle;
	v_length = coords.starts_at_distance;
	v_ret -= (&ps.c.origin_ccw /* current */ - &ps.c.start_ccw /* target */);
	_BP -= (&ps.c.origin /* current */ - &ps.c.origin_ccw /* target */);
	v_center = &_BP->sp;
	vector2_at_opt();

	/// ps.c.end_ccw = vector2_at(
	/// 	ps.c.origin_ccw, coords.ends_at_distance, coords.angle
	/// );
	v_length = coords.ends_at_distance;
	v_ret += (&ps.c.end_ccw /* target */ - &ps.c.start_ccw /* current */);
	vector2_at_opt();

	/// ps.p.start_ccw = ps.c.start_ccw.to_pixel();
	/// ps.p.start_cw = (ps.c.start_ccw + ps.c.ccw_to_cw_delta).to_pixel();
	lea_local_to_reg(p_0_, &ps.bp[5], &ps.p.start_ccw);
	lea_local_to_reg(p_1_, &ps.bp[5], &ps.p.start_cw);
	p_distance = (&_BP->sp + p_distance_offset + (
		&ps.c.origin_ccw /* current */ - &ps.c.ccw_to_cw_delta /* target */
	));
	build_line_in_pixels();

	/// ps.p.end_ccw = ps.c.end_ccw.to_pixel();
	/// ps.p.end_cw = (ps.c.end_ccw + ps.c.ccw_to_cw_delta).to_pixel();
	p_0 += (&ps.p.end_ccw /* target */ - &ps.p.start_ccw /* current */);
	p_1 += (&ps.p.end_cw /* target */ - &ps.p.start_cw /* current */);
	build_line_in_pixels();

	// Return BP back to where you'd expect it to be
	_BP += (&ps.bp[8].sp /* target */ - &ps.c.origin_ccw /* current */);

	lea_local_to_reg(v_ret_, &ps.bp[8], &ps.clipped[0]);
	point_count = grc_clip_polygon_n(&v_ret->pixel, 8, &v_ret->pixel, 4);
	if(point_count == 0) {
		goto offscreen;
	}
	asm { jge draw; } /// if(point_count < 0) {
		point_count = 4;
	/// }

draw:
	grcg_polygon_cx(&v_ret->pixel, point_count);
	return false;

offscreen:
	return true;

	#undef point_count
	#undef _BP
}

void pascal near laser_hittest(Laser near& laser__)
{
	#define laser_         	_DI
	#define laser          	reinterpret_cast<Laser near *>(laser_)
	#define distance_start_	_SI
	#define distance_start 	static_cast<subpixel_t>(distance_start_)

	union {
		struct {
			SPPoint test_center;
			SPPoint origin;
		} c;

		// BP reference points for stack offset calculation
		SPPoint bp[2];
	} ps;

	// ZUN bloat: A reversed prolog and epilog means that we've got to
	// __emit__() *every* instruction that touches these registers... Luckily,
	// this function is simple enough, and doesn't need lots of comments to
	// describe what it does: generating boxes at fixed intervals along the
	// laser ray and hit-testing every one of them.
	__emit__(0x57); // PUSH DI
	__emit__(0x56); // PUSH SI

	mov_param_to_reg(laser_, 4); (laser__); /// laser_ = &laser__;

	mov_to_reg(
		v_length_, _DS, laser_, offsetof(Laser, coords.ends_at_distance)
	);
	mov_to_reg(
		distance_start_, _DS, laser_, offsetof(Laser, coords.starts_at_distance)
	);
	reinterpret_cast<SPPoint __ss *>(_BP) -= (
		&ps.bp[2] /* current */ - &ps.c.origin /* target */
	);
	v_center = reinterpret_cast<SPPoint __ss *>(_BP);
	mov_to_reg(_EAX, _DS, laser_, offsetof(Laser, coords.origin));
	mov_to_mem(_SS, v_center_, 0, _EAX);
	mov_to_reg(v_angle_low, _DS, laser_, offsetof(Laser, coords.angle));
	v_angle_high ^= v_angle_high;
	lea_local_to_reg(v_ret_, &ps.c.origin, &ps.c.test_center);

	loop: {
		_AX = vector2_at_opt();

		// ZUN quirk: 12×12-pixel boxes in 16-pixel intervals = 4-pixel gaps
		// between the boxes that allow the player to pass through the laser.
		if(overlap_1d_fast(_AX, player_pos.cur.y, to_sp(12.0f))) {
			mov_to_reg(_AX, _SS, v_ret_, offsetof(SPPoint, x));
			if(overlap_1d_fast(_AX, player_pos.cur.x, to_sp(12.0f))) {
				player_is_hit = true;
				goto ret;
			}
		}
		v_length -= to_sp(16.0f);
		cmp_reg_reg(v_length_, distance_start_);
		asm { jge loop; }
	}

ret:
	// Return BP back to where you'd expect it to be, allowing the function to
	// properly return.
	reinterpret_cast<SPPoint __ss *>(_BP) += (
		&ps.bp[2] /* target */ - &ps.c.origin /* current */
	);

	__emit__(0x5E); // POP SI
	__emit__(0x5F); // POP DI

	#undef distance_start
	#undef distance_start_
	#undef laser
	#undef laser_
}
