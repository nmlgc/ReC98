/* ReC98
 * -----
 * 1st part of code segment #2 of TH02's OP.EXE
 */

#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th02/resident.hpp"

resident_t *resident;
char unused_op_2_3;
char lives;
char bombs;
long unused_4;
long unused_5;

#include "th01/hardware/vplanset.c"
}
