#pragma option -zCSHARED

#include "libs/kaja/kaja.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th04/hardware/grcg.hpp"
#include "th05/op/piano.hpp"
#include "th05/sprites/piano_l.hpp"

/// Coordinates
/// -----------

static const screen_x_t PIANO_LEFT = 384;
static const pixel_t PIANO_KEY_W = 4;
static const pixel_t PIANO_BLACK_H = 9;
static const pixel_t PIANO_BLACK_PRESSED_H = 8;

static const int PIANO_OCTAVES = 8;
static const pixel_t PIANO_OCTAVE_W = (7 * PIANO_KEY_W);

static const vram_x_t PIANO_VRAM_LEFT = (PIANO_LEFT / BYTE_DOTS);
static const vram_byte_amount_t PIANO_VRAM_W = (
	(PIANO_OCTAVES * PIANO_OCTAVE_W) / BYTE_DOTS
);

static const pixel_t PIANO_LABEL_DIST_X = 32;
static const pixel_t PIANO_LABEL_DIST_Y = 4;

static inline screen_x_t label_left(int col) {
	return (PIANO_LEFT - PIANO_LABEL_DIST_X + (col * PIANO_LABEL_FONT_W));
}

static inline screen_x_t label_top(int row) {
	return 	(PIANO_TOP  + PIANO_LABEL_DIST_Y + (row * PIANO_H_PADDED));
}
/// -----------

// Sprite data
extern const dots8_t PIANO_KEYS_BLACK[PIANO_VRAM_W];

/// Note data
/// ---------

// Actually a single `OPEN_WORK far *`.
extern uint16_t pmd_workadr[2];

struct piano_notes_t {
	char fm[5];
	char unused[3]; // SSG?
};

extern piano_notes_t piano_notes_cur;
extern piano_notes_t piano_notes_prev;
/// ---------

/// ZUN bloat: Redundant garbage
/// ----------------------------

#define grcg_setmode(mode) { \
	_outportb_(0x7C, mode); \
}

#define grcg_off() _asm { \
	db 	0x32, 0xC0; /* XOR AL, AL (alternate encoding) */ \
	out	0x7C, al; \
}
/// ----------------------------

/// Helper functions
/// ----------------
extern "C" {

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// • `int fm_part_id` in SI
// • `void __seg *original_data_ds` in FS
// Draws a piano with the currently pressed note retrieved from [qq]. In
// addition to SI, the part is also indicated through the VRAM offset in
// ES:DI.
void __fastcall near piano_fm_part_put_raw(
	int16_t ax_unused, int16_t dx_unused, QQ near *near *qq
);
#define piano_fm_part_put(part_id, qq) \
	_DI = vram_offset_shift(0, piano_part_top(part_id)); \
	_asm { mov si, part_id; } \
	piano_fm_part_put_raw(_AX, _DX, qq);

// Returns the currently played note from [qq] as a KAJA onkai value, or
// ONKAI_REST if none is played.
char __fastcall near piano_current_note_from(
	int16_t ax_unused, int16_t dx_unused, QQ near *near *qq
);

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// Draws a blank piano, for the part is indicated through the VRAM offset in
// ES:DI.
void near piano_part_keys_put_raw();
inline void piano_part_keys_put(int part_id) {
	_DI = vram_offset_shift(0, piano_part_top(part_id));
	piano_part_keys_put_raw();
}

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// Draws the key given in [onkai] as pressed. The part is indicated through
// the VRAM offset in ES:DI.
void __fastcall near piano_pressed_key_put(char onkai);

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// Blits a piano label character to the top-left VRAM position indicated in
// ES:DI. Assumes that the GRCG is active.
void __fastcall near piano_label_put_raw(piano_label_t label_char);
inline void piano_label_putc(int col, int row, piano_label_t chr) {
	_AL = chr;
	_DI = vram_offset_muldiv(label_left(col), label_top(row));
	piano_label_put_raw(static_cast<piano_label_t>(_AL));
}
#define piano_label_puts(row, chr1, chr2, chr3) \
	piano_label_putc(0, row, pl_##chr1); \
	piano_label_putc(1, row, pl_##chr2); \
	piano_label_putc(2, row, pl_##chr3);
}
/// ----------------

void piano_setup_and_put_initial(void)
{
	grcg_setmode(GC_RMW);
	_ES = SEG_PLANE_B;
	// Thanks, Turbo C++, for indicating that SI actually didn't need to be
	// saved in this function!
	_SI = _SI;

	static_assert(PIANO_PART_COUNT == 6);
	piano_part_keys_put(0);
	piano_part_keys_put(1);
	piano_part_keys_put(2);
	piano_part_keys_put(3);
	piano_part_keys_put(4);
	piano_part_keys_put(5);

	grcg_setcolor_direct(5);
	piano_label_puts(0, F, M, 1);
	piano_label_puts(1, F, M, 2);
	piano_label_puts(2, F, M, 3);
	piano_label_puts(3, F, M, 4);
	piano_label_puts(4, F, M, 5);
	piano_label_puts(5, S, S, G);
	grcg_off();

	_asm { push	ds; }
	_AH = PMD_GET_WORKAREA_ADDRESS;
	geninterrupt(PMD);
	_AX = _DS;
	_asm { pop 	ds; }

	// pmd_workadr = reinterpret_cast<OPEN_WORK far *>(MK_FP(_DX, _AX));
	pmd_workadr[0] = _DX;
	pmd_workadr[1] = _AX;
}

void piano_render(void)
{
	_asm { push	ds; }
	_asm { push	ds; }
	__emit__(0x0F, 0xA1); // POP FS

	grcg_setmode(GC_RMW);
	_ES = SEG_PLANE_B;

	piano_part_keys_put(5);

	_asm { lds	bx, dword ptr pmd_workadr; }	// BX = FMPart[0]

	#define _BX	reinterpret_cast<QQ near *near *>(_BX)

	static_assert(PIANO_PART_COUNT == 6);
	piano_fm_part_put(0, _BX);	_BX++;	// BX = FMPart[1]
	piano_fm_part_put(1, _BX);	_BX++;	// BX = FMPart[2]
	piano_fm_part_put(2, _BX);	_BX++;	// BX = FMPart[3]
	piano_fm_part_put(3, _BX);	_BX++;	// BX = FMPart[4]
	piano_fm_part_put(4, _BX);

	grcg_setcolor_direct(5);
	_DI = vram_offset_shift(0, piano_part_top(5));
	_BX += 2;	// BX = SSGPart[0]
	piano_pressed_key_put(piano_current_note_from(_AX, _DX, _BX));
	_BX++;	// BX = SSGPart[1]
	piano_pressed_key_put(piano_current_note_from(_AX, _DX, _BX));

	#undef _BX

	grcg_off();

	_asm { pop 	ds; }
}
