// In TH02, ZUN messed up and swapped M and N in MIKOFT.BFT for both regular
// and bold fonts. Therefore, other code shouldn't really use the
// straightforward solution of just adding char literals to a defined start
// offset, as it may suggest that this also works for M and N (which it
// doesn't). This was fixed in later games.
#if (GAME == 2)
# define gb_MN_BUG gb_N_, gb_M_
#else
# define gb_MN_BUG gb_M_, gb_N_
#endif

#define gaiji_boldfont(start) \
	gb_0_ = start, \
	gb_1_, \
	gb_2_, \
	gb_3_, \
	gb_4_, \
	gb_5_, \
	gb_6_, \
	gb_7_, \
	gb_8_, \
	gb_9_, \
	gb_A_, \
	gb_B_, \
	gb_C_, \
	gb_D_, \
	gb_E_, \
	gb_F_, \
	gb_G_, \
	gb_H_, \
	gb_I_, \
	gb_J_, \
	gb_K_, \
	gb_L_, \
	gb_MN_BUG, \
	gb_O_, \
	gb_P_, \
	gb_Q_, \
	gb_R_, \
	gb_S_, \
	gb_T_, \
	gb_U_, \
	gb_V_, \
	gb_W_, \
	gb_X_, \
	gb_Y_, \
	gb_Z_
