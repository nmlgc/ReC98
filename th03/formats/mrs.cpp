#pragma codeseg SHARED

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th03/formats/hfliplut.h"
#include "th03/formats/mrs.hpp"

static const vram_byte_amount_t MRS_BYTE_W = (MRS_W / BYTE_DOTS);
static const vram_dword_amount_t MRS_DWORD_W = (MRS_BYTE_W / sizeof(dots32_t));

struct mrs_plane_t {
	dots32_t dots[MRS_DWORD_W][MRS_H];
};

// On-disk per-image structure
struct mrs_t {
	mrs_plane_t alpha;
	Planar<mrs_plane_t> planes;
};

extern mrs_t far *mrs_images[MRS_SLOT_COUNT];

// Points [reg_sgm]:[reg_off] to the alpha plane of the .MRS image in the
// given [slot].
#define mrs_slot_assign(reg_sgm, reg_off, slot) { \
	_BX = slot; \
	_BX <<= 2; \
	__asm { l##reg_sgm reg_off, mrs_images[bx]; } \
}

void pascal mrs_hflip(int slot)
{
	_CX = sizeof(mrs_t);
	mrs_slot_assign(es, di, slot);
	reinterpret_cast<dots8_t near *>(_BX) = hflip_lut;

	flip_dots_within_bytes: __asm {
		mov 	al, es:[di];
		xlat;
		mov 	es:[di], al;
		inc 	di;
		loop	flip_dots_within_bytes;
	}

	_CX = (sizeof(mrs_t) / MRS_BYTE_W);
	/* vram_byte_amount_t offset_y */ _BX = 0;

	flip_bytes: {
		// Assumes that the offset part of all image pointers is 0. Storing
		// segment pointers in [mrs_images] would have been clearer in this
		// case...
		/* vram_byte_amount_t offset_left  */ _DI = 0;
		/* vram_byte_amount_t offset_right */ _SI = (MRS_BYTE_W - 1);
		do {
			__asm {
				mov al, es:[bx+di]
				mov dl, es:[bx+si]
				mov es:[bx+si], al
				mov es:[bx+di], dl
			}
			_SI--;
			_DI++;
		} while(_DI <= ((MRS_BYTE_W / 2) - 1));
		_BX += MRS_BYTE_W;
		__asm { loop flip_bytes; }
	}
}

#pragma codestring "\x90"
