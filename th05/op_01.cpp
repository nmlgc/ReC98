/* ReC98
 * -----
 * Code segment #1 of TH02's OP.EXE
 */

extern "C" {

#include "platform.h"
#include "th01/ranks.h"
#include "th05/player/chars.h"

static uint8_t padding;

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
