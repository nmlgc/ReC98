/* ReC98
 * -----
 * Shared high score code
 */

const char *SCOREDAT_FN = "huuhi.dat";
const unsigned char gbHI_SCORE[] = {
	gb_H_, gb_I_, gb_SP, gb_S_, gb_C_, gb_O_, gb_R_, gb_E_, 0
};

#define ALPHABET_ROWS 3
#define ALPHABET_COLS 17
const unsigned char gALPHABET[ALPHABET_ROWS][ALPHABET_COLS] = {
	gb_A_, gb_B_, gb_C_, gb_D_, gb_E_, gb_F_, gb_G_, gb_H_, gb_I_, gb_J_,
	gb_K_, gb_L_, gb_M_, gb_N_, gb_O_, gb_P_, gb_Q_, gb_R_, gb_S_, gb_T_,
	gb_U_, gb_V_, gb_W_, gb_X_, gb_Y_, gb_Z_,
	gs_BULLET, gs_PERIOD, gs_EXCLAMATION, gs_QUESTION, gs_ELLIPSIS,
	gs_HEART, gs_YINYANG, gs_BOMB,
	gb_0_, gb_1_, gb_2_, gb_3_, gb_4_, gb_5_, gb_6_, gb_7_, gb_8_, gb_9_,
	gs_SKULL, gs_GHOST, gs_SIDDHAM_HAM, gs_SPACE,
	gs_ARROW_LEFT, gs_ARROW_RIGHT, gs_END
};

const unsigned char gbNAME[] = {gb_N_, gb_A_, gb_M_, gb_E_, 0};
const unsigned char gbPOINT[] = {gb_P_, gb_O_, gb_I_, gb_N_, gb_T_, 0};
const unsigned char gbST[] = {gb_S_, gb_T_, 0};

#define ATRB_SET(place) \
	if((place) == place_to_highlight) { \
		atrb = TX_GREEN; \
	} else { \
		atrb = TX_WHITE; \
	}
