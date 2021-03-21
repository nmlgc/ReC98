/* ReC98
 * -----
 * 2nd part of code segment #1 of TH01's REIIDEN.EXE
 */

#pragma option -zCmain_01__TEXT -zPmain_01

extern "C" {
#include "ReC98.h"
#include "master.hpp"
#include "th01/hardware/egc.h"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/stage/palette.hpp"
}

#include "th01/main/stage/palette.cpp"
#include "th01/main/player/inv_spr.cpp"

extern "C" {
#include "th01/main/player/orb.cpp"
}
