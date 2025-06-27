// Cutscene/ending picture dimensions
// ----------------------------------

#include "game/cutscene.hpp"

extern const LTWH<upixel_t> CUTSCENE_QUARTERS[CUTSCENE_QUARTER_COUNT] = {
	{              0,              0, CUTSCENE_PIC_W, CUTSCENE_PIC_H },
	{ CUTSCENE_PIC_W,              0, CUTSCENE_PIC_W, CUTSCENE_PIC_H },
	{              0, CUTSCENE_PIC_H, CUTSCENE_PIC_W, CUTSCENE_PIC_H },
	{ CUTSCENE_PIC_W, CUTSCENE_PIC_H, CUTSCENE_PIC_W, CUTSCENE_PIC_H },
};
