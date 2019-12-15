/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's OP.EXE
 */

#include "th02/th02.h"
#include "th02/mem.h"
#include "th02/initexit.h"
#include "th02/formats/pi.h"

#pragma codeseg op_02_TEXT
#pragma option -3

const char pf_fn[] = PF_FN;
#include "th02/snd/data.c"
#include "th02/snd/se_data.c"

#include "th02/hardware/input.c"
#include "th02/initop.c"
#include "th02/exit.c"

#pragma codestring "\x00"

#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
#include "th02/snd/pmd_res.c"
#include "th02/snd/load.c"
#include "th02/formats/pi_put.c"
#include "th02/snd/kajaint.c"
#include "th02/snd/delaymea.c"
#include "th02/snd/se.c"
#include "th02/hardware/frmdely1.c"
