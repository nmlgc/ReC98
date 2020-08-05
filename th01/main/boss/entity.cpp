#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/formats/bos.hpp"

void bos_reset_all_broken(void)
{
	for(int slot = 0; slot < 10; slot++) { // should be BOS_SLOT_COUNT
		for(int image = 0; image < BOS_IMAGES_PER_SLOT; image++) {
			bos_images[slot].image[image].alpha = NULL;
			bos_images[slot].image[image].planes.B = NULL;
			bos_images[slot].image[image].planes.R = NULL;
			bos_images[slot].image[image].planes.G = NULL;
			bos_images[slot].image[image].planes.E = NULL;
		}
	}
}
