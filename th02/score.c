/* ReC98
 * -----
 * Shared high score code
 */

#include "th02/hiscore/regist.h"
#include "th02/gaiji/str.hpp"

const char *SCOREDAT_FN = "huuhi.dat";
const unsigned char gbHI_SCORE[] = { g_chr_8(gb, H,I,_,S,C,O,R,E), '\0' };

const unsigned char gALPHABET[ALPHABET_ROWS][ALPHABET_COLS] = {
	g_chr_17(gb, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q),

	g_chr_9(gb, R, S, T, U, V, W, X, Y, Z),
	g_chr_8(gs, BULLET,PERIOD,EXCLAMATION,QUESTION,ELLIPSIS,HEART,YINYANG,BOMB),

	g_chr_10(gb, 0, 1, 2, 3, 4 ,5, 6, 7, 8, 9),
	g_chr_7(gs, SKULL, GHOST, SIDDHAM_HAM, SPACE, ARROW_LEFT, ARROW_RIGHT, END),
};

const unsigned char gbNAME[] = { g_chr_4(gb, N,A,M,E), '\0' };
const unsigned char gbPOINT[] = { g_chr_5(gb, P,O,I,N,T), '\0' };
const unsigned char gbST[] = { g_chr_2(gb, S,T), '\0' };
