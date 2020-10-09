extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/sprfmt_h.hpp"
#include "th01/formats/bos.hpp"
#include "th01/main/player/anim.hpp"
}

int CPlayerAnim::load(const char fn[PF_FN_LEN])
{
	vram_byte_amount_t plane_size;
	vram_byte_amount_t bos_p;

	bos_header_load(this, plane_size, fn, false);
	// MODDERS: [bos_image_count] must be < [PLAYER_ANIM_IMAGES_PER_SLOT]
	for(int i = 0; bos_image_count > i; i++) {
		alpha[i] = new dots8_t[plane_size];
		planes.B[i] = new dots8_t[plane_size];
		planes.R[i] = new dots8_t[plane_size];
		planes.G[i] = new dots8_t[plane_size];
		planes.E[i] = new dots8_t[plane_size];
		arc_file_get(reinterpret_cast<char *>(alpha[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.B[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.R[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.G[i]), plane_size);
		arc_file_get(reinterpret_cast<char *>(planes.E[i]), plane_size);

		for(bos_p = 0; bos_p < plane_size; bos_p++) {
			alpha[i][bos_p] = ~alpha[i][bos_p];
			planes.B[i][bos_p] &= alpha[i][bos_p];
			planes.R[i][bos_p] &= alpha[i][bos_p];
			planes.G[i][bos_p] &= alpha[i][bos_p];
			planes.E[i][bos_p] &= alpha[i][bos_p];
		}
	}
	arc_file_free();
	return 0;
}
