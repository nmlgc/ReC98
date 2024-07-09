#include "th01/core/entry.hpp"

// Sets up the 640x400 graphics + text mode, as well as the vsync callback.
void game_init(void);

// Clears all text and fades out the graphics layer to prepare for exiting the
// game.
void game_exit(void);

// Clears all text, fades out the graphics layer, and executes another binary.
// (Mostly the same as game_exit().)
void game_switch_binary(entrypoint_t entrypoint);
