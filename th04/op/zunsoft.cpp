#include "platform.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/op/zunsoft.h"

// Copy of the palette used during the logo, to allow non-blocking fades in
// contrast to master.lib's blocking palette_black_in() and palette_black_out()
// functions. (Then again, master.lib has the PaletteTone global for that...)
Palette8 zunsoft_palette;

// ZUN Soft logo explosion structure.
// These are only animated by increasing the distance; origin, angle, and speed
// stay constant.
struct pyro_t {
	bool alive;
	uint8_t age;
	SPPoint origin;
	Subpixel distance_prev; // ZUN bloat: Unused.
	Subpixel distance;
	Subpixel speed;
	unsigned char angle;
	unsigned char patnum_base; // displayed sprite is incremented every 4 frames
};

// Spawns [n] new explosions at the given screen-coordinate [origin] position.
void pascal zunsoft_pyro_new(screen_point_t origin, int n, char patnum_base)
;

void zunsoft_update_and_render(void)
;

void zunsoft_palette_update_and_show(int tone)
;

static const int PYRO_COUNT = 256;
pyro_t pyros[PYRO_COUNT];

char zun00_pi[] = "zun00.pi";
char logo[] = "logo";
char zun02_bft[] = "zun02.bft";
char zun04_bft[] = "zun04.bft";
char zun01_bft[] = "zun01.bft";
char zun03_bft[] = "zun03.bft";
