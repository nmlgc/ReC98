extern "C" {
#if (GAME == 5)
	#include "th05/hardware/input.h"
#elif (GAME == 4)
	#include "th04/hardware/input.h"
#else
	#include "th03/hardware/input.h"
#endif
}

static const shiftjis_ank_amount_t NAME_LEN = 6;
static const shiftjis_kanji_amount_t NAME_KANJI_LEN = (
	NAME_LEN / sizeof(shiftjis_kanji_t)
);

// Adding a fullwidth colon after the name
static const pixel_t NAME_W = ((NAME_LEN * GLYPH_HALF_W) + GLYPH_FULL_W);

// Note that this does not correspond to the tiled area painted into TH05's
// EDBK?.PI images.
static const screen_x_t BOX_LEFT = 80;
static const screen_y_t BOX_TOP = 320;
static const pixel_t BOX_W = 480;
static const pixel_t BOX_H = (GLYPH_H * 4);

static const vram_byte_amount_t BOX_VRAM_W = (BOX_W / BYTE_DOTS);
static const screen_x_t BOX_RIGHT = (BOX_LEFT + BOX_W);
static const screen_y_t BOX_BOTTOM = (BOX_TOP + BOX_H);

extern Planar<dots16_t>* box_bg;

// Skips most delays during the cutscene if `true`.
extern bool fast_forward;

// [y] is always aligned to GLYPH_H pixels.
extern screen_point_t cursor;

extern int text_interval;

// Loads the cutscene script from the given file, returning `false` on success.
// TH03 frees the previously loaded script and allocates a new one with [fn]'s
// file size before loading it from the file.
bool16 pascal near cutscene_script_load(const char *fn);

// Frees the cutscene script. No-op in TH04 and TH05, where it's statically
// allocated.
#if (GAME == 5)
	inline void cutscene_script_free() {
	}
#else
	void near cutscene_script_free();
#endif

// ZUN quirk: The cutscene system features both
// 1) a top-level input sensing mechanism (for updating the fast-forward flag),
//    and
// 2) nested, blocking input loops (during all the interruptable wait commands)
//    which are skipped based on the fast-forward flag.
// With this combination, the accurate detection of held keys matters: Since
// this function is only called once on every iteration of the loop before
// evaluating a command, a momentary key release scancode from 1) can cause 2)
// to be entered even if the fast-forward key is still being held. Only TH03's
// and TH05's input functions defend against this possibility – at the cost of
// 614.4 µs for every call to them. TH04's cutscene system does suffer from the
// detection issue, but runs significantly faster in exchange, as it's not
// slowed down on every iteration of the script interpreter loop, i.e., between
// every script command or 2-byte text pair.
inline void cutscene_input_sense(void) {
	#if (GAME == 5)
		input_reset_sense_held();
	#elif (GAME == 4)
		input_reset_sense();
	#elif (GAME == 3)
		input_mode_interface();
	#endif
}
