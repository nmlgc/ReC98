/* ReC98
 * -----
 * Code segment #2 of TH02's MAIN.EXE
 */

#include "th02/th02.h"

extern char snd_active;

#define frame_delay_2 frame_delay

#include "th02/snd/kajafunc.c"
#include "th02/snd/delaymea.c"
#pragma codestring "\x00"
#include "th02/snd/se.c"
