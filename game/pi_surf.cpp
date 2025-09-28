// Temporary implementation of the original .PI interface via GrpSurface
// ---------------------------------------------------------------------

#define GAME 5

#include "th02/formats/pi.h"
#include "platform/grp_surf.hpp"

struct pi_surface_slot_t {
	GrpSurface_M4 surf;
	Palette8 palette;
};

pi_surface_slot_t pi_surface_slots[8];

int pi_load(int slot, const char *fn, pi_flag_t flags)
{
	pi_surface_slot_t near& slot_ref = pi_surface_slots[slot];
	return GrpSurface_LoadPI(slot_ref.surf, &slot_ref.palette, fn, flags);
}

int pi_load(int slot, const char *fn)
{
	return pi_load(slot, fn, PIF_NONE);
}

int pi_load_lineskip(int slot, const char *fn)
{
	return pi_load(slot, fn, PIF_LINESKIP);
}

void pi_palette_apply(int slot)
{
	Palettes = pi_surface_slots[slot].palette;
	palette_show();
}

void pi_free(int slot)
{
	pi_surface_slots[slot].surf.free();
	// The games actually use the palette after freeing the pixels!
}

void pi_put_8(screen_x_t left, vram_y_t top, int slot)
{
	pi_surface_slots[slot].surf.write(left, top);
}
