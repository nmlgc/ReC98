// Retrieves another incomplete bunch of data from the resident structure.
// Returns 0 on success, 1 on error.
int resident_stuff_get(
	int8_t& rank,
	bgm_mode_t& bgm_mode,
	int8_t& bombs,
	int8_t& start_lives_extra,
	unsigned long& rand,
	long& continues_total,
	int& stage_id
);
