/* ReC98
 * -----
 * Shared high score code
 */

#include "th02/hiscore/regist.h"

const char *SCOREDAT_FN = "huuhi.dat";
const unsigned char gbHI_SCORE[] = {
	gb_H, gb_I, gb__, gb_S, gb_C, gb_O, gb_R, gb_E, '\0'
};

const unsigned char gALPHABET[ALPHABET_ROWS][ALPHABET_COLS] = {
	gb_A, gb_B, gb_C, gb_D, gb_E, gb_F, gb_G, gb_H, gb_I, gb_J,
	gb_K, gb_L, gb_M, gb_N, gb_O, gb_P, gb_Q, gb_R, gb_S, gb_T,
	gb_U, gb_V, gb_W, gb_X, gb_Y, gb_Z,
	gs_BULLET, gs_PERIOD, gs_EXCLAMATION, gs_QUESTION, gs_ELLIPSIS,
	gs_HEART, gs_YINYANG, gs_BOMB,
	gb_0, gb_1, gb_2, gb_3, gb_4, gb_5, gb_6, gb_7, gb_8, gb_9,
	gs_SKULL, gs_GHOST, gs_SIDDHAM_HAM, gs_SPACE,
	gs_ARROW_LEFT, gs_ARROW_RIGHT, gs_END
};

const unsigned char gbNAME[] = { gb_N, gb_A, gb_M, gb_E, '\0' };
const unsigned char gbPOINT[] = { gb_P, gb_O, gb_I, gb_N, gb_T, '\0' };
const unsigned char gbST[] = { gb_S, gb_T, '\0' };
