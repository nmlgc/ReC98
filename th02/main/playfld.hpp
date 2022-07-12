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
#define PLAYFIELD_TRAM_TOP (PLAYFIELD_TOP / 16)
#define PLAYFIELD_TRAM_W (PLAYFIELD_W / 8)
#define PLAYFIELD_TRAM_CENTER_X \
	((PLAYFIELD_LEFT + (PLAYFIELD_W / 2)) / GLYPH_HALF_W)
#define PLAYFIELD_TRAM_CENTER_Y \
	((PLAYFIELD_TOP + (PLAYFIELD_H / 2)) / GLYPH_H)
#define PLAYFIELD_TRAM_RIGHT (PLAYFIELD_RIGHT / 8)
#define PLAYFIELD_TRAM_BOTTOM (PLAYFIELD_BOTTOM / 16)

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

#ifdef SUBPIXEL_HPP
	struct PlayfieldPoint : public SPPoint {
		screen_x_t to_screen_left(pixel_t sprite_w_if_centered = 0) const {
			return (PLAYFIELD_LEFT + x.to_pixel() - (sprite_w_if_centered / 2));
		}

		screen_y_t to_screen_top(pixel_t sprite_h_if_centered = 0) const {
			return (PLAYFIELD_TOP + y.to_pixel() - (sprite_h_if_centered / 2));
		}

		#ifdef SCROLL_HPP
			vram_y_t to_vram_top_scrolled_seg3(
				pixel_t sprite_h_if_centered
			) const {
				return scroll_subpixel_y_to_vram_seg3(
					y + (PLAYFIELD_TOP - (sprite_h_if_centered / 2))
				);
			}
		#endif
	};
#endif

#include "th01/main/playfld.hpp"
