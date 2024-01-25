#include "th01/math/polar.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grpinv32.hpp"
#include "th01/hardware/scrollup.hpp"
#include "th01/formats/grc.hpp"

// Coordinates
// -----------

static const pixel_t KUJI_W = 32;
static const pixel_t KUJI_H = 32;

static const screen_x_t KUJI_CENTER_X = ((RES_X / 2) - (KUJI_W / 2));
static const screen_y_t KUJI_CENTER_Y = ((RES_Y / 2) - (KUJI_H / 2));
static const screen_x_t SQUARE_CENTER_X = ((RES_X / 2) - (32 / 2));
static const screen_y_t SQUARE_CENTER_Y = ((RES_Y / 2) - (32 / 2));
// -----------

void bomb_kuji_load(void)
{
	grc_load(GRC_SLOT_BOMB_KUJI_1, "kuzi1.grc");
	grc_load(GRC_SLOT_BOMB_KUJI_2, "kuzi2.grc");
}

bool16 bomb_update_and_render(int frame)
{
	enum {
		KUJI_COUNT = 9,
		KUJI_RINGS = 2,
		SQUARE_STACK = 3,
		SQUARE_RING = 16,

		KEYFRAME_ACTIVE = 50,
		KEYFRAME_DONE = 140,
	};

	extern const Palette4 palette_flash_peak_;

	// ZUN bloat: Only uses its V_WHITE value.
	static Palette4 palette_white;

	static Palette4 palette_flash_bright;
	static svc_comp_t white_to_blue_speed;

	static struct {
		screen_x_t left[(KUJI_COUNT * KUJI_RINGS) + 9]; // yup, 9 extra
		screen_y_t top[(KUJI_COUNT * KUJI_RINGS) + 9]; // yup, 9 extra
		unsigned char angle; // should be local

		pixel_t kuji_radius(const int& frame, const int& ring_offset) const {
			// Yup, this becomes negative near KEYFRAME_ACTIVE.
			return (500 - (ring_offset * 10) - ((frame + 60) * 4));
		}

		void square_invert(const int& frame, int factor) {
			// Could easily use local variables instead.
			left[0] = polar_x(
				SQUARE_CENTER_X, ((frame - KEYFRAME_ACTIVE) * factor), angle
			);
			top[0]  = polar_y(
				SQUARE_CENTER_Y, ((frame - KEYFRAME_ACTIVE) * factor), angle
			);
			graph_invert_32x32_8(left[0], top[0], VRAM_PLANE_B);
		}
	} entity;

	int i;
	int j;

	#define col 	i
	#define comp	j

	Palette4 palette_flash_peak = {
		0xF, 0xF, 0xF, // 0
		0xD, 0xD, 0xF, // 1
		0xD, 0xD, 0xF, // 2
		0xD, 0xD, 0xF, // 3
		0xD, 0xD, 0xF, // 4
		0xD, 0xD, 0xF, // 5
		0xD, 0xD, 0xF, // 6
		0xF, 0xF, 0xF, // 7 (V_WHITE)
		0xD, 0xD, 0xF, // 8
		0xD, 0xD, 0xF, // 9
		0xD, 0xD, 0xF, // 10
		0xD, 0xD, 0xF, // 11
		0xD, 0xD, 0xF, // 12
		0xD, 0xD, 0xF, // 13
		0xD, 0xD, 0xF, // 14
		0x6, 0x6, 0xF, // 15
	};

	player_invincible = true;
	if(frame == 0) {
		Pellets.decay();
		ptn_put_8(player_left, player_top, PTN_MIKO_L_CAST);

		for(col = 0; col < COLOR_COUNT; col++) {
			for(comp = 0; comp < COMPONENT_COUNT; comp++) {
				palette_white[col].v[comp] = z_Palettes[col].v[comp];
				palette_flash_bright[col].v[comp] = (
					(z_Palettes[col].v[comp] > 0x0A)
						? ((comp == 2) ? 0x0F : 0x0D)
						: (z_Palettes[col].v[comp] + comp)
				);
			}
		}

		white_to_blue_speed = -1;
	} else if(frame < KEYFRAME_ACTIVE) {
		if((frame % 2) == 0) {
			z_palette_set_show(V_WHITE,
				(palette_white[V_WHITE].c.r + white_to_blue_speed),
				(palette_white[V_WHITE].c.g + white_to_blue_speed),
				palette_white[V_WHITE].c.b
			);
		}
		if((frame % 4) == 0) {
			white_to_blue_speed = ((((frame % 80) / 40) == 0)
				? (white_to_blue_speed - 1)
				: (white_to_blue_speed + 1)
			);
		}
		if((frame % 2) == 0) {
			entity.angle = frame;

			#define kuji_i     	i
			#define ring_offset	j
			for(
				ring_offset = 0;
				ring_offset <= (KUJI_COUNT * (KUJI_RINGS - 1));
				ring_offset += KUJI_COUNT
			) {
				kuji_i = ring_offset;
				while((ring_offset + KUJI_COUNT) > kuji_i) {
					grc_sloppy_unput(entity.left[kuji_i], entity.top[kuji_i]);

					entity.left[kuji_i] = polar_x(
						KUJI_CENTER_X,
						entity.kuji_radius(frame, ring_offset),
						entity.angle
					);
					entity.top[kuji_i] = polar_y(
						KUJI_CENTER_Y,
						entity.kuji_radius(frame, ring_offset),
						entity.angle
					);

					if((ring_offset + GRC_IMAGES_PER_SLOT) != kuji_i) {
						grc_put_8(
							entity.left[kuji_i],
							entity.top[kuji_i],
							GRC_SLOT_BOMB_KUJI_1,
							(kuji_i - ring_offset),
							V_WHITE
						);
					} else {
						grc_put_8(
							entity.left[kuji_i],
							entity.top[kuji_i],
							GRC_SLOT_BOMB_KUJI_2,
							0,
							V_WHITE
						);

					}
					kuji_i++;
					entity.angle += (0x100 / KUJI_COUNT);
				}
				entity.angle = -frame;
			}
			#undef ring_offset
			#undef kuji_i
		}
		if((frame % 30) == 0) {
			mdrv2_se_play(8);
		}
		if((frame % 10) == 0) {
			Pellets.decay();
		}
	} else if(frame == KEYFRAME_ACTIVE) {
		for(i = 0; i < (KUJI_COUNT * KUJI_RINGS); i++) {
			grc_sloppy_unput(entity.left[i], entity.top[i]);
		}
		bomb_damaging = true;
	} else if((frame > KEYFRAME_ACTIVE) && (frame < KEYFRAME_DONE)) {
		if((frame % 10) == 0) {
			mdrv2_se_play(9);
		}

		if((frame % 4) == 0) {
			z_palette_set_all_show(palette_flash_peak);
		} else if((frame % 4) == 2) {
			z_palette_set_all_show(palette_flash_bright);
		}

		if((frame % 16) == 0) {
			z_vsync_wait_and_scrollup(RES_Y - 8);
		} else if((frame % 16) == 4) {
			z_vsync_wait_and_scrollup(RES_Y - 0);
		} else if((frame % 16) == 8) {
			z_vsync_wait_and_scrollup(RES_Y - 16);
		} else if((frame % 16) == 12) {
			z_vsync_wait_and_scrollup(RES_Y - 0);
		} else if((frame % 8) == 0) { // never actually executed
			Pellets.decay();
		}

		for(
			(i = 0, entity.angle = 0x00);
			i < SQUARE_RING;
			(i++, entity.angle += (0x100 / SQUARE_RING))
		) {
			// SQUARE_STACK times.
			entity.square_invert(frame, 6);
			entity.square_invert(frame, 7);
			entity.square_invert(frame, 8);
		}

		if((frame % 20) == 0) {
			for(col = 0; col < COLOR_COUNT; col++) {
				for(comp = 0; comp < COMPONENT_COUNT; comp++) {
					palette_flash_bright.colors[col].v[comp] += (
						(palette_flash_bright[col].v[comp] < 0x0F) ? 1 : 0
					);
				}
			}
		}
	} else if(frame == KEYFRAME_DONE) {
		z_vsync_wait_and_scrollup(0);

		graph_accesspage_func(1);
		graph_copy_accessed_page_to_other();
		graph_accesspage_func(0);

		z_palette_set_all_show(stage_palette);

		player_invincibility_time = 100;

		bomb_damaging = false;
		return true;
	}

	return false;

	#undef comp
	#undef col
}
