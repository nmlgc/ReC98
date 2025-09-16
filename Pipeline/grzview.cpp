#include <stdio.h>
#include <stdlib.h>
#include "planar.h"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "platform/palette.hpp"
#include "th01/formats/grz.h"

void grcg_setcolor_rmw(vc2 col)
{
	grcg_setcolor(GC_RMW, col);
}

void grcg_off_func(void)
{
	grcg_off();
}

const Palette4 boss8_grz_pal = {
	0x0, 0x0, 0x0,
	0x5, 0x5, 0x5,
	0xC, 0x2, 0x2,
	0x1, 0x0, 0x6,
	0x6, 0x5, 0x9,
	0x8, 0x8, 0xA,
	0xC, 0xB, 0xC,
	0xF, 0xF, 0xF,
	0x1, 0x3, 0xA,
	0x0, 0x8, 0x9,
	0xF, 0x0, 0x0,
	0xA, 0x0, 0x0,
	0x0, 0x0, 0x0,
	0xF, 0xF, 0x0,
	0xE, 0xB, 0xA,
	0x9, 0x9, 0x9,
};

int __cdecl main(int argc, const char **argv)
{
	if((get_machine() & PC9801) == 0) {
		printf("This program must be run on a PC-98.\n");
		return -1;
	}
	if(argc != 3) {
		printf(
			".GRZ viewer\n"
			"Usage: %s filename.grz subimage\n",
			argv[0]
		);
		return 1;
	}
	unsigned int subimage = atoi(argv[2]);
	if(subimage >= GRZ_IMAGE_COUNT) {
		printf("subimage must be between 0 and %u\n", GRZ_IMAGE_COUNT - 1);
		return 3;
	}
	if(grz_load_single(0, argv[1], subimage)) {
		printf("Error loading %s\n", argv[1]);
		return 2;
	}
	text_hide();
	graph_start();
	palette_show(boss8_grz_pal);

	grx_put(0);
	dos_getch();

	text_show();
	grx_free(0);
	return 0;
}
