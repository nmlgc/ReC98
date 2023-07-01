#include "platform/x86real/pc98/page.hpp"
#include "th01/hardware/grp2xscs.hpp"
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
	svc2 col;
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

	// ZUN landmine: Wrong left coordinate. Thankfully doesn't matter due to
	// that function's word alignment.
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

	// ZUN landmine: Same as above.
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

// Continue menu
// -------------

enum continue_line_t {
	TITLE, YES_SELECTED, NO_SELECTED, YES, NO
};

inline void continue_back_put(
	continue_line_t line, th01_vram_colors_t col, const shiftjis_t str[]
) {
	graph_putsa_fx(
		0, (line * GLYPH_H), (FX_CLEAR_BG | FX_WEIGHT_BOLD | col), str
	);
}

inline void continue_back_2xscale_to_front(
	screen_x_t left_0, screen_y_t top_0, pixel_t w, continue_line_t line
) {
	graph_2xscale_byterect_1_to_0_slow(
		left_0, top_0, 0, (line * GLYPH_H), w, GLYPH_H
	);
}

inline void continue_choice_put(continue_line_t line) {
	continue_back_2xscale_to_front(
		((RES_X / 2) - (GLYPH_FULL_W * 2)),
		((RES_Y / 2) + (((line - YES_SELECTED) % 2) * (GLYPH_H * 2))),
		CONTINUE_CHOICE_W,
		line
	);
}

inline void continue_choice_render(bool yes) {
	continue_choice_put(yes ? YES_SELECTED : YES);
	continue_choice_put(yes ? NO : NO_SELECTED);
}

bool16 continue_menu(void)
{
	bool16 sel;
	unsigned int frames = 0;

	graph_copy_page_to_other(1);
	page_access(1);
	continue_back_put(TITLE, V_WHITE, CONTINUE_TITLE);
	continue_back_put(YES_SELECTED, V_WHITE, CONTINUE_YES_1);
	continue_back_put(NO_SELECTED, V_WHITE, CONTINUE_NO_1);
	continue_back_put(YES, V_GRAY, CONTINUE_YES_2);
	continue_back_put(NO, V_GRAY, CONTINUE_NO_2);

	page_access(0);
	continue_back_2xscale_to_front(
		(RES_X / 4), PLAYFIELD_TOP, CONTINUE_TITLE_W, TITLE
	);

	continue_choice_render(true);
	sel = true;
	input_ok = false;
	paused = false;
	input_shot = false;
	input_reset_sense();

	// If we don't, we quit back to the main menu anyway.
	resident_continue_use();
	if(resident->score_highest < score) {
		resident->score_highest = score;
	}
	resident->score = 0;
	resident->rem_lives = (resident->credit_lives_extra + 2);
	pellet_speed_lower(-2, -5);

	while(1) {
		input_sense(false);
		frames++;
		frame_delay(1);

		if((input_ok == true) || (input_shot == true)) {
			if(sel == true) {
				resident->snd_need_init = false;
				resident->point_value = 0;
				game_switch_binary(EP_MAIN);
			} else {
				no_continue:
				player_is_hit = false;
				paused = false;
				mdrv2_bgm_stop();
				return false;
			}
		}
		if(frames > 3000) {
			goto no_continue;
		}
		if(paused == true) {
			player_is_hit = false;
			paused = false;
			return false;
		}
		if(input_up == true) {
			sel = true;
			continue_choice_render(true);
		}
		if(input_down == true) {
			sel = false;
			continue_choice_render(false);
		}
	};
}
// -------------
