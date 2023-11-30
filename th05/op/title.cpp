#include "platform.h"
#include "pc98.h"
#include "planar.h"
extern "C" {
#include "th03/formats/cdg.h"
#include "th04/op/op.hpp"
#include "th04/snd/snd.h"
}
#include "th05/playchar.h"
#include "th04/sprites/op_cdg.hpp"

void near main_cdg_load(void)
{
	op_cdg_load_shared();
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_REIMU), "sl00.cdg", 0);
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_MARISA), "sl01.cdg", 0);
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_MIMA), "sl02.cdg", 0);
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_YUUKA), "sl03.cdg", 0);
	cdg_load_single(CDG_CLEARED, "slcl.cdg", 0);
	cdg_load_single_noalpha(CDG_PIC_NOT_CLEARED, "sl04.cdg", 0);
}

void near main_cdg_free(void)
{
	cdg_free_all();
}
