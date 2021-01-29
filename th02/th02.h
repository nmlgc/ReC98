/* ReC98
 * -----
 * Include file for TH02
 */

#include "ReC98.h"
#include "th01/ranks.h"

#undef grcg_off

// Hardware
// -------
#include "th01/hardware/grppsafx.h"
// -------

// Music Room
#define MUSIC_CMT_FILE "MUSIC.TXT"
#define MUSIC_CMT_LINE_LEN 42
#define MUSIC_CMT_LINE_COUNT 20

extern char unused_op_2_3; // Maybe debug mode?
extern char rank;
extern char lives;
extern char bombs;

#define SHOTTYPE_COUNT 3
