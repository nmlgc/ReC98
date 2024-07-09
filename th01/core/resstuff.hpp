#include "th01/resident.hpp"

// Allocates the resident structure if it doesn't exist yet, and initializes
// the given bunch of data with the respective values.
void resident_create_and_stuff_set(
	int8_t rank,
	bgm_mode_t bgm_mode,
	int8_t rem_bombs,
	int8_t credit_lives_extra,
	long rand
);

// Retrieves another incomplete bunch of data from the resident structure.
// Returns 0 on success, 1 on error.
int resident_stuff_get(
	int8_t& rank,
	bgm_mode_t& bgm_mode,
	int8_t& rem_bombs,
	int8_t& credit_lives_extra,
	unsigned long& rand,
	int32_t& continues_total,
	int& stage_id
);

// Frees the resident structure if it exists.
void resident_free(void);
