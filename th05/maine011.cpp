/* ReC98
 * -----
 * 2nd part of code segment #1 of TH05's MAINE.EXE
 */

#pragma codeseg maine_01_TEXT

extern "C" {
#include "th04/end/box.cpp"

/// String-to-color map
/// -------------------
/// Used to automatically change the text color whenever a specific
/// Shift-JIS codepoint is encountered.
static const int COLMAP_COUNT = 8;

typedef struct {
	twobyte_t kanji;
	int8_t padding[4]; // Might have been originally meant for full strings?
} colmap_key_t;

typedef struct {
	uint4_t values[COLMAP_COUNT];
	colmap_key_t keys[COLMAP_COUNT];
} colmap_t;

extern colmap_t colmap;
extern unsigned char colmap_count;
/// -------------------

extern unsigned char text_col;
}
