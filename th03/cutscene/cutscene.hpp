#include "platform.h"

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

// Runs the loaded cutscene script in a blocking way.
void near cutscene_animate(void);
