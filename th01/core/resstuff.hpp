// Retrieves another incomplete bunch of data from the resident structure.
// Returns 0 on success, 1 on error.
int resident_stuff_get(
	char& rank,
	int8_t& bgm_mode,
	char& bombs,
	char& start_lives_extra,
	unsigned long& rand,
	long& continues_total,
	int& stage_id
);
