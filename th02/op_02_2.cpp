/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's OP.EXE
 */

#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include "platform.h"
#include "master.hpp"
#include "th02/mem.h"
#include "th02/core/initexit.h"
#include "th02/formats/pf.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"

const char pf_fn[] = PF_FN;
#include "th02/snd/data.c"
#include "th02/snd/se_data.c"

#include "th02/hardware/input.c"
#include "th02/core/initop.cpp"
}
