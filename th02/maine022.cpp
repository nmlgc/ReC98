/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's MAINE.EXE
 */

#pragma codeseg SHARED

extern "C" {
#include <dos.h>
#include "libs/kaja/kaja.h"
#include "th02/th02.h"
#include "master.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/mem.h"
#include "th02/snd/snd.h"

#include "th02/snd/data.c"
const char pf_fn[] = PF_FN;

#include "th02/hardware/input.c"
#include "th02/exit.c"
#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
#include "th02/snd/pmd_res.c"
#include "th02/snd/load.c"

#pragma option -k

#include "th02/initmain.c"
}
