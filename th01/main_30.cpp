/* ReC98
 * -----
 * Code segment #30 of TH01's REIIDEN.EXE
 */

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/main/debug.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/bomb.hpp"
#include "th01/snd/mdrv2.h"
}
#include "th01/main/hud/hud.hpp"
#include "th01/main/stage/item.hpp"
#include "th01/main/stage/stageobj.hpp"

#include "th01/main/stage/card_hit.cpp"
#include "th01/core/str_val.cpp"
