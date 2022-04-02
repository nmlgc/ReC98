/* ReC98
 * -----
 * 1st part of code segment #13 of TH01's REIIDEN.EXE
 */

#pragma option -2 -Z-

#include <dos.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "master.hpp"
extern "C" {
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"

#include "th01/hardware/scrollup.cpp"
#include "th01/hardware/egcrows.cpp"
#include "th01/hardware/ptrans_d.cpp"
}
