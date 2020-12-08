#include "th01/sprites/main_ptn.h"
#include "th01/main/hud/hp.hpp"

/// Constants
/// ---------

static const screen_x_t HP_LEFT = 128;
static const vram_y_t HP_TOP = 48;
#define HP_POINT_W 8
#define HP_H 15
/// ---------

/// Foreground
/// ----------

// Yup, numbered right-to-left :zunpet:
enum hp_section_t {
	HP_SECTION_WHITE,
	HP_SECTION_REDWHITE,
	HP_SECTION_RED,

	_hp_section_t_FORCE_INT16 = 0x7FFF,
};

void grcg_set_redwhite(void)
{
	grcg_setmode(GC_RMW);	// Final color: (A7A7A7A7)
	outportb(0x7E, 0x55);	//           B: ( * * * *)
	outportb(0x7E, 0xFF);	//           R: (********)
	outportb(0x7E, 0x55);	//           G: ( * * * *)
	outportb(0x7E, 0xAA);	//           E: (* * * * )
}

void hp_put_with_section_pattern(int point, hp_section_t section)
{
	dots8_t dots = 0xFE; // (******* )
	vram_offset_t vo = (
		vram_offset_shift(HP_LEFT, HP_TOP) + (point * (HP_POINT_W / BYTE_DOTS))
	);

	if(section == HP_SECTION_RED) {
		grcg_setcolor_rmw(10);
	} else if(section == HP_SECTION_WHITE) {
		grcg_setcolor_rmw(7);
	} else if(section == HP_SECTION_REDWHITE) {
		grcg_set_redwhite();
	}

	for(unsigned char y = 0; y < HP_H; y++) {
		graph_accesspage_func(1);	grcg_put(vo, dots, HP_POINT_W);
		graph_accesspage_func(0);	grcg_put(vo, dots, HP_POINT_W);
		vo += ROW_SIZE;
	}
	grcg_off();
}
/// ----------
