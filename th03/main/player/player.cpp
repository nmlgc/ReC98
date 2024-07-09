#pragma option -G

#include "decomp.hpp"
#include "th03/common.h"
#include "th03/main/player/player.hpp"

// Enforces signed 8-bit comparisons in one place. MODDERS: Just remove these.
inline int8_t collmap_byte_x_min(void) { return 0; }
inline int8_t collmap_byte_x_max(void) { return COLLMAP_MEMORY_W; }

void near pascal player_hittest(collmap_tile_amount_t hitbox_size)
{
	#define hitbox_radius    	static_cast<collmap_tile_amount_t>(_AX)
	#define tile_top         	static_cast<collmap_tile_amount_t>(_AX)
	#define tile_top_low     	static_cast<uint8_t>(_AL)
	#define tile_y           	static_cast<uint8_t>(_AH)
	#define collmap_p        	reinterpret_cast<uint8_t near *>(_BX)
	#define bottom_wide      	static_cast<collmap_tile_amount_t>(_BX)
	#define tile_w_wide      	static_cast<collmap_tile_amount_t>(_BX)
	#define tile_w           	static_cast<uint8_t>(_BL)
	#define bottom           	static_cast<uint8_t>(_BL)
	#define top              	static_cast<collmap_tile_amount_t>(_CX)
	#define first_bit_wide   	static_cast<int16_t>(_CX)
	#define column_stride_wide	static_cast<collmap_tile_amount_t>(_CX)
	#define first_bit        	static_cast<uint8_t>(_CL)
	#define column_stride    	static_cast<uint8_t>(_CL)
	#define mask             	static_cast<uint8_t>(_CH)
	#define column_stride_high	static_cast<uint8_t>(_CH)
	#define left             	static_cast<collmap_tile_amount_t>(_DX)
	#define byte_x_wide      	static_cast<collmap_tile_amount_t>(_DX)
	#define byte_x           	static_cast<int8_t>(_DL)
	#define byte_x_high      	static_cast<int8_t>(_DH)
	#define tile_bottom      	static_cast<uint8_t>(_DH)
	collmap_tile_amount_t tile_top_;
	unsigned char tile_bottom_; // collmap_tile_amount_t

	player_t near &player = *player_cur;
	collmap_tile_amount_t tile_w_remaining;

	if((player.invincibility_time != 0) || player.hyper_active) {
		optimization_barrier();
		return;
	}

	bottom_wide = hitbox_radius = hitbox_size;
	hitbox_radius >>= 1;

	left = player.center.x.v;
	left >>= (SUBPIXEL_BITS + COLLMAP_TILE_W_BITS);
	left -= hitbox_radius;
	top = player.center.y.v;
	top >>= (SUBPIXEL_BITS + COLLMAP_TILE_H_BITS);
	top -= hitbox_radius;
	bottom_wide += top;

	// if(top < 0) { top = 0; }. As simple as that, but Turbo C++ can only
	// generate the superior `OR CX, CX` here. Since the 0 here is only 8 bits
	// wide, we can't even use keep_0().
	asm { cmp	cx, 0; }
	asm { jge	above_0; }
	top = 0;
	goto clip_y_done;

above_0:
	if(bottom_wide >= COLLMAP_H) {
		bottom_wide = (COLLMAP_H - 1);
	}
clip_y_done:

	tile_bottom_ = bottom;
	tile_top_ = top;
	first_bit_wide = left;

	// first_bit_wide &= (8 - 1);. Using a 16-bit-immediate for some reason.
	asm { and	cx, (8 - 1); }
	// byte_x_wide = (left >> 3);
	byte_x_wide >>= 3;

	// Enlarge the width by the position of the first bit…? Required for every
	// single overly clever calculation below that involves this variable.
	tile_w_remaining = hitbox_size;
	tile_w_remaining += first_bit_wide;

	mask = 0xFF;
	mask >>= first_bit;
	tile_w_wide = tile_w_remaining;

	// Remove tiles from the right of the initial pattern if the rectangle is
	// less than 8 tiles wide. After the addition above, any rectangle that
	// spans more than one byte (and thus, doesn't need tiles removed here)
	// will have [tile_w] > 8. That addition is also required for this bit
	// twiddling hack to work correctly, since the removed tiles are past both
	// the first bit and the width in tiles.
	//
	// An example with [first_bit] = 2 and an original [tile_w] of 4:
	// • [mask] >> [first_bit]: 00111111
	// •   Tiles to be removed: 00000011 (11111111 >> (4 + 2))
	// •          Final [mask]: 00111100
	if(tile_w_wide <= 8) {
		_BH = 0xFF;
		_BH >>= tile_w;
		mask ^= _BH;
	}

	// collmap_p = &collmap[pid.current][byte_x][tile_top];
	_AL = byte_x;
	_BL = COLLMAP_H;
	asm { mul	bl; }
	collmap_p = &collmap[0][0][0];
	collmap_p += _AX;
	if(pid.current == 1) {
		collmap_p += COLLMAP_SIZE;
	}
	collmap_p += tile_top_;

	tile_bottom = tile_bottom_;
	tile_top = tile_top_;
	do {
		if(byte_x >= collmap_byte_x_max()) {
			break;
		}
		// Might have been more appropriate to do this clipping at the top!
		if(byte_x >= collmap_byte_x_min()) {
			tile_y = tile_top_low;
			column_stride = COLLMAP_H;
			do {
				if(*collmap_p & mask) {
					byte_x_high ^= byte_x_high;
					// byte_x_wide *= (SUBPIXEL_FACTOR * COLLMAP_TILE_W * 8);
					byte_x_wide <<= (SUBPIXEL_BITS + COLLMAP_TILE_W_BITS + 3);

					player_hittest_collision_top.x.v = byte_x_wide;
					tile_y = 0;
					player_hittest_collision_top.y.v = (tile_top * (
						static_cast<long>(SUBPIXEL_FACTOR * COLLMAP_TILE_H)
					));
					player.is_hit = true;
					return;
				}
				collmap_p++;
				column_stride--;
				tile_y++;
			} while(tile_y < tile_bottom);
		}
		byte_x++;
		column_stride_high = 0x00;
		collmap_p += column_stride_wide;
		tile_w_remaining -= 8;

		// mask = (tile_w_remaining < 8) ? ~(0xFF >> tile_w_remaining) : 0xFF;
		//
		// Since we consistently subtract 8, [tile_w_remaining] will only have
		// the correct amount of carry tiles if we previously added [first_bit]
		// to it (which we did).
		// And while that cast is technically wrong, it thankfully has no
		// consequences, since this loop will terminate anyway if
		// [tile_w_remaining] is ≤0.
		mask = 0xFF;
		if(static_cast<uint16_t>(tile_w_remaining) < 8) {
			first_bit_wide = tile_w_remaining;
			mask = 0xFF; // so optimized, wow
			mask >>= first_bit;
			asm { not ch; } // mask = ~mask;
		}
	} while(tile_w_remaining > 0);

	#undef tile_bottom
	#undef byte_x_high
	#undef byte_x
	#undef byte_x_wide
	#undef left
	#undef column_stride_high
	#undef mask
	#undef column_stride
	#undef first_bit
	#undef column_stride_wide
	#undef first_bit_wide
	#undef top
	#undef bottom
	#undef tile_w
	#undef tile_w_wide
	#undef bottom_wide
	#undef collmap_p
	#undef tile_y
	#undef tile_top_low
	#undef tile_top
	#undef hitbox_radius
}
