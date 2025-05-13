#include "th03/sprites/opwin.hpp"

// Coordinates
// -----------

static const pixel_t BOX_H = OPWIN_H;
static const pixel_t MAIN_W = 136;
static const pixel_t SUBMENU_W = 240;

static const screen_x_t BOX_LEFT = 160;
static const screen_y_t BOX_TOP = 256;

static const screen_y_t BOX_BOTTOM = (BOX_TOP + BOX_H);
static const screen_x_t BOX_MAIN_RIGHT = (BOX_LEFT + MAIN_W);
static const screen_x_t BOX_MAIN_CENTER_X = (BOX_LEFT + (MAIN_W / 2));
static const screen_x_t BOX_SUBMENU_CENTER_X = (BOX_LEFT + (SUBMENU_W / 2));
static const screen_x_t BOX_SUBMENU_RIGHT = (BOX_LEFT + SUBMENU_W);
// -----------

// Restores the 16×[BOX_H]-pixel column starting at ([left], BOX_TOP) from
// VRAM page 1. Returns with page 0 as the accessed page.
void pascal near box_column16_unput(uscreen_x_t left);

// Animates the box from its current width of [w_cur] to a width of [w_target].
// Does nothing if both values are identical.
void pascal near box_animate(pixel_t w_cur, pixel_t w_target);

// Shows either the long (shifting kanji and flashing) or short (just fading)
// title animation. Both of these return with the title image blitted to both
// VRAM pages, page 0 both accessed and shown, and parts 1 and 3 of the
// character selection CDG images loaded.
void near op_animate(void);
void near op_fadein_animate(void);
