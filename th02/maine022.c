/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's MAINE.EXE
 */

#include "th02/th02.h"
#include "th02/mem.h"
#include "th02/formats/pi.h"

#pragma codeseg maine_02_TEXT

#include "th02/snd/data.c"
const char pf_fn[] = PF_FN;

#define frame_delay_2 frame_delay

#include "th02/hardware/input.c"
#include "th02/exit.c"
#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
#include "th02/snd/pmd_res.c"
#include "th02/snd/load.c"

#pragma option -k

#include "th02/initmain.c"
#include "th02/formats/pi_put.c"
#include "th02/snd/kajaint.c"
#include "th02/snd/delaymea.c"
