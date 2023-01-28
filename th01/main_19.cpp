/* ReC98
 * -----
 * Code segment #19 of TH01's REIIDEN.EXE
 */

#include <string.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/shiftjis/regist.hpp"
#include "th01/formats/scoredat.hpp"

#define graph_printf_fx graph_putsa_fx
#define graph_printf_s_fx graph_putsa_fx

#include "th01/hiscore/regist.cpp"
