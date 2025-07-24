// Subprocess spawning
// -------------------

#include "platform.h"

struct SpawnEnv;

// Spawns the given executable at the top of conventional RAM, assuming that it
// will take up the given number of bytes. Useful to keep TSRs from occupying
// the memory area directly after the program image, which would block the C
// heap from expanding. Returns the TSR's exit code, or -1 if memory couldn't
// be arranged for it to run.
// Potentially dangerous because there is no way to control the size of the
// automatically created DOS environment segment.
int pascal spawn_at_top_report(
	const uint32_t reserve_bytes,
	const char* path,
	const char *args,
	const SpawnEnv *env = nullptr
);

// Regular spawning immediately after this process in conventional RAM.
// Equivalent to the standard spawn() function, but using the same API as the
// above function for symmetry.
int pascal spawn_adjacent_report(
	const char* path, const char *args, const SpawnEnv *env = nullptr
);
