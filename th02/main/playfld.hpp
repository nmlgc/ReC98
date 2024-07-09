#define PLAYFIELD_LEFT (32)
#define PLAYFIELD_TOP (16)
#define PLAYFIELD_W (384)
#define PLAYFIELD_H (368)

#define PLAYFIELD_RIGHT (PLAYFIELD_LEFT + PLAYFIELD_W)
#define PLAYFIELD_BOTTOM (PLAYFIELD_TOP + PLAYFIELD_H)

#define PLAYFIELD_VRAM_LEFT (PLAYFIELD_LEFT / BYTE_DOTS)
#define PLAYFIELD_VRAM_W (PLAYFIELD_W / BYTE_DOTS)
#define PLAYFIELD_VRAM_RIGHT (PLAYFIELD_RIGHT / BYTE_DOTS)

#define PLAYFIELD_TRAM_LEFT (PLAYFIELD_LEFT / 8)
#define PLAYFIELD_TRAM_TOP (PLAYFIELD_TOP / GLYPH_H)
#define PLAYFIELD_TRAM_W (PLAYFIELD_W / 8)
#define PLAYFIELD_TRAM_CENTER_X \
	((PLAYFIELD_LEFT + (PLAYFIELD_W / 2)) / GLYPH_HALF_W)
#define PLAYFIELD_TRAM_CENTER_Y \
	((PLAYFIELD_TOP + (PLAYFIELD_H / 2)) / GLYPH_H)
#define PLAYFIELD_TRAM_RIGHT (PLAYFIELD_RIGHT / 8)
#define PLAYFIELD_TRAM_BOTTOM (PLAYFIELD_BOTTOM / GLYPH_H)

/// Workarounds for the lack of clipping in master.lib's super_*() functions
/// ------------------------------------------------------------------------
/// ZUN bug: These functions ignore not only the grc_setclip() region, but also
/// at least the left and right edges of VRAM. They always blit any sprite at
/// its full size to the naively calculated ((top * ROW_SIZE) + left) offset,
/// incorrectly wrapping around at the horizontal edges into the previous
/// (left) or next (right) row. While the *_roll_*() functions do have to
/// correctly wrap at the top and bottom edges of VRAM, the non-rolling ones
/// don't, falling back on the hardware's unhelpful wrapping around the 0x8000
/// offset limit for VRAM segments.
/// (Yes, the hardware ANDs VRAM offsets with 0x7FFF before a write, but this
/// does *not* mean that such offsets are wrapped vertically. 0x8000 is not a
/// multiple of the ROW_SIZE, and any pixels wrapped this way would be
/// horizontally shifted by 384 pixels.)
///
/// For this reason, any sprite larger than the 32×16 (non-rolling) or 32×32
/// (rolling) playfield margin must be clipped earlier than the technically
/// correct position. The smallest allowed top-left coordinate in screen space
/// therefore is
///
/// 	(  0,   0) non-rolling / (  0, -16) rolling,
///
/// and the bottom-right coordinate must never reach
///
/// 	(448, 400) non-rolling / (448, 416) rolling.
///
/// This is the only way to avoid glitches from master.lib's incorrect
/// wraparounds, such as HUD background or tile source area corruption. Since
/// these larger sprites can still be displayed at the calculated clipping
/// point, we use < and > for the clipping condition. For smaller sprites, we
/// instead use ≤ and ≥ to clip them as early as possible.
///
/// (Technically, non-rolling sprites could even extend into the invisible 9.6
/// rows of VRAM between offsets 0x7D00 and 0x7FFF inclusive, which would allow
/// them to be clipped 9 pixels later. These rows are not used for anything
/// else, and could be overwritten without observable effects. Thankfully, ZUN
/// doesn't make use of this.)
///
/// ZUN bloat: Unfortunately, Turbo C++ 4.0J can't constant-fold the ternary
/// expressions that would allow us to abstract away the difference between
/// small and large sprites. This forces us to duplicate every macro, and every
/// call site to spell out which of these two it wants to use. Then again, ZUN
/// even forces us to, as certain rendering functions actually use the
/// incorrect variant...
///
/// These macros should only be used in rendering code. This allows all usages
/// to share the same ZUN bug, and to be fixed simultaneously without affecting
/// gameplay. For clipping checks that *are* supposed to influence gameplay,
/// use the playfield_encloses*() functions further below, which always clip
/// correctly and without this workaround.

#define PLAYFIELD_CLIP_RIGHT (HUD_LEFT * GLYPH_HALF_W)

// Sum of the top and bottom margin. Rolled sprites can be freely blitted
// within this area where they will consequently wrap vertically at the edge of
// the screen, but these wrapped pixels won't be visible because they're always
// covered by opaque black TRAM cells.
#define PLAYFIELD_ROLL_MARGIN (PLAYFIELD_TOP + (RES_Y - PLAYFIELD_BOTTOM))

#define playfield_clip_center_left_small(center_x, w) ( \
	center_x <= to_sp((w / 2) - PLAYFIELD_LEFT) \
)
#define playfield_clip_center_left_large(center_x, w) ( \
	center_x <  to_sp((w / 2) - PLAYFIELD_LEFT) \
)

