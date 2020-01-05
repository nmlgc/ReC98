#pragma option -Z

extern "C" {
#include <dos.h>
#include "ReC98.h"
#include "th01/hardware/palette.hpp"

// Resident palette
// ----------------
#define RESPAL_ID "pal98 grb"
struct hack { char x[sizeof(RESPAL_ID)]; }; // XXX
extern const hack PAL98_GRB;

#pragma option -a1
// MASTER.MAN suggests that GBR ordering is some sort of standard on PC-98.
// It does match the order of the hardware's palette register ports, after
// all. (0AAh = green, 0ACh = red, 0AEh = blue)
struct grb_t {
	uint4_t g, r, b;
};

struct respal_t {
	char id[sizeof(RESPAL_ID)];
	unsigned char tone;
	int8_t padding[5];
	grb_t pal[COLOR_COUNT];
};
// ----------------

// Memory Control Block
// Adapted from FreeDOS' kernel/hdr/mcb.h
// --------------------
#define MCB_NORMAL 0x4d
#define MCB_LAST   0x5a

struct mcb_t {
	uint8_t m_type;	// mcb type - chain or end
	uint16_t __seg* m_psp;	// owner id via psp segment
	uint16_t m_size;	// size of segment in paragraphs
	uint8_t m_fill[3];
	uint8_t m_name[8];
};
#pragma option -a.

respal_t __seg* z_respal_exist(void)
{
	union REGS regs;
	struct SREGS sregs;
	const hack ID = PAL98_GRB;
	seg_t mcb;
	int i;

#define MCB reinterpret_cast<mcb_t __seg *>(mcb)	/* For easy derefencing */
#define MCB_PARAS (sizeof(mcb_t) / 16)	/* For segment pointer arithmetic */

	// "Get list of lists"
	segread(&sregs);
	regs.h.ah = 0x52;
	intdosx(&regs, &regs, &sregs);

	mcb = *reinterpret_cast<seg_t *>(MK_FP(sregs.es, regs.w.bx - 2));
	while(1) {
		if(MCB->m_psp != 0) {
			for(i = 0; i < sizeof(ID); i++) {
				if(reinterpret_cast<respal_t *>(MCB + 1)->id[i] != ID.x[i]) {
					break;
				}
			}
			if(i == sizeof(ID)) {
				return reinterpret_cast<respal_t __seg *>(mcb + MCB_PARAS);
			}
		}
		if(MCB->m_type != MCB_NORMAL) {
			return 0;
		}
		mcb += MCB_PARAS + MCB->m_size;
	};

#undef MCB_PARAS
#undef MCB
}

int z_respal_get_show(void)
{
	int i;
	respal_t __seg *respal_seg = z_respal_exist();
	if(respal_seg) {
		grb_t *respal = respal_seg->pal;
		for(i = 0; i < COLOR_COUNT; i++) {
			/* TODO: Replace with the decompiled call
			 * z_palette_set_show(i, respal->r, respal->g, respal->b);
			 * once that function is part of this translation unit */
			__asm {
				les 	bx, respal
				mov 	al, es:[bx+2]
				cbw
				push	ax
				mov 	al, es:[bx+0]
				cbw
				push	ax
				mov 	al, es:[bx+1]
				cbw
				push	ax
				// Spelling out PUSH SI causes Turbo C++ to interpret SI as
				// reserved, and it then moves [i] to DI rather than SI
				db	0x56
				push	cs
				call	near ptr z_palette_set_show
				add 	sp, 8
			}
			respal++;
		}
		return 0;
	}
	return 1;
}

int z_respal_set(void)
{
	int i;
	respal_t __seg *respal_seg = z_respal_exist();
	if(respal_seg) {
		grb_t *respal = respal_seg->pal;
		for(i = 0; i < COLOR_COUNT; i++) {
			respal->g = z_Palettes.colors[i].c.g;
			respal->r = z_Palettes.colors[i].c.r;
			respal->b = z_Palettes.colors[i].c.b;
			respal++;
		}
		return 0;
	}
	return 1;
}

}
