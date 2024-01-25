/* ReC98
 * -----
 * Code segment #3 of TH02's MAIN.EXE
 */

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th02/math/randring.hpp"

#define RANDRING_INSTANCE 2
#include "th02/math/randring.cpp"

extern "C" {
#include "th02/main/bullet/pellet_r.cpp"
}
