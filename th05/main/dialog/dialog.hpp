#include "th04/main/dialog/dialog.hpp"
#include "pc98.h"

// Dialog-related image functions with optional EMS support
// --------------------------------------------------------

// Loads the face image at the given ID for the current [dialog_side] from
// either the EMS area or disk, then calls dialog_face_unput_8([left], [top]),
// blits the loaded image to the same position, and frees it again.
// Can also just unblit the face image without blitting a new one by setting
// [face_id] to FACE_NONE, if you don't like calling dialog_face_unput_8()
// directly for whatever reason.
void pascal near dialog_face_load_unput_put_free_8(
	screen_x_t left, vram_y_t top, int face_id
);

// Restores the bomb background image by loading it from either the EMS area
// or disk.
void near dialog_exit(void);
// --------------------------------------------------------
