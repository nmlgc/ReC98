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

// A completely hidden timeout that force-enters a high score name after
// 1000... *keyboard inputs*? Not frames? Why. Like, how do even you
// realistically get to such a number.
// (Best guess: It's a hidden easter egg to amuse players who place drinking
// glasses on cursor keys. Or beer bottles.)
#define regist_input_timeout_declare() unsigned int timeout;
#define regist_input_timeout_reset() timeout = 0;
#define regist_input_timeout_inc() timeout++;
#define regist_input_timeout_if_reached(then) if(timeout > 1000) then

#include "th01/hiscore/regist.cpp"
