#include "platform/x86real/pc98/page.hpp"
#include "th01/v_colors.hpp"
#include "th01/hardware/grcg.hpp"
#include "th01/main/hud/hp.hpp"

/// Constants
/// ---------

static const screen_x_t HP_LEFT = 128;
static const vram_y_t HP_TOP = 48;
/// ---------

/// Foreground
/// ----------

void grcg_set_redwhite(void)
{
	grcg_setmode(GC_RMW);	// Final color: (A7A7A7A7)
	outportb(0x7E, 0x55);	//           B: ( * * * *)
	outportb(0x7E, 0xFF);	//           R: (********)
	outportb(0x7E, 0x55);	//           G: ( * * * *)
	outportb(0x7E, 0xAA);	//           E: (* * * * )
}

void hp_put(int point)
{
	dots8_t dots = 0xFE; // (******* )
	vram_offset_t vo = (
		vram_offset_shift(HP_LEFT, HP_TOP) + (point * (HP_POINT_W / BYTE_DOTS))
	);

	if(point < hud_hp_first_redwhite) {
		grcg_setcolor_rmw(V_RED);
	} else if(point < hud_hp_first_white) {
		grcg_set_redwhite();
	} else {
		grcg_setcolor_rmw(V_WHITE);
	}

	for(unsigned char y = 0; y < HP_H; y++) {
		page_access(1);	grcg_put(vo, dots, HP_POINT_W);
		page_access(0);	grcg_put(vo, dots, HP_POINT_W);
		vo += ROW_SIZE;
	}
	grcg_off_func();
}
/// ----------

/// Background
/// ----------
/// Whew, using a 16x16 wrapper around a 32x32 set of graphics functions in
/// order to handle backgrounds for 8x16 sprites... That's quite the recipe
/// for confusion. *Especially* if you don't write functions to abstract away
/// this needless complexity.

#if (HP_POINT_W != (PTN_QUARTER_W / 2))
	#error Original code assumes HP_POINT_W == (PTN_QUARTER_W / 2)
#endif

static const pixel_t HP_2POINT_W = PTN_QUARTER_W;

#define hp_bg_left(point_divided_by_2) \
	(((point_divided_by_2) * HP_2POINT_W) + HP_LEFT)

// As a result, this one ends up always being called twice as often (i.e., for
// each hit point) as it needs to be (i.e., once for every 2 HP).
// ZUN bug: This further limits HP_MAX to half of its value.
#define hp_bg_snap_nth_doublepoint(point_divided_by_2) \
	ptn_snap_quarter_8(\
		hp_bg_left(point_divided_by_2), \
		HP_TOP, \
		(((point_divided_by_2) / 4) + PTN_BG_HP), \
		((point_divided_by_2) % 4) \
	)

#define hp_bg_put_doublepoint_containing(point) \
	ptn_put_quarter_noalpha_8( \
		hp_bg_left((point) / 2), \
		HP_TOP, \
		(((point) / 8) + PTN_BG_HP), \
		(((point) / 2) % 4) \
	)
/// ---------

void hud_hp_decrement(int hp_total_new)
{
	page_access(1); hp_bg_put_doublepoint_containing(hp_total_new);
	page_access(0); hp_bg_put_doublepoint_containing(hp_total_new);
	// Since a .PTN quarter stores the background of two hit points, the calls
	// above will unblit two hit points if [hp_total_new] is odd. So...
	if((hp_total_new & 1) == 1) {
		hp_put(hp_total_new - 1);
	}
}

void hud_hp_rerender(int hp_total)
{
	for(int i = 0; i < hp_total; i++) {
		hp_bg_snap_nth_doublepoint(i);
		hp_put(i);
	}
}

void hud_hp_increment_render(bool& done, int hp_total, int hp_cur)
{
	if(done) {
		return;
	}
	// ZUN bug: [hp_cur] should be limited to (HP_MAX / 2) here to prevent
	// heap corruption.
	hp_bg_snap_nth_doublepoint(hp_cur);
	hp_put(hp_cur);

	// ZUN bug: Should be <= to ensure that the incrementing process always
	// completes.
	done = ((hp_total - 1) == hp_cur);
}
