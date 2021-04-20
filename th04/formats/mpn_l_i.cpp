#pragma option -zCSHARED

extern "C" {
#include <stddef.h>
#include <mem.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th04/main/playfld.h"
#include "th04/main/tile.hpp"
#include "th04/formats/mpn.hpp"

void pascal mpn_palette_show(int slot)
{
	palette_set_all(mpn_slots[slot].palette);
	palette_show();
}

}
