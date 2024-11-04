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

// Shows the animation that changes the size of the box.
void near box_main_to_submenu_animate(void);
void near box_submenu_to_main_animate(void);
