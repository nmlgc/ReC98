/* ReC98
 * -----
 * Code segment #2 of TH02's OP.EXE
 */

#include "th02/th02.h"

#pragma option -3
#pragma option -k-

char snd_active = 0;
char snd_unused = 0;

extern char snd_interrupt_if_midi;
extern char snd_fm_possible;
extern char snd_midi_active;

#include "th02/snd/se_data.c"

#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
#include "th02/snd/pmd_res.c"
#include "th02/snd/load.c"
#include "th02/formats/pi_put.c"
#include "th02/snd/kajafunc.c"
#include "th02/snd/delaymea.c"
#include "th02/snd/se.c"
#include "th02/hardware/frmdely1.c"
