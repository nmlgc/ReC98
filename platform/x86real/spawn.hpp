// Subprocess spawning
// -------------------

#include "platform.h"

struct SpawnEnv;

static const uint16_t SPAWN_SPACER_ERROR = 0xFFFF;

struct SpawnSpacer {
	uint16_t prev_paras;

	operator bool(void) const {
		return (prev_paras == SPAWN_SPACER_ERROR);
	}
	void set_error(void) {
		prev_paras = SPAWN_SPACER_ERROR;
	}

	void pascal release(void);
};

// Resizes the DOS memory block of the current process to its largest possible
// size minus [payload_bytes], plus [process_count] times the guessed amount of
// memory that DOS will add to new processes. The environment block is assumed
// to be at least as large to additionally contain [max_binary_fn_len], without
// the terminating '\0'. Returns a spacer object that evaluates to `true` on
// failure and a more specific error code in [errno].
SpawnSpacer pascal spawn_claim_memory_minus(
	uint32_t payload_bytes,
	unsigned int process_count,
	unsigned int max_binary_fn_len,
	const SpawnEnv *env
);

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
