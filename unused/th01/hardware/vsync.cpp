#include "pc98.h"

extern bool16 vsync_callback_is_set = false;
static void (*vsync_callback)(void);

// Unused mouse cursor (?!)
// -------------------

// (These meanings are just a guess.)
static screen_x_t MOUSE_MIN_X;
static screen_y_t MOUSE_MIN_Y;
static screen_x_t MOUSE_MAX_X;
static screen_x_t MOUSE_MAX_Y;
static int8_t mouse_unused;
#include "th01/sprites/mousecur.csp"
// -------------------

void vsync_callback_set(void (*vsync_callback_new)());
void vsync_callback_clear(void);
