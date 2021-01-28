/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's MAIN.EXE
 */

#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include <dos.h>
#include "libs/kaja/kaja.h"
#include "th02/th02.h"
#include "master.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/snd/snd.h"

#include "th02/hardware/input.c"
#include "th02/exit.c"
#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
}
