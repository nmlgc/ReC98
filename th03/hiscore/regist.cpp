#pragma option -zPgroup_01

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th03/common.h"
#include "th03/score.h"
#include "th03/playchar.hpp"
#include "th03/resident.hpp"
#include "th03/sprites/regi.h"
#include "th03/formats/cdg.h"
#include "th03/formats/pi.hpp"
}
#include "th03/formats/scoredat.hpp"

#include "th03/formats/score_ld.cpp"
#include "th03/formats/score_es.cpp"

void near regist_load_and_put_initial(void)
{
	enum {
		RANK_IMAGE_W = 320,
		RANK_IMAGE_H = 88,
	};

	extern unsigned char near *rank_image_fn;
	extern const char regib_pi[];
	extern const char regi2_bft[];
	extern const char regi1_bft[];

	palette_black();
	graph_accesspage(0);
	graph_showpage(0);

	pi_load_put_8_free(0, regib_pi);

	// Kind of assumes that we only show this screen once for the lifetime of
	// the process.
	rank_image_fn[3] += resident->rank;

	cdg_load_single(0, rank_image_fn, 0);
	cdg_put_8((RES_X - RANK_IMAGE_W), (RES_Y - RANK_IMAGE_H), 0);
	cdg_free(0);

	super_entry_bfnt(regi2_bft);
	super_entry_bfnt(regi1_bft);

	graph_copy_page(1);
	graph_accesspage(0);
}
