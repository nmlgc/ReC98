// Pre-generating DOS environment blocks for process spawning
// ----------------------------------------------------------
// Only necessary if any changes to the environment variables made through
// [environ] should be passed on to the spawned process. Required for a correct
// implementation of spawning processes at the top of conventional DOS RAM, but
// not actually necessary for PC-98 Touhou since we don't mutate [environ].

#include "platform.h"
#include <alloc.h>

// Critical for removing the exception handling code that Turbo C++ 4.0J would
// generate for the destructor by default.
#pragma option -x-

struct SpawnEnv {
	char far* buf; // Unaligned heap allocation
	char __seg* buf_aligned; // Paragraph-aligned pointer into [env]
	uint16_t added_bytes;

	SpawnEnv(void);
	~SpawnEnv() {
		if(buf) {
			free(buf);
		}
	}
};
