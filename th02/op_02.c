/* ReC98
 * -----
 * Code segment #2 of TH02's OP.EXE
 */

#include "th02/th02.h"

char snd_active = 0;
char snd_unused = 0;

extern char snd_midi_active;

#include "th02/snd/se_data.c"

#include "th02/snd/kajafunc.c"
#include "th02/snd/delaymea.c"
#include "th02/snd/se.c"
#include "th02/hardware/frmdely1.c"
