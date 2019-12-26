/* ReC98
 * -----
 * Code segment #1 of TH05's OP.EXE
 */

extern "C" {

#include "platform.h"
#include "th01/ranks.h"
#include "th04/formats/scoredat.h"
#include "th05/player/chars.h"

scoredat_section_t hi;
scoredat_section_t hi2;
static uint8_t scoredat_unused;

unsigned char hiscore_rank;
unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];
bool extra_unlocked;
static uint8_t unused_2;
unsigned char playchar_menu_sel;
static uint8_t unused_1;
unsigned char rank;
static uint8_t unused_0[4];
bool extra_playable_with[PLAYCHAR_COUNT];
bool selectable_with[PLAYCHAR_COUNT];

}