#define playfield_clip_center_right_small(center_x, w) ( \
	center_x >= to_sp(PLAYFIELD_CLIP_RIGHT - PLAYFIELD_LEFT - (w / 2)) \
)
#define playfield_clip_center_right_large(center_x, w) ( \
	center_x >  to_sp(PLAYFIELD_CLIP_RIGHT - PLAYFIELD_LEFT - (w / 2)) \
)

#define playfield_clip_center_top_small_roll(center_y, h) ( \
	center_y <= to_sp((h / 2) - PLAYFIELD_ROLL_MARGIN) \
)
#define playfield_clip_center_top_large_roll(center_y, h) ( \
	center_y <  to_sp((h / 2) - PLAYFIELD_ROLL_MARGIN) \
)

#define playfield_clip_center_bottom_small_roll(center_y, h) ( \
	center_y >= to_sp(PLAYFIELD_H + PLAYFIELD_ROLL_MARGIN - (h / 2)) \
)
#define playfield_clip_center_bottom_large_roll(center_y, h) ( \
	center_y >  to_sp(PLAYFIELD_H + PLAYFIELD_ROLL_MARGIN - (h / 2)) \
)

#define playfield_clip_left_small( left, w) (left <= (PLAYFIELD_LEFT - w))
#define playfield_clip_right_small(left, w) (left >= PLAYFIELD_RIGHT)

#define playfield_clip_left_large( left, w) (left < 0)
#define playfield_clip_right_large(left, w) (left > (PLAYFIELD_CLIP_RIGHT - w))

#define playfield_clip_top_small(   top, h) (top <= (PLAYFIELD_TOP - h))
#define playfield_clip_bottom_small(top, h) (top >= PLAYFIELD_BOTTOM)

// Also working with unsigned [top] values.
#define playfield_clip_top_large(   top, h) (top < 0)
#define playfield_clip_bottom_large(top, h) (top > (RES_Y - h))

#define playfield_clip_topleft_small(left, top, w, h) ( \
	playfield_clip_left_small(left, w) || \
	playfield_clip_right_small(left, w) || \
	playfield_clip_top_small(top, h) || \
	playfield_clip_bottom_small(top, h) \
)
#define playfield_clip_topleft_large(left, top, w, h) ( \
	playfield_clip_left_large(left, w) || \
	playfield_clip_right_large(left, w) || \
	playfield_clip_top_large(top, h) || \
	playfield_clip_bottom_large(top, h) \
)

#define playfield_clip_center_yx_small_roll(center_x, center_y, w, h) ( \
	(playfield_clip_center_top_small_roll((subpixel_t)(center_y), h)) || \
	(playfield_clip_center_bottom_small_roll((subpixel_t)(center_y), h)) || \
	(playfield_clip_center_left_small((subpixel_t)(center_x), w)) || \
	(playfield_clip_center_right_small((subpixel_t)(center_x), w)) \
)
#define playfield_clip_center_yx_large_roll(center_x, center_y, w, h) ( \
	(playfield_clip_center_top_large_roll((subpixel_t)(center_y), h)) || \
	(playfield_clip_center_bottom_large_roll((subpixel_t)(center_y), h)) || \
	(playfield_clip_center_left_large((subpixel_t)(center_x), w)) || \
	(playfield_clip_center_right_large((subpixel_t)(center_x), w)) \
)

#define playfield_clip_point_yx_small_roll(center, w, h) \
	playfield_clip_center_yx_small_roll(center.x, center.y, w, h)
#define playfield_clip_point_yx_large_roll(center, w, h) \
	playfield_clip_center_yx_large_roll(center.x, center.y, w, h)
/// ------------------------------------------------------------------------

#define playfield_encloses_yx_lt_ge(center_x, center_y, w, h) ( \
	/* Casting the center coordinate allows this macro to easily be used */ \
	/* with the _AX and _DX pseudoregisters after motion_update(). */ \
	(static_cast<subpixel_t>(center_y) >= to_sp(0 - (h  / 2))) && \
	(static_cast<subpixel_t>(center_y) < to_sp(PLAYFIELD_H + (h / 2))) && \
	(static_cast<subpixel_t>(center_x) >= to_sp(0 - (w / 2))) && \
	(static_cast<subpixel_t>(center_x) < to_sp(PLAYFIELD_W + (w / 2))) \
)

#define playfield_encloses(center_x, center_y, w, h) ( \
	/* Casting the center coordinate allows this macro to easily be used */ \
	/* with the _AX and _DX pseudoregisters after motion_update(). */ \
	(static_cast<subpixel_t>(center_x) > to_sp(0 - (w / 2))) && \
	(static_cast<subpixel_t>(center_x) < to_sp(PLAYFIELD_W + (w / 2))) && \
	(static_cast<subpixel_t>(center_y) > to_sp(0 - (h  / 2))) && \
	(static_cast<subpixel_t>(center_y) < to_sp(PLAYFIELD_H + (h / 2))) \
)

#define playfield_encloses_point(center, w, h) \
	playfield_encloses(center.x, center.y, w, h)

#define playfield_to_screen_left(subpixel_center_x, sprite_w) ( \
	PLAYFIELD_LEFT + TO_PIXEL(subpixel_center_x) - (sprite_w / 2) \
)

#define playfield_to_screen_top(subpixel_center_y, sprite_h) ( \
	PLAYFIELD_TOP + TO_PIXEL(subpixel_center_y) - (sprite_h / 2) \
)

#include "th01/main/playfld.hpp"
