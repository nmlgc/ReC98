/* ReC98
 * -----
 * Code segment #32 of TH01's REIIDEN.EXE
 */

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/graph.h"
#include "th01/snd/mdrv2.h"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/debug.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/shot.hpp"
}
#include "th01/main/hud/hud.hpp"
#include "th01/main/boss/palette.hpp"

#include "th01/main/boss/nop.cpp"
#include "th01/main/hud/hp.cpp"
#include "th01/main/boss/hit.cpp"
