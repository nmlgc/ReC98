#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"

static const int MUSIC_CMT_LINE_LEN = 42;
static const int MUSIC_CMT_LINE_COUNT = 20;

dots8_t *nopoly_B;
Planar<dots8_t far *> cmt_bg;
shiftjis_t music_cmt[MUSIC_CMT_LINE_COUNT][MUSIC_CMT_LINE_LEN];
