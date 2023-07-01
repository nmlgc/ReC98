#pragma option -zCSHARED

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th04/main/playfld.hpp"
extern "C" {
#include "th04/main/tile/tile.hpp"
#include "th04/formats/mpn.hpp"

void pascal mpn_free(int slot)
{
	mpn_t near &mpn = mpn_slots[slot];
	if(mpn.images) {
		hmem_free(static_cast<mpn_image_t __seg *>(mpn.images));
		mpn.images = nullptr;
	}
}

}
