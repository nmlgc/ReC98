#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"

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

static const int PYRO_COUNT = 256;
pyro_t pyros[PYRO_COUNT];

char zun00_pi[] = "zun00.pi";
char logo[] = "logo";
char zun02_bft[] = "zun02.bft";
char zun04_bft[] = "zun04.bft";
char zun01_bft[] = "zun01.bft";
char zun03_bft[] = "zun03.bft";
