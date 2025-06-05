/// Basic code shared among all blitting benchmark tests
/// ----------------------------------------------------

#include "pc98.h"

#ifndef CPU
	#error CPU macro not defined
#endif

// Macro stringification helpers
#define _(x) __(x)
#define __(x) #x

enum option_type_t {
	OPT_SPRITE_COUNT,
	OPT_DURATION,
	OPT_SPRITE_COL,
	OPT_COUNT,
	OPT_INVALID = -1
};

struct Option {
	char cmd_c;
	const char* desc;
	uint16_t val;
	uint16_t min;
	uint16_t max;
};

struct Test {
	Option opt[OPT_COUNT];
	unsigned int slowdown;
	uint16_t frame;
	bool skip_locked;

	void frame_delay(unsigned int frames);

	void run(bool grcg);
};

extern const Palette4 PALETTE_DEFAULT;
extern svc_t COL_CLEAR; // Set to -1 to disable per-frame VRAM clearing.
extern Test t;

// To be defined by the specific test
// ----------------------------------

extern const char BANNER[];

void test_update(void);
void test_render(void);
void test_main(void);
// ----------------------------------
