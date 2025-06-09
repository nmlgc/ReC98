#include "th04/op/op.hpp"
#include "th04/sprites/op_cdg.hpp"
#include "th04/shiftjis/fnshared.hpp"

void near main_cdg_load(void)
{
	op_cdg_load_shared();
	extern const char SL_CD2[];
	cdg_load_all_noalpha(CDG_PIC, SL_CD2);
}

void near main_cdg_free(void)
{
	cdg_free_all();
}
