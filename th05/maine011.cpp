/* ReC98
 * -----
 * 2nd part of code segment #1 of TH05's MAINE.EXE
 */

#pragma option -zCmaine_01_TEXT

#include "th04/cutscene/box.cpp"

/// String-to-color map
/// -------------------
/// Used to automatically change the text color whenever a specific
/// Shift-JIS code point is encountered.

static const int COLMAP_COUNT = 8;

typedef struct {
	uint4_t values[COLMAP_COUNT];

	// Might have been originally meant for a complete character name?
	shiftjis_kanji_t keys[COLMAP_COUNT][NAME_KANJI_LEN];
} colmap_t;

extern colmap_t colmap;
extern unsigned char colmap_count;
/// -------------------
