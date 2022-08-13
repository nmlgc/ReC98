#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/formats/grz.h"

void grcg_setcolor_rmw(int col)
{
	grcg_setcolor(GC_RMW, col);
}

void grcg_off_func(void)
{
	grcg_off();
}

void z_palette_set_all_show(const Palette4& pal)
{
	for(int i = 0; i < COLOR_COUNT; i++) {
		outportb(0xA8, i);
		outportb(0xAA, pal[i].c.g);
		outportb(0xAC, pal[i].c.r);
		outportb(0xAE, pal[i].c.b);
	}
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

int main(int argc, const char **argv)
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
	z_palette_set_all_show(boss8_grz_pal);

	grx_put(0);
	dos_getch();

	text_show();
	grx_free(0);
	return 0;
}
