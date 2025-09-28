#include "platform.h"

// Frees any previously loaded cutscene script, allocates a new one with [fn]'s
// file size, and loads it from the file. Returns `false` on success.
bool16 pascal near cutscene_script_load(const char *fn);

// Frees the cutscene script.
void near cutscene_script_free();

// Runs the loaded cutscene script in a blocking way.
void near cutscene_animate(void);
