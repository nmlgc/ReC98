// Writes the parameter for the current [rank] to [ret]. Duplicated for all
// bosses except YuugenMagan, who has a much cleaner implementation that just
// returns the selected value.
static void select_for_rank(
	int &ret, int for_easy, int for_normal, int for_hard, int for_lunatic
)
{
	ret =
		(rank == RANK_EASY) ? for_easy :
		(rank == RANK_NORMAL) ? for_normal :
		(rank == RANK_HARD) ? for_hard :
		(rank == RANK_LUNATIC) ? for_lunatic :
		for_normal;
}

inline void select_subpixel_for_rank(
	subpixel_t& ret,
	float for_easy,
	float for_normal,
	float for_hard,
	float for_lunatic
) {
	select_for_rank(ret,
		to_sp(for_easy), to_sp(for_normal), to_sp(for_hard), to_sp(for_lunatic)
	);
}

inline void select_laser_speed_for_rank(
	int& ret,
	float for_easy,
	float for_normal,
	float for_hard,
	float for_lunatic
) {
	select_subpixel_for_rank(ret,
		(for_easy / 2), (for_normal / 2), (for_hard / 2), (for_lunatic / 2)
	);
}
