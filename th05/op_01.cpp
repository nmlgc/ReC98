/* ReC98
 * -----
 * Code segment #1 of TH05's OP.EXE
 */

extern "C" {

#include "ReC98.h"
#include "th01/ranks.h"
#include "th04/formats/scoredat.h"
#include "th05/chars.h"
#include "th04/op/op.h"

scoredat_section_t hi;
scoredat_section_t hi2;
static uint8_t scoredat_unused;

unsigned char hiscore_rank;
unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];
bool extra_unlocked;


}
