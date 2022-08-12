#include "th01/math/clamp.hpp"
#include "th01/main/hud/menu.hpp"
#include "th01/shiftjis/hud.hpp"

// Pause menu
// ----------

// Not quite the center.
static const screen_x_t PAUSE_CENTER_X = (PLAYFIELD_CENTER_X - GLYPH_HALF_W);

inline screen_y_t pause_top(int line) {
	return (PLAYFIELD_TOP + ((PLAYFIELD_H / 21) * 4) + (line * GLYPH_H));
}

void z_palette_settone_but_keep_white(int tone)
{
	int col;
	int comp;

	for(col = 0; col < COLOR_COUNT; col++) {
		if(col == V_WHITE) {
			continue;
		}
		for(comp = 0; comp < COMPONENT_COUNT; comp++) {
			z_Palettes[col].v[comp] = ((z_Palettes[col].v[comp]) * tone / 100);

			// ZUN bloat: Already done by z_palette_set_all_show().
			if(z_Palettes[col].v[comp] < 0x0) {
				z_Palettes[col].v[comp] = 0x0;
			}

			if(z_Palettes[col].v[comp] > 0xF) {
				z_Palettes[col].v[comp] = 0xF;
			}
		}
	}
	z_palette_set_all_show(z_Palettes);
}

inline void pause_cursor_unput(screen_x_t  left) {
	egc_copy_rect_1_to_0_16(
		left, pause_top(1), shiftjis_w(PAUSE_CURSOR), GLYPH_H
	);
}

inline void pause_cursor_put(screen_x_t left, const shiftjis_t* str) {
	graph_putsa_fx(left, pause_top(1), V_WHITE, str);
}

inline void pause_str_put(screen_x_t left, int line, const shiftjis_t* str) {
	graph_putsa_fx(left, pause_top(line), (V_WHITE | FX_WEIGHT_BLACK), str);
}

#define pause_select_loop(ret, sel_0_left, sel_1_left) { \
	while(paused) { \
		input_sense(false); \
		/**
		 * ZUN bloat: Just replace with \
		 * \
		 * 	((input_shot == true) && (input_ok == true)) \
		 * \
		 * No need to complicate input handling and abuse this variable. \
		 * (And yes, you *can* trigger this one instead of the `break` case \
		 * below. \
		 */ \
		if(player_is_hit == true) { \
			return true; \
		} \
		if(input_lr == INPUT_LEFT) { \
			pause_cursor_unput(sel_1_left); \
			pause_cursor_put(sel_0_left, PAUSE_CURSOR); \
			sel = 0; \
		} \
		if(input_lr == INPUT_RIGHT) { \
			pause_cursor_unput(sel_0_left); \
			pause_cursor_put(sel_1_left, PAUSE_CURSOR); \
			sel = 1; \
		} \
		if(input_shot || input_ok) { \
			break; \
		} \
		frame_delay(1); \
	} \
}

bool16 pause_menu(void)
{
	enum {
		PAUSE_TITLE_W = shiftjis_w(PAUSE_TITLE),
		PAUSE_CHOICES_W = shiftjis_w(PAUSE_CHOICES),
		PAUSE_TITLE_LEFT = (PAUSE_CENTER_X - (PAUSE_TITLE_W / 2)),
		PAUSE_CHOICES_LEFT = (PAUSE_CENTER_X - (PAUSE_CHOICES_W / 2)),
		PAUSE_CHOICE_0_LEFT = PAUSE_CHOICES_LEFT,
		PAUSE_CHOICE_1_LEFT = (
			PAUSE_CHOICE_0_LEFT + shiftjis_w(PAUSE_CHOICE_0)
		),

		QUIT_TITLE_W = shiftjis_w(QUIT_TITLE),
		QUIT_CHOICES_W = shiftjis_w(QUIT_CHOICES),
		QUIT_TITLE_LEFT = (PAUSE_CENTER_X - (QUIT_TITLE_W / 2)),
		QUIT_CHOICES_LEFT = (PAUSE_CENTER_X - (QUIT_CHOICES_W / 2)),
		QUIT_CHOICE_0_LEFT = QUIT_CHOICES_LEFT,
		QUIT_CHOICE_1_LEFT = (QUIT_CHOICE_0_LEFT + shiftjis_w(QUIT_CHOICE_0)),

		TITLE_W = max_macro(PAUSE_TITLE_W, QUIT_TITLE_W),
		OPTIONS_W = max_macro(PAUSE_CHOICES_W, QUIT_CHOICES_W),
		MENU_W = max_macro(TITLE_W, OPTIONS_W),
	};

	int8_t sel = 0;

	pause_str_put(PAUSE_TITLE_LEFT, 0, PAUSE_TITLE);
	pause_str_put(PAUSE_CHOICES_LEFT, 1, PAUSE_CHOICES);
	pause_cursor_put(PAUSE_CHOICE_0_LEFT, PAUSE_CURSOR_INITIAL);
	z_palette_settone_but_keep_white(40);

	input_reset_menu_related();
	pause_select_loop(sel, PAUSE_CHOICE_0_LEFT, PAUSE_CHOICE_1_LEFT);

	// ZUN bug: Wrong left coordinate. Thankfully doesn't matter due to that
	// function's word alignment.
	egc_copy_rect_1_to_0_16(
		(PAUSE_TITLE_LEFT + 4), pause_top(0), shiftjis_w(PAUSE_TITLE), GLYPH_H
	);
	egc_copy_rect_1_to_0_16(
		PAUSE_CHOICES_LEFT, pause_top(1), shiftjis_w(PAUSE_CHOICES), GLYPH_H
	);

	frame_delay(20);
	input_reset_menu_related();
	if((sel != 0) && paused) {
		pause_str_put(QUIT_TITLE_LEFT, 0, QUIT_TITLE);
		pause_str_put(QUIT_CHOICES_LEFT, 1, QUIT_CHOICES);
		pause_cursor_put(QUIT_CHOICE_0_LEFT, PAUSE_CURSOR);
		sel = 0;
		pause_select_loop(sel, QUIT_CHOICE_0_LEFT, QUIT_CHOICE_1_LEFT);

		if(sel != 0) {
			resident_continue_use();
			return true;
		}
	}

	z_palette_set_all_show(stage_palette);
	input_reset_sense();

	// ZUN bug: Same as above.
	egc_copy_rect_1_to_0_16(
		((PAUSE_CENTER_X - (MENU_W / 2)) + 8),
		pause_top(0),
		MENU_W,
		(pause_top(2) - pause_top(0))
	);

	return false;
}
// -----------

#include "th01/main/bullet/pellet_s.cpp"
