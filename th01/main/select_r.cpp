// Writes the parameter for the current [rank] to [ret]. Duplicated for all
// bosses except YuugenMagan, for some reason...
// TODO: Should be `static` once all bosses have been decompiled.
void select_for_rank(
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
