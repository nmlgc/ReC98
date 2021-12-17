// Shows the high score list for the current difficulty. If the given game
// result is good enough to be on there, the player is asked to enter a name,
// before the result is inserted and written to the high score file.
void regist(
	int32_t score, int16_t stage, const char route[SCOREDAT_ROUTE_LEN + 1]
);
