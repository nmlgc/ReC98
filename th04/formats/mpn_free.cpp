#pragma option -zCSHARED

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "libs/master.lib/master.hpp"
#include "th02/formats/tile.hpp"
#include "th04/formats/mpn.hpp"

void pascal mpn_free(int slot)
{
	mpn_t near &mpn = mpn_slots[slot];
	if(mpn.images) {
		hmem_free(static_cast<mpn_image_t __seg *>(mpn.images));
		mpn.images = nullptr;
	}
}
